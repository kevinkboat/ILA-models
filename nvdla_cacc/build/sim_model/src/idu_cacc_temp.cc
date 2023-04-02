#include <cacc.h>
bool cacc::decode_cacc_cacc_temp() {
auto local_var_1 = cacc_cacc_s_status.range(1, 0);
sc_biguint<2> local_var_2 = 2;
bool local_var_3 = (local_var_1 == local_var_2);
auto local_var_4 = cacc_cacc_s_status.range(17, 16);
sc_biguint<2> local_var_5 = 2;
bool local_var_6 = (local_var_4 == local_var_5);
bool local_var_7 = (local_var_3 ^ local_var_6);
bool local_var_10 = (cacc_cacc2csb_rdy & cacc_csb2cacc_vld);
bool local_var_11 = !local_var_10;
bool local_var_12 = (local_var_7 & local_var_11);
auto& univ_var_23 = local_var_12;
return univ_var_23;
}
void cacc::update_cacc_cacc_temp() {
sc_biguint<32> local_var_1 = 65536;
sc_biguint<32> local_var_2 = ~local_var_1;
sc_biguint<32> local_var_3 = (cacc_cacc_s_pointer & local_var_2);
auto local_var_4 = cacc_cacc_s_pointer.range(16, 16);
sc_biguint<1> local_var_5 = ~local_var_4;
auto local_var_6 = (local_var_5[0] == 1) ? (~local_var_5) : local_var_5;
local_var_6 = (local_var_5[0] == 1) ? (~local_var_6) : local_var_6;
sc_biguint<32> local_var_7 = 16;
sc_biguint<32> local_var_8 = (local_var_6 << local_var_7);
sc_biguint<32> local_var_9 = (local_var_8 & local_var_1);
sc_biguint<32> local_var_10 = (local_var_3 | local_var_9);
auto local_var_10_nxt_holder = local_var_10;
sc_biguint<1> local_var_11 = 0;
bool local_var_12 = (local_var_4 == local_var_11);
sc_biguint<32> local_var_14 = 3;
sc_biguint<32> local_var_15 = ~local_var_14;
sc_biguint<32> local_var_16 = (cacc_cacc_s_status & local_var_15);
sc_biguint<2> local_var_17 = 1;
auto local_var_18 = (local_var_17[1] == 1) ? (~local_var_17) : local_var_17;
local_var_18 = (local_var_17[1] == 1) ? (~local_var_18) : local_var_18;
sc_biguint<32> local_var_19 = 0;
sc_biguint<32> local_var_20 = (local_var_18 << local_var_19);
sc_biguint<32> local_var_21 = (local_var_20 & local_var_14);
sc_biguint<32> local_var_22 = (local_var_16 | local_var_21);
sc_biguint<32> local_var_23 = 196608;
sc_biguint<32> local_var_24 = ~local_var_23;
sc_biguint<32> local_var_25 = (cacc_cacc_s_status & local_var_24);
sc_biguint<2> local_var_26 = 1;
auto local_var_27 = (local_var_26[1] == 1) ? (~local_var_26) : local_var_26;
local_var_27 = (local_var_26[1] == 1) ? (~local_var_27) : local_var_27;
sc_biguint<32> local_var_28 = 16;
sc_biguint<32> local_var_29 = (local_var_27 << local_var_28);
sc_biguint<32> local_var_30 = (local_var_29 & local_var_23);
sc_biguint<32> local_var_31 = (local_var_25 | local_var_30);
auto local_var_32 = (local_var_12) ? local_var_22 : local_var_31;
auto local_var_32_nxt_holder = local_var_32;
cacc_cacc_s_pointer = local_var_10_nxt_holder;
cacc_cacc_s_status = local_var_32_nxt_holder;
#ifdef ILATOR_VERBOSE
instr_update_log << "No." << std::dec << GetInstrCntr() << '\t' << "cacc_temp state updates:" << std::endl;
instr_update_log << "    cacc_cacc_s_pointer => " << std::hex << "0x" << cacc_cacc_s_pointer << std::endl; 
instr_update_log << "    cacc_cacc_s_status => " << std::hex << "0x" << cacc_cacc_s_status << std::endl; 
instr_update_log << std::endl;
#endif
}
