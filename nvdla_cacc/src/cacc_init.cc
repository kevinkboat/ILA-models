// File: cacc_init.cc

#include <ilang/ilang++.h>
#include <cacc_config.h>

namespace ilang {

    void DefineCACCInit(Ila& m){

        //////////////////////////////////////////////////////////////////////////////
        ///  OUTPUTS
        //////////////////////////////////////////////////////////////////////////////

        

        //////////////////////////////////////////////////////////////////////////////
        ///  INTERNAL STATES
        //////////////////////////////////////////////////////////////////////////////
        
        m.AddInit(m.state(NVDLA_CACC_S_STATUS) == BvConst(0, NVDLA_CACC_REG_WIDTH));        
        m.AddInit(m.state(NVDLA_CACC_S_POINTER) == BvConst(0, NVDLA_CACC_REG_WIDTH));

        for (auto i = 0; i < 2; i++) {
            auto prefix = "group" + (std::to_string(i)) + "_";

            m.AddInit(m.state(prefix + NVDLA_CACC_D_OP_ENABLE) == BvConst(0, NVDLA_CACC_REG_WIDTH));
            m.AddInit(m.state(prefix + NVDLA_CACC_D_MISC_CFG) == BvConst(0, NVDLA_CACC_REG_WIDTH));
            m.AddInit(m.state(prefix + NVDLA_CACC_D_DATAOUT_SIZE_0) == BvConst(0, NVDLA_CACC_REG_WIDTH));
            m.AddInit(m.state(prefix + NVDLA_CACC_D_DATAOUT_SIZE_1) == BvConst(0, NVDLA_CACC_REG_WIDTH));
            m.AddInit(m.state(prefix + NVDLA_CACC_D_DATAOUT_ADDR) == BvConst(0, NVDLA_CACC_REG_WIDTH));
            m.AddInit(m.state(prefix + NVDLA_CACC_D_BATCH_NUMBER) == BvConst(0, NVDLA_CACC_REG_WIDTH));
            m.AddInit(m.state(prefix + NVDLA_CACC_D_LINE_STRIDE) == BvConst(0, NVDLA_CACC_REG_WIDTH));
            m.AddInit(m.state(prefix + NVDLA_CACC_D_SURF_STRIDE) == BvConst(0, NVDLA_CACC_REG_WIDTH));
            m.AddInit(m.state(prefix + NVDLA_CACC_D_DATAOUT_MAP) == BvConst(0, NVDLA_CACC_REG_WIDTH));
            m.AddInit(m.state(prefix + NVDLA_CACC_D_CLIP_CFG) == BvConst(0, NVDLA_CACC_REG_WIDTH));
            m.AddInit(m.state(prefix + NVDLA_CACC_D_OUT_SATURATION) == BvConst(0, NVDLA_CACC_REG_WIDTH));
        }
    }

} // namespace ilang 