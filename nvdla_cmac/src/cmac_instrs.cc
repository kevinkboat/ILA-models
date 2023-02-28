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
        auto cmac_producer = m.state(NVDLA_CMAC_S_PRODUCER);
        auto cmac_consumer = m.state(NVDLA_CMAC_S_CONSUMER);
        auto cmac_state = m.state("cmac_state");        

        auto csc2cmac_vld = m.input("csc2cmac_vld");
        auto csc2cmac_sending_last_batch = m.input("csc2cmac_sending_last_batch");
        auto using_stale_data = BoolConst(false);
        auto data_precision = Extract(m.state(GetVarName("group0_", NVDLA_CMAC_D_MISC_CFG)), 13, 12);
        auto conv_mode = Extract(m.state(GetVarName("group0_", NVDLA_CMAC_D_MISC_CFG)), 0, 0);

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
        
        { // CMAC Set Config Group 0 (addr:00c)
            auto instr = m.NewInstr("cmac_set_config_group0");
            instr.SetDecode(cmac_csb_addr == 0x00c & cmac_csb_valid & cmac_csb_write & cmac_producer == BvConst(0,1) & cmac_group0_unset);
            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_CMAC_D_MISC_CFG)), Extract(m.input("csb2cmac_data"), NVDLA_CMAC_D_MISC_CFG_WIDTH - 1, 0));
        }

        //////////////////////////////////////////////////////////////////////////////
        ///  EXPLICIT STATUS CONTROL
        //////////////////////////////////////////////////////////////////////////////

        { // Start from IDLE
            auto instr = m.NewInstr("cmac_start_from_idle");
            auto group0_ok = cmac_consumer == BvConst(0,1) & m.state(GetVarName("group0_", NVDLA_CMAC_D_OP_ENABLE)) == BvConst(1,1);
            instr.SetDecode(cmac_state == IDLE & group0_ok & csc2cmac_vld);
            
            // Cold start
            instr.SetUpdate(m.state("cmac_state"), BUSY);
            using_stale_data = BoolConst(true);
        }

        { // Pend2Busy
            auto instr = m.NewInstr("pend2busy");
            instr.SetDecode(cmac_state == PEND & csc2cmac_vld);
            instr.SetUpdate(m.state("cmac_state"), BUSY);
            using_stale_data = (conv_mode == WINOGRAD) | !(m.input("csc2cmac_reuse_weights"));
        }

        //////////////////////////////////////////////////////////////////////////////
        ///  COMPUTATION
        //////////////////////////////////////////////////////////////////////////////

        { // Cache new weights
            auto instr = m.NewInstr("cmac_cache_weights");
            instr.SetDecode((cmac_state == BUSY) & using_stale_data);
            
            for (auto i = 0; i < NVDLA_CMAC_NUM_MAC_CELLS; i++) {
                auto mem_ptr = MemConst(0, {}, NVDLA_CMAC_KERNEL_ADDR_WIDTH, NVDLA_CMAC_KERNEL_MAX_ELEM_WIDTH).get();
                
                for (auto j = 0; j < NVDLA_CMAC_KERNEL_NUM_ELEM; j++){
                    
                    auto wt = m.input("csc2cmac_wt_" + (std::to_string(i)) + "_" + (std::to_string(j)));
                    wt = Ite(data_precision == INT8, int8_to_int16(wt), wt);

                    // Update memory and store new address
                    auto new_mem = ExprRef(mem_ptr).Store(BvConst(j, NVDLA_CMAC_KERNEL_ADDR_WIDTH), wt);
                    mem_ptr = new_mem.get();
                }

                instr.SetUpdate(m.state("cached_wt_kernel_" + (std::to_string(i))), ExprRef(mem_ptr));
            } 

            using_stale_data = BoolConst(false);
        }


        { // Compute dot product using cached weights
            auto instr = m.NewInstr("cmac_conv_direct");
            instr.SetDecode((cmac_state == BUSY) & !using_stale_data & (conv_mode == DIRECT));

            for (auto i = 0; i < NVDLA_CMAC_NUM_MAC_CELLS; i++) {
                // Reset output channels
                auto mem_ptr = MemConst(0, {}, NVDLA_CMAC_MAC_CELL_OUTPUT_ADDR_WIDTH, NVDLA_CMAC_KERNEL_MAX_ELEM_WIDTH).get();

                // int calculation
                auto sum = BvConst(0, NVDLA_CMAC_KERNEL_MAX_ELEM_WIDTH);                
                for (auto j = 0; j < NVDLA_CMAC_KERNEL_NUM_ELEM; j++){
                    auto wt = Load(m.state("cached_wt_kernel_" + (std::to_string(i))), BvConst(j, NVDLA_CMAC_KERNEL_ADDR_WIDTH)); 
                    auto ft = m.input("csc2cmac_ft_" + (std::to_string(j)));
                    ft = Ite(data_precision == INT8, int8_to_int16(ft), ft);

                    // accumulate
                    sum = Ite(data_precision == FP16, fp16_add(sum, fp16_mult(wt, ft)), sum + (wt * ft));
                }
                
                sum = Ite(data_precision == INT8, int8_to_int16(sum), sum);

                // Update memory and store new address
                auto new_mem = ExprRef(mem_ptr).Store(BvConst(0, NVDLA_CMAC_MAC_CELL_OUTPUT_ADDR_WIDTH), sum);
                mem_ptr = new_mem.get();

                // update state
                instr.SetUpdate(m.state("cmac2cacc_partial_sum_mac_" + (std::to_string(i))), ExprRef(mem_ptr));                   
            }

            instr.SetUpdate(m.state("cmac_state"), Ite(m.input("csc2cmac_sending_last_batch") == BoolConst(false), PEND, IDLE));
            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_CMAC_D_OP_ENABLE)), Ite(m.input("csc2cmac_sending_last_batch") == BoolConst(false), BvConst(1,1), BvConst(0,1)));
        }

        { // (Winograd mode) Compute partial sum using cached weights
            auto instr = m.NewInstr("cmac_conv_winograd");
            instr.SetDecode((cmac_state == BUSY) & !using_stale_data & (conv_mode == WINOGRAD));

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

            instr.SetUpdate(m.state("cmac_state"), IDLE);
            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_CMAC_D_OP_ENABLE)), BvConst(0,1));
        }
    }

} // namespace ilang
