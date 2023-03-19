// File: cmac_instrs.cc

#include <ilang/ilang++.h>
#include <cmac_config.h>
#include <math.h>
#include <tuple>

using namespace std;

namespace ilang {

    //////////////////////////////////////////////////////////////////////////////
    ///  HELPER FUNCTIONS
    //////////////////////////////////////////////////////////////////////////////

    // Return 16-bit representation of int8
    ExprRef int8_to_int16(ExprRef num){
        auto bv7_unsigned = num & BvConst(0x7F, NVDLA_CMAC_KERNEL_MAX_ELEM_WIDTH);
        auto bv = Ite(SelectBit(num, 7) == 0, bv7_unsigned, bv7_unsigned | BvConst(0xFF80, NVDLA_CMAC_KERNEL_MAX_ELEM_WIDTH));
        return bv;
    }

    // Sum of fp16 numbers
    ExprRef fp16_add(ExprRef a, ExprRef b){
        // Place holder code
        return BvConst(0, NVDLA_CMAC_KERNEL_MAX_ELEM_WIDTH);
    }

    // Product of fp16 numbers
    ExprRef fp16_mult(ExprRef a, ExprRef b){
        // Place holder code
        return BvConst(0, NVDLA_CMAC_KERNEL_MAX_ELEM_WIDTH);
    }

    // (For Winograd mode) Matrix multiplication of two bit vectors. out_addr_width is an optional argument that is used to specify result size
    // iff the matrix operation results in a smaller output address width.
    ExprRef matrix_mul(ExprRef& a, ExprRef& b, tuple<int, int> a_size, tuple<int, int> b_size, int out_addr_width = 0, int shamt = 0){
        // get dimensions
        int a_rows = get<0>(a_size);
        int ab_dim_shared = get<1>((a_size));
        int b_cols = get<1>(b_size);

        // output dimensions
        int res_size = a_rows * b_cols;
        int res_addr_width = ceil(log2(res_size));
        res_addr_width = (res_addr_width > out_addr_width)? res_addr_width : out_addr_width;

        // compute output
        auto res = MemConst(0, {}, res_addr_width, NVDLA_CMAC_KERNEL_MAX_ELEM_WIDTH);
        for (int i = 0; i < a_rows; i++){
            for (int j = 0; j < b_cols; j++){
                // Reset sum
                auto sum = BvConst(0, NVDLA_CMAC_KERNEL_MAX_ELEM_WIDTH);
                for (int k = 0; k < ab_dim_shared; k++){
                    // sum += a[i][k] + b[k][j]
                    sum = sum + a.Load(BvConst(i * ab_dim_shared + k, res_addr_width)) * b.Load(BvConst(k * b_cols + j, NVDLA_CMAC_KERNEL_ADDR_WIDTH)); 
                }
                
                // Apply shift
                sum = (shamt < 0) ? sum >> -shamt : sum << shamt;
                
                // res[i][j] = sum
                res = res.Store(BvConst(i * b_cols + j, res_addr_width), sum);
            }
        }

        return res;
    }

    //////////////////////////////////////////////////////////////////////////////
    /// ILA INSTRUCTIONS
    //////////////////////////////////////////////////////////////////////////////

