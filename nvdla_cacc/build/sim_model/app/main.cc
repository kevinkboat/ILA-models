#include <cacc.h>
#include <systemc>
#include <iostream>
#include <sstream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdio>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

#define NUM_OUTPUTS_PER_MAC_CELL 8

#define GET_JSON_INT(json_val, default_val) (!(json_val.is_null()) ? json_val.get<int>() : default_val)
#define GET_JSON_INT_FROM_HEX_STR(json_val, default_val) (!(json_val.is_null()) ? (std::stoi(json_val.get<std::string>().c_str(), nullptr, 16)) : default_val)
#define GET_JSON_BOOL(json_val, default_val) (!(json_val.is_null()) ? json_val.get<bool>() : default_val)

std::string file_in;
std::string file_out;
std::ofstream fout;

#define NVDLA_CONV_MAX_STRIPE_LEN         32
#define PRINT_NUM_WIDTH                   1

// Print assembly sub group
void print_assembly_subgroup(int num,  std::unordered_map<int, sc_biguint<48>, MemAddrHashFunc> data_addr){ 
  fout << "asm_kernel_" << std::dec << num << " ";
  for (int i = 0; i < NVDLA_CONV_MAX_STRIPE_LEN; i++){
    fout << std::dec << std::setw(PRINT_NUM_WIDTH) << (sc_dt::sc_bigint<48>) data_addr[i] << " ";
  }
  fout << std::endl;
}

// Print assembly sub group
void print_delivery_subgroup(int num,  std::unordered_map<int, sc_biguint<32>, MemAddrHashFunc> data_addr){ 
  fout << "delivery_group_" << std::dec << num << " ";
  for (int i = 0; i < NVDLA_CONV_MAX_STRIPE_LEN; i++){
    fout << std::dec << std::setw(PRINT_NUM_WIDTH) << (sc_dt::sc_bigint<32>) data_addr[i] << " ";
  }
  fout << std::endl;
} 

// Module for reading inputs into ILA model
SC_MODULE(Source) {
  sc_in<bool> clk{"clk"};
  sc_out< sc_biguint<1> > input_done;

  // CSB inputs
  sc_out<sc_biguint<16>> cacc_csb2cacc_addr;
  sc_out<sc_biguint<32>> cacc_csb2cacc_data;
  sc_out<bool> cacc_csb2cacc_write;
  sc_out<bool> cacc_csb2cacc_vld;

  // CMAC inputs
  sc_out<sc_biguint<2>> cacc_cmac2cacc_status;

  sc_out<sc_biguint<16>> cacc_cmac2cacc_ps_mac_0[NUM_OUTPUTS_PER_MAC_CELL];
  sc_out<sc_biguint<16>> cacc_cmac2cacc_ps_mac_1[NUM_OUTPUTS_PER_MAC_CELL];
  sc_out<sc_biguint<16>> cacc_cmac2cacc_ps_mac_2[NUM_OUTPUTS_PER_MAC_CELL];
  sc_out<sc_biguint<16>> cacc_cmac2cacc_ps_mac_3[NUM_OUTPUTS_PER_MAC_CELL];

  sc_out<sc_biguint<16>> cacc_cmac2cacc_ps_mac_4[NUM_OUTPUTS_PER_MAC_CELL];
  sc_out<sc_biguint<16>> cacc_cmac2cacc_ps_mac_5[NUM_OUTPUTS_PER_MAC_CELL];
  sc_out<sc_biguint<16>> cacc_cmac2cacc_ps_mac_6[NUM_OUTPUTS_PER_MAC_CELL];
  sc_out<sc_biguint<16>> cacc_cmac2cacc_ps_mac_7[NUM_OUTPUTS_PER_MAC_CELL];

  sc_out<sc_biguint<16>> cacc_cmac2cacc_ps_mac_8[NUM_OUTPUTS_PER_MAC_CELL];
  sc_out<sc_biguint<16>> cacc_cmac2cacc_ps_mac_9[NUM_OUTPUTS_PER_MAC_CELL];
  sc_out<sc_biguint<16>> cacc_cmac2cacc_ps_mac_10[NUM_OUTPUTS_PER_MAC_CELL];
  sc_out<sc_biguint<16>> cacc_cmac2cacc_ps_mac_11[NUM_OUTPUTS_PER_MAC_CELL];

  sc_out<sc_biguint<16>> cacc_cmac2cacc_ps_mac_12[NUM_OUTPUTS_PER_MAC_CELL];
  sc_out<sc_biguint<16>> cacc_cmac2cacc_ps_mac_13[NUM_OUTPUTS_PER_MAC_CELL];
  sc_out<sc_biguint<16>> cacc_cmac2cacc_ps_mac_14[NUM_OUTPUTS_PER_MAC_CELL];
  sc_out<sc_biguint<16>> cacc_cmac2cacc_ps_mac_15[NUM_OUTPUTS_PER_MAC_CELL];

  SC_CTOR(Source) {
    SC_THREAD(source_input);
    sensitive << clk.pos();
  }

  void source_input() {
    // reset done signal
    input_done = 0;
    
    // read program fragment from file ports implicitly reset)
    std::ifstream fin;
    fin.open(file_in, ios::in);
    
    json cmd_seq;
    cmd_seq = json::parse(fin);
    
    // Pass the command to the ports
    for (size_t i = 0; i < cmd_seq["program fragment"].size(); i++) {
      cacc_csb2cacc_addr = GET_JSON_INT_FROM_HEX_STR(cmd_seq["program fragment"][i]["cacc_csb2cacc_addr"], 0);
      cacc_csb2cacc_data = GET_JSON_INT_FROM_HEX_STR(cmd_seq["program fragment"][i]["cacc_csb2cacc_data"], 0);
      cacc_csb2cacc_write = GET_JSON_BOOL(cmd_seq["program fragment"][i]["cacc_csb2cacc_write"], false);
      cacc_csb2cacc_vld = GET_JSON_BOOL(cmd_seq["program fragment"][i]["cacc_csb2cacc_vld"], false);
    
      cacc_cmac2cacc_status = GET_JSON_INT(cmd_seq["program fragment"][i]["cacc_cmac2cacc_status"], 0);
      // Read in array data
      for (size_t j = 0; j < NUM_OUTPUTS_PER_MAC_CELL; j++) {        
        cacc_cmac2cacc_ps_mac_0[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["cacc_cmac2cacc_ps_mac_0_" + std::to_string(j)], 0);
        cacc_cmac2cacc_ps_mac_1[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["cacc_cmac2cacc_ps_mac_1_" + std::to_string(j)], 0);
        cacc_cmac2cacc_ps_mac_2[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["cacc_cmac2cacc_ps_mac_2_" + std::to_string(j)], 0);
        cacc_cmac2cacc_ps_mac_3[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["cacc_cmac2cacc_ps_mac_3_" + std::to_string(j)], 0);
        
        cacc_cmac2cacc_ps_mac_4[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["cacc_cmac2cacc_ps_mac_4_" + std::to_string(j)], 0);
        cacc_cmac2cacc_ps_mac_5[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["cacc_cmac2cacc_ps_mac_5_" + std::to_string(j)], 0);
        cacc_cmac2cacc_ps_mac_6[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["cacc_cmac2cacc_ps_mac_6_" + std::to_string(j)], 0);
        cacc_cmac2cacc_ps_mac_7[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["cacc_cmac2cacc_ps_mac_7_" + std::to_string(j)], 0);
        
        cacc_cmac2cacc_ps_mac_8[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["cacc_cmac2cacc_ps_mac_8_" + std::to_string(j)], 0);
        cacc_cmac2cacc_ps_mac_9[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["cacc_cmac2cacc_ps_mac_9_" + std::to_string(j)], 0);
        cacc_cmac2cacc_ps_mac_10[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["cacc_cmac2cacc_ps_mac_10_" + std::to_string(j)], 0);       
        cacc_cmac2cacc_ps_mac_11[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["cacc_cmac2cacc_ps_mac_11_" + std::to_string(j)], 0);       
        
        cacc_cmac2cacc_ps_mac_12[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["cacc_cmac2cacc_ps_mac_12_" + std::to_string(j)], 0);       
        cacc_cmac2cacc_ps_mac_13[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["cacc_cmac2cacc_ps_mac_13_" + std::to_string(j)], 0);       
        cacc_cmac2cacc_ps_mac_14[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["cacc_cmac2cacc_ps_mac_14_" + std::to_string(j)], 0);       
        cacc_cmac2cacc_ps_mac_15[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["cacc_cmac2cacc_ps_mac_15_" + std::to_string(j)], 0);
      }

      wait(10, SC_NS);
    }

    input_done = 1;
    std::cout << "read inputs from: " << file_in << std::endl;
    std::cout << std::endl;

  }

};

