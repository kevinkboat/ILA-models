#include <cacc.h>
bool cacc::decode_cacc_cacc_set_out_saturation_reg_group0() {
auto local_var_1 = cacc_csb2cacc_addr.range(16, 0);
sc_biguint<17> local_var_2 = 36912;
bool local_var_3 = (local_var_1 == local_var_2);
bool local_var_6 = (cacc_cacc2csb_rdy & cacc_csb2cacc_vld);
bool local_var_7 = (local_var_3 & local_var_6);
bool local_var_9 = (local_var_7 & cacc_csb2cacc_write);
auto local_var_11 = cacc_cacc_s_pointer.range(0, 0);
sc_biguint<1> local_var_12 = 0;
bool local_var_13 = (local_var_11 == local_var_12);
bool local_var_14 = (local_var_9 & local_var_13);
auto local_var_16 = cacc_group0_cacc_d_op_enable.range(0, 0);
sc_biguint<1> local_var_17 = 0;
bool local_var_18 = (local_var_16 == local_var_17);
bool local_var_19 = (local_var_14 & local_var_18);
auto& univ_var_12 = local_var_19;
return univ_var_12;
}
void cacc::update_cacc_cacc_set_out_saturation_reg_group0() {
auto cacc_csb2cacc_data_nxt_holder = cacc_csb2cacc_data;
cacc_group0_cacc_d_out_saturation = cacc_csb2cacc_data_nxt_holder;
#ifdef ILATOR_VERBOSE
instr_update_log << "No." << std::dec << GetInstrCntr() << '\t' << "cacc_set_out_saturation_reg_group0 state updates:" << std::endl;
instr_update_log << "    cacc_group0_cacc_d_out_saturation => " << std::hex << "0x" << cacc_group0_cacc_d_out_saturation << std::endl; 
instr_update_log << std::endl;
#endif
}
