// File: cacc_instrs.cc

#include <ilang/ilang++.h>
#include <cacc_config.h>
#include <math.h>

using namespace std;

namespace ilang {

    ExprRef abs_int48(ExprRef num){
        auto sign_idx = 47;
        auto sign_bit = SelectBit(num, sign_idx);
        auto mask = (BvConst(1, NVDLA_CACC_ACCU_INT16_BIT_WIDTH) << sign_idx) - BvConst(1, NVDLA_CACC_ACCU_INT16_BIT_WIDTH);
        auto absVal_data = Ite(sign_bit == BvConst(1, 1), (~num) + BvConst(1, NVDLA_CACC_ACCU_INT16_BIT_WIDTH), num);
        return absVal_data & mask;
    }

    // Return 16-bit representation of int8
    ExprRef fp44_to_fp32(ExprRef num){
        // Placeholder
        return BvConst(0, NVDLA_CACC_ACCU_INT16_BIT_WIDTH);
    }

    // Return 16-bit representation of int8
    ExprRef int8_to_int16(ExprRef num){
        auto bv7_unsigned = num & BvConst(0x7F, NVDLA_INT16_BIT_WIDTH);
        auto bv = Ite(SelectBit(num, 7) == 0, bv7_unsigned, bv7_unsigned | BvConst(0xFF80, NVDLA_INT16_BIT_WIDTH));
        return bv;
    }

    // Return the next state of the register
    ExprRef get_updated_reg_value(ExprRef old_reg, ExprRef new_value, int mask_val, int offset){
        auto mask = BvConst((mask_val << offset), NVDLA_CACC_REG_WIDTH);
        auto tmp = (old_reg & (~mask)) | ((new_value.ZExt(NVDLA_CACC_REG_WIDTH) << offset) & mask);
        return tmp;
    }

    // Sum of fp44 (a) and fp16 numbers (b). Note these numbers are stored as 48 bit states
    ExprRef accu_fp16_add(ExprRef a, ExprRef b){
        // Placeholder code
        return BvConst(0, NVDLA_CACC_ACCU_INT16_BIT_WIDTH);
    }

    // a is assumed to be 48 bits and b can be int16/int8/fp16
    ExprRef accu_add(ExprRef data_precision, ExprRef a, ExprRef b){
        auto res = Ite(data_precision == INT16, a + b.SExt(NVDLA_CACC_ACCU_INT16_BIT_WIDTH),
                    Ite(data_precision == INT8, a + (int8_to_int16(b)).SExt(NVDLA_CACC_ACCU_INT16_BIT_WIDTH),
                    Ite(data_precision == FP16, accu_fp16_add(a, b), BvConst(0, NVDLA_CACC_ACCU_INT16_BIT_WIDTH))));
        return res;
    }

    // Check overflow
    ExprRef saturation_clip(ExprRef sum){
        // extract sign bit
        auto is_negative = SelectBit(sum, 47) == BvConst(1, 1);
        auto absVal_data = abs_int48(sum);

        auto res = Ite(!is_negative & (absVal_data > MAX_INT32), MAX_INT32,
                    Ite(is_negative & (absVal_data > MIN_ABS_INT32), MIN_ABS_INT32, sum));
        return res;
    }

    // Truncate op. Adapted from https://github.com/nvdla/hw/blob/nvdlav1/cmod/cacc/NV_NVDLA_cacc.cpp#L853
    ExprRef truncate(ExprRef trunc_factor, ExprRef sum){
        // extract data 
        auto absVal_data = abs_int48(sum);
        auto is_negative = SelectBit(sum, 47) == BvConst(1,1);
       
        auto K = trunc_factor + BvConst(0, 5);
        auto clip_truncate = BvConst(0, NVDLA_CACC_ACCU_INT16_BIT_WIDTH) | K.ZExt(NVDLA_CACC_ACCU_INT16_BIT_WIDTH);
        
        auto rouding_addend = Ite(clip_truncate == BvConst(0, NVDLA_CACC_ACCU_INT16_BIT_WIDTH), BvConst(0, NVDLA_CACC_ACCU_INT16_BIT_WIDTH), 
                            BvConst(1, NVDLA_CACC_ACCU_INT16_BIT_WIDTH) << (clip_truncate - BvConst(1, NVDLA_CACC_ACCU_INT16_BIT_WIDTH)));

        auto tmp = absVal_data + rouding_addend;
        tmp = tmp >> clip_truncate;
        tmp = Ite(is_negative, (~tmp) + BvConst(1, NVDLA_CACC_ACCU_INT16_BIT_WIDTH), tmp);
        return tmp;
    }

    //////////////////////////////////////////////////////////////////////////////
    /// ILA INSTRUCTIONS
    //////////////////////////////////////////////////////////////////////////////
    
