#include "d2xsec.h"

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
 * @remark to compute electron production xsecs one must use \c xsec.create_secondary_leptons(electron)
 * @remark primary kinetic energy per nucleon \c T_n_proj is 100 GeV
 */
int main() {
	DRAGON2::D2XSEC xsec;
	xsec.set_secondary_leptons("Kamae2006");

	DRAGON2::PID electron(-1, 0), positron(1, 0);
	DRAGON2::PID H(1, 1), He(2, 4);
	DRAGON2::TARGET H_ISM(1), He_ISM(2);

	auto x_leptons = xsec.create_secondary_leptons(positron);

	double T_n_proj = 100 * GeV;

	for (double T_lepton = 1 * GeV; T_lepton < T_n_proj; T_lepton *= 1.1) {
		std::cout << T_lepton / GeV << " ";
		std::cout << x_leptons->get(H, H_ISM, T_n_proj, T_lepton) / (mbarn / GeV) << "\t";
		std::cout << x_leptons->get(He, H_ISM, T_n_proj, T_lepton) / (mbarn / GeV) << "\n";
	}
}
