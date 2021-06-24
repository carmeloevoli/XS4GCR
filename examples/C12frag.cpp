// Copyright (c) 2017 Carmelo Evoli - MIT License

#include <vector>

#include "XS4GCR/nucleinames.h"
#include "XS4GCR/pid.h"
#include "XS4GCR/xs4gcr.h"
/**
 * @brief Compute the secondary production cross-sections.
 *
 * This function computes the secondary nuclei production cross-sections
 * from the interaction of primary H and He on ISM
 *
 * @param model production model identifier, e.g. Webber1993
 * @param filename output file name
 */
int main() {
    XS4GCR::XSECS xsec;
    xsec.set_secondary_nuclei("Evoli2019");

    const auto x_in = xsec.create_secondary_nuclei();

    std::vector<XS4GCR::PID> fragments{XS4GCR::Be7, XS4GCR::Be9, XS4GCR::Be10,
                                       XS4GCR::B10, XS4GCR::B11, XS4GCR::C11};

    std::ofstream ofile("C12_fragxsecs.txt");
    if (ofile.is_open()) {
        ofile << "T [GeV/n] - Be7 [mb] - Be9 [mb] - Be10 [mb] - B10 [mb] - B11 [mb] - C11 [mb]\n";
        for (double T_n = 100. * MKS::MeV; T_n < 2e4 * MKS::GeV; T_n *= 1.1) {
            ofile << std::scientific << T_n / MKS::GeV << "\t";  // TODO passa a CGS!
            for (auto& fragment : fragments) {
                XS4GCR::channel ch(XS4GCR::C12, fragment);
                ofile << x_in->get(ch, XS4GCR::H_ISM, T_n, false) / MKS::mbarn << "\t";
            }
            ofile << "\n";
        }
        ofile.close();
    }
    return 0;
}
