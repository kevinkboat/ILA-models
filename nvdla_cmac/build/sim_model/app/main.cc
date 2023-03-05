#include <systemc>
#include <iostream>
#include <sstream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdio>

#include "nlohmann/json.hpp"
#include "cmac.h"

using json = nlohmann::json;


#define NUM_KERNEL_ELEM           64 
#define NUM_OUTPUTS_PER_MAC_CELL  4
#define DISABLE_TESTING           false

#define GET_JSON_INT(json_val, default_val) (!(json_val.is_null()) ? json_val.get<int>() : default_val)
#define GET_JSON_INT_FROM_HEX_STR(json_val, default_val) (!(json_val.is_null()) ? (std::stoi(json_val.get<std::string>().c_str(), nullptr, 16)) : default_val)
#define GET_JSON_BOOL(json_val, default_val) (!(json_val.is_null()) ? json_val.get<bool>() : default_val)

std::string file_in;
std::string file_out;
std::ofstream fout;

// Print line to file in the format: mac_<cell_num> out1 out2 out3 out4
void print_cell_output(int cell_num,  std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> data_addr){ 
  fout << "mac_" << std::dec << cell_num << " ";
  for (int i = 0; i < NUM_OUTPUTS_PER_MAC_CELL; i++){
    fout << std::dec << (sc_dt::sc_bigint<16>) data_addr[i] << " ";
  }
  fout << std::endl;
}

// Module for reading inputs into ILA model
SC_MODULE(Source) {
  sc_in<bool> clk{"clk"};

  // CSB inputs
  sc_out<sc_biguint<16>> cmac_csb2cmac_addr;
  sc_out<sc_biguint<32>> cmac_csb2cmac_data;
  sc_out<sc_biguint<1>> cmac_csb2cmac_write;
  sc_out<sc_biguint<1>> cmac_csb2cmac_vld;
  
  // CSC non-array inputs
  sc_out<sc_biguint<8>> cmac_csc2cmac_status;
  sc_out<bool> cmac_csc2cmac_reuse_weights;
  sc_out<bool> cmac_csc2cmac_vld;
  sc_out<bool> cmac_csc2cmac_sending_last_batch;

  // CSC array inputs
  sc_out<sc_biguint<16>> cmac_csc2cmac_ft[NUM_KERNEL_ELEM];
  
  sc_out<sc_biguint<16>> cmac_csc2cmac_wt_0[NUM_KERNEL_ELEM];
  sc_out<sc_biguint<16>> cmac_csc2cmac_wt_1[NUM_KERNEL_ELEM];
  sc_out<sc_biguint<16>> cmac_csc2cmac_wt_2[NUM_KERNEL_ELEM];
  sc_out<sc_biguint<16>> cmac_csc2cmac_wt_3[NUM_KERNEL_ELEM];

  sc_out<sc_biguint<16>> cmac_csc2cmac_wt_4[NUM_KERNEL_ELEM];
  sc_out<sc_biguint<16>> cmac_csc2cmac_wt_5[NUM_KERNEL_ELEM];
  sc_out<sc_biguint<16>> cmac_csc2cmac_wt_6[NUM_KERNEL_ELEM];
  sc_out<sc_biguint<16>> cmac_csc2cmac_wt_7[NUM_KERNEL_ELEM];
  
  sc_out<sc_biguint<16>> cmac_csc2cmac_wt_8[NUM_KERNEL_ELEM];
  sc_out<sc_biguint<16>> cmac_csc2cmac_wt_9[NUM_KERNEL_ELEM];
  sc_out<sc_biguint<16>> cmac_csc2cmac_wt_10[NUM_KERNEL_ELEM];
  sc_out<sc_biguint<16>> cmac_csc2cmac_wt_11[NUM_KERNEL_ELEM];
  
  sc_out<sc_biguint<16>> cmac_csc2cmac_wt_12[NUM_KERNEL_ELEM];
  sc_out<sc_biguint<16>> cmac_csc2cmac_wt_13[NUM_KERNEL_ELEM];
  sc_out<sc_biguint<16>> cmac_csc2cmac_wt_14[NUM_KERNEL_ELEM];
  sc_out<sc_biguint<16>> cmac_csc2cmac_wt_15[NUM_KERNEL_ELEM];
  
  sc_out< sc_biguint<1> > input_done;

  SC_CTOR(Source) {
    SC_THREAD(source_input);
    sensitive << clk.pos();
  }

  void source_input() {
    // reset the ports

    cmac_csb2cmac_addr = 0;
    cmac_csb2cmac_data = 0;
    cmac_csb2cmac_write = 0;
    cmac_csb2cmac_vld = 0;

    cmac_csc2cmac_status = 0;
    cmac_csc2cmac_reuse_weights = false;
    cmac_csc2cmac_vld = false;
    cmac_csc2cmac_sending_last_batch = false;

    std::fill(cmac_csc2cmac_ft, cmac_csc2cmac_ft + NUM_KERNEL_ELEM, 0);

    std::fill(cmac_csc2cmac_wt_0, cmac_csc2cmac_wt_0 + NUM_KERNEL_ELEM, 0);
    std::fill(cmac_csc2cmac_wt_1, cmac_csc2cmac_wt_1 + NUM_KERNEL_ELEM, 0);
    std::fill(cmac_csc2cmac_wt_2, cmac_csc2cmac_wt_2 + NUM_KERNEL_ELEM, 0);
    std::fill(cmac_csc2cmac_wt_3, cmac_csc2cmac_wt_3 + NUM_KERNEL_ELEM, 0);

    std::fill(cmac_csc2cmac_wt_4, cmac_csc2cmac_wt_4 + NUM_KERNEL_ELEM, 0);
    std::fill(cmac_csc2cmac_wt_5, cmac_csc2cmac_wt_5 + NUM_KERNEL_ELEM, 0);
    std::fill(cmac_csc2cmac_wt_6, cmac_csc2cmac_wt_6 + NUM_KERNEL_ELEM, 0);
    std::fill(cmac_csc2cmac_wt_7, cmac_csc2cmac_wt_7 + NUM_KERNEL_ELEM, 0);

    std::fill(cmac_csc2cmac_wt_8, cmac_csc2cmac_wt_8 + NUM_KERNEL_ELEM, 0);
    std::fill(cmac_csc2cmac_wt_9, cmac_csc2cmac_wt_9 + NUM_KERNEL_ELEM, 0);
    std::fill(cmac_csc2cmac_wt_10, cmac_csc2cmac_wt_10 + NUM_KERNEL_ELEM, 0);
    std::fill(cmac_csc2cmac_wt_11, cmac_csc2cmac_wt_11 + NUM_KERNEL_ELEM, 0);

    std::fill(cmac_csc2cmac_wt_12, cmac_csc2cmac_wt_12 + NUM_KERNEL_ELEM, 0);
    std::fill(cmac_csc2cmac_wt_13, cmac_csc2cmac_wt_13 + NUM_KERNEL_ELEM, 0);
    std::fill(cmac_csc2cmac_wt_14, cmac_csc2cmac_wt_14 + NUM_KERNEL_ELEM, 0);
    std::fill(cmac_csc2cmac_wt_15, cmac_csc2cmac_wt_15 + NUM_KERNEL_ELEM, 0);

    input_done = 0;
    
    // read program fragment from file
    std::ifstream fin;
    fin.open(file_in, ios::in);
    
    json cmd_seq;
    cmd_seq = json::parse(fin);
    
    // Pass the command to the ports
    for (size_t i = 0; i < cmd_seq["program fragment"].size(); i++) {
      cmac_csb2cmac_addr = GET_JSON_INT_FROM_HEX_STR(cmd_seq["program fragment"][i]["cmac_csb2cmac_addr"], 0);
      cmac_csb2cmac_data = GET_JSON_INT_FROM_HEX_STR(cmd_seq["program fragment"][i]["cmac_csb2cmac_data"], 0);
      cmac_csb2cmac_write = GET_JSON_INT(cmd_seq["program fragment"][i]["cmac_csb2cmac_write"], 0);
      cmac_csb2cmac_vld = GET_JSON_INT(cmd_seq["program fragment"][i]["cmac_csb2cmac_vld"], 0);
    
      cmac_csc2cmac_status = GET_JSON_INT(cmd_seq["program fragment"][i]["cmac_csc2cmac_status"], 0);
      cmac_csc2cmac_reuse_weights = GET_JSON_BOOL(cmd_seq["program fragment"][i]["cmac_csc2cmac_reuse_weights"], false);
      cmac_csc2cmac_vld = GET_JSON_BOOL(cmd_seq["program fragment"][i]["cmac_csc2cmac_vld"], false);
      cmac_csc2cmac_sending_last_batch = GET_JSON_BOOL(cmd_seq["program fragment"][i]["cmac_csc2cmac_sending_last_batch"], false);

      // Read in array data
      for (size_t j = 0; j < NUM_KERNEL_ELEM; j++) {
        cmac_csc2cmac_ft[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["cmac_csc2cmac_ft_" + std::to_string(j)], 0);
        
        cmac_csc2cmac_wt_0[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["cmac_csc2cmac_wt_0_" + std::to_string(j)], 0);
        cmac_csc2cmac_wt_1[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["cmac_csc2cmac_wt_1_" + std::to_string(j)], 0);
        cmac_csc2cmac_wt_2[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["cmac_csc2cmac_wt_2_" + std::to_string(j)], 0);
        cmac_csc2cmac_wt_3[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["cmac_csc2cmac_wt_3_" + std::to_string(j)], 0);

        cmac_csc2cmac_wt_4[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["cmac_csc2cmac_wt_4_" + std::to_string(j)], 0);
        cmac_csc2cmac_wt_5[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["cmac_csc2cmac_wt_5_" + std::to_string(j)], 0);
        cmac_csc2cmac_wt_6[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["cmac_csc2cmac_wt_6_" + std::to_string(j)], 0);
        cmac_csc2cmac_wt_7[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["cmac_csc2cmac_wt_7_" + std::to_string(j)], 0);
        
        cmac_csc2cmac_wt_8[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["cmac_csc2cmac_wt_8_" + std::to_string(j)], 0);
        cmac_csc2cmac_wt_9[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["cmac_csc2cmac_wt_9_" + std::to_string(j)], 0);
        cmac_csc2cmac_wt_10[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["cmac_csc2cmac_wt_10_" + std::to_string(j)], 0);
        cmac_csc2cmac_wt_11[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["cmac_csc2cmac_wt_11_" + std::to_string(j)], 0);
        
        cmac_csc2cmac_wt_12[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["cmac_csc2cmac_wt_12_" + std::to_string(j)], 0);
        cmac_csc2cmac_wt_13[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["cmac_csc2cmac_wt_13_" + std::to_string(j)], 0);
        cmac_csc2cmac_wt_14[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["cmac_csc2cmac_wt_14_" + std::to_string(j)], 0);
        cmac_csc2cmac_wt_15[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["cmac_csc2cmac_wt_15_" + std::to_string(j)], 0);
      }
    
      wait(10, SC_NS);
    }

    input_done = 1;
    std::cout << "read_file" << std::flush;
  }

};

// Link input data to SystemC model
SC_MODULE(testbench) {
  cmac cmac_inst;
  Source src;

  sc_clock clk;

  sc_signal<sc_biguint<16>> cmac_csb2cmac_addr_signal;
  sc_signal<sc_biguint<32>> cmac_csb2cmac_data_signal;
  sc_signal<sc_biguint<1>> cmac_csb2cmac_write_signal;
  sc_signal<sc_biguint<1>> cmac_csb2cmac_vld_signal;

  sc_signal<sc_biguint<8>> cmac_csc2cmac_status_signal;
  sc_signal<bool> cmac_csc2cmac_reuse_weights_signal;
  sc_signal<bool> cmac_csc2cmac_vld_signal;
  sc_signal<bool> cmac_csc2cmac_sending_last_batch_signal;
  
  sc_signal<sc_biguint<16>> cmac_csc2cmac_ft_signal[NUM_KERNEL_ELEM];
  
  sc_signal<sc_biguint<16>> cmac_csc2cmac_wt_0_signal[NUM_KERNEL_ELEM];
  sc_signal<sc_biguint<16>> cmac_csc2cmac_wt_1_signal[NUM_KERNEL_ELEM];
  sc_signal<sc_biguint<16>> cmac_csc2cmac_wt_2_signal[NUM_KERNEL_ELEM];
  sc_signal<sc_biguint<16>> cmac_csc2cmac_wt_3_signal[NUM_KERNEL_ELEM];

  sc_signal<sc_biguint<16>> cmac_csc2cmac_wt_4_signal[NUM_KERNEL_ELEM];
  sc_signal<sc_biguint<16>> cmac_csc2cmac_wt_5_signal[NUM_KERNEL_ELEM];
  sc_signal<sc_biguint<16>> cmac_csc2cmac_wt_6_signal[NUM_KERNEL_ELEM];
  sc_signal<sc_biguint<16>> cmac_csc2cmac_wt_7_signal[NUM_KERNEL_ELEM];
  
  sc_signal<sc_biguint<16>> cmac_csc2cmac_wt_8_signal[NUM_KERNEL_ELEM];
  sc_signal<sc_biguint<16>> cmac_csc2cmac_wt_9_signal[NUM_KERNEL_ELEM];
  sc_signal<sc_biguint<16>> cmac_csc2cmac_wt_10_signal[NUM_KERNEL_ELEM];
  sc_signal<sc_biguint<16>> cmac_csc2cmac_wt_11_signal[NUM_KERNEL_ELEM];
  
  sc_signal<sc_biguint<16>> cmac_csc2cmac_wt_12_signal[NUM_KERNEL_ELEM];
  sc_signal<sc_biguint<16>> cmac_csc2cmac_wt_13_signal[NUM_KERNEL_ELEM];
  sc_signal<sc_biguint<16>> cmac_csc2cmac_wt_14_signal[NUM_KERNEL_ELEM];
  sc_signal<sc_biguint<16>> cmac_csc2cmac_wt_15_signal[NUM_KERNEL_ELEM];

  sc_signal<sc_biguint<1>> input_done;

  SC_CTOR(testbench) :
    clk("clk", 1, SC_NS),
    cmac_inst("cmac_inst"),
    src("source")
  {
    // Read in signals from the prog_frag file
    src.clk(clk);

    src.cmac_csb2cmac_addr(cmac_csb2cmac_addr_signal);
    src.cmac_csb2cmac_data(cmac_csb2cmac_data_signal);
    src.cmac_csb2cmac_write(cmac_csb2cmac_write_signal);
    src.cmac_csb2cmac_vld(cmac_csb2cmac_vld_signal);

    src.cmac_csc2cmac_status(cmac_csc2cmac_status_signal);
    src.cmac_csc2cmac_reuse_weights(cmac_csc2cmac_reuse_weights_signal);
    src.cmac_csc2cmac_vld(cmac_csc2cmac_vld_signal);
    src.cmac_csc2cmac_sending_last_batch(cmac_csc2cmac_sending_last_batch_signal); 

    for (size_t i = 0; i < NUM_KERNEL_ELEM; i++) {      
      src.cmac_csc2cmac_ft[i](cmac_csc2cmac_ft_signal[i]);
  
      src.cmac_csc2cmac_wt_0[i](cmac_csc2cmac_wt_0_signal[i]);
      src.cmac_csc2cmac_wt_1[i](cmac_csc2cmac_wt_1_signal[i]);
      src.cmac_csc2cmac_wt_2[i](cmac_csc2cmac_wt_2_signal[i]);
      src.cmac_csc2cmac_wt_3[i](cmac_csc2cmac_wt_3_signal[i]);

      src.cmac_csc2cmac_wt_4[i](cmac_csc2cmac_wt_4_signal[i]);
      src.cmac_csc2cmac_wt_5[i](cmac_csc2cmac_wt_5_signal[i]);
      src.cmac_csc2cmac_wt_6[i](cmac_csc2cmac_wt_6_signal[i]);
      src.cmac_csc2cmac_wt_7[i](cmac_csc2cmac_wt_7_signal[i]);

      src.cmac_csc2cmac_wt_8[i](cmac_csc2cmac_wt_8_signal[i]);
      src.cmac_csc2cmac_wt_9[i](cmac_csc2cmac_wt_9_signal[i]);
      src.cmac_csc2cmac_wt_10[i](cmac_csc2cmac_wt_10_signal[i]);
      src.cmac_csc2cmac_wt_11[i](cmac_csc2cmac_wt_11_signal[i]);

      src.cmac_csc2cmac_wt_12[i](cmac_csc2cmac_wt_12_signal[i]);
      src.cmac_csc2cmac_wt_13[i](cmac_csc2cmac_wt_13_signal[i]);
      src.cmac_csc2cmac_wt_14[i](cmac_csc2cmac_wt_14_signal[i]);
      src.cmac_csc2cmac_wt_15[i](cmac_csc2cmac_wt_15_signal[i]);
    }

    src.input_done(input_done);

    // Link with the cmac.h SystemC model

    cmac_inst.cmac_csb2cmac_addr_in(cmac_csb2cmac_addr_signal);
    cmac_inst.cmac_csb2cmac_data_in(cmac_csb2cmac_data_signal);
    cmac_inst.cmac_csb2cmac_write_in(cmac_csb2cmac_write_signal);
    cmac_inst.cmac_csb2cmac_vld_in(cmac_csb2cmac_vld_signal);

    cmac_inst.cmac_csc2cmac_status_in(cmac_csc2cmac_status_signal);
    cmac_inst.cmac_csc2cmac_reuse_weights_in(cmac_csc2cmac_reuse_weights_signal);
    cmac_inst.cmac_csc2cmac_vld_in(cmac_csc2cmac_vld_signal);
    cmac_inst.cmac_csc2cmac_sending_last_batch_in(cmac_csc2cmac_sending_last_batch_signal); 

    cmac_inst.cmac_csc2cmac_ft_0_in(cmac_csc2cmac_ft_signal[0]);
    cmac_inst.cmac_csc2cmac_ft_1_in(cmac_csc2cmac_ft_signal[1]);
    cmac_inst.cmac_csc2cmac_ft_2_in(cmac_csc2cmac_ft_signal[2]);
    cmac_inst.cmac_csc2cmac_ft_3_in(cmac_csc2cmac_ft_signal[3]);
    cmac_inst.cmac_csc2cmac_ft_4_in(cmac_csc2cmac_ft_signal[4]);
    cmac_inst.cmac_csc2cmac_ft_5_in(cmac_csc2cmac_ft_signal[5]);
    cmac_inst.cmac_csc2cmac_ft_6_in(cmac_csc2cmac_ft_signal[6]);
    cmac_inst.cmac_csc2cmac_ft_7_in(cmac_csc2cmac_ft_signal[7]);
    cmac_inst.cmac_csc2cmac_ft_8_in(cmac_csc2cmac_ft_signal[8]);
    cmac_inst.cmac_csc2cmac_ft_9_in(cmac_csc2cmac_ft_signal[9]);
    cmac_inst.cmac_csc2cmac_ft_10_in(cmac_csc2cmac_ft_signal[10]);
    cmac_inst.cmac_csc2cmac_ft_11_in(cmac_csc2cmac_ft_signal[11]);
    cmac_inst.cmac_csc2cmac_ft_12_in(cmac_csc2cmac_ft_signal[12]);
    cmac_inst.cmac_csc2cmac_ft_13_in(cmac_csc2cmac_ft_signal[13]);
    cmac_inst.cmac_csc2cmac_ft_14_in(cmac_csc2cmac_ft_signal[14]);
    cmac_inst.cmac_csc2cmac_ft_15_in(cmac_csc2cmac_ft_signal[15]);
    cmac_inst.cmac_csc2cmac_ft_16_in(cmac_csc2cmac_ft_signal[16]);
    cmac_inst.cmac_csc2cmac_ft_17_in(cmac_csc2cmac_ft_signal[17]);
    cmac_inst.cmac_csc2cmac_ft_18_in(cmac_csc2cmac_ft_signal[18]);
    cmac_inst.cmac_csc2cmac_ft_19_in(cmac_csc2cmac_ft_signal[19]);
    cmac_inst.cmac_csc2cmac_ft_20_in(cmac_csc2cmac_ft_signal[20]);
    cmac_inst.cmac_csc2cmac_ft_21_in(cmac_csc2cmac_ft_signal[21]);
    cmac_inst.cmac_csc2cmac_ft_22_in(cmac_csc2cmac_ft_signal[22]);
    cmac_inst.cmac_csc2cmac_ft_23_in(cmac_csc2cmac_ft_signal[23]);
    cmac_inst.cmac_csc2cmac_ft_24_in(cmac_csc2cmac_ft_signal[24]);
    cmac_inst.cmac_csc2cmac_ft_25_in(cmac_csc2cmac_ft_signal[25]);
    cmac_inst.cmac_csc2cmac_ft_26_in(cmac_csc2cmac_ft_signal[26]);
    cmac_inst.cmac_csc2cmac_ft_27_in(cmac_csc2cmac_ft_signal[27]);
    cmac_inst.cmac_csc2cmac_ft_28_in(cmac_csc2cmac_ft_signal[28]);
    cmac_inst.cmac_csc2cmac_ft_29_in(cmac_csc2cmac_ft_signal[29]);
    cmac_inst.cmac_csc2cmac_ft_30_in(cmac_csc2cmac_ft_signal[30]);
    cmac_inst.cmac_csc2cmac_ft_31_in(cmac_csc2cmac_ft_signal[31]);
    cmac_inst.cmac_csc2cmac_ft_32_in(cmac_csc2cmac_ft_signal[32]);
    cmac_inst.cmac_csc2cmac_ft_33_in(cmac_csc2cmac_ft_signal[33]);
    cmac_inst.cmac_csc2cmac_ft_34_in(cmac_csc2cmac_ft_signal[34]);
    cmac_inst.cmac_csc2cmac_ft_35_in(cmac_csc2cmac_ft_signal[35]);
    cmac_inst.cmac_csc2cmac_ft_36_in(cmac_csc2cmac_ft_signal[36]);
    cmac_inst.cmac_csc2cmac_ft_37_in(cmac_csc2cmac_ft_signal[37]);
    cmac_inst.cmac_csc2cmac_ft_38_in(cmac_csc2cmac_ft_signal[38]);
    cmac_inst.cmac_csc2cmac_ft_39_in(cmac_csc2cmac_ft_signal[39]);
    cmac_inst.cmac_csc2cmac_ft_40_in(cmac_csc2cmac_ft_signal[40]);
    cmac_inst.cmac_csc2cmac_ft_41_in(cmac_csc2cmac_ft_signal[41]);
    cmac_inst.cmac_csc2cmac_ft_42_in(cmac_csc2cmac_ft_signal[42]);
    cmac_inst.cmac_csc2cmac_ft_43_in(cmac_csc2cmac_ft_signal[43]);
    cmac_inst.cmac_csc2cmac_ft_44_in(cmac_csc2cmac_ft_signal[44]);
    cmac_inst.cmac_csc2cmac_ft_45_in(cmac_csc2cmac_ft_signal[45]);
    cmac_inst.cmac_csc2cmac_ft_46_in(cmac_csc2cmac_ft_signal[46]);
    cmac_inst.cmac_csc2cmac_ft_47_in(cmac_csc2cmac_ft_signal[47]);
    cmac_inst.cmac_csc2cmac_ft_48_in(cmac_csc2cmac_ft_signal[48]);
    cmac_inst.cmac_csc2cmac_ft_49_in(cmac_csc2cmac_ft_signal[49]);
    cmac_inst.cmac_csc2cmac_ft_50_in(cmac_csc2cmac_ft_signal[50]);
    cmac_inst.cmac_csc2cmac_ft_51_in(cmac_csc2cmac_ft_signal[51]);
    cmac_inst.cmac_csc2cmac_ft_52_in(cmac_csc2cmac_ft_signal[52]);
    cmac_inst.cmac_csc2cmac_ft_53_in(cmac_csc2cmac_ft_signal[53]);
    cmac_inst.cmac_csc2cmac_ft_54_in(cmac_csc2cmac_ft_signal[54]);
    cmac_inst.cmac_csc2cmac_ft_55_in(cmac_csc2cmac_ft_signal[55]);
    cmac_inst.cmac_csc2cmac_ft_56_in(cmac_csc2cmac_ft_signal[56]);
    cmac_inst.cmac_csc2cmac_ft_57_in(cmac_csc2cmac_ft_signal[57]);
    cmac_inst.cmac_csc2cmac_ft_58_in(cmac_csc2cmac_ft_signal[58]);
    cmac_inst.cmac_csc2cmac_ft_59_in(cmac_csc2cmac_ft_signal[59]);
    cmac_inst.cmac_csc2cmac_ft_60_in(cmac_csc2cmac_ft_signal[60]);
    cmac_inst.cmac_csc2cmac_ft_61_in(cmac_csc2cmac_ft_signal[61]);
    cmac_inst.cmac_csc2cmac_ft_62_in(cmac_csc2cmac_ft_signal[62]);
    cmac_inst.cmac_csc2cmac_ft_63_in(cmac_csc2cmac_ft_signal[63]);

    cmac_inst.cmac_csc2cmac_wt_0_0_in(cmac_csc2cmac_wt_0_signal[0]);
    cmac_inst.cmac_csc2cmac_wt_0_1_in(cmac_csc2cmac_wt_0_signal[1]);
    cmac_inst.cmac_csc2cmac_wt_0_2_in(cmac_csc2cmac_wt_0_signal[2]);
    cmac_inst.cmac_csc2cmac_wt_0_3_in(cmac_csc2cmac_wt_0_signal[3]);
    cmac_inst.cmac_csc2cmac_wt_0_4_in(cmac_csc2cmac_wt_0_signal[4]);
    cmac_inst.cmac_csc2cmac_wt_0_5_in(cmac_csc2cmac_wt_0_signal[5]);
    cmac_inst.cmac_csc2cmac_wt_0_6_in(cmac_csc2cmac_wt_0_signal[6]);
    cmac_inst.cmac_csc2cmac_wt_0_7_in(cmac_csc2cmac_wt_0_signal[7]);
    cmac_inst.cmac_csc2cmac_wt_0_8_in(cmac_csc2cmac_wt_0_signal[8]);
    cmac_inst.cmac_csc2cmac_wt_0_9_in(cmac_csc2cmac_wt_0_signal[9]);
    cmac_inst.cmac_csc2cmac_wt_0_10_in(cmac_csc2cmac_wt_0_signal[10]);
    cmac_inst.cmac_csc2cmac_wt_0_11_in(cmac_csc2cmac_wt_0_signal[11]);
    cmac_inst.cmac_csc2cmac_wt_0_12_in(cmac_csc2cmac_wt_0_signal[12]);
    cmac_inst.cmac_csc2cmac_wt_0_13_in(cmac_csc2cmac_wt_0_signal[13]);
    cmac_inst.cmac_csc2cmac_wt_0_14_in(cmac_csc2cmac_wt_0_signal[14]);
    cmac_inst.cmac_csc2cmac_wt_0_15_in(cmac_csc2cmac_wt_0_signal[15]);
    cmac_inst.cmac_csc2cmac_wt_0_16_in(cmac_csc2cmac_wt_0_signal[16]);
    cmac_inst.cmac_csc2cmac_wt_0_17_in(cmac_csc2cmac_wt_0_signal[17]);
    cmac_inst.cmac_csc2cmac_wt_0_18_in(cmac_csc2cmac_wt_0_signal[18]);
    cmac_inst.cmac_csc2cmac_wt_0_19_in(cmac_csc2cmac_wt_0_signal[19]);
    cmac_inst.cmac_csc2cmac_wt_0_20_in(cmac_csc2cmac_wt_0_signal[20]);
    cmac_inst.cmac_csc2cmac_wt_0_21_in(cmac_csc2cmac_wt_0_signal[21]);
    cmac_inst.cmac_csc2cmac_wt_0_22_in(cmac_csc2cmac_wt_0_signal[22]);
    cmac_inst.cmac_csc2cmac_wt_0_23_in(cmac_csc2cmac_wt_0_signal[23]);
    cmac_inst.cmac_csc2cmac_wt_0_24_in(cmac_csc2cmac_wt_0_signal[24]);
    cmac_inst.cmac_csc2cmac_wt_0_25_in(cmac_csc2cmac_wt_0_signal[25]);
    cmac_inst.cmac_csc2cmac_wt_0_26_in(cmac_csc2cmac_wt_0_signal[26]);
    cmac_inst.cmac_csc2cmac_wt_0_27_in(cmac_csc2cmac_wt_0_signal[27]);
    cmac_inst.cmac_csc2cmac_wt_0_28_in(cmac_csc2cmac_wt_0_signal[28]);
    cmac_inst.cmac_csc2cmac_wt_0_29_in(cmac_csc2cmac_wt_0_signal[29]);
    cmac_inst.cmac_csc2cmac_wt_0_30_in(cmac_csc2cmac_wt_0_signal[30]);
    cmac_inst.cmac_csc2cmac_wt_0_31_in(cmac_csc2cmac_wt_0_signal[31]);
    cmac_inst.cmac_csc2cmac_wt_0_32_in(cmac_csc2cmac_wt_0_signal[32]);
    cmac_inst.cmac_csc2cmac_wt_0_33_in(cmac_csc2cmac_wt_0_signal[33]);
    cmac_inst.cmac_csc2cmac_wt_0_34_in(cmac_csc2cmac_wt_0_signal[34]);
    cmac_inst.cmac_csc2cmac_wt_0_35_in(cmac_csc2cmac_wt_0_signal[35]);
    cmac_inst.cmac_csc2cmac_wt_0_36_in(cmac_csc2cmac_wt_0_signal[36]);
    cmac_inst.cmac_csc2cmac_wt_0_37_in(cmac_csc2cmac_wt_0_signal[37]);
    cmac_inst.cmac_csc2cmac_wt_0_38_in(cmac_csc2cmac_wt_0_signal[38]);
    cmac_inst.cmac_csc2cmac_wt_0_39_in(cmac_csc2cmac_wt_0_signal[39]);
    cmac_inst.cmac_csc2cmac_wt_0_40_in(cmac_csc2cmac_wt_0_signal[40]);
    cmac_inst.cmac_csc2cmac_wt_0_41_in(cmac_csc2cmac_wt_0_signal[41]);
    cmac_inst.cmac_csc2cmac_wt_0_42_in(cmac_csc2cmac_wt_0_signal[42]);
    cmac_inst.cmac_csc2cmac_wt_0_43_in(cmac_csc2cmac_wt_0_signal[43]);
    cmac_inst.cmac_csc2cmac_wt_0_44_in(cmac_csc2cmac_wt_0_signal[44]);
    cmac_inst.cmac_csc2cmac_wt_0_45_in(cmac_csc2cmac_wt_0_signal[45]);
    cmac_inst.cmac_csc2cmac_wt_0_46_in(cmac_csc2cmac_wt_0_signal[46]);
    cmac_inst.cmac_csc2cmac_wt_0_47_in(cmac_csc2cmac_wt_0_signal[47]);
    cmac_inst.cmac_csc2cmac_wt_0_48_in(cmac_csc2cmac_wt_0_signal[48]);
    cmac_inst.cmac_csc2cmac_wt_0_49_in(cmac_csc2cmac_wt_0_signal[49]);
    cmac_inst.cmac_csc2cmac_wt_0_50_in(cmac_csc2cmac_wt_0_signal[50]);
    cmac_inst.cmac_csc2cmac_wt_0_51_in(cmac_csc2cmac_wt_0_signal[51]);
    cmac_inst.cmac_csc2cmac_wt_0_52_in(cmac_csc2cmac_wt_0_signal[52]);
    cmac_inst.cmac_csc2cmac_wt_0_53_in(cmac_csc2cmac_wt_0_signal[53]);
    cmac_inst.cmac_csc2cmac_wt_0_54_in(cmac_csc2cmac_wt_0_signal[54]);
    cmac_inst.cmac_csc2cmac_wt_0_55_in(cmac_csc2cmac_wt_0_signal[55]);
    cmac_inst.cmac_csc2cmac_wt_0_56_in(cmac_csc2cmac_wt_0_signal[56]);
    cmac_inst.cmac_csc2cmac_wt_0_57_in(cmac_csc2cmac_wt_0_signal[57]);
    cmac_inst.cmac_csc2cmac_wt_0_58_in(cmac_csc2cmac_wt_0_signal[58]);
    cmac_inst.cmac_csc2cmac_wt_0_59_in(cmac_csc2cmac_wt_0_signal[59]);
    cmac_inst.cmac_csc2cmac_wt_0_60_in(cmac_csc2cmac_wt_0_signal[60]);
    cmac_inst.cmac_csc2cmac_wt_0_61_in(cmac_csc2cmac_wt_0_signal[61]);
    cmac_inst.cmac_csc2cmac_wt_0_62_in(cmac_csc2cmac_wt_0_signal[62]);
    cmac_inst.cmac_csc2cmac_wt_0_63_in(cmac_csc2cmac_wt_0_signal[63]);

    cmac_inst.cmac_csc2cmac_wt_1_0_in(cmac_csc2cmac_wt_1_signal[0]);
    cmac_inst.cmac_csc2cmac_wt_1_1_in(cmac_csc2cmac_wt_1_signal[1]);
    cmac_inst.cmac_csc2cmac_wt_1_2_in(cmac_csc2cmac_wt_1_signal[2]);
    cmac_inst.cmac_csc2cmac_wt_1_3_in(cmac_csc2cmac_wt_1_signal[3]);
    cmac_inst.cmac_csc2cmac_wt_1_4_in(cmac_csc2cmac_wt_1_signal[4]);
    cmac_inst.cmac_csc2cmac_wt_1_5_in(cmac_csc2cmac_wt_1_signal[5]);
    cmac_inst.cmac_csc2cmac_wt_1_6_in(cmac_csc2cmac_wt_1_signal[6]);
    cmac_inst.cmac_csc2cmac_wt_1_7_in(cmac_csc2cmac_wt_1_signal[7]);
    cmac_inst.cmac_csc2cmac_wt_1_8_in(cmac_csc2cmac_wt_1_signal[8]);
    cmac_inst.cmac_csc2cmac_wt_1_9_in(cmac_csc2cmac_wt_1_signal[9]);
    cmac_inst.cmac_csc2cmac_wt_1_10_in(cmac_csc2cmac_wt_1_signal[10]);
    cmac_inst.cmac_csc2cmac_wt_1_11_in(cmac_csc2cmac_wt_1_signal[11]);
    cmac_inst.cmac_csc2cmac_wt_1_12_in(cmac_csc2cmac_wt_1_signal[12]);
    cmac_inst.cmac_csc2cmac_wt_1_13_in(cmac_csc2cmac_wt_1_signal[13]);
    cmac_inst.cmac_csc2cmac_wt_1_14_in(cmac_csc2cmac_wt_1_signal[14]);
    cmac_inst.cmac_csc2cmac_wt_1_15_in(cmac_csc2cmac_wt_1_signal[15]);
    cmac_inst.cmac_csc2cmac_wt_1_16_in(cmac_csc2cmac_wt_1_signal[16]);
    cmac_inst.cmac_csc2cmac_wt_1_17_in(cmac_csc2cmac_wt_1_signal[17]);
    cmac_inst.cmac_csc2cmac_wt_1_18_in(cmac_csc2cmac_wt_1_signal[18]);
    cmac_inst.cmac_csc2cmac_wt_1_19_in(cmac_csc2cmac_wt_1_signal[19]);
    cmac_inst.cmac_csc2cmac_wt_1_20_in(cmac_csc2cmac_wt_1_signal[20]);
    cmac_inst.cmac_csc2cmac_wt_1_21_in(cmac_csc2cmac_wt_1_signal[21]);
    cmac_inst.cmac_csc2cmac_wt_1_22_in(cmac_csc2cmac_wt_1_signal[22]);
    cmac_inst.cmac_csc2cmac_wt_1_23_in(cmac_csc2cmac_wt_1_signal[23]);
    cmac_inst.cmac_csc2cmac_wt_1_24_in(cmac_csc2cmac_wt_1_signal[24]);
    cmac_inst.cmac_csc2cmac_wt_1_25_in(cmac_csc2cmac_wt_1_signal[25]);
    cmac_inst.cmac_csc2cmac_wt_1_26_in(cmac_csc2cmac_wt_1_signal[26]);
    cmac_inst.cmac_csc2cmac_wt_1_27_in(cmac_csc2cmac_wt_1_signal[27]);
    cmac_inst.cmac_csc2cmac_wt_1_28_in(cmac_csc2cmac_wt_1_signal[28]);
    cmac_inst.cmac_csc2cmac_wt_1_29_in(cmac_csc2cmac_wt_1_signal[29]);
    cmac_inst.cmac_csc2cmac_wt_1_30_in(cmac_csc2cmac_wt_1_signal[30]);
    cmac_inst.cmac_csc2cmac_wt_1_31_in(cmac_csc2cmac_wt_1_signal[31]);
    cmac_inst.cmac_csc2cmac_wt_1_32_in(cmac_csc2cmac_wt_1_signal[32]);
    cmac_inst.cmac_csc2cmac_wt_1_33_in(cmac_csc2cmac_wt_1_signal[33]);
    cmac_inst.cmac_csc2cmac_wt_1_34_in(cmac_csc2cmac_wt_1_signal[34]);
    cmac_inst.cmac_csc2cmac_wt_1_35_in(cmac_csc2cmac_wt_1_signal[35]);
    cmac_inst.cmac_csc2cmac_wt_1_36_in(cmac_csc2cmac_wt_1_signal[36]);
    cmac_inst.cmac_csc2cmac_wt_1_37_in(cmac_csc2cmac_wt_1_signal[37]);
    cmac_inst.cmac_csc2cmac_wt_1_38_in(cmac_csc2cmac_wt_1_signal[38]);
    cmac_inst.cmac_csc2cmac_wt_1_39_in(cmac_csc2cmac_wt_1_signal[39]);
    cmac_inst.cmac_csc2cmac_wt_1_40_in(cmac_csc2cmac_wt_1_signal[40]);
    cmac_inst.cmac_csc2cmac_wt_1_41_in(cmac_csc2cmac_wt_1_signal[41]);
    cmac_inst.cmac_csc2cmac_wt_1_42_in(cmac_csc2cmac_wt_1_signal[42]);
    cmac_inst.cmac_csc2cmac_wt_1_43_in(cmac_csc2cmac_wt_1_signal[43]);
    cmac_inst.cmac_csc2cmac_wt_1_44_in(cmac_csc2cmac_wt_1_signal[44]);
    cmac_inst.cmac_csc2cmac_wt_1_45_in(cmac_csc2cmac_wt_1_signal[45]);
    cmac_inst.cmac_csc2cmac_wt_1_46_in(cmac_csc2cmac_wt_1_signal[46]);
    cmac_inst.cmac_csc2cmac_wt_1_47_in(cmac_csc2cmac_wt_1_signal[47]);
    cmac_inst.cmac_csc2cmac_wt_1_48_in(cmac_csc2cmac_wt_1_signal[48]);
    cmac_inst.cmac_csc2cmac_wt_1_49_in(cmac_csc2cmac_wt_1_signal[49]);
    cmac_inst.cmac_csc2cmac_wt_1_50_in(cmac_csc2cmac_wt_1_signal[50]);
    cmac_inst.cmac_csc2cmac_wt_1_51_in(cmac_csc2cmac_wt_1_signal[51]);
    cmac_inst.cmac_csc2cmac_wt_1_52_in(cmac_csc2cmac_wt_1_signal[52]);
    cmac_inst.cmac_csc2cmac_wt_1_53_in(cmac_csc2cmac_wt_1_signal[53]);
    cmac_inst.cmac_csc2cmac_wt_1_54_in(cmac_csc2cmac_wt_1_signal[54]);
    cmac_inst.cmac_csc2cmac_wt_1_55_in(cmac_csc2cmac_wt_1_signal[55]);
    cmac_inst.cmac_csc2cmac_wt_1_56_in(cmac_csc2cmac_wt_1_signal[56]);
    cmac_inst.cmac_csc2cmac_wt_1_57_in(cmac_csc2cmac_wt_1_signal[57]);
    cmac_inst.cmac_csc2cmac_wt_1_58_in(cmac_csc2cmac_wt_1_signal[58]);
    cmac_inst.cmac_csc2cmac_wt_1_59_in(cmac_csc2cmac_wt_1_signal[59]);
    cmac_inst.cmac_csc2cmac_wt_1_60_in(cmac_csc2cmac_wt_1_signal[60]);
    cmac_inst.cmac_csc2cmac_wt_1_61_in(cmac_csc2cmac_wt_1_signal[61]);
    cmac_inst.cmac_csc2cmac_wt_1_62_in(cmac_csc2cmac_wt_1_signal[62]);
    cmac_inst.cmac_csc2cmac_wt_1_63_in(cmac_csc2cmac_wt_1_signal[63]);

    cmac_inst.cmac_csc2cmac_wt_2_0_in(cmac_csc2cmac_wt_2_signal[0]);
    cmac_inst.cmac_csc2cmac_wt_2_1_in(cmac_csc2cmac_wt_2_signal[1]);
    cmac_inst.cmac_csc2cmac_wt_2_2_in(cmac_csc2cmac_wt_2_signal[2]);
    cmac_inst.cmac_csc2cmac_wt_2_3_in(cmac_csc2cmac_wt_2_signal[3]);
    cmac_inst.cmac_csc2cmac_wt_2_4_in(cmac_csc2cmac_wt_2_signal[4]);
    cmac_inst.cmac_csc2cmac_wt_2_5_in(cmac_csc2cmac_wt_2_signal[5]);
    cmac_inst.cmac_csc2cmac_wt_2_6_in(cmac_csc2cmac_wt_2_signal[6]);
    cmac_inst.cmac_csc2cmac_wt_2_7_in(cmac_csc2cmac_wt_2_signal[7]);
    cmac_inst.cmac_csc2cmac_wt_2_8_in(cmac_csc2cmac_wt_2_signal[8]);
    cmac_inst.cmac_csc2cmac_wt_2_9_in(cmac_csc2cmac_wt_2_signal[9]);
    cmac_inst.cmac_csc2cmac_wt_2_10_in(cmac_csc2cmac_wt_2_signal[10]);
    cmac_inst.cmac_csc2cmac_wt_2_11_in(cmac_csc2cmac_wt_2_signal[11]);
    cmac_inst.cmac_csc2cmac_wt_2_12_in(cmac_csc2cmac_wt_2_signal[12]);
    cmac_inst.cmac_csc2cmac_wt_2_13_in(cmac_csc2cmac_wt_2_signal[13]);
    cmac_inst.cmac_csc2cmac_wt_2_14_in(cmac_csc2cmac_wt_2_signal[14]);
    cmac_inst.cmac_csc2cmac_wt_2_15_in(cmac_csc2cmac_wt_2_signal[15]);
    cmac_inst.cmac_csc2cmac_wt_2_16_in(cmac_csc2cmac_wt_2_signal[16]);
    cmac_inst.cmac_csc2cmac_wt_2_17_in(cmac_csc2cmac_wt_2_signal[17]);
    cmac_inst.cmac_csc2cmac_wt_2_18_in(cmac_csc2cmac_wt_2_signal[18]);
    cmac_inst.cmac_csc2cmac_wt_2_19_in(cmac_csc2cmac_wt_2_signal[19]);
    cmac_inst.cmac_csc2cmac_wt_2_20_in(cmac_csc2cmac_wt_2_signal[20]);
    cmac_inst.cmac_csc2cmac_wt_2_21_in(cmac_csc2cmac_wt_2_signal[21]);
    cmac_inst.cmac_csc2cmac_wt_2_22_in(cmac_csc2cmac_wt_2_signal[22]);
    cmac_inst.cmac_csc2cmac_wt_2_23_in(cmac_csc2cmac_wt_2_signal[23]);
    cmac_inst.cmac_csc2cmac_wt_2_24_in(cmac_csc2cmac_wt_2_signal[24]);
    cmac_inst.cmac_csc2cmac_wt_2_25_in(cmac_csc2cmac_wt_2_signal[25]);
    cmac_inst.cmac_csc2cmac_wt_2_26_in(cmac_csc2cmac_wt_2_signal[26]);
    cmac_inst.cmac_csc2cmac_wt_2_27_in(cmac_csc2cmac_wt_2_signal[27]);
    cmac_inst.cmac_csc2cmac_wt_2_28_in(cmac_csc2cmac_wt_2_signal[28]);
    cmac_inst.cmac_csc2cmac_wt_2_29_in(cmac_csc2cmac_wt_2_signal[29]);
    cmac_inst.cmac_csc2cmac_wt_2_30_in(cmac_csc2cmac_wt_2_signal[30]);
    cmac_inst.cmac_csc2cmac_wt_2_31_in(cmac_csc2cmac_wt_2_signal[31]);
    cmac_inst.cmac_csc2cmac_wt_2_32_in(cmac_csc2cmac_wt_2_signal[32]);
    cmac_inst.cmac_csc2cmac_wt_2_33_in(cmac_csc2cmac_wt_2_signal[33]);
    cmac_inst.cmac_csc2cmac_wt_2_34_in(cmac_csc2cmac_wt_2_signal[34]);
    cmac_inst.cmac_csc2cmac_wt_2_35_in(cmac_csc2cmac_wt_2_signal[35]);
    cmac_inst.cmac_csc2cmac_wt_2_36_in(cmac_csc2cmac_wt_2_signal[36]);
    cmac_inst.cmac_csc2cmac_wt_2_37_in(cmac_csc2cmac_wt_2_signal[37]);
    cmac_inst.cmac_csc2cmac_wt_2_38_in(cmac_csc2cmac_wt_2_signal[38]);
    cmac_inst.cmac_csc2cmac_wt_2_39_in(cmac_csc2cmac_wt_2_signal[39]);
    cmac_inst.cmac_csc2cmac_wt_2_40_in(cmac_csc2cmac_wt_2_signal[40]);
    cmac_inst.cmac_csc2cmac_wt_2_41_in(cmac_csc2cmac_wt_2_signal[41]);
    cmac_inst.cmac_csc2cmac_wt_2_42_in(cmac_csc2cmac_wt_2_signal[42]);
    cmac_inst.cmac_csc2cmac_wt_2_43_in(cmac_csc2cmac_wt_2_signal[43]);
    cmac_inst.cmac_csc2cmac_wt_2_44_in(cmac_csc2cmac_wt_2_signal[44]);
    cmac_inst.cmac_csc2cmac_wt_2_45_in(cmac_csc2cmac_wt_2_signal[45]);
    cmac_inst.cmac_csc2cmac_wt_2_46_in(cmac_csc2cmac_wt_2_signal[46]);
    cmac_inst.cmac_csc2cmac_wt_2_47_in(cmac_csc2cmac_wt_2_signal[47]);
    cmac_inst.cmac_csc2cmac_wt_2_48_in(cmac_csc2cmac_wt_2_signal[48]);
    cmac_inst.cmac_csc2cmac_wt_2_49_in(cmac_csc2cmac_wt_2_signal[49]);
    cmac_inst.cmac_csc2cmac_wt_2_50_in(cmac_csc2cmac_wt_2_signal[50]);
    cmac_inst.cmac_csc2cmac_wt_2_51_in(cmac_csc2cmac_wt_2_signal[51]);
    cmac_inst.cmac_csc2cmac_wt_2_52_in(cmac_csc2cmac_wt_2_signal[52]);
    cmac_inst.cmac_csc2cmac_wt_2_53_in(cmac_csc2cmac_wt_2_signal[53]);
    cmac_inst.cmac_csc2cmac_wt_2_54_in(cmac_csc2cmac_wt_2_signal[54]);
    cmac_inst.cmac_csc2cmac_wt_2_55_in(cmac_csc2cmac_wt_2_signal[55]);
    cmac_inst.cmac_csc2cmac_wt_2_56_in(cmac_csc2cmac_wt_2_signal[56]);
    cmac_inst.cmac_csc2cmac_wt_2_57_in(cmac_csc2cmac_wt_2_signal[57]);
    cmac_inst.cmac_csc2cmac_wt_2_58_in(cmac_csc2cmac_wt_2_signal[58]);
    cmac_inst.cmac_csc2cmac_wt_2_59_in(cmac_csc2cmac_wt_2_signal[59]);
    cmac_inst.cmac_csc2cmac_wt_2_60_in(cmac_csc2cmac_wt_2_signal[60]);
    cmac_inst.cmac_csc2cmac_wt_2_61_in(cmac_csc2cmac_wt_2_signal[61]);
    cmac_inst.cmac_csc2cmac_wt_2_62_in(cmac_csc2cmac_wt_2_signal[62]);
    cmac_inst.cmac_csc2cmac_wt_2_63_in(cmac_csc2cmac_wt_2_signal[63]);

    cmac_inst.cmac_csc2cmac_wt_3_0_in(cmac_csc2cmac_wt_3_signal[0]);
    cmac_inst.cmac_csc2cmac_wt_3_1_in(cmac_csc2cmac_wt_3_signal[1]);
    cmac_inst.cmac_csc2cmac_wt_3_2_in(cmac_csc2cmac_wt_3_signal[2]);
    cmac_inst.cmac_csc2cmac_wt_3_3_in(cmac_csc2cmac_wt_3_signal[3]);
    cmac_inst.cmac_csc2cmac_wt_3_4_in(cmac_csc2cmac_wt_3_signal[4]);
    cmac_inst.cmac_csc2cmac_wt_3_5_in(cmac_csc2cmac_wt_3_signal[5]);
    cmac_inst.cmac_csc2cmac_wt_3_6_in(cmac_csc2cmac_wt_3_signal[6]);
    cmac_inst.cmac_csc2cmac_wt_3_7_in(cmac_csc2cmac_wt_3_signal[7]);
    cmac_inst.cmac_csc2cmac_wt_3_8_in(cmac_csc2cmac_wt_3_signal[8]);
    cmac_inst.cmac_csc2cmac_wt_3_9_in(cmac_csc2cmac_wt_3_signal[9]);
    cmac_inst.cmac_csc2cmac_wt_3_10_in(cmac_csc2cmac_wt_3_signal[10]);
    cmac_inst.cmac_csc2cmac_wt_3_11_in(cmac_csc2cmac_wt_3_signal[11]);
    cmac_inst.cmac_csc2cmac_wt_3_12_in(cmac_csc2cmac_wt_3_signal[12]);
    cmac_inst.cmac_csc2cmac_wt_3_13_in(cmac_csc2cmac_wt_3_signal[13]);
    cmac_inst.cmac_csc2cmac_wt_3_14_in(cmac_csc2cmac_wt_3_signal[14]);
    cmac_inst.cmac_csc2cmac_wt_3_15_in(cmac_csc2cmac_wt_3_signal[15]);
    cmac_inst.cmac_csc2cmac_wt_3_16_in(cmac_csc2cmac_wt_3_signal[16]);
    cmac_inst.cmac_csc2cmac_wt_3_17_in(cmac_csc2cmac_wt_3_signal[17]);
    cmac_inst.cmac_csc2cmac_wt_3_18_in(cmac_csc2cmac_wt_3_signal[18]);
    cmac_inst.cmac_csc2cmac_wt_3_19_in(cmac_csc2cmac_wt_3_signal[19]);
    cmac_inst.cmac_csc2cmac_wt_3_20_in(cmac_csc2cmac_wt_3_signal[20]);
    cmac_inst.cmac_csc2cmac_wt_3_21_in(cmac_csc2cmac_wt_3_signal[21]);
    cmac_inst.cmac_csc2cmac_wt_3_22_in(cmac_csc2cmac_wt_3_signal[22]);
    cmac_inst.cmac_csc2cmac_wt_3_23_in(cmac_csc2cmac_wt_3_signal[23]);
    cmac_inst.cmac_csc2cmac_wt_3_24_in(cmac_csc2cmac_wt_3_signal[24]);
    cmac_inst.cmac_csc2cmac_wt_3_25_in(cmac_csc2cmac_wt_3_signal[25]);
    cmac_inst.cmac_csc2cmac_wt_3_26_in(cmac_csc2cmac_wt_3_signal[26]);
    cmac_inst.cmac_csc2cmac_wt_3_27_in(cmac_csc2cmac_wt_3_signal[27]);
    cmac_inst.cmac_csc2cmac_wt_3_28_in(cmac_csc2cmac_wt_3_signal[28]);
    cmac_inst.cmac_csc2cmac_wt_3_29_in(cmac_csc2cmac_wt_3_signal[29]);
    cmac_inst.cmac_csc2cmac_wt_3_30_in(cmac_csc2cmac_wt_3_signal[30]);
    cmac_inst.cmac_csc2cmac_wt_3_31_in(cmac_csc2cmac_wt_3_signal[31]);
    cmac_inst.cmac_csc2cmac_wt_3_32_in(cmac_csc2cmac_wt_3_signal[32]);
    cmac_inst.cmac_csc2cmac_wt_3_33_in(cmac_csc2cmac_wt_3_signal[33]);
    cmac_inst.cmac_csc2cmac_wt_3_34_in(cmac_csc2cmac_wt_3_signal[34]);
    cmac_inst.cmac_csc2cmac_wt_3_35_in(cmac_csc2cmac_wt_3_signal[35]);
    cmac_inst.cmac_csc2cmac_wt_3_36_in(cmac_csc2cmac_wt_3_signal[36]);
    cmac_inst.cmac_csc2cmac_wt_3_37_in(cmac_csc2cmac_wt_3_signal[37]);
    cmac_inst.cmac_csc2cmac_wt_3_38_in(cmac_csc2cmac_wt_3_signal[38]);
    cmac_inst.cmac_csc2cmac_wt_3_39_in(cmac_csc2cmac_wt_3_signal[39]);
    cmac_inst.cmac_csc2cmac_wt_3_40_in(cmac_csc2cmac_wt_3_signal[40]);
    cmac_inst.cmac_csc2cmac_wt_3_41_in(cmac_csc2cmac_wt_3_signal[41]);
    cmac_inst.cmac_csc2cmac_wt_3_42_in(cmac_csc2cmac_wt_3_signal[42]);
    cmac_inst.cmac_csc2cmac_wt_3_43_in(cmac_csc2cmac_wt_3_signal[43]);
    cmac_inst.cmac_csc2cmac_wt_3_44_in(cmac_csc2cmac_wt_3_signal[44]);
    cmac_inst.cmac_csc2cmac_wt_3_45_in(cmac_csc2cmac_wt_3_signal[45]);
    cmac_inst.cmac_csc2cmac_wt_3_46_in(cmac_csc2cmac_wt_3_signal[46]);
    cmac_inst.cmac_csc2cmac_wt_3_47_in(cmac_csc2cmac_wt_3_signal[47]);
    cmac_inst.cmac_csc2cmac_wt_3_48_in(cmac_csc2cmac_wt_3_signal[48]);
    cmac_inst.cmac_csc2cmac_wt_3_49_in(cmac_csc2cmac_wt_3_signal[49]);
    cmac_inst.cmac_csc2cmac_wt_3_50_in(cmac_csc2cmac_wt_3_signal[50]);
    cmac_inst.cmac_csc2cmac_wt_3_51_in(cmac_csc2cmac_wt_3_signal[51]);
    cmac_inst.cmac_csc2cmac_wt_3_52_in(cmac_csc2cmac_wt_3_signal[52]);
    cmac_inst.cmac_csc2cmac_wt_3_53_in(cmac_csc2cmac_wt_3_signal[53]);
    cmac_inst.cmac_csc2cmac_wt_3_54_in(cmac_csc2cmac_wt_3_signal[54]);
    cmac_inst.cmac_csc2cmac_wt_3_55_in(cmac_csc2cmac_wt_3_signal[55]);
    cmac_inst.cmac_csc2cmac_wt_3_56_in(cmac_csc2cmac_wt_3_signal[56]);
    cmac_inst.cmac_csc2cmac_wt_3_57_in(cmac_csc2cmac_wt_3_signal[57]);
    cmac_inst.cmac_csc2cmac_wt_3_58_in(cmac_csc2cmac_wt_3_signal[58]);
    cmac_inst.cmac_csc2cmac_wt_3_59_in(cmac_csc2cmac_wt_3_signal[59]);
    cmac_inst.cmac_csc2cmac_wt_3_60_in(cmac_csc2cmac_wt_3_signal[60]);
    cmac_inst.cmac_csc2cmac_wt_3_61_in(cmac_csc2cmac_wt_3_signal[61]);
    cmac_inst.cmac_csc2cmac_wt_3_62_in(cmac_csc2cmac_wt_3_signal[62]);
    cmac_inst.cmac_csc2cmac_wt_3_63_in(cmac_csc2cmac_wt_3_signal[63]);

    cmac_inst.cmac_csc2cmac_wt_4_0_in(cmac_csc2cmac_wt_4_signal[0]);
    cmac_inst.cmac_csc2cmac_wt_4_1_in(cmac_csc2cmac_wt_4_signal[1]);
    cmac_inst.cmac_csc2cmac_wt_4_2_in(cmac_csc2cmac_wt_4_signal[2]);
    cmac_inst.cmac_csc2cmac_wt_4_3_in(cmac_csc2cmac_wt_4_signal[3]);
    cmac_inst.cmac_csc2cmac_wt_4_4_in(cmac_csc2cmac_wt_4_signal[4]);
    cmac_inst.cmac_csc2cmac_wt_4_5_in(cmac_csc2cmac_wt_4_signal[5]);
    cmac_inst.cmac_csc2cmac_wt_4_6_in(cmac_csc2cmac_wt_4_signal[6]);
    cmac_inst.cmac_csc2cmac_wt_4_7_in(cmac_csc2cmac_wt_4_signal[7]);
    cmac_inst.cmac_csc2cmac_wt_4_8_in(cmac_csc2cmac_wt_4_signal[8]);
    cmac_inst.cmac_csc2cmac_wt_4_9_in(cmac_csc2cmac_wt_4_signal[9]);
    cmac_inst.cmac_csc2cmac_wt_4_10_in(cmac_csc2cmac_wt_4_signal[10]);
    cmac_inst.cmac_csc2cmac_wt_4_11_in(cmac_csc2cmac_wt_4_signal[11]);
    cmac_inst.cmac_csc2cmac_wt_4_12_in(cmac_csc2cmac_wt_4_signal[12]);
    cmac_inst.cmac_csc2cmac_wt_4_13_in(cmac_csc2cmac_wt_4_signal[13]);
    cmac_inst.cmac_csc2cmac_wt_4_14_in(cmac_csc2cmac_wt_4_signal[14]);
    cmac_inst.cmac_csc2cmac_wt_4_15_in(cmac_csc2cmac_wt_4_signal[15]);
    cmac_inst.cmac_csc2cmac_wt_4_16_in(cmac_csc2cmac_wt_4_signal[16]);
    cmac_inst.cmac_csc2cmac_wt_4_17_in(cmac_csc2cmac_wt_4_signal[17]);
    cmac_inst.cmac_csc2cmac_wt_4_18_in(cmac_csc2cmac_wt_4_signal[18]);
    cmac_inst.cmac_csc2cmac_wt_4_19_in(cmac_csc2cmac_wt_4_signal[19]);
    cmac_inst.cmac_csc2cmac_wt_4_20_in(cmac_csc2cmac_wt_4_signal[20]);
    cmac_inst.cmac_csc2cmac_wt_4_21_in(cmac_csc2cmac_wt_4_signal[21]);
    cmac_inst.cmac_csc2cmac_wt_4_22_in(cmac_csc2cmac_wt_4_signal[22]);
    cmac_inst.cmac_csc2cmac_wt_4_23_in(cmac_csc2cmac_wt_4_signal[23]);
    cmac_inst.cmac_csc2cmac_wt_4_24_in(cmac_csc2cmac_wt_4_signal[24]);
    cmac_inst.cmac_csc2cmac_wt_4_25_in(cmac_csc2cmac_wt_4_signal[25]);
    cmac_inst.cmac_csc2cmac_wt_4_26_in(cmac_csc2cmac_wt_4_signal[26]);
    cmac_inst.cmac_csc2cmac_wt_4_27_in(cmac_csc2cmac_wt_4_signal[27]);
    cmac_inst.cmac_csc2cmac_wt_4_28_in(cmac_csc2cmac_wt_4_signal[28]);
    cmac_inst.cmac_csc2cmac_wt_4_29_in(cmac_csc2cmac_wt_4_signal[29]);
    cmac_inst.cmac_csc2cmac_wt_4_30_in(cmac_csc2cmac_wt_4_signal[30]);
    cmac_inst.cmac_csc2cmac_wt_4_31_in(cmac_csc2cmac_wt_4_signal[31]);
    cmac_inst.cmac_csc2cmac_wt_4_32_in(cmac_csc2cmac_wt_4_signal[32]);
    cmac_inst.cmac_csc2cmac_wt_4_33_in(cmac_csc2cmac_wt_4_signal[33]);
    cmac_inst.cmac_csc2cmac_wt_4_34_in(cmac_csc2cmac_wt_4_signal[34]);
    cmac_inst.cmac_csc2cmac_wt_4_35_in(cmac_csc2cmac_wt_4_signal[35]);
    cmac_inst.cmac_csc2cmac_wt_4_36_in(cmac_csc2cmac_wt_4_signal[36]);
    cmac_inst.cmac_csc2cmac_wt_4_37_in(cmac_csc2cmac_wt_4_signal[37]);
    cmac_inst.cmac_csc2cmac_wt_4_38_in(cmac_csc2cmac_wt_4_signal[38]);
    cmac_inst.cmac_csc2cmac_wt_4_39_in(cmac_csc2cmac_wt_4_signal[39]);
    cmac_inst.cmac_csc2cmac_wt_4_40_in(cmac_csc2cmac_wt_4_signal[40]);
    cmac_inst.cmac_csc2cmac_wt_4_41_in(cmac_csc2cmac_wt_4_signal[41]);
    cmac_inst.cmac_csc2cmac_wt_4_42_in(cmac_csc2cmac_wt_4_signal[42]);
    cmac_inst.cmac_csc2cmac_wt_4_43_in(cmac_csc2cmac_wt_4_signal[43]);
    cmac_inst.cmac_csc2cmac_wt_4_44_in(cmac_csc2cmac_wt_4_signal[44]);
    cmac_inst.cmac_csc2cmac_wt_4_45_in(cmac_csc2cmac_wt_4_signal[45]);
    cmac_inst.cmac_csc2cmac_wt_4_46_in(cmac_csc2cmac_wt_4_signal[46]);
    cmac_inst.cmac_csc2cmac_wt_4_47_in(cmac_csc2cmac_wt_4_signal[47]);
    cmac_inst.cmac_csc2cmac_wt_4_48_in(cmac_csc2cmac_wt_4_signal[48]);
    cmac_inst.cmac_csc2cmac_wt_4_49_in(cmac_csc2cmac_wt_4_signal[49]);
    cmac_inst.cmac_csc2cmac_wt_4_50_in(cmac_csc2cmac_wt_4_signal[50]);
    cmac_inst.cmac_csc2cmac_wt_4_51_in(cmac_csc2cmac_wt_4_signal[51]);
    cmac_inst.cmac_csc2cmac_wt_4_52_in(cmac_csc2cmac_wt_4_signal[52]);
    cmac_inst.cmac_csc2cmac_wt_4_53_in(cmac_csc2cmac_wt_4_signal[53]);
    cmac_inst.cmac_csc2cmac_wt_4_54_in(cmac_csc2cmac_wt_4_signal[54]);
    cmac_inst.cmac_csc2cmac_wt_4_55_in(cmac_csc2cmac_wt_4_signal[55]);
    cmac_inst.cmac_csc2cmac_wt_4_56_in(cmac_csc2cmac_wt_4_signal[56]);
    cmac_inst.cmac_csc2cmac_wt_4_57_in(cmac_csc2cmac_wt_4_signal[57]);
    cmac_inst.cmac_csc2cmac_wt_4_58_in(cmac_csc2cmac_wt_4_signal[58]);
    cmac_inst.cmac_csc2cmac_wt_4_59_in(cmac_csc2cmac_wt_4_signal[59]);
    cmac_inst.cmac_csc2cmac_wt_4_60_in(cmac_csc2cmac_wt_4_signal[60]);
    cmac_inst.cmac_csc2cmac_wt_4_61_in(cmac_csc2cmac_wt_4_signal[61]);
    cmac_inst.cmac_csc2cmac_wt_4_62_in(cmac_csc2cmac_wt_4_signal[62]);
    cmac_inst.cmac_csc2cmac_wt_4_63_in(cmac_csc2cmac_wt_4_signal[63]);

    cmac_inst.cmac_csc2cmac_wt_5_0_in(cmac_csc2cmac_wt_5_signal[0]);
    cmac_inst.cmac_csc2cmac_wt_5_1_in(cmac_csc2cmac_wt_5_signal[1]);
    cmac_inst.cmac_csc2cmac_wt_5_2_in(cmac_csc2cmac_wt_5_signal[2]);
    cmac_inst.cmac_csc2cmac_wt_5_3_in(cmac_csc2cmac_wt_5_signal[3]);
    cmac_inst.cmac_csc2cmac_wt_5_4_in(cmac_csc2cmac_wt_5_signal[4]);
    cmac_inst.cmac_csc2cmac_wt_5_5_in(cmac_csc2cmac_wt_5_signal[5]);
    cmac_inst.cmac_csc2cmac_wt_5_6_in(cmac_csc2cmac_wt_5_signal[6]);
    cmac_inst.cmac_csc2cmac_wt_5_7_in(cmac_csc2cmac_wt_5_signal[7]);
    cmac_inst.cmac_csc2cmac_wt_5_8_in(cmac_csc2cmac_wt_5_signal[8]);
    cmac_inst.cmac_csc2cmac_wt_5_9_in(cmac_csc2cmac_wt_5_signal[9]);
    cmac_inst.cmac_csc2cmac_wt_5_10_in(cmac_csc2cmac_wt_5_signal[10]);
    cmac_inst.cmac_csc2cmac_wt_5_11_in(cmac_csc2cmac_wt_5_signal[11]);
    cmac_inst.cmac_csc2cmac_wt_5_12_in(cmac_csc2cmac_wt_5_signal[12]);
    cmac_inst.cmac_csc2cmac_wt_5_13_in(cmac_csc2cmac_wt_5_signal[13]);
    cmac_inst.cmac_csc2cmac_wt_5_14_in(cmac_csc2cmac_wt_5_signal[14]);
    cmac_inst.cmac_csc2cmac_wt_5_15_in(cmac_csc2cmac_wt_5_signal[15]);
    cmac_inst.cmac_csc2cmac_wt_5_16_in(cmac_csc2cmac_wt_5_signal[16]);
    cmac_inst.cmac_csc2cmac_wt_5_17_in(cmac_csc2cmac_wt_5_signal[17]);
    cmac_inst.cmac_csc2cmac_wt_5_18_in(cmac_csc2cmac_wt_5_signal[18]);
    cmac_inst.cmac_csc2cmac_wt_5_19_in(cmac_csc2cmac_wt_5_signal[19]);
    cmac_inst.cmac_csc2cmac_wt_5_20_in(cmac_csc2cmac_wt_5_signal[20]);
    cmac_inst.cmac_csc2cmac_wt_5_21_in(cmac_csc2cmac_wt_5_signal[21]);
    cmac_inst.cmac_csc2cmac_wt_5_22_in(cmac_csc2cmac_wt_5_signal[22]);
    cmac_inst.cmac_csc2cmac_wt_5_23_in(cmac_csc2cmac_wt_5_signal[23]);
    cmac_inst.cmac_csc2cmac_wt_5_24_in(cmac_csc2cmac_wt_5_signal[24]);
    cmac_inst.cmac_csc2cmac_wt_5_25_in(cmac_csc2cmac_wt_5_signal[25]);
    cmac_inst.cmac_csc2cmac_wt_5_26_in(cmac_csc2cmac_wt_5_signal[26]);
    cmac_inst.cmac_csc2cmac_wt_5_27_in(cmac_csc2cmac_wt_5_signal[27]);
    cmac_inst.cmac_csc2cmac_wt_5_28_in(cmac_csc2cmac_wt_5_signal[28]);
    cmac_inst.cmac_csc2cmac_wt_5_29_in(cmac_csc2cmac_wt_5_signal[29]);
    cmac_inst.cmac_csc2cmac_wt_5_30_in(cmac_csc2cmac_wt_5_signal[30]);
    cmac_inst.cmac_csc2cmac_wt_5_31_in(cmac_csc2cmac_wt_5_signal[31]);
    cmac_inst.cmac_csc2cmac_wt_5_32_in(cmac_csc2cmac_wt_5_signal[32]);
    cmac_inst.cmac_csc2cmac_wt_5_33_in(cmac_csc2cmac_wt_5_signal[33]);
    cmac_inst.cmac_csc2cmac_wt_5_34_in(cmac_csc2cmac_wt_5_signal[34]);
    cmac_inst.cmac_csc2cmac_wt_5_35_in(cmac_csc2cmac_wt_5_signal[35]);
    cmac_inst.cmac_csc2cmac_wt_5_36_in(cmac_csc2cmac_wt_5_signal[36]);
    cmac_inst.cmac_csc2cmac_wt_5_37_in(cmac_csc2cmac_wt_5_signal[37]);
    cmac_inst.cmac_csc2cmac_wt_5_38_in(cmac_csc2cmac_wt_5_signal[38]);
    cmac_inst.cmac_csc2cmac_wt_5_39_in(cmac_csc2cmac_wt_5_signal[39]);
    cmac_inst.cmac_csc2cmac_wt_5_40_in(cmac_csc2cmac_wt_5_signal[40]);
    cmac_inst.cmac_csc2cmac_wt_5_41_in(cmac_csc2cmac_wt_5_signal[41]);
    cmac_inst.cmac_csc2cmac_wt_5_42_in(cmac_csc2cmac_wt_5_signal[42]);
    cmac_inst.cmac_csc2cmac_wt_5_43_in(cmac_csc2cmac_wt_5_signal[43]);
    cmac_inst.cmac_csc2cmac_wt_5_44_in(cmac_csc2cmac_wt_5_signal[44]);
    cmac_inst.cmac_csc2cmac_wt_5_45_in(cmac_csc2cmac_wt_5_signal[45]);
    cmac_inst.cmac_csc2cmac_wt_5_46_in(cmac_csc2cmac_wt_5_signal[46]);
    cmac_inst.cmac_csc2cmac_wt_5_47_in(cmac_csc2cmac_wt_5_signal[47]);
    cmac_inst.cmac_csc2cmac_wt_5_48_in(cmac_csc2cmac_wt_5_signal[48]);
    cmac_inst.cmac_csc2cmac_wt_5_49_in(cmac_csc2cmac_wt_5_signal[49]);
    cmac_inst.cmac_csc2cmac_wt_5_50_in(cmac_csc2cmac_wt_5_signal[50]);
    cmac_inst.cmac_csc2cmac_wt_5_51_in(cmac_csc2cmac_wt_5_signal[51]);
    cmac_inst.cmac_csc2cmac_wt_5_52_in(cmac_csc2cmac_wt_5_signal[52]);
    cmac_inst.cmac_csc2cmac_wt_5_53_in(cmac_csc2cmac_wt_5_signal[53]);
    cmac_inst.cmac_csc2cmac_wt_5_54_in(cmac_csc2cmac_wt_5_signal[54]);
    cmac_inst.cmac_csc2cmac_wt_5_55_in(cmac_csc2cmac_wt_5_signal[55]);
    cmac_inst.cmac_csc2cmac_wt_5_56_in(cmac_csc2cmac_wt_5_signal[56]);
    cmac_inst.cmac_csc2cmac_wt_5_57_in(cmac_csc2cmac_wt_5_signal[57]);
    cmac_inst.cmac_csc2cmac_wt_5_58_in(cmac_csc2cmac_wt_5_signal[58]);
    cmac_inst.cmac_csc2cmac_wt_5_59_in(cmac_csc2cmac_wt_5_signal[59]);
    cmac_inst.cmac_csc2cmac_wt_5_60_in(cmac_csc2cmac_wt_5_signal[60]);
    cmac_inst.cmac_csc2cmac_wt_5_61_in(cmac_csc2cmac_wt_5_signal[61]);
    cmac_inst.cmac_csc2cmac_wt_5_62_in(cmac_csc2cmac_wt_5_signal[62]);
    cmac_inst.cmac_csc2cmac_wt_5_63_in(cmac_csc2cmac_wt_5_signal[63]);

    cmac_inst.cmac_csc2cmac_wt_6_0_in(cmac_csc2cmac_wt_6_signal[0]);
    cmac_inst.cmac_csc2cmac_wt_6_1_in(cmac_csc2cmac_wt_6_signal[1]);
    cmac_inst.cmac_csc2cmac_wt_6_2_in(cmac_csc2cmac_wt_6_signal[2]);
    cmac_inst.cmac_csc2cmac_wt_6_3_in(cmac_csc2cmac_wt_6_signal[3]);
    cmac_inst.cmac_csc2cmac_wt_6_4_in(cmac_csc2cmac_wt_6_signal[4]);
    cmac_inst.cmac_csc2cmac_wt_6_5_in(cmac_csc2cmac_wt_6_signal[5]);
    cmac_inst.cmac_csc2cmac_wt_6_6_in(cmac_csc2cmac_wt_6_signal[6]);
    cmac_inst.cmac_csc2cmac_wt_6_7_in(cmac_csc2cmac_wt_6_signal[7]);
    cmac_inst.cmac_csc2cmac_wt_6_8_in(cmac_csc2cmac_wt_6_signal[8]);
    cmac_inst.cmac_csc2cmac_wt_6_9_in(cmac_csc2cmac_wt_6_signal[9]);
    cmac_inst.cmac_csc2cmac_wt_6_10_in(cmac_csc2cmac_wt_6_signal[10]);
    cmac_inst.cmac_csc2cmac_wt_6_11_in(cmac_csc2cmac_wt_6_signal[11]);
    cmac_inst.cmac_csc2cmac_wt_6_12_in(cmac_csc2cmac_wt_6_signal[12]);
    cmac_inst.cmac_csc2cmac_wt_6_13_in(cmac_csc2cmac_wt_6_signal[13]);
    cmac_inst.cmac_csc2cmac_wt_6_14_in(cmac_csc2cmac_wt_6_signal[14]);
    cmac_inst.cmac_csc2cmac_wt_6_15_in(cmac_csc2cmac_wt_6_signal[15]);
    cmac_inst.cmac_csc2cmac_wt_6_16_in(cmac_csc2cmac_wt_6_signal[16]);
    cmac_inst.cmac_csc2cmac_wt_6_17_in(cmac_csc2cmac_wt_6_signal[17]);
    cmac_inst.cmac_csc2cmac_wt_6_18_in(cmac_csc2cmac_wt_6_signal[18]);
    cmac_inst.cmac_csc2cmac_wt_6_19_in(cmac_csc2cmac_wt_6_signal[19]);
    cmac_inst.cmac_csc2cmac_wt_6_20_in(cmac_csc2cmac_wt_6_signal[20]);
    cmac_inst.cmac_csc2cmac_wt_6_21_in(cmac_csc2cmac_wt_6_signal[21]);
    cmac_inst.cmac_csc2cmac_wt_6_22_in(cmac_csc2cmac_wt_6_signal[22]);
    cmac_inst.cmac_csc2cmac_wt_6_23_in(cmac_csc2cmac_wt_6_signal[23]);
    cmac_inst.cmac_csc2cmac_wt_6_24_in(cmac_csc2cmac_wt_6_signal[24]);
    cmac_inst.cmac_csc2cmac_wt_6_25_in(cmac_csc2cmac_wt_6_signal[25]);
    cmac_inst.cmac_csc2cmac_wt_6_26_in(cmac_csc2cmac_wt_6_signal[26]);
    cmac_inst.cmac_csc2cmac_wt_6_27_in(cmac_csc2cmac_wt_6_signal[27]);
    cmac_inst.cmac_csc2cmac_wt_6_28_in(cmac_csc2cmac_wt_6_signal[28]);
    cmac_inst.cmac_csc2cmac_wt_6_29_in(cmac_csc2cmac_wt_6_signal[29]);
    cmac_inst.cmac_csc2cmac_wt_6_30_in(cmac_csc2cmac_wt_6_signal[30]);
    cmac_inst.cmac_csc2cmac_wt_6_31_in(cmac_csc2cmac_wt_6_signal[31]);
    cmac_inst.cmac_csc2cmac_wt_6_32_in(cmac_csc2cmac_wt_6_signal[32]);
    cmac_inst.cmac_csc2cmac_wt_6_33_in(cmac_csc2cmac_wt_6_signal[33]);
    cmac_inst.cmac_csc2cmac_wt_6_34_in(cmac_csc2cmac_wt_6_signal[34]);
    cmac_inst.cmac_csc2cmac_wt_6_35_in(cmac_csc2cmac_wt_6_signal[35]);
    cmac_inst.cmac_csc2cmac_wt_6_36_in(cmac_csc2cmac_wt_6_signal[36]);
    cmac_inst.cmac_csc2cmac_wt_6_37_in(cmac_csc2cmac_wt_6_signal[37]);
    cmac_inst.cmac_csc2cmac_wt_6_38_in(cmac_csc2cmac_wt_6_signal[38]);
    cmac_inst.cmac_csc2cmac_wt_6_39_in(cmac_csc2cmac_wt_6_signal[39]);
    cmac_inst.cmac_csc2cmac_wt_6_40_in(cmac_csc2cmac_wt_6_signal[40]);
    cmac_inst.cmac_csc2cmac_wt_6_41_in(cmac_csc2cmac_wt_6_signal[41]);
    cmac_inst.cmac_csc2cmac_wt_6_42_in(cmac_csc2cmac_wt_6_signal[42]);
    cmac_inst.cmac_csc2cmac_wt_6_43_in(cmac_csc2cmac_wt_6_signal[43]);
    cmac_inst.cmac_csc2cmac_wt_6_44_in(cmac_csc2cmac_wt_6_signal[44]);
    cmac_inst.cmac_csc2cmac_wt_6_45_in(cmac_csc2cmac_wt_6_signal[45]);
    cmac_inst.cmac_csc2cmac_wt_6_46_in(cmac_csc2cmac_wt_6_signal[46]);
    cmac_inst.cmac_csc2cmac_wt_6_47_in(cmac_csc2cmac_wt_6_signal[47]);
    cmac_inst.cmac_csc2cmac_wt_6_48_in(cmac_csc2cmac_wt_6_signal[48]);
    cmac_inst.cmac_csc2cmac_wt_6_49_in(cmac_csc2cmac_wt_6_signal[49]);
    cmac_inst.cmac_csc2cmac_wt_6_50_in(cmac_csc2cmac_wt_6_signal[50]);
    cmac_inst.cmac_csc2cmac_wt_6_51_in(cmac_csc2cmac_wt_6_signal[51]);
    cmac_inst.cmac_csc2cmac_wt_6_52_in(cmac_csc2cmac_wt_6_signal[52]);
    cmac_inst.cmac_csc2cmac_wt_6_53_in(cmac_csc2cmac_wt_6_signal[53]);
    cmac_inst.cmac_csc2cmac_wt_6_54_in(cmac_csc2cmac_wt_6_signal[54]);
    cmac_inst.cmac_csc2cmac_wt_6_55_in(cmac_csc2cmac_wt_6_signal[55]);
    cmac_inst.cmac_csc2cmac_wt_6_56_in(cmac_csc2cmac_wt_6_signal[56]);
    cmac_inst.cmac_csc2cmac_wt_6_57_in(cmac_csc2cmac_wt_6_signal[57]);
    cmac_inst.cmac_csc2cmac_wt_6_58_in(cmac_csc2cmac_wt_6_signal[58]);
    cmac_inst.cmac_csc2cmac_wt_6_59_in(cmac_csc2cmac_wt_6_signal[59]);
    cmac_inst.cmac_csc2cmac_wt_6_60_in(cmac_csc2cmac_wt_6_signal[60]);
    cmac_inst.cmac_csc2cmac_wt_6_61_in(cmac_csc2cmac_wt_6_signal[61]);
    cmac_inst.cmac_csc2cmac_wt_6_62_in(cmac_csc2cmac_wt_6_signal[62]);
    cmac_inst.cmac_csc2cmac_wt_6_63_in(cmac_csc2cmac_wt_6_signal[63]);

    cmac_inst.cmac_csc2cmac_wt_7_0_in(cmac_csc2cmac_wt_7_signal[0]);
    cmac_inst.cmac_csc2cmac_wt_7_1_in(cmac_csc2cmac_wt_7_signal[1]);
    cmac_inst.cmac_csc2cmac_wt_7_2_in(cmac_csc2cmac_wt_7_signal[2]);
    cmac_inst.cmac_csc2cmac_wt_7_3_in(cmac_csc2cmac_wt_7_signal[3]);
    cmac_inst.cmac_csc2cmac_wt_7_4_in(cmac_csc2cmac_wt_7_signal[4]);
    cmac_inst.cmac_csc2cmac_wt_7_5_in(cmac_csc2cmac_wt_7_signal[5]);
    cmac_inst.cmac_csc2cmac_wt_7_6_in(cmac_csc2cmac_wt_7_signal[6]);
    cmac_inst.cmac_csc2cmac_wt_7_7_in(cmac_csc2cmac_wt_7_signal[7]);
    cmac_inst.cmac_csc2cmac_wt_7_8_in(cmac_csc2cmac_wt_7_signal[8]);
    cmac_inst.cmac_csc2cmac_wt_7_9_in(cmac_csc2cmac_wt_7_signal[9]);
    cmac_inst.cmac_csc2cmac_wt_7_10_in(cmac_csc2cmac_wt_7_signal[10]);
    cmac_inst.cmac_csc2cmac_wt_7_11_in(cmac_csc2cmac_wt_7_signal[11]);
    cmac_inst.cmac_csc2cmac_wt_7_12_in(cmac_csc2cmac_wt_7_signal[12]);
    cmac_inst.cmac_csc2cmac_wt_7_13_in(cmac_csc2cmac_wt_7_signal[13]);
    cmac_inst.cmac_csc2cmac_wt_7_14_in(cmac_csc2cmac_wt_7_signal[14]);
    cmac_inst.cmac_csc2cmac_wt_7_15_in(cmac_csc2cmac_wt_7_signal[15]);
    cmac_inst.cmac_csc2cmac_wt_7_16_in(cmac_csc2cmac_wt_7_signal[16]);
    cmac_inst.cmac_csc2cmac_wt_7_17_in(cmac_csc2cmac_wt_7_signal[17]);
    cmac_inst.cmac_csc2cmac_wt_7_18_in(cmac_csc2cmac_wt_7_signal[18]);
    cmac_inst.cmac_csc2cmac_wt_7_19_in(cmac_csc2cmac_wt_7_signal[19]);
    cmac_inst.cmac_csc2cmac_wt_7_20_in(cmac_csc2cmac_wt_7_signal[20]);
    cmac_inst.cmac_csc2cmac_wt_7_21_in(cmac_csc2cmac_wt_7_signal[21]);
    cmac_inst.cmac_csc2cmac_wt_7_22_in(cmac_csc2cmac_wt_7_signal[22]);
    cmac_inst.cmac_csc2cmac_wt_7_23_in(cmac_csc2cmac_wt_7_signal[23]);
    cmac_inst.cmac_csc2cmac_wt_7_24_in(cmac_csc2cmac_wt_7_signal[24]);
    cmac_inst.cmac_csc2cmac_wt_7_25_in(cmac_csc2cmac_wt_7_signal[25]);
    cmac_inst.cmac_csc2cmac_wt_7_26_in(cmac_csc2cmac_wt_7_signal[26]);
    cmac_inst.cmac_csc2cmac_wt_7_27_in(cmac_csc2cmac_wt_7_signal[27]);
    cmac_inst.cmac_csc2cmac_wt_7_28_in(cmac_csc2cmac_wt_7_signal[28]);
    cmac_inst.cmac_csc2cmac_wt_7_29_in(cmac_csc2cmac_wt_7_signal[29]);
    cmac_inst.cmac_csc2cmac_wt_7_30_in(cmac_csc2cmac_wt_7_signal[30]);
    cmac_inst.cmac_csc2cmac_wt_7_31_in(cmac_csc2cmac_wt_7_signal[31]);
    cmac_inst.cmac_csc2cmac_wt_7_32_in(cmac_csc2cmac_wt_7_signal[32]);
    cmac_inst.cmac_csc2cmac_wt_7_33_in(cmac_csc2cmac_wt_7_signal[33]);
    cmac_inst.cmac_csc2cmac_wt_7_34_in(cmac_csc2cmac_wt_7_signal[34]);
    cmac_inst.cmac_csc2cmac_wt_7_35_in(cmac_csc2cmac_wt_7_signal[35]);
    cmac_inst.cmac_csc2cmac_wt_7_36_in(cmac_csc2cmac_wt_7_signal[36]);
    cmac_inst.cmac_csc2cmac_wt_7_37_in(cmac_csc2cmac_wt_7_signal[37]);
    cmac_inst.cmac_csc2cmac_wt_7_38_in(cmac_csc2cmac_wt_7_signal[38]);
    cmac_inst.cmac_csc2cmac_wt_7_39_in(cmac_csc2cmac_wt_7_signal[39]);
    cmac_inst.cmac_csc2cmac_wt_7_40_in(cmac_csc2cmac_wt_7_signal[40]);
    cmac_inst.cmac_csc2cmac_wt_7_41_in(cmac_csc2cmac_wt_7_signal[41]);
    cmac_inst.cmac_csc2cmac_wt_7_42_in(cmac_csc2cmac_wt_7_signal[42]);
    cmac_inst.cmac_csc2cmac_wt_7_43_in(cmac_csc2cmac_wt_7_signal[43]);
    cmac_inst.cmac_csc2cmac_wt_7_44_in(cmac_csc2cmac_wt_7_signal[44]);
    cmac_inst.cmac_csc2cmac_wt_7_45_in(cmac_csc2cmac_wt_7_signal[45]);
    cmac_inst.cmac_csc2cmac_wt_7_46_in(cmac_csc2cmac_wt_7_signal[46]);
    cmac_inst.cmac_csc2cmac_wt_7_47_in(cmac_csc2cmac_wt_7_signal[47]);
    cmac_inst.cmac_csc2cmac_wt_7_48_in(cmac_csc2cmac_wt_7_signal[48]);
    cmac_inst.cmac_csc2cmac_wt_7_49_in(cmac_csc2cmac_wt_7_signal[49]);
    cmac_inst.cmac_csc2cmac_wt_7_50_in(cmac_csc2cmac_wt_7_signal[50]);
    cmac_inst.cmac_csc2cmac_wt_7_51_in(cmac_csc2cmac_wt_7_signal[51]);
    cmac_inst.cmac_csc2cmac_wt_7_52_in(cmac_csc2cmac_wt_7_signal[52]);
    cmac_inst.cmac_csc2cmac_wt_7_53_in(cmac_csc2cmac_wt_7_signal[53]);
    cmac_inst.cmac_csc2cmac_wt_7_54_in(cmac_csc2cmac_wt_7_signal[54]);
    cmac_inst.cmac_csc2cmac_wt_7_55_in(cmac_csc2cmac_wt_7_signal[55]);
    cmac_inst.cmac_csc2cmac_wt_7_56_in(cmac_csc2cmac_wt_7_signal[56]);
    cmac_inst.cmac_csc2cmac_wt_7_57_in(cmac_csc2cmac_wt_7_signal[57]);
    cmac_inst.cmac_csc2cmac_wt_7_58_in(cmac_csc2cmac_wt_7_signal[58]);
    cmac_inst.cmac_csc2cmac_wt_7_59_in(cmac_csc2cmac_wt_7_signal[59]);
    cmac_inst.cmac_csc2cmac_wt_7_60_in(cmac_csc2cmac_wt_7_signal[60]);
    cmac_inst.cmac_csc2cmac_wt_7_61_in(cmac_csc2cmac_wt_7_signal[61]);
    cmac_inst.cmac_csc2cmac_wt_7_62_in(cmac_csc2cmac_wt_7_signal[62]);
    cmac_inst.cmac_csc2cmac_wt_7_63_in(cmac_csc2cmac_wt_7_signal[63]);

    cmac_inst.cmac_csc2cmac_wt_8_0_in(cmac_csc2cmac_wt_8_signal[0]);
    cmac_inst.cmac_csc2cmac_wt_8_1_in(cmac_csc2cmac_wt_8_signal[1]);
    cmac_inst.cmac_csc2cmac_wt_8_2_in(cmac_csc2cmac_wt_8_signal[2]);
    cmac_inst.cmac_csc2cmac_wt_8_3_in(cmac_csc2cmac_wt_8_signal[3]);
    cmac_inst.cmac_csc2cmac_wt_8_4_in(cmac_csc2cmac_wt_8_signal[4]);
    cmac_inst.cmac_csc2cmac_wt_8_5_in(cmac_csc2cmac_wt_8_signal[5]);
    cmac_inst.cmac_csc2cmac_wt_8_6_in(cmac_csc2cmac_wt_8_signal[6]);
    cmac_inst.cmac_csc2cmac_wt_8_7_in(cmac_csc2cmac_wt_8_signal[7]);
    cmac_inst.cmac_csc2cmac_wt_8_8_in(cmac_csc2cmac_wt_8_signal[8]);
    cmac_inst.cmac_csc2cmac_wt_8_9_in(cmac_csc2cmac_wt_8_signal[9]);
    cmac_inst.cmac_csc2cmac_wt_8_10_in(cmac_csc2cmac_wt_8_signal[10]);
    cmac_inst.cmac_csc2cmac_wt_8_11_in(cmac_csc2cmac_wt_8_signal[11]);
    cmac_inst.cmac_csc2cmac_wt_8_12_in(cmac_csc2cmac_wt_8_signal[12]);
    cmac_inst.cmac_csc2cmac_wt_8_13_in(cmac_csc2cmac_wt_8_signal[13]);
    cmac_inst.cmac_csc2cmac_wt_8_14_in(cmac_csc2cmac_wt_8_signal[14]);
    cmac_inst.cmac_csc2cmac_wt_8_15_in(cmac_csc2cmac_wt_8_signal[15]);
    cmac_inst.cmac_csc2cmac_wt_8_16_in(cmac_csc2cmac_wt_8_signal[16]);
    cmac_inst.cmac_csc2cmac_wt_8_17_in(cmac_csc2cmac_wt_8_signal[17]);
    cmac_inst.cmac_csc2cmac_wt_8_18_in(cmac_csc2cmac_wt_8_signal[18]);
    cmac_inst.cmac_csc2cmac_wt_8_19_in(cmac_csc2cmac_wt_8_signal[19]);
    cmac_inst.cmac_csc2cmac_wt_8_20_in(cmac_csc2cmac_wt_8_signal[20]);
    cmac_inst.cmac_csc2cmac_wt_8_21_in(cmac_csc2cmac_wt_8_signal[21]);
    cmac_inst.cmac_csc2cmac_wt_8_22_in(cmac_csc2cmac_wt_8_signal[22]);
    cmac_inst.cmac_csc2cmac_wt_8_23_in(cmac_csc2cmac_wt_8_signal[23]);
    cmac_inst.cmac_csc2cmac_wt_8_24_in(cmac_csc2cmac_wt_8_signal[24]);
    cmac_inst.cmac_csc2cmac_wt_8_25_in(cmac_csc2cmac_wt_8_signal[25]);
    cmac_inst.cmac_csc2cmac_wt_8_26_in(cmac_csc2cmac_wt_8_signal[26]);
    cmac_inst.cmac_csc2cmac_wt_8_27_in(cmac_csc2cmac_wt_8_signal[27]);
    cmac_inst.cmac_csc2cmac_wt_8_28_in(cmac_csc2cmac_wt_8_signal[28]);
    cmac_inst.cmac_csc2cmac_wt_8_29_in(cmac_csc2cmac_wt_8_signal[29]);
    cmac_inst.cmac_csc2cmac_wt_8_30_in(cmac_csc2cmac_wt_8_signal[30]);
    cmac_inst.cmac_csc2cmac_wt_8_31_in(cmac_csc2cmac_wt_8_signal[31]);
    cmac_inst.cmac_csc2cmac_wt_8_32_in(cmac_csc2cmac_wt_8_signal[32]);
    cmac_inst.cmac_csc2cmac_wt_8_33_in(cmac_csc2cmac_wt_8_signal[33]);
    cmac_inst.cmac_csc2cmac_wt_8_34_in(cmac_csc2cmac_wt_8_signal[34]);
    cmac_inst.cmac_csc2cmac_wt_8_35_in(cmac_csc2cmac_wt_8_signal[35]);
    cmac_inst.cmac_csc2cmac_wt_8_36_in(cmac_csc2cmac_wt_8_signal[36]);
    cmac_inst.cmac_csc2cmac_wt_8_37_in(cmac_csc2cmac_wt_8_signal[37]);
    cmac_inst.cmac_csc2cmac_wt_8_38_in(cmac_csc2cmac_wt_8_signal[38]);
    cmac_inst.cmac_csc2cmac_wt_8_39_in(cmac_csc2cmac_wt_8_signal[39]);
    cmac_inst.cmac_csc2cmac_wt_8_40_in(cmac_csc2cmac_wt_8_signal[40]);
    cmac_inst.cmac_csc2cmac_wt_8_41_in(cmac_csc2cmac_wt_8_signal[41]);
    cmac_inst.cmac_csc2cmac_wt_8_42_in(cmac_csc2cmac_wt_8_signal[42]);
    cmac_inst.cmac_csc2cmac_wt_8_43_in(cmac_csc2cmac_wt_8_signal[43]);
    cmac_inst.cmac_csc2cmac_wt_8_44_in(cmac_csc2cmac_wt_8_signal[44]);
    cmac_inst.cmac_csc2cmac_wt_8_45_in(cmac_csc2cmac_wt_8_signal[45]);
    cmac_inst.cmac_csc2cmac_wt_8_46_in(cmac_csc2cmac_wt_8_signal[46]);
    cmac_inst.cmac_csc2cmac_wt_8_47_in(cmac_csc2cmac_wt_8_signal[47]);
    cmac_inst.cmac_csc2cmac_wt_8_48_in(cmac_csc2cmac_wt_8_signal[48]);
    cmac_inst.cmac_csc2cmac_wt_8_49_in(cmac_csc2cmac_wt_8_signal[49]);
    cmac_inst.cmac_csc2cmac_wt_8_50_in(cmac_csc2cmac_wt_8_signal[50]);
    cmac_inst.cmac_csc2cmac_wt_8_51_in(cmac_csc2cmac_wt_8_signal[51]);
    cmac_inst.cmac_csc2cmac_wt_8_52_in(cmac_csc2cmac_wt_8_signal[52]);
    cmac_inst.cmac_csc2cmac_wt_8_53_in(cmac_csc2cmac_wt_8_signal[53]);
    cmac_inst.cmac_csc2cmac_wt_8_54_in(cmac_csc2cmac_wt_8_signal[54]);
    cmac_inst.cmac_csc2cmac_wt_8_55_in(cmac_csc2cmac_wt_8_signal[55]);
    cmac_inst.cmac_csc2cmac_wt_8_56_in(cmac_csc2cmac_wt_8_signal[56]);
    cmac_inst.cmac_csc2cmac_wt_8_57_in(cmac_csc2cmac_wt_8_signal[57]);
    cmac_inst.cmac_csc2cmac_wt_8_58_in(cmac_csc2cmac_wt_8_signal[58]);
    cmac_inst.cmac_csc2cmac_wt_8_59_in(cmac_csc2cmac_wt_8_signal[59]);
    cmac_inst.cmac_csc2cmac_wt_8_60_in(cmac_csc2cmac_wt_8_signal[60]);
    cmac_inst.cmac_csc2cmac_wt_8_61_in(cmac_csc2cmac_wt_8_signal[61]);
    cmac_inst.cmac_csc2cmac_wt_8_62_in(cmac_csc2cmac_wt_8_signal[62]);
    cmac_inst.cmac_csc2cmac_wt_8_63_in(cmac_csc2cmac_wt_8_signal[63]);

    cmac_inst.cmac_csc2cmac_wt_9_0_in(cmac_csc2cmac_wt_9_signal[0]);
    cmac_inst.cmac_csc2cmac_wt_9_1_in(cmac_csc2cmac_wt_9_signal[1]);
    cmac_inst.cmac_csc2cmac_wt_9_2_in(cmac_csc2cmac_wt_9_signal[2]);
    cmac_inst.cmac_csc2cmac_wt_9_3_in(cmac_csc2cmac_wt_9_signal[3]);
    cmac_inst.cmac_csc2cmac_wt_9_4_in(cmac_csc2cmac_wt_9_signal[4]);
    cmac_inst.cmac_csc2cmac_wt_9_5_in(cmac_csc2cmac_wt_9_signal[5]);
    cmac_inst.cmac_csc2cmac_wt_9_6_in(cmac_csc2cmac_wt_9_signal[6]);
    cmac_inst.cmac_csc2cmac_wt_9_7_in(cmac_csc2cmac_wt_9_signal[7]);
    cmac_inst.cmac_csc2cmac_wt_9_8_in(cmac_csc2cmac_wt_9_signal[8]);
    cmac_inst.cmac_csc2cmac_wt_9_9_in(cmac_csc2cmac_wt_9_signal[9]);
    cmac_inst.cmac_csc2cmac_wt_9_10_in(cmac_csc2cmac_wt_9_signal[10]);
    cmac_inst.cmac_csc2cmac_wt_9_11_in(cmac_csc2cmac_wt_9_signal[11]);
    cmac_inst.cmac_csc2cmac_wt_9_12_in(cmac_csc2cmac_wt_9_signal[12]);
    cmac_inst.cmac_csc2cmac_wt_9_13_in(cmac_csc2cmac_wt_9_signal[13]);
    cmac_inst.cmac_csc2cmac_wt_9_14_in(cmac_csc2cmac_wt_9_signal[14]);
    cmac_inst.cmac_csc2cmac_wt_9_15_in(cmac_csc2cmac_wt_9_signal[15]);
    cmac_inst.cmac_csc2cmac_wt_9_16_in(cmac_csc2cmac_wt_9_signal[16]);
    cmac_inst.cmac_csc2cmac_wt_9_17_in(cmac_csc2cmac_wt_9_signal[17]);
    cmac_inst.cmac_csc2cmac_wt_9_18_in(cmac_csc2cmac_wt_9_signal[18]);
    cmac_inst.cmac_csc2cmac_wt_9_19_in(cmac_csc2cmac_wt_9_signal[19]);
    cmac_inst.cmac_csc2cmac_wt_9_20_in(cmac_csc2cmac_wt_9_signal[20]);
    cmac_inst.cmac_csc2cmac_wt_9_21_in(cmac_csc2cmac_wt_9_signal[21]);
    cmac_inst.cmac_csc2cmac_wt_9_22_in(cmac_csc2cmac_wt_9_signal[22]);
    cmac_inst.cmac_csc2cmac_wt_9_23_in(cmac_csc2cmac_wt_9_signal[23]);
    cmac_inst.cmac_csc2cmac_wt_9_24_in(cmac_csc2cmac_wt_9_signal[24]);
    cmac_inst.cmac_csc2cmac_wt_9_25_in(cmac_csc2cmac_wt_9_signal[25]);
    cmac_inst.cmac_csc2cmac_wt_9_26_in(cmac_csc2cmac_wt_9_signal[26]);
    cmac_inst.cmac_csc2cmac_wt_9_27_in(cmac_csc2cmac_wt_9_signal[27]);
    cmac_inst.cmac_csc2cmac_wt_9_28_in(cmac_csc2cmac_wt_9_signal[28]);
    cmac_inst.cmac_csc2cmac_wt_9_29_in(cmac_csc2cmac_wt_9_signal[29]);
    cmac_inst.cmac_csc2cmac_wt_9_30_in(cmac_csc2cmac_wt_9_signal[30]);
    cmac_inst.cmac_csc2cmac_wt_9_31_in(cmac_csc2cmac_wt_9_signal[31]);
    cmac_inst.cmac_csc2cmac_wt_9_32_in(cmac_csc2cmac_wt_9_signal[32]);
    cmac_inst.cmac_csc2cmac_wt_9_33_in(cmac_csc2cmac_wt_9_signal[33]);
    cmac_inst.cmac_csc2cmac_wt_9_34_in(cmac_csc2cmac_wt_9_signal[34]);
    cmac_inst.cmac_csc2cmac_wt_9_35_in(cmac_csc2cmac_wt_9_signal[35]);
    cmac_inst.cmac_csc2cmac_wt_9_36_in(cmac_csc2cmac_wt_9_signal[36]);
    cmac_inst.cmac_csc2cmac_wt_9_37_in(cmac_csc2cmac_wt_9_signal[37]);
    cmac_inst.cmac_csc2cmac_wt_9_38_in(cmac_csc2cmac_wt_9_signal[38]);
    cmac_inst.cmac_csc2cmac_wt_9_39_in(cmac_csc2cmac_wt_9_signal[39]);
    cmac_inst.cmac_csc2cmac_wt_9_40_in(cmac_csc2cmac_wt_9_signal[40]);
    cmac_inst.cmac_csc2cmac_wt_9_41_in(cmac_csc2cmac_wt_9_signal[41]);
    cmac_inst.cmac_csc2cmac_wt_9_42_in(cmac_csc2cmac_wt_9_signal[42]);
    cmac_inst.cmac_csc2cmac_wt_9_43_in(cmac_csc2cmac_wt_9_signal[43]);
    cmac_inst.cmac_csc2cmac_wt_9_44_in(cmac_csc2cmac_wt_9_signal[44]);
    cmac_inst.cmac_csc2cmac_wt_9_45_in(cmac_csc2cmac_wt_9_signal[45]);
    cmac_inst.cmac_csc2cmac_wt_9_46_in(cmac_csc2cmac_wt_9_signal[46]);
    cmac_inst.cmac_csc2cmac_wt_9_47_in(cmac_csc2cmac_wt_9_signal[47]);
    cmac_inst.cmac_csc2cmac_wt_9_48_in(cmac_csc2cmac_wt_9_signal[48]);
    cmac_inst.cmac_csc2cmac_wt_9_49_in(cmac_csc2cmac_wt_9_signal[49]);
    cmac_inst.cmac_csc2cmac_wt_9_50_in(cmac_csc2cmac_wt_9_signal[50]);
    cmac_inst.cmac_csc2cmac_wt_9_51_in(cmac_csc2cmac_wt_9_signal[51]);
    cmac_inst.cmac_csc2cmac_wt_9_52_in(cmac_csc2cmac_wt_9_signal[52]);
    cmac_inst.cmac_csc2cmac_wt_9_53_in(cmac_csc2cmac_wt_9_signal[53]);
    cmac_inst.cmac_csc2cmac_wt_9_54_in(cmac_csc2cmac_wt_9_signal[54]);
    cmac_inst.cmac_csc2cmac_wt_9_55_in(cmac_csc2cmac_wt_9_signal[55]);
    cmac_inst.cmac_csc2cmac_wt_9_56_in(cmac_csc2cmac_wt_9_signal[56]);
    cmac_inst.cmac_csc2cmac_wt_9_57_in(cmac_csc2cmac_wt_9_signal[57]);
    cmac_inst.cmac_csc2cmac_wt_9_58_in(cmac_csc2cmac_wt_9_signal[58]);
    cmac_inst.cmac_csc2cmac_wt_9_59_in(cmac_csc2cmac_wt_9_signal[59]);
    cmac_inst.cmac_csc2cmac_wt_9_60_in(cmac_csc2cmac_wt_9_signal[60]);
    cmac_inst.cmac_csc2cmac_wt_9_61_in(cmac_csc2cmac_wt_9_signal[61]);
    cmac_inst.cmac_csc2cmac_wt_9_62_in(cmac_csc2cmac_wt_9_signal[62]);
    cmac_inst.cmac_csc2cmac_wt_9_63_in(cmac_csc2cmac_wt_9_signal[63]);

    cmac_inst.cmac_csc2cmac_wt_10_0_in(cmac_csc2cmac_wt_10_signal[0]);
    cmac_inst.cmac_csc2cmac_wt_10_1_in(cmac_csc2cmac_wt_10_signal[1]);
    cmac_inst.cmac_csc2cmac_wt_10_2_in(cmac_csc2cmac_wt_10_signal[2]);
    cmac_inst.cmac_csc2cmac_wt_10_3_in(cmac_csc2cmac_wt_10_signal[3]);
    cmac_inst.cmac_csc2cmac_wt_10_4_in(cmac_csc2cmac_wt_10_signal[4]);
    cmac_inst.cmac_csc2cmac_wt_10_5_in(cmac_csc2cmac_wt_10_signal[5]);
    cmac_inst.cmac_csc2cmac_wt_10_6_in(cmac_csc2cmac_wt_10_signal[6]);
    cmac_inst.cmac_csc2cmac_wt_10_7_in(cmac_csc2cmac_wt_10_signal[7]);
    cmac_inst.cmac_csc2cmac_wt_10_8_in(cmac_csc2cmac_wt_10_signal[8]);
    cmac_inst.cmac_csc2cmac_wt_10_9_in(cmac_csc2cmac_wt_10_signal[9]);
    cmac_inst.cmac_csc2cmac_wt_10_10_in(cmac_csc2cmac_wt_10_signal[10]);
    cmac_inst.cmac_csc2cmac_wt_10_11_in(cmac_csc2cmac_wt_10_signal[11]);
    cmac_inst.cmac_csc2cmac_wt_10_12_in(cmac_csc2cmac_wt_10_signal[12]);
    cmac_inst.cmac_csc2cmac_wt_10_13_in(cmac_csc2cmac_wt_10_signal[13]);
    cmac_inst.cmac_csc2cmac_wt_10_14_in(cmac_csc2cmac_wt_10_signal[14]);
    cmac_inst.cmac_csc2cmac_wt_10_15_in(cmac_csc2cmac_wt_10_signal[15]);
    cmac_inst.cmac_csc2cmac_wt_10_16_in(cmac_csc2cmac_wt_10_signal[16]);
    cmac_inst.cmac_csc2cmac_wt_10_17_in(cmac_csc2cmac_wt_10_signal[17]);
    cmac_inst.cmac_csc2cmac_wt_10_18_in(cmac_csc2cmac_wt_10_signal[18]);
    cmac_inst.cmac_csc2cmac_wt_10_19_in(cmac_csc2cmac_wt_10_signal[19]);
    cmac_inst.cmac_csc2cmac_wt_10_20_in(cmac_csc2cmac_wt_10_signal[20]);
    cmac_inst.cmac_csc2cmac_wt_10_21_in(cmac_csc2cmac_wt_10_signal[21]);
    cmac_inst.cmac_csc2cmac_wt_10_22_in(cmac_csc2cmac_wt_10_signal[22]);
    cmac_inst.cmac_csc2cmac_wt_10_23_in(cmac_csc2cmac_wt_10_signal[23]);
    cmac_inst.cmac_csc2cmac_wt_10_24_in(cmac_csc2cmac_wt_10_signal[24]);
    cmac_inst.cmac_csc2cmac_wt_10_25_in(cmac_csc2cmac_wt_10_signal[25]);
    cmac_inst.cmac_csc2cmac_wt_10_26_in(cmac_csc2cmac_wt_10_signal[26]);
    cmac_inst.cmac_csc2cmac_wt_10_27_in(cmac_csc2cmac_wt_10_signal[27]);
    cmac_inst.cmac_csc2cmac_wt_10_28_in(cmac_csc2cmac_wt_10_signal[28]);
    cmac_inst.cmac_csc2cmac_wt_10_29_in(cmac_csc2cmac_wt_10_signal[29]);
    cmac_inst.cmac_csc2cmac_wt_10_30_in(cmac_csc2cmac_wt_10_signal[30]);
    cmac_inst.cmac_csc2cmac_wt_10_31_in(cmac_csc2cmac_wt_10_signal[31]);
    cmac_inst.cmac_csc2cmac_wt_10_32_in(cmac_csc2cmac_wt_10_signal[32]);
    cmac_inst.cmac_csc2cmac_wt_10_33_in(cmac_csc2cmac_wt_10_signal[33]);
    cmac_inst.cmac_csc2cmac_wt_10_34_in(cmac_csc2cmac_wt_10_signal[34]);
    cmac_inst.cmac_csc2cmac_wt_10_35_in(cmac_csc2cmac_wt_10_signal[35]);
    cmac_inst.cmac_csc2cmac_wt_10_36_in(cmac_csc2cmac_wt_10_signal[36]);
    cmac_inst.cmac_csc2cmac_wt_10_37_in(cmac_csc2cmac_wt_10_signal[37]);
    cmac_inst.cmac_csc2cmac_wt_10_38_in(cmac_csc2cmac_wt_10_signal[38]);
    cmac_inst.cmac_csc2cmac_wt_10_39_in(cmac_csc2cmac_wt_10_signal[39]);
    cmac_inst.cmac_csc2cmac_wt_10_40_in(cmac_csc2cmac_wt_10_signal[40]);
    cmac_inst.cmac_csc2cmac_wt_10_41_in(cmac_csc2cmac_wt_10_signal[41]);
    cmac_inst.cmac_csc2cmac_wt_10_42_in(cmac_csc2cmac_wt_10_signal[42]);
    cmac_inst.cmac_csc2cmac_wt_10_43_in(cmac_csc2cmac_wt_10_signal[43]);
    cmac_inst.cmac_csc2cmac_wt_10_44_in(cmac_csc2cmac_wt_10_signal[44]);
    cmac_inst.cmac_csc2cmac_wt_10_45_in(cmac_csc2cmac_wt_10_signal[45]);
    cmac_inst.cmac_csc2cmac_wt_10_46_in(cmac_csc2cmac_wt_10_signal[46]);
    cmac_inst.cmac_csc2cmac_wt_10_47_in(cmac_csc2cmac_wt_10_signal[47]);
    cmac_inst.cmac_csc2cmac_wt_10_48_in(cmac_csc2cmac_wt_10_signal[48]);
    cmac_inst.cmac_csc2cmac_wt_10_49_in(cmac_csc2cmac_wt_10_signal[49]);
    cmac_inst.cmac_csc2cmac_wt_10_50_in(cmac_csc2cmac_wt_10_signal[50]);
    cmac_inst.cmac_csc2cmac_wt_10_51_in(cmac_csc2cmac_wt_10_signal[51]);
    cmac_inst.cmac_csc2cmac_wt_10_52_in(cmac_csc2cmac_wt_10_signal[52]);
    cmac_inst.cmac_csc2cmac_wt_10_53_in(cmac_csc2cmac_wt_10_signal[53]);
    cmac_inst.cmac_csc2cmac_wt_10_54_in(cmac_csc2cmac_wt_10_signal[54]);
    cmac_inst.cmac_csc2cmac_wt_10_55_in(cmac_csc2cmac_wt_10_signal[55]);
    cmac_inst.cmac_csc2cmac_wt_10_56_in(cmac_csc2cmac_wt_10_signal[56]);
    cmac_inst.cmac_csc2cmac_wt_10_57_in(cmac_csc2cmac_wt_10_signal[57]);
    cmac_inst.cmac_csc2cmac_wt_10_58_in(cmac_csc2cmac_wt_10_signal[58]);
    cmac_inst.cmac_csc2cmac_wt_10_59_in(cmac_csc2cmac_wt_10_signal[59]);
    cmac_inst.cmac_csc2cmac_wt_10_60_in(cmac_csc2cmac_wt_10_signal[60]);
    cmac_inst.cmac_csc2cmac_wt_10_61_in(cmac_csc2cmac_wt_10_signal[61]);
    cmac_inst.cmac_csc2cmac_wt_10_62_in(cmac_csc2cmac_wt_10_signal[62]);
    cmac_inst.cmac_csc2cmac_wt_10_63_in(cmac_csc2cmac_wt_10_signal[63]);

    cmac_inst.cmac_csc2cmac_wt_11_0_in(cmac_csc2cmac_wt_11_signal[0]);
    cmac_inst.cmac_csc2cmac_wt_11_1_in(cmac_csc2cmac_wt_11_signal[1]);
    cmac_inst.cmac_csc2cmac_wt_11_2_in(cmac_csc2cmac_wt_11_signal[2]);
    cmac_inst.cmac_csc2cmac_wt_11_3_in(cmac_csc2cmac_wt_11_signal[3]);
    cmac_inst.cmac_csc2cmac_wt_11_4_in(cmac_csc2cmac_wt_11_signal[4]);
    cmac_inst.cmac_csc2cmac_wt_11_5_in(cmac_csc2cmac_wt_11_signal[5]);
    cmac_inst.cmac_csc2cmac_wt_11_6_in(cmac_csc2cmac_wt_11_signal[6]);
    cmac_inst.cmac_csc2cmac_wt_11_7_in(cmac_csc2cmac_wt_11_signal[7]);
    cmac_inst.cmac_csc2cmac_wt_11_8_in(cmac_csc2cmac_wt_11_signal[8]);
    cmac_inst.cmac_csc2cmac_wt_11_9_in(cmac_csc2cmac_wt_11_signal[9]);
    cmac_inst.cmac_csc2cmac_wt_11_10_in(cmac_csc2cmac_wt_11_signal[10]);
    cmac_inst.cmac_csc2cmac_wt_11_11_in(cmac_csc2cmac_wt_11_signal[11]);
    cmac_inst.cmac_csc2cmac_wt_11_12_in(cmac_csc2cmac_wt_11_signal[12]);
    cmac_inst.cmac_csc2cmac_wt_11_13_in(cmac_csc2cmac_wt_11_signal[13]);
    cmac_inst.cmac_csc2cmac_wt_11_14_in(cmac_csc2cmac_wt_11_signal[14]);
    cmac_inst.cmac_csc2cmac_wt_11_15_in(cmac_csc2cmac_wt_11_signal[15]);
    cmac_inst.cmac_csc2cmac_wt_11_16_in(cmac_csc2cmac_wt_11_signal[16]);
    cmac_inst.cmac_csc2cmac_wt_11_17_in(cmac_csc2cmac_wt_11_signal[17]);
    cmac_inst.cmac_csc2cmac_wt_11_18_in(cmac_csc2cmac_wt_11_signal[18]);
    cmac_inst.cmac_csc2cmac_wt_11_19_in(cmac_csc2cmac_wt_11_signal[19]);
    cmac_inst.cmac_csc2cmac_wt_11_20_in(cmac_csc2cmac_wt_11_signal[20]);
    cmac_inst.cmac_csc2cmac_wt_11_21_in(cmac_csc2cmac_wt_11_signal[21]);
    cmac_inst.cmac_csc2cmac_wt_11_22_in(cmac_csc2cmac_wt_11_signal[22]);
    cmac_inst.cmac_csc2cmac_wt_11_23_in(cmac_csc2cmac_wt_11_signal[23]);
    cmac_inst.cmac_csc2cmac_wt_11_24_in(cmac_csc2cmac_wt_11_signal[24]);
    cmac_inst.cmac_csc2cmac_wt_11_25_in(cmac_csc2cmac_wt_11_signal[25]);
    cmac_inst.cmac_csc2cmac_wt_11_26_in(cmac_csc2cmac_wt_11_signal[26]);
    cmac_inst.cmac_csc2cmac_wt_11_27_in(cmac_csc2cmac_wt_11_signal[27]);
    cmac_inst.cmac_csc2cmac_wt_11_28_in(cmac_csc2cmac_wt_11_signal[28]);
    cmac_inst.cmac_csc2cmac_wt_11_29_in(cmac_csc2cmac_wt_11_signal[29]);
    cmac_inst.cmac_csc2cmac_wt_11_30_in(cmac_csc2cmac_wt_11_signal[30]);
    cmac_inst.cmac_csc2cmac_wt_11_31_in(cmac_csc2cmac_wt_11_signal[31]);
    cmac_inst.cmac_csc2cmac_wt_11_32_in(cmac_csc2cmac_wt_11_signal[32]);
    cmac_inst.cmac_csc2cmac_wt_11_33_in(cmac_csc2cmac_wt_11_signal[33]);
    cmac_inst.cmac_csc2cmac_wt_11_34_in(cmac_csc2cmac_wt_11_signal[34]);
    cmac_inst.cmac_csc2cmac_wt_11_35_in(cmac_csc2cmac_wt_11_signal[35]);
    cmac_inst.cmac_csc2cmac_wt_11_36_in(cmac_csc2cmac_wt_11_signal[36]);
    cmac_inst.cmac_csc2cmac_wt_11_37_in(cmac_csc2cmac_wt_11_signal[37]);
    cmac_inst.cmac_csc2cmac_wt_11_38_in(cmac_csc2cmac_wt_11_signal[38]);
    cmac_inst.cmac_csc2cmac_wt_11_39_in(cmac_csc2cmac_wt_11_signal[39]);
    cmac_inst.cmac_csc2cmac_wt_11_40_in(cmac_csc2cmac_wt_11_signal[40]);
    cmac_inst.cmac_csc2cmac_wt_11_41_in(cmac_csc2cmac_wt_11_signal[41]);
    cmac_inst.cmac_csc2cmac_wt_11_42_in(cmac_csc2cmac_wt_11_signal[42]);
    cmac_inst.cmac_csc2cmac_wt_11_43_in(cmac_csc2cmac_wt_11_signal[43]);
    cmac_inst.cmac_csc2cmac_wt_11_44_in(cmac_csc2cmac_wt_11_signal[44]);
    cmac_inst.cmac_csc2cmac_wt_11_45_in(cmac_csc2cmac_wt_11_signal[45]);
    cmac_inst.cmac_csc2cmac_wt_11_46_in(cmac_csc2cmac_wt_11_signal[46]);
    cmac_inst.cmac_csc2cmac_wt_11_47_in(cmac_csc2cmac_wt_11_signal[47]);
    cmac_inst.cmac_csc2cmac_wt_11_48_in(cmac_csc2cmac_wt_11_signal[48]);
    cmac_inst.cmac_csc2cmac_wt_11_49_in(cmac_csc2cmac_wt_11_signal[49]);
    cmac_inst.cmac_csc2cmac_wt_11_50_in(cmac_csc2cmac_wt_11_signal[50]);
    cmac_inst.cmac_csc2cmac_wt_11_51_in(cmac_csc2cmac_wt_11_signal[51]);
    cmac_inst.cmac_csc2cmac_wt_11_52_in(cmac_csc2cmac_wt_11_signal[52]);
    cmac_inst.cmac_csc2cmac_wt_11_53_in(cmac_csc2cmac_wt_11_signal[53]);
    cmac_inst.cmac_csc2cmac_wt_11_54_in(cmac_csc2cmac_wt_11_signal[54]);
    cmac_inst.cmac_csc2cmac_wt_11_55_in(cmac_csc2cmac_wt_11_signal[55]);
    cmac_inst.cmac_csc2cmac_wt_11_56_in(cmac_csc2cmac_wt_11_signal[56]);
    cmac_inst.cmac_csc2cmac_wt_11_57_in(cmac_csc2cmac_wt_11_signal[57]);
    cmac_inst.cmac_csc2cmac_wt_11_58_in(cmac_csc2cmac_wt_11_signal[58]);
    cmac_inst.cmac_csc2cmac_wt_11_59_in(cmac_csc2cmac_wt_11_signal[59]);
    cmac_inst.cmac_csc2cmac_wt_11_60_in(cmac_csc2cmac_wt_11_signal[60]);
    cmac_inst.cmac_csc2cmac_wt_11_61_in(cmac_csc2cmac_wt_11_signal[61]);
    cmac_inst.cmac_csc2cmac_wt_11_62_in(cmac_csc2cmac_wt_11_signal[62]);
    cmac_inst.cmac_csc2cmac_wt_11_63_in(cmac_csc2cmac_wt_11_signal[63]);

    cmac_inst.cmac_csc2cmac_wt_12_0_in(cmac_csc2cmac_wt_12_signal[0]);
    cmac_inst.cmac_csc2cmac_wt_12_1_in(cmac_csc2cmac_wt_12_signal[1]);
    cmac_inst.cmac_csc2cmac_wt_12_2_in(cmac_csc2cmac_wt_12_signal[2]);
    cmac_inst.cmac_csc2cmac_wt_12_3_in(cmac_csc2cmac_wt_12_signal[3]);
    cmac_inst.cmac_csc2cmac_wt_12_4_in(cmac_csc2cmac_wt_12_signal[4]);
    cmac_inst.cmac_csc2cmac_wt_12_5_in(cmac_csc2cmac_wt_12_signal[5]);
    cmac_inst.cmac_csc2cmac_wt_12_6_in(cmac_csc2cmac_wt_12_signal[6]);
    cmac_inst.cmac_csc2cmac_wt_12_7_in(cmac_csc2cmac_wt_12_signal[7]);
    cmac_inst.cmac_csc2cmac_wt_12_8_in(cmac_csc2cmac_wt_12_signal[8]);
    cmac_inst.cmac_csc2cmac_wt_12_9_in(cmac_csc2cmac_wt_12_signal[9]);
    cmac_inst.cmac_csc2cmac_wt_12_10_in(cmac_csc2cmac_wt_12_signal[10]);
    cmac_inst.cmac_csc2cmac_wt_12_11_in(cmac_csc2cmac_wt_12_signal[11]);
    cmac_inst.cmac_csc2cmac_wt_12_12_in(cmac_csc2cmac_wt_12_signal[12]);
    cmac_inst.cmac_csc2cmac_wt_12_13_in(cmac_csc2cmac_wt_12_signal[13]);
    cmac_inst.cmac_csc2cmac_wt_12_14_in(cmac_csc2cmac_wt_12_signal[14]);
    cmac_inst.cmac_csc2cmac_wt_12_15_in(cmac_csc2cmac_wt_12_signal[15]);
    cmac_inst.cmac_csc2cmac_wt_12_16_in(cmac_csc2cmac_wt_12_signal[16]);
    cmac_inst.cmac_csc2cmac_wt_12_17_in(cmac_csc2cmac_wt_12_signal[17]);
    cmac_inst.cmac_csc2cmac_wt_12_18_in(cmac_csc2cmac_wt_12_signal[18]);
    cmac_inst.cmac_csc2cmac_wt_12_19_in(cmac_csc2cmac_wt_12_signal[19]);
    cmac_inst.cmac_csc2cmac_wt_12_20_in(cmac_csc2cmac_wt_12_signal[20]);
    cmac_inst.cmac_csc2cmac_wt_12_21_in(cmac_csc2cmac_wt_12_signal[21]);
    cmac_inst.cmac_csc2cmac_wt_12_22_in(cmac_csc2cmac_wt_12_signal[22]);
    cmac_inst.cmac_csc2cmac_wt_12_23_in(cmac_csc2cmac_wt_12_signal[23]);
    cmac_inst.cmac_csc2cmac_wt_12_24_in(cmac_csc2cmac_wt_12_signal[24]);
    cmac_inst.cmac_csc2cmac_wt_12_25_in(cmac_csc2cmac_wt_12_signal[25]);
    cmac_inst.cmac_csc2cmac_wt_12_26_in(cmac_csc2cmac_wt_12_signal[26]);
    cmac_inst.cmac_csc2cmac_wt_12_27_in(cmac_csc2cmac_wt_12_signal[27]);
    cmac_inst.cmac_csc2cmac_wt_12_28_in(cmac_csc2cmac_wt_12_signal[28]);
    cmac_inst.cmac_csc2cmac_wt_12_29_in(cmac_csc2cmac_wt_12_signal[29]);
    cmac_inst.cmac_csc2cmac_wt_12_30_in(cmac_csc2cmac_wt_12_signal[30]);
    cmac_inst.cmac_csc2cmac_wt_12_31_in(cmac_csc2cmac_wt_12_signal[31]);
    cmac_inst.cmac_csc2cmac_wt_12_32_in(cmac_csc2cmac_wt_12_signal[32]);
    cmac_inst.cmac_csc2cmac_wt_12_33_in(cmac_csc2cmac_wt_12_signal[33]);
    cmac_inst.cmac_csc2cmac_wt_12_34_in(cmac_csc2cmac_wt_12_signal[34]);
    cmac_inst.cmac_csc2cmac_wt_12_35_in(cmac_csc2cmac_wt_12_signal[35]);
    cmac_inst.cmac_csc2cmac_wt_12_36_in(cmac_csc2cmac_wt_12_signal[36]);
    cmac_inst.cmac_csc2cmac_wt_12_37_in(cmac_csc2cmac_wt_12_signal[37]);
    cmac_inst.cmac_csc2cmac_wt_12_38_in(cmac_csc2cmac_wt_12_signal[38]);
    cmac_inst.cmac_csc2cmac_wt_12_39_in(cmac_csc2cmac_wt_12_signal[39]);
    cmac_inst.cmac_csc2cmac_wt_12_40_in(cmac_csc2cmac_wt_12_signal[40]);
    cmac_inst.cmac_csc2cmac_wt_12_41_in(cmac_csc2cmac_wt_12_signal[41]);
    cmac_inst.cmac_csc2cmac_wt_12_42_in(cmac_csc2cmac_wt_12_signal[42]);
    cmac_inst.cmac_csc2cmac_wt_12_43_in(cmac_csc2cmac_wt_12_signal[43]);
    cmac_inst.cmac_csc2cmac_wt_12_44_in(cmac_csc2cmac_wt_12_signal[44]);
    cmac_inst.cmac_csc2cmac_wt_12_45_in(cmac_csc2cmac_wt_12_signal[45]);
    cmac_inst.cmac_csc2cmac_wt_12_46_in(cmac_csc2cmac_wt_12_signal[46]);
    cmac_inst.cmac_csc2cmac_wt_12_47_in(cmac_csc2cmac_wt_12_signal[47]);
    cmac_inst.cmac_csc2cmac_wt_12_48_in(cmac_csc2cmac_wt_12_signal[48]);
    cmac_inst.cmac_csc2cmac_wt_12_49_in(cmac_csc2cmac_wt_12_signal[49]);
    cmac_inst.cmac_csc2cmac_wt_12_50_in(cmac_csc2cmac_wt_12_signal[50]);
    cmac_inst.cmac_csc2cmac_wt_12_51_in(cmac_csc2cmac_wt_12_signal[51]);
    cmac_inst.cmac_csc2cmac_wt_12_52_in(cmac_csc2cmac_wt_12_signal[52]);
    cmac_inst.cmac_csc2cmac_wt_12_53_in(cmac_csc2cmac_wt_12_signal[53]);
    cmac_inst.cmac_csc2cmac_wt_12_54_in(cmac_csc2cmac_wt_12_signal[54]);
    cmac_inst.cmac_csc2cmac_wt_12_55_in(cmac_csc2cmac_wt_12_signal[55]);
    cmac_inst.cmac_csc2cmac_wt_12_56_in(cmac_csc2cmac_wt_12_signal[56]);
    cmac_inst.cmac_csc2cmac_wt_12_57_in(cmac_csc2cmac_wt_12_signal[57]);
    cmac_inst.cmac_csc2cmac_wt_12_58_in(cmac_csc2cmac_wt_12_signal[58]);
    cmac_inst.cmac_csc2cmac_wt_12_59_in(cmac_csc2cmac_wt_12_signal[59]);
    cmac_inst.cmac_csc2cmac_wt_12_60_in(cmac_csc2cmac_wt_12_signal[60]);
    cmac_inst.cmac_csc2cmac_wt_12_61_in(cmac_csc2cmac_wt_12_signal[61]);
    cmac_inst.cmac_csc2cmac_wt_12_62_in(cmac_csc2cmac_wt_12_signal[62]);
    cmac_inst.cmac_csc2cmac_wt_12_63_in(cmac_csc2cmac_wt_12_signal[63]);

    cmac_inst.cmac_csc2cmac_wt_13_0_in(cmac_csc2cmac_wt_13_signal[0]);
    cmac_inst.cmac_csc2cmac_wt_13_1_in(cmac_csc2cmac_wt_13_signal[1]);
    cmac_inst.cmac_csc2cmac_wt_13_2_in(cmac_csc2cmac_wt_13_signal[2]);
    cmac_inst.cmac_csc2cmac_wt_13_3_in(cmac_csc2cmac_wt_13_signal[3]);
    cmac_inst.cmac_csc2cmac_wt_13_4_in(cmac_csc2cmac_wt_13_signal[4]);
    cmac_inst.cmac_csc2cmac_wt_13_5_in(cmac_csc2cmac_wt_13_signal[5]);
    cmac_inst.cmac_csc2cmac_wt_13_6_in(cmac_csc2cmac_wt_13_signal[6]);
    cmac_inst.cmac_csc2cmac_wt_13_7_in(cmac_csc2cmac_wt_13_signal[7]);
    cmac_inst.cmac_csc2cmac_wt_13_8_in(cmac_csc2cmac_wt_13_signal[8]);
    cmac_inst.cmac_csc2cmac_wt_13_9_in(cmac_csc2cmac_wt_13_signal[9]);
    cmac_inst.cmac_csc2cmac_wt_13_10_in(cmac_csc2cmac_wt_13_signal[10]);
    cmac_inst.cmac_csc2cmac_wt_13_11_in(cmac_csc2cmac_wt_13_signal[11]);
    cmac_inst.cmac_csc2cmac_wt_13_12_in(cmac_csc2cmac_wt_13_signal[12]);
    cmac_inst.cmac_csc2cmac_wt_13_13_in(cmac_csc2cmac_wt_13_signal[13]);
    cmac_inst.cmac_csc2cmac_wt_13_14_in(cmac_csc2cmac_wt_13_signal[14]);
    cmac_inst.cmac_csc2cmac_wt_13_15_in(cmac_csc2cmac_wt_13_signal[15]);
    cmac_inst.cmac_csc2cmac_wt_13_16_in(cmac_csc2cmac_wt_13_signal[16]);
    cmac_inst.cmac_csc2cmac_wt_13_17_in(cmac_csc2cmac_wt_13_signal[17]);
    cmac_inst.cmac_csc2cmac_wt_13_18_in(cmac_csc2cmac_wt_13_signal[18]);
    cmac_inst.cmac_csc2cmac_wt_13_19_in(cmac_csc2cmac_wt_13_signal[19]);
    cmac_inst.cmac_csc2cmac_wt_13_20_in(cmac_csc2cmac_wt_13_signal[20]);
    cmac_inst.cmac_csc2cmac_wt_13_21_in(cmac_csc2cmac_wt_13_signal[21]);
    cmac_inst.cmac_csc2cmac_wt_13_22_in(cmac_csc2cmac_wt_13_signal[22]);
    cmac_inst.cmac_csc2cmac_wt_13_23_in(cmac_csc2cmac_wt_13_signal[23]);
    cmac_inst.cmac_csc2cmac_wt_13_24_in(cmac_csc2cmac_wt_13_signal[24]);
    cmac_inst.cmac_csc2cmac_wt_13_25_in(cmac_csc2cmac_wt_13_signal[25]);
    cmac_inst.cmac_csc2cmac_wt_13_26_in(cmac_csc2cmac_wt_13_signal[26]);
    cmac_inst.cmac_csc2cmac_wt_13_27_in(cmac_csc2cmac_wt_13_signal[27]);
    cmac_inst.cmac_csc2cmac_wt_13_28_in(cmac_csc2cmac_wt_13_signal[28]);
    cmac_inst.cmac_csc2cmac_wt_13_29_in(cmac_csc2cmac_wt_13_signal[29]);
    cmac_inst.cmac_csc2cmac_wt_13_30_in(cmac_csc2cmac_wt_13_signal[30]);
    cmac_inst.cmac_csc2cmac_wt_13_31_in(cmac_csc2cmac_wt_13_signal[31]);
    cmac_inst.cmac_csc2cmac_wt_13_32_in(cmac_csc2cmac_wt_13_signal[32]);
    cmac_inst.cmac_csc2cmac_wt_13_33_in(cmac_csc2cmac_wt_13_signal[33]);
    cmac_inst.cmac_csc2cmac_wt_13_34_in(cmac_csc2cmac_wt_13_signal[34]);
    cmac_inst.cmac_csc2cmac_wt_13_35_in(cmac_csc2cmac_wt_13_signal[35]);
    cmac_inst.cmac_csc2cmac_wt_13_36_in(cmac_csc2cmac_wt_13_signal[36]);
    cmac_inst.cmac_csc2cmac_wt_13_37_in(cmac_csc2cmac_wt_13_signal[37]);
    cmac_inst.cmac_csc2cmac_wt_13_38_in(cmac_csc2cmac_wt_13_signal[38]);
    cmac_inst.cmac_csc2cmac_wt_13_39_in(cmac_csc2cmac_wt_13_signal[39]);
    cmac_inst.cmac_csc2cmac_wt_13_40_in(cmac_csc2cmac_wt_13_signal[40]);
    cmac_inst.cmac_csc2cmac_wt_13_41_in(cmac_csc2cmac_wt_13_signal[41]);
    cmac_inst.cmac_csc2cmac_wt_13_42_in(cmac_csc2cmac_wt_13_signal[42]);
    cmac_inst.cmac_csc2cmac_wt_13_43_in(cmac_csc2cmac_wt_13_signal[43]);
    cmac_inst.cmac_csc2cmac_wt_13_44_in(cmac_csc2cmac_wt_13_signal[44]);
    cmac_inst.cmac_csc2cmac_wt_13_45_in(cmac_csc2cmac_wt_13_signal[45]);
    cmac_inst.cmac_csc2cmac_wt_13_46_in(cmac_csc2cmac_wt_13_signal[46]);
    cmac_inst.cmac_csc2cmac_wt_13_47_in(cmac_csc2cmac_wt_13_signal[47]);
    cmac_inst.cmac_csc2cmac_wt_13_48_in(cmac_csc2cmac_wt_13_signal[48]);
    cmac_inst.cmac_csc2cmac_wt_13_49_in(cmac_csc2cmac_wt_13_signal[49]);
    cmac_inst.cmac_csc2cmac_wt_13_50_in(cmac_csc2cmac_wt_13_signal[50]);
    cmac_inst.cmac_csc2cmac_wt_13_51_in(cmac_csc2cmac_wt_13_signal[51]);
    cmac_inst.cmac_csc2cmac_wt_13_52_in(cmac_csc2cmac_wt_13_signal[52]);
    cmac_inst.cmac_csc2cmac_wt_13_53_in(cmac_csc2cmac_wt_13_signal[53]);
    cmac_inst.cmac_csc2cmac_wt_13_54_in(cmac_csc2cmac_wt_13_signal[54]);
    cmac_inst.cmac_csc2cmac_wt_13_55_in(cmac_csc2cmac_wt_13_signal[55]);
    cmac_inst.cmac_csc2cmac_wt_13_56_in(cmac_csc2cmac_wt_13_signal[56]);
    cmac_inst.cmac_csc2cmac_wt_13_57_in(cmac_csc2cmac_wt_13_signal[57]);
    cmac_inst.cmac_csc2cmac_wt_13_58_in(cmac_csc2cmac_wt_13_signal[58]);
    cmac_inst.cmac_csc2cmac_wt_13_59_in(cmac_csc2cmac_wt_13_signal[59]);
    cmac_inst.cmac_csc2cmac_wt_13_60_in(cmac_csc2cmac_wt_13_signal[60]);
    cmac_inst.cmac_csc2cmac_wt_13_61_in(cmac_csc2cmac_wt_13_signal[61]);
    cmac_inst.cmac_csc2cmac_wt_13_62_in(cmac_csc2cmac_wt_13_signal[62]);
    cmac_inst.cmac_csc2cmac_wt_13_63_in(cmac_csc2cmac_wt_13_signal[63]);

    cmac_inst.cmac_csc2cmac_wt_14_0_in(cmac_csc2cmac_wt_14_signal[0]);
    cmac_inst.cmac_csc2cmac_wt_14_1_in(cmac_csc2cmac_wt_14_signal[1]);
    cmac_inst.cmac_csc2cmac_wt_14_2_in(cmac_csc2cmac_wt_14_signal[2]);
    cmac_inst.cmac_csc2cmac_wt_14_3_in(cmac_csc2cmac_wt_14_signal[3]);
    cmac_inst.cmac_csc2cmac_wt_14_4_in(cmac_csc2cmac_wt_14_signal[4]);
    cmac_inst.cmac_csc2cmac_wt_14_5_in(cmac_csc2cmac_wt_14_signal[5]);
    cmac_inst.cmac_csc2cmac_wt_14_6_in(cmac_csc2cmac_wt_14_signal[6]);
    cmac_inst.cmac_csc2cmac_wt_14_7_in(cmac_csc2cmac_wt_14_signal[7]);
    cmac_inst.cmac_csc2cmac_wt_14_8_in(cmac_csc2cmac_wt_14_signal[8]);
    cmac_inst.cmac_csc2cmac_wt_14_9_in(cmac_csc2cmac_wt_14_signal[9]);
    cmac_inst.cmac_csc2cmac_wt_14_10_in(cmac_csc2cmac_wt_14_signal[10]);
    cmac_inst.cmac_csc2cmac_wt_14_11_in(cmac_csc2cmac_wt_14_signal[11]);
    cmac_inst.cmac_csc2cmac_wt_14_12_in(cmac_csc2cmac_wt_14_signal[12]);
    cmac_inst.cmac_csc2cmac_wt_14_13_in(cmac_csc2cmac_wt_14_signal[13]);
    cmac_inst.cmac_csc2cmac_wt_14_14_in(cmac_csc2cmac_wt_14_signal[14]);
    cmac_inst.cmac_csc2cmac_wt_14_15_in(cmac_csc2cmac_wt_14_signal[15]);
    cmac_inst.cmac_csc2cmac_wt_14_16_in(cmac_csc2cmac_wt_14_signal[16]);
    cmac_inst.cmac_csc2cmac_wt_14_17_in(cmac_csc2cmac_wt_14_signal[17]);
    cmac_inst.cmac_csc2cmac_wt_14_18_in(cmac_csc2cmac_wt_14_signal[18]);
    cmac_inst.cmac_csc2cmac_wt_14_19_in(cmac_csc2cmac_wt_14_signal[19]);
    cmac_inst.cmac_csc2cmac_wt_14_20_in(cmac_csc2cmac_wt_14_signal[20]);
    cmac_inst.cmac_csc2cmac_wt_14_21_in(cmac_csc2cmac_wt_14_signal[21]);
    cmac_inst.cmac_csc2cmac_wt_14_22_in(cmac_csc2cmac_wt_14_signal[22]);
    cmac_inst.cmac_csc2cmac_wt_14_23_in(cmac_csc2cmac_wt_14_signal[23]);
    cmac_inst.cmac_csc2cmac_wt_14_24_in(cmac_csc2cmac_wt_14_signal[24]);
    cmac_inst.cmac_csc2cmac_wt_14_25_in(cmac_csc2cmac_wt_14_signal[25]);
    cmac_inst.cmac_csc2cmac_wt_14_26_in(cmac_csc2cmac_wt_14_signal[26]);
    cmac_inst.cmac_csc2cmac_wt_14_27_in(cmac_csc2cmac_wt_14_signal[27]);
    cmac_inst.cmac_csc2cmac_wt_14_28_in(cmac_csc2cmac_wt_14_signal[28]);
    cmac_inst.cmac_csc2cmac_wt_14_29_in(cmac_csc2cmac_wt_14_signal[29]);
    cmac_inst.cmac_csc2cmac_wt_14_30_in(cmac_csc2cmac_wt_14_signal[30]);
    cmac_inst.cmac_csc2cmac_wt_14_31_in(cmac_csc2cmac_wt_14_signal[31]);
    cmac_inst.cmac_csc2cmac_wt_14_32_in(cmac_csc2cmac_wt_14_signal[32]);
    cmac_inst.cmac_csc2cmac_wt_14_33_in(cmac_csc2cmac_wt_14_signal[33]);
    cmac_inst.cmac_csc2cmac_wt_14_34_in(cmac_csc2cmac_wt_14_signal[34]);
    cmac_inst.cmac_csc2cmac_wt_14_35_in(cmac_csc2cmac_wt_14_signal[35]);
    cmac_inst.cmac_csc2cmac_wt_14_36_in(cmac_csc2cmac_wt_14_signal[36]);
    cmac_inst.cmac_csc2cmac_wt_14_37_in(cmac_csc2cmac_wt_14_signal[37]);
    cmac_inst.cmac_csc2cmac_wt_14_38_in(cmac_csc2cmac_wt_14_signal[38]);
    cmac_inst.cmac_csc2cmac_wt_14_39_in(cmac_csc2cmac_wt_14_signal[39]);
    cmac_inst.cmac_csc2cmac_wt_14_40_in(cmac_csc2cmac_wt_14_signal[40]);
    cmac_inst.cmac_csc2cmac_wt_14_41_in(cmac_csc2cmac_wt_14_signal[41]);
    cmac_inst.cmac_csc2cmac_wt_14_42_in(cmac_csc2cmac_wt_14_signal[42]);
    cmac_inst.cmac_csc2cmac_wt_14_43_in(cmac_csc2cmac_wt_14_signal[43]);
    cmac_inst.cmac_csc2cmac_wt_14_44_in(cmac_csc2cmac_wt_14_signal[44]);
    cmac_inst.cmac_csc2cmac_wt_14_45_in(cmac_csc2cmac_wt_14_signal[45]);
    cmac_inst.cmac_csc2cmac_wt_14_46_in(cmac_csc2cmac_wt_14_signal[46]);
    cmac_inst.cmac_csc2cmac_wt_14_47_in(cmac_csc2cmac_wt_14_signal[47]);
    cmac_inst.cmac_csc2cmac_wt_14_48_in(cmac_csc2cmac_wt_14_signal[48]);
    cmac_inst.cmac_csc2cmac_wt_14_49_in(cmac_csc2cmac_wt_14_signal[49]);
    cmac_inst.cmac_csc2cmac_wt_14_50_in(cmac_csc2cmac_wt_14_signal[50]);
    cmac_inst.cmac_csc2cmac_wt_14_51_in(cmac_csc2cmac_wt_14_signal[51]);
    cmac_inst.cmac_csc2cmac_wt_14_52_in(cmac_csc2cmac_wt_14_signal[52]);
    cmac_inst.cmac_csc2cmac_wt_14_53_in(cmac_csc2cmac_wt_14_signal[53]);
    cmac_inst.cmac_csc2cmac_wt_14_54_in(cmac_csc2cmac_wt_14_signal[54]);
    cmac_inst.cmac_csc2cmac_wt_14_55_in(cmac_csc2cmac_wt_14_signal[55]);
    cmac_inst.cmac_csc2cmac_wt_14_56_in(cmac_csc2cmac_wt_14_signal[56]);
    cmac_inst.cmac_csc2cmac_wt_14_57_in(cmac_csc2cmac_wt_14_signal[57]);
    cmac_inst.cmac_csc2cmac_wt_14_58_in(cmac_csc2cmac_wt_14_signal[58]);
    cmac_inst.cmac_csc2cmac_wt_14_59_in(cmac_csc2cmac_wt_14_signal[59]);
    cmac_inst.cmac_csc2cmac_wt_14_60_in(cmac_csc2cmac_wt_14_signal[60]);
    cmac_inst.cmac_csc2cmac_wt_14_61_in(cmac_csc2cmac_wt_14_signal[61]);
    cmac_inst.cmac_csc2cmac_wt_14_62_in(cmac_csc2cmac_wt_14_signal[62]);
    cmac_inst.cmac_csc2cmac_wt_14_63_in(cmac_csc2cmac_wt_14_signal[63]);

    cmac_inst.cmac_csc2cmac_wt_15_0_in(cmac_csc2cmac_wt_15_signal[0]);
    cmac_inst.cmac_csc2cmac_wt_15_1_in(cmac_csc2cmac_wt_15_signal[1]);
    cmac_inst.cmac_csc2cmac_wt_15_2_in(cmac_csc2cmac_wt_15_signal[2]);
    cmac_inst.cmac_csc2cmac_wt_15_3_in(cmac_csc2cmac_wt_15_signal[3]);
    cmac_inst.cmac_csc2cmac_wt_15_4_in(cmac_csc2cmac_wt_15_signal[4]);
    cmac_inst.cmac_csc2cmac_wt_15_5_in(cmac_csc2cmac_wt_15_signal[5]);
    cmac_inst.cmac_csc2cmac_wt_15_6_in(cmac_csc2cmac_wt_15_signal[6]);
    cmac_inst.cmac_csc2cmac_wt_15_7_in(cmac_csc2cmac_wt_15_signal[7]);
    cmac_inst.cmac_csc2cmac_wt_15_8_in(cmac_csc2cmac_wt_15_signal[8]);
    cmac_inst.cmac_csc2cmac_wt_15_9_in(cmac_csc2cmac_wt_15_signal[9]);
    cmac_inst.cmac_csc2cmac_wt_15_10_in(cmac_csc2cmac_wt_15_signal[10]);
    cmac_inst.cmac_csc2cmac_wt_15_11_in(cmac_csc2cmac_wt_15_signal[11]);
    cmac_inst.cmac_csc2cmac_wt_15_12_in(cmac_csc2cmac_wt_15_signal[12]);
    cmac_inst.cmac_csc2cmac_wt_15_13_in(cmac_csc2cmac_wt_15_signal[13]);
    cmac_inst.cmac_csc2cmac_wt_15_14_in(cmac_csc2cmac_wt_15_signal[14]);
    cmac_inst.cmac_csc2cmac_wt_15_15_in(cmac_csc2cmac_wt_15_signal[15]);
    cmac_inst.cmac_csc2cmac_wt_15_16_in(cmac_csc2cmac_wt_15_signal[16]);
    cmac_inst.cmac_csc2cmac_wt_15_17_in(cmac_csc2cmac_wt_15_signal[17]);
    cmac_inst.cmac_csc2cmac_wt_15_18_in(cmac_csc2cmac_wt_15_signal[18]);
    cmac_inst.cmac_csc2cmac_wt_15_19_in(cmac_csc2cmac_wt_15_signal[19]);
    cmac_inst.cmac_csc2cmac_wt_15_20_in(cmac_csc2cmac_wt_15_signal[20]);
    cmac_inst.cmac_csc2cmac_wt_15_21_in(cmac_csc2cmac_wt_15_signal[21]);
    cmac_inst.cmac_csc2cmac_wt_15_22_in(cmac_csc2cmac_wt_15_signal[22]);
    cmac_inst.cmac_csc2cmac_wt_15_23_in(cmac_csc2cmac_wt_15_signal[23]);
    cmac_inst.cmac_csc2cmac_wt_15_24_in(cmac_csc2cmac_wt_15_signal[24]);
    cmac_inst.cmac_csc2cmac_wt_15_25_in(cmac_csc2cmac_wt_15_signal[25]);
    cmac_inst.cmac_csc2cmac_wt_15_26_in(cmac_csc2cmac_wt_15_signal[26]);
    cmac_inst.cmac_csc2cmac_wt_15_27_in(cmac_csc2cmac_wt_15_signal[27]);
    cmac_inst.cmac_csc2cmac_wt_15_28_in(cmac_csc2cmac_wt_15_signal[28]);
    cmac_inst.cmac_csc2cmac_wt_15_29_in(cmac_csc2cmac_wt_15_signal[29]);
    cmac_inst.cmac_csc2cmac_wt_15_30_in(cmac_csc2cmac_wt_15_signal[30]);
    cmac_inst.cmac_csc2cmac_wt_15_31_in(cmac_csc2cmac_wt_15_signal[31]);
    cmac_inst.cmac_csc2cmac_wt_15_32_in(cmac_csc2cmac_wt_15_signal[32]);
    cmac_inst.cmac_csc2cmac_wt_15_33_in(cmac_csc2cmac_wt_15_signal[33]);
    cmac_inst.cmac_csc2cmac_wt_15_34_in(cmac_csc2cmac_wt_15_signal[34]);
    cmac_inst.cmac_csc2cmac_wt_15_35_in(cmac_csc2cmac_wt_15_signal[35]);
    cmac_inst.cmac_csc2cmac_wt_15_36_in(cmac_csc2cmac_wt_15_signal[36]);
    cmac_inst.cmac_csc2cmac_wt_15_37_in(cmac_csc2cmac_wt_15_signal[37]);
    cmac_inst.cmac_csc2cmac_wt_15_38_in(cmac_csc2cmac_wt_15_signal[38]);
    cmac_inst.cmac_csc2cmac_wt_15_39_in(cmac_csc2cmac_wt_15_signal[39]);
    cmac_inst.cmac_csc2cmac_wt_15_40_in(cmac_csc2cmac_wt_15_signal[40]);
    cmac_inst.cmac_csc2cmac_wt_15_41_in(cmac_csc2cmac_wt_15_signal[41]);
    cmac_inst.cmac_csc2cmac_wt_15_42_in(cmac_csc2cmac_wt_15_signal[42]);
    cmac_inst.cmac_csc2cmac_wt_15_43_in(cmac_csc2cmac_wt_15_signal[43]);
    cmac_inst.cmac_csc2cmac_wt_15_44_in(cmac_csc2cmac_wt_15_signal[44]);
    cmac_inst.cmac_csc2cmac_wt_15_45_in(cmac_csc2cmac_wt_15_signal[45]);
    cmac_inst.cmac_csc2cmac_wt_15_46_in(cmac_csc2cmac_wt_15_signal[46]);
    cmac_inst.cmac_csc2cmac_wt_15_47_in(cmac_csc2cmac_wt_15_signal[47]);
    cmac_inst.cmac_csc2cmac_wt_15_48_in(cmac_csc2cmac_wt_15_signal[48]);
    cmac_inst.cmac_csc2cmac_wt_15_49_in(cmac_csc2cmac_wt_15_signal[49]);
    cmac_inst.cmac_csc2cmac_wt_15_50_in(cmac_csc2cmac_wt_15_signal[50]);
    cmac_inst.cmac_csc2cmac_wt_15_51_in(cmac_csc2cmac_wt_15_signal[51]);
    cmac_inst.cmac_csc2cmac_wt_15_52_in(cmac_csc2cmac_wt_15_signal[52]);
    cmac_inst.cmac_csc2cmac_wt_15_53_in(cmac_csc2cmac_wt_15_signal[53]);
    cmac_inst.cmac_csc2cmac_wt_15_54_in(cmac_csc2cmac_wt_15_signal[54]);
    cmac_inst.cmac_csc2cmac_wt_15_55_in(cmac_csc2cmac_wt_15_signal[55]);
    cmac_inst.cmac_csc2cmac_wt_15_56_in(cmac_csc2cmac_wt_15_signal[56]);
    cmac_inst.cmac_csc2cmac_wt_15_57_in(cmac_csc2cmac_wt_15_signal[57]);
    cmac_inst.cmac_csc2cmac_wt_15_58_in(cmac_csc2cmac_wt_15_signal[58]);
    cmac_inst.cmac_csc2cmac_wt_15_59_in(cmac_csc2cmac_wt_15_signal[59]);
    cmac_inst.cmac_csc2cmac_wt_15_60_in(cmac_csc2cmac_wt_15_signal[60]);
    cmac_inst.cmac_csc2cmac_wt_15_61_in(cmac_csc2cmac_wt_15_signal[61]);
    cmac_inst.cmac_csc2cmac_wt_15_62_in(cmac_csc2cmac_wt_15_signal[62]);
    cmac_inst.cmac_csc2cmac_wt_15_63_in(cmac_csc2cmac_wt_15_signal[63]);

    SC_THREAD(run);
  }

  // Run the SystemC simuation and log outputs
  void run() {
    cmac_inst.instr_log.open("instr_log_conv.txt", ofstream::out | ofstream::trunc);
    cmac_inst.instr_update_log.open("instr_update_log_conv.txt", ios::out | ios::trunc);

    std::cout << "start running" << std::endl;
    std::cout << "*********** simulation start ***********" << std::endl;
    wait(10, SC_NS);

    // Log final outputs
    fout.open(file_out, ios::out | ios::trunc);

    int index = 0;

    while (input_done == 0) {
      if (DISABLE_TESTING || (!DISABLE_TESTING && cmac_inst.cmac_csc2cmac_vld)){
        // std::cout << "current simulation time: " << '\t' << sc_time_stamp() << "\r" << std::flush;
        // fout << "datatype => " << std::hex << cmac_inst.cmac_group0_cmac_d_misc_cfg << std::endl;

        /* Output format:
          instr No. [index]
          mac_0 [out1] [out2] [out3] [out4]
          mac_1 [out1] [out2] [out3] [out4]
          ...
          mac_15 [out1] [out2] [out3] [out4]
        */

        fout << "instr No. " << std::dec << index++ << std::endl;
        fout << "consumer = " << std::dec << cmac_inst.cmac_cmac_s_consumer << std::endl;

        // fout << "group0_cfg = " << std::hex << cmac_inst.cmac_group0_cmac_d_misc_cfg << std::endl;
        // fout << "group1_cfg = " << std::hex << cmac_inst.cmac_group1_cmac_d_misc_cfg << std::endl;

        print_cell_output(0, cmac_inst.cmac_cmac2cacc_partial_sum_mac_0);
        print_cell_output(1, cmac_inst.cmac_cmac2cacc_partial_sum_mac_1);
        print_cell_output(2, cmac_inst.cmac_cmac2cacc_partial_sum_mac_2);
        print_cell_output(3, cmac_inst.cmac_cmac2cacc_partial_sum_mac_3);

        print_cell_output(4, cmac_inst.cmac_cmac2cacc_partial_sum_mac_4);
        print_cell_output(5, cmac_inst.cmac_cmac2cacc_partial_sum_mac_5);
        print_cell_output(6, cmac_inst.cmac_cmac2cacc_partial_sum_mac_6);
        print_cell_output(7, cmac_inst.cmac_cmac2cacc_partial_sum_mac_7);

        print_cell_output(8, cmac_inst.cmac_cmac2cacc_partial_sum_mac_8);
        print_cell_output(9, cmac_inst.cmac_cmac2cacc_partial_sum_mac_9);
        print_cell_output(10, cmac_inst.cmac_cmac2cacc_partial_sum_mac_10);
        print_cell_output(11, cmac_inst.cmac_cmac2cacc_partial_sum_mac_11);

        print_cell_output(12, cmac_inst.cmac_cmac2cacc_partial_sum_mac_12);
        print_cell_output(13, cmac_inst.cmac_cmac2cacc_partial_sum_mac_13);
        print_cell_output(14, cmac_inst.cmac_cmac2cacc_partial_sum_mac_14);
        print_cell_output(15, cmac_inst.cmac_cmac2cacc_partial_sum_mac_15);

        fout << std::endl;
      } else{
        index++;
      }
      
      wait(10, SC_NS);
    }
    wait(1000, SC_NS);

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
      std::cout << "Usage: ./cmac [prog_frag_in_path] [result_out_dump_path]" << std::endl;
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

