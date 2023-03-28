#include <iomanip>
#include <cacc.h>
#include <chrono>
static int instr_cntr = 0;
int cacc::GetInstrCntr() {
  return instr_cntr;
}
void cacc::IncrementInstrCntr() {
  instr_cntr++;
}
void cacc::LogInstrSequence(const std::string& instr_name, const long int& exec_time) {
  instr_log << "Instr No. " << std::setw(8) << GetInstrCntr() << '\t';
  instr_log << instr_name << " is activated\t";
  instr_log << "exec_time: " << exec_time * 1e-3 << " us\n";
  IncrementInstrCntr();
}
static bool g_initialized = false;
void cacc::compute() {
if (!g_initialized) {
  setup_initial_condition();
  g_initialized = true;
}
cacc_csb2cacc_addr = cacc_csb2cacc_addr_in.read();
cacc_csb2cacc_data = cacc_csb2cacc_data_in.read();
cacc_csb2cacc_write = cacc_csb2cacc_write_in.read();
cacc_csb2cacc_vld = cacc_csb2cacc_vld_in.read();
cacc_cmac2cacc_ps_mac_0_0 = cacc_cmac2cacc_ps_mac_0_0_in.read();
cacc_cmac2cacc_ps_mac_0_1 = cacc_cmac2cacc_ps_mac_0_1_in.read();
cacc_cmac2cacc_ps_mac_0_2 = cacc_cmac2cacc_ps_mac_0_2_in.read();
cacc_cmac2cacc_ps_mac_0_3 = cacc_cmac2cacc_ps_mac_0_3_in.read();
cacc_cmac2cacc_ps_mac_0_4 = cacc_cmac2cacc_ps_mac_0_4_in.read();
cacc_cmac2cacc_ps_mac_0_5 = cacc_cmac2cacc_ps_mac_0_5_in.read();
cacc_cmac2cacc_ps_mac_0_6 = cacc_cmac2cacc_ps_mac_0_6_in.read();
cacc_cmac2cacc_ps_mac_0_7 = cacc_cmac2cacc_ps_mac_0_7_in.read();
cacc_cmac2cacc_ps_mac_1_0 = cacc_cmac2cacc_ps_mac_1_0_in.read();
cacc_cmac2cacc_ps_mac_1_1 = cacc_cmac2cacc_ps_mac_1_1_in.read();
cacc_cmac2cacc_ps_mac_1_2 = cacc_cmac2cacc_ps_mac_1_2_in.read();
cacc_cmac2cacc_ps_mac_1_3 = cacc_cmac2cacc_ps_mac_1_3_in.read();
cacc_cmac2cacc_ps_mac_1_4 = cacc_cmac2cacc_ps_mac_1_4_in.read();
cacc_cmac2cacc_ps_mac_1_5 = cacc_cmac2cacc_ps_mac_1_5_in.read();
cacc_cmac2cacc_ps_mac_1_6 = cacc_cmac2cacc_ps_mac_1_6_in.read();
cacc_cmac2cacc_ps_mac_1_7 = cacc_cmac2cacc_ps_mac_1_7_in.read();
cacc_cmac2cacc_ps_mac_2_0 = cacc_cmac2cacc_ps_mac_2_0_in.read();
cacc_cmac2cacc_ps_mac_2_1 = cacc_cmac2cacc_ps_mac_2_1_in.read();
cacc_cmac2cacc_ps_mac_2_2 = cacc_cmac2cacc_ps_mac_2_2_in.read();
cacc_cmac2cacc_ps_mac_2_3 = cacc_cmac2cacc_ps_mac_2_3_in.read();
cacc_cmac2cacc_ps_mac_2_4 = cacc_cmac2cacc_ps_mac_2_4_in.read();
cacc_cmac2cacc_ps_mac_2_5 = cacc_cmac2cacc_ps_mac_2_5_in.read();
cacc_cmac2cacc_ps_mac_2_6 = cacc_cmac2cacc_ps_mac_2_6_in.read();
cacc_cmac2cacc_ps_mac_2_7 = cacc_cmac2cacc_ps_mac_2_7_in.read();
cacc_cmac2cacc_ps_mac_3_0 = cacc_cmac2cacc_ps_mac_3_0_in.read();
cacc_cmac2cacc_ps_mac_3_1 = cacc_cmac2cacc_ps_mac_3_1_in.read();
cacc_cmac2cacc_ps_mac_3_2 = cacc_cmac2cacc_ps_mac_3_2_in.read();
cacc_cmac2cacc_ps_mac_3_3 = cacc_cmac2cacc_ps_mac_3_3_in.read();
cacc_cmac2cacc_ps_mac_3_4 = cacc_cmac2cacc_ps_mac_3_4_in.read();
cacc_cmac2cacc_ps_mac_3_5 = cacc_cmac2cacc_ps_mac_3_5_in.read();
cacc_cmac2cacc_ps_mac_3_6 = cacc_cmac2cacc_ps_mac_3_6_in.read();
cacc_cmac2cacc_ps_mac_3_7 = cacc_cmac2cacc_ps_mac_3_7_in.read();
cacc_cmac2cacc_ps_mac_4_0 = cacc_cmac2cacc_ps_mac_4_0_in.read();
cacc_cmac2cacc_ps_mac_4_1 = cacc_cmac2cacc_ps_mac_4_1_in.read();
cacc_cmac2cacc_ps_mac_4_2 = cacc_cmac2cacc_ps_mac_4_2_in.read();
cacc_cmac2cacc_ps_mac_4_3 = cacc_cmac2cacc_ps_mac_4_3_in.read();
cacc_cmac2cacc_ps_mac_4_4 = cacc_cmac2cacc_ps_mac_4_4_in.read();
cacc_cmac2cacc_ps_mac_4_5 = cacc_cmac2cacc_ps_mac_4_5_in.read();
cacc_cmac2cacc_ps_mac_4_6 = cacc_cmac2cacc_ps_mac_4_6_in.read();
cacc_cmac2cacc_ps_mac_4_7 = cacc_cmac2cacc_ps_mac_4_7_in.read();
cacc_cmac2cacc_ps_mac_5_0 = cacc_cmac2cacc_ps_mac_5_0_in.read();
cacc_cmac2cacc_ps_mac_5_1 = cacc_cmac2cacc_ps_mac_5_1_in.read();
cacc_cmac2cacc_ps_mac_5_2 = cacc_cmac2cacc_ps_mac_5_2_in.read();
cacc_cmac2cacc_ps_mac_5_3 = cacc_cmac2cacc_ps_mac_5_3_in.read();
cacc_cmac2cacc_ps_mac_5_4 = cacc_cmac2cacc_ps_mac_5_4_in.read();
cacc_cmac2cacc_ps_mac_5_5 = cacc_cmac2cacc_ps_mac_5_5_in.read();
cacc_cmac2cacc_ps_mac_5_6 = cacc_cmac2cacc_ps_mac_5_6_in.read();
cacc_cmac2cacc_ps_mac_5_7 = cacc_cmac2cacc_ps_mac_5_7_in.read();
cacc_cmac2cacc_ps_mac_6_0 = cacc_cmac2cacc_ps_mac_6_0_in.read();
cacc_cmac2cacc_ps_mac_6_1 = cacc_cmac2cacc_ps_mac_6_1_in.read();
cacc_cmac2cacc_ps_mac_6_2 = cacc_cmac2cacc_ps_mac_6_2_in.read();
cacc_cmac2cacc_ps_mac_6_3 = cacc_cmac2cacc_ps_mac_6_3_in.read();
cacc_cmac2cacc_ps_mac_6_4 = cacc_cmac2cacc_ps_mac_6_4_in.read();
cacc_cmac2cacc_ps_mac_6_5 = cacc_cmac2cacc_ps_mac_6_5_in.read();
cacc_cmac2cacc_ps_mac_6_6 = cacc_cmac2cacc_ps_mac_6_6_in.read();
cacc_cmac2cacc_ps_mac_6_7 = cacc_cmac2cacc_ps_mac_6_7_in.read();
cacc_cmac2cacc_ps_mac_7_0 = cacc_cmac2cacc_ps_mac_7_0_in.read();
cacc_cmac2cacc_ps_mac_7_1 = cacc_cmac2cacc_ps_mac_7_1_in.read();
cacc_cmac2cacc_ps_mac_7_2 = cacc_cmac2cacc_ps_mac_7_2_in.read();
cacc_cmac2cacc_ps_mac_7_3 = cacc_cmac2cacc_ps_mac_7_3_in.read();
cacc_cmac2cacc_ps_mac_7_4 = cacc_cmac2cacc_ps_mac_7_4_in.read();
cacc_cmac2cacc_ps_mac_7_5 = cacc_cmac2cacc_ps_mac_7_5_in.read();
cacc_cmac2cacc_ps_mac_7_6 = cacc_cmac2cacc_ps_mac_7_6_in.read();
cacc_cmac2cacc_ps_mac_7_7 = cacc_cmac2cacc_ps_mac_7_7_in.read();
cacc_cmac2cacc_ps_mac_8_0 = cacc_cmac2cacc_ps_mac_8_0_in.read();
cacc_cmac2cacc_ps_mac_8_1 = cacc_cmac2cacc_ps_mac_8_1_in.read();
cacc_cmac2cacc_ps_mac_8_2 = cacc_cmac2cacc_ps_mac_8_2_in.read();
cacc_cmac2cacc_ps_mac_8_3 = cacc_cmac2cacc_ps_mac_8_3_in.read();
cacc_cmac2cacc_ps_mac_8_4 = cacc_cmac2cacc_ps_mac_8_4_in.read();
cacc_cmac2cacc_ps_mac_8_5 = cacc_cmac2cacc_ps_mac_8_5_in.read();
cacc_cmac2cacc_ps_mac_8_6 = cacc_cmac2cacc_ps_mac_8_6_in.read();
cacc_cmac2cacc_ps_mac_8_7 = cacc_cmac2cacc_ps_mac_8_7_in.read();
cacc_cmac2cacc_ps_mac_9_0 = cacc_cmac2cacc_ps_mac_9_0_in.read();
cacc_cmac2cacc_ps_mac_9_1 = cacc_cmac2cacc_ps_mac_9_1_in.read();
cacc_cmac2cacc_ps_mac_9_2 = cacc_cmac2cacc_ps_mac_9_2_in.read();
cacc_cmac2cacc_ps_mac_9_3 = cacc_cmac2cacc_ps_mac_9_3_in.read();
cacc_cmac2cacc_ps_mac_9_4 = cacc_cmac2cacc_ps_mac_9_4_in.read();
cacc_cmac2cacc_ps_mac_9_5 = cacc_cmac2cacc_ps_mac_9_5_in.read();
cacc_cmac2cacc_ps_mac_9_6 = cacc_cmac2cacc_ps_mac_9_6_in.read();
cacc_cmac2cacc_ps_mac_9_7 = cacc_cmac2cacc_ps_mac_9_7_in.read();
cacc_cmac2cacc_ps_mac_10_0 = cacc_cmac2cacc_ps_mac_10_0_in.read();
cacc_cmac2cacc_ps_mac_10_1 = cacc_cmac2cacc_ps_mac_10_1_in.read();
cacc_cmac2cacc_ps_mac_10_2 = cacc_cmac2cacc_ps_mac_10_2_in.read();
cacc_cmac2cacc_ps_mac_10_3 = cacc_cmac2cacc_ps_mac_10_3_in.read();
cacc_cmac2cacc_ps_mac_10_4 = cacc_cmac2cacc_ps_mac_10_4_in.read();
cacc_cmac2cacc_ps_mac_10_5 = cacc_cmac2cacc_ps_mac_10_5_in.read();
cacc_cmac2cacc_ps_mac_10_6 = cacc_cmac2cacc_ps_mac_10_6_in.read();
cacc_cmac2cacc_ps_mac_10_7 = cacc_cmac2cacc_ps_mac_10_7_in.read();
cacc_cmac2cacc_ps_mac_11_0 = cacc_cmac2cacc_ps_mac_11_0_in.read();
cacc_cmac2cacc_ps_mac_11_1 = cacc_cmac2cacc_ps_mac_11_1_in.read();
cacc_cmac2cacc_ps_mac_11_2 = cacc_cmac2cacc_ps_mac_11_2_in.read();
cacc_cmac2cacc_ps_mac_11_3 = cacc_cmac2cacc_ps_mac_11_3_in.read();
cacc_cmac2cacc_ps_mac_11_4 = cacc_cmac2cacc_ps_mac_11_4_in.read();
cacc_cmac2cacc_ps_mac_11_5 = cacc_cmac2cacc_ps_mac_11_5_in.read();
cacc_cmac2cacc_ps_mac_11_6 = cacc_cmac2cacc_ps_mac_11_6_in.read();
cacc_cmac2cacc_ps_mac_11_7 = cacc_cmac2cacc_ps_mac_11_7_in.read();
cacc_cmac2cacc_ps_mac_12_0 = cacc_cmac2cacc_ps_mac_12_0_in.read();
cacc_cmac2cacc_ps_mac_12_1 = cacc_cmac2cacc_ps_mac_12_1_in.read();
cacc_cmac2cacc_ps_mac_12_2 = cacc_cmac2cacc_ps_mac_12_2_in.read();
cacc_cmac2cacc_ps_mac_12_3 = cacc_cmac2cacc_ps_mac_12_3_in.read();
cacc_cmac2cacc_ps_mac_12_4 = cacc_cmac2cacc_ps_mac_12_4_in.read();
cacc_cmac2cacc_ps_mac_12_5 = cacc_cmac2cacc_ps_mac_12_5_in.read();
cacc_cmac2cacc_ps_mac_12_6 = cacc_cmac2cacc_ps_mac_12_6_in.read();
cacc_cmac2cacc_ps_mac_12_7 = cacc_cmac2cacc_ps_mac_12_7_in.read();
cacc_cmac2cacc_ps_mac_13_0 = cacc_cmac2cacc_ps_mac_13_0_in.read();
cacc_cmac2cacc_ps_mac_13_1 = cacc_cmac2cacc_ps_mac_13_1_in.read();
cacc_cmac2cacc_ps_mac_13_2 = cacc_cmac2cacc_ps_mac_13_2_in.read();
cacc_cmac2cacc_ps_mac_13_3 = cacc_cmac2cacc_ps_mac_13_3_in.read();
cacc_cmac2cacc_ps_mac_13_4 = cacc_cmac2cacc_ps_mac_13_4_in.read();
cacc_cmac2cacc_ps_mac_13_5 = cacc_cmac2cacc_ps_mac_13_5_in.read();
cacc_cmac2cacc_ps_mac_13_6 = cacc_cmac2cacc_ps_mac_13_6_in.read();
cacc_cmac2cacc_ps_mac_13_7 = cacc_cmac2cacc_ps_mac_13_7_in.read();
cacc_cmac2cacc_ps_mac_14_0 = cacc_cmac2cacc_ps_mac_14_0_in.read();
cacc_cmac2cacc_ps_mac_14_1 = cacc_cmac2cacc_ps_mac_14_1_in.read();
cacc_cmac2cacc_ps_mac_14_2 = cacc_cmac2cacc_ps_mac_14_2_in.read();
cacc_cmac2cacc_ps_mac_14_3 = cacc_cmac2cacc_ps_mac_14_3_in.read();
cacc_cmac2cacc_ps_mac_14_4 = cacc_cmac2cacc_ps_mac_14_4_in.read();
cacc_cmac2cacc_ps_mac_14_5 = cacc_cmac2cacc_ps_mac_14_5_in.read();
cacc_cmac2cacc_ps_mac_14_6 = cacc_cmac2cacc_ps_mac_14_6_in.read();
cacc_cmac2cacc_ps_mac_14_7 = cacc_cmac2cacc_ps_mac_14_7_in.read();
cacc_cmac2cacc_ps_mac_15_0 = cacc_cmac2cacc_ps_mac_15_0_in.read();
cacc_cmac2cacc_ps_mac_15_1 = cacc_cmac2cacc_ps_mac_15_1_in.read();
cacc_cmac2cacc_ps_mac_15_2 = cacc_cmac2cacc_ps_mac_15_2_in.read();
cacc_cmac2cacc_ps_mac_15_3 = cacc_cmac2cacc_ps_mac_15_3_in.read();
cacc_cmac2cacc_ps_mac_15_4 = cacc_cmac2cacc_ps_mac_15_4_in.read();
cacc_cmac2cacc_ps_mac_15_5 = cacc_cmac2cacc_ps_mac_15_5_in.read();
cacc_cmac2cacc_ps_mac_15_6 = cacc_cmac2cacc_ps_mac_15_6_in.read();
cacc_cmac2cacc_ps_mac_15_7 = cacc_cmac2cacc_ps_mac_15_7_in.read();
cacc_cmac2cacc_status = cacc_cmac2cacc_status_in.read();
if (valid_cacc() && decode_cacc_cacc_set_producer()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_cacc_cacc_set_producer();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("cacc_set_producer", exec_time);
#endif
}
if (valid_cacc() && decode_cacc_cacc_set_op_enable_reg_group0()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_cacc_cacc_set_op_enable_reg_group0();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("cacc_set_op_enable_reg_group0", exec_time);
#endif
}
if (valid_cacc() && decode_cacc_cacc_set_misc_cfg_reg_group0()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_cacc_cacc_set_misc_cfg_reg_group0();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("cacc_set_misc_cfg_reg_group0", exec_time);
#endif
}
if (valid_cacc() && decode_cacc_cacc_set_dataout_size_0_reg_group0()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_cacc_cacc_set_dataout_size_0_reg_group0();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("cacc_set_dataout_size_0_reg_group0", exec_time);
#endif
}
if (valid_cacc() && decode_cacc_cacc_set_dataout_size_1_reg_group0()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_cacc_cacc_set_dataout_size_1_reg_group0();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("cacc_set_dataout_size_1_reg_group0", exec_time);
#endif
}
if (valid_cacc() && decode_cacc_cacc_set_dataout_addr_reg_group0()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_cacc_cacc_set_dataout_addr_reg_group0();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("cacc_set_dataout_addr_reg_group0", exec_time);
#endif
}
if (valid_cacc() && decode_cacc_cacc_set_batch_number_reg_group0()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_cacc_cacc_set_batch_number_reg_group0();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("cacc_set_batch_number_reg_group0", exec_time);
#endif
}
if (valid_cacc() && decode_cacc_cacc_set_line_stride_reg_group0()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_cacc_cacc_set_line_stride_reg_group0();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("cacc_set_line_stride_reg_group0", exec_time);
#endif
}
if (valid_cacc() && decode_cacc_cacc_set_surf_stride_reg_group0()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_cacc_cacc_set_surf_stride_reg_group0();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("cacc_set_surf_stride_reg_group0", exec_time);
#endif
}
if (valid_cacc() && decode_cacc_cacc_set_dataout_map_reg_group0()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_cacc_cacc_set_dataout_map_reg_group0();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("cacc_set_dataout_map_reg_group0", exec_time);
#endif
}
if (valid_cacc() && decode_cacc_cacc_set_clip_cfg_reg_group0()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_cacc_cacc_set_clip_cfg_reg_group0();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("cacc_set_clip_cfg_reg_group0", exec_time);
#endif
}
if (valid_cacc() && decode_cacc_cacc_set_op_enable_reg_group1()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_cacc_cacc_set_op_enable_reg_group1();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("cacc_set_op_enable_reg_group1", exec_time);
#endif
}
if (valid_cacc() && decode_cacc_cacc_set_misc_cfg_reg_group1()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_cacc_cacc_set_misc_cfg_reg_group1();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("cacc_set_misc_cfg_reg_group1", exec_time);
#endif
}
if (valid_cacc() && decode_cacc_cacc_set_dataout_size_0_reg_group1()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_cacc_cacc_set_dataout_size_0_reg_group1();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("cacc_set_dataout_size_0_reg_group1", exec_time);
#endif
}
if (valid_cacc() && decode_cacc_cacc_set_dataout_size_1_reg_group1()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_cacc_cacc_set_dataout_size_1_reg_group1();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("cacc_set_dataout_size_1_reg_group1", exec_time);
#endif
}
if (valid_cacc() && decode_cacc_cacc_set_dataout_addr_reg_group1()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_cacc_cacc_set_dataout_addr_reg_group1();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("cacc_set_dataout_addr_reg_group1", exec_time);
#endif
}
if (valid_cacc() && decode_cacc_cacc_set_batch_number_reg_group1()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_cacc_cacc_set_batch_number_reg_group1();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("cacc_set_batch_number_reg_group1", exec_time);
#endif
}
if (valid_cacc() && decode_cacc_cacc_set_line_stride_reg_group1()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_cacc_cacc_set_line_stride_reg_group1();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("cacc_set_line_stride_reg_group1", exec_time);
#endif
}
if (valid_cacc() && decode_cacc_cacc_set_surf_stride_reg_group1()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_cacc_cacc_set_surf_stride_reg_group1();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("cacc_set_surf_stride_reg_group1", exec_time);
#endif
}
if (valid_cacc() && decode_cacc_cacc_set_dataout_map_reg_group1()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_cacc_cacc_set_dataout_map_reg_group1();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("cacc_set_dataout_map_reg_group1", exec_time);
#endif
}
if (valid_cacc() && decode_cacc_cacc_set_clip_cfg_reg_group1()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_cacc_cacc_set_clip_cfg_reg_group1();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("cacc_set_clip_cfg_reg_group1", exec_time);
#endif
}
while (1) {
  int schedule_counter = 0;
  if (schedule_counter == 0) {
    break;
  }
}
}
