#include "d2xsec.h"

/**
 * @example example_1.cpp
 * In this example the Carbon fragmentation timescale
 * is computed as a function of kinetic energy per nucleon
 *
 * @remark Options available for inelastic xsec : Tripathi99, CROSEC
 * @remark Local ISM number density : 1 cm$^{-3}$
 * @remark Helium fraction in number : 0.11
 *
 * @see https://arxiv.org/abs/1711.09616
 */
int main() {
	D2XSEC xsec;
	xsec.set_total_inelastic("Tripathi99");
	auto x_in = xsec.create_total_inelastic();

	PID C(6, 12);
	TARGET H_ISM(1), He_ISM(2);

	double f_He = 0.11;
	double n_gas = 1.0 / pow3(cm);

	for (double T_n = 0.1 * GeV; T_n < TeV; T_n *= 1.1) {
		double v = c_light * sqrt(1 - pow2(proton_mass_c2) / pow2(T_n + proton_mass_c2));
		double t_f = 1. / v / n_gas / (x_in->get(C, H_ISM, T_n) + f_He * x_in->get(C, He_ISM, T_n));
		std::cout << T_n / GeV << "   " << t_f / Myr << "\n";
	}
}
