#include "spallation.h"

namespace DRAGON2 {

Webber1993_Spallation::Webber1993_Spallation() {
}

Webber2003_Spallation::Webber2003_Spallation() {
}

void Webber1993_Spallation::print() {
	std::cout << "# using Webber1998 spallation model: REF" << '\n';
}

void Webber2003_Spallation::print() {
	std::cout << "# using Webber2003 spallation model: REF" << '\n';
}

void Webber1993_Spallation::init() {
	set_sigma_cc();
}

void Webber2003_Spallation::init() {
    //assert(file_exist(data_filename));
    //read_data_file();
    //std::cout << " - read reaction database with size " << spallation_map.size() << '\n';
    assert(file_exist(ghostlist_filename));
	ghostTree = GhostTree(ghostlist_filename);
    //read_ghost_list();
    //std::cout << " - read ghost nuclei database with size " << ghosts_map.size() << '\n';
	set_sigma_cc();
}

std::shared_ptr<Spallation> Webber1993_Spallation::clone() {
	init();
	return std::make_shared<Webber1993_Spallation>(*this);
}

std::shared_ptr<Spallation> Webber2003_Spallation::clone() {
	init();
	return std::make_shared<Webber2003_Spallation>(*this);
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

double Webber1993_Spallation::get(const channel& ch, const TARGET& target, const double& T_n, bool do_ghosts) {
	assert(ch.first != ch.second);
	assert(!do_ghosts); // Ghosts are not implemented in this model
	double value = direct(ch, T_n);
	value *= (target.is_H()) ? 1 : Ferrando1998_He2H(T_n, ch.first.get_Z(), ch.second.get_Z());
	return value;
}

double Webber2003_Spallation::get(const channel& ch, const TARGET& target, const double& T_n, bool do_ghosts) {
	return with_ghosts(ch, T_n);
}

double sigma_s(PID pid) {
	return 1;
}

double Webber2003_Spallation::with_ghosts(const channel& ch, const double& T_n) {
	auto projectile = ch.first;
	auto child = ch.second;
	if (ghostTree.n_parents(child) == 0) {
		return sigma_s(child);
	}
	else {
		double value = 0;
		for (auto& p : ghostTree.get_parents(child)) {
			value += p.second * with_ghosts(std::make_pair(projectile, p.first), T_n);
		}
		return value + sigma_s(child);
	}
}

} // namespace DRAGON2
