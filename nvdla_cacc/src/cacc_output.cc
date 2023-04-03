// File: cacc_output.cc

#include <ilang/ilang++.h>
#include <cacc_config.h>
#include <iostream>

namespace ilang {

     void DefineCACCOutput(Ila& m) {
        
        //////////////////////////////////////////////////////////////////////////////
        ///  TO CSB
        //////////////////////////////////////////////////////////////////////////////

        m.NewBoolState("cacc2csb_rdy");
        m.NewBoolState("cacc2csb_data_vld");

        //////////////////////////////////////////////////////////////////////////////
        ///  TO SDP 
        //////////////////////////////////////////////////////////////////////////////

        // // Dennis wrote
        // for (int i = 0; i < 16; i++) {
        //     // Primary inputs
        //     m.NewBvInput(GetVarName("cacc_data_", (std::to_string(i))), 32);
        //     //...
        // }

        // doubles as delivery group
        for (int i = 0; i < NVDLA_CMAC_MAX_NUM_KERNELS; i++){
            m.NewMemState("cacc_output_" + (std::to_string(i)), NVDLA_CONV_STRIPE_ADDR_WIDTH, NVDLA_CACC_OUTPUT_BIT_WIDTH);
        }
        
    }

} // namespace ilang 