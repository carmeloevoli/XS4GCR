#include "d2xsec.h"
#include "pid.h"

/**
 * @brief Compute the secondary production cross-sections.
 *
 * This function computes the ap production cross-sections
 * from the interaction of primary H and He on ISM and write them in a text file,
 * where columns represent: \n
 * 1) the primary kinetic energy per nucleon in GeV/n \n
 * 2) \f$\sigma(p + H_{ISM} \rightarrow \bar{p})\f$ in mbarn \n
 * 3) \f$\sigma(He + H_{ISM} \rightarrow \bar{p})\f$ in mbarn \n
 * 4) \f$\sigma(H + He_{ISM} \rightarrow \bar{p})\f$ in mbarn
 *
 * @param model production model identifier, e.g. Webber1993
 * @param filename output file name
 */
int main() {
	DRAGON2::D2XSEC xsec;

	xsec.set_secondary_nuclei("Webber1993");
	auto x_in = xsec.create_secondary_nuclei();

	DRAGON2::TARGET H_ISM(1), He_ISM(2);
	DRAGON2::channel ch(DRAGON2::C12, DRAGON2::Li6);

	std::cout << std::scientific;
	for (double T_n = MeV; T_n < 1.1 * TeV; T_n *= 1.1)
		std::cout << T_n / GeV << "\t" << x_in->get(ch, H_ISM, T_n, false) / mbarn << "\n";

	return 0;
}

