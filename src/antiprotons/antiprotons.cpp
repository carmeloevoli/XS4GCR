#include "antiprotons.h"

namespace DRAGON2 {

double Secondary_Antiprotons::get_total_inelastic(const TARGET& target, const double& T_ap) {
	double value = 0;
	if (target.is_H()) {
		double E_GeV = (T_ap + MKS::proton_mass_c2) / MKS::GeV;
		double R_GV = std::sqrt(E_GeV * E_GeV - MKS::proton_mass_c2 * MKS::proton_mass_c2);
		value = a[0] + a[1] * log(R_GV) + a[2] * pow2(log(R_GV)) + a[3] * pow(R_GV, -alpha);
	} else { // duperray2003
		double sigma_0 = 45 * pow(4, 0.7) * (1. + 0.016 * std::sin(5.3 - 2.63 * std::log(4.)));
		double E_inc = T_ap / MKS::MeV;
		value = sigma_0 * (1. - 0.62 * std::exp(-E_inc / 200) * std::sin(10.9 * std::pow(E_inc, -0.28)));
	}
	return value * MKS::mbarn;
}

double Secondary_Antiprotons::get_annihilating_inelastic(const TARGET& target, const double& T_ap) {
	double E_GeV = (T_ap + MKS::proton_mass_c2) / MKS::GeV;
	double R_GV = std::sqrt(E_GeV * E_GeV - MKS::proton_mass_c2 * MKS::proton_mass_c2);
	double value = b[0] + b[1] * log(R_GV) + b[2] * pow2(log(R_GV)) + b[3] * pow(R_GV, -alpha);
	if (target.is_He())
		value *= get_total_inelastic(target, T_ap) / get_total_inelastic(TARGET(1), T_ap);
	return value * MKS::mbarn;
}

double Secondary_Antiprotons::get_non_annihilating_inelastic(const TARGET& target, const double& T_ap) {
	return get_total_inelastic(target, T_ap) - get_annihilating_inelastic(target, T_ap);
}

TanNg1983_antiprotons::TanNg1983_antiprotons() {
	set_model_name("TanNg1983");
}

void TanNg1983_antiprotons::print() const {
	std::cout << "#Using Tan & Ng 1983 antiproton model: REF" << std::endl;
}

std::shared_ptr<Secondary_Antiprotons> TanNg1983_antiprotons::clone() {
	return std::make_shared<TanNg1983_antiprotons>(*this);
}

double TanNg1983_antiprotons::get(const PID& particle, const TARGET& target, const double& T_n,
		const double& T_ap) const {
	if (particle.is_H() && target.is_H()) {
		double sigma_pp = TanNg83::dsigma_dT(T_n, T_ap);
		return sigma_pp;
	} else {
		double sigma_pA = 0;
		return sigma_pA;
	}
}

DiMauro_Secondary_Antiprotons::DiMauro_Secondary_Antiprotons() {
	set_model_name("DiMauro");
}

void DiMauro_Secondary_Antiprotons::print() const {
	std::cout << "#Using DiMauro2015 antiproton model: REF" << std::endl;
}

std::shared_ptr<Secondary_Antiprotons> DiMauro_Secondary_Antiprotons::clone() {
	return std::make_shared<DiMauro_Secondary_Antiprotons>(*this);
}

double DiMauro_Secondary_Antiprotons::get(const PID& particle, const TARGET& target, const double& T_n,
		const double& T_ap) const {
	if (particle == PID(1, 1) && target.is_H()) {
		return DiMauro2015::dsigma_dT(T_n, T_ap);
	} else if (particle == PID(2, 4) && target.is_H()) {
		return Duperray03::dsigma_dT(T_n, T_ap);
	} else if (particle == PID(1, 1) && target.is_He()) {
		return Duperray03::dsigma_dT(T_n, T_ap);
	} else {
		return 0;
	}
}

Winkler2017_antiprotons::Winkler2017_antiprotons() :
		data_filename("data/Winkler2017_antiprotons.txt"), table(std::make_pair(132, 251)) {
	set_model_name("Winkler2017");
	assert(file_exist(data_filename));
	table.read_data_file(data_filename, MKS::GeV, MKS::mbarn / MKS::GeV);
}

void Winkler2017_antiprotons::print() const {
	std::cout << "#Using Winkler2017 antiproton model: REF" << std::endl;
}

std::shared_ptr<Secondary_Antiprotons> Winkler2017_antiprotons::clone() {
	return std::make_shared<Winkler2017_antiprotons>(*this);
}

double Winkler2017_antiprotons::get(const PID& projectile, const TARGET& target, const double& T_n,
		const double& T_ap) const {
	return table.dsigma_dT(T_n, T_ap, projectile.is_H(), target.is_H());
}

Feng2016_antiprotons::Feng2016_antiprotons(generators g) :
		generator(g), table(std::make_pair(129, 129)) {
	set_model_name("Feng2016");
	std::string filename;
	if (generator == EPOS)
		filename = "data/Feng2016_EPOS_LHC_antiprotons.txt";
	else if (generator == SIBYLL)
		filename = "data/Feng2016_EPOS_LHC_antiprotons.txt";
	else if (generator == QGSJET)
		filename = "data/Feng2016_EPOS_LHC_antiprotons.txt";
	else if (generator == DIMAURO)
		filename = "data/Feng2016_QGSJET04_antiprotons.txt";
	else
		assert(generator == EPOS);
	table.read_data_file(filename, MKS::GeV, MKS::barn / MKS::GeV);
}

void Feng2016_antiprotons::print() const {
	std::cout << "#Using Feng2016" << "\n";
}

std::shared_ptr<Secondary_Antiprotons> Feng2016_antiprotons::clone() {
	return std::make_shared<Feng2016_antiprotons>(*this);
}

double Feng2016_antiprotons::get(const PID& projectile, const TARGET& target, const double& T_n,
		const double& T_ap) const {
	return table.dsigma_dT(T_n, T_ap, projectile.is_H(), target.is_H());
}

} // namespace DRAGON2

