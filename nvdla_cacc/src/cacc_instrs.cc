// File: cacc_instrs.cc

#include <ilang/ilang++.h>
#include <cacc_config.h>
#include <math.h>

using namespace std;

namespace ilang {

    //////////////////////////////////////////////////////////////////////////////
    /// UNINTERPRETED FUNCTIONS
    //////////////////////////////////////////////////////////////////////////////

    // Return 32-bit respresention of fp44.
    ExprRef fp44_to_fp32(ExprRef num){
        // <Implement code>
        return BvConst(0, NVDLA_CACC_OUTPUT_BIT_WIDTH);
    }

    // Return sum of fp44 and fp16 numbers (a and b respectively). Output should be stored in 
    // in a 48-bit state.
    ExprRef accu_fp16_add(ExprRef a, ExprRef b){
        // <Implement code>
        return BvConst(0, NVDLA_CACC_ACCU_INT16_BIT_WIDTH);
    }

    //////////////////////////////////////////////////////////////////////////////
    /// HELPER FUNCTIONS
    //////////////////////////////////////////////////////////////////////////////

    // Return the new register state after new_value is inserted in the field specified by the
    // given mask_value and offset 
    ExprRef get_updated_reg_value(ExprRef old_reg, ExprRef new_value, int mask_val, int offset){
        auto mask = BvConst((mask_val << offset), NVDLA_CACC_REG_WIDTH);
        auto tmp = (old_reg & (~mask)) | ((new_value.ZExt(NVDLA_CACC_REG_WIDTH) << offset) & mask);
        return tmp;
    }

    // General sign_extend.
    ExprRef sign_extend(ExprRef num, int sign_idx, int new_length){
        auto is_negative = SelectBit(num, sign_idx) == BvConst(1, 1);
        auto mask = (BvConst(1, new_length) << (sign_idx + 1)) - BvConst(1, new_length);
        auto trailing_ones = ~mask;

        auto tmp = num.ZExt(new_length);
        tmp = Ite(is_negative, trailing_ones | tmp, tmp);
        return tmp;
    }

    // Returns true iff num (assumed to be a 48-bit state) is beyond the scope int32 values. 
    // Otherwise returns false.
    ExprRef is_int32_saturated(ExprRef num){
        return num == MAX_INT32 | num == MIN_INT32;
    }

    // Return a + b. Result is sign extended to fit a 48-bit state.
    ExprRef accu_add(ExprRef data_precision, ExprRef a, ExprRef b){
        auto res = Ite(data_precision == INT8, a + sign_extend(b, 7, NVDLA_CACC_ACCU_INT16_BIT_WIDTH),
                    Ite(data_precision == INT16, a + sign_extend(b, 15, NVDLA_CACC_ACCU_INT16_BIT_WIDTH),
                    Ite(data_precision == FP16, accu_fp16_add(a, b), BvConst(0, NVDLA_CACC_ACCU_INT16_BIT_WIDTH))));
        return res;
    }

    // Constrain int48 num to range [MIN_INT32, MAX_INT32]. Numbers that are out of this range are
    // snapped to the closest boundary.
    ExprRef saturation_clip(ExprRef num){
        auto is_negative = SelectBit(num, 47) == BvConst(1,1); 
        auto res = Ite(!is_negative & (num >= MAX_INT32), MAX_INT32,
                    Ite(is_negative & (num <= MIN_INT32), MIN_INT32, num));
        return res;
    }

    // Add a to b and enforce output saturation constraints.
    // Note a is assumed to be 48-bit state and b is taken as data type specified by data_precision. The
    // output is constrained as a 32-bit number, although it is stored in a 48-bit state.
    ExprRef add_clip_32bit(ExprRef data_precision, ExprRef a, ExprRef b){
        // Accumulate
        auto sum = accu_add(data_precision, a, b);
        // Clip
        auto clipped_sum = saturation_clip(sum);
        return clipped_sum;
    }

