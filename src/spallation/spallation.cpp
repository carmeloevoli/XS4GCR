#include "spallation.h"

namespace DRAGON2 {

Webber1993_Spallation::Webber1993_Spallation() {
}

void Webber1993_Spallation::print() {
	std::cout << "# using Webber1998 spallation model: REF" << '\n';
}

void Webber1993_Spallation::init() {
	set_sigma_cc();
}

std::shared_ptr<Spallation> Webber1993_Spallation::clone() {
	init();
	return std::make_shared<Webber1993_Spallation>(*this);
}

double Webber1993_Spallation::direct(const channel& ch, const double& T_n) {
	PID proj = ch.first, frag = ch.second;
	double direct = 0.;
	if (frag.get_Z() <= 3)
		direct = yieldx_cc(proj.get_Z(), proj.get_A(), frag.get_Z(), frag.get_A(), T_n);
	else
		direct = wsigma_cc(proj.get_Z(), proj.get_A(), frag.get_Z(), frag.get_A(), T_n);
	return direct;
}

double Webber1993_Spallation::get(const channel& ch, const TARGET& target, const double& T_n,
		bool do_ghosts) {
	assert(ch.first != ch.second);
	assert(!do_ghosts); // Ghosts are not implemented in this model
	double value = direct(ch, T_n);
	value *= (target.is_H()) ? 1 : Ferrando1998_He2H(T_n, ch.first.get_Z(), ch.second.get_Z());
	return value;
}

} // namespace DRAGON2
