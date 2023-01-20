// File: cmac_output.cc

#include <ilang/ilang++.h>
#include <cmac_config.h>
#include <iostream>

namespace ilang {

     void DefineCMACOutput(Ila& m) {
        
        //////////////////////////////////////////////////////////////////////////////
        ///  TO CSB
        //////////////////////////////////////////////////////////////////////////////

        m.NewBvState("cmac2csb_rdy", 1);
        m.NewBvState("cmac2csb_data_vld", 1);

        //////////////////////////////////////////////////////////////////////////////
        ///  TO CACC 
        //////////////////////////////////////////////////////////////////////////////

        // 16 Partial Sums
        m.NewMemState("cmac2cacc_partial_sums", NVDLA_CMAC_MAC_CELLS_ADDR_WIDTH, NVDLA_CMAC_KERNEL_MAX_ELEM_WIDTH);
        
        m.NewBvState("cmac2cacc_status", NVDLA_CMAC_PIPELINE_STATUS_WIDTH);
    }

} // namespace ilang 