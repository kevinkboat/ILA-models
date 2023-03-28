// File: cacc_instrs.cc

#include <ilang/ilang++.h>
#include <cacc_config.h>
#include <math.h>

using namespace std;

namespace ilang {

    struct regGrp{
        ExprRef cacc_op_enable = BvConst(0, 1);
        ExprRef cacc_conv_mode = BvConst(0, 1);
        ExprRef cacc_data_precision = BvConst(0, 2);
        ExprRef cacc_dataout_width = BvConst(0, 13);
        ExprRef cacc_dataout_height = BvConst(0, 13);
        ExprRef cacc_dataout_channel = BvConst(0, 13);
        ExprRef cacc_dataout_addr = BvConst(0, 27);
        ExprRef cacc_batches = BvConst(0, 5);
        ExprRef cacc_line_stride = BvConst(0, 19);
        ExprRef cacc_surf_stride = BvConst(0, 19);
        ExprRef cacc_line_packed = BvConst(0, 1);
        ExprRef cacc_surf_packed = BvConst(0, 1);
        ExprRef cacc_clip_truncate = BvConst(0, 5);
        ExprRef cacc_sat_count = BvConst(0, 32);
    };

    regGrp init_regGrp(string prefix, Ila& m){
        regGrp reg;

        reg.cacc_op_enable = Extract(m.state(prefix + NVDLA_CACC_D_OP_ENABLE), 0, 0);
        reg.cacc_conv_mode = Extract(m.state(prefix + NVDLA_CACC_D_MISC_CFG), 0, 0);
        reg.cacc_data_precision = Extract(m.state(prefix + NVDLA_CACC_D_MISC_CFG), 13, 12);
        reg.cacc_dataout_width = Extract(m.state(prefix + NVDLA_CACC_D_DATAOUT_SIZE_0), 12, 0);
        reg.cacc_dataout_height = Extract(m.state(prefix + NVDLA_CACC_D_DATAOUT_SIZE_0), 28, 16);
        reg.cacc_dataout_channel = Extract(m.state(prefix + NVDLA_CACC_D_DATAOUT_SIZE_1), 12, 0);
        reg.cacc_dataout_addr = Extract(m.state(prefix + NVDLA_CACC_D_DATAOUT_ADDR), 31, 5);
        reg.cacc_batches = Extract(m.state(prefix + NVDLA_CACC_D_BATCH_NUMBER), 4, 0);
        reg.cacc_line_stride = Extract(m.state(prefix + NVDLA_CACC_D_LINE_STRIDE), 23, 5);
        reg.cacc_surf_stride = Extract(m.state(prefix + NVDLA_CACC_D_SURF_STRIDE), 23, 5);
        reg.cacc_line_packed = Extract(m.state(prefix + NVDLA_CACC_D_DATAOUT_MAP), 0, 0);
        reg.cacc_surf_packed = Extract(m.state(prefix + NVDLA_CACC_D_DATAOUT_MAP), 16, 16);
        reg.cacc_clip_truncate = Extract(m.state(prefix + NVDLA_CACC_D_CLIP_CFG), 4, 0);
        reg.cacc_sat_count = Extract(m.state(prefix + NVDLA_CACC_D_OUT_SATURATION), 31, 0);

        return reg;
    }


    // ExprRef insert(ExprRef& old_value, ExprRef& new_value, int bit_width, int min_idx){
    //     auto mask = BvConst(round(pow(2, bit_width)) - 1, old_value.bit_width);
    //     mask = mask << min_idx;
    //     auto tmp = old_value & BvConst(0, )


    // }

    //////////////////////////////////////////////////////////////////////////////
    /// ILA INSTRUCTIONS
    //////////////////////////////////////////////////////////////////////////////
    

