#include <cmac.h>
bool cmac::decode_cmac_cmac_compute_dot_product_winograd() {
sc_biguint<2> local_var_1 = 2;
bool local_var_2 = (cmac_cmac_state == local_var_1);
bool local_var_3 = false;
bool local_var_4 = !local_var_3;
bool local_var_5 = (local_var_2 & local_var_4);
auto& univ_var_40 = local_var_5;
return univ_var_40;
}
void cmac::update_cmac_cmac_compute_dot_product_winograd() {
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_0;
store_41(local_var_0);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_1;
store_43(local_var_1);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_2;
store_45(local_var_2);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_3;
store_47(local_var_3);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_4;
store_49(local_var_4);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_5;
store_51(local_var_5);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_6;
store_53(local_var_6);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_7;
store_55(local_var_7);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_8;
store_57(local_var_8);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_9;
store_59(local_var_9);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_10;
store_61(local_var_10);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_11;
store_63(local_var_11);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_12;
store_65(local_var_12);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_13;
store_67(local_var_13);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_14;
store_69(local_var_14);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_15;
store_71(local_var_15);
bool local_var_17 = false;
bool local_var_18 = (cmac_csc2cmac_sending_last_batch == local_var_17);
sc_biguint<2> local_var_19 = 1;
sc_biguint<2> local_var_20 = 0;
auto local_var_21 = (local_var_18) ? local_var_19 : local_var_20;
auto local_var_21_nxt_holder = local_var_21;
bool local_var_22 = false;
bool local_var_23 = (cmac_csc2cmac_sending_last_batch == local_var_22);
sc_biguint<1> local_var_24 = 1;
sc_biguint<1> local_var_25 = 0;
auto local_var_26 = (local_var_23) ? local_var_24 : local_var_25;
auto local_var_26_nxt_holder = local_var_26;
for (auto& it : local_var_0) {
  cmac_cmac2cacc_partial_sum_mac_0[it.first] = it.second;
}
for (auto& it : local_var_1) {
  cmac_cmac2cacc_partial_sum_mac_1[it.first] = it.second;
}
for (auto& it : local_var_2) {
  cmac_cmac2cacc_partial_sum_mac_10[it.first] = it.second;
}
for (auto& it : local_var_3) {
  cmac_cmac2cacc_partial_sum_mac_11[it.first] = it.second;
}
for (auto& it : local_var_4) {
  cmac_cmac2cacc_partial_sum_mac_12[it.first] = it.second;
}
for (auto& it : local_var_5) {
  cmac_cmac2cacc_partial_sum_mac_13[it.first] = it.second;
}
for (auto& it : local_var_6) {
  cmac_cmac2cacc_partial_sum_mac_14[it.first] = it.second;
}
for (auto& it : local_var_7) {
  cmac_cmac2cacc_partial_sum_mac_15[it.first] = it.second;
}
for (auto& it : local_var_8) {
  cmac_cmac2cacc_partial_sum_mac_2[it.first] = it.second;
}
for (auto& it : local_var_9) {
  cmac_cmac2cacc_partial_sum_mac_3[it.first] = it.second;
}
for (auto& it : local_var_10) {
  cmac_cmac2cacc_partial_sum_mac_4[it.first] = it.second;
}
for (auto& it : local_var_11) {
  cmac_cmac2cacc_partial_sum_mac_5[it.first] = it.second;
}
for (auto& it : local_var_12) {
  cmac_cmac2cacc_partial_sum_mac_6[it.first] = it.second;
}
for (auto& it : local_var_13) {
  cmac_cmac2cacc_partial_sum_mac_7[it.first] = it.second;
}
for (auto& it : local_var_14) {
  cmac_cmac2cacc_partial_sum_mac_8[it.first] = it.second;
}
for (auto& it : local_var_15) {
  cmac_cmac2cacc_partial_sum_mac_9[it.first] = it.second;
}
cmac_cmac_state = local_var_21_nxt_holder;
cmac_group0_cmac_d_op_en = local_var_26_nxt_holder;
#ifdef ILATOR_VERBOSE
instr_update_log << "No." << std::dec << GetInstrCntr() << '\t' << "cmac_compute_dot_product_winograd state updates:" << std::endl;
instr_update_log << "    cmac_cmac2cacc_partial_sum_mac_0 get updated" << std::endl;
instr_update_log << "    cmac_cmac2cacc_partial_sum_mac_1 get updated" << std::endl;
instr_update_log << "    cmac_cmac2cacc_partial_sum_mac_10 get updated" << std::endl;
instr_update_log << "    cmac_cmac2cacc_partial_sum_mac_11 get updated" << std::endl;
instr_update_log << "    cmac_cmac2cacc_partial_sum_mac_12 get updated" << std::endl;
instr_update_log << "    cmac_cmac2cacc_partial_sum_mac_13 get updated" << std::endl;
instr_update_log << "    cmac_cmac2cacc_partial_sum_mac_14 get updated" << std::endl;
instr_update_log << "    cmac_cmac2cacc_partial_sum_mac_15 get updated" << std::endl;
instr_update_log << "    cmac_cmac2cacc_partial_sum_mac_2 get updated" << std::endl;
instr_update_log << "    cmac_cmac2cacc_partial_sum_mac_3 get updated" << std::endl;
instr_update_log << "    cmac_cmac2cacc_partial_sum_mac_4 get updated" << std::endl;
instr_update_log << "    cmac_cmac2cacc_partial_sum_mac_5 get updated" << std::endl;
instr_update_log << "    cmac_cmac2cacc_partial_sum_mac_6 get updated" << std::endl;
instr_update_log << "    cmac_cmac2cacc_partial_sum_mac_7 get updated" << std::endl;
instr_update_log << "    cmac_cmac2cacc_partial_sum_mac_8 get updated" << std::endl;
instr_update_log << "    cmac_cmac2cacc_partial_sum_mac_9 get updated" << std::endl;
instr_update_log << "    cmac_cmac_state => " << std::hex << "0x" << cmac_cmac_state << std::endl; 
instr_update_log << "    cmac_group0_cmac_d_op_en => " << std::hex << "0x" << cmac_group0_cmac_d_op_en << std::endl; 
instr_update_log << std::endl;
#endif
}
