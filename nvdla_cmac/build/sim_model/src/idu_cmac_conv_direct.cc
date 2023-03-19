#include <cmac.h>
bool cmac::decode_cmac_cmac_conv_direct() {
sc_biguint<2> local_var_1 = 2;
bool local_var_2 = (cmac_cmac_s_status0 == local_var_1);
sc_biguint<2> local_var_4 = 2;
bool local_var_5 = (cmac_cmac_s_status1 == local_var_4);
bool local_var_6 = (local_var_2 | local_var_5);
bool local_var_7 = false;
bool local_var_8 = !local_var_7;
bool local_var_9 = (local_var_6 & local_var_8);
sc_biguint<1> local_var_11 = 0;
bool local_var_12 = (cmac_cmac_s_consumer == local_var_11);
auto local_var_14 = cmac_group0_cmac_d_misc_cfg.range(0, 0);
auto local_var_16 = cmac_group1_cmac_d_misc_cfg.range(0, 0);
auto local_var_17 = (local_var_12) ? local_var_14 : local_var_16;
sc_biguint<1> local_var_18 = 0;
bool local_var_19 = (local_var_17 == local_var_18);
bool local_var_20 = (local_var_9 & local_var_19);
auto& univ_var_73 = local_var_20;
return univ_var_73;
}
void cmac::update_cmac_cmac_conv_direct() {
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_0;
store_74(local_var_0);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_1;
store_76(local_var_1);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_2;
store_78(local_var_2);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_3;
store_80(local_var_3);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_4;
store_82(local_var_4);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_5;
store_84(local_var_5);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_6;
store_86(local_var_6);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_7;
store_88(local_var_7);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_8;
store_90(local_var_8);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_9;
store_92(local_var_9);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_10;
store_94(local_var_10);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_11;
store_96(local_var_11);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_12;
store_98(local_var_12);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_13;
store_100(local_var_13);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_14;
store_102(local_var_14);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_15;
store_104(local_var_15);
bool local_var_17 = true;
bool local_var_18 = (cmac_csc2cmac_sending_last_batch == local_var_17);
sc_biguint<1> local_var_20 = ~cmac_cmac_s_consumer;
auto local_var_21 = (local_var_18) ? local_var_20 : cmac_cmac_s_consumer;
auto local_var_21_nxt_holder = local_var_21;
sc_biguint<1> local_var_22 = 0;
bool local_var_23 = (cmac_cmac_s_consumer == local_var_22);
sc_biguint<2> local_var_24 = 0;
sc_biguint<2> local_var_25 = 1;
auto local_var_26 = (local_var_18) ? local_var_24 : local_var_25;
auto local_var_28 = (local_var_23) ? local_var_26 : cmac_cmac_s_status0;
auto local_var_28_nxt_holder = local_var_28;
bool local_var_29 = !local_var_23;
auto local_var_31 = (local_var_29) ? local_var_26 : cmac_cmac_s_status1;
auto local_var_31_nxt_holder = local_var_31;
sc_biguint<1> local_var_32 = 0;
sc_biguint<1> local_var_33 = 1;
auto local_var_34 = (local_var_18) ? local_var_32 : local_var_33;
auto local_var_36 = (local_var_23) ? local_var_34 : cmac_group0_cmac_d_op_en;
auto local_var_36_nxt_holder = local_var_36;
bool local_var_37 = !local_var_23;
auto local_var_39 = (local_var_37) ? local_var_34 : cmac_group1_cmac_d_op_en;
auto local_var_39_nxt_holder = local_var_39;
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
cmac_cmac_s_consumer = local_var_21_nxt_holder;
cmac_cmac_s_status0 = local_var_28_nxt_holder;
cmac_cmac_s_status1 = local_var_31_nxt_holder;
cmac_group0_cmac_d_op_en = local_var_36_nxt_holder;
cmac_group1_cmac_d_op_en = local_var_39_nxt_holder;
#ifdef ILATOR_VERBOSE
instr_update_log << "No." << std::dec << GetInstrCntr() << '\t' << "cmac_conv_direct state updates:" << std::endl;
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
instr_update_log << "    cmac_cmac_s_consumer => " << std::hex << "0x" << cmac_cmac_s_consumer << std::endl; 
instr_update_log << "    cmac_cmac_s_status0 => " << std::hex << "0x" << cmac_cmac_s_status0 << std::endl; 
instr_update_log << "    cmac_cmac_s_status1 => " << std::hex << "0x" << cmac_cmac_s_status1 << std::endl; 
instr_update_log << "    cmac_group0_cmac_d_op_en => " << std::hex << "0x" << cmac_group0_cmac_d_op_en << std::endl; 
instr_update_log << "    cmac_group1_cmac_d_op_en => " << std::hex << "0x" << cmac_group1_cmac_d_op_en << std::endl; 
instr_update_log << std::endl;
#endif
}
