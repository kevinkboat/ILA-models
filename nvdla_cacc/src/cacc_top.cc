// File: cacc_top.cc

#include <cacc.h>

namespace ilang {

    Ila GetCACCIla(const std::string& model_name){
        auto m = Ila(model_name);
        SetUnsignedComparison(true);
        DefineCACCInput(m);
        DefineCACCOutput(m);
        DefineCACCState(m);
        DefineCACCInit(m);
        DefineCACCInstrs(m);
        return m;
    }

} // namespace ilang