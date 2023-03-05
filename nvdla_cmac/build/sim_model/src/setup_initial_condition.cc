#include <cmac.h>
void cmac::setup_initial_condition() {
cmac_cmac2csb_rdy = 1;
cmac_cmac2csb_data_vld = 1;
cmac_cmac2cacc_status = 0;
cmac_cmac_s_status0 = 0;
cmac_cmac_s_status1 = 0;
cmac_cmac_s_producer = 0;
cmac_cmac_s_consumer = 0;
cmac_group0_cmac_d_op_en = 0;
cmac_group0_cmac_d_misc_cfg = 0;
cmac_group1_cmac_d_op_en = 0;
cmac_group1_cmac_d_misc_cfg = 0;
}
