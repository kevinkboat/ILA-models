// File: cmac_init.cc

#include <ilang/ilang++.h>
#include <cmac_config.h>

namespace ilang {

    void DefineCMACInit(Ila& m){

        //////////////////////////////////////////////////////////////////////////////
        ///  OUTPUTS
        //////////////////////////////////////////////////////////////////////////////

        m.AddInit(m.state("cmac2csb_rdy") == BoolConst(true));
        m.AddInit(m.state("cmac2csb_data_vld") == BoolConst(false));
        m.AddInit(m.state("cmac2cacc_status") == BvConst(0,NVDLA_CMAC_PIPELINE_STATUS_WIDTH));

        //////////////////////////////////////////////////////////////////////////////
        ///  INTERNAL STATES
        //////////////////////////////////////////////////////////////////////////////
        
        // m.AddInit(m.state("cmac_state") == IDLE);
        m.AddInit(m.state(NVDLA_CMAC_S_STATUS_0) == IDLE);
        m.AddInit(m.state(NVDLA_CMAC_S_STATUS_1) ==IDLE);
        
        m.AddInit(m.state(NVDLA_CMAC_S_PRODUCER) == BvConst(0, NVDLA_CMAC_S_PRODUCER_WIDTH));
        m.AddInit(m.state(NVDLA_CMAC_S_CONSUMER) == BvConst(0, NVDLA_CMAC_S_CONSUMER_WIDTH));
        
        for (auto i = 0; i < 2; i++) {
            m.AddInit(m.state("group" + (std::to_string(i)) + "_" + NVDLA_CMAC_D_OP_ENABLE) == BvConst(0, NVDLA_CMAC_D_OP_ENABLE_WIDTH));
            m.AddInit(m.state("group" + (std::to_string(i)) + "_" + NVDLA_CMAC_D_MISC_CFG) == BvConst(0, NVDLA_CMAC_D_MISC_CFG_WIDTH));
        }
    }

} // namespace ilang 