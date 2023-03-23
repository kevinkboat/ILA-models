// File: main.cc

#include <cacc.h>

#include <ilang/ilang++.h>
#include <ilang/util/log.h>
#include <iostream>

using namespace std;
using namespace ilang;

int main(int argc, char* argv[]) {
  SetToStdErr(1);

  cout << "start";
  
  // get the ILA model
  auto cacc = GetCACCIla("cacc");

  cout << "p9";
  ILA_INFO << "#instr: " << cacc.instr_num();
  for (auto i = 0; i < cacc.instr_num(); i++) {
    ILA_INFO << cacc.instr(i);
  }

  cout << "p8";
  ILA_INFO << "#state: " << cacc.state_num();
  for (auto i = 0; i < cacc.state_num(); i++) {
    ILA_INFO << cacc.state(i);
  }

  cout << "p7";
  ILA_INFO << "#input: " << cacc.input_num();
  for (auto i = 0; i < cacc.input_num(); i++) {
    ILA_INFO << cacc.input(i);
  }

  std::vector<std::string> cacc_design_files = {
    "NV_NVDLA_cacc_top.v"
  };

  ExportSysCSim(cacc, "./sim_model", false);

  return 0;
}



