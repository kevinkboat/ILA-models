#include <cmac.h>
bool cmac::decode_cmac_cmac_compute_dot_product() {
sc_biguint<2> local_var_1 = 2;
bool local_var_2 = (cmac_cmac_state == local_var_1);
bool local_var_3 = false;
bool local_var_4 = !local_var_3;
bool local_var_5 = (local_var_2 & local_var_4);
auto& univ_var_39 = local_var_5;
return univ_var_39;
}
void cmac::update_cmac_cmac_compute_dot_product() {
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_0;
store_40(local_var_0);
bool local_var_2 = false;
bool local_var_3 = (cmac_csc2cmac_sending_last_batch == local_var_2);
sc_biguint<2> local_var_4 = 1;
sc_biguint<2> local_var_5 = 0;
auto local_var_6 = (local_var_3) ? local_var_4 : local_var_5;
auto local_var_6_nxt_holder = local_var_6;
bool local_var_7 = false;
bool local_var_8 = (cmac_csc2cmac_sending_last_batch == local_var_7);
sc_biguint<1> local_var_9 = 1;
sc_biguint<1> local_var_10 = 0;
auto local_var_11 = (local_var_8) ? local_var_9 : local_var_10;
auto local_var_11_nxt_holder = local_var_11;
for (auto& it : local_var_0) {
  cmac_cmac2cacc_partial_sums[it.first] = it.second;
}
cmac_cmac_state = local_var_6_nxt_holder;
cmac_group0_cmac_d_op_en = local_var_11_nxt_holder;
#ifdef ILATOR_VERBOSE
instr_update_log << "No." << std::dec << GetInstrCntr() << '\t' << "cmac_compute_dot_product state updates:" << std::endl;
instr_update_log << "    cmac_cmac2cacc_partial_sums get updated" << std::endl;
instr_update_log << "    cmac_cmac_state => " << std::hex << "0x" << cmac_cmac_state << std::endl; 
instr_update_log << "    cmac_group0_cmac_d_op_en => " << std::hex << "0x" << cmac_group0_cmac_d_op_en << std::endl; 
instr_update_log << std::endl;
#endif
}
