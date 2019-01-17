#include "Evoli2018.h"

namespace DRAGON2 {

Evoli2018_Spallation::Evoli2018_Spallation() {
}

void Evoli2018_Spallation::print() {
	std::cout << "# using Evoli2018 spallation model: REF" << '\n';
}

void Evoli2018_Spallation::init() {
	assert(file_exist(fitdata_filename));
	fitData = FitData(fitdata_filename);
	assert(file_exist(paramsfit_filename));
	fittingFunctions = FittingFunctions(paramsfit_filename);
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

double Evoli2018_Spallation::bestfit_normalization(const channel& ch) {
	auto data = fitData.get_data(ch);
	PID proj = ch.first, frag = ch.second;

	std::pair<double, double> bestfit(1e100, 1e100);

	for (double norm = 0.1; norm < 10.; norm *= 1.01) {
		double chi2 = 0.;
		for (auto d : data) {
			double model = 0;
			if (frag.get_Z() <= 3)
				model = norm
						* yieldx_cc(proj.get_Z(), proj.get_A(), frag.get_Z(), frag.get_A(), d.T);
			else
				model = norm
						* wsigma_cc(proj.get_Z(), proj.get_A(), frag.get_Z(), frag.get_A(), d.T);
			chi2 += pow2(d.sigma - model) / pow2(d.sigma_err);
		}
		if (chi2 < bestfit.first) {
			bestfit.first = chi2;
			bestfit.second = norm;
		}
	}
	return bestfit.second;
}

double Evoli2018_Spallation::direct(const channel& ch, const double& T_n) {
	if (fittingFunctions.is_present(ch)) {
		return fittingFunctions.get(ch, T_n);
	} else {
		double norm = 1.;
		if (fitData.channel_exists(ch))
			norm = bestfit_normalization(ch);
		PID proj = ch.first, frag = ch.second;
		if (frag.get_Z() <= 3)
			return norm * yieldx_cc(proj.get_Z(), proj.get_A(), frag.get_Z(), frag.get_A(), T_n);
		else
			return norm * wsigma_cc(proj.get_Z(), proj.get_A(), frag.get_Z(), frag.get_A(), T_n);
	}
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
