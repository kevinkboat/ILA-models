#include <cmac.h>
bool cmac::decode_cmac_cmac_cache_weights() {
sc_biguint<2> local_var_1 = 2;
bool local_var_2 = (cmac_cmac_state == local_var_1);
bool local_var_4 = !cmac_csc2cmac_reuse_weights;
bool local_var_5 = (local_var_2 & local_var_4);
auto& univ_var_6 = local_var_5;
return univ_var_6;
}
void cmac::update_cmac_cmac_cache_weights() {
#ifdef ILATOR_VERBOSE
instr_update_log << "No." << std::dec << GetInstrCntr() << '\t' << "cmac_cache_weights state updates:" << std::endl;
instr_update_log << std::endl;
#endif
}