    void DefineCACCInstrs(Ila& m) {

        //////////////////////////////////////////////////////////////////////////////
        ///  VARIABLES
        //////////////////////////////////////////////////////////////////////////////

        // For single reg group
        auto cacc_group0_status = Extract(m.state(NVDLA_CACC_S_STATUS), 1, 0);
        auto cacc_group1_status = Extract(m.state(NVDLA_CACC_S_STATUS), 17, 16);
        auto cacc_producer = Extract(m.state(NVDLA_CACC_S_POINTER), 0, 0);
        auto cacc_consumer = Extract(m.state(NVDLA_CACC_S_POINTER), 16, 16);

        // // For duplicated reg group 
        regGrp group0 = init_regGrp("group0_", m);
        regGrp group1 = init_regGrp("group1_", m);
        regGrp consumer_reg = group0;                   // default value

        auto cacc_csb_addr = Extract(m.input("csb2cacc_addr"), 15, 0);
        auto cacc_csb_valid = m.state("cacc2csb_rdy") & m.input("csb2cacc_vld");
        auto cacc_csb_write = m.input("csb2cacc_write");
        
        auto cacc_group0_unset = Extract(m.state(GetVarName("group0_", NVDLA_CACC_D_OP_ENABLE)), 0, 0) == BvConst(0, 1);
        auto cacc_group1_unset = Extract(m.state(GetVarName("group1_", NVDLA_CACC_D_OP_ENABLE)), 0, 0) == BvConst(0, 1);

        //////////////////////////////////////////////////////////////////////////////
        ///  SET REGISTERS
        //////////////////////////////////////////////////////////////////////////////

        { // Address 0x9004 (part read-only)
            auto instr = m.NewInstr("cacc_set_producer");
            instr.SetDecode(cacc_csb_addr == 0x9004 & cacc_csb_valid & cacc_csb_write);

            // Note: Status bits are stored in the same memory address but are read-only.
            auto old_state = m.state(NVDLA_CACC_S_POINTER);

            // Producer bit is stored in index 0
            auto mask = BvConst(0xFFFE, NVDLA_CACC_REG_WIDTH);
            auto tmp = (old_state & mask) | (m.input("csb2cacc_data") & (~mask));
            instr.SetUpdate(m.state(NVDLA_CACC_S_POINTER), tmp);
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

        // { // Start from IDLE
        //     auto instr = m.NewInstr("cacc_start_from_idle");
        //     auto group0_ok = cacc_consumer == BvConst(0,1) & !cacc_group0_unset & (cacc_group0_status == IDLE);
        //     auto group1_ok = cacc_consumer == BvConst(1,1) & !cacc_group1_unset & (cacc_group1_status == IDLE);
        //     instr.SetDecode((group0_ok ^ group1_ok) & csc2cacc_vld);
            
        //     data_precision = Ite(cacc_consumer == BvConst(0,1), Extract(m.state(GetVarName("group0_", NVDLA_CACC_D_MISC_CFG)), 13, 12),
        //                             Extract(m.state(GetVarName("group1_", NVDLA_CACC_D_MISC_CFG)), 13, 12));

        //     conv_mode = Ite(cacc_consumer == BvConst(0,1), Extract(m.state(GetVarName("group0_", NVDLA_CACC_D_MISC_CFG)), 0, 0),
        //                         Extract(m.state(GetVarName("group1_", NVDLA_CACC_D_MISC_CFG)), 0, 0));

        //     // Update status
        //     instr.SetUpdate(cacc_group0_status, Ite(group0_ok, BUSY, cacc_group0_status));
        //     instr.SetUpdate(cacc_group1_status, Ite(group1_ok, BUSY, cacc_group1_status)); 

        //     // Cold start
        //     using_stale_data = BoolConst(true);
        // }

        // { // Pend2Busy
        //     auto instr = m.NewInstr("pend2busy");
        //     auto group0_pend = cacc_group0_status == PEND & cacc_consumer == BvConst(0,1);
        //     auto group1_pend = cacc_group1_status == PEND & cacc_consumer == BvConst(1,1);

        //     instr.SetDecode((group0_pend | group1_pend) & csc2cacc_vld);
        //     instr.SetUpdate(cacc_group0_status, Ite(group0_pend, BUSY, cacc_group0_status));
        //     instr.SetUpdate(cacc_group1_status, Ite(group1_pend, BUSY, cacc_group1_status)); 
        //     using_stale_data = (conv_mode == WINOGRAD) | !(m.input("csc2cacc_reuse_weights"));
        // }

        //////////////////////////////////////////////////////////////////////////////
        ///  COMPUTATION
        //////////////////////////////////////////////////////////////////////////////

        
    }

} // namespace ilang
