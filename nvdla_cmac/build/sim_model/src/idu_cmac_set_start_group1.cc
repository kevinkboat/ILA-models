#include <cmac.h>
bool cmac::decode_cmac_cmac_set_start_group1() {
auto local_var_1 = cmac_csb2cmac_addr.range(11, 0);
sc_biguint<12> local_var_2 = 8;
bool local_var_3 = (local_var_1 == local_var_2);
sc_biguint<1> local_var_5 = 1;
bool local_var_6 = (cmac_cmac2csb_rdy == local_var_5);
sc_biguint<1> local_var_8 = 1;
bool local_var_9 = (cmac_csb2cmac_vld == local_var_8);
bool local_var_10 = (local_var_6 & local_var_9);
bool local_var_11 = (local_var_3 & local_var_10);
sc_biguint<1> local_var_13 = 1;
bool local_var_14 = (cmac_csb2cmac_write == local_var_13);
bool local_var_15 = (local_var_11 & local_var_14);
sc_biguint<1> local_var_17 = 1;
bool local_var_18 = (cmac_cmac_s_producer == local_var_17);
bool local_var_19 = (local_var_15 & local_var_18);
sc_biguint<1> local_var_21 = 0;
bool local_var_22 = (cmac_group1_cmac_d_op_en == local_var_21);
bool local_var_23 = (local_var_19 & local_var_22);
auto& univ_var_3 = local_var_23;
return univ_var_3;
}
void cmac::update_cmac_cmac_set_start_group1() {
auto local_var_1 = cmac_csb2cmac_data.range(0, 0);
auto local_var_1_nxt_holder = local_var_1;
cmac_group1_cmac_d_op_en = local_var_1_nxt_holder;
#ifdef ILATOR_VERBOSE
instr_update_log << "No." << std::dec << GetInstrCntr() << '\t' << "cmac_set_start_group1 state updates:" << std::endl;
instr_update_log << "    cmac_group1_cmac_d_op_en => " << std::hex << "0x" << cmac_group1_cmac_d_op_en << std::endl; 
instr_update_log << std::endl;
#endif
}
