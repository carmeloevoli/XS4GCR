#include "protons.h"

DRAGON2_Proton_Xsecs::DRAGON2_Proton_Xsecs() {
	set_model_name("DRAGON2");
}

void DRAGON2_Proton_Xsecs::print() const {
	std::cout << "... use Kamae lepton production model: " << std::endl;
}

std::shared_ptr<Proton_Xsecs> DRAGON2_Proton_Xsecs::clone() {
	return std::make_shared<DRAGON2_Proton_Xsecs>(*this);
}

double DRAGON2_Proton_Xsecs::get_inelastic(const TARGET& target, const double& T) const {
	double value = 0;
	if (target.is_H()) {
		double x = T / T_threshold;
		if (x > 1) {
			value = 30.7 - 0.96 * log(x) + 0.18 * pow2(log(x));
			value *= pow3(1 - pow(x, -1.9));
		}
		return value * mbarn;
	}
	else {
		return Tripathi99::inelastic_sigma(4, 2, 1, 1, T);
	}
}
