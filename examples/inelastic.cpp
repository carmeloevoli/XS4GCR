// Copyright (c) 2017 Carmelo Evoli - MIT License
#include "XS4GCR/xs4gcr.h"

/**
 * @example example1.cpp
 * In this example the Carbon fragmentation timescale
 * is computed as a function of kinetic energy per nucleon
 *
 * @remark Options available for inelastic xsec : Tripathi99, CROSEC
 * @remark Local ISM number density is 1 cm\f$^{-3}\f$
 * @remark Helium fraction is 0.11
 *
 * @see https://arxiv.org/abs/1711.09616
 */

double beta(double T_n) {
    return sqrt(1 - pow2(cgs::proton_mass_c2) / pow2(T_n + cgs::proton_mass_c2));
}

/**
 * @brief Main function for example1
 */
int main() {
    XS4GCR::XSECS xsec;
    xsec.set_total_inelastic("Tripathi99");
    const auto x_in = xsec.create_total_inelastic();

    XS4GCR::PID C(6, 12);

    const double f_He = 0.11;
    const double n_gas = 1.0 / pow3(cgs::cm);

    for (double T_n = 0.1 * cgs::GeV; T_n < cgs::TeV; T_n *= 1.1) {
        auto v = cgs::c_light * beta(T_n);
        auto sigma = x_in->get(C, XS4GCR::H_ISM, T_n) + f_He * x_in->get(C, XS4GCR::He_ISM, T_n);
        auto t_f = 1. / v / n_gas / sigma;
        std::cout << T_n / cgs::GeV << "   " << t_f / cgs::Myr << "\n";
    }
}