    void DefineCACCInstrs(Ila& m) {

        //////////////////////////////////////////////////////////////////////////////
        ///  VARIABLES
        //////////////////////////////////////////////////////////////////////////////

        // For single reg group
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

        auto accumulate_flag = Extract(m.input("cmac2cacc_status"), 0, 0) == BvConst(1,1);
        auto truncate_flag = m.input("cmac2cacc_status") == LAST_BATCH;
        auto stripe_counter = m.state("stripe_counter");

        //////////////////////////////////////////////////////////////////////////////
        ///  SET REGISTERS
        //////////////////////////////////////////////////////////////////////////////

        { // Address 0x9004 (part read-only)
            auto instr = m.NewInstr("cacc_set_producer");
            instr.SetDecode(cacc_csb_addr == 0x9004 & cacc_csb_valid & cacc_csb_write);

            // Note: Status bits are stored in the same memory address but are read-only.
            auto old_state = m.state(NVDLA_CACC_S_POINTER);

            // Producer bit is stored in index 0
            // auto mask = BvConst(1, NVDLA_CACC_REG_WIDTH);
            // auto tmp = (old_state & (~mask)) | (m.input("csb2cacc_data") & mask);
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
            
            // Update status
            instr.SetUpdate(cacc_status_reg, Ite(group0_active, get_updated_reg_value(cacc_status_reg, BUSY, 3, 0),
                                                                get_updated_reg_value(cacc_status_reg, BUSY, 3, 16)));

            instr.SetUpdate(stripe_counter, BvConst(0, NVDLA_CONV_STRIPE_ADDR_WIDTH));

            // reset assembly group
            for(auto i = 0; i < NVDLA_CMAC_MAX_NUM_KERNELS; i++){
                auto mem_ptr = MemConst(0, {}, NVDLA_CONV_STRIPE_ADDR_WIDTH, NVDLA_CACC_ACCU_INT16_BIT_WIDTH).get();
                for(auto j = 0; j < NVDLA_CONV_MAX_STRIPE_LEN; j++){
                    auto data = BvConst(0, NVDLA_CACC_ACCU_INT16_BIT_WIDTH);
                    auto new_mem = ExprRef(mem_ptr).Store(BvConst(j, NVDLA_CONV_STRIPE_ADDR_WIDTH), data);
                    mem_ptr = new_mem.get();
                }
                instr.SetUpdate(m.state("assembly_kernel_" + (std::to_string(i))), ExprRef(mem_ptr));
            } 
            
        }

        { // Pend2Busy
            auto instr = m.NewInstr("pend2busy");

            instr.SetDecode((cacc_group0_status == PEND ^ cacc_group1_status == PEND) & m.input("cmac2cacc_status") == ACK);
            instr.SetUpdate(cacc_status_reg, Ite(group0_active, get_updated_reg_value(cacc_status_reg, BUSY, 3, 0),
                                                                get_updated_reg_value(cacc_status_reg, BUSY, 3, 16)));
        }

        //////////////////////////////////////////////////////////////////////////////
        ///  COMPUTATION
        //////////////////////////////////////////////////////////////////////////////

        { // Accumulate
            auto instr = m.NewInstr("cacc_dc_accumulate");

            instr.SetDecode((cacc_group0_status == BUSY ^ cacc_group1_status == BUSY) & accumulate_flag);

            auto addr = stripe_counter;
            auto saturation_count = BvConst(0, NVDLA_CACC_REG_WIDTH);
            for(auto i = 0; i < NVDLA_CMAC_MAX_NUM_KERNELS; i++){
                auto assembly_group_i = m.state("assembly_kernel_" + (std::to_string(i)));
                auto mem = assembly_group_i;
                
                auto mac_id = i % NVDLA_CMAC_NUM_MAC_CELLS;
                auto idx = int(i / NVDLA_CMAC_NUM_MAC_CELLS);
                auto data = m.input("cmac2cacc_ps_mac_" + (std::to_string(mac_id)) + "_" + (std::to_string(idx)));

                auto data_precision = Ite(group0_active, m.state(GetVarName("group0_", NVDLA_CACC_D_MISC_CFG)), 
                                                        m.state(GetVarName("group1_", NVDLA_CACC_D_MISC_CFG)));
                data_precision = Extract(data_precision, 13, 12);
                
                // calculate sum
                auto sum = accu_add(data_precision, assembly_group_i.Load(addr), data);
                // mem = mem.Store(addr, sum);

                
                // truncate sum
                auto clip_truncate_reg = Ite(group0_active, m.state(GetVarName("group0_", NVDLA_CACC_D_CLIP_CFG)), 
                                                        m.state(GetVarName("group1_", NVDLA_CACC_D_CLIP_CFG)));
                auto clip_truncate = Extract(clip_truncate_reg, 4, 0);
                auto truncated_sum = truncate(clip_truncate, sum);
                mem = mem.Store(addr, truncated_sum);

                // // // clip sum
                // auto clipped_sum = saturation_clip(truncated_sum);
                // saturation_count = Ite(clipped_sum != truncated_sum, saturation_count + BvConst(1, NVDLA_CACC_REG_WIDTH), saturation_count);
                // // mem = mem.Store(addr, clipped_sum);

                instr.SetUpdate(assembly_group_i, mem);
            }  

            // State Updates
            auto group0_sat_reg = m.state(GetVarName("group0_", NVDLA_CACC_D_OUT_SATURATION));
            auto group1_sat_reg = m.state(GetVarName("group1_", NVDLA_CACC_D_OUT_SATURATION));
            instr.SetUpdate(group0_sat_reg, Ite(group0_active, saturation_count, group0_sat_reg));
            instr.SetUpdate(group1_sat_reg, Ite(!group0_active, saturation_count, group1_sat_reg));

            instr.SetUpdate(cacc_status_reg, Ite(group0_active, get_updated_reg_value(cacc_status_reg, PEND, 3, 0), 
                                                                get_updated_reg_value(cacc_status_reg, PEND, 3, 16)));

            auto num_batches = Ite(group0_active, m.state(GetVarName("group0_", NVDLA_CACC_D_BATCH_NUMBER)), 
                                                    m.state(GetVarName("group1_", NVDLA_CACC_D_BATCH_NUMBER)));
            num_batches = Extract(num_batches, 4, 0);

            auto wrap_around = stripe_counter == (num_batches - BvConst(1, NVDLA_CONV_STRIPE_ADDR_WIDTH));
            instr.SetUpdate(stripe_counter, Ite(!wrap_around, stripe_counter + BvConst(1, NVDLA_CONV_STRIPE_ADDR_WIDTH), 
                                                                BvConst(0, NVDLA_CONV_STRIPE_ADDR_WIDTH)));
        }


        { // Truncate
            auto instr = m.NewInstr("cacc_dc_truncate");
            instr.SetDecode((cacc_group0_status == PEND ^ cacc_group1_status == PEND) & truncate_flag);

            for (int i = 0; i < NVDLA_CMAC_MAX_NUM_KERNELS; i++){
                auto assembly_group_i = m.state("assembly_kernel_" + (std::to_string(i)));
                auto delivery_group_i = m.state("cacc_output_" + (std::to_string(i)));
                                
                auto mem_ptr = MemConst(0, {}, NVDLA_CONV_STRIPE_ADDR_WIDTH, NVDLA_CACC_OUTPUT_BIT_WIDTH).get();
                for (int j = 0; j < NVDLA_CONV_MAX_STRIPE_LEN; j++){
                    auto data = assembly_group_i.Load(BvConst(j, NVDLA_CONV_STRIPE_ADDR_WIDTH));

                    auto data_precision = Ite(group0_active, m.state(GetVarName("group0_", NVDLA_CACC_D_MISC_CFG)), 
                                                        m.state(GetVarName("group1_", NVDLA_CACC_D_MISC_CFG)));
                    data_precision = Extract(data_precision, 13, 12);

                    auto lower_31 = data & MAX_INT32;
                    data = Ite(data_precision == FP16, fp44_to_fp32(data),
                            Ite(SelectBit(data, 31) == BvConst(1, 1), (lower_31 | MIN_ABS_INT32), lower_31));
                    data = Extract(data, 31, 0);
                    
                    auto new_mem = ExprRef(mem_ptr).Store(BvConst(j, NVDLA_CONV_STRIPE_ADDR_WIDTH), data);
                    mem_ptr = new_mem.get();
                }

                instr.SetUpdate(delivery_group_i, ExprRef(mem_ptr));
            }

            // State updates
            auto group0_enable = m.state(GetVarName("group0_", NVDLA_CACC_D_OP_ENABLE));
            auto group1_enable = m.state(GetVarName("group1_", NVDLA_CACC_D_OP_ENABLE));
            instr.SetUpdate(group0_enable, Ite(group0_active, get_updated_reg_value(group0_enable, BvConst(0,1), 1, 0), group0_enable));
            instr.SetUpdate(group1_enable, Ite(!group0_active, get_updated_reg_value(group1_enable, BvConst(0,1), 1, 0), group1_enable));
        
            instr.SetUpdate(cacc_status_reg, Ite(group0_active, get_updated_reg_value(cacc_status_reg, IDLE, 3, 0), 
                                                                get_updated_reg_value(cacc_status_reg, IDLE, 3, 16)));

            instr.SetUpdate(cacc_pointer_reg, get_updated_reg_value(cacc_pointer_reg, ~cacc_consumer, 1, 16));
        
        }
    }

} // namespace ilang
