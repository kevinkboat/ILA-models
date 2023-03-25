#include <cmac.h>
bool cmac::decode_cmac_cmac_set_producer() {
auto local_var_1 = cmac_csb2cmac_addr.range(11, 0);
sc_biguint<12> local_var_2 = 4;
bool local_var_3 = (local_var_1 == local_var_2);
bool local_var_6 = (cmac_cmac2csb_rdy & cmac_csb2cmac_vld);
bool local_var_7 = (local_var_3 & local_var_6);
bool local_var_9 = (local_var_7 & cmac_csb2cmac_write);
auto& univ_var_1 = local_var_9;
return univ_var_1;
}
void cmac::update_cmac_cmac_set_producer() {
auto local_var_1 = cmac_csb2cmac_data.range(0, 0);
auto local_var_1_nxt_holder = local_var_1;
cmac_cmac_s_producer = local_var_1_nxt_holder;
#ifdef ILATOR_VERBOSE
instr_update_log << "No." << std::dec << GetInstrCntr() << '\t' << "cmac_set_producer state updates:" << std::endl;
instr_update_log << "    cmac_cmac_s_producer => " << std::hex << "0x" << cmac_cmac_s_producer << std::endl; 
instr_update_log << std::endl;
#endif
}
