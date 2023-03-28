// File: "cacc_config.h

#ifndef NVDLA_CACC_CONFIG_H
#define NVDLA_CACC_CONFIG_H

namespace ilang {

inline std::string GetVarName(const std::string& var_name0, const std::string& var_name1) {
  return var_name0 + var_name1;
}

//////////////////////////////////////////////////////////////////////////////
///  CONFIG REGISTERS
//////////////////////////////////////////////////////////////////////////////

#define NVDLA_CACC_REG_WIDTH 32

// 0x9000
#define NVDLA_CACC_S_STATUS "cacc_s_status"

// 0x9004 (partially read-only)
#define NVDLA_CACC_S_POINTER "cacc_s_pointer"

// 0x9008 
#define NVDLA_CACC_D_OP_ENABLE "cacc_d_op_enable"

// 0x900c 
#define NVDLA_CACC_D_MISC_CFG "cacc_d_misc_cfg"

// 0x9010 
#define NVDLA_CACC_D_DATAOUT_SIZE_0 "cacc_d_dataout_size_0"

// 0x9014 
#define NVDLA_CACC_D_DATAOUT_SIZE_1 "cacc_d_dataout_size_1"

// 0x9018 
#define NVDLA_CACC_D_DATAOUT_ADDR "cacc_d_dataout_addr"

// 0x901c 
#define NVDLA_CACC_D_BATCH_NUMBER "cacc_d_batch_number"

// 0x9020 
#define NVDLA_CACC_D_LINE_STRIDE "cacc_d_line_stride"

// 0x9024 
#define NVDLA_CACC_D_SURF_STRIDE "cacc_d_surf_stride"

// 0x9028 
#define NVDLA_CACC_D_DATAOUT_MAP "cacc_d_dataout_map"

// 0x902c 
#define NVDLA_CACC_D_CLIP_CFG "cacc_d_clip_cfg"

// 0x9030 (read-only)
#define NVDLA_CACC_D_OUT_SATURATION "cacc_d_out_saturation"


// //////////////////////////////////////////////////////////////////////////////
// /// REGISTERS STATUS STATES
// //////////////////////////////////////////////////////////////////////////////

#define IDLE BvConst(0,2)
#define PEND BvConst(1,2)
#define BUSY BvConst(2,2)

//////////////////////////////////////////////////////////////////////////////
/// DATA PRECISION
//////////////////////////////////////////////////////////////////////////////

#define INT8  BvConst(0,2)
#define INT16 BvConst(1,2)
#define FP16  BvConst(2,2)

//////////////////////////////////////////////////////////////////////////////
/// CONVOLUTION MODE
//////////////////////////////////////////////////////////////////////////////

#define DIRECT    BvConst(0,1)
#define WINOGRAD  BvConst(1,1)

//////////////////////////////////////////////////////////////////////////////
///  OTHER CONSTANTS
//////////////////////////////////////////////////////////////////////////////

#define NVDLA_CMAC_NUM_MAC_CELLS                16  
#define NVDLA_CMAC_NUM_OUTPUTS_PER_MAC_CELL     8       

#define NVDLA_CACC_OUTPUT_ADDR_WIDTH   4        // 2 ^ 4 = 16       
#define NVDLA_CACC_OUTPUT_DATA_WIDTH   32       // width per unit output

#define NVDLA_CACC_INT16_DATA_WIDTH       16       
#define NVDLA_CACC_INT8_DATA_WIDTH        8    

#define NVDLA_CACC_PIPELINE_STATUS_WIDTH  2       // contains start and end operation flags

} // namespace ilang

#endif // NVDLA_CACC_CONFIG_H