#include <systemc>
#include <iostream>
#include <sstream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "nlohmann/json.hpp"
#include "cmac.h"

using json = nlohmann::json;

std::string file_in;
std::string file_out;

// Module for reading inputs into ILA model
SC_MODULE(Source) {
  sc_in<bool> clk{"clk"};

  sc_out<bool> cmac_csc2cmac_sending_last_batch;
  sc_out<bool> cmac_csc2cmac_vld;
  sc_out<bool> cmac_csc2cmac_reuse_weights;
  sc_out<sc_biguint<8>> cmac_csc2cmac_status;
  sc_out<sc_biguint<1024>> cmac_csc2cmac_feature_kernel;

  sc_out<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_15;
  sc_out<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_14;
  sc_out<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_13;
  sc_out<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_12;
  sc_out<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_11;
  sc_out<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_10;
  sc_out<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_9;
  sc_out<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_0;
  sc_out<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_1;
  sc_out<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_2;
  sc_out<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_3;
  sc_out<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_4;
  sc_out<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_5;
  sc_out<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_6;
  sc_out<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_7;
  sc_out<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_8;

  sc_out<sc_biguint<16>> cmac_csb2cmac_addr;
  sc_out<sc_biguint<32>> cmac_csb2cmac_data;
  sc_out<sc_biguint<1>> cmac_csb2cmac_write;
  sc_out<sc_biguint<1>> cmac_csb2cmac_vld;
  
  sc_out< sc_biguint<1> > input_done;

  SC_CTOR(Source) {
    SC_THREAD(source_input);
    sensitive << clk.pos();
  }

  void source_input() {
    // reset the port
    cmac_csc2cmac_sending_last_batch = false;
    cmac_csc2cmac_vld = false;
    cmac_csc2cmac_reuse_weights = false;
    cmac_csc2cmac_status = 0;
    cmac_csc2cmac_feature_kernel = "0x0";

    cmac_csc2cmac_weight_kernel_15 = "0x0";
    cmac_csc2cmac_weight_kernel_14 = "0x0";
    cmac_csc2cmac_weight_kernel_13 = "0x0";
    cmac_csc2cmac_weight_kernel_12 = "0x0";
    cmac_csc2cmac_weight_kernel_11 = "0x0";
    cmac_csc2cmac_weight_kernel_10 = "0x0";
    cmac_csc2cmac_weight_kernel_9 = "0x0";
    cmac_csc2cmac_weight_kernel_0 = "0x0";
    cmac_csc2cmac_weight_kernel_1 = "0x0";
    cmac_csc2cmac_weight_kernel_2 = "0x0";
    cmac_csc2cmac_weight_kernel_3 = "0x0";
    cmac_csc2cmac_weight_kernel_4 = "0x0";
    cmac_csc2cmac_weight_kernel_5 = "0x0";
    cmac_csc2cmac_weight_kernel_6 = "0x0";
    cmac_csc2cmac_weight_kernel_7 = "0x0";
    cmac_csc2cmac_weight_kernel_8 = "0x0";
    
    cmac_csb2cmac_addr = "0x0000";
    cmac_csb2cmac_data = 0;
    cmac_csb2cmac_write = 0;
    cmac_csb2cmac_vld = 0;

    input_done = 0;
    
    // read program fragment from file
    std::ifstream fin;
    fin.open(file_in, ios::in);
    
    json cmd_seq;
    cmd_seq = json::parse(fin);

    // Pass the command to the ports
    for (size_t i = 0; i < cmd_seq["program fragment"].size(); i++) {
    //   for (size_t j = 0; j < 16; j++) {
    //     sdp_cacc_data[j] = cmd_seq["program fragment"][i]["cacc_data_" + std::to_string(j)].get<int>();
    //   }
    // }

    // cmac_cmac_a_csb_addr = std::stoi((cmd_seq["program fragment"][i]["cmac_cmac_a_csb_addr"].get<std::string>()).c_str(), nullptr, 16);
    
    // cmac_cmac_a_csb_data = cmd_seq["program fragment"][i]["cmac_cmac_a_csb_data"].get<int>();
    // cmac_cmac_a_csb_write = cmd_seq["program fragment"][i]["cmac_cmac_a_csb_write"].get<int>();    
    // cmac_cmac_a_csb_vld = cmd_seq["program fragment"][i]["cmac_cmac_a_csb_vld"].get<int>();
    // // cmac_csc_weights_int16 = cmd_seq["program fragment"][i]["cmac_csc_weights_int16"].get<int>();
    // cmac_csc_weights_int16 = std::stoi((cmd_seq["program fragment"][i]["cmac_csc_weights_int16"].get<std::string>()).c_str(), nullptr, 16);
    // cmac_csc_data_int16 = cmd_seq["program fragment"][i]["cmac_csc_data_int16"].get<int>();
    // cmac_status = cmd_seq["program fragment"][i]["cmac_status"].get<int>();
    // cmac_output_ack = cmd_seq["program fragment"][i]["cmac_output_ack"].get<int>();
    // cmac_done = cmd_seq["program fragment"][i]["cmac_done"].get<int>();

    cmac_csc2cmac_sending_last_batch = cmd_seq["program fragment"][i]["cmac_csc2cmac_sending_last_batch"].get<bool>();
    cmac_csc2cmac_vld = cmd_seq["program fragment"][i]["cmac_csc2cmac_vld"].get<bool>();
    cmac_csc2cmac_reuse_weights = cmd_seq["program fragment"][i]["cmac_csc2cmac_reuse_weights"].get<bool>();
    cmac_csc2cmac_status = cmd_seq["program fragment"][i]["cmac_csc2cmac_status"].get<int>();
    
    cmac_csb2cmac_addr = std::stoi((cmd_seq["program fragment"][i]["cmac_csb2cmac_addr"].get<std::string>()).c_str(), nullptr, 16);
    cmac_csb2cmac_data = cmd_seq["program fragment"][i]["cmac_csb2cmac_data"].get<int>();
    cmac_csb2cmac_write = cmd_seq["program fragment"][i]["cmac_csb2cmac_write"].get<int>();
    cmac_csb2cmac_vld = cmd_seq["program fragment"][i]["cmac_csb2cmac_vld"].get<int>();

    cmac_csc2cmac_feature_kernel = std::stoi((cmd_seq["program fragment"][i]["cmac_csc2cmac_feature_kernel"].get<std::string>()).c_str(), nullptr, 16);

    cmac_csc2cmac_weight_kernel_15 = std::stoi((cmd_seq["program fragment"][i]["cmac_csc2cmac_weight_kernel_15"].get<std::string>()).c_str(), nullptr, 16);
    cmac_csc2cmac_weight_kernel_14 = std::stoi((cmd_seq["program fragment"][i]["cmac_csc2cmac_weight_kernel_14"].get<std::string>()).c_str(), nullptr, 16);
    cmac_csc2cmac_weight_kernel_13 = std::stoi((cmd_seq["program fragment"][i]["cmac_csc2cmac_weight_kernel_13"].get<std::string>()).c_str(), nullptr, 16);
    cmac_csc2cmac_weight_kernel_12 = std::stoi((cmd_seq["program fragment"][i]["cmac_csc2cmac_weight_kernel_12"].get<std::string>()).c_str(), nullptr, 16);
    
    cmac_csc2cmac_weight_kernel_11 = std::stoi((cmd_seq["program fragment"][i]["cmac_csc2cmac_weight_kernel_11"].get<std::string>()).c_str(), nullptr, 16);
    cmac_csc2cmac_weight_kernel_10 = std::stoi((cmd_seq["program fragment"][i]["cmac_csc2cmac_weight_kernel_10"].get<std::string>()).c_str(), nullptr, 16);
    cmac_csc2cmac_weight_kernel_9 = std::stoi((cmd_seq["program fragment"][i]["cmac_csc2cmac_weight_kernel_9"].get<std::string>()).c_str(), nullptr, 16);
    cmac_csc2cmac_weight_kernel_0 = std::stoi((cmd_seq["program fragment"][i]["cmac_csc2cmac_weight_kernel_0"].get<std::string>()).c_str(), nullptr, 16);
    
    cmac_csc2cmac_weight_kernel_1 = std::stoi((cmd_seq["program fragment"][i]["cmac_csc2cmac_weight_kernel_1"].get<std::string>()).c_str(), nullptr, 16);
    cmac_csc2cmac_weight_kernel_2 = std::stoi((cmd_seq["program fragment"][i]["cmac_csc2cmac_weight_kernel_2"].get<std::string>()).c_str(), nullptr, 16);
    cmac_csc2cmac_weight_kernel_3 = std::stoi((cmd_seq["program fragment"][i]["cmac_csc2cmac_weight_kernel_3"].get<std::string>()).c_str(), nullptr, 16);
    cmac_csc2cmac_weight_kernel_4 = std::stoi((cmd_seq["program fragment"][i]["cmac_csc2cmac_weight_kernel_4"].get<std::string>()).c_str(), nullptr, 16);
    
    cmac_csc2cmac_weight_kernel_5 = std::stoi((cmd_seq["program fragment"][i]["cmac_csc2cmac_weight_kernel_5"].get<std::string>()).c_str(), nullptr, 16);
    cmac_csc2cmac_weight_kernel_6 = std::stoi((cmd_seq["program fragment"][i]["cmac_csc2cmac_weight_kernel_6"].get<std::string>()).c_str(), nullptr, 16);
    cmac_csc2cmac_weight_kernel_7 = std::stoi((cmd_seq["program fragment"][i]["cmac_csc2cmac_weight_kernel_7"].get<std::string>()).c_str(), nullptr, 16);
    cmac_csc2cmac_weight_kernel_8 = std::stoi((cmd_seq["program fragment"][i]["cmac_csc2cmac_weight_kernel_8"].get<std::string>()).c_str(), nullptr, 16);

    wait(10, SC_NS);
    
    }

    input_done = 1;
    std::cout << "read_file" << std::flush;

  }

};

