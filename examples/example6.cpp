#include "pid.h"

#include <vector>
#include "../include/xs4gcr.h"

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
	XS4GCR::D2XSEC xsec;

	xsec.set_secondary_nuclei("Evoli2018");
	auto x_in = xsec.create_secondary_nuclei();

	XS4GCR::TARGET H_ISM(1), He_ISM(2);

	XS4GCR::PID proj = XS4GCR::N14;

	std::vector<XS4GCR::PID> fragments { XS4GCR::Li6, XS4GCR::Li7, XS4GCR::Be7, XS4GCR::Be9,
			XS4GCR::Be10, XS4GCR::B10, XS4GCR::B11 };

	std::cout << std::scientific;

	for (double T_n = 100. * MKS::MeV; T_n < 2e4 * MKS::GeV; T_n *= 1.1) {
		std::cout << T_n / MKS::GeV << "\t";
		for (auto& fragment : fragments) {
			XS4GCR::channel ch(proj, fragment);
			std::cout << x_in->get(ch, H_ISM, T_n, true) / MKS::mbarn << "\t";
		}
		std::cout << "\n";
	}
	return 0;
}
