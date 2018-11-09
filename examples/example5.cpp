#include "d2xsec.h"
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
void print_decay_properties(std::shared_ptr<DRAGON2::Decay_Chart> decays, DRAGON2::PID particle) {
	if (decays->get_halftime(particle) > 0) {
		std::cout << particle << " decays in "
				<< decays->get_halftime(DRAGON2::Be10) / year
				<< " years with mode " << decays->get_mode(DRAGON2::Be10)
				<< "\n";
	} else {
		std::cout << particle << " is stable (as far as we know).\n";
	}
}

/**
 * @brief Main function for example5
 */
int main() {
	DRAGON2::D2XSEC xsec;
	auto decays = xsec.create_decay_chart();
	print_decay_properties(decays, DRAGON2::Be10);
	print_decay_properties(decays, DRAGON2::B10);
	return 0;
}

