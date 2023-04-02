#include <cacc.h>
bool cacc::decode_cacc_cacc_accumulate() {
auto local_var_1 = cacc_cacc_s_status.range(1, 0);
sc_biguint<2> local_var_2 = 2;
bool local_var_3 = (local_var_1 == local_var_2);
auto local_var_4 = cacc_cacc_s_status.range(17, 16);
sc_biguint<2> local_var_5 = 2;
bool local_var_6 = (local_var_4 == local_var_5);
bool local_var_7 = (local_var_3 ^ local_var_6);
sc_biguint<2> local_var_9 = 1;
bool local_var_10 = (cacc_cmac2cacc_status == local_var_9);
bool local_var_11 = (local_var_7 & local_var_10);
auto& univ_var_56 = local_var_11;
return univ_var_56;
}
void cacc::update_cacc_cacc_accumulate() {
std::unordered_map<int, sc_biguint<1088>, MemAddrHashFunc> local_var_0;
store_57(local_var_0);
std::unordered_map<int, sc_biguint<1088>, MemAddrHashFunc> local_var_1;
store_59(local_var_1);
std::unordered_map<int, sc_biguint<1088>, MemAddrHashFunc> local_var_2;
store_61(local_var_2);
std::unordered_map<int, sc_biguint<1088>, MemAddrHashFunc> local_var_3;
store_63(local_var_3);
std::unordered_map<int, sc_biguint<1088>, MemAddrHashFunc> local_var_4;
store_65(local_var_4);
std::unordered_map<int, sc_biguint<1088>, MemAddrHashFunc> local_var_5;
store_67(local_var_5);
std::unordered_map<int, sc_biguint<1088>, MemAddrHashFunc> local_var_6;
store_69(local_var_6);
std::unordered_map<int, sc_biguint<1088>, MemAddrHashFunc> local_var_7;
store_71(local_var_7);
std::unordered_map<int, sc_biguint<1088>, MemAddrHashFunc> local_var_8;
store_73(local_var_8);
std::unordered_map<int, sc_biguint<1088>, MemAddrHashFunc> local_var_9;
store_75(local_var_9);
std::unordered_map<int, sc_biguint<1088>, MemAddrHashFunc> local_var_10;
store_77(local_var_10);
std::unordered_map<int, sc_biguint<1088>, MemAddrHashFunc> local_var_11;
store_79(local_var_11);
std::unordered_map<int, sc_biguint<1088>, MemAddrHashFunc> local_var_12;
store_81(local_var_12);
std::unordered_map<int, sc_biguint<1088>, MemAddrHashFunc> local_var_13;
store_83(local_var_13);
std::unordered_map<int, sc_biguint<1088>, MemAddrHashFunc> local_var_14;
store_85(local_var_14);
std::unordered_map<int, sc_biguint<1088>, MemAddrHashFunc> local_var_15;
store_87(local_var_15);
auto local_var_17 = cacc_cacc_s_pointer.range(16, 16);
sc_biguint<1> local_var_18 = 0;
bool local_var_19 = (local_var_17 == local_var_18);
sc_biguint<32> local_var_21 = 3;
sc_biguint<32> local_var_22 = ~local_var_21;
sc_biguint<32> local_var_23 = (cacc_cacc_s_status & local_var_22);
sc_biguint<2> local_var_24 = 1;
auto local_var_25 = (local_var_24[1] == 1) ? (~local_var_24) : local_var_24;
local_var_25 = (local_var_24[1] == 1) ? (~local_var_25) : local_var_25;
sc_biguint<32> local_var_26 = 0;
sc_biguint<32> local_var_27 = (local_var_25 << local_var_26);
sc_biguint<32> local_var_28 = (local_var_27 & local_var_21);
sc_biguint<32> local_var_29 = (local_var_23 | local_var_28);
sc_biguint<32> local_var_30 = 196608;
sc_biguint<32> local_var_31 = ~local_var_30;
sc_biguint<32> local_var_32 = (cacc_cacc_s_status & local_var_31);
sc_biguint<2> local_var_33 = 1;
auto local_var_34 = (local_var_33[1] == 1) ? (~local_var_33) : local_var_33;
local_var_34 = (local_var_33[1] == 1) ? (~local_var_34) : local_var_34;
sc_biguint<32> local_var_35 = 16;
sc_biguint<32> local_var_36 = (local_var_34 << local_var_35);
sc_biguint<32> local_var_37 = (local_var_36 & local_var_30);
sc_biguint<32> local_var_38 = (local_var_32 | local_var_37);
auto local_var_39 = (local_var_19) ? local_var_29 : local_var_38;
auto local_var_39_nxt_holder = local_var_39;
for (auto& it : local_var_0) {
  cacc_assembly_group_mac_0[it.first] = it.second;
}
for (auto& it : local_var_1) {
  cacc_assembly_group_mac_1[it.first] = it.second;
}
for (auto& it : local_var_2) {
  cacc_assembly_group_mac_10[it.first] = it.second;
}
for (auto& it : local_var_3) {
  cacc_assembly_group_mac_11[it.first] = it.second;
}
for (auto& it : local_var_4) {
  cacc_assembly_group_mac_12[it.first] = it.second;
}
for (auto& it : local_var_5) {
  cacc_assembly_group_mac_13[it.first] = it.second;
}
for (auto& it : local_var_6) {
  cacc_assembly_group_mac_14[it.first] = it.second;
}
for (auto& it : local_var_7) {
  cacc_assembly_group_mac_15[it.first] = it.second;
}
for (auto& it : local_var_8) {
  cacc_assembly_group_mac_2[it.first] = it.second;
}
for (auto& it : local_var_9) {
  cacc_assembly_group_mac_3[it.first] = it.second;
}
for (auto& it : local_var_10) {
  cacc_assembly_group_mac_4[it.first] = it.second;
}
for (auto& it : local_var_11) {
  cacc_assembly_group_mac_5[it.first] = it.second;
}
for (auto& it : local_var_12) {
  cacc_assembly_group_mac_6[it.first] = it.second;
}
for (auto& it : local_var_13) {
  cacc_assembly_group_mac_7[it.first] = it.second;
}
for (auto& it : local_var_14) {
  cacc_assembly_group_mac_8[it.first] = it.second;
}
for (auto& it : local_var_15) {
  cacc_assembly_group_mac_9[it.first] = it.second;
}
cacc_cacc_s_status = local_var_39_nxt_holder;
#ifdef ILATOR_VERBOSE
instr_update_log << "No." << std::dec << GetInstrCntr() << '\t' << "cacc_accumulate state updates:" << std::endl;
instr_update_log << "    cacc_assembly_group_mac_0 get updated" << std::endl;
instr_update_log << "    cacc_assembly_group_mac_1 get updated" << std::endl;
instr_update_log << "    cacc_assembly_group_mac_10 get updated" << std::endl;
instr_update_log << "    cacc_assembly_group_mac_11 get updated" << std::endl;
instr_update_log << "    cacc_assembly_group_mac_12 get updated" << std::endl;
instr_update_log << "    cacc_assembly_group_mac_13 get updated" << std::endl;
instr_update_log << "    cacc_assembly_group_mac_14 get updated" << std::endl;
instr_update_log << "    cacc_assembly_group_mac_15 get updated" << std::endl;
instr_update_log << "    cacc_assembly_group_mac_2 get updated" << std::endl;
instr_update_log << "    cacc_assembly_group_mac_3 get updated" << std::endl;
instr_update_log << "    cacc_assembly_group_mac_4 get updated" << std::endl;
instr_update_log << "    cacc_assembly_group_mac_5 get updated" << std::endl;
instr_update_log << "    cacc_assembly_group_mac_6 get updated" << std::endl;
instr_update_log << "    cacc_assembly_group_mac_7 get updated" << std::endl;
instr_update_log << "    cacc_assembly_group_mac_8 get updated" << std::endl;
instr_update_log << "    cacc_assembly_group_mac_9 get updated" << std::endl;
instr_update_log << "    cacc_cacc_s_status => " << std::hex << "0x" << cacc_cacc_s_status << std::endl; 
instr_update_log << std::endl;
#endif
}
