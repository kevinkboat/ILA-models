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
bool local_var_1 = false;
bool local_var_2 = (cmac_csc2cmac_sending_last_batch == local_var_1);
sc_biguint<2> local_var_3 = 1;
sc_biguint<2> local_var_4 = 0;
auto local_var_5 = (local_var_2) ? local_var_3 : local_var_4;
auto local_var_5_nxt_holder = local_var_5;
bool local_var_6 = false;
bool local_var_7 = (cmac_csc2cmac_sending_last_batch == local_var_6);
sc_biguint<1> local_var_8 = 1;
sc_biguint<1> local_var_9 = 0;
auto local_var_10 = (local_var_7) ? local_var_8 : local_var_9;
auto local_var_10_nxt_holder = local_var_10;
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_11;
store_40(local_var_11);
cmac_cmac_state = local_var_5_nxt_holder;
cmac_group0_cmac_d_op_en = local_var_10_nxt_holder;
for (auto& it : local_var_11) {
  cmac_tmp_mem[it.first] = it.second;
}
#ifdef ILATOR_VERBOSE
instr_update_log << "No." << std::dec << GetInstrCntr() << '\t' << "cmac_compute_dot_product state updates:" << std::endl;
instr_update_log << "    cmac_cmac_state => " << std::hex << "0x" << cmac_cmac_state << std::endl; 
instr_update_log << "    cmac_group0_cmac_d_op_en => " << std::hex << "0x" << cmac_group0_cmac_d_op_en << std::endl; 
instr_update_log << "    cmac_tmp_mem get updated" << std::endl;
instr_update_log << std::endl;
#endif
}
