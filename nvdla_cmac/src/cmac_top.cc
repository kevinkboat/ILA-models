// File: cmac_top.cc

#include <cmac.h>

namespace ilang {

    Ila GetCMACIla(const std::string& model_name){
        auto m = Ila(model_name);
        SetUnsignedComparison(true);
        DefineCMACInput(m);
        DefineCMACOutput(m);
        DefineCMACState(m);
        DefineCMACInit(m);
        DefineCMACInstrs(m);
        return m;
    }

} // namespace ilang