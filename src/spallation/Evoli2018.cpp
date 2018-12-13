#include "Evoli2018.h"

namespace DRAGON2 {

Evoli2018_Spallation::Evoli2018_Spallation() {
}

void Evoli2018_Spallation::print() {
	std::cout << "# using Evoli2018 spallation model: REF" << '\n';
}

void Evoli2018_Spallation::init() {
	assert(file_exist(paramsfit_filename));
	fittingFormulae = Evoli2018_table(paramsfit_filename);
	assert(file_exist(ghostlist_filename));
	ghostTree = GhostTree(ghostlist_filename);
	set_sigma_cc();
}

std::shared_ptr<Spallation> Evoli2018_Spallation::clone() {
	init();
	return std::make_shared<Evoli2018_Spallation>(*this);
}

double Evoli2018_Spallation::get(const channel& ch, const TARGET& target, const double& T_n,
		bool do_ghosts) {
	if (do_ghosts)
		return with_ghosts(ch, T_n);
	else
		return direct(ch, T_n);
}

double Evoli2018_Spallation::direct(const channel& ch, const double& T_n) {
	double value = fittingFormulae.get(ch, T_n);
	if (value < 0) {
		PID proj = ch.first, frag = ch.second;
		if (frag.get_Z() <= 3)
			value = yieldx_cc(proj.get_Z(), proj.get_A(), frag.get_Z(), frag.get_A(), T_n);
		else
			value = wsigma_cc(proj.get_Z(), proj.get_A(), frag.get_Z(), frag.get_A(), T_n);
	}
	return value;
}

double Evoli2018_Spallation::with_ghosts(const channel& ch, const double& T_n) {
	auto projectile = ch.first;
	auto child = ch.second;
	if (ghostTree.n_parents(child) == 0) {
		return direct(ch, T_n);
	} else {
		double value = 0;
		for (auto& p : ghostTree.get_parents(child)) {
			value += p.second * with_ghosts(std::make_pair(projectile, p.first), T_n);
		}
		return value + direct(ch, T_n);
	}
}

} // namespace DRAGON2
