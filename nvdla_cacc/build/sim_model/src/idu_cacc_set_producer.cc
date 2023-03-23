#include <cacc.h>
bool cacc::decode_cacc_cacc_set_producer() {
auto local_var_1 = cacc_csb2cacc_addr.range(16, 0);
sc_biguint<17> local_var_2 = 36868;
bool local_var_3 = (local_var_1 == local_var_2);
bool local_var_6 = (cacc_cacc2csb_rdy & cacc_csb2cacc_vld);
bool local_var_7 = (local_var_3 & local_var_6);
bool local_var_9 = (local_var_7 & cacc_csb2cacc_write);
auto& univ_var_1 = local_var_9;
return univ_var_1;
}
void cacc::update_cacc_cacc_set_producer() {
sc_biguint<32> local_var_1 = 65534;
sc_biguint<32> local_var_2 = (cacc_cacc_s_pointer & local_var_1);
sc_biguint<32> local_var_4 = ~local_var_1;
sc_biguint<32> local_var_5 = (cacc_csb2cacc_data & local_var_4);
sc_biguint<32> local_var_6 = (local_var_2 | local_var_5);
auto local_var_6_nxt_holder = local_var_6;
cacc_cacc_s_pointer = local_var_6_nxt_holder;
#ifdef ILATOR_VERBOSE
instr_update_log << "No." << std::dec << GetInstrCntr() << '\t' << "cacc_set_producer state updates:" << std::endl;
instr_update_log << "    cacc_cacc_s_pointer => " << std::hex << "0x" << cacc_cacc_s_pointer << std::endl; 
instr_update_log << std::endl;
#endif
}