// Link input data to SystemC model
SC_MODULE(testbench) {
  cacc cacc_inst;
  Source src;
  
  sc_clock clk;
  sc_signal<sc_biguint<1>> input_done;

  sc_signal<sc_biguint<16>> cacc_csb2cacc_addr_signal;
  sc_signal<sc_biguint<32>> cacc_csb2cacc_data_signal;
  sc_signal<bool> cacc_csb2cacc_write_signal;
  sc_signal<bool> cacc_csb2cacc_vld_signal;

  sc_signal<sc_biguint<2>> cacc_cmac2cacc_status_signal;

  sc_signal<sc_biguint<16>> cacc_cmac2cacc_ps_mac_0_signal[NUM_OUTPUTS_PER_MAC_CELL];
  sc_signal<sc_biguint<16>> cacc_cmac2cacc_ps_mac_1_signal[NUM_OUTPUTS_PER_MAC_CELL];
  sc_signal<sc_biguint<16>> cacc_cmac2cacc_ps_mac_2_signal[NUM_OUTPUTS_PER_MAC_CELL];
  sc_signal<sc_biguint<16>> cacc_cmac2cacc_ps_mac_3_signal[NUM_OUTPUTS_PER_MAC_CELL];

  sc_signal<sc_biguint<16>> cacc_cmac2cacc_ps_mac_4_signal[NUM_OUTPUTS_PER_MAC_CELL];
  sc_signal<sc_biguint<16>> cacc_cmac2cacc_ps_mac_5_signal[NUM_OUTPUTS_PER_MAC_CELL];
  sc_signal<sc_biguint<16>> cacc_cmac2cacc_ps_mac_6_signal[NUM_OUTPUTS_PER_MAC_CELL];
  sc_signal<sc_biguint<16>> cacc_cmac2cacc_ps_mac_7_signal[NUM_OUTPUTS_PER_MAC_CELL];

  sc_signal<sc_biguint<16>> cacc_cmac2cacc_ps_mac_8_signal[NUM_OUTPUTS_PER_MAC_CELL];
  sc_signal<sc_biguint<16>> cacc_cmac2cacc_ps_mac_9_signal[NUM_OUTPUTS_PER_MAC_CELL];
  sc_signal<sc_biguint<16>> cacc_cmac2cacc_ps_mac_10_signal[NUM_OUTPUTS_PER_MAC_CELL];
  sc_signal<sc_biguint<16>> cacc_cmac2cacc_ps_mac_11_signal[NUM_OUTPUTS_PER_MAC_CELL];

  sc_signal<sc_biguint<16>> cacc_cmac2cacc_ps_mac_12_signal[NUM_OUTPUTS_PER_MAC_CELL];
  sc_signal<sc_biguint<16>> cacc_cmac2cacc_ps_mac_13_signal[NUM_OUTPUTS_PER_MAC_CELL];
  sc_signal<sc_biguint<16>> cacc_cmac2cacc_ps_mac_14_signal[NUM_OUTPUTS_PER_MAC_CELL];
  sc_signal<sc_biguint<16>> cacc_cmac2cacc_ps_mac_15_signal[NUM_OUTPUTS_PER_MAC_CELL];

  SC_CTOR(testbench) :
    clk("clk", 1, SC_NS),
    cacc_inst("cacc_inst"),
    src("source")
  {
    // Read in signals from the prog_frag file
    src.clk(clk);
  
    src.cacc_csb2cacc_addr(cacc_csb2cacc_addr_signal);
    src.cacc_csb2cacc_data(cacc_csb2cacc_data_signal);
    src.cacc_csb2cacc_write(cacc_csb2cacc_write_signal);
    src.cacc_csb2cacc_vld(cacc_csb2cacc_vld_signal);

    src.cacc_cmac2cacc_status(cacc_cmac2cacc_status_signal);

    for (size_t i = 0; i < NUM_OUTPUTS_PER_MAC_CELL; i++) { 
      src.cacc_cmac2cacc_ps_mac_0[i](cacc_cmac2cacc_ps_mac_0_signal[i]);
      src.cacc_cmac2cacc_ps_mac_1[i](cacc_cmac2cacc_ps_mac_1_signal[i]);
      src.cacc_cmac2cacc_ps_mac_2[i](cacc_cmac2cacc_ps_mac_2_signal[i]);
      src.cacc_cmac2cacc_ps_mac_3[i](cacc_cmac2cacc_ps_mac_3_signal[i]);

      src.cacc_cmac2cacc_ps_mac_4[i](cacc_cmac2cacc_ps_mac_4_signal[i]);
      src.cacc_cmac2cacc_ps_mac_5[i](cacc_cmac2cacc_ps_mac_5_signal[i]);
      src.cacc_cmac2cacc_ps_mac_6[i](cacc_cmac2cacc_ps_mac_6_signal[i]);
      src.cacc_cmac2cacc_ps_mac_7[i](cacc_cmac2cacc_ps_mac_7_signal[i]);

      src.cacc_cmac2cacc_ps_mac_8[i](cacc_cmac2cacc_ps_mac_8_signal[i]);
      src.cacc_cmac2cacc_ps_mac_9[i](cacc_cmac2cacc_ps_mac_9_signal[i]);
      src.cacc_cmac2cacc_ps_mac_10[i](cacc_cmac2cacc_ps_mac_10_signal[i]);
      src.cacc_cmac2cacc_ps_mac_11[i](cacc_cmac2cacc_ps_mac_11_signal[i]);

      src.cacc_cmac2cacc_ps_mac_12[i](cacc_cmac2cacc_ps_mac_12_signal[i]);
      src.cacc_cmac2cacc_ps_mac_13[i](cacc_cmac2cacc_ps_mac_13_signal[i]);
      src.cacc_cmac2cacc_ps_mac_14[i](cacc_cmac2cacc_ps_mac_14_signal[i]);
      src.cacc_cmac2cacc_ps_mac_15[i](cacc_cmac2cacc_ps_mac_15_signal[i]);
    }

    src.input_done(input_done);

    // Link with the cacc_inst.h SystemC model
    cacc_inst.cacc_csb2cacc_addr_in(cacc_csb2cacc_addr_signal);
    cacc_inst.cacc_csb2cacc_data_in(cacc_csb2cacc_data_signal);
    cacc_inst.cacc_csb2cacc_write_in(cacc_csb2cacc_write_signal);
    cacc_inst.cacc_csb2cacc_vld_in(cacc_csb2cacc_vld_signal);

    cacc_inst.cacc_cmac2cacc_status_in(cacc_cmac2cacc_status_signal);

    cacc_inst.cacc_cmac2cacc_ps_mac_0_0_in(cacc_cmac2cacc_ps_mac_0_signal[0]);
    cacc_inst.cacc_cmac2cacc_ps_mac_0_1_in(cacc_cmac2cacc_ps_mac_0_signal[1]);
    cacc_inst.cacc_cmac2cacc_ps_mac_0_2_in(cacc_cmac2cacc_ps_mac_0_signal[2]);
    cacc_inst.cacc_cmac2cacc_ps_mac_0_3_in(cacc_cmac2cacc_ps_mac_0_signal[3]);
    cacc_inst.cacc_cmac2cacc_ps_mac_0_4_in(cacc_cmac2cacc_ps_mac_0_signal[4]);
    cacc_inst.cacc_cmac2cacc_ps_mac_0_5_in(cacc_cmac2cacc_ps_mac_0_signal[5]);
    cacc_inst.cacc_cmac2cacc_ps_mac_0_6_in(cacc_cmac2cacc_ps_mac_0_signal[6]);
    cacc_inst.cacc_cmac2cacc_ps_mac_0_7_in(cacc_cmac2cacc_ps_mac_0_signal[7]);

    cacc_inst.cacc_cmac2cacc_ps_mac_1_0_in(cacc_cmac2cacc_ps_mac_1_signal[0]);
    cacc_inst.cacc_cmac2cacc_ps_mac_1_1_in(cacc_cmac2cacc_ps_mac_1_signal[1]);
    cacc_inst.cacc_cmac2cacc_ps_mac_1_2_in(cacc_cmac2cacc_ps_mac_1_signal[2]);
    cacc_inst.cacc_cmac2cacc_ps_mac_1_3_in(cacc_cmac2cacc_ps_mac_1_signal[3]);
    cacc_inst.cacc_cmac2cacc_ps_mac_1_4_in(cacc_cmac2cacc_ps_mac_1_signal[4]);
    cacc_inst.cacc_cmac2cacc_ps_mac_1_5_in(cacc_cmac2cacc_ps_mac_1_signal[5]);
    cacc_inst.cacc_cmac2cacc_ps_mac_1_6_in(cacc_cmac2cacc_ps_mac_1_signal[6]);
    cacc_inst.cacc_cmac2cacc_ps_mac_1_7_in(cacc_cmac2cacc_ps_mac_1_signal[7]);

    cacc_inst.cacc_cmac2cacc_ps_mac_2_0_in(cacc_cmac2cacc_ps_mac_2_signal[0]);
    cacc_inst.cacc_cmac2cacc_ps_mac_2_1_in(cacc_cmac2cacc_ps_mac_2_signal[1]);
    cacc_inst.cacc_cmac2cacc_ps_mac_2_2_in(cacc_cmac2cacc_ps_mac_2_signal[2]);
    cacc_inst.cacc_cmac2cacc_ps_mac_2_3_in(cacc_cmac2cacc_ps_mac_2_signal[3]);
    cacc_inst.cacc_cmac2cacc_ps_mac_2_4_in(cacc_cmac2cacc_ps_mac_2_signal[4]);
    cacc_inst.cacc_cmac2cacc_ps_mac_2_5_in(cacc_cmac2cacc_ps_mac_2_signal[5]);
    cacc_inst.cacc_cmac2cacc_ps_mac_2_6_in(cacc_cmac2cacc_ps_mac_2_signal[6]);
    cacc_inst.cacc_cmac2cacc_ps_mac_2_7_in(cacc_cmac2cacc_ps_mac_2_signal[7]);

    cacc_inst.cacc_cmac2cacc_ps_mac_3_0_in(cacc_cmac2cacc_ps_mac_3_signal[0]);
    cacc_inst.cacc_cmac2cacc_ps_mac_3_1_in(cacc_cmac2cacc_ps_mac_3_signal[1]);
    cacc_inst.cacc_cmac2cacc_ps_mac_3_2_in(cacc_cmac2cacc_ps_mac_3_signal[2]);
    cacc_inst.cacc_cmac2cacc_ps_mac_3_3_in(cacc_cmac2cacc_ps_mac_3_signal[3]);
    cacc_inst.cacc_cmac2cacc_ps_mac_3_4_in(cacc_cmac2cacc_ps_mac_3_signal[4]);
    cacc_inst.cacc_cmac2cacc_ps_mac_3_5_in(cacc_cmac2cacc_ps_mac_3_signal[5]);
    cacc_inst.cacc_cmac2cacc_ps_mac_3_6_in(cacc_cmac2cacc_ps_mac_3_signal[6]);
    cacc_inst.cacc_cmac2cacc_ps_mac_3_7_in(cacc_cmac2cacc_ps_mac_3_signal[7]);

    cacc_inst.cacc_cmac2cacc_ps_mac_4_0_in(cacc_cmac2cacc_ps_mac_4_signal[0]);
    cacc_inst.cacc_cmac2cacc_ps_mac_4_1_in(cacc_cmac2cacc_ps_mac_4_signal[1]);
    cacc_inst.cacc_cmac2cacc_ps_mac_4_2_in(cacc_cmac2cacc_ps_mac_4_signal[2]);
    cacc_inst.cacc_cmac2cacc_ps_mac_4_3_in(cacc_cmac2cacc_ps_mac_4_signal[3]);
    cacc_inst.cacc_cmac2cacc_ps_mac_4_4_in(cacc_cmac2cacc_ps_mac_4_signal[4]);
    cacc_inst.cacc_cmac2cacc_ps_mac_4_5_in(cacc_cmac2cacc_ps_mac_4_signal[5]);
    cacc_inst.cacc_cmac2cacc_ps_mac_4_6_in(cacc_cmac2cacc_ps_mac_4_signal[6]);
    cacc_inst.cacc_cmac2cacc_ps_mac_4_7_in(cacc_cmac2cacc_ps_mac_4_signal[7]);

    cacc_inst.cacc_cmac2cacc_ps_mac_5_0_in(cacc_cmac2cacc_ps_mac_5_signal[0]);
    cacc_inst.cacc_cmac2cacc_ps_mac_5_1_in(cacc_cmac2cacc_ps_mac_5_signal[1]);
    cacc_inst.cacc_cmac2cacc_ps_mac_5_2_in(cacc_cmac2cacc_ps_mac_5_signal[2]);
    cacc_inst.cacc_cmac2cacc_ps_mac_5_3_in(cacc_cmac2cacc_ps_mac_5_signal[3]);
    cacc_inst.cacc_cmac2cacc_ps_mac_5_4_in(cacc_cmac2cacc_ps_mac_5_signal[4]);
    cacc_inst.cacc_cmac2cacc_ps_mac_5_5_in(cacc_cmac2cacc_ps_mac_5_signal[5]);
    cacc_inst.cacc_cmac2cacc_ps_mac_5_6_in(cacc_cmac2cacc_ps_mac_5_signal[6]);
    cacc_inst.cacc_cmac2cacc_ps_mac_5_7_in(cacc_cmac2cacc_ps_mac_5_signal[7]);

    cacc_inst.cacc_cmac2cacc_ps_mac_6_0_in(cacc_cmac2cacc_ps_mac_6_signal[0]);
    cacc_inst.cacc_cmac2cacc_ps_mac_6_1_in(cacc_cmac2cacc_ps_mac_6_signal[1]);
    cacc_inst.cacc_cmac2cacc_ps_mac_6_2_in(cacc_cmac2cacc_ps_mac_6_signal[2]);
    cacc_inst.cacc_cmac2cacc_ps_mac_6_3_in(cacc_cmac2cacc_ps_mac_6_signal[3]);
    cacc_inst.cacc_cmac2cacc_ps_mac_6_4_in(cacc_cmac2cacc_ps_mac_6_signal[4]);
    cacc_inst.cacc_cmac2cacc_ps_mac_6_5_in(cacc_cmac2cacc_ps_mac_6_signal[5]);
    cacc_inst.cacc_cmac2cacc_ps_mac_6_6_in(cacc_cmac2cacc_ps_mac_6_signal[6]);
    cacc_inst.cacc_cmac2cacc_ps_mac_6_7_in(cacc_cmac2cacc_ps_mac_6_signal[7]);

    cacc_inst.cacc_cmac2cacc_ps_mac_7_0_in(cacc_cmac2cacc_ps_mac_7_signal[0]);
    cacc_inst.cacc_cmac2cacc_ps_mac_7_1_in(cacc_cmac2cacc_ps_mac_7_signal[1]);
    cacc_inst.cacc_cmac2cacc_ps_mac_7_2_in(cacc_cmac2cacc_ps_mac_7_signal[2]);
    cacc_inst.cacc_cmac2cacc_ps_mac_7_3_in(cacc_cmac2cacc_ps_mac_7_signal[3]);
    cacc_inst.cacc_cmac2cacc_ps_mac_7_4_in(cacc_cmac2cacc_ps_mac_7_signal[4]);
    cacc_inst.cacc_cmac2cacc_ps_mac_7_5_in(cacc_cmac2cacc_ps_mac_7_signal[5]);
    cacc_inst.cacc_cmac2cacc_ps_mac_7_6_in(cacc_cmac2cacc_ps_mac_7_signal[6]);
    cacc_inst.cacc_cmac2cacc_ps_mac_7_7_in(cacc_cmac2cacc_ps_mac_7_signal[7]);

    cacc_inst.cacc_cmac2cacc_ps_mac_8_0_in(cacc_cmac2cacc_ps_mac_8_signal[0]);
    cacc_inst.cacc_cmac2cacc_ps_mac_8_1_in(cacc_cmac2cacc_ps_mac_8_signal[1]);
    cacc_inst.cacc_cmac2cacc_ps_mac_8_2_in(cacc_cmac2cacc_ps_mac_8_signal[2]);
    cacc_inst.cacc_cmac2cacc_ps_mac_8_3_in(cacc_cmac2cacc_ps_mac_8_signal[3]);
    cacc_inst.cacc_cmac2cacc_ps_mac_8_4_in(cacc_cmac2cacc_ps_mac_8_signal[4]);
    cacc_inst.cacc_cmac2cacc_ps_mac_8_5_in(cacc_cmac2cacc_ps_mac_8_signal[5]);
    cacc_inst.cacc_cmac2cacc_ps_mac_8_6_in(cacc_cmac2cacc_ps_mac_8_signal[6]);
    cacc_inst.cacc_cmac2cacc_ps_mac_8_7_in(cacc_cmac2cacc_ps_mac_8_signal[7]);

    cacc_inst.cacc_cmac2cacc_ps_mac_9_0_in(cacc_cmac2cacc_ps_mac_9_signal[0]);
    cacc_inst.cacc_cmac2cacc_ps_mac_9_1_in(cacc_cmac2cacc_ps_mac_9_signal[1]);
    cacc_inst.cacc_cmac2cacc_ps_mac_9_2_in(cacc_cmac2cacc_ps_mac_9_signal[2]);
    cacc_inst.cacc_cmac2cacc_ps_mac_9_3_in(cacc_cmac2cacc_ps_mac_9_signal[3]);
    cacc_inst.cacc_cmac2cacc_ps_mac_9_4_in(cacc_cmac2cacc_ps_mac_9_signal[4]);
    cacc_inst.cacc_cmac2cacc_ps_mac_9_5_in(cacc_cmac2cacc_ps_mac_9_signal[5]);
    cacc_inst.cacc_cmac2cacc_ps_mac_9_6_in(cacc_cmac2cacc_ps_mac_9_signal[6]);
    cacc_inst.cacc_cmac2cacc_ps_mac_9_7_in(cacc_cmac2cacc_ps_mac_9_signal[7]);

    cacc_inst.cacc_cmac2cacc_ps_mac_10_0_in(cacc_cmac2cacc_ps_mac_10_signal[0]);
    cacc_inst.cacc_cmac2cacc_ps_mac_10_1_in(cacc_cmac2cacc_ps_mac_10_signal[1]);
    cacc_inst.cacc_cmac2cacc_ps_mac_10_2_in(cacc_cmac2cacc_ps_mac_10_signal[2]);
    cacc_inst.cacc_cmac2cacc_ps_mac_10_3_in(cacc_cmac2cacc_ps_mac_10_signal[3]);
    cacc_inst.cacc_cmac2cacc_ps_mac_10_4_in(cacc_cmac2cacc_ps_mac_10_signal[4]);
    cacc_inst.cacc_cmac2cacc_ps_mac_10_5_in(cacc_cmac2cacc_ps_mac_10_signal[5]);
    cacc_inst.cacc_cmac2cacc_ps_mac_10_6_in(cacc_cmac2cacc_ps_mac_10_signal[6]);
    cacc_inst.cacc_cmac2cacc_ps_mac_10_7_in(cacc_cmac2cacc_ps_mac_10_signal[7]);

    cacc_inst.cacc_cmac2cacc_ps_mac_11_0_in(cacc_cmac2cacc_ps_mac_11_signal[0]);
    cacc_inst.cacc_cmac2cacc_ps_mac_11_1_in(cacc_cmac2cacc_ps_mac_11_signal[1]);
    cacc_inst.cacc_cmac2cacc_ps_mac_11_2_in(cacc_cmac2cacc_ps_mac_11_signal[2]);
    cacc_inst.cacc_cmac2cacc_ps_mac_11_3_in(cacc_cmac2cacc_ps_mac_11_signal[3]);
    cacc_inst.cacc_cmac2cacc_ps_mac_11_4_in(cacc_cmac2cacc_ps_mac_11_signal[4]);
    cacc_inst.cacc_cmac2cacc_ps_mac_11_5_in(cacc_cmac2cacc_ps_mac_11_signal[5]);
    cacc_inst.cacc_cmac2cacc_ps_mac_11_6_in(cacc_cmac2cacc_ps_mac_11_signal[6]);
    cacc_inst.cacc_cmac2cacc_ps_mac_11_7_in(cacc_cmac2cacc_ps_mac_11_signal[7]);

    cacc_inst.cacc_cmac2cacc_ps_mac_12_0_in(cacc_cmac2cacc_ps_mac_12_signal[0]);
    cacc_inst.cacc_cmac2cacc_ps_mac_12_1_in(cacc_cmac2cacc_ps_mac_12_signal[1]);
    cacc_inst.cacc_cmac2cacc_ps_mac_12_2_in(cacc_cmac2cacc_ps_mac_12_signal[2]);
    cacc_inst.cacc_cmac2cacc_ps_mac_12_3_in(cacc_cmac2cacc_ps_mac_12_signal[3]);
    cacc_inst.cacc_cmac2cacc_ps_mac_12_4_in(cacc_cmac2cacc_ps_mac_12_signal[4]);
    cacc_inst.cacc_cmac2cacc_ps_mac_12_5_in(cacc_cmac2cacc_ps_mac_12_signal[5]);
    cacc_inst.cacc_cmac2cacc_ps_mac_12_6_in(cacc_cmac2cacc_ps_mac_12_signal[6]);
    cacc_inst.cacc_cmac2cacc_ps_mac_12_7_in(cacc_cmac2cacc_ps_mac_12_signal[7]);

    cacc_inst.cacc_cmac2cacc_ps_mac_13_0_in(cacc_cmac2cacc_ps_mac_13_signal[0]);
    cacc_inst.cacc_cmac2cacc_ps_mac_13_1_in(cacc_cmac2cacc_ps_mac_13_signal[1]);
    cacc_inst.cacc_cmac2cacc_ps_mac_13_2_in(cacc_cmac2cacc_ps_mac_13_signal[2]);
    cacc_inst.cacc_cmac2cacc_ps_mac_13_3_in(cacc_cmac2cacc_ps_mac_13_signal[3]);
    cacc_inst.cacc_cmac2cacc_ps_mac_13_4_in(cacc_cmac2cacc_ps_mac_13_signal[4]);
    cacc_inst.cacc_cmac2cacc_ps_mac_13_5_in(cacc_cmac2cacc_ps_mac_13_signal[5]);
    cacc_inst.cacc_cmac2cacc_ps_mac_13_6_in(cacc_cmac2cacc_ps_mac_13_signal[6]);
    cacc_inst.cacc_cmac2cacc_ps_mac_13_7_in(cacc_cmac2cacc_ps_mac_13_signal[7]);

    cacc_inst.cacc_cmac2cacc_ps_mac_14_0_in(cacc_cmac2cacc_ps_mac_14_signal[0]);
    cacc_inst.cacc_cmac2cacc_ps_mac_14_1_in(cacc_cmac2cacc_ps_mac_14_signal[1]);
    cacc_inst.cacc_cmac2cacc_ps_mac_14_2_in(cacc_cmac2cacc_ps_mac_14_signal[2]);
    cacc_inst.cacc_cmac2cacc_ps_mac_14_3_in(cacc_cmac2cacc_ps_mac_14_signal[3]);
    cacc_inst.cacc_cmac2cacc_ps_mac_14_4_in(cacc_cmac2cacc_ps_mac_14_signal[4]);
    cacc_inst.cacc_cmac2cacc_ps_mac_14_5_in(cacc_cmac2cacc_ps_mac_14_signal[5]);
    cacc_inst.cacc_cmac2cacc_ps_mac_14_6_in(cacc_cmac2cacc_ps_mac_14_signal[6]);
    cacc_inst.cacc_cmac2cacc_ps_mac_14_7_in(cacc_cmac2cacc_ps_mac_14_signal[7]);

    cacc_inst.cacc_cmac2cacc_ps_mac_15_0_in(cacc_cmac2cacc_ps_mac_15_signal[0]);
    cacc_inst.cacc_cmac2cacc_ps_mac_15_1_in(cacc_cmac2cacc_ps_mac_15_signal[1]);
    cacc_inst.cacc_cmac2cacc_ps_mac_15_2_in(cacc_cmac2cacc_ps_mac_15_signal[2]);
    cacc_inst.cacc_cmac2cacc_ps_mac_15_3_in(cacc_cmac2cacc_ps_mac_15_signal[3]);
    cacc_inst.cacc_cmac2cacc_ps_mac_15_4_in(cacc_cmac2cacc_ps_mac_15_signal[4]);
    cacc_inst.cacc_cmac2cacc_ps_mac_15_5_in(cacc_cmac2cacc_ps_mac_15_signal[5]);
    cacc_inst.cacc_cmac2cacc_ps_mac_15_6_in(cacc_cmac2cacc_ps_mac_15_signal[6]);
    cacc_inst.cacc_cmac2cacc_ps_mac_15_7_in(cacc_cmac2cacc_ps_mac_15_signal[7]);

    SC_THREAD(run);
  }

  // Run the SystemC simuation and log outputs
  void run() {
    cacc_inst.instr_log.open("instr_log_conv.txt", ofstream::out | ofstream::trunc);
    cacc_inst.instr_update_log.open("instr_update_log_conv.txt", ios::out | ios::trunc);

    std::cout << "start running" << std::endl;
    std::cout << "*********** simulation start ***********" << std::endl;
    std::cout << std::endl;

    wait(10, SC_NS);

    // Log final outputs
    fout.open(file_out, ios::out | ios::trunc);

    int index = 0;

    while (input_done == 0) {
      // std::cout << "current simulation time: " << '\t' << sc_time_stamp() << "\r" << std::flush;

      fout << "current simulation time: " << '\t' << sc_time_stamp() << std::endl;
      fout << "instr No. " << std::dec << index++ << std::endl;
      
      fout << "(Output) cacc_cacc2csb_rdy = " << (bool) cacc_inst.cacc_cacc2csb_rdy << std::endl;
      fout << "(Output) cacc_cacc2csb_data_vld = " << (bool) cacc_inst.cacc_cacc2csb_data_vld << std::endl;

      bool group0_active = (cacc_inst.cacc_cacc_s_status & 0x10000) == 0;
      int num_batches = group0_active ? (int) cacc_inst.cacc_group0_cacc_d_batch_number: 
                                        (int) cacc_inst.cacc_group1_cacc_d_batch_number;
      fout << "(State) consumer_num_batches = " << std::dec << num_batches << std::endl;
      
      fout << "(State) cacc_cacc_s_status = 0x" << std::hex << cacc_inst.cacc_cacc_s_status << std::endl;
      fout << "(State) cacc_cacc_s_pointer = 0x" << std::hex << cacc_inst.cacc_cacc_s_pointer << std::endl;
      
      // fout << "(State) cacc_group0_cacc_d_out_saturation = " << std::dec << cacc_inst.cacc_group0_cacc_d_out_saturation << std::endl;
      // fout << "(State) cacc_group0_cacc_d_clip_cfg = " << cacc_inst.cacc_group0_cacc_d_clip_cfg << std::endl;
      fout << "(State) cacc_group0_cacc_d_op_enable = 0x" << cacc_inst.cacc_group0_cacc_d_op_enable << std::endl;
      // fout << "(State) cacc_group0_cacc_d_misc_cfg = " << cacc_inst.cacc_group0_cacc_d_misc_cfg << std::endl;
      // fout << "(State) cacc_group0_cacc_d_dataout_size_0 = " << cacc_inst.cacc_group0_cacc_d_dataout_size_0 << std::endl;
      // fout << "(State) cacc_group0_cacc_d_dataout_size_1 = " << cacc_inst.cacc_group0_cacc_d_dataout_size_1 << std::endl;
      // fout << "(State) cacc_group0_cacc_d_dataout_addr = " << cacc_inst.cacc_group0_cacc_d_dataout_addr << std::endl;
      fout << "(State) cacc_group0_cacc_d_batch_number = " << cacc_inst.cacc_group0_cacc_d_batch_number << std::endl;
      // fout << "(State) cacc_group0_cacc_d_line_stride = " << cacc_inst.cacc_group0_cacc_d_line_stride << std::endl;
      // fout << "(State) cacc_group0_cacc_d_surf_stride = " << cacc_inst.cacc_group0_cacc_d_surf_stride << std::endl;
      // fout << "(State) cacc_group0_cacc_d_dataout_map = " << cacc_inst.cacc_group0_cacc_d_dataout_map << std::endl;

      // fout << "(State) cacc_group1_cacc_d_out_saturation = " << cacc_inst.cacc_group1_cacc_d_out_saturation << std::endl;
      // fout << "(State) cacc_group1_cacc_d_clip_cfg = " << cacc_inst.cacc_group1_cacc_d_clip_cfg << std::endl;
      // fout << "(State) cacc_group1_cacc_d_dataout_map = " << cacc_inst.cacc_group1_cacc_d_dataout_map << std::endl;
      // fout << "(State) cacc_group1_cacc_d_surf_stride = " << cacc_inst.cacc_group1_cacc_d_surf_stride << std::endl;
      // fout << "(State) cacc_group1_cacc_d_line_stride = " << cacc_inst.cacc_group1_cacc_d_line_stride << std::endl;
      fout << "(State) cacc_group1_cacc_d_batch_number = " << cacc_inst.cacc_group1_cacc_d_batch_number << std::endl;
      // fout << "(State) cacc_group1_cacc_d_dataout_addr = " << cacc_inst.cacc_group1_cacc_d_dataout_addr << std::endl;
      // fout << "(State) cacc_group1_cacc_d_dataout_size_1 = " << cacc_inst.cacc_group1_cacc_d_dataout_size_1 << std::endl;
      // fout << "(State) cacc_group1_cacc_d_dataout_size_0 = " << cacc_inst.cacc_group1_cacc_d_dataout_size_0 << std::endl;
      fout << "(State) cacc_group1_cacc_d_op_enable = 0x" << cacc_inst.cacc_group1_cacc_d_op_enable << std::endl;
      // fout << "(State) cacc_group1_cacc_d_misc_cfg = " << cacc_inst.cacc_group1_cacc_d_misc_cfg << std::endl;
      fout << "(Debug) stripe_counter_pre_incr = " << std::dec << cacc_inst.cacc_tmp << std::endl;
      fout << "(State) stripe_counter_post_incr = " << std::dec << cacc_inst.cacc_stripe_counter << std::endl;


      print_assembly_subgroup(0, cacc_inst.cacc_assembly_kernel_0);
      print_assembly_subgroup(1, cacc_inst.cacc_assembly_kernel_1);  
      print_assembly_subgroup(2, cacc_inst.cacc_assembly_kernel_2);  
      print_assembly_subgroup(3, cacc_inst.cacc_assembly_kernel_3);  
      // print_assembly_subgroup(4, cacc_inst.cacc_assembly_kernel_4);  
      // print_assembly_subgroup(5, cacc_inst.cacc_assembly_kernel_5);  
      // print_assembly_subgroup(6, cacc_inst.cacc_assembly_kernel_6);  
      // print_assembly_subgroup(7, cacc_inst.cacc_assembly_kernel_7);  
      print_assembly_subgroup(8, cacc_inst.cacc_assembly_kernel_8);  
      print_assembly_subgroup(9, cacc_inst.cacc_assembly_kernel_9);  
      print_assembly_subgroup(10, cacc_inst.cacc_assembly_kernel_10);
      print_assembly_subgroup(11, cacc_inst.cacc_assembly_kernel_11);
      // print_assembly_subgroup(12, cacc_inst.cacc_assembly_kernel_12);
      // print_assembly_subgroup(13, cacc_inst.cacc_assembly_kernel_13);
      // print_assembly_subgroup(14, cacc_inst.cacc_assembly_kernel_14);
      // print_assembly_subgroup(15, cacc_inst.cacc_assembly_kernel_15);
      print_assembly_subgroup(16, cacc_inst.cacc_assembly_kernel_16);
      print_assembly_subgroup(17, cacc_inst.cacc_assembly_kernel_17);
      print_assembly_subgroup(18, cacc_inst.cacc_assembly_kernel_18);
      print_assembly_subgroup(19, cacc_inst.cacc_assembly_kernel_19);
      // print_assembly_subgroup(20, cacc_inst.cacc_assembly_kernel_20);
      // print_assembly_subgroup(21, cacc_inst.cacc_assembly_kernel_21);
      // print_assembly_subgroup(22, cacc_inst.cacc_assembly_kernel_22);
      // print_assembly_subgroup(23, cacc_inst.cacc_assembly_kernel_23);
      print_assembly_subgroup(24, cacc_inst.cacc_assembly_kernel_24);
      print_assembly_subgroup(25, cacc_inst.cacc_assembly_kernel_25);
      print_assembly_subgroup(26, cacc_inst.cacc_assembly_kernel_26);
      print_assembly_subgroup(27, cacc_inst.cacc_assembly_kernel_27);
      // print_assembly_subgroup(28, cacc_inst.cacc_assembly_kernel_28);
      // print_assembly_subgroup(29, cacc_inst.cacc_assembly_kernel_29);
      // print_assembly_subgroup(30, cacc_inst.cacc_assembly_kernel_30);
      // print_assembly_subgroup(31, cacc_inst.cacc_assembly_kernel_31);

      print_delivery_subgroup(0, cacc_inst.cacc_cacc_output_0);
      print_delivery_subgroup(1, cacc_inst.cacc_cacc_output_1);
      print_delivery_subgroup(2, cacc_inst.cacc_cacc_output_2);
      print_delivery_subgroup(3, cacc_inst.cacc_cacc_output_3);
      // print_delivery_subgroup(4, cacc_inst.cacc_cacc_output_4);
      // print_delivery_subgroup(5, cacc_inst.cacc_cacc_output_5);
      // print_delivery_subgroup(6, cacc_inst.cacc_cacc_output_6);
      // print_delivery_subgroup(7, cacc_inst.cacc_cacc_output_7);
      print_delivery_subgroup(8, cacc_inst.cacc_cacc_output_8);
      print_delivery_subgroup(9, cacc_inst.cacc_cacc_output_9);
      print_delivery_subgroup(10, cacc_inst.cacc_cacc_output_10);
      print_delivery_subgroup(11, cacc_inst.cacc_cacc_output_11);
      // print_delivery_subgroup(12, cacc_inst.cacc_cacc_output_12);
      // print_delivery_subgroup(13, cacc_inst.cacc_cacc_output_13);
      // print_delivery_subgroup(14, cacc_inst.cacc_cacc_output_14);
      // print_delivery_subgroup(15, cacc_inst.cacc_cacc_output_15);
      print_delivery_subgroup(16, cacc_inst.cacc_cacc_output_16);
      print_delivery_subgroup(17, cacc_inst.cacc_cacc_output_17);
      print_delivery_subgroup(18, cacc_inst.cacc_cacc_output_18);
      print_delivery_subgroup(19, cacc_inst.cacc_cacc_output_19);
      // print_delivery_subgroup(20, cacc_inst.cacc_cacc_output_20);
      // print_delivery_subgroup(21, cacc_inst.cacc_cacc_output_21);
      // print_delivery_subgroup(22, cacc_inst.cacc_cacc_output_22);
      // print_delivery_subgroup(23, cacc_inst.cacc_cacc_output_23);
      print_delivery_subgroup(24, cacc_inst.cacc_cacc_output_24);
      print_delivery_subgroup(25, cacc_inst.cacc_cacc_output_25);
      print_delivery_subgroup(26, cacc_inst.cacc_cacc_output_26);
      print_delivery_subgroup(27, cacc_inst.cacc_cacc_output_27);
      // print_delivery_subgroup(28, cacc_inst.cacc_cacc_output_28);
      // print_delivery_subgroup(29, cacc_inst.cacc_cacc_output_29);
      // print_delivery_subgroup(30, cacc_inst.cacc_cacc_output_30);
      // print_delivery_subgroup(31, cacc_inst.cacc_cacc_output_31);
      
      fout << std::endl;
            
      wait(10, SC_NS);
    }
    wait(1000, SC_NS);

    fout.close();

    std::cout << "stored outputs in: " << file_out << std::endl;

    wait(100000, SC_NS);
    std::cout << std::endl;
    std::cout << "************* sc_stop **************" << std::endl;

    cacc_inst.instr_log.close();
    sc_stop(); 

  }
};

int sc_main(int argc, char *argv[]) {
  if (argc != 3) {
      std::cout << "Usage: ./cacc [prog_frag_in_path] [result_out_dump_path]" << std::endl;
      return 0;
  } else {
      file_in = argv[1];
      file_out = argv[2];
  }

  // Begin simulation
  std::cout << "test start" << std::endl;
  testbench tb("tb");

  sc_start();

  return 0;

}

