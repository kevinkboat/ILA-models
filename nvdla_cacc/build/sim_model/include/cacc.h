#include <fstream>
#include <systemc.h>
#include <map>
#include <unordered_map>
struct MemAddrHashFunc {
  std::size_t operator() (int const& addr) const noexcept {
    return addr;
  }
};
SC_MODULE(cacc) {
  std::ofstream instr_log;
  std::ofstream instr_update_log;
  int GetInstrCntr();
  void IncrementInstrCntr();
  void LogInstrSequence(const std::string& instr_name, const long int&);
  sc_in<bool> cacc_csb2cacc_vld_in;
  bool cacc_csb2cacc_vld;
  sc_in<bool> cacc_csb2cacc_write_in;
  bool cacc_csb2cacc_write;
  sc_in<sc_biguint<32>> cacc_csb2cacc_data_in;
  sc_biguint<32> cacc_csb2cacc_data;
  sc_in<sc_biguint<16>> cacc_csb2cacc_addr_in;
  sc_biguint<16> cacc_csb2cacc_addr;
  sc_biguint<32> cacc_group1_cacc_d_out_saturation;
  sc_biguint<32> cacc_group1_cacc_d_clip_cfg;
  sc_biguint<32> cacc_group1_cacc_d_dataout_map;
  sc_biguint<32> cacc_group1_cacc_d_surf_stride;
  sc_biguint<32> cacc_group1_cacc_d_line_stride;
  sc_biguint<32> cacc_group1_cacc_d_batch_number;
  sc_biguint<32> cacc_group1_cacc_d_dataout_addr;
  sc_biguint<32> cacc_group1_cacc_d_dataout_size_1;
  sc_biguint<32> cacc_group1_cacc_d_dataout_size_0;
  sc_biguint<32> cacc_group1_cacc_d_misc_cfg;
  sc_biguint<32> cacc_group1_cacc_d_op_enable;
  sc_biguint<32> cacc_group0_cacc_d_out_saturation;
  sc_biguint<32> cacc_group0_cacc_d_clip_cfg;
  bool cacc_cacc2csb_rdy;
  bool cacc_cacc2csb_data_vld;
  sc_biguint<32> cacc_cacc_s_status;
  sc_biguint<32> cacc_cacc_s_pointer;
  sc_biguint<32> cacc_group0_cacc_d_op_enable;
  sc_biguint<32> cacc_group0_cacc_d_misc_cfg;
  sc_biguint<32> cacc_group0_cacc_d_dataout_size_0;
  sc_biguint<32> cacc_group0_cacc_d_dataout_size_1;
  sc_biguint<32> cacc_group0_cacc_d_dataout_addr;
  sc_biguint<32> cacc_group0_cacc_d_batch_number;
  sc_biguint<32> cacc_group0_cacc_d_line_stride;
  sc_biguint<32> cacc_group0_cacc_d_surf_stride;
  sc_biguint<32> cacc_group0_cacc_d_dataout_map;
  void compute();
  bool decode_cacc_cacc_set_batch_number_reg_group0();
  bool decode_cacc_cacc_set_batch_number_reg_group1();
  bool decode_cacc_cacc_set_clip_cfg_reg_group0();
  bool decode_cacc_cacc_set_clip_cfg_reg_group1();
  bool decode_cacc_cacc_set_dataout_addr_reg_group0();
  bool decode_cacc_cacc_set_dataout_addr_reg_group1();
  bool decode_cacc_cacc_set_dataout_map_reg_group0();
  bool decode_cacc_cacc_set_dataout_map_reg_group1();
  bool decode_cacc_cacc_set_dataout_size_0_reg_group0();
  bool decode_cacc_cacc_set_dataout_size_0_reg_group1();
  bool decode_cacc_cacc_set_dataout_size_1_reg_group0();
  bool decode_cacc_cacc_set_dataout_size_1_reg_group1();
  bool decode_cacc_cacc_set_line_stride_reg_group0();
  bool decode_cacc_cacc_set_line_stride_reg_group1();
  bool decode_cacc_cacc_set_misc_cfg_reg_group0();
  bool decode_cacc_cacc_set_misc_cfg_reg_group1();
  bool decode_cacc_cacc_set_op_enable_reg_group0();
  bool decode_cacc_cacc_set_op_enable_reg_group1();
  bool decode_cacc_cacc_set_out_saturation_reg_group0();
  bool decode_cacc_cacc_set_out_saturation_reg_group1();
  bool decode_cacc_cacc_set_producer();
  bool decode_cacc_cacc_set_surf_stride_reg_group0();
  bool decode_cacc_cacc_set_surf_stride_reg_group1();
  void setup_initial_condition();
  void update_cacc_cacc_set_batch_number_reg_group0();
  void update_cacc_cacc_set_batch_number_reg_group1();
  void update_cacc_cacc_set_clip_cfg_reg_group0();
  void update_cacc_cacc_set_clip_cfg_reg_group1();
  void update_cacc_cacc_set_dataout_addr_reg_group0();
  void update_cacc_cacc_set_dataout_addr_reg_group1();
  void update_cacc_cacc_set_dataout_map_reg_group0();
  void update_cacc_cacc_set_dataout_map_reg_group1();
  void update_cacc_cacc_set_dataout_size_0_reg_group0();
  void update_cacc_cacc_set_dataout_size_0_reg_group1();
  void update_cacc_cacc_set_dataout_size_1_reg_group0();
  void update_cacc_cacc_set_dataout_size_1_reg_group1();
  void update_cacc_cacc_set_line_stride_reg_group0();
  void update_cacc_cacc_set_line_stride_reg_group1();
  void update_cacc_cacc_set_misc_cfg_reg_group0();
  void update_cacc_cacc_set_misc_cfg_reg_group1();
  void update_cacc_cacc_set_op_enable_reg_group0();
  void update_cacc_cacc_set_op_enable_reg_group1();
  void update_cacc_cacc_set_out_saturation_reg_group0();
  void update_cacc_cacc_set_out_saturation_reg_group1();
  void update_cacc_cacc_set_producer();
  void update_cacc_cacc_set_surf_stride_reg_group0();
  void update_cacc_cacc_set_surf_stride_reg_group1();
  bool valid_cacc();
  SC_HAS_PROCESS(cacc);
  cacc(sc_module_name name_) : sc_module(name_) {
    SC_METHOD(compute);
    sensitive << cacc_csb2cacc_vld_in << cacc_csb2cacc_write_in << cacc_csb2cacc_data_in << cacc_csb2cacc_addr_in;
  }
};
