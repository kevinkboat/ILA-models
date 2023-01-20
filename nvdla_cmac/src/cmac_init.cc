// File: cmac_init.cc

#include <ilang/ilang++.h>
#include <cmac_config.h>

namespace ilang {

    void DefineCMACInit(Ila& m){

        //////////////////////////////////////////////////////////////////////////////
        ///  OUTPUTS
        //////////////////////////////////////////////////////////////////////////////

        m.AddInit(m.state("cmac2csb_rdy") == BvConst(1,1));
        m.AddInit(m.state("cmac2csb_data_vld") == BvConst(1,1));
        m.AddInit(m.state("cmac2cacc_status") == BvConst(0,NVDLA_CMAC_PIPELINE_STATUS_WIDTH));
        // m.AddInit(m.state("cmac2cacc_partial_sums") == MemConst(0, {}, NVDLA_CMAC_MAC_CELLS_ADDR_WIDTH, NVDLA_CMAC_KERNEL_MAX_ELEM_WIDTH));

        //////////////////////////////////////////////////////////////////////////////
        ///  INTERNAL STATES
        //////////////////////////////////////////////////////////////////////////////
        
        m.AddInit(m.state("cmac_state") == IDLE);
        
        m.AddInit(m.state(NVDLA_CMAC_S_PRODUCER) == BvConst(0, NVDLA_CMAC_S_PRODUCER_WIDTH));
        m.AddInit(m.state(NVDLA_CMAC_S_CONSUMER) == BvConst(0, NVDLA_CMAC_S_CONSUMER_WIDTH));
        
        m.AddInit(m.state(NVDLA_CMAC_S_STATUS_0) == BvConst(0, NVDLA_CMAC_S_STATUS_WIDTH));
        m.AddInit(m.state(NVDLA_CMAC_S_STATUS_1) == BvConst(0, NVDLA_CMAC_S_STATUS_WIDTH));

        m.AddInit(m.state(GetVarName("group0_", NVDLA_CMAC_D_OP_ENABLE)) == BvConst(0, NVDLA_CMAC_D_OP_ENABLE_WIDTH));
        m.AddInit(m.state(GetVarName("group0_", NVDLA_CMAC_D_MISC_CFG)) == BvConst(0, NVDLA_CMAC_D_MISC_CFG_WIDTH));

        // for (auto i = 0; i < NVDLA_CMAC_NUM_MAC_CELLS; i++) {
        //     m.AddInit(m.state("cached_wt_kernel_" + (std::to_string(i))) == MemConst(0, {}, NVDLA_CMAC_KERNEL_ADDR_WIDTH, NVDLA_CMAC_KERNEL_MAX_ELEM_WIDTH));
        // } 
    }

} // namespace ilang 