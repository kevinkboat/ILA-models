#include <cmac.h>
bool cmac::decode_cmac_cmac_start_from_idle() {
sc_biguint<1> local_var_1 = 0;
bool local_var_2 = (cmac_cmac_s_consumer == local_var_1);
sc_biguint<1> local_var_4 = 0;
bool local_var_5 = (cmac_group0_cmac_d_op_en == local_var_4);
bool local_var_6 = !local_var_5;
bool local_var_7 = (local_var_2 & local_var_6);
sc_biguint<2> local_var_9 = 0;
bool local_var_10 = (cmac_cmac_s_status0 == local_var_9);
bool local_var_11 = (local_var_7 & local_var_10);
sc_biguint<1> local_var_12 = 1;
bool local_var_13 = (cmac_cmac_s_consumer == local_var_12);
sc_biguint<1> local_var_15 = 0;
bool local_var_16 = (cmac_group1_cmac_d_op_en == local_var_15);
bool local_var_17 = !local_var_16;
bool local_var_18 = (local_var_13 & local_var_17);
sc_biguint<2> local_var_20 = 0;
bool local_var_21 = (cmac_cmac_s_status1 == local_var_20);
bool local_var_22 = (local_var_18 & local_var_21);
bool local_var_23 = (local_var_11 ^ local_var_22);
bool local_var_25 = (local_var_23 & cmac_csc2cmac_vld);
auto& univ_var_6 = local_var_25;
return univ_var_6;
}
void cmac::update_cmac_cmac_start_from_idle() {
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_0;
store_7(local_var_0);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_1;
store_9(local_var_1);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_2;
store_11(local_var_2);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_3;
store_13(local_var_3);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_4;
store_15(local_var_4);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_5;
store_17(local_var_5);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_6;
store_19(local_var_6);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_7;
store_21(local_var_7);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_8;
store_23(local_var_8);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_9;
store_25(local_var_9);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_10;
store_27(local_var_10);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_11;
store_29(local_var_11);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_12;
store_31(local_var_12);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_13;
store_33(local_var_13);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_14;
store_35(local_var_14);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_15;
store_37(local_var_15);
sc_biguint<1> local_var_17 = 0;
bool local_var_18 = (cmac_cmac_s_consumer == local_var_17);
sc_biguint<1> local_var_20 = 0;
bool local_var_21 = (cmac_group0_cmac_d_op_en == local_var_20);
bool local_var_22 = !local_var_21;
bool local_var_23 = (local_var_18 & local_var_22);
sc_biguint<2> local_var_25 = 0;
bool local_var_26 = (cmac_cmac_s_status0 == local_var_25);
bool local_var_27 = (local_var_23 & local_var_26);
sc_biguint<2> local_var_28 = 2;
auto local_var_29 = (local_var_27) ? local_var_28 : cmac_cmac_s_status0;
auto local_var_29_nxt_holder = local_var_29;
sc_biguint<1> local_var_30 = 1;
bool local_var_31 = (cmac_cmac_s_consumer == local_var_30);
sc_biguint<1> local_var_33 = 0;
bool local_var_34 = (cmac_group1_cmac_d_op_en == local_var_33);
bool local_var_35 = !local_var_34;
bool local_var_36 = (local_var_31 & local_var_35);
sc_biguint<2> local_var_38 = 0;
bool local_var_39 = (cmac_cmac_s_status1 == local_var_38);
bool local_var_40 = (local_var_36 & local_var_39);
sc_biguint<2> local_var_41 = 2;
auto local_var_42 = (local_var_40) ? local_var_41 : cmac_cmac_s_status1;
auto local_var_42_nxt_holder = local_var_42;
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
cmac_cmac_s_status0 = local_var_29_nxt_holder;
cmac_cmac_s_status1 = local_var_42_nxt_holder;
#ifdef ILATOR_VERBOSE
instr_update_log << "No." << std::dec << GetInstrCntr() << '\t' << "cmac_start_from_idle state updates:" << std::endl;
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
instr_update_log << "    cmac_cmac_s_status0 => " << std::hex << "0x" << cmac_cmac_s_status0 << std::endl; 
instr_update_log << "    cmac_cmac_s_status1 => " << std::hex << "0x" << cmac_cmac_s_status1 << std::endl; 
instr_update_log << std::endl;
#endif
}
