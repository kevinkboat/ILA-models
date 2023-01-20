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
        
        // 16 Weight Kernels
        for (auto i = 0; i < NVDLA_CMAC_NUM_MAC_CELLS; i++) {
            for (auto j = 0; j < NVDLA_CMAC_KERNEL_NUM_ELEM; j++){
                m.NewBvInput("csc2cmac_wt_" + (std::to_string(i)) + "_" + (std::to_string(j)), NVDLA_CMAC_KERNEL_MAX_ELEM_WIDTH);
            }
        } 

        // 1 Feature Kernel
        for (auto i = 0; i < NVDLA_CMAC_KERNEL_NUM_ELEM; i++){
            m.NewBvInput("csc2cmac_ft_" + (std::to_string(i)), NVDLA_CMAC_KERNEL_MAX_ELEM_WIDTH);
        }
        
        m.NewBvInput("csc2cmac_status", NVDLA_CMAC_PIPELINE_STATUS_WIDTH);
        m.NewBoolInput("csc2cmac_reuse_weights");
        m.NewBoolInput("csc2cmac_vld");
        m.NewBoolInput("csc2cmac_sending_last_batch");
    }

} // namespace ilang 