SC_MODULE(testbench) {
  // SC_HAS_PROCESS(testbench);
  cmac cmac_inst;
  Source src;

  sc_clock clk;

  sc_out<bool> cmac_csc2cmac_sending_last_batch_signal{"cmac_csc2cmac_sending_last_batch_signal"};
  sc_out<bool> cmac_csc2cmac_vld_signal{"cmac_csc2cmac_vld_signal"};
  sc_out<bool> cmac_csc2cmac_reuse_weights_signal{"cmac_csc2cmac_reuse_weights_signal"};
  sc_out<sc_biguint<8>> cmac_csc2cmac_status_signal{"cmac_csc2cmac_status_signal"};
  sc_out<sc_biguint<1024>> cmac_csc2cmac_feature_kernel_signal{"cmac_csc2cmac_feature_kernel_signal"};

  sc_out<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_15_signal{"cmac_csc2cmac_weight_kernel_15_signal"};
  sc_out<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_14_signal{"cmac_csc2cmac_weight_kernel_14_signal"};
  sc_out<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_13_signal{"cmac_csc2cmac_weight_kernel_13_signal"};
  sc_out<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_12_signal{"cmac_csc2cmac_weight_kernel_12_signal"};
  sc_out<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_11_signal{"cmac_csc2cmac_weight_kernel_11_signal"};
  sc_out<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_10_signal{"cmac_csc2cmac_weight_kernel_10_signal"};
  sc_out<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_9_signal{"cmac_csc2cmac_weight_kernel_9_signal"};
  sc_out<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_0_signal{"cmac_csc2cmac_weight_kernel_0_signal"};
  sc_out<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_1_signal{"cmac_csc2cmac_weight_kernel_1_signal"};
  sc_out<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_2_signal{"cmac_csc2cmac_weight_kernel_2_signal"};
  sc_out<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_3_signal{"cmac_csc2cmac_weight_kernel_3_signal"};
  sc_out<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_4_signal{"cmac_csc2cmac_weight_kernel_4_signal"};
  sc_out<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_5_signal{"cmac_csc2cmac_weight_kernel_5_signal"};
  sc_out<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_6_signal{"cmac_csc2cmac_weight_kernel_6_signal"};
  sc_out<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_7_signal{"cmac_csc2cmac_weight_kernel_7_signal"};
  sc_out<sc_biguint<1024>> cmac_csc2cmac_weight_kernel_8_signal{"cmac_csc2cmac_weight_kernel_8_signal"};

  sc_out<sc_biguint<16>> cmac_csb2cmac_addr_signal{"cmac_csb2cmac_addr_signal"};
  sc_out<sc_biguint<32>> cmac_csb2cmac_data_signal{"cmac_csb2cmac_data_signal"};
  sc_out<sc_biguint<1>> cmac_csb2cmac_write_signal{"cmac_csb2cmac_write_signal"};
  sc_out<sc_biguint<1>> cmac_csb2cmac_vld_signal{"cmac_csb2cmac_vld_signal"};

  sc_out< sc_biguint<1> > input_done{"input_done"};

  SC_CTOR(testbench) :
    clk("clk", 1, SC_NS),
    cmac_inst("cmac_inst"),
    src("source")
  {
    // Read in signals from the prog_frag file
    src.clk(clk);

    src.cmac_csc2cmac_sending_last_batch(cmac_csc2cmac_sending_last_batch_signal); 
    src.cmac_csc2cmac_vld(cmac_csc2cmac_vld_signal);
    src.cmac_csc2cmac_reuse_weights(cmac_csc2cmac_reuse_weights_signal);
    src.cmac_csc2cmac_status(cmac_csc2cmac_status_signal);
    src.cmac_csc2cmac_feature_kernel(cmac_csc2cmac_feature_kernel_signal);

    src.cmac_csc2cmac_weight_kernel_15(cmac_csc2cmac_weight_kernel_15_signal);
    src.cmac_csc2cmac_weight_kernel_14(cmac_csc2cmac_weight_kernel_14_signal);
    src.cmac_csc2cmac_weight_kernel_13(cmac_csc2cmac_weight_kernel_13_signal);
    src.cmac_csc2cmac_weight_kernel_12(cmac_csc2cmac_weight_kernel_12_signal);
    
    src.cmac_csc2cmac_weight_kernel_11(cmac_csc2cmac_weight_kernel_11_signal);
    src.cmac_csc2cmac_weight_kernel_10(cmac_csc2cmac_weight_kernel_10_signal);
    src.cmac_csc2cmac_weight_kernel_9(cmac_csc2cmac_weight_kernel_9_signal);
    src.cmac_csc2cmac_weight_kernel_0(cmac_csc2cmac_weight_kernel_0_signal);
    
    src.cmac_csc2cmac_weight_kernel_1(cmac_csc2cmac_weight_kernel_1_signal);
    src.cmac_csc2cmac_weight_kernel_2(cmac_csc2cmac_weight_kernel_2_signal);
    src.cmac_csc2cmac_weight_kernel_3(cmac_csc2cmac_weight_kernel_3_signal);
    src.cmac_csc2cmac_weight_kernel_4(cmac_csc2cmac_weight_kernel_4_signal);
    
    src.cmac_csc2cmac_weight_kernel_5(cmac_csc2cmac_weight_kernel_5_signal);
    src.cmac_csc2cmac_weight_kernel_6(cmac_csc2cmac_weight_kernel_6_signal);
    src.cmac_csc2cmac_weight_kernel_7(cmac_csc2cmac_weight_kernel_7_signal);
    src.cmac_csc2cmac_weight_kernel_8(cmac_csc2cmac_weight_kernel_8_signal);
    
    src.cmac_csb2cmac_addr(cmac_csb2cmac_addr_signal);
    src.cmac_csb2cmac_data(cmac_csb2cmac_data_signal);
    src.cmac_csb2cmac_write(cmac_csb2cmac_write_signal);
    src.cmac_csb2cmac_vld(cmac_csb2cmac_vld_signal);

    src.input_done(input_done);

    // Link with the sdp.h SystemC model

    cmac_inst.cmac_csc2cmac_sending_last_batch_in(cmac_csc2cmac_sending_last_batch_signal); 
    cmac_inst.cmac_csc2cmac_vld_in(cmac_csc2cmac_vld_signal);
    cmac_inst.cmac_csc2cmac_reuse_weights_in(cmac_csc2cmac_reuse_weights_signal);
    cmac_inst.cmac_csc2cmac_status_in(cmac_csc2cmac_status_signal);
    cmac_inst.cmac_csc2cmac_feature_kernel_in(cmac_csc2cmac_feature_kernel_signal);

    cmac_inst.cmac_csc2cmac_weight_kernel_15_in(cmac_csc2cmac_weight_kernel_15_signal);
    cmac_inst.cmac_csc2cmac_weight_kernel_14_in(cmac_csc2cmac_weight_kernel_14_signal);
    cmac_inst.cmac_csc2cmac_weight_kernel_13_in(cmac_csc2cmac_weight_kernel_13_signal);
    cmac_inst.cmac_csc2cmac_weight_kernel_12_in(cmac_csc2cmac_weight_kernel_12_signal);
    
    cmac_inst.cmac_csc2cmac_weight_kernel_11_in(cmac_csc2cmac_weight_kernel_11_signal);
    cmac_inst.cmac_csc2cmac_weight_kernel_10_in(cmac_csc2cmac_weight_kernel_10_signal);
    cmac_inst.cmac_csc2cmac_weight_kernel_9_in(cmac_csc2cmac_weight_kernel_9_signal);
    cmac_inst.cmac_csc2cmac_weight_kernel_0_in(cmac_csc2cmac_weight_kernel_0_signal);
    
    cmac_inst.cmac_csc2cmac_weight_kernel_1_in(cmac_csc2cmac_weight_kernel_1_signal);
    cmac_inst.cmac_csc2cmac_weight_kernel_2_in(cmac_csc2cmac_weight_kernel_2_signal);
    cmac_inst.cmac_csc2cmac_weight_kernel_3_in(cmac_csc2cmac_weight_kernel_3_signal);
    cmac_inst.cmac_csc2cmac_weight_kernel_4_in(cmac_csc2cmac_weight_kernel_4_signal);
    
    cmac_inst.cmac_csc2cmac_weight_kernel_5_in(cmac_csc2cmac_weight_kernel_5_signal);
    cmac_inst.cmac_csc2cmac_weight_kernel_6_in(cmac_csc2cmac_weight_kernel_6_signal);
    cmac_inst.cmac_csc2cmac_weight_kernel_7_in(cmac_csc2cmac_weight_kernel_7_signal);
    cmac_inst.cmac_csc2cmac_weight_kernel_8_in(cmac_csc2cmac_weight_kernel_8_signal);
    
    cmac_inst.cmac_csb2cmac_addr_in(cmac_csb2cmac_addr_signal);
    cmac_inst.cmac_csb2cmac_data_in(cmac_csb2cmac_data_signal);
    cmac_inst.cmac_csb2cmac_write_in(cmac_csb2cmac_write_signal);
    cmac_inst.cmac_csb2cmac_vld_in(cmac_csb2cmac_vld_signal);

    SC_THREAD(run);
  }

  // Run the SystemC simuation and log outputs
  void run() {
    cmac_inst.instr_log.open("instr_log_conv.txt", ofstream::out | ofstream::trunc);
    cmac_inst.instr_update_log.open("instr_update_log_conv.txt", ios::out | ios::trunc);

    std::cout << "start running" << std::endl;
    std::cout << "*********** simulation start ***********" << std::endl;
    wait(10, SC_NS);

    while (input_done == 0) {
		  std::cout << "current simulation time: " << '\t' << sc_time_stamp() << "\r" << std::flush;
      wait(10, SC_NS);
    }
    wait(1000, SC_NS);

    // Log final outputs
    std::ofstream fout;
    fout.open(file_out, ios::out | ios::trunc);
 
    fout << "    addr => " << std::hex << "0x" << cmac_inst.cmac_csb2cmac_addr << std::endl; 
    // fout << "    step_num => " << std::dec << cmac_inst.cmac_step_num << std::endl; 
    // fout << "    cmac_cmac_a_state => " << std::dec << cmac_inst.cmac_cmac_a_state << std::endl; 
    // fout << "    done_with_computation => " << std::boolalpha << cmac_inst.cmac_done_with_computation << std::endl; 
    // fout << "    cmac_cmac_partial_sum_rdy => " << std::boolalpha << cmac_inst.cmac_cmac_partial_sum_rdy << std::endl; 
    // fout << std::endl; 

    // fout << "    cmac_csc_data_int16 => " << std::hex << "0x" << cmac_inst.cmac_csc_data_int16 << std::endl; 
    // fout << std::endl; 

    // fout << "    cmac_partial_sum_0 => " << std::hex << "0x" << cmac_inst.cmac_partial_sum_0 << std::endl; 
    // fout << "    cmac_partial_sum_1 => " << std::hex << "0x" << cmac_inst.cmac_partial_sum_1 << std::endl; 
    // fout << "    cmac_partial_sum_2 => " << std::hex << "0x" << cmac_inst.cmac_partial_sum_2 << std::endl; 
    // fout << "    cmac_partial_sum_3 => " << std::hex << "0x" << cmac_inst.cmac_partial_sum_3 << std::endl; 
    // fout << "    cmac_partial_sum_4 => " << std::hex << "0x" << cmac_inst.cmac_partial_sum_4 << std::endl; 
    // fout << "    cmac_partial_sum_5 => " << std::hex << "0x" << cmac_inst.cmac_partial_sum_5 << std::endl; 
    // fout << "    cmac_partial_sum_6 => " << std::hex << "0x" << cmac_inst.cmac_partial_sum_6 << std::endl; 
    // fout << "    cmac_partial_sum_7 => " << std::hex << "0x" << cmac_inst.cmac_partial_sum_7 << std::endl; 
    // fout << "    cmac_partial_sum_8 => " << std::hex << "0x" << cmac_inst.cmac_partial_sum_8 << std::endl; 
    // fout << "    cmac_partial_sum_9 => " << std::hex << "0x" << cmac_inst.cmac_partial_sum_9 << std::endl; 
    // fout << "    cmac_partial_sum_10 => " << std::hex << "0x" << cmac_inst.cmac_partial_sum_10 << std::endl; 
    // fout << "    cmac_partial_sum_11 => " << std::hex << "0x" << cmac_inst.cmac_partial_sum_11 << std::endl; 
    // fout << "    cmac_partial_sum_12 => " << std::hex << "0x" << cmac_inst.cmac_partial_sum_12 << std::endl; 
    // fout << "    cmac_partial_sum_13 => " << std::hex << "0x" << cmac_inst.cmac_partial_sum_13 << std::endl; 
    // fout << "    cmac_partial_sum_14 => " << std::hex << "0x" << cmac_inst.cmac_partial_sum_14 << std::endl; 
    // fout << "    cmac_partial_sum_15 => " << std::hex << "0x" << cmac_inst.cmac_partial_sum_15 << std::endl; 
    // fout << std::endl; 

    // fout << "    cmac_cmac_weight_0 => " << std::hex << "0x" << cmac_inst.cmac_cmac_weight_0 << std::endl; 
    // fout << "    cmac_cmac_weight_1 => " << std::hex << "0x" << cmac_inst.cmac_cmac_weight_1 << std::endl; 
    // fout << "    cmac_cmac_weight_2 => " << std::hex << "0x" << cmac_inst.cmac_cmac_weight_2 << std::endl; 
    // fout << "    cmac_cmac_weight_3 => " << std::hex << "0x" << cmac_inst.cmac_cmac_weight_3 << std::endl; 
    // fout << "    cmac_cmac_weight_4 => " << std::hex << "0x" << cmac_inst.cmac_cmac_weight_4 << std::endl; 
    // fout << "    cmac_cmac_weight_5 => " << std::hex << "0x" << cmac_inst.cmac_cmac_weight_5 << std::endl; 
    // fout << "    cmac_cmac_weight_6 => " << std::hex << "0x" << cmac_inst.cmac_cmac_weight_6 << std::endl; 
    // fout << "    cmac_cmac_weight_7 => " << std::hex << "0x" << cmac_inst.cmac_cmac_weight_7 << std::endl; 
    // fout << "    cmac_cmac_weight_8 => " << std::hex << "0x" << cmac_inst.cmac_cmac_weight_8 << std::endl; 
    // fout << "    cmac_cmac_weight_9 => " << std::hex << "0x" << cmac_inst.cmac_cmac_weight_9 << std::endl; 
    // fout << "    cmac_cmac_weight_10 => " << std::hex << "0x" << cmac_inst.cmac_cmac_weight_10 << std::endl; 
    // fout << "    cmac_cmac_weight_11 => " << std::hex << "0x" << cmac_inst.cmac_cmac_weight_11 << std::endl; 
    // fout << "    cmac_cmac_weight_12 => " << std::hex << "0x" << cmac_inst.cmac_cmac_weight_12 << std::endl; 
    // fout << "    cmac_cmac_weight_13 => " << std::hex << "0x" << cmac_inst.cmac_cmac_weight_13 << std::endl; 
    // fout << "    cmac_cmac_weight_14 => " << std::hex << "0x" << cmac_inst.cmac_cmac_weight_14 << std::endl; 
    // fout << "    cmac_cmac_weight_15 => " << std::hex << "0x" << cmac_inst.cmac_cmac_weight_15 << std::endl;
    

    fout.close();
    std::cout << "outputs have been stored at " << file_out << std::endl;

    wait(100000, SC_NS);
    std::cout << '\n' << std::endl;
    std::cout << "************* sc_stop **************" << std::endl;

    cmac_inst.instr_log.close();
    sc_stop(); 

  }
};

