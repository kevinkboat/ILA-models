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
if (valid_cacc() && decode_cacc_cacc_set_out_saturation_reg_group0()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_cacc_cacc_set_out_saturation_reg_group0();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("cacc_set_out_saturation_reg_group0", exec_time);
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
if (valid_cacc() && decode_cacc_cacc_set_out_saturation_reg_group1()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_cacc_cacc_set_out_saturation_reg_group1();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("cacc_set_out_saturation_reg_group1", exec_time);
#endif
}
while (1) {
  int schedule_counter = 0;
  if (schedule_counter == 0) {
    break;
  }
}
}
