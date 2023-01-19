// File: cmac_instrs.cc

#include <ilang/ilang++.h>
#include <cmac_config.h>
// #include <cmath>

namespace ilang {

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
        ///  STATUS CONTROL
        //////////////////////////////////////////////////////////////////////////////

        { // Start from IDLE
            auto instr = m.NewInstr("cmac_start_from_idle");
            auto group0_ok = cmac_consumer == BvConst(0,1) & m.state(GetVarName("group0_", NVDLA_CMAC_D_OP_ENABLE)) == BvConst(1,1);
            instr.SetDecode(cmac_state == IDLE & group0_ok & csc2cmac_vld);
            
            instr.SetUpdate(m.state("cmac_state"), BUSY);
            using_stale_data = !(m.input("csc2cmac_reuse_weights"))
        }

        { // Pend2Busy
            auto instr = m.NewInstr("pend2busy");
            instr.SetDecode(cmac_state == PEND & csc2cmac_vld);

            instr.SetUpdate(m.state("cmac_state"), BUSY);
            using_stale_data = !(m.input("csc2cmac_reuse_weights"))
        }

       // Busy2Pend and Busy2Idle handles in "cmac_compute_dot_product"

        //////////////////////////////////////////////////////////////////////////////
        ///  COMPUTATION
        //////////////////////////////////////////////////////////////////////////////

        { // Cache new weights
            auto instr = m.NewInstr("cmac_cache_weights");
            instr.SetDecode((cmac_state == BUSY) & using_stale_data);
            
            for (auto i = 0; i < 16; i++) {
                auto wt = m.input("csc2cmac_weight_kernel_" + (std::to_string(i)));
                Store(m.state("cached_weights"), BvConst(i, NVDLA_CMAC_MAC_ARRAY_ADDR_WIDTH), wt);            
            }

            using_stale_data = BoolConst(false);
        }


        { // Compute dot product using cached weights
            auto instr = m.NewInstr("cmac_compute_dot_product");
            instr.SetDecode((cmac_state == BUSY) & !using_stale_data);

            for (auto i = 0; i < 16; i++) {
                // get inputs for each cell
                auto wt = BvConst(0, NVDLA_CMAC_INT16_KERNEL_WIDTH);
                Load(m.state("cached_weights"), BvConst(i, NVDLA_CMAC_MAC_ARRAY_ADDR_WIDTH), wt);   
                auto feature = m.input("csc2cmac_feature_kernel");

                // int16 calculation
                auto sum_int16 = BvConst(0, NVDLA_CMAC_INT16_DATA_WIDTH);
                for (auto j = 0; j < 64; j++) {
                    auto lo = NVDLA_CMAC_INT16_DATA_WIDTH * j;
                    auto hi = lo + NVDLA_CMAC_INT16_DATA_WIDTH - 1;
                    sum_int16 = sum_int16 + Extract(wt, hi, lo) * Extract(feature, hi, lo);
                }
                Store(m.state("cmac2cacc_partial_sums"), BvConst(i, NVDLA_CMAC_MAC_ARRAY_ADDR_WIDTH), sum_int16);         

                // // int8 calculation
                // auto sum = BvConst(0, NVDLA_CMAC_INT16_DATA_WIDTH);
                // for (auto j = 0; j < 64; j++) {
                //     auto lo_0 = NVDLA_CMAC_INT16_DATA_WIDTH * j;
                //     auto hi_0 = lo_0 + NVDLA_CMAC_INT8_DATA_WIDTH - 1;
                    
                //     auto lo_1 = hi_0 + 1;
                //     auto hi_1 = lo_1 + NVDLA_CMAC_INT8_DATA_WIDTH - 1;

                //     auto sum_int8 = Extract(wt, hi_0, lo_0) * Extract(feature, hi_0, lo_0) + 
                //         Extract(wt, hi_1, lo_1) * Extract(feature, hi_1, lo_1);

                //     sum = sum + Sext(sum_int8, NVDLA_CMAC_INT16_DATA_WIDTH)
                // }
                // Store(m.state("cmac2cacc_partial_sums"), BvConst(i, NVDLA_CMAC_MAC_ARRAY_ADDR_WIDTH), sum);         
            }

            instr.SetUpdate(m.state("cmac_state"), Ite(m.input("csc2cmac_sending_last_batch") == BoolConst(false), PEND, IDLE));
        }

    }

} // namespace ilang
