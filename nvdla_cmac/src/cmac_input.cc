// File: cmac_input.cc

#include <ilang/ilang++.h>
#include <cmac_config.h>

namespace ilang {

    void DefineCMACInput(Ila& m){

        //////////////////////////////////////////////////////////////////////////////
        ///  FROM CSB
        //////////////////////////////////////////////////////////////////////////////

        m.NewBvInput("csb2cmac_addr", 16);
        m.NewBvInput("csb2cmac_data", 32);
        m.NewBvInput("csb2cmac_write", 1);
        m.NewBvInput("csb2cmac_vld", 1);

        //////////////////////////////////////////////////////////////////////////////
        ///  FROM CSC
        //////////////////////////////////////////////////////////////////////////////

        for (auto i = 0; i < 16; i++) {
            m.NewBvInput("csc2cmac_weight_kernel_" + (std::to_string(i)), NVDLA_CMAC_INT16_KERNEL_WIDTH);
        }

        m.NewBvInput("csc2cmac_feature_kernel", NVDLA_CMAC_INT16_KERNEL_WIDTH);
        m.NewBvInput("csc2cmac_status", NVDLA_CMAC_PIPELINE_STATUS_WIDTH);
        m.NewBoolInput("csc2cmac_reuse_weights");
        m.NewBoolInput("csc2cmac_vld");
        m.NewBoolInput("csc2cmac_sending_last_batch");
    }

} // namespace ilang 