int sc_main(int argc, char *argv[]) {
  if (argc != 3) {
      std::cout << "Usage: my_driver [prog_frag_in_path] [result_out_dump_path]" << std::endl;
      return 0;
  } else {
      file_in = argv[1];
      file_out = argv[2];
  }

  // Dummy ports

  sc_signal <bool> cmac_csc2cmac_sending_last_batch_main;
  sc_signal <bool> cmac_csc2cmac_vld_main;
  sc_signal <bool> cmac_csc2cmac_reuse_weights_main;
  sc_signal <sc_biguint<8>> cmac_csc2cmac_status_main;
  sc_signal <sc_biguint<1024>> cmac_csc2cmac_feature_kernel_main;

  sc_signal <sc_biguint<1024>> cmac_csc2cmac_weight_kernel_15_main;
  sc_signal <sc_biguint<1024>> cmac_csc2cmac_weight_kernel_14_main;
  sc_signal <sc_biguint<1024>> cmac_csc2cmac_weight_kernel_13_main;
  sc_signal <sc_biguint<1024>> cmac_csc2cmac_weight_kernel_12_main;
  sc_signal <sc_biguint<1024>> cmac_csc2cmac_weight_kernel_11_main;
  sc_signal <sc_biguint<1024>> cmac_csc2cmac_weight_kernel_10_main;
  sc_signal <sc_biguint<1024>> cmac_csc2cmac_weight_kernel_9_main;
  sc_signal <sc_biguint<1024>> cmac_csc2cmac_weight_kernel_0_main;
  sc_signal <sc_biguint<1024>> cmac_csc2cmac_weight_kernel_1_main;
  sc_signal <sc_biguint<1024>> cmac_csc2cmac_weight_kernel_2_main;
  sc_signal <sc_biguint<1024>> cmac_csc2cmac_weight_kernel_3_main;
  sc_signal <sc_biguint<1024>> cmac_csc2cmac_weight_kernel_4_main;
  sc_signal <sc_biguint<1024>> cmac_csc2cmac_weight_kernel_5_main;
  sc_signal <sc_biguint<1024>> cmac_csc2cmac_weight_kernel_6_main;
  sc_signal <sc_biguint<1024>> cmac_csc2cmac_weight_kernel_7_main;
  sc_signal <sc_biguint<1024>> cmac_csc2cmac_weight_kernel_8_main;

  sc_signal <sc_biguint<16>> cmac_csb2cmac_addr_main;
  sc_signal <sc_biguint<32>> cmac_csb2cmac_data_main;
  sc_signal <sc_biguint<1>> cmac_csb2cmac_write_main;
  sc_signal <sc_biguint<1>> cmac_csb2cmac_vld_main;

  sc_signal < sc_biguint<1> > input_done_main;

  // Begin simulation
  std::cout << "test start" << std::endl;
  testbench tb("tb");

  
  // Linking to dummy ports

    tb.cmac_csc2cmac_sending_last_batch_signal(cmac_csc2cmac_sending_last_batch_main); 
    tb.cmac_csc2cmac_vld_signal(cmac_csc2cmac_vld_main);
    tb.cmac_csc2cmac_reuse_weights_signal(cmac_csc2cmac_reuse_weights_main);
    tb.cmac_csc2cmac_status_signal(cmac_csc2cmac_status_main);
    tb.cmac_csc2cmac_feature_kernel_signal(cmac_csc2cmac_feature_kernel_main);

    tb.cmac_csc2cmac_weight_kernel_15_signal(cmac_csc2cmac_weight_kernel_15_main);
    tb.cmac_csc2cmac_weight_kernel_14_signal(cmac_csc2cmac_weight_kernel_14_main);
    tb.cmac_csc2cmac_weight_kernel_13_signal(cmac_csc2cmac_weight_kernel_13_main);
    tb.cmac_csc2cmac_weight_kernel_12_signal(cmac_csc2cmac_weight_kernel_12_main);

    tb.cmac_csc2cmac_weight_kernel_11_signal(cmac_csc2cmac_weight_kernel_11_main);
    tb.cmac_csc2cmac_weight_kernel_10_signal(cmac_csc2cmac_weight_kernel_10_main);
    tb.cmac_csc2cmac_weight_kernel_9_signal(cmac_csc2cmac_weight_kernel_9_main);
    tb.cmac_csc2cmac_weight_kernel_0_signal(cmac_csc2cmac_weight_kernel_0_main);

    tb.cmac_csc2cmac_weight_kernel_1_signal(cmac_csc2cmac_weight_kernel_1_main);
    tb.cmac_csc2cmac_weight_kernel_2_signal(cmac_csc2cmac_weight_kernel_2_main);
    tb.cmac_csc2cmac_weight_kernel_3_signal(cmac_csc2cmac_weight_kernel_3_main);
    tb.cmac_csc2cmac_weight_kernel_4_signal(cmac_csc2cmac_weight_kernel_4_main);

    tb.cmac_csc2cmac_weight_kernel_5_signal(cmac_csc2cmac_weight_kernel_5_main);
    tb.cmac_csc2cmac_weight_kernel_6_signal(cmac_csc2cmac_weight_kernel_6_main);
    tb.cmac_csc2cmac_weight_kernel_7_signal(cmac_csc2cmac_weight_kernel_7_main);
    tb.cmac_csc2cmac_weight_kernel_8_signal(cmac_csc2cmac_weight_kernel_8_main);

    tb.cmac_csb2cmac_addr_signal(cmac_csb2cmac_addr_main);
    tb.cmac_csb2cmac_data_signal(cmac_csb2cmac_data_main);
    tb.cmac_csb2cmac_write_signal(cmac_csb2cmac_write_main);
    tb.cmac_csb2cmac_vld_signal(cmac_csb2cmac_vld_main);

  tb.input_done(input_done_main);

  sc_start();

  return 0;

}


