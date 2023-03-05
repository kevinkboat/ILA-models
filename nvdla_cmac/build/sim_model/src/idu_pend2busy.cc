#include <cmac.h>
bool cmac::decode_cmac_pend2busy() {
sc_biguint<2> local_var_1 = 1;
bool local_var_2 = (cmac_cmac_s_status0 == local_var_1);
sc_biguint<1> local_var_4 = 0;
bool local_var_5 = (cmac_cmac_s_consumer == local_var_4);
bool local_var_6 = (local_var_2 & local_var_5);
sc_biguint<2> local_var_8 = 1;
bool local_var_9 = (cmac_cmac_s_status1 == local_var_8);
sc_biguint<1> local_var_10 = 1;
bool local_var_11 = (cmac_cmac_s_consumer == local_var_10);
bool local_var_12 = (local_var_9 & local_var_11);
bool local_var_13 = (local_var_6 | local_var_12);
bool local_var_15 = (local_var_13 & cmac_csc2cmac_vld);
auto& univ_var_7 = local_var_15;
return univ_var_7;
}
void cmac::update_cmac_pend2busy() {
sc_biguint<2> local_var_1 = 1;
bool local_var_2 = (cmac_cmac_s_status0 == local_var_1);
sc_biguint<1> local_var_4 = 0;
bool local_var_5 = (cmac_cmac_s_consumer == local_var_4);
bool local_var_6 = (local_var_2 & local_var_5);
sc_biguint<2> local_var_7 = 2;
auto local_var_8 = (local_var_6) ? local_var_7 : cmac_cmac_s_status0;
auto local_var_8_nxt_holder = local_var_8;
sc_biguint<2> local_var_10 = 1;
bool local_var_11 = (cmac_cmac_s_status1 == local_var_10);
sc_biguint<1> local_var_12 = 1;
bool local_var_13 = (cmac_cmac_s_consumer == local_var_12);
bool local_var_14 = (local_var_11 & local_var_13);
sc_biguint<2> local_var_15 = 2;
auto local_var_16 = (local_var_14) ? local_var_15 : cmac_cmac_s_status1;
auto local_var_16_nxt_holder = local_var_16;
cmac_cmac_s_status0 = local_var_8_nxt_holder;
cmac_cmac_s_status1 = local_var_16_nxt_holder;
#ifdef ILATOR_VERBOSE
instr_update_log << "No." << std::dec << GetInstrCntr() << '\t' << "pend2busy state updates:" << std::endl;
instr_update_log << "    cmac_cmac_s_status0 => " << std::hex << "0x" << cmac_cmac_s_status0 << std::endl; 
instr_update_log << "    cmac_cmac_s_status1 => " << std::hex << "0x" << cmac_cmac_s_status1 << std::endl; 
instr_update_log << std::endl;
#endif
}
