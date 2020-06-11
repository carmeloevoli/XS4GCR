// Copyright (c) 2017 Carmelo Evoli - MIT License
#include "XS4GCR/xs4gcr.h"

/**
 * @example example2.cpp
 * In this example the positron production cross sections
 * are computed as a function of the positron kinetic energy
 *
 * @remark Options available for production xsec : Kamae2006, HuangPohl2007
 *
 * @see https://arxiv.org/abs/1711.09616
 */

/**
 * @brief Main function for example2
 *
 * Production xsecs for positrons are computed, columns represent: \n
 * 1) \f$T\f$ positron energy in GeV \n
 * 2) \f$d\sigma/dT(p + H_{ISM} \rightarrow e^+)\f$ in mbarn/GeV \n
 * 3) \f$d\sigma/dT(He + H_{ISM} \rightarrow e^+)\f$ in mbarn/GeV \n
 *
 * @remark to compute electron production xsecs one must use \c
 * xsec.create_secondary_leptons(electron)
 * @remark primary kinetic energy per nucleon \c T_n_proj is 100 GeV
 */
int main() {
    XS4GCR::XSECS xsec;
    xsec.set_secondary_leptons("Kamae2006");

    XS4GCR::PID electron(-1, 0);
    XS4GCR::PID positron(1, 0);
    XS4GCR::PID H(1, 1);
    XS4GCR::PID He(2, 4);
    XS4GCR::TARGET H_ISM(1);
    XS4GCR::TARGET He_ISM(2);

    auto x_leptons = xsec.create_secondary_leptons(positron);

    double T_n_proj = 100 * MKS::GeV;

    for (double T_lepton = 1 * MKS::GeV; T_lepton < T_n_proj; T_lepton *= 1.1) {
        std::cout << T_lepton / MKS::GeV << " ";
        std::cout << x_leptons->get(H, H_ISM, T_n_proj, T_lepton) / (MKS::mbarn / MKS::GeV) << "\t";
        std::cout << x_leptons->get(He, H_ISM, T_n_proj, T_lepton) / (MKS::mbarn / MKS::GeV)
                  << "\n";
    }
}
