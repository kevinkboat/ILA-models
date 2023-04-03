#include <cacc.h>
bool cacc::decode_cacc_pend2busy() {
auto local_var_1 = cacc_cacc_s_status.range(1, 0);
sc_biguint<2> local_var_2 = 1;
bool local_var_3 = (local_var_1 == local_var_2);
auto local_var_4 = cacc_cacc_s_status.range(17, 16);
sc_biguint<2> local_var_5 = 1;
bool local_var_6 = (local_var_4 == local_var_5);
bool local_var_7 = (local_var_3 ^ local_var_6);
sc_biguint<2> local_var_9 = 2;
bool local_var_10 = (cacc_cmac2cacc_status == local_var_9);
bool local_var_11 = (local_var_7 & local_var_10);
auto& univ_var_151 = local_var_11;
return univ_var_151;
}
void cacc::update_cacc_pend2busy() {
auto local_var_1 = cacc_cacc_s_pointer.range(16, 16);
sc_biguint<1> local_var_2 = 0;
bool local_var_3 = (local_var_1 == local_var_2);
sc_biguint<32> local_var_5 = 3;
sc_biguint<32> local_var_6 = ~local_var_5;
sc_biguint<32> local_var_7 = (cacc_cacc_s_status & local_var_6);
sc_biguint<2> local_var_8 = 2;
auto local_var_9 = (local_var_8[1] == 1) ? (~local_var_8) : local_var_8;
local_var_9 = (local_var_8[1] == 1) ? (~local_var_9) : local_var_9;
sc_biguint<32> local_var_10 = 0;
sc_biguint<32> local_var_11 = (local_var_9 << local_var_10);
sc_biguint<32> local_var_12 = (local_var_11 & local_var_5);
sc_biguint<32> local_var_13 = (local_var_7 | local_var_12);
sc_biguint<32> local_var_14 = 196608;
sc_biguint<32> local_var_15 = ~local_var_14;
sc_biguint<32> local_var_16 = (cacc_cacc_s_status & local_var_15);
sc_biguint<2> local_var_17 = 2;
auto local_var_18 = (local_var_17[1] == 1) ? (~local_var_17) : local_var_17;
local_var_18 = (local_var_17[1] == 1) ? (~local_var_18) : local_var_18;
sc_biguint<32> local_var_19 = 16;
sc_biguint<32> local_var_20 = (local_var_18 << local_var_19);
sc_biguint<32> local_var_21 = (local_var_20 & local_var_14);
sc_biguint<32> local_var_22 = (local_var_16 | local_var_21);
auto local_var_23 = (local_var_3) ? local_var_13 : local_var_22;
auto local_var_23_nxt_holder = local_var_23;
cacc_cacc_s_status = local_var_23_nxt_holder;
#ifdef ILATOR_VERBOSE
instr_update_log << "No." << std::dec << GetInstrCntr() << '\t' << "pend2busy state updates:" << std::endl;
instr_update_log << "    cacc_cacc_s_status => " << std::hex << "0x" << cacc_cacc_s_status << std::endl; 
instr_update_log << std::endl;
#endif
}
