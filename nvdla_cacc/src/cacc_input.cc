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
        
        // CMAC output
        // // MAC array outputs
        // for(auto i = 0; i < NVDLA_CMAC_NUM_MAC_CELLS; i++){
        //     m.NewMemState("cmac2cacc_partial_sum_mac_" + (std::to_string(i)), NVDLA_CMAC_MAC_CELL_OUTPUT_ADDR_WIDTH, NVDLA_CMAC_KERNEL_MAX_ELEM_WIDTH);
        // }
        
        // m.NewBvState("cmac2cacc_status", NVDLA_CMAC_PIPELINE_STATUS_WIDTH);


        // Partial sums
        for (auto i = 0; i < NVDLA_CMAC_NUM_MAC_CELLS; i++){
            for (auto j = 0; j < NVDLA_CMAC_NUM_OUTPUTS_PER_MAC_CELL; j++){
                m.NewBvInput("cmac2cacc_ps_mac_" + (std::to_string(i)) + "_" + (std::to_string(j)), NVDLA_CACC_INT16_DATA_WIDTH);
            }
        }

        m.NewBvInput("cmac2cacc_status", NVDLA_CACC_PIPELINE_STATUS_WIDTH);
    }

} // namespace ilang 