    // Return |num|, where num has type int48.
    ExprRef abs_int48(ExprRef num){
        auto sign_idx = 47;
        auto is_negative = SelectBit(num, sign_idx) == BvConst(1, 1);
        auto abs_val = Ite(is_negative, (~num) + BvConst(1, NVDLA_CACC_ACCU_INT16_BIT_WIDTH), num);  
        return abs_val;
    }

    // Result is equivalent to Concat(sign(num), (|num| >> clip_truncate) + 0.5).
    // We don't have to worry about overflow since this operation only reduces the magnitude of the original nuumber.
    // Note: Code was adapted from https://github.com/nvdla/hw/blob/nvdlav1/cmod/cacc/NV_NVDLA_cacc.cpp#L853
    ExprRef truncate(ExprRef clip_truncate, ExprRef num){
        auto abs_val = abs_int48(num);
        auto is_negative = SelectBit(num, 47) == BvConst(1,1);
        auto shamt = clip_truncate + BvConst(0, 5);
        shamt = BvConst(0, NVDLA_CACC_ACCU_INT16_BIT_WIDTH) | shamt.ZExt(NVDLA_CACC_ACCU_INT16_BIT_WIDTH);
        // shamt is in48 representation of clip_truncate
        
        auto rouding_addend = Ite(clip_truncate == BvConst(0, 5), BvConst(0, NVDLA_CACC_ACCU_INT16_BIT_WIDTH), 
                            BvConst(1, NVDLA_CACC_ACCU_INT16_BIT_WIDTH) << (shamt - BvConst(1, NVDLA_CACC_ACCU_INT16_BIT_WIDTH)));
        auto res = (abs_val + rouding_addend) >> shamt;
        res = Ite(is_negative, (~res) + BvConst(1, NVDLA_CACC_ACCU_INT16_BIT_WIDTH), res);
        return res;
    }

    //////////////////////////////////////////////////////////////////////////////
    /// ILA INSTRUCTIONS
    //////////////////////////////////////////////////////////////////////////////
    
