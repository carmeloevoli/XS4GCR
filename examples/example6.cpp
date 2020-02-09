#include "d2xsec.h"
#include "pid.h"

#include <vector>

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
	DRAGON2::D2XSEC xsec;

	xsec.set_secondary_nuclei("Evoli2018");
	auto x_in = xsec.create_secondary_nuclei();

	DRAGON2::TARGET H_ISM(1), He_ISM(2);

	DRAGON2::PID proj = DRAGON2::N14;

	std::vector<DRAGON2::PID> fragments { DRAGON2::Li6, DRAGON2::Li7, DRAGON2::Be7, DRAGON2::Be9,
			DRAGON2::Be10, DRAGON2::B10, DRAGON2::B11 };

	std::cout << std::scientific;

	for (double T_n = 100. * MKS::MeV; T_n < 2e4 * MKS::GeV; T_n *= 1.1) {
		std::cout << T_n / MKS::GeV << "\t";
		for (auto& fragment : fragments) {
			DRAGON2::channel ch(proj, fragment);
			std::cout << x_in->get(ch, H_ISM, T_n, true) / MKS::mbarn << "\t";
		}
		std::cout << "\n";
	}
	return 0;
}
