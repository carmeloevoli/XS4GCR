#include "d2xsec.h"

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

/**
 * @brief Main function for example1
 */
int main() {
	DRAGON2::D2XSEC xsec;
	xsec.set_total_inelastic("Tripathi99");
	auto x_in = xsec.create_total_inelastic();

	DRAGON2::PID C(6, 12);
	DRAGON2::TARGET H_ISM(1), He_ISM(2);

	double f_He = 0.11;
	double n_gas = 1.0 / pow3(MKS::cm);

	for (double T_n = 0.1 * MKS::GeV; T_n < MKS::TeV; T_n *= 1.1) {
		double v = MKS::c_light * sqrt(1 - pow2(MKS::proton_mass_c2) / pow2(T_n + MKS::proton_mass_c2));
		double t_f = 1. / v / n_gas / (x_in->get(C, H_ISM, T_n) + f_He * x_in->get(C, He_ISM, T_n));
		std::cout << T_n / MKS::GeV << "   " << t_f / MKS::Myr << "\n";
	}
}