    void DefineCMACInstrs(Ila& m) {

        //////////////////////////////////////////////////////////////////////////////
        ///  VARIABLES
        //////////////////////////////////////////////////////////////////////////////

        auto cmac_csb_addr = Extract(m.input("csb2cmac_addr"), 11, 0);
        auto cmac_csb_valid = (m.state("cmac2csb_rdy") == BvConst(1,1)) & (m.input("csb2cmac_vld") == BvConst(1,1));
        auto cmac_csb_write = m.input("csb2cmac_write") == BvConst(1,1);
        
        auto cmac_group0_unset = m.state(GetVarName("group0_", NVDLA_CMAC_D_OP_ENABLE)) == BvConst(0,1);
        auto cmac_group1_unset = m.state(GetVarName("group1_", NVDLA_CMAC_D_OP_ENABLE)) == BvConst(0,1);
        auto cmac_group0_status = m.state(NVDLA_CMAC_S_STATUS_0);
        auto cmac_group1_status = m.state(NVDLA_CMAC_S_STATUS_1);
        
        auto cmac_producer = m.state(NVDLA_CMAC_S_PRODUCER);
        auto cmac_consumer = m.state(NVDLA_CMAC_S_CONSUMER);

        auto csc2cmac_vld = m.input("csc2cmac_vld");
        auto csc2cmac_sending_last_batch = m.input("csc2cmac_sending_last_batch");
        auto using_stale_data = BoolConst(false);
        auto data_precision = BvConst(0,2);        // defualt value is INT8
        auto conv_mode = BvConst(0,1);             // default value is Direct Convolution

        //////////////////////////////////////////////////////////////////////////////
        ///  SET REGISTERS
        //////////////////////////////////////////////////////////////////////////////

        { // CMAC Set Producer (addr:004)
            auto instr = m.NewInstr("cmac_set_producer");
            instr.SetDecode(cmac_csb_addr == 0x004 & cmac_csb_valid & cmac_csb_write);
            instr.SetUpdate(cmac_producer, Extract(m.input("csb2cmac_data"), NVDLA_CMAC_S_PRODUCER_WIDTH - 1, 0));
        }

        { // CMAC Set Start Group 0 (addr:008)
            auto instr = m.NewInstr("cmac_set_start_group0");
            instr.SetDecode(cmac_csb_addr == 0x008 & cmac_csb_valid & cmac_csb_write & cmac_producer == BvConst(0,1) & cmac_group0_unset);
            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_CMAC_D_OP_ENABLE)), Extract(m.input("csb2cmac_data"), NVDLA_CMAC_D_OP_ENABLE_WIDTH - 1, 0));
        }      
        
        { // CMAC Set Start Group 1 (addr:008)
            auto instr = m.NewInstr("cmac_set_start_group1");
            instr.SetDecode(cmac_csb_addr == 0x008 & cmac_csb_valid & cmac_csb_write & cmac_producer == BvConst(1,1) & cmac_group1_unset);
            instr.SetUpdate(m.state(GetVarName("group1_", NVDLA_CMAC_D_OP_ENABLE)), Extract(m.input("csb2cmac_data"), NVDLA_CMAC_D_OP_ENABLE_WIDTH - 1, 0));
        } 

        { // CMAC Set Config Group 0 (addr:00c)
            auto instr = m.NewInstr("cmac_set_config_group0");
            instr.SetDecode(cmac_csb_addr == 0x00c & cmac_csb_valid & cmac_csb_write & cmac_producer == BvConst(0,1) & cmac_group0_unset);
            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_CMAC_D_MISC_CFG)), Extract(m.input("csb2cmac_data"), NVDLA_CMAC_D_MISC_CFG_WIDTH - 1, 0));
        }

        { // CMAC Set Config Group 1 (addr:00c)
            auto instr = m.NewInstr("cmac_set_config_group1");
            instr.SetDecode(cmac_csb_addr == 0x00c & cmac_csb_valid & cmac_csb_write & cmac_producer == BvConst(1,1) & cmac_group1_unset);
            instr.SetUpdate(m.state(GetVarName("group1_", NVDLA_CMAC_D_MISC_CFG)), Extract(m.input("csb2cmac_data"), NVDLA_CMAC_D_MISC_CFG_WIDTH - 1, 0));
        }

        //////////////////////////////////////////////////////////////////////////////
        ///  EXPLICIT STATUS CONTROL
        //////////////////////////////////////////////////////////////////////////////

        { // Start from IDLE
            auto instr = m.NewInstr("cmac_start_from_idle");
            auto group0_ok = cmac_consumer == BvConst(0,1) & !cmac_group0_unset & (cmac_group0_status == IDLE);
            auto group1_ok = cmac_consumer == BvConst(1,1) & !cmac_group1_unset & (cmac_group1_status == IDLE);
            instr.SetDecode((group0_ok ^ group1_ok) & csc2cmac_vld);
            
            data_precision = Ite(cmac_consumer == BvConst(0,1), Extract(m.state(GetVarName("group0_", NVDLA_CMAC_D_MISC_CFG)), 13, 12),
                                    Extract(m.state(GetVarName("group1_", NVDLA_CMAC_D_MISC_CFG)), 13, 12));

            conv_mode = Ite(cmac_consumer == BvConst(0,1), Extract(m.state(GetVarName("group0_", NVDLA_CMAC_D_MISC_CFG)), 0, 0),
                                Extract(m.state(GetVarName("group1_", NVDLA_CMAC_D_MISC_CFG)), 0, 0));

            // Update status
            instr.SetUpdate(cmac_group0_status, Ite(group0_ok, BUSY, cmac_group0_status));
            instr.SetUpdate(cmac_group1_status, Ite(group1_ok, BUSY, cmac_group1_status)); 

            // Cold start
            using_stale_data = BoolConst(true);
        }

        { // Pend2Busy
            auto instr = m.NewInstr("pend2busy");
            auto group0_pend = cmac_group0_status == PEND & cmac_consumer == BvConst(0,1);
            auto group1_pend = cmac_group1_status == PEND & cmac_consumer == BvConst(1,1);

            instr.SetDecode((group0_pend | group1_pend) & csc2cmac_vld);
            instr.SetUpdate(cmac_group0_status, Ite(group0_pend, BUSY, cmac_group0_status));
            instr.SetUpdate(cmac_group1_status, Ite(group1_pend, BUSY, cmac_group1_status)); 
            using_stale_data = (conv_mode == WINOGRAD) | !(m.input("csc2cmac_reuse_weights"));
        }

        //////////////////////////////////////////////////////////////////////////////
        ///  COMPUTATION
        //////////////////////////////////////////////////////////////////////////////

        { // Cache new weights
            auto instr = m.NewInstr("cmac_cache_weights");
            instr.SetDecode((cmac_group0_status == BUSY | cmac_group1_status == BUSY) & using_stale_data);
            
            for (auto i = 0; i < NVDLA_CMAC_MAX_NUM_KERNELS_ATOMIC_OP; i++) {
                // auto mem_ptr = MemConst(0, {}, NVDLA_CMAC_KERNEL_ADDR_WIDTH, NVDLA_CMAC_KERNEL_MAX_ELEM_WIDTH).get();
                auto mem = MemConst(0, {}, NVDLA_CMAC_KERNEL_ADDR_WIDTH, NVDLA_CMAC_KERNEL_MAX_ELEM_WIDTH);
                
                for (auto j = 0; j < NVDLA_CMAC_KERNEL_NUM_ELEM; j++){
                    
                    auto wt = m.input("csc2cmac_wt_" + (std::to_string(i)) + "_" + (std::to_string(j)));
                    wt = Ite(data_precision == INT8, int8_to_int16(wt), wt);

                    // Update memory and store new address
                    // auto new_mem = ExprRef(mem_ptr).Store(BvConst(j, NVDLA_CMAC_KERNEL_ADDR_WIDTH), wt);
                    // mem_ptr = new_mem.get();
                    mem = mem.Store(BvConst(j, NVDLA_CMAC_KERNEL_ADDR_WIDTH), wt);
                }

                // instr.SetUpdate(m.state("cached_wt_kernel_" + (std::to_string(i))), ExprRef(mem_ptr));
                instr.SetUpdate(m.state("cached_wt_kernel_" + (std::to_string(i))), mem);

            } 

            using_stale_data = BoolConst(false);
        }

        { // Compute dot product using cached weights
            auto instr = m.NewInstr("cmac_conv_direct");
            instr.SetDecode((cmac_group0_status == BUSY | cmac_group1_status == BUSY) & !using_stale_data & (conv_mode == DIRECT));

            for (auto i = 0; i < NVDLA_CMAC_NUM_MAC_CELLS; i++) {
                // Reset output channels
                // auto mem_ptr = MemConst(0, {}, NVDLA_CMAC_MAC_CELL_OUTPUT_ADDR_WIDTH, NVDLA_CMAC_KERNEL_MAX_ELEM_WIDTH).get();
                auto mem = MemConst(0, {}, NVDLA_CMAC_MAC_CELL_OUTPUT_ADDR_WIDTH, NVDLA_CMAC_KERNEL_MAX_ELEM_WIDTH);

                auto sum0 = BvConst(0, NVDLA_CMAC_KERNEL_MAX_ELEM_WIDTH);    
                auto sum1 = BvConst(0, NVDLA_CMAC_KERNEL_MAX_ELEM_WIDTH);             
                for (auto j = 0; j < NVDLA_CMAC_KERNEL_NUM_ELEM; j++){
                    auto wt0 = Load(m.state("cached_wt_kernel_" + (std::to_string(i))), BvConst(j, NVDLA_CMAC_KERNEL_ADDR_WIDTH));
                    auto wt1 = Load(m.state("cached_wt_kernel_" + (std::to_string(NVDLA_CMAC_NUM_MAC_CELLS + i))), BvConst(j, NVDLA_CMAC_KERNEL_ADDR_WIDTH));
                    auto ft = m.input("csc2cmac_ft_" + (std::to_string(j)));
                    ft = Ite(data_precision == INT8, int8_to_int16(ft), ft);

                    // accumulate
                    sum0 = Ite(data_precision == FP16, fp16_add(sum0, fp16_mult(wt0, ft)), sum0 + (wt0 * ft));
                    sum1 = Ite(data_precision == INT8, sum1 + (wt1 * ft), BvConst(0, NVDLA_CMAC_KERNEL_MAX_ELEM_WIDTH));
                }
                
                sum0 = Ite(data_precision == INT8, int8_to_int16(sum0), sum0);
                sum1 = int8_to_int16(sum1);

                // Update memory and store new address
                // auto new_mem = ExprRef(mem_ptr).Store(BvConst(0, NVDLA_CMAC_MAC_CELL_OUTPUT_ADDR_WIDTH), sum0);
                // mem_ptr = new_mem.get();
                mem = mem.Store(BvConst(0, NVDLA_CMAC_MAC_CELL_OUTPUT_ADDR_WIDTH), sum0);
                mem = mem.Store(BvConst(1, NVDLA_CMAC_MAC_CELL_OUTPUT_ADDR_WIDTH), sum1);

                // update state
                instr.SetUpdate(m.state("cmac2cacc_partial_sum_mac_" + (std::to_string(i))), mem);                   
            }

            auto done = m.input("csc2cmac_sending_last_batch") == BoolConst(true);
            auto group0_active = cmac_consumer == BvConst(0,1);
            
            auto status_update = Ite(done, IDLE, PEND);
            instr.SetUpdate(cmac_group0_status, Ite(group0_active, status_update, cmac_group0_status));
            instr.SetUpdate(cmac_group1_status, Ite(!group0_active, status_update, cmac_group1_status));

            auto enable_flag_update = Ite(done, BvConst(0,1), BvConst(1,1));
            auto group0_enable = m.state(GetVarName("group0_", NVDLA_CMAC_D_OP_ENABLE));
            auto group1_enable = m.state(GetVarName("group1_", NVDLA_CMAC_D_OP_ENABLE));
            instr.SetUpdate(group0_enable, Ite(group0_active, enable_flag_update, group0_enable));
            instr.SetUpdate(group1_enable, Ite(!group0_active, enable_flag_update, group1_enable));

            instr.SetUpdate(cmac_consumer, Ite(done, ~cmac_consumer, cmac_consumer));
        }

        { // (Winograd mode) Compute partial sum using cached weights
            auto instr = m.NewInstr("cmac_conv_winograd");
            instr.SetDecode((cmac_group0_status == BUSY | cmac_group1_status == BUSY) & !using_stale_data & (conv_mode == WINOGRAD));

            // Constant matrices used in winograd mode
            auto C = MemConst(0, {{0,1},{5,1}, {6,0xFFFF}, {7,1}, {8,0xFFFF}, {9,1}, {10,1}, {15, 0xFFFF}}, NVDLA_CMAC_KERNEL_ADDR_WIDTH, NVDLA_CMAC_KERNEL_MAX_ELEM_WIDTH); 
            tuple<int, int> C_size = make_tuple(4, 4);

            auto double_G = MemConst(0, {{0,2}, {3,1}, {4,1}, {5,1}, {6,1}, {7, 0xFFFF}, {8,1}, {11, 2}}, NVDLA_CMAC_KERNEL_ADDR_WIDTH, NVDLA_CMAC_KERNEL_MAX_ELEM_WIDTH); 
            tuple<int, int> double_G_size = make_tuple(4, 3);

            auto A_T = MemConst(0, {{0,1}, {1,1}, {2,1}, {5,1}, {6,0xFFFF}, {7,0xFFFF}}, NVDLA_CMAC_KERNEL_ADDR_WIDTH, NVDLA_CMAC_KERNEL_MAX_ELEM_WIDTH);
            tuple<int, int> A_T_size = make_tuple(2, 4);

            for (auto i = 0; i < NVDLA_CMAC_NUM_MAC_CELLS; i++) {
                // Reset output channels
                auto mem_ptr = MemConst(0, {}, NVDLA_CMAC_MAC_CELL_OUTPUT_ADDR_WIDTH, NVDLA_CMAC_KERNEL_MAX_ELEM_WIDTH).get();
                auto sum = BvConst(0, NVDLA_CMAC_KERNEL_MAX_ELEM_WIDTH);                
                
                //*********** <Insert code here> ****************
                // matrix_mul(arr1, arr2, arr1_size, arr2_size, NVDLA_CMAC_KERNEL_ADDR_WIDTH, shamt);

                // Note: ILAng doesn't allow loads from local memory variables. Will have to break down computation into multiple
                //      steps if that functionality is needed. 
                // sum = ...
                // **********************************************

                sum = Ite(data_precision == INT8, int8_to_int16(sum), sum);

                // Update memory and store new address
                auto new_mem = ExprRef(mem_ptr).Store(BvConst(0, NVDLA_CMAC_MAC_CELL_OUTPUT_ADDR_WIDTH), sum);
                // auto new_mem = ExprRef(mem_ptr).Store(BvConst(1, NVDLA_CMAC_MAC_CELL_OUTPUT_ADDR_WIDTH), sum);
                // auto new_mem = ExprRef(mem_ptr).Store(BvConst(2, NVDLA_CMAC_MAC_CELL_OUTPUT_ADDR_WIDTH), sum);
                // auto new_mem = ExprRef(mem_ptr).Store(BvConst(3, NVDLA_CMAC_MAC_CELL_OUTPUT_ADDR_WIDTH), sum);
                mem_ptr = new_mem.get();

                // update state
                instr.SetUpdate(m.state("cmac2cacc_partial_sum_mac_" + (std::to_string(i))), ExprRef(mem_ptr));                   
            }

            auto group0_active = cmac_consumer == BvConst(0,1);
            instr.SetUpdate(cmac_group0_status, Ite(group0_active, IDLE, cmac_group0_status));
            instr.SetUpdate(cmac_group1_status, Ite(!group0_active, IDLE, cmac_group1_status));

            auto group0_enable = m.state(GetVarName("group0_", NVDLA_CMAC_D_OP_ENABLE));
            auto group1_enable = m.state(GetVarName("group1_", NVDLA_CMAC_D_OP_ENABLE));
            instr.SetUpdate(group0_enable, Ite(group0_active, BvConst(0,1), group0_enable));
            instr.SetUpdate(group1_enable, Ite(!group0_active, BvConst(0,1), group1_enable));
            
            instr.SetUpdate(cmac_consumer, ~cmac_consumer);
        }
    }

} // namespace ilang
