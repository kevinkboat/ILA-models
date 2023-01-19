// File: cmac.h

#ifndef NVDLA_CMAC_H
#define NVDLA_CMAC_H

#include <string>
#include <ilang/ilang++.h>
#include <cmac_config.h>

namespace ilang {

// CMAC
Ila GetCMACIla(const std::string& model_name = "cmac");
void DefineCMACInput(Ila& m);
void DefineCMACOutput(Ila& m);
void DefineCMACState(Ila& m);
void DefineCMACInit(Ila& m);
void DefineCMACInstrs(Ila& m);

} // namespace ilang

#endif // NVDLA_CMAC_H