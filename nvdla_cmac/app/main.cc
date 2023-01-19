// File: main.cc

#include <cmac.h>

#include <ilang/ilang++.h>
#include <ilang/util/log.h>
#include <iostream>

using namespace std;
using namespace ilang;

int main(int argc, char* argv[]) {
  SetToStdErr(1);

  cout << "start";
  
  // get the ILA model
  auto cmac = GetCMACIla("cmac");

  cout << "p9";
  ILA_INFO << "#instr: " << cmac.instr_num();
  for (auto i = 0; i < cmac.instr_num(); i++) {
    ILA_INFO << cmac.instr(i);
  }

  cout << "p8";
  ILA_INFO << "#state: " << cmac.state_num();
  for (auto i = 0; i < cmac.state_num(); i++) {
    ILA_INFO << cmac.state(i);
  }

  cout << "p7";
  ILA_INFO << "#input: " << cmac.input_num();
  for (auto i = 0; i < cmac.input_num(); i++) {
    ILA_INFO << cmac.input(i);
  }

  std::vector<std::string> cmac_design_files = {
    "NV_NVDLA_cmac_top.v"
  };

  ExportSysCSim(cmac, "./sim_model", false);

  return 0;
}



