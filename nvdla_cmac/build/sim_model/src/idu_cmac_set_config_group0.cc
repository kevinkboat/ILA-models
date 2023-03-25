#include <cmac.h>
bool cmac::decode_cmac_cmac_set_config_group0() {
auto local_var_1 = cmac_csb2cmac_addr.range(11, 0);
sc_biguint<12> local_var_2 = 12;
bool local_var_3 = (local_var_1 == local_var_2);
bool local_var_6 = (cmac_cmac2csb_rdy & cmac_csb2cmac_vld);
bool local_var_7 = (local_var_3 & local_var_6);
bool local_var_9 = (local_var_7 & cmac_csb2cmac_write);
sc_biguint<1> local_var_11 = 0;
bool local_var_12 = (cmac_cmac_s_producer == local_var_11);
bool local_var_13 = (local_var_9 & local_var_12);
sc_biguint<1> local_var_15 = 0;
bool local_var_16 = (cmac_group0_cmac_d_op_en == local_var_15);
bool local_var_17 = (local_var_13 & local_var_16);
auto& univ_var_4 = local_var_17;
return univ_var_4;
}
void cmac::update_cmac_cmac_set_config_group0() {
auto local_var_1 = cmac_csb2cmac_data.range(31, 0);
auto local_var_1_nxt_holder = local_var_1;
cmac_group0_cmac_d_misc_cfg = local_var_1_nxt_holder;
#ifdef ILATOR_VERBOSE
instr_update_log << "No." << std::dec << GetInstrCntr() << '\t' << "cmac_set_config_group0 state updates:" << std::endl;
instr_update_log << "    cmac_group0_cmac_d_misc_cfg => " << std::hex << "0x" << cmac_group0_cmac_d_misc_cfg << std::endl; 
instr_update_log << std::endl;
#endif
}