    void DefineCACCInstrs(Ila& m) {

        //////////////////////////////////////////////////////////////////////////////
        ///  GLOBAL VARIABLES
        //////////////////////////////////////////////////////////////////////////////

        auto cacc_status_reg = m.state(NVDLA_CACC_S_STATUS);
        auto cacc_group0_status = Extract(m.state(NVDLA_CACC_S_STATUS), 1, 0);
        auto cacc_group1_status = Extract(m.state(NVDLA_CACC_S_STATUS), 17, 16);
        
        auto cacc_pointer_reg = m.state(NVDLA_CACC_S_POINTER);
        auto cacc_producer = Extract(m.state(NVDLA_CACC_S_POINTER), 0, 0);
        auto cacc_consumer = Extract(m.state(NVDLA_CACC_S_POINTER), 16, 16);
        auto group0_active = cacc_consumer == BvConst(0, 1);

        auto cacc_csb_addr = Extract(m.input("csb2cacc_addr"), 15, 0);
        auto cacc_csb_valid = m.state("cacc2csb_rdy") & m.input("csb2cacc_vld");
        auto cacc_csb_write = m.input("csb2cacc_write");
        
        auto cacc_group0_unset = Extract(m.state(GetVarName("group0_", NVDLA_CACC_D_OP_ENABLE)), 0, 0) == BvConst(0, 1);
        auto cacc_group1_unset = Extract(m.state(GetVarName("group1_", NVDLA_CACC_D_OP_ENABLE)), 0, 0) == BvConst(0, 1);

        auto accumulate_flag = m.input("cmac2cacc_status") == RUN;
        auto truncate_flag = m.input("cmac2cacc_status") == LAST_BATCH;
        auto stripe_counter = m.state("stripe_counter");

        auto conv_mode = BvConst(0, 1);         // default is DC mode
        auto data_precision = BvConst(0,2);     // defualt value is INT8
        auto clip_truncate = BvConst(0, 5);
        auto num_batches = BvConst(0, 5);

        //////////////////////////////////////////////////////////////////////////////
        ///  SET REGISTERS
        //////////////////////////////////////////////////////////////////////////////

        { // Address 0x9004 (part read-only)
            auto instr = m.NewInstr("cacc_set_producer");
            instr.SetDecode(cacc_csb_addr == 0x9004 & cacc_csb_valid & cacc_csb_write);

            // Note: Consumer bit is stored in the same register but is a read-only field.
            auto old_state = m.state(NVDLA_CACC_S_POINTER);
            instr.SetUpdate(old_state, get_updated_reg_value(old_state, m.input("csb2cacc_data"), 1, 0));
        }

        {   // Group0 register writes
            
            { // Address 0x9008
                auto instr = m.NewInstr("cacc_set_op_enable_reg_group0");
                instr.SetDecode(cacc_csb_addr == 0x9008 & cacc_csb_valid & cacc_csb_write & cacc_producer == BvConst(0,1) & cacc_group0_unset);
                instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_CACC_D_OP_ENABLE)), m.input("csb2cacc_data"));
            }

            { // Address 0x900c
                auto instr = m.NewInstr("cacc_set_misc_cfg_reg_group0");
                instr.SetDecode(cacc_csb_addr == 0x900c & cacc_csb_valid & cacc_csb_write & cacc_producer == BvConst(0,1) & cacc_group0_unset);
                instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_CACC_D_MISC_CFG)), m.input("csb2cacc_data"));
            }

            { // Address 0x9010
                auto instr = m.NewInstr("cacc_set_dataout_size_0_reg_group0");
                instr.SetDecode(cacc_csb_addr == 0x9010 & cacc_csb_valid & cacc_csb_write & cacc_producer == BvConst(0,1) & cacc_group0_unset);
                instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_CACC_D_DATAOUT_SIZE_0)), m.input("csb2cacc_data"));
            }

            { // Address 0x9014
                auto instr = m.NewInstr("cacc_set_dataout_size_1_reg_group0");
                instr.SetDecode(cacc_csb_addr == 0x9014 & cacc_csb_valid & cacc_csb_write & cacc_producer == BvConst(0,1) & cacc_group0_unset);
                instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_CACC_D_DATAOUT_SIZE_1)), m.input("csb2cacc_data"));
            }

            { // Address 0x9018
                auto instr = m.NewInstr("cacc_set_dataout_addr_reg_group0");
                instr.SetDecode(cacc_csb_addr == 0x9018 & cacc_csb_valid & cacc_csb_write & cacc_producer == BvConst(0,1) & cacc_group0_unset);
                instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_CACC_D_DATAOUT_ADDR)), m.input("csb2cacc_data"));
            }

            { // Address 0x901c
                auto instr = m.NewInstr("cacc_set_batch_number_reg_group0");
                instr.SetDecode(cacc_csb_addr == 0x901c & cacc_csb_valid & cacc_csb_write & cacc_producer == BvConst(0,1) & cacc_group0_unset);
                instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_CACC_D_BATCH_NUMBER)), m.input("csb2cacc_data"));
            }

            { // Address 0x9020
                auto instr = m.NewInstr("cacc_set_line_stride_reg_group0");
                instr.SetDecode(cacc_csb_addr == 0x9020 & cacc_csb_valid & cacc_csb_write & cacc_producer == BvConst(0,1) & cacc_group0_unset);
                instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_CACC_D_LINE_STRIDE)), m.input("csb2cacc_data"));
            }

            { // Address 0x9024
                auto instr = m.NewInstr("cacc_set_surf_stride_reg_group0");
                instr.SetDecode(cacc_csb_addr == 0x9024 & cacc_csb_valid & cacc_csb_write & cacc_producer == BvConst(0,1) & cacc_group0_unset);
                instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_CACC_D_SURF_STRIDE)), m.input("csb2cacc_data"));
            }

            { // Address 0x9028
                auto instr = m.NewInstr("cacc_set_dataout_map_reg_group0");
                instr.SetDecode(cacc_csb_addr == 0x9028 & cacc_csb_valid & cacc_csb_write & cacc_producer == BvConst(0,1) & cacc_group0_unset);
                instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_CACC_D_DATAOUT_MAP)), m.input("csb2cacc_data"));
            }

            { // Address 0x902c
                auto instr = m.NewInstr("cacc_set_clip_cfg_reg_group0");
                instr.SetDecode(cacc_csb_addr == 0x902c & cacc_csb_valid & cacc_csb_write & cacc_producer == BvConst(0,1) & cacc_group0_unset);
                instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_CACC_D_CLIP_CFG)), m.input("csb2cacc_data"));
            }

            // Note: Address 0x9030 is read-only
        }

        {   // Group1 register writes

            { // Address 0x9008
                auto instr = m.NewInstr("cacc_set_op_enable_reg_group1");
                instr.SetDecode(cacc_csb_addr == 0x9008 & cacc_csb_valid & cacc_csb_write & cacc_producer == BvConst(1,1) & cacc_group1_unset);
                instr.SetUpdate(m.state(GetVarName("group1_", NVDLA_CACC_D_OP_ENABLE)), m.input("csb2cacc_data"));
            }

            { // Address 0x900c
                auto instr = m.NewInstr("cacc_set_misc_cfg_reg_group1");
                instr.SetDecode(cacc_csb_addr == 0x900c & cacc_csb_valid & cacc_csb_write & cacc_producer == BvConst(1,1) & cacc_group1_unset);
                instr.SetUpdate(m.state(GetVarName("group1_", NVDLA_CACC_D_MISC_CFG)), m.input("csb2cacc_data"));
            }

            { // Address 0x9010
                auto instr = m.NewInstr("cacc_set_dataout_size_0_reg_group1");
                instr.SetDecode(cacc_csb_addr == 0x9010 & cacc_csb_valid & cacc_csb_write & cacc_producer == BvConst(1,1) & cacc_group1_unset);
                instr.SetUpdate(m.state(GetVarName("group1_", NVDLA_CACC_D_DATAOUT_SIZE_0)), m.input("csb2cacc_data"));
            }

            { // Address 0x9014
                auto instr = m.NewInstr("cacc_set_dataout_size_1_reg_group1");
                instr.SetDecode(cacc_csb_addr == 0x9014 & cacc_csb_valid & cacc_csb_write & cacc_producer == BvConst(1,1) & cacc_group1_unset);
                instr.SetUpdate(m.state(GetVarName("group1_", NVDLA_CACC_D_DATAOUT_SIZE_1)), m.input("csb2cacc_data"));
            }

            { // Address 0x9018
                auto instr = m.NewInstr("cacc_set_dataout_addr_reg_group1");
                instr.SetDecode(cacc_csb_addr == 0x9018 & cacc_csb_valid & cacc_csb_write & cacc_producer == BvConst(1,1) & cacc_group1_unset);
                instr.SetUpdate(m.state(GetVarName("group1_", NVDLA_CACC_D_DATAOUT_ADDR)), m.input("csb2cacc_data"));
            }

            { // Address 0x901c
                auto instr = m.NewInstr("cacc_set_batch_number_reg_group1");
                instr.SetDecode(cacc_csb_addr == 0x901c & cacc_csb_valid & cacc_csb_write & cacc_producer == BvConst(1,1) & cacc_group1_unset);
                instr.SetUpdate(m.state(GetVarName("group1_", NVDLA_CACC_D_BATCH_NUMBER)), m.input("csb2cacc_data"));
            }

            { // Address 0x9020
                auto instr = m.NewInstr("cacc_set_line_stride_reg_group1");
                instr.SetDecode(cacc_csb_addr == 0x9020 & cacc_csb_valid & cacc_csb_write & cacc_producer == BvConst(1,1) & cacc_group1_unset);
                instr.SetUpdate(m.state(GetVarName("group1_", NVDLA_CACC_D_LINE_STRIDE)), m.input("csb2cacc_data"));
            }

            { // Address 0x9024
                auto instr = m.NewInstr("cacc_set_surf_stride_reg_group1");
                instr.SetDecode(cacc_csb_addr == 0x9024 & cacc_csb_valid & cacc_csb_write & cacc_producer == BvConst(1,1) & cacc_group1_unset);
                instr.SetUpdate(m.state(GetVarName("group1_", NVDLA_CACC_D_SURF_STRIDE)), m.input("csb2cacc_data"));
            }

            { // Address 0x9028
                auto instr = m.NewInstr("cacc_set_dataout_map_reg_group1");
                instr.SetDecode(cacc_csb_addr == 0x9028 & cacc_csb_valid & cacc_csb_write & cacc_producer == BvConst(1,1) & cacc_group1_unset);
                instr.SetUpdate(m.state(GetVarName("group1_", NVDLA_CACC_D_DATAOUT_MAP)), m.input("csb2cacc_data"));
            }

            { // Address 0x902c
                auto instr = m.NewInstr("cacc_set_clip_cfg_reg_group1");
                instr.SetDecode(cacc_csb_addr == 0x902c & cacc_csb_valid & cacc_csb_write & cacc_producer == BvConst(1,1) & cacc_group1_unset);
                instr.SetUpdate(m.state(GetVarName("group1_", NVDLA_CACC_D_CLIP_CFG)), m.input("csb2cacc_data"));
            }

            // Note: Address 0x9030 is read-only
        }


        //////////////////////////////////////////////////////////////////////////////
        ///  EXPLICIT STATUS CONTROL
        //////////////////////////////////////////////////////////////////////////////

        { // Start from IDLE
            auto instr = m.NewInstr("cacc_start_from_idle");
            auto group0_ok = cacc_consumer == BvConst(0,1) & !cacc_group0_unset & (cacc_group0_status == IDLE);
            auto group1_ok = cacc_consumer == BvConst(1,1) & !cacc_group1_unset & (cacc_group1_status == IDLE);
            instr.SetDecode(group0_ok ^ group1_ok);
            
            // Cache consumer states
            auto consumer_misc_cfg = Ite(group0_active, m.state(GetVarName("group0_", NVDLA_CACC_D_MISC_CFG)), 
                                                        m.state(GetVarName("group1_", NVDLA_CACC_D_MISC_CFG)));
            conv_mode = Extract(consumer_misc_cfg, 0, 0);
            data_precision = Extract(consumer_misc_cfg, 13, 12);

            auto clip_truncate_cfg = Ite(group0_active, m.state(GetVarName("group0_", NVDLA_CACC_D_CLIP_CFG)), 
                                                m.state(GetVarName("group1_", NVDLA_CACC_D_CLIP_CFG)));
            clip_truncate = Extract(clip_truncate_cfg, 4, 0);

            auto batch_num_reg = Ite(group0_active, m.state(GetVarName("group0_", NVDLA_CACC_D_BATCH_NUMBER)), 
                                                    m.state(GetVarName("group1_", NVDLA_CACC_D_BATCH_NUMBER)));
            num_batches = Extract(batch_num_reg, 4, 0);

            // Update status
            instr.SetUpdate(cacc_status_reg, Ite(group0_active, get_updated_reg_value(cacc_status_reg, BUSY, NVDLA_CACC_STATUS_REG_MASK, 0),
                                                                get_updated_reg_value(cacc_status_reg, BUSY, NVDLA_CACC_STATUS_REG_MASK, 16)));

            // Reset stripe counter
            instr.SetUpdate(stripe_counter, BvConst(0, NVDLA_CONV_STRIPE_ADDR_WIDTH));

            // Reset assembly and delivery groups (reset value = 0)
            for(auto i = 0; i < NVDLA_CMAC_MAX_NUM_KERNELS; i++){
                auto mem_ptr_assembly = MemConst(0, {}, NVDLA_CONV_STRIPE_ADDR_WIDTH, NVDLA_CACC_ACCU_INT16_BIT_WIDTH).get();
                auto mem_ptr_delivery = MemConst(0, {}, NVDLA_CONV_STRIPE_ADDR_WIDTH, NVDLA_CACC_OUTPUT_BIT_WIDTH).get();
                
                for(auto j = 0; j < NVDLA_CONV_MAX_STRIPE_LEN; j++){
                    auto addr = BvConst(j, NVDLA_CONV_STRIPE_ADDR_WIDTH);

                    auto new_mem = ExprRef(mem_ptr_assembly).Store(addr, BvConst(0, NVDLA_CACC_ACCU_INT16_BIT_WIDTH));
                    mem_ptr_assembly = new_mem.get();
                    
                    new_mem = ExprRef(mem_ptr_delivery).Store(addr, BvConst(0, NVDLA_CACC_OUTPUT_BIT_WIDTH));
                    mem_ptr_delivery = new_mem.get();
                }
                instr.SetUpdate(m.state("assembly_kernel_" + (std::to_string(i))), ExprRef(mem_ptr_assembly));
                instr.SetUpdate(m.state("cacc_output_" + (std::to_string(i))), ExprRef(mem_ptr_delivery));
            } 
        }

        { // Pend2Busy
            auto instr = m.NewInstr("pend2busy");
            auto sig_advance = m.input("cmac2cacc_status") == ACK | truncate_flag;
            instr.SetDecode((cacc_group0_status == PEND ^ cacc_group1_status == PEND) & sig_advance);
            instr.SetUpdate(cacc_status_reg, Ite(group0_active, get_updated_reg_value(cacc_status_reg, BUSY, NVDLA_CACC_STATUS_REG_MASK, 0),
                                                                get_updated_reg_value(cacc_status_reg, BUSY, NVDLA_CACC_STATUS_REG_MASK, 16)));
        }

        //////////////////////////////////////////////////////////////////////////////
        ///  COMPUTATION
        //////////////////////////////////////////////////////////////////////////////

        { // Accumulate (DC mode)
            auto instr = m.NewInstr("cacc_dc_accumulate");
            instr.SetDecode((cacc_group0_status == BUSY ^ cacc_group1_status == BUSY) & accumulate_flag & conv_mode == DIRECT);

            auto addr = stripe_counter;
            auto saturation_count = BvConst(0, NVDLA_CACC_REG_WIDTH);
            for(auto i = 0; i < NVDLA_CMAC_MAX_NUM_KERNELS; i++){
                auto assembly_group_i = m.state("assembly_kernel_" + (std::to_string(i)));
                auto mem = assembly_group_i;
                
                // Inputs are grouped by mac cell, each of which has multiple output channels 
                auto mac_idx = i % NVDLA_CMAC_NUM_MAC_CELLS;
                auto out_idx = int(i / NVDLA_CMAC_NUM_MAC_CELLS);
                auto data = m.input("cmac2cacc_ps_mac_" + (std::to_string(mac_idx)) + "_" + (std::to_string(out_idx)));
                
                auto cached_val = assembly_group_i.Load(addr);
                auto already_sat = is_int32_saturated(cached_val);

                // Perform computation iff cached value is not saturated.
                auto res = Ite(!already_sat, add_clip_32bit(data_precision, cached_val, data), cached_val);
                // res is a 32-bit number in a 48-bit state. In case of integers, res is sign extended to occupy 48 bits
                mem = mem.Store(addr, res);
                instr.SetUpdate(assembly_group_i, mem);

                // Update saturation count
                auto res_is_sat = is_int32_saturated(res);
                saturation_count = Ite(!already_sat & res_is_sat, saturation_count + BvConst(1, NVDLA_CACC_REG_WIDTH), saturation_count);                
            }  

            // State Updates
            auto group0_sat_reg = m.state(GetVarName("group0_", NVDLA_CACC_D_OUT_SATURATION));
            auto group1_sat_reg = m.state(GetVarName("group1_", NVDLA_CACC_D_OUT_SATURATION));
            instr.SetUpdate(group0_sat_reg, Ite(group0_active, group0_sat_reg + saturation_count, group0_sat_reg));
            instr.SetUpdate(group1_sat_reg, Ite(!group0_active, group1_sat_reg + saturation_count, group1_sat_reg));

            instr.SetUpdate(cacc_status_reg, Ite(group0_active, get_updated_reg_value(cacc_status_reg, PEND, NVDLA_CACC_STATUS_REG_MASK, 0), 
                                                                get_updated_reg_value(cacc_status_reg, PEND, NVDLA_CACC_STATUS_REG_MASK, 16)));

            auto wrap_around = stripe_counter == (num_batches - BvConst(1, NVDLA_CONV_STRIPE_ADDR_WIDTH));
            instr.SetUpdate(stripe_counter, Ite(!wrap_around, stripe_counter + BvConst(1, NVDLA_CONV_STRIPE_ADDR_WIDTH), 
                                                                BvConst(0, NVDLA_CONV_STRIPE_ADDR_WIDTH)));
        }


        { // Truncate (DC mode)
            auto instr = m.NewInstr("cacc_dc_truncate");
            instr.SetDecode((cacc_group0_status == BUSY ^ cacc_group1_status == BUSY) & truncate_flag & conv_mode == DIRECT);

            for (int i = 0; i < NVDLA_CMAC_MAX_NUM_KERNELS; i++){
                auto assembly_group_i = m.state("assembly_kernel_" + (std::to_string(i)));
                auto delivery_group_i = m.state("cacc_output_" + (std::to_string(i)));
                                
                auto mem_ptr = MemConst(0, {}, NVDLA_CONV_STRIPE_ADDR_WIDTH, NVDLA_CACC_OUTPUT_BIT_WIDTH).get();
                for (int j = 0; j < NVDLA_CONV_MAX_STRIPE_LEN; j++){
                    // get data 
                    auto addr = BvConst(j, NVDLA_CONV_STRIPE_ADDR_WIDTH);
                    auto data = assembly_group_i.Load(addr);

                    // Truncate and clip
                    data = truncate(clip_truncate, data); 
                    data = saturation_clip(data);
                    
                    // Cast to 32-bit state and store
                    data = Ite(data_precision == FP16, fp44_to_fp32(data), Extract(data, 31, 0));                                                           
                    auto new_mem = ExprRef(mem_ptr).Store(addr, data);
                    mem_ptr = new_mem.get();
                }

                instr.SetUpdate(delivery_group_i, ExprRef(mem_ptr));
            }

            // State updates
            auto group0_enable = m.state(GetVarName("group0_", NVDLA_CACC_D_OP_ENABLE));
            auto group1_enable = m.state(GetVarName("group1_", NVDLA_CACC_D_OP_ENABLE));
            instr.SetUpdate(group0_enable, Ite(group0_active, get_updated_reg_value(group0_enable, BvConst(0,1), 1, 0), group0_enable));
            instr.SetUpdate(group1_enable, Ite(!group0_active, get_updated_reg_value(group1_enable, BvConst(0,1), 1, 0), group1_enable));
        
            instr.SetUpdate(cacc_status_reg, Ite(group0_active, get_updated_reg_value(cacc_status_reg, IDLE, NVDLA_CACC_STATUS_REG_MASK, 0), 
                                                                get_updated_reg_value(cacc_status_reg, IDLE, NVDLA_CACC_STATUS_REG_MASK, 16)));

            instr.SetUpdate(cacc_pointer_reg, get_updated_reg_value(cacc_pointer_reg, ~cacc_consumer, 1, 16));
        }
    }

} // namespace ilang
