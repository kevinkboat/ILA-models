#include <cmac.h>
bool cmac::decode_cmac_cmac_cache_weights() {
sc_biguint<2> local_var_1 = 2;
bool local_var_2 = (cmac_cmac_state == local_var_1);
auto local_var_4 = cmac_group0_cmac_d_misc_cfg.range(0, 0);
sc_biguint<1> local_var_5 = 1;
bool local_var_6 = (local_var_4 == local_var_5);
bool local_var_8 = !cmac_csc2cmac_reuse_weights;
bool local_var_9 = (local_var_6 | local_var_8);
bool local_var_10 = (local_var_2 & local_var_9);
auto& univ_var_6 = local_var_10;
return univ_var_6;
}
void cmac::update_cmac_cmac_cache_weights() {
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
  cmac_cached_wt_kernel_2[it.first] = it.second;
}
for (auto& it : local_var_9) {
  cmac_cached_wt_kernel_3[it.first] = it.second;
}
for (auto& it : local_var_10) {
  cmac_cached_wt_kernel_4[it.first] = it.second;
}
for (auto& it : local_var_11) {
  cmac_cached_wt_kernel_5[it.first] = it.second;
}
for (auto& it : local_var_12) {
  cmac_cached_wt_kernel_6[it.first] = it.second;
}
for (auto& it : local_var_13) {
  cmac_cached_wt_kernel_7[it.first] = it.second;
}
for (auto& it : local_var_14) {
  cmac_cached_wt_kernel_8[it.first] = it.second;
}
for (auto& it : local_var_15) {
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
instr_update_log << "    cmac_cached_wt_kernel_2 get updated" << std::endl;
instr_update_log << "    cmac_cached_wt_kernel_3 get updated" << std::endl;
instr_update_log << "    cmac_cached_wt_kernel_4 get updated" << std::endl;
instr_update_log << "    cmac_cached_wt_kernel_5 get updated" << std::endl;
instr_update_log << "    cmac_cached_wt_kernel_6 get updated" << std::endl;
instr_update_log << "    cmac_cached_wt_kernel_7 get updated" << std::endl;
instr_update_log << "    cmac_cached_wt_kernel_8 get updated" << std::endl;
instr_update_log << "    cmac_cached_wt_kernel_9 get updated" << std::endl;
instr_update_log << std::endl;
#endif
}
