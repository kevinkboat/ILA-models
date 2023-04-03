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
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_32;
store_87(local_var_32);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_33;
store_89(local_var_33);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_34;
store_91(local_var_34);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_35;
store_93(local_var_35);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_36;
store_95(local_var_36);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_37;
store_97(local_var_37);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_38;
store_99(local_var_38);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_39;
store_101(local_var_39);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_40;
store_103(local_var_40);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_41;
store_105(local_var_41);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_42;
store_107(local_var_42);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_43;
store_109(local_var_43);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_44;
store_111(local_var_44);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_45;
store_113(local_var_45);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_46;
store_115(local_var_46);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_47;
store_117(local_var_47);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_48;
store_119(local_var_48);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_49;
store_121(local_var_49);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_50;
store_123(local_var_50);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_51;
store_125(local_var_51);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_52;
store_127(local_var_52);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_53;
store_129(local_var_53);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_54;
store_131(local_var_54);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_55;
store_133(local_var_55);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_56;
store_135(local_var_56);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_57;
store_137(local_var_57);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_58;
store_139(local_var_58);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_59;
store_141(local_var_59);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_60;
store_143(local_var_60);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_61;
store_145(local_var_61);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_62;
store_147(local_var_62);
std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> local_var_63;
store_149(local_var_63);
auto local_var_65 = cacc_cacc_s_pointer.range(16, 16);
sc_biguint<1> local_var_66 = 0;
bool local_var_67 = (local_var_65 == local_var_66);
sc_biguint<32> local_var_69 = 3;
sc_biguint<32> local_var_70 = ~local_var_69;
sc_biguint<32> local_var_71 = (cacc_cacc_s_status & local_var_70);
sc_biguint<2> local_var_72 = 2;
auto local_var_73 = (local_var_72[1] == 1) ? (~local_var_72) : local_var_72;
local_var_73 = (local_var_72[1] == 1) ? (~local_var_73) : local_var_73;
sc_biguint<32> local_var_74 = 0;
sc_biguint<32> local_var_75 = (local_var_73 << local_var_74);
sc_biguint<32> local_var_76 = (local_var_75 & local_var_69);
sc_biguint<32> local_var_77 = (local_var_71 | local_var_76);
sc_biguint<32> local_var_78 = 196608;
sc_biguint<32> local_var_79 = ~local_var_78;
sc_biguint<32> local_var_80 = (cacc_cacc_s_status & local_var_79);
sc_biguint<2> local_var_81 = 2;
auto local_var_82 = (local_var_81[1] == 1) ? (~local_var_81) : local_var_81;
local_var_82 = (local_var_81[1] == 1) ? (~local_var_82) : local_var_82;
sc_biguint<32> local_var_83 = 16;
sc_biguint<32> local_var_84 = (local_var_82 << local_var_83);
sc_biguint<32> local_var_85 = (local_var_84 & local_var_78);
sc_biguint<32> local_var_86 = (local_var_80 | local_var_85);
auto local_var_87 = (local_var_67) ? local_var_77 : local_var_86;
auto local_var_87_nxt_holder = local_var_87;
sc_biguint<5> local_var_88 = 0;
auto local_var_88_nxt_holder = local_var_88;
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
for (auto& it : local_var_32) {
  cacc_cacc_output_0[it.first] = it.second;
}
for (auto& it : local_var_33) {
  cacc_cacc_output_1[it.first] = it.second;
}
for (auto& it : local_var_34) {
  cacc_cacc_output_10[it.first] = it.second;
}
for (auto& it : local_var_35) {
  cacc_cacc_output_11[it.first] = it.second;
}
for (auto& it : local_var_36) {
  cacc_cacc_output_12[it.first] = it.second;
}
for (auto& it : local_var_37) {
  cacc_cacc_output_13[it.first] = it.second;
}
for (auto& it : local_var_38) {
  cacc_cacc_output_14[it.first] = it.second;
}
for (auto& it : local_var_39) {
  cacc_cacc_output_15[it.first] = it.second;
}
for (auto& it : local_var_40) {
  cacc_cacc_output_16[it.first] = it.second;
}
for (auto& it : local_var_41) {
  cacc_cacc_output_17[it.first] = it.second;
}
for (auto& it : local_var_42) {
  cacc_cacc_output_18[it.first] = it.second;
}
for (auto& it : local_var_43) {
  cacc_cacc_output_19[it.first] = it.second;
}
for (auto& it : local_var_44) {
  cacc_cacc_output_2[it.first] = it.second;
}
for (auto& it : local_var_45) {
  cacc_cacc_output_20[it.first] = it.second;
}
for (auto& it : local_var_46) {
  cacc_cacc_output_21[it.first] = it.second;
}
for (auto& it : local_var_47) {
  cacc_cacc_output_22[it.first] = it.second;
}
for (auto& it : local_var_48) {
  cacc_cacc_output_23[it.first] = it.second;
}
for (auto& it : local_var_49) {
  cacc_cacc_output_24[it.first] = it.second;
}
for (auto& it : local_var_50) {
  cacc_cacc_output_25[it.first] = it.second;
}
for (auto& it : local_var_51) {
  cacc_cacc_output_26[it.first] = it.second;
}
for (auto& it : local_var_52) {
  cacc_cacc_output_27[it.first] = it.second;
}
for (auto& it : local_var_53) {
  cacc_cacc_output_28[it.first] = it.second;
}
for (auto& it : local_var_54) {
  cacc_cacc_output_29[it.first] = it.second;
}
for (auto& it : local_var_55) {
  cacc_cacc_output_3[it.first] = it.second;
}
for (auto& it : local_var_56) {
  cacc_cacc_output_30[it.first] = it.second;
}
for (auto& it : local_var_57) {
  cacc_cacc_output_31[it.first] = it.second;
}
for (auto& it : local_var_58) {
  cacc_cacc_output_4[it.first] = it.second;
}
for (auto& it : local_var_59) {
  cacc_cacc_output_5[it.first] = it.second;
}
for (auto& it : local_var_60) {
  cacc_cacc_output_6[it.first] = it.second;
}
for (auto& it : local_var_61) {
  cacc_cacc_output_7[it.first] = it.second;
}
for (auto& it : local_var_62) {
  cacc_cacc_output_8[it.first] = it.second;
}
for (auto& it : local_var_63) {
  cacc_cacc_output_9[it.first] = it.second;
}
cacc_cacc_s_status = local_var_87_nxt_holder;
cacc_stripe_counter = local_var_88_nxt_holder;
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
instr_update_log << "    cacc_cacc_s_status => " << std::hex << "0x" << cacc_cacc_s_status << std::endl; 
instr_update_log << "    cacc_stripe_counter => " << std::hex << "0x" << cacc_stripe_counter << std::endl; 
instr_update_log << std::endl;
#endif
}
