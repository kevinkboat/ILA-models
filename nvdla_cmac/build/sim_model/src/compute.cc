#include <iomanip>
#include <cmac.h>
#include <chrono>
static int instr_cntr = 0;
int cmac::GetInstrCntr() {
  return instr_cntr;
}
void cmac::IncrementInstrCntr() {
  instr_cntr++;
}
void cmac::LogInstrSequence(const std::string& instr_name, const long int& exec_time) {
  instr_log << "Instr No. " << std::setw(8) << GetInstrCntr() << '\t';
  instr_log << instr_name << " is activated\t";
  instr_log << "exec_time: " << exec_time * 1e-3 << " us\n";
  IncrementInstrCntr();
}
static bool g_initialized = false;
void cmac::compute() {
if (!g_initialized) {
  setup_initial_condition();
  g_initialized = true;
}
cmac_csb2cmac_addr = cmac_csb2cmac_addr_in.read();
cmac_csb2cmac_data = cmac_csb2cmac_data_in.read();
cmac_csb2cmac_write = cmac_csb2cmac_write_in.read();
cmac_csb2cmac_vld = cmac_csb2cmac_vld_in.read();
cmac_csc2cmac_weight_kernel_0 = cmac_csc2cmac_weight_kernel_0_in.read();
cmac_csc2cmac_weight_kernel_1 = cmac_csc2cmac_weight_kernel_1_in.read();
cmac_csc2cmac_weight_kernel_2 = cmac_csc2cmac_weight_kernel_2_in.read();
cmac_csc2cmac_weight_kernel_3 = cmac_csc2cmac_weight_kernel_3_in.read();
cmac_csc2cmac_weight_kernel_4 = cmac_csc2cmac_weight_kernel_4_in.read();
cmac_csc2cmac_weight_kernel_5 = cmac_csc2cmac_weight_kernel_5_in.read();
cmac_csc2cmac_weight_kernel_6 = cmac_csc2cmac_weight_kernel_6_in.read();
cmac_csc2cmac_weight_kernel_7 = cmac_csc2cmac_weight_kernel_7_in.read();
cmac_csc2cmac_weight_kernel_8 = cmac_csc2cmac_weight_kernel_8_in.read();
cmac_csc2cmac_weight_kernel_9 = cmac_csc2cmac_weight_kernel_9_in.read();
cmac_csc2cmac_weight_kernel_10 = cmac_csc2cmac_weight_kernel_10_in.read();
cmac_csc2cmac_weight_kernel_11 = cmac_csc2cmac_weight_kernel_11_in.read();
cmac_csc2cmac_weight_kernel_12 = cmac_csc2cmac_weight_kernel_12_in.read();
cmac_csc2cmac_weight_kernel_13 = cmac_csc2cmac_weight_kernel_13_in.read();
cmac_csc2cmac_weight_kernel_14 = cmac_csc2cmac_weight_kernel_14_in.read();
cmac_csc2cmac_weight_kernel_15 = cmac_csc2cmac_weight_kernel_15_in.read();
cmac_csc2cmac_feature_kernel = cmac_csc2cmac_feature_kernel_in.read();
cmac_csc2cmac_status = cmac_csc2cmac_status_in.read();
cmac_csc2cmac_reuse_weights = cmac_csc2cmac_reuse_weights_in.read();
cmac_csc2cmac_vld = cmac_csc2cmac_vld_in.read();
cmac_csc2cmac_sending_last_batch = cmac_csc2cmac_sending_last_batch_in.read();
if (valid_cmac() && decode_cmac_cmac_set_producer()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_cmac_cmac_set_producer();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("cmac_set_producer", exec_time);
#endif
}
if (valid_cmac() && decode_cmac_cmac_set_start_group0()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_cmac_cmac_set_start_group0();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("cmac_set_start_group0", exec_time);
#endif
}
if (valid_cmac() && decode_cmac_cmac_set_config_group0()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_cmac_cmac_set_config_group0();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("cmac_set_config_group0", exec_time);
#endif
}
if (valid_cmac() && decode_cmac_cmac_start_from_idle()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_cmac_cmac_start_from_idle();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("cmac_start_from_idle", exec_time);
#endif
}
if (valid_cmac() && decode_cmac_pend2busy()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_cmac_pend2busy();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("pend2busy", exec_time);
#endif
}
if (valid_cmac() && decode_cmac_cmac_cache_weights()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_cmac_cmac_cache_weights();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("cmac_cache_weights", exec_time);
#endif
}
if (valid_cmac() && decode_cmac_cmac_compute_dot_product()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_cmac_cmac_compute_dot_product();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("cmac_compute_dot_product", exec_time);
#endif
}
while (1) {
  int schedule_counter = 0;
  if (schedule_counter == 0) {
    break;
  }
}
}
