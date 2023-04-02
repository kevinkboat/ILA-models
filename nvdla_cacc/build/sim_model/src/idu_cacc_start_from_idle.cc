#include <cacc.h>
bool cacc::decode_cacc_cacc_start_from_idle() {
auto local_var_1 = cacc_cacc_s_pointer.range(16, 16);
sc_biguint<1> local_var_2 = 0;
bool local_var_3 = (local_var_1 == local_var_2);
auto local_var_5 = cacc_group0_cacc_d_op_enable.range(0, 0);
sc_biguint<1> local_var_6 = 0;
bool local_var_7 = (local_var_5 == local_var_6);
bool local_var_8 = !local_var_7;
bool local_var_9 = (local_var_3 & local_var_8);
auto local_var_11 = cacc_cacc_s_status.range(1, 0);
sc_biguint<2> local_var_12 = 0;
bool local_var_13 = (local_var_11 == local_var_12);
bool local_var_14 = (local_var_9 & local_var_13);
sc_biguint<1> local_var_15 = 1;
bool local_var_16 = (local_var_1 == local_var_15);
auto local_var_18 = cacc_group1_cacc_d_op_enable.range(0, 0);
sc_biguint<1> local_var_19 = 0;
bool local_var_20 = (local_var_18 == local_var_19);
bool local_var_21 = !local_var_20;
bool local_var_22 = (local_var_16 & local_var_21);
auto local_var_23 = cacc_cacc_s_status.range(17, 16);
sc_biguint<2> local_var_24 = 0;
bool local_var_25 = (local_var_23 == local_var_24);
bool local_var_26 = (local_var_22 & local_var_25);
bool local_var_27 = (local_var_14 ^ local_var_26);
auto& univ_var_22 = local_var_27;
return univ_var_22;
}
void cacc::update_cacc_cacc_start_from_idle() {
std::unordered_map<int, sc_biguint<48>, MemAddrHashFunc> local_var_0;
store_23(local_var_0);
std::unordered_map<int, sc_biguint<48>, MemAddrHashFunc> local_var_1;
store_25(local_var_1);
std::unordered_map<int, sc_biguint<48>, MemAddrHashFunc> local_var_2;
store_27(local_var_2);
std::unordered_map<int, sc_biguint<48>, MemAddrHashFunc> local_var_3;
store_29(local_var_3);
std::unordered_map<int, sc_biguint<48>, MemAddrHashFunc> local_var_4;
store_31(local_var_4);
std::unordered_map<int, sc_biguint<48>, MemAddrHashFunc> local_var_5;
store_33(local_var_5);
std::unordered_map<int, sc_biguint<48>, MemAddrHashFunc> local_var_6;
store_35(local_var_6);
std::unordered_map<int, sc_biguint<48>, MemAddrHashFunc> local_var_7;
store_37(local_var_7);
std::unordered_map<int, sc_biguint<48>, MemAddrHashFunc> local_var_8;
store_39(local_var_8);
std::unordered_map<int, sc_biguint<48>, MemAddrHashFunc> local_var_9;
store_41(local_var_9);
std::unordered_map<int, sc_biguint<48>, MemAddrHashFunc> local_var_10;
store_43(local_var_10);
std::unordered_map<int, sc_biguint<48>, MemAddrHashFunc> local_var_11;
store_45(local_var_11);
std::unordered_map<int, sc_biguint<48>, MemAddrHashFunc> local_var_12;
store_47(local_var_12);
std::unordered_map<int, sc_biguint<48>, MemAddrHashFunc> local_var_13;
store_49(local_var_13);
std::unordered_map<int, sc_biguint<48>, MemAddrHashFunc> local_var_14;
store_51(local_var_14);
std::unordered_map<int, sc_biguint<48>, MemAddrHashFunc> local_var_15;
store_53(local_var_15);
std::unordered_map<int, sc_biguint<48>, MemAddrHashFunc> local_var_16;
store_55(local_var_16);
std::unordered_map<int, sc_biguint<48>, MemAddrHashFunc> local_var_17;
store_57(local_var_17);
std::unordered_map<int, sc_biguint<48>, MemAddrHashFunc> local_var_18;
store_59(local_var_18);
std::unordered_map<int, sc_biguint<48>, MemAddrHashFunc> local_var_19;
store_61(local_var_19);
std::unordered_map<int, sc_biguint<48>, MemAddrHashFunc> local_var_20;
store_63(local_var_20);
std::unordered_map<int, sc_biguint<48>, MemAddrHashFunc> local_var_21;
store_65(local_var_21);
std::unordered_map<int, sc_biguint<48>, MemAddrHashFunc> local_var_22;
store_67(local_var_22);
std::unordered_map<int, sc_biguint<48>, MemAddrHashFunc> local_var_23;
store_69(local_var_23);
std::unordered_map<int, sc_biguint<48>, MemAddrHashFunc> local_var_24;
store_71(local_var_24);
std::unordered_map<int, sc_biguint<48>, MemAddrHashFunc> local_var_25;
store_73(local_var_25);
std::unordered_map<int, sc_biguint<48>, MemAddrHashFunc> local_var_26;
store_75(local_var_26);
std::unordered_map<int, sc_biguint<48>, MemAddrHashFunc> local_var_27;
store_77(local_var_27);
std::unordered_map<int, sc_biguint<48>, MemAddrHashFunc> local_var_28;
store_79(local_var_28);
std::unordered_map<int, sc_biguint<48>, MemAddrHashFunc> local_var_29;
store_81(local_var_29);
std::unordered_map<int, sc_biguint<48>, MemAddrHashFunc> local_var_30;
store_83(local_var_30);
std::unordered_map<int, sc_biguint<48>, MemAddrHashFunc> local_var_31;
store_85(local_var_31);
auto local_var_33 = cacc_cacc_s_pointer.range(16, 16);
sc_biguint<1> local_var_34 = 0;
bool local_var_35 = (local_var_33 == local_var_34);
sc_biguint<32> local_var_37 = 3;
sc_biguint<32> local_var_38 = ~local_var_37;
sc_biguint<32> local_var_39 = (cacc_cacc_s_status & local_var_38);
sc_biguint<2> local_var_40 = 2;
auto local_var_41 = (local_var_40[1] == 1) ? (~local_var_40) : local_var_40;
local_var_41 = (local_var_40[1] == 1) ? (~local_var_41) : local_var_41;
sc_biguint<32> local_var_42 = 0;
sc_biguint<32> local_var_43 = (local_var_41 << local_var_42);
sc_biguint<32> local_var_44 = (local_var_43 & local_var_37);
sc_biguint<32> local_var_45 = (local_var_39 | local_var_44);
sc_biguint<32> local_var_46 = 196608;
sc_biguint<32> local_var_47 = ~local_var_46;
sc_biguint<32> local_var_48 = (cacc_cacc_s_status & local_var_47);
sc_biguint<2> local_var_49 = 2;
auto local_var_50 = (local_var_49[1] == 1) ? (~local_var_49) : local_var_49;
local_var_50 = (local_var_49[1] == 1) ? (~local_var_50) : local_var_50;
sc_biguint<32> local_var_51 = 16;
sc_biguint<32> local_var_52 = (local_var_50 << local_var_51);
sc_biguint<32> local_var_53 = (local_var_52 & local_var_46);
sc_biguint<32> local_var_54 = (local_var_48 | local_var_53);
auto local_var_55 = (local_var_35) ? local_var_45 : local_var_54;
auto local_var_55_nxt_holder = local_var_55;
sc_biguint<5> local_var_56 = 0;
auto local_var_56_nxt_holder = local_var_56;
for (auto& it : local_var_0) {
  cacc_assembly_kernel_0[it.first] = it.second;
}
for (auto& it : local_var_1) {
  cacc_assembly_kernel_1[it.first] = it.second;
}
for (auto& it : local_var_2) {
  cacc_assembly_kernel_10[it.first] = it.second;
}
for (auto& it : local_var_3) {
  cacc_assembly_kernel_11[it.first] = it.second;
}
for (auto& it : local_var_4) {
  cacc_assembly_kernel_12[it.first] = it.second;
}
for (auto& it : local_var_5) {
  cacc_assembly_kernel_13[it.first] = it.second;
}
for (auto& it : local_var_6) {
  cacc_assembly_kernel_14[it.first] = it.second;
}
for (auto& it : local_var_7) {
  cacc_assembly_kernel_15[it.first] = it.second;
}
for (auto& it : local_var_8) {
  cacc_assembly_kernel_16[it.first] = it.second;
}
for (auto& it : local_var_9) {
  cacc_assembly_kernel_17[it.first] = it.second;
}
for (auto& it : local_var_10) {
  cacc_assembly_kernel_18[it.first] = it.second;
}
for (auto& it : local_var_11) {
  cacc_assembly_kernel_19[it.first] = it.second;
}
for (auto& it : local_var_12) {
  cacc_assembly_kernel_2[it.first] = it.second;
}
for (auto& it : local_var_13) {
  cacc_assembly_kernel_20[it.first] = it.second;
}
for (auto& it : local_var_14) {
  cacc_assembly_kernel_21[it.first] = it.second;
}
for (auto& it : local_var_15) {
  cacc_assembly_kernel_22[it.first] = it.second;
}
for (auto& it : local_var_16) {
  cacc_assembly_kernel_23[it.first] = it.second;
}
for (auto& it : local_var_17) {
  cacc_assembly_kernel_24[it.first] = it.second;
}
for (auto& it : local_var_18) {
  cacc_assembly_kernel_25[it.first] = it.second;
}
for (auto& it : local_var_19) {
  cacc_assembly_kernel_26[it.first] = it.second;
}
for (auto& it : local_var_20) {
  cacc_assembly_kernel_27[it.first] = it.second;
}
for (auto& it : local_var_21) {
  cacc_assembly_kernel_28[it.first] = it.second;
}
for (auto& it : local_var_22) {
  cacc_assembly_kernel_29[it.first] = it.second;
}
for (auto& it : local_var_23) {
  cacc_assembly_kernel_3[it.first] = it.second;
}
for (auto& it : local_var_24) {
  cacc_assembly_kernel_30[it.first] = it.second;
}
for (auto& it : local_var_25) {
  cacc_assembly_kernel_31[it.first] = it.second;
}
for (auto& it : local_var_26) {
  cacc_assembly_kernel_4[it.first] = it.second;
}
for (auto& it : local_var_27) {
  cacc_assembly_kernel_5[it.first] = it.second;
}
for (auto& it : local_var_28) {
  cacc_assembly_kernel_6[it.first] = it.second;
}
for (auto& it : local_var_29) {
  cacc_assembly_kernel_7[it.first] = it.second;
}
for (auto& it : local_var_30) {
  cacc_assembly_kernel_8[it.first] = it.second;
}
for (auto& it : local_var_31) {
  cacc_assembly_kernel_9[it.first] = it.second;
}
cacc_cacc_s_status = local_var_55_nxt_holder;
cacc_stripe_counter = local_var_56_nxt_holder;
#ifdef ILATOR_VERBOSE
instr_update_log << "No." << std::dec << GetInstrCntr() << '\t' << "cacc_start_from_idle state updates:" << std::endl;
instr_update_log << "    cacc_assembly_kernel_0 get updated" << std::endl;
instr_update_log << "    cacc_assembly_kernel_1 get updated" << std::endl;
instr_update_log << "    cacc_assembly_kernel_10 get updated" << std::endl;
instr_update_log << "    cacc_assembly_kernel_11 get updated" << std::endl;
instr_update_log << "    cacc_assembly_kernel_12 get updated" << std::endl;
instr_update_log << "    cacc_assembly_kernel_13 get updated" << std::endl;
instr_update_log << "    cacc_assembly_kernel_14 get updated" << std::endl;
instr_update_log << "    cacc_assembly_kernel_15 get updated" << std::endl;
instr_update_log << "    cacc_assembly_kernel_16 get updated" << std::endl;
instr_update_log << "    cacc_assembly_kernel_17 get updated" << std::endl;
instr_update_log << "    cacc_assembly_kernel_18 get updated" << std::endl;
instr_update_log << "    cacc_assembly_kernel_19 get updated" << std::endl;
instr_update_log << "    cacc_assembly_kernel_2 get updated" << std::endl;
instr_update_log << "    cacc_assembly_kernel_20 get updated" << std::endl;
instr_update_log << "    cacc_assembly_kernel_21 get updated" << std::endl;
instr_update_log << "    cacc_assembly_kernel_22 get updated" << std::endl;
instr_update_log << "    cacc_assembly_kernel_23 get updated" << std::endl;
instr_update_log << "    cacc_assembly_kernel_24 get updated" << std::endl;
instr_update_log << "    cacc_assembly_kernel_25 get updated" << std::endl;
instr_update_log << "    cacc_assembly_kernel_26 get updated" << std::endl;
instr_update_log << "    cacc_assembly_kernel_27 get updated" << std::endl;
instr_update_log << "    cacc_assembly_kernel_28 get updated" << std::endl;
instr_update_log << "    cacc_assembly_kernel_29 get updated" << std::endl;
instr_update_log << "    cacc_assembly_kernel_3 get updated" << std::endl;
instr_update_log << "    cacc_assembly_kernel_30 get updated" << std::endl;
instr_update_log << "    cacc_assembly_kernel_31 get updated" << std::endl;
instr_update_log << "    cacc_assembly_kernel_4 get updated" << std::endl;
instr_update_log << "    cacc_assembly_kernel_5 get updated" << std::endl;
instr_update_log << "    cacc_assembly_kernel_6 get updated" << std::endl;
instr_update_log << "    cacc_assembly_kernel_7 get updated" << std::endl;
instr_update_log << "    cacc_assembly_kernel_8 get updated" << std::endl;
instr_update_log << "    cacc_assembly_kernel_9 get updated" << std::endl;
instr_update_log << "    cacc_cacc_s_status => " << std::hex << "0x" << cacc_cacc_s_status << std::endl; 
instr_update_log << "    cacc_stripe_counter => " << std::hex << "0x" << cacc_stripe_counter << std::endl; 
instr_update_log << std::endl;
#endif
}
