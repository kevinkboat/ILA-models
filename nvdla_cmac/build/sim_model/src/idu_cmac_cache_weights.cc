#include <cmac.h>
bool cmac::decode_cmac_cmac_cache_weights() {
sc_biguint<2> local_var_1 = 2;
bool local_var_2 = (cmac_cmac_s_status0 == local_var_1);
sc_biguint<2> local_var_4 = 2;
bool local_var_5 = (cmac_cmac_s_status1 == local_var_4);
bool local_var_6 = (local_var_2 | local_var_5);
sc_biguint<1> local_var_8 = 0;
bool local_var_9 = (cmac_cmac_s_consumer == local_var_8);
auto local_var_11 = cmac_group0_cmac_d_misc_cfg.range(0, 0);
auto local_var_13 = cmac_group1_cmac_d_misc_cfg.range(0, 0);
auto local_var_14 = (local_var_9) ? local_var_11 : local_var_13;
sc_biguint<1> local_var_15 = 1;
bool local_var_16 = (local_var_14 == local_var_15);
bool local_var_18 = !cmac_csc2cmac_reuse_weights;
bool local_var_19 = (local_var_16 | local_var_18);
bool local_var_20 = (local_var_6 & local_var_19);
auto& univ_var_8 = local_var_20;
return univ_var_8;
}
void cmac::update_cmac_cmac_cache_weights() {
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_0;
store_9(local_var_0);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_1;
store_11(local_var_1);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_2;
store_13(local_var_2);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_3;
store_15(local_var_3);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_4;
store_17(local_var_4);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_5;
store_19(local_var_5);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_6;
store_21(local_var_6);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_7;
store_23(local_var_7);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_8;
store_25(local_var_8);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_9;
store_27(local_var_9);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_10;
store_29(local_var_10);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_11;
store_31(local_var_11);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_12;
store_33(local_var_12);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_13;
store_35(local_var_13);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_14;
store_37(local_var_14);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_15;
store_39(local_var_15);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_16;
store_41(local_var_16);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_17;
store_43(local_var_17);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_18;
store_45(local_var_18);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_19;
store_47(local_var_19);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_20;
store_49(local_var_20);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_21;
store_51(local_var_21);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_22;
store_53(local_var_22);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_23;
store_55(local_var_23);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_24;
store_57(local_var_24);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_25;
store_59(local_var_25);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_26;
store_61(local_var_26);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_27;
store_63(local_var_27);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_28;
store_65(local_var_28);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_29;
store_67(local_var_29);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_30;
store_69(local_var_30);
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_31;
store_71(local_var_31);
for (auto& it : local_var_0) {
  cmac_cached_wt_kernel_0[it.first] = it.second;
}
for (auto& it : local_var_1) {
  cmac_cached_wt_kernel_1[it.first] = it.second;
}
for (auto& it : local_var_2) {
  cmac_cached_wt_kernel_10[it.first] = it.second;
}
for (auto& it : local_var_3) {
  cmac_cached_wt_kernel_11[it.first] = it.second;
}
for (auto& it : local_var_4) {
  cmac_cached_wt_kernel_12[it.first] = it.second;
}
for (auto& it : local_var_5) {
  cmac_cached_wt_kernel_13[it.first] = it.second;
}
for (auto& it : local_var_6) {
  cmac_cached_wt_kernel_14[it.first] = it.second;
}
for (auto& it : local_var_7) {
  cmac_cached_wt_kernel_15[it.first] = it.second;
}
for (auto& it : local_var_8) {
  cmac_cached_wt_kernel_16[it.first] = it.second;
}
for (auto& it : local_var_9) {
  cmac_cached_wt_kernel_17[it.first] = it.second;
}
for (auto& it : local_var_10) {
  cmac_cached_wt_kernel_18[it.first] = it.second;
}
for (auto& it : local_var_11) {
  cmac_cached_wt_kernel_19[it.first] = it.second;
}
for (auto& it : local_var_12) {
  cmac_cached_wt_kernel_2[it.first] = it.second;
}
for (auto& it : local_var_13) {
  cmac_cached_wt_kernel_20[it.first] = it.second;
}
for (auto& it : local_var_14) {
  cmac_cached_wt_kernel_21[it.first] = it.second;
}
for (auto& it : local_var_15) {
  cmac_cached_wt_kernel_22[it.first] = it.second;
}
for (auto& it : local_var_16) {
  cmac_cached_wt_kernel_23[it.first] = it.second;
}
for (auto& it : local_var_17) {
  cmac_cached_wt_kernel_24[it.first] = it.second;
}
for (auto& it : local_var_18) {
  cmac_cached_wt_kernel_25[it.first] = it.second;
}
for (auto& it : local_var_19) {
  cmac_cached_wt_kernel_26[it.first] = it.second;
}
for (auto& it : local_var_20) {
  cmac_cached_wt_kernel_27[it.first] = it.second;
}
for (auto& it : local_var_21) {
  cmac_cached_wt_kernel_28[it.first] = it.second;
}
for (auto& it : local_var_22) {
  cmac_cached_wt_kernel_29[it.first] = it.second;
}
for (auto& it : local_var_23) {
  cmac_cached_wt_kernel_3[it.first] = it.second;
}
for (auto& it : local_var_24) {
  cmac_cached_wt_kernel_30[it.first] = it.second;
}
for (auto& it : local_var_25) {
  cmac_cached_wt_kernel_31[it.first] = it.second;
}
for (auto& it : local_var_26) {
  cmac_cached_wt_kernel_4[it.first] = it.second;
}
for (auto& it : local_var_27) {
  cmac_cached_wt_kernel_5[it.first] = it.second;
}
for (auto& it : local_var_28) {
  cmac_cached_wt_kernel_6[it.first] = it.second;
}
for (auto& it : local_var_29) {
  cmac_cached_wt_kernel_7[it.first] = it.second;
}
for (auto& it : local_var_30) {
  cmac_cached_wt_kernel_8[it.first] = it.second;
}
for (auto& it : local_var_31) {
  cmac_cached_wt_kernel_9[it.first] = it.second;
}
#ifdef ILATOR_VERBOSE
instr_update_log << "No." << std::dec << GetInstrCntr() << '\t' << "cmac_cache_weights state updates:" << std::endl;
instr_update_log << "    cmac_cached_wt_kernel_0 get updated" << std::endl;
instr_update_log << "    cmac_cached_wt_kernel_1 get updated" << std::endl;
instr_update_log << "    cmac_cached_wt_kernel_10 get updated" << std::endl;
instr_update_log << "    cmac_cached_wt_kernel_11 get updated" << std::endl;
instr_update_log << "    cmac_cached_wt_kernel_12 get updated" << std::endl;
instr_update_log << "    cmac_cached_wt_kernel_13 get updated" << std::endl;
instr_update_log << "    cmac_cached_wt_kernel_14 get updated" << std::endl;
instr_update_log << "    cmac_cached_wt_kernel_15 get updated" << std::endl;
instr_update_log << "    cmac_cached_wt_kernel_16 get updated" << std::endl;
instr_update_log << "    cmac_cached_wt_kernel_17 get updated" << std::endl;
instr_update_log << "    cmac_cached_wt_kernel_18 get updated" << std::endl;
instr_update_log << "    cmac_cached_wt_kernel_19 get updated" << std::endl;
instr_update_log << "    cmac_cached_wt_kernel_2 get updated" << std::endl;
instr_update_log << "    cmac_cached_wt_kernel_20 get updated" << std::endl;
instr_update_log << "    cmac_cached_wt_kernel_21 get updated" << std::endl;
instr_update_log << "    cmac_cached_wt_kernel_22 get updated" << std::endl;
instr_update_log << "    cmac_cached_wt_kernel_23 get updated" << std::endl;
instr_update_log << "    cmac_cached_wt_kernel_24 get updated" << std::endl;
instr_update_log << "    cmac_cached_wt_kernel_25 get updated" << std::endl;
instr_update_log << "    cmac_cached_wt_kernel_26 get updated" << std::endl;
instr_update_log << "    cmac_cached_wt_kernel_27 get updated" << std::endl;
instr_update_log << "    cmac_cached_wt_kernel_28 get updated" << std::endl;
instr_update_log << "    cmac_cached_wt_kernel_29 get updated" << std::endl;
instr_update_log << "    cmac_cached_wt_kernel_3 get updated" << std::endl;
instr_update_log << "    cmac_cached_wt_kernel_30 get updated" << std::endl;
instr_update_log << "    cmac_cached_wt_kernel_31 get updated" << std::endl;
instr_update_log << "    cmac_cached_wt_kernel_4 get updated" << std::endl;
instr_update_log << "    cmac_cached_wt_kernel_5 get updated" << std::endl;
instr_update_log << "    cmac_cached_wt_kernel_6 get updated" << std::endl;
instr_update_log << "    cmac_cached_wt_kernel_7 get updated" << std::endl;
instr_update_log << "    cmac_cached_wt_kernel_8 get updated" << std::endl;
instr_update_log << "    cmac_cached_wt_kernel_9 get updated" << std::endl;
instr_update_log << std::endl;
#endif
}
