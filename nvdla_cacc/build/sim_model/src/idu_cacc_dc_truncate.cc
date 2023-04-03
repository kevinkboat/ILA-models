#include <cacc.h>
bool cacc::decode_cacc_cacc_dc_truncate() {
auto local_var_1 = cacc_cacc_s_status.range(1, 0);
sc_biguint<2> local_var_2 = 1;
bool local_var_3 = (local_var_1 == local_var_2);
auto local_var_4 = cacc_cacc_s_status.range(17, 16);
sc_biguint<2> local_var_5 = 1;
bool local_var_6 = (local_var_4 == local_var_5);
bool local_var_7 = (local_var_3 ^ local_var_6);
sc_biguint<2> local_var_9 = 3;
bool local_var_10 = (cacc_cmac2cacc_status == local_var_9);
bool local_var_11 = (local_var_7 & local_var_10);
auto& univ_var_121 = local_var_11;
return univ_var_121;
}
void cacc::update_cacc_cacc_dc_truncate() {
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_0;
store_122(local_var_0);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_1;
store_124(local_var_1);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_2;
store_126(local_var_2);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_3;
store_128(local_var_3);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_4;
store_130(local_var_4);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_5;
store_132(local_var_5);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_6;
store_134(local_var_6);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_7;
store_136(local_var_7);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_8;
store_138(local_var_8);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_9;
store_140(local_var_9);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_10;
store_142(local_var_10);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_11;
store_144(local_var_11);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_12;
store_146(local_var_12);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_13;
store_148(local_var_13);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_14;
store_150(local_var_14);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_15;
store_152(local_var_15);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_16;
store_154(local_var_16);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_17;
store_156(local_var_17);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_18;
store_158(local_var_18);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_19;
store_160(local_var_19);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_20;
store_162(local_var_20);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_21;
store_164(local_var_21);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_22;
store_166(local_var_22);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_23;
store_168(local_var_23);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_24;
store_170(local_var_24);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_25;
store_172(local_var_25);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_26;
store_174(local_var_26);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_27;
store_176(local_var_27);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_28;
store_178(local_var_28);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_29;
store_180(local_var_29);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_30;
store_182(local_var_30);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_31;
store_184(local_var_31);
sc_biguint<32> local_var_33 = 65536;
sc_biguint<32> local_var_34 = ~local_var_33;
sc_biguint<32> local_var_35 = (cacc_cacc_s_pointer & local_var_34);
auto local_var_36 = cacc_cacc_s_pointer.range(16, 16);
sc_biguint<1> local_var_37 = ~local_var_36;
auto local_var_38 = (local_var_37[0] == 1) ? (~local_var_37) : local_var_37;
local_var_38 = (local_var_37[0] == 1) ? (~local_var_38) : local_var_38;
sc_biguint<32> local_var_39 = 16;
sc_biguint<32> local_var_40 = (local_var_38 << local_var_39);
sc_biguint<32> local_var_41 = (local_var_40 & local_var_33);
sc_biguint<32> local_var_42 = (local_var_35 | local_var_41);
auto local_var_42_nxt_holder = local_var_42;
sc_biguint<1> local_var_43 = 0;
bool local_var_44 = (local_var_36 == local_var_43);
sc_biguint<32> local_var_46 = 3;
sc_biguint<32> local_var_47 = ~local_var_46;
sc_biguint<32> local_var_48 = (cacc_cacc_s_status & local_var_47);
sc_biguint<2> local_var_49 = 0;
auto local_var_50 = (local_var_49[1] == 1) ? (~local_var_49) : local_var_49;
local_var_50 = (local_var_49[1] == 1) ? (~local_var_50) : local_var_50;
sc_biguint<32> local_var_51 = 0;
sc_biguint<32> local_var_52 = (local_var_50 << local_var_51);
sc_biguint<32> local_var_53 = (local_var_52 & local_var_46);
sc_biguint<32> local_var_54 = (local_var_48 | local_var_53);
sc_biguint<32> local_var_55 = 196608;
sc_biguint<32> local_var_56 = ~local_var_55;
sc_biguint<32> local_var_57 = (cacc_cacc_s_status & local_var_56);
sc_biguint<2> local_var_58 = 0;
auto local_var_59 = (local_var_58[1] == 1) ? (~local_var_58) : local_var_58;
local_var_59 = (local_var_58[1] == 1) ? (~local_var_59) : local_var_59;
sc_biguint<32> local_var_60 = 16;
sc_biguint<32> local_var_61 = (local_var_59 << local_var_60);
sc_biguint<32> local_var_62 = (local_var_61 & local_var_55);
sc_biguint<32> local_var_63 = (local_var_57 | local_var_62);
auto local_var_64 = (local_var_44) ? local_var_54 : local_var_63;
auto local_var_64_nxt_holder = local_var_64;
sc_biguint<32> local_var_66 = 1;
sc_biguint<32> local_var_67 = ~local_var_66;
sc_biguint<32> local_var_68 = (cacc_group0_cacc_d_op_enable & local_var_67);
sc_biguint<1> local_var_69 = 0;
auto local_var_70 = (local_var_69[0] == 1) ? (~local_var_69) : local_var_69;
local_var_70 = (local_var_69[0] == 1) ? (~local_var_70) : local_var_70;
sc_biguint<32> local_var_71 = 0;
sc_biguint<32> local_var_72 = (local_var_70 << local_var_71);
sc_biguint<32> local_var_73 = (local_var_72 & local_var_66);
sc_biguint<32> local_var_74 = (local_var_68 | local_var_73);
auto local_var_75 = (local_var_44) ? local_var_74 : cacc_group0_cacc_d_op_enable;
auto local_var_75_nxt_holder = local_var_75;
bool local_var_76 = !local_var_44;
sc_biguint<32> local_var_78 = 1;
sc_biguint<32> local_var_79 = ~local_var_78;
sc_biguint<32> local_var_80 = (cacc_group1_cacc_d_op_enable & local_var_79);
sc_biguint<1> local_var_81 = 0;
auto local_var_82 = (local_var_81[0] == 1) ? (~local_var_81) : local_var_81;
local_var_82 = (local_var_81[0] == 1) ? (~local_var_82) : local_var_82;
sc_biguint<32> local_var_83 = 0;
sc_biguint<32> local_var_84 = (local_var_82 << local_var_83);
sc_biguint<32> local_var_85 = (local_var_84 & local_var_78);
sc_biguint<32> local_var_86 = (local_var_80 | local_var_85);
auto local_var_87 = (local_var_76) ? local_var_86 : cacc_group1_cacc_d_op_enable;
auto local_var_87_nxt_holder = local_var_87;
for (auto& it : local_var_0) {
  cacc_cacc_output_0[it.first] = it.second;
}
for (auto& it : local_var_1) {
  cacc_cacc_output_1[it.first] = it.second;
}
for (auto& it : local_var_2) {
  cacc_cacc_output_10[it.first] = it.second;
}
for (auto& it : local_var_3) {
  cacc_cacc_output_11[it.first] = it.second;
}
for (auto& it : local_var_4) {
  cacc_cacc_output_12[it.first] = it.second;
}
for (auto& it : local_var_5) {
  cacc_cacc_output_13[it.first] = it.second;
}
for (auto& it : local_var_6) {
  cacc_cacc_output_14[it.first] = it.second;
}
for (auto& it : local_var_7) {
  cacc_cacc_output_15[it.first] = it.second;
}
for (auto& it : local_var_8) {
  cacc_cacc_output_16[it.first] = it.second;
}
for (auto& it : local_var_9) {
  cacc_cacc_output_17[it.first] = it.second;
}
for (auto& it : local_var_10) {
  cacc_cacc_output_18[it.first] = it.second;
}
for (auto& it : local_var_11) {
  cacc_cacc_output_19[it.first] = it.second;
}
for (auto& it : local_var_12) {
  cacc_cacc_output_2[it.first] = it.second;
}
for (auto& it : local_var_13) {
  cacc_cacc_output_20[it.first] = it.second;
}
for (auto& it : local_var_14) {
  cacc_cacc_output_21[it.first] = it.second;
}
for (auto& it : local_var_15) {
  cacc_cacc_output_22[it.first] = it.second;
}
for (auto& it : local_var_16) {
  cacc_cacc_output_23[it.first] = it.second;
}
for (auto& it : local_var_17) {
  cacc_cacc_output_24[it.first] = it.second;
}
for (auto& it : local_var_18) {
  cacc_cacc_output_25[it.first] = it.second;
}
for (auto& it : local_var_19) {
  cacc_cacc_output_26[it.first] = it.second;
}
for (auto& it : local_var_20) {
  cacc_cacc_output_27[it.first] = it.second;
}
for (auto& it : local_var_21) {
  cacc_cacc_output_28[it.first] = it.second;
}
for (auto& it : local_var_22) {
  cacc_cacc_output_29[it.first] = it.second;
}
for (auto& it : local_var_23) {
  cacc_cacc_output_3[it.first] = it.second;
}
for (auto& it : local_var_24) {
  cacc_cacc_output_30[it.first] = it.second;
}
for (auto& it : local_var_25) {
  cacc_cacc_output_31[it.first] = it.second;
}
for (auto& it : local_var_26) {
  cacc_cacc_output_4[it.first] = it.second;
}
for (auto& it : local_var_27) {
  cacc_cacc_output_5[it.first] = it.second;
}
for (auto& it : local_var_28) {
  cacc_cacc_output_6[it.first] = it.second;
}
for (auto& it : local_var_29) {
  cacc_cacc_output_7[it.first] = it.second;
}
for (auto& it : local_var_30) {
  cacc_cacc_output_8[it.first] = it.second;
}
for (auto& it : local_var_31) {
  cacc_cacc_output_9[it.first] = it.second;
}
cacc_cacc_s_pointer = local_var_42_nxt_holder;
cacc_cacc_s_status = local_var_64_nxt_holder;
cacc_group0_cacc_d_op_enable = local_var_75_nxt_holder;
cacc_group1_cacc_d_op_enable = local_var_87_nxt_holder;
#ifdef ILATOR_VERBOSE
instr_update_log << "No." << std::dec << GetInstrCntr() << '\t' << "cacc_dc_truncate state updates:" << std::endl;
instr_update_log << "    cacc_cacc_output_0 get updated" << std::endl;
instr_update_log << "    cacc_cacc_output_1 get updated" << std::endl;
instr_update_log << "    cacc_cacc_output_10 get updated" << std::endl;
instr_update_log << "    cacc_cacc_output_11 get updated" << std::endl;
instr_update_log << "    cacc_cacc_output_12 get updated" << std::endl;
instr_update_log << "    cacc_cacc_output_13 get updated" << std::endl;
instr_update_log << "    cacc_cacc_output_14 get updated" << std::endl;
instr_update_log << "    cacc_cacc_output_15 get updated" << std::endl;
instr_update_log << "    cacc_cacc_output_16 get updated" << std::endl;
instr_update_log << "    cacc_cacc_output_17 get updated" << std::endl;
instr_update_log << "    cacc_cacc_output_18 get updated" << std::endl;
instr_update_log << "    cacc_cacc_output_19 get updated" << std::endl;
instr_update_log << "    cacc_cacc_output_2 get updated" << std::endl;
instr_update_log << "    cacc_cacc_output_20 get updated" << std::endl;
instr_update_log << "    cacc_cacc_output_21 get updated" << std::endl;
instr_update_log << "    cacc_cacc_output_22 get updated" << std::endl;
instr_update_log << "    cacc_cacc_output_23 get updated" << std::endl;
instr_update_log << "    cacc_cacc_output_24 get updated" << std::endl;
instr_update_log << "    cacc_cacc_output_25 get updated" << std::endl;
instr_update_log << "    cacc_cacc_output_26 get updated" << std::endl;
instr_update_log << "    cacc_cacc_output_27 get updated" << std::endl;
instr_update_log << "    cacc_cacc_output_28 get updated" << std::endl;
instr_update_log << "    cacc_cacc_output_29 get updated" << std::endl;
instr_update_log << "    cacc_cacc_output_3 get updated" << std::endl;
instr_update_log << "    cacc_cacc_output_30 get updated" << std::endl;
instr_update_log << "    cacc_cacc_output_31 get updated" << std::endl;
instr_update_log << "    cacc_cacc_output_4 get updated" << std::endl;
instr_update_log << "    cacc_cacc_output_5 get updated" << std::endl;
instr_update_log << "    cacc_cacc_output_6 get updated" << std::endl;
instr_update_log << "    cacc_cacc_output_7 get updated" << std::endl;
instr_update_log << "    cacc_cacc_output_8 get updated" << std::endl;
instr_update_log << "    cacc_cacc_output_9 get updated" << std::endl;
instr_update_log << "    cacc_cacc_s_pointer => " << std::hex << "0x" << cacc_cacc_s_pointer << std::endl; 
instr_update_log << "    cacc_cacc_s_status => " << std::hex << "0x" << cacc_cacc_s_status << std::endl; 
instr_update_log << "    cacc_group0_cacc_d_op_enable => " << std::hex << "0x" << cacc_group0_cacc_d_op_enable << std::endl; 
instr_update_log << "    cacc_group1_cacc_d_op_enable => " << std::hex << "0x" << cacc_group1_cacc_d_op_enable << std::endl; 
instr_update_log << std::endl;
#endif
}
