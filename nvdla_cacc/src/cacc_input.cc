// File: cacc_input.cc

#include <ilang/ilang++.h>
#include <cacc_config.h>

namespace ilang {

    void DefineCACCInput(Ila& m){

        //////////////////////////////////////////////////////////////////////////////
        ///  FROM CSB
        //////////////////////////////////////////////////////////////////////////////

        m.NewBvInput("csb2cacc_addr", 16);
        m.NewBvInput("csb2cacc_data", 32);
        m.NewBoolInput("csb2cacc_write");
        m.NewBoolInput("csb2cacc_vld");

        //////////////////////////////////////////////////////////////////////////////
        ///  FROM CMAC
        //////////////////////////////////////////////////////////////////////////////
        
        // m.NewBvInput("csc2cacc_status", NVDLA_CMAC_PIPELINE_STATUS_WIDTH);
        // m.NewBoolInput("csc2cacc_sending_last_batch");

    }

} // namespace ilang 