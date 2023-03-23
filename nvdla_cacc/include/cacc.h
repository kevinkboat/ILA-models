// File: cacc.h

#ifndef NVDLA_CACC_H
#define NVDLA_CACC_H

#include <string>
#include <ilang/ilang++.h>
#include <cacc_config.h>

namespace ilang {

// CACC
Ila GetCACCIla(const std::string& model_name = "cacc");
void DefineCACCInput(Ila& m);
void DefineCACCOutput(Ila& m);
void DefineCACCState(Ila& m);
void DefineCACCInit(Ila& m);
void DefineCACCInstrs(Ila& m);

} // namespace ilang

#endif // NVDLA_CACC_H