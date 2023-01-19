// File: cmac_config.h

#ifndef NVDLA_CMAC_CONFIG_H
#define NVDLA_CMAC_CONFIG_H

namespace ilang {

inline std::string GetVarName(const std::string& var_name0, const std::string& var_name1) {
  return var_name0 + var_name1;
}

//////////////////////////////////////////////////////////////////////////////
///  CONFIG REGISTERS
//////////////////////////////////////////////////////////////////////////////

/* Note:
    1. CMAC is subdivided into two parts, CMAC_A and CMAC_B, to optimizae performance. 
        Although these parts have distinct interfaces, they can be treated as one unit. 
        In this model, I consider CMAC_A as the sole unit and call it CMAC for short.

    2. All sizes are in bits
*/ 

// 0x7000
#define NVDLA_CMAC_S_STATUS_0 "cmac_s_status0"
#define NVDLA_CMAC_S_STATUS_1 "cmac_s_status1"
#define NVDLA_CMAC_S_STATUS_WIDTH 2

// 0x7004
#define NVDLA_CMAC_S_PRODUCER "cmac_s_producer"
#define NVDLA_CMAC_S_CONSUMER "cmac_s_consumer"
#define NVDLA_CMAC_S_PRODUCER_WIDTH 1
#define NVDLA_CMAC_S_CONSUMER_WIDTH 1

// 0x7008
#define NVDLA_CMAC_D_OP_ENABLE "cmac_d_op_en"
#define NVDLA_CMAC_D_OP_ENABLE_WIDTH 1

// 0x700c
#define NVDLA_CMAC_D_MISC_CFG "cmac_d_misc_cfg"
#define NVDLA_CMAC_D_MISC_CFG_WIDTH 32


//////////////////////////////////////////////////////////////////////////////
/// REGISTERS STATES
//////////////////////////////////////////////////////////////////////////////

#define IDLE BvConst(0,2)
#define PEND BvConst(1,2)
#define BUSY BvConst(2,2)
#define DONE BvConst(3,2)

//////////////////////////////////////////////////////////////////////////////
///  CONSTANTS
//////////////////////////////////////////////////////////////////////////////

#define NVDLA_CMAC_INT16_KERNEL_WIDTH     1024    // 64 * 16 bits = 1024 bits
#define NVDLA_CMAC_INT16_DATA_WIDTH       16       
#define NVDLA_CMAC_INT8_DATA_WIDTH        8       
#define NVDLA_CMAC_MAC_ARRAY_ADDR_WIDTH   4       // 2 ^ 14 = 16       
#define NVDLA_CMAC_PIPELINE_STATUS_WIDTH  8       // Assumed value

// #define NVDLA_CMAC_WT_BLOCK_SIZE_INT8   512     // 64 * 8 bits = 512 bits

} // namespace ilang

#endif // NVDLA_CMAC_CONFIG_H