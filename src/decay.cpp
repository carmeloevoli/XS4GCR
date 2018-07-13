#include "decay.h"

namespace DRAGON2 {

void DRAGON2_Decay_Chart::print() {
	std::cout << "Using DRAGON2 decay chart: REF" << std::endl;
}

std::shared_ptr<Decay_Chart> DRAGON2_Decay_Chart::clone() {
	return std::make_shared<DRAGON2_Decay_Chart>(*this);
}

double DRAGON2_Decay_Chart::get_halftime(PID particle) {
	if (particle == PID(3, 4)) {
		return 100;
	} else {
		return 0;
	}
}

DRAGON2_Decay_Chart::decay_mode DRAGON2_Decay_Chart::get_mode(PID particle) {
	if (particle == PID(3, 4)) {
		return EC;
	} else {
		return STABLE;
	}
}

} // namespace DRAGON2
