// File: cacc_state.cc

#include <ilang/ilang++.h>
#include <cacc_config.h>

namespace ilang {

    void DefineCACCState(Ila& m){

        //////////////////////////////////////////////////////////////////////////////
        ///  FOR DEBUGGING
        //////////////////////////////////////////////////////////////////////////////
        
        m.NewBvState("tmp", NVDLA_CACC_REG_WIDTH);
        // m.NewMemState("tmp_mem", NVDLA_CMAC_KERNEL_ADDR_WIDTH, NVDLA_CMAC_KERNEL_MAX_ELEM_WIDTH);


        m.NewBvState("stripe_counter", NVDLA_CONV_STRIPE_ADDR_WIDTH);
        
        //////////////////////////////////////////////////////////////////////////////
        ///  REGISTER STATES
        //////////////////////////////////////////////////////////////////////////////

        // 0x9000 
        m.NewBvState(NVDLA_CACC_S_STATUS, NVDLA_CACC_REG_WIDTH);

        // 0x9004 
        m.NewBvState(NVDLA_CACC_S_POINTER, NVDLA_CACC_REG_WIDTH);

        // Duplicated Register Group
        for (auto i = 0; i < 2; i++) {
            auto prefix = "group" + (std::to_string(i)) + "_";

            // 0x9008 
            m.NewBvState(prefix + NVDLA_CACC_D_OP_ENABLE, NVDLA_CACC_REG_WIDTH);

            // 0x900c 
            m.NewBvState(prefix + NVDLA_CACC_D_MISC_CFG, NVDLA_CACC_REG_WIDTH);

            // 0x9010 
            m.NewBvState(prefix + NVDLA_CACC_D_DATAOUT_SIZE_0, NVDLA_CACC_REG_WIDTH);

            // 0x9014 
            m.NewBvState(prefix + NVDLA_CACC_D_DATAOUT_SIZE_1, NVDLA_CACC_REG_WIDTH);

            // 0x9018 
            m.NewBvState(prefix + NVDLA_CACC_D_DATAOUT_ADDR, NVDLA_CACC_REG_WIDTH);

            // 0x901c 
            m.NewBvState(prefix + NVDLA_CACC_D_BATCH_NUMBER, NVDLA_CACC_REG_WIDTH);

            // 0x9020 
            m.NewBvState(prefix + NVDLA_CACC_D_LINE_STRIDE, NVDLA_CACC_REG_WIDTH);

            // 0x9024 
            m.NewBvState(prefix + NVDLA_CACC_D_SURF_STRIDE, NVDLA_CACC_REG_WIDTH);

            // 0x9028 
            m.NewBvState(prefix + NVDLA_CACC_D_DATAOUT_MAP, NVDLA_CACC_REG_WIDTH);

            // 0x902c 
            m.NewBvState(prefix + NVDLA_CACC_D_CLIP_CFG, NVDLA_CACC_REG_WIDTH);

            // 0x9030 
            m.NewBvState(prefix + NVDLA_CACC_D_OUT_SATURATION, NVDLA_CACC_REG_WIDTH);
        }

        //////////////////////////////////////////////////////////////////////////////
        ///  OTHER STATES
        //////////////////////////////////////////////////////////////////////////////

        for(auto i = 0; i < NVDLA_CMAC_MAX_NUM_KERNELS; i++){
            m.NewMemState("assembly_kernel_" + (std::to_string(i)), NVDLA_CONV_STRIPE_ADDR_WIDTH, NVDLA_CACC_ACCU_INT16_BIT_WIDTH);
        } 
        
    }


} // namespace ilang 