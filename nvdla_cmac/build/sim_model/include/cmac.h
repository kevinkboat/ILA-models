#include <fstream>
#include <systemc.h>
#include <map>
#include <unordered_map>
struct MemAddrHashFunc {
  std::size_t operator() (int const& addr) const noexcept {
    return addr;
  }
};
SC_MODULE(cmac) {
  std::ofstream instr_log;
  std::ofstream instr_update_log;
  int GetInstrCntr();
  void IncrementInstrCntr();
  void LogInstrSequence(const std::string& instr_name, const long int&);
  sc_in<bool> cmac_csc2cmac_sending_last_batch_in;
  bool cmac_csc2cmac_sending_last_batch;
  sc_in<bool> cmac_csc2cmac_vld_in;
  bool cmac_csc2cmac_vld;
  sc_in<bool> cmac_csc2cmac_reuse_weights_in;
  bool cmac_csc2cmac_reuse_weights;
  sc_in<sc_biguint<8>> cmac_csc2cmac_status_in;
  sc_biguint<8> cmac_csc2cmac_status;
  sc_in<sc_biguint<1024>> cmac_csc2cmac_feature_kernel_in;
  sc_biguint<1024> cmac_csc2cmac_feature_kernel;
  sc_in<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_15_in;
  sc_biguint<1024> cmac_csc2cmac_weight_kernel_15;
  sc_in<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_14_in;
  sc_biguint<1024> cmac_csc2cmac_weight_kernel_14;
  sc_in<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_13_in;
  sc_biguint<1024> cmac_csc2cmac_weight_kernel_13;
  sc_in<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_12_in;
  sc_biguint<1024> cmac_csc2cmac_weight_kernel_12;
  sc_in<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_11_in;
  sc_biguint<1024> cmac_csc2cmac_weight_kernel_11;
  sc_in<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_10_in;
  sc_biguint<1024> cmac_csc2cmac_weight_kernel_10;
  sc_in<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_9_in;
  sc_biguint<1024> cmac_csc2cmac_weight_kernel_9;
  sc_in<sc_biguint<16>> cmac_csb2cmac_addr_in;
  sc_biguint<16> cmac_csb2cmac_addr;
  sc_in<sc_biguint<32>> cmac_csb2cmac_data_in;
  sc_biguint<32> cmac_csb2cmac_data;
  sc_in<sc_biguint<1>> cmac_csb2cmac_write_in;
  sc_biguint<1> cmac_csb2cmac_write;
  sc_in<sc_biguint<1>> cmac_csb2cmac_vld_in;
  sc_biguint<1> cmac_csb2cmac_vld;
  sc_in<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_0_in;
  sc_biguint<1024> cmac_csc2cmac_weight_kernel_0;
  sc_in<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_1_in;
  sc_biguint<1024> cmac_csc2cmac_weight_kernel_1;
  sc_in<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_2_in;
  sc_biguint<1024> cmac_csc2cmac_weight_kernel_2;
  sc_in<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_3_in;
  sc_biguint<1024> cmac_csc2cmac_weight_kernel_3;
  sc_in<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_4_in;
  sc_biguint<1024> cmac_csc2cmac_weight_kernel_4;
  sc_in<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_5_in;
  sc_biguint<1024> cmac_csc2cmac_weight_kernel_5;
  sc_in<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_6_in;
  sc_biguint<1024> cmac_csc2cmac_weight_kernel_6;
  sc_in<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_7_in;
  sc_biguint<1024> cmac_csc2cmac_weight_kernel_7;
  sc_in<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_8_in;
  sc_biguint<1024> cmac_csc2cmac_weight_kernel_8;
  std::unordered_map<int, sc_biguint<1024>, MemAddrHashFunc> cmac_cached_weights;
  sc_biguint<1> cmac_cmac2csb_rdy;
  sc_biguint<1> cmac_cmac2csb_data_vld;
  std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> cmac_cmac2cacc_partial_sums;
  sc_biguint<8> cmac_cmac2cacc_status;
  sc_biguint<2> cmac_cmac_state;
  sc_biguint<2> cmac_cmac_s_status0;
  sc_biguint<2> cmac_cmac_s_status1;
  sc_biguint<1> cmac_cmac_s_producer;
  sc_biguint<1> cmac_cmac_s_consumer;
  sc_biguint<1> cmac_group0_cmac_d_op_en;
  sc_biguint<32> cmac_group0_cmac_d_misc_cfg;
  sc_biguint<1> cmac_group1_cmac_d_op_en;
  sc_biguint<32> cmac_group1_cmac_d_misc_cfg;
  void compute();
  bool decode_cmac_cmac_cache_weights();
  bool decode_cmac_cmac_compute_dot_product();
  bool decode_cmac_cmac_set_config_group0();
  bool decode_cmac_cmac_set_producer();
  bool decode_cmac_cmac_set_start_group0();
  bool decode_cmac_cmac_start_from_idle();
  bool decode_cmac_pend2busy();
  void setup_initial_condition();
  void update_cmac_cmac_cache_weights();
  void update_cmac_cmac_compute_dot_product();
  void update_cmac_cmac_set_config_group0();
  void update_cmac_cmac_set_producer();
  void update_cmac_cmac_set_start_group0();
  void update_cmac_cmac_start_from_idle();
  void update_cmac_pend2busy();
  bool valid_cmac();
  SC_HAS_PROCESS(cmac);
  cmac(sc_module_name name_) : sc_module(name_) {
    SC_METHOD(compute);
    sensitive << cmac_csc2cmac_sending_last_batch_in << cmac_csc2cmac_vld_in << cmac_csc2cmac_reuse_weights_in << cmac_csc2cmac_status_in << cmac_csc2cmac_feature_kernel_in << cmac_csc2cmac_weight_kernel_15_in << cmac_csc2cmac_weight_kernel_14_in << cmac_csc2cmac_weight_kernel_13_in << cmac_csc2cmac_weight_kernel_12_in << cmac_csc2cmac_weight_kernel_11_in << cmac_csc2cmac_weight_kernel_10_in << cmac_csc2cmac_weight_kernel_9_in << cmac_csb2cmac_addr_in << cmac_csb2cmac_data_in << cmac_csb2cmac_write_in << cmac_csb2cmac_vld_in << cmac_csc2cmac_weight_kernel_0_in << cmac_csc2cmac_weight_kernel_1_in << cmac_csc2cmac_weight_kernel_2_in << cmac_csc2cmac_weight_kernel_3_in << cmac_csc2cmac_weight_kernel_4_in << cmac_csc2cmac_weight_kernel_5_in << cmac_csc2cmac_weight_kernel_6_in << cmac_csc2cmac_weight_kernel_7_in << cmac_csc2cmac_weight_kernel_8_in;
  }
};
