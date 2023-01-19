#include <cmac.h>
bool cmac::decode_cmac_cmac_start_from_idle() {
sc_biguint<2> local_var_1 = 0;
bool local_var_2 = (cmac_cmac_state == local_var_1);
sc_biguint<1> local_var_4 = 0;
bool local_var_5 = (cmac_cmac_s_consumer == local_var_4);
sc_biguint<1> local_var_7 = 1;
bool local_var_8 = (cmac_group0_cmac_d_op_en == local_var_7);
bool local_var_9 = (local_var_5 & local_var_8);
bool local_var_10 = (local_var_2 & local_var_9);
bool local_var_12 = (local_var_10 & cmac_csc2cmac_vld);
auto& univ_var_4 = local_var_12;
return univ_var_4;
}
void cmac::update_cmac_cmac_start_from_idle() {
sc_biguint<2> local_var_0 = 2;
auto local_var_0_nxt_holder = local_var_0;
cmac_cmac_state = local_var_0_nxt_holder;
#ifdef ILATOR_VERBOSE
instr_update_log << "No." << std::dec << GetInstrCntr() << '\t' << "cmac_start_from_idle state updates:" << std::endl;
instr_update_log << "    cmac_cmac_state => " << std::hex << "0x" << cmac_cmac_state << std::endl; 
instr_update_log << std::endl;
#endif
}
