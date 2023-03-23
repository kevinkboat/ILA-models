// File: cacc_instrs.cc

#include <ilang/ilang++.h>
#include <cacc_config.h>

using namespace std;

#define NVDLA_CACC_D_OP_ENABLE_WIDTH 1
#define NVDLA_CACC_D_MISC_CFG 
namespace ilang {

    struct regGrp{
        ExprRef cacc_op_enable;
        ExprRef cacc_conv_mode;
        ExprRef cacc_data_precision;
        ExprRef cacc_dataout_width;
        ExprRef cacc_dataout_height;
        ExprRef cacc_dataout_channel;
        ExprRef cacc_dataout_addr;
        ExprRef cacc_batches;
        ExprRef cacc_line_stride;
        ExprRef cacc_surf_stride;
        ExprRef cacc_line_packed;
        ExprRef cacc_surf_packed;
        ExprRef cacc_clip_truncate;
        ExprRef cacc_sat_count;
    };

    regGrp init_regGrp(string prefix){
        // reg.cacc_op_enable = NewBvState(0, 1);
        // reg.cacc_conv_mode = NewBvState(0, 1);
        // reg.cacc_data_precision = NewBvState(0, 2);
        // reg.cacc_dataout_width = NewBvState(0, 13);
        // reg.cacc_dataout_height = NewBvState(0, 13);
        // reg.cacc_dataout_channel = NewBvState(0, 13);
        // reg.cacc_dataout_addr = NewBvState(0, 27);
        // reg.cacc_batches = NewBvState(0, 5);
        // reg.cacc_line_stride = NewBvState(0, 19);
        // reg.cacc_surf_stride = NewBvState(0, 19);
        // reg.cacc_line_packed = NewBvState(0, 1);
        // reg.cacc_surf_packed = NewBvState(0, 1);
        // reg.cacc_clip_truncate = NewBvState(0, 5);
        // reg.cacc_sat_count = NewBvState(0, 32);

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

        // For duplicated reg group 
        regGrp group0 = init_regGrp("group0_");
        regGrp group1 = init_regGrp("group1_");

        // auto cacc_d_op_enable = Extract(m.state(NVDLA_CACC_D_OP_ENABLE), 0, 0);
        // auto cacc_d_conv_mode = Extract(m.state(NVDLA_CACC_D_MISC_CFG), 0, 0);
        // auto cacc_d_data_precision = Extract(m.state(NVDLA_CACC_D_MISC_CFG), 13, 12);
        // auto cacc_d_dataout_width = Extract(m.state(NVDLA_CACC_D_DATAOUT_SIZE_0), 12, 0);
        // auto cacc_d_dataout_height = Extract(m.state(NVDLA_CACC_D_DATAOUT_SIZE_0), 28, 16);
        // auto cacc_d_dataout_channel = Extract(m.state(NVDLA_CACC_D_DATAOUT_SIZE_1), 12, 0);
        // auto cacc_d_dataout_addr = Extract(m.state(NVDLA_CACC_D_DATAOUT_ADDR), 31, 5);
        // auto cacc_d_batches = Extract(m.state(NVDLA_CACC_D_BATCH_NUMBER), 4, 0);
        // auto cacc_d_line_stride = Extract(m.state(NVDLA_CACC_D_LINE_STRIDE), 23, 5);
        // auto cacc_d_surf_stride = Extract(m.state(NVDLA_CACC_D_SURF_STRIDE), 23, 5);
        // auto cacc_d_line_packed = Extract(m.state(NVDLA_CACC_D_DATAOUT_MAP), 0, 0);
        // auto cacc_d_surf_packed = Extract(m.state(NVDLA_CACC_D_DATAOUT_MAP), 16, 16);
        // auto cacc_d_clip_truncate = Extract(m.state(NVDLA_CACC_D_CLIP_CFG), 4, 0);
        // auto cacc_d_sat_count = Extract(m.state(NVDLA_CACC_D_OUT_SATURATION), 31, 0);

        auto cacc_csb_addr = Extract(m.input("csb2cacc_addr"), 11, 0);
        auto cacc_csb_valid = m.state("cacc2csb_rdy") & m.input("csb2cacc_vld");
        auto cacc_csb_write = m.input("csb2cacc_write");
        
        auto cacc_group0_unset = group0.cacc_op_enable == BvConst(0, 1);
        auto cacc_group1_unset = group1.cacc_op_enable == BvConst(0, 1);

        // auto cacc_group0_unset = m.state(GetVarName("group0_", NVDLA_CACC_D_OP_ENABLE)) == BvConst(0, NVDLA_CACC_REG_WIDTH);
        // auto cacc_group1_unset = m.state(GetVarName("group1_", NVDLA_CACC_D_OP_ENABLE)) == BvConst(0, NVDLA_CACC_REG_WIDTH);

        //////////////////////////////////////////////////////////////////////////////
        ///  SET REGISTERS
        //////////////////////////////////////////////////////////////////////////////

        { // CACC Set Producer (addr:004)
            auto instr = m.NewInstr("cacc_set_producer");
            instr.SetDecode(cacc_csb_addr == 0x004 & cacc_csb_valid & cacc_csb_write);
            instr.SetUpdate(cacc_producer, Extract(m.input("csb2cacc_data"), 0, 0));
        }

        { // CACC Set Start Group 0 (addr:008)
            auto instr = m.NewInstr("cacc_set_start_group0");
            instr.SetDecode(cacc_csb_addr == 0x008 & cacc_csb_valid & cacc_csb_write & cacc_producer == BvConst(0,1) & cacc_group0_unset);
            instr.SetUpdate(group0.cacc_op_enable, Extract(m.input("csb2cacc_data"), 0, 0));
        }      

        { // CACC Set Start Group 1 (addr:008)
            auto instr = m.NewInstr("cacc_set_start_group1");
            instr.SetDecode(cacc_csb_addr == 0x008 & cacc_csb_valid & cacc_csb_write & cacc_producer == BvConst(1,1) & cacc_group1_unset);
            instr.SetUpdate(group1.cacc_op_enable, Extract(m.input("csb2cacc_data"), 0, 0));
        } 

        // { // CACC Set Start Group 1 (addr:008)
        //     auto instr = m.NewInstr("cacc_set_start_group1");
        //     instr.SetDecode(cacc_csb_addr == 0x008 & cacc_csb_valid & cacc_csb_write & cacc_producer == BvConst(1,1) & cacc_group1_unset);
        //     instr.SetUpdate(m.state(GetVarName("group1_", NVDLA_CACC_D_OP_ENABLE)), Extract(m.input("csb2cacc_data"), NVDLA_CACC_D_OP_ENABLE_WIDTH - 1, 0));
        // } 

        // { // CACC Set Config Group 0 (addr:00c)
        //     auto instr = m.NewInstr("cacc_set_config_group0");
        //     instr.SetDecode(cacc_csb_addr == 0x00c & cacc_csb_valid & cacc_csb_write & cacc_producer == BvConst(0,1) & cacc_group0_unset);
        //     instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_CACC_D_MISC_CFG)), Extract(m.input("csb2cacc_data"), NVDLA_CACC_D_MISC_CFG_WIDTH - 1, 0));
        // }

        // { // CACC Set Config Group 1 (addr:00c)
        //     auto instr = m.NewInstr("cacc_set_config_group1");
        //     instr.SetDecode(cacc_csb_addr == 0x00c & cacc_csb_valid & cacc_csb_write & cacc_producer == BvConst(1,1) & cacc_group1_unset);
        //     instr.SetUpdate(m.state(GetVarName("group1_", NVDLA_CACC_D_MISC_CFG)), Extract(m.input("csb2cacc_data"), NVDLA_CACC_D_MISC_CFG_WIDTH - 1, 0));
        // }

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
