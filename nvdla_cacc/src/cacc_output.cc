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

        // // MAC array outputs
        // for(auto i = 0; i < NVDLA_CMAC_NUM_MAC_CELLS; i++){
        //     m.NewMemState("cacc2cacc_partial_sum_mac_" + (std::to_string(i)), NVDLA_CMAC_MAC_CELL_OUTPUT_ADDR_WIDTH, NVDLA_CMAC_KERNEL_MAX_ELEM_WIDTH);
        // }
        
        // m.NewBvState("cacc2cacc_status", NVDLA_CMAC_PIPELINE_STATUS_WIDTH);
    }

} // namespace ilang 