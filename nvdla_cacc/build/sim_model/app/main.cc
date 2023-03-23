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

#define GET_JSON_INT(json_val, default_val) (!(json_val.is_null()) ? json_val.get<int>() : default_val)
#define GET_JSON_INT_FROM_HEX_STR(json_val, default_val) (!(json_val.is_null()) ? (std::stoi(json_val.get<std::string>().c_str(), nullptr, 16)) : default_val)
#define GET_JSON_BOOL(json_val, default_val) (!(json_val.is_null()) ? json_val.get<bool>() : default_val)

std::string file_in;
std::string file_out;
std::ofstream fout;

// Module for reading inputs into ILA model
SC_MODULE(Source) {
  sc_in<bool> clk{"clk"};
  sc_out< sc_biguint<1> > input_done;

  // CSB inputs
  sc_out<sc_biguint<16>> cacc_csb2cacc_addr;
  sc_out<sc_biguint<32>> cacc_csb2cacc_data;
  sc_out<bool> cacc_csb2cacc_write;
  sc_out<bool> cacc_csb2cacc_vld;

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
    
      wait(10, SC_NS);
    }

    input_done = 1;
    std::cout << "read_file" << std::flush;
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

    src.input_done(input_done);

    // Link with the cacc_inst.h SystemC model
    cacc_inst.cacc_csb2cacc_addr_in(cacc_csb2cacc_addr_signal);
    cacc_inst.cacc_csb2cacc_data_in(cacc_csb2cacc_data_signal);
    cacc_inst.cacc_csb2cacc_write_in(cacc_csb2cacc_write_signal);
    cacc_inst.cacc_csb2cacc_vld_in(cacc_csb2cacc_vld_signal);

    SC_THREAD(run);
  }

  // Run the SystemC simuation and log outputs
  void run() {
    cacc_inst.instr_log.open("instr_log_conv.txt", ofstream::out | ofstream::trunc);
    cacc_inst.instr_update_log.open("instr_update_log_conv.txt", ios::out | ios::trunc);

    std::cout << "start running" << std::endl;
    std::cout << "*********** simulation start ***********" << std::endl;
    wait(10, SC_NS);

    // Log final outputs
    fout.open(file_out, ios::out | ios::trunc);

    int index = 0;

    while (input_done == 0) {
      // std::cout << "current simulation time: " << '\t' << sc_time_stamp() << "\r" << std::flush;

      fout << "current simulation time: " << '\t' << sc_time_stamp() << std::endl;
      fout << "instr No. " << std::dec << index++ << std::endl;
      
      fout << "(Output) cacc_cacc2csb_rdy = " << cacc_inst.cacc_cacc2csb_rdy << std::endl;
      fout << "(Output) cacc_cacc2csb_data_vld = " << cacc_inst.cacc_cacc2csb_data_vld << std::endl;

      fout << "(State) cacc_cacc_s_status = " << (sc_dt::sc_bigint<32>) cacc_inst.cacc_cacc_s_status << std::endl;
      fout << "(State) cacc_cacc_s_pointer = " << (sc_dt::sc_bigint<32>) cacc_inst.cacc_cacc_s_pointer << std::endl;
      
      fout << "(State) cacc_group0_cacc_d_out_saturation = " << (sc_dt::sc_bigint<32>) cacc_inst.cacc_group0_cacc_d_out_saturation << std::endl;
      fout << "(State) cacc_group0_cacc_d_clip_cfg = " << (sc_dt::sc_bigint<32>) cacc_inst.cacc_group0_cacc_d_clip_cfg << std::endl;
      fout << "(State) cacc_group0_cacc_d_op_enable = " << (sc_dt::sc_bigint<32>) cacc_inst.cacc_group0_cacc_d_op_enable << std::endl;
      fout << "(State) cacc_group0_cacc_d_misc_cfg = " << (sc_dt::sc_bigint<32>) cacc_inst.cacc_group0_cacc_d_misc_cfg << std::endl;
      fout << "(State) cacc_group0_cacc_d_dataout_size_0 = " << (sc_dt::sc_bigint<32>) cacc_inst.cacc_group0_cacc_d_dataout_size_0 << std::endl;
      fout << "(State) cacc_group0_cacc_d_dataout_size_1 = " << (sc_dt::sc_bigint<32>) cacc_inst.cacc_group0_cacc_d_dataout_size_1 << std::endl;
      fout << "(State) cacc_group0_cacc_d_dataout_addr = " << (sc_dt::sc_bigint<32>) cacc_inst.cacc_group0_cacc_d_dataout_addr << std::endl;
      fout << "(State) cacc_group0_cacc_d_batch_number = " << (sc_dt::sc_bigint<32>) cacc_inst.cacc_group0_cacc_d_batch_number << std::endl;
      fout << "(State) cacc_group0_cacc_d_line_stride = " << (sc_dt::sc_bigint<32>) cacc_inst.cacc_group0_cacc_d_line_stride << std::endl;
      fout << "(State) cacc_group0_cacc_d_surf_stride = " << (sc_dt::sc_bigint<32>) cacc_inst.cacc_group0_cacc_d_surf_stride << std::endl;
      fout << "(State) cacc_group0_cacc_d_dataout_map = " << (sc_dt::sc_bigint<32>) cacc_inst.cacc_group0_cacc_d_dataout_map << std::endl;

      fout << "(State) cacc_group1_cacc_d_out_saturation = " << (sc_dt::sc_bigint<32>) cacc_inst.cacc_group1_cacc_d_out_saturation << std::endl;
      fout << "(State) cacc_group1_cacc_d_clip_cfg = " << (sc_dt::sc_bigint<32>) cacc_inst.cacc_group1_cacc_d_clip_cfg << std::endl;
      fout << "(State) cacc_group1_cacc_d_dataout_map = " << (sc_dt::sc_bigint<32>) cacc_inst.cacc_group1_cacc_d_dataout_map << std::endl;
      fout << "(State) cacc_group1_cacc_d_surf_stride = " << (sc_dt::sc_bigint<32>) cacc_inst.cacc_group1_cacc_d_surf_stride << std::endl;
      fout << "(State) cacc_group1_cacc_d_line_stride = " << (sc_dt::sc_bigint<32>) cacc_inst.cacc_group1_cacc_d_line_stride << std::endl;
      fout << "(State) cacc_group1_cacc_d_batch_number = " << (sc_dt::sc_bigint<32>) cacc_inst.cacc_group1_cacc_d_batch_number << std::endl;
      fout << "(State) cacc_group1_cacc_d_dataout_addr = " << (sc_dt::sc_bigint<32>) cacc_inst.cacc_group1_cacc_d_dataout_addr << std::endl;
      fout << "(State) cacc_group1_cacc_d_dataout_size_1 = " << (sc_dt::sc_bigint<32>) cacc_inst.cacc_group1_cacc_d_dataout_size_1 << std::endl;
      fout << "(State) cacc_group1_cacc_d_dataout_size_0 = " << (sc_dt::sc_bigint<32>) cacc_inst.cacc_group1_cacc_d_dataout_size_0 << std::endl;
      fout << "(State) cacc_group1_cacc_d_misc_cfg = " << (sc_dt::sc_bigint<32>) cacc_inst.cacc_group1_cacc_d_misc_cfg << std::endl;
      fout << "(State) cacc_group1_cacc_d_op_enable = " << (sc_dt::sc_bigint<32>) cacc_inst.cacc_group1_cacc_d_op_enable << std::endl;

      fout << std::endl;
            
      wait(10, SC_NS);
    }
    wait(1000, SC_NS);

    fout.close();

    std::cout << "outputs have been stored at " << file_out << std::endl;

    wait(100000, SC_NS);
    std::cout << '\n' << std::endl;
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

