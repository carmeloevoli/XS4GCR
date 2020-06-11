#include "../include/xs4gcr.h"
#include "pid.h"

/**
 * @example example5.cpp
 *
 * In this example the decay properties of a
 * nuclear species are displayed.
 *
 * @see https://arxiv.org/abs/1711.09616
 */

/**
 * @brief Display half-life in year and decay mode
 *
 * @param particle identifier
 */
void print_decay_properties(std::shared_ptr<XS4GCR::Decay_Chart> decays, XS4GCR::PID particle) {
	if (decays->get_halftime(particle) > 0) {
		std::cout << particle << " decays in "
				<< decays->get_halftime(XS4GCR::Be10) / MKS::year
				<< " years with mode " << decays->get_mode(XS4GCR::Be10)
				<< "\n";
	} else {
		std::cout << particle << " is stable (as far as we know).\n";
	}
}

/**
 * @brief Main function for example5
 */
int main() {
	XS4GCR::D2XSEC xsec;
	auto decays = xsec.create_decay_chart();
	print_decay_properties(decays, XS4GCR::Be10);
	print_decay_properties(decays, XS4GCR::B10);
	return 0;
}

