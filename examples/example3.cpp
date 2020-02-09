#include "d2xsec.h"
#include "lis.h"

/**
 * @example example3.cpp
 *
 * In this example some quantities relevant for protons
 * are computed on text files
 *
 * @remark Options available for xsec model : DRAGON2
 *
 * @see https://arxiv.org/abs/1711.09616
 */

/**
 * @brief Compute the proton timescale for inelastic fragmentation.
 *
 * This function computes proton timescale for inelastic fragmentation
 * from the interaction of primary H on ISM and write them in a text file,
 * where columns represent: \n
 * 1) the proton kinetic energy in GeV/n \n
 * 2) \f$\tau_{H}\f$ for interaction with H + He in Myr \n
 * 3) \f$\tau_{H}\f$ for interaction with H in Myr
 *
 * @remark Local ISM gas density is 1 cm\f$^{-3}\f$
 * @param filename output file name
 */
void get_fragmentation_timescale(std::string filename) {
	DRAGON2::D2XSEC xsec;
	xsec.set_proton_xsecs("DRAGON2");
	auto x_pr = xsec.create_proton_xsecs();
	DRAGON2::TARGET H_ISM(1), He_ISM(2);
	double n_gas = 1. / MKS::cm3;
	std::ofstream outfile(filename);
	outfile << std::scientific;
	for (double T = 0.1 * MKS::GeV; T < 1e4 * MKS::GeV; T *= 1.1) {
		double v = MKS::c_light * sqrt(1 - pow2(MKS::proton_mass_c2) / pow2(T + MKS::proton_mass_c2));
		double sigma_total = x_pr->get_inelastic(H_ISM, T) + MKS::f_He * x_pr->get_inelastic(He_ISM, T);
		double t_f = 1. / (v * n_gas * sigma_total);
		double t_f_H = 1. / (v * n_gas * x_pr->get_inelastic(H_ISM, T));
		outfile << T / MKS::GeV << " " << t_f / MKS::Myr << " " << t_f_H / MKS::Myr << "\n";
	}
	outfile.close();
}

/**
 * @brief Compute the secondary proton production cross-sections.
 *
 * This function computes the secondary proton production cross-sections
 * from the interaction of primary H on ISM and write them in a text file,
 * where columns represent: \n
 * 1) the secondary proton kinetic energy in GeV/n \n
 * 2) \f$d\sigma/dT(p + {\rm ISM} \rightarrow p)\f$ in mbarn / GeV \n
 *
 * @param T_proj is the proton primary energy
 * @param filename output file name
 */
void get_secondary_production(const double& T_proj, std::string filename) {
	DRAGON2::D2XSEC xsec;
	xsec.set_proton_xsecs("DRAGON2");
	auto x_pr = xsec.create_proton_xsecs();
	DRAGON2::TARGET H_ISM(1), He_ISM(2);
	std::ofstream outfile(filename);
	for (double T_sec = 0.1 * MKS::GeV; T_sec < T_proj; T_sec *= 1.1) {
		double sigma_H = x_pr->get_inelastic(H_ISM, T_proj) / T_proj;
		sigma_H += MKS::f_He * x_pr->get_inelastic(He_ISM, T_proj) / T_proj;
		outfile << std::scientific << T_sec / MKS::GeV << " " << sigma_H / MKS::mbarn << "\n";
	}
	outfile.close();
}

/**
 * @brief Main function for example3
 */
int main() {
	get_fragmentation_timescale("output/xsec_frag_protons.txt");
	get_secondary_production(100 * MKS::GeV, "output/xsec_secondary_protons.txt");
	return 0;
}
