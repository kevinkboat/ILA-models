// File: cmac_instrs.cc

#include <ilang/ilang++.h>
#include <cmac_config.h>
// #include <cmath>

namespace ilang {

    ExprRef int8_to_int16(ExprRef bv16, ExprRef data_type){
        auto bv7_unsigned = bv16 & BvConst(0x7F, NVDLA_CMAC_KERNEL_MAX_ELEM_WIDTH);

        // update weight based on datatype
        auto bv = Ite(data_type == INT16, bv16, 
                Ite(data_type == INT8, Ite(SelectBit(bv16, 7) == 0, bv7_unsigned, bv7_unsigned | BvConst(0xFF80, NVDLA_CMAC_KERNEL_MAX_ELEM_WIDTH)), 
                BvConst(0, NVDLA_CMAC_KERNEL_MAX_ELEM_WIDTH)));
        
        return bv;
    }

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
        auto data_type = Extract(m.state(GetVarName("group0_", NVDLA_CMAC_D_MISC_CFG)), 1, 0);

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
            using_stale_data = !(m.input("csc2cmac_reuse_weights"));
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
                    
                    auto wt = int8_to_int16(m.input("csc2cmac_wt_" + (std::to_string(i)) + "_" + (std::to_string(j))), data_type);
                    
                    // // Store weights
                    // auto wt16 = m.input("csc2cmac_wt_" + (std::to_string(i)) + "_" + (std::to_string(j)));
                    // auto wt7_unsigned = wt16 & BvConst(0x7F, NVDLA_CMAC_KERNEL_MAX_ELEM_WIDTH);

                    // // update weight based on datatype
                    // auto wt = Ite(data_type == INT16, wt16, 
                    //         Ite(data_type == INT8, Ite(SelectBit(wt16, 7) == 0, wt7_unsigned, wt7_unsigned | BvConst(0xFF80, NVDLA_CMAC_KERNEL_MAX_ELEM_WIDTH)), 
                    //         BvConst(0, NVDLA_CMAC_KERNEL_MAX_ELEM_WIDTH)));
                       
                    // Update memory and store new address
                    auto new_mem = ExprRef(mem_ptr).Store(BvConst(j, NVDLA_CMAC_KERNEL_ADDR_WIDTH), wt);
                    mem_ptr = new_mem.get();
                }

                instr.SetUpdate(m.state("cached_wt_kernel_" + (std::to_string(i))), ExprRef(mem_ptr));
            } 

            using_stale_data = BoolConst(false);
        }


        { // Compute dot product using cached weights
            auto instr = m.NewInstr("cmac_compute_dot_product");
            instr.SetDecode((cmac_state == BUSY) & !using_stale_data);

            auto mem_ptr = MemConst(0, {}, NVDLA_CMAC_MAC_CELLS_ADDR_WIDTH, NVDLA_CMAC_KERNEL_MAX_ELEM_WIDTH).get();

            for (auto i = 0; i < NVDLA_CMAC_NUM_MAC_CELLS; i++) {

                // int calculation
                auto sum = BvConst(0, NVDLA_CMAC_KERNEL_MAX_ELEM_WIDTH);                
                for (auto j = 0; j < NVDLA_CMAC_KERNEL_NUM_ELEM; j++){
                    auto wt = Load(m.state("cached_wt_kernel_" + (std::to_string(i))), BvConst(j, NVDLA_CMAC_KERNEL_ADDR_WIDTH)); 
                    auto ft = m.input("csc2cmac_ft_" + (std::to_string(j)));

                    // accumulate
                    sum = sum + (wt * ft);
                }

                sum = int8_to_int16(sum, data_type);
                // auto sum7_unsigned = sum & BvConst(0x7F, NVDLA_CMAC_KERNEL_MAX_ELEM_WIDTH);
                // sum = Ite(data_type == INT16, sum, 
                //         Ite(data_type == INT8, Ite(SelectBit(sum, 7) == 0, sum7_unsigned, sum7_unsigned | BvConst(0xFF80, NVDLA_CMAC_KERNEL_MAX_ELEM_WIDTH)), 
                //         BvConst(0, NVDLA_CMAC_KERNEL_MAX_ELEM_WIDTH)));

                // Update memory and store new address
                auto new_mem = ExprRef(mem_ptr).Store(BvConst(i, NVDLA_CMAC_MAC_CELLS_ADDR_WIDTH), sum);
                mem_ptr = new_mem.get();

                // Floating point calculation here 
                   
            }


            instr.SetUpdate(m.state("cmac2cacc_partial_sums"), ExprRef(mem_ptr));
            instr.SetUpdate(m.state("cmac_state"), Ite(m.input("csc2cmac_sending_last_batch") == BoolConst(false), PEND, IDLE));
            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_CMAC_D_OP_ENABLE)), Ite(m.input("csc2cmac_sending_last_batch") == BoolConst(false), BvConst(1,1), BvConst(0,1)));
        }

    }

} // namespace ilang
