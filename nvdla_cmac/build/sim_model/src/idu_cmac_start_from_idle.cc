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
sc_biguint<1> local_var_1 = 0;
bool local_var_2 = (cmac_cmac_s_consumer == local_var_1);
sc_biguint<1> local_var_4 = 0;
bool local_var_5 = (cmac_group0_cmac_d_op_en == local_var_4);
bool local_var_6 = !local_var_5;
bool local_var_7 = (local_var_2 & local_var_6);
sc_biguint<2> local_var_9 = 0;
bool local_var_10 = (cmac_cmac_s_status0 == local_var_9);
bool local_var_11 = (local_var_7 & local_var_10);
sc_biguint<2> local_var_12 = 2;
auto local_var_13 = (local_var_11) ? local_var_12 : cmac_cmac_s_status0;
auto local_var_13_nxt_holder = local_var_13;
sc_biguint<1> local_var_14 = 1;
bool local_var_15 = (cmac_cmac_s_consumer == local_var_14);
sc_biguint<1> local_var_17 = 0;
bool local_var_18 = (cmac_group1_cmac_d_op_en == local_var_17);
bool local_var_19 = !local_var_18;
bool local_var_20 = (local_var_15 & local_var_19);
sc_biguint<2> local_var_22 = 0;
bool local_var_23 = (cmac_cmac_s_status1 == local_var_22);
bool local_var_24 = (local_var_20 & local_var_23);
sc_biguint<2> local_var_25 = 2;
auto local_var_26 = (local_var_24) ? local_var_25 : cmac_cmac_s_status1;
auto local_var_26_nxt_holder = local_var_26;
cmac_cmac_s_status0 = local_var_13_nxt_holder;
cmac_cmac_s_status1 = local_var_26_nxt_holder;
#ifdef ILATOR_VERBOSE
instr_update_log << "No." << std::dec << GetInstrCntr() << '\t' << "cmac_start_from_idle state updates:" << std::endl;
instr_update_log << "    cmac_cmac_s_status0 => " << std::hex << "0x" << cmac_cmac_s_status0 << std::endl; 
instr_update_log << "    cmac_cmac_s_status1 => " << std::hex << "0x" << cmac_cmac_s_status1 << std::endl; 
instr_update_log << std::endl;
#endif
}
