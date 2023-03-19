// File: cmac_state.cc

#include <ilang/ilang++.h>
#include <cmac_config.h>

namespace ilang {

    void DefineCMACState(Ila& m){

        //////////////////////////////////////////////////////////////////////////////
        ///  FOR DEBUGGING
        //////////////////////////////////////////////////////////////////////////////
        
        // m.NewBvState("tmp", NVDLA_CMAC_KERNEL_MAX_ELEM_WIDTH);
        // m.NewMemState("tmp_mem", NVDLA_CMAC_KERNEL_ADDR_WIDTH, NVDLA_CMAC_KERNEL_MAX_ELEM_WIDTH);

        //////////////////////////////////////////////////////////////////////////////
        ///  REGISTER STATES
        //////////////////////////////////////////////////////////////////////////////

        // 0x7000
        m.NewBvState(NVDLA_CMAC_S_STATUS_0, NVDLA_CMAC_S_STATUS_WIDTH);
        m.NewBvState(NVDLA_CMAC_S_STATUS_1, NVDLA_CMAC_S_STATUS_WIDTH);

        // 0x7004
        m.NewBvState(NVDLA_CMAC_S_PRODUCER, NVDLA_CMAC_S_PRODUCER_WIDTH);
        m.NewBvState(NVDLA_CMAC_S_CONSUMER, NVDLA_CMAC_S_CONSUMER_WIDTH);

        // Duplicated Register Group
        for (auto i = 0; i < 2; i++) {
            // 0x7008
            m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_CMAC_D_OP_ENABLE, NVDLA_CMAC_D_OP_ENABLE_WIDTH);
            // 0x700c
            m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_CMAC_D_MISC_CFG, NVDLA_CMAC_D_MISC_CFG_WIDTH);
        }

        //////////////////////////////////////////////////////////////////////////////
        ///  MAC ARRAY STATES
        //////////////////////////////////////////////////////////////////////////////

        // Cached Weight Kernels
        for (auto i = 0; i < NVDLA_CMAC_MAX_NUM_KERNELS_ATOMIC_OP; i++) {
            m.NewMemState("cached_wt_kernel_" + (std::to_string(i)), NVDLA_CMAC_KERNEL_ADDR_WIDTH, NVDLA_CMAC_KERNEL_MAX_ELEM_WIDTH);
        } 
        
    }


} // namespace ilang 