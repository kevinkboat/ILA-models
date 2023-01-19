#include <cmac.h>
bool cmac::decode_cmac_pend2busy() {
sc_biguint<2> local_var_1 = 1;
bool local_var_2 = (cmac_cmac_state == local_var_1);
bool local_var_4 = (local_var_2 & cmac_csc2cmac_vld);
auto& univ_var_5 = local_var_4;
return univ_var_5;
}
void cmac::update_cmac_pend2busy() {
sc_biguint<2> local_var_0 = 2;
auto local_var_0_nxt_holder = local_var_0;
cmac_cmac_state = local_var_0_nxt_holder;
#ifdef ILATOR_VERBOSE
instr_update_log << "No." << std::dec << GetInstrCntr() << '\t' << "pend2busy state updates:" << std::endl;
instr_update_log << "    cmac_cmac_state => " << std::hex << "0x" << cmac_cmac_state << std::endl; 
instr_update_log << std::endl;
#endif
}
