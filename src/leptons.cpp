#include "leptons.h"

double Secondary_Leptons::annihilation_xsec(const PID& target, const double& T_positron) const {
	double Gamma = 1.0 + T_positron / electron_mass_c2;
	double logGamma = std::log(Gamma + sqrt(pow2(Gamma) - 1));
	double value = target.get_Z() * M_PI * pow2(electron_radius) / (Gamma + 1.);
	value *= (pow2(Gamma) + 4 * Gamma + 1) / (pow2(Gamma) - 1) * logGamma - (Gamma + 3) / sqrt(pow2(Gamma) - 1);
	return value;
}

Kamae2006_Secondary_Leptons::Kamae2006_Secondary_Leptons(const PID& lepton) {
	assert(lepton.is_lepton());
	this->lepton = lepton;
	set_model_name("Kamae2006");
}

void Kamae2006_Secondary_Leptons::print() const {
	std::cout << "... use Kamae lepton production model: " << std::endl;
}

std::shared_ptr<Secondary_Leptons> Kamae2006_Secondary_Leptons::clone() {
	return std::make_shared<Kamae2006_Secondary_Leptons>(*this);
}

double Kamae2006_Secondary_Leptons::get_cparamlib_sigma(const PID& lepton_, const double& T_proton_GeV_,
		const double& T_lepton_GeV_) const {
	PARAMSET parameters;
	PARTICLE_IDS par;
	if (lepton_.is_electron()) {
		par = ID_ELECTRON;
		elec_param(T_proton_GeV_, &parameters);
	} else if (lepton_.is_positron()) {
		par = ID_POSITRON;
		posi_param(T_proton_GeV_, &parameters);
	} else {
		assert(lepton_.is_lepton());
	}
	double dsigma_dlogT = sigma_incl_tot(par, (T_lepton_GeV_ + electron_mass_c2), min(T_proton_GeV_, 1e5), &parameters);
	return dsigma_dlogT / T_lepton_GeV_ * (mbarn / GeV);
}

double Kamae2006_Secondary_Leptons::He_function(const double& T_n, const double& T_lepton) const {
	PID electron(-1, 0), positron(1, 0);
	double sigma_plus = get_cparamlib_sigma(positron, T_n / GeV, T_lepton / GeV);
	double sigma_minus = get_cparamlib_sigma(electron, T_n / GeV, T_lepton / GeV);
	double value = 1;
	if (sigma_plus > 0 && sigma_minus > 0)
		value /= .25 * sigma_plus / sigma_minus + .25 * sigma_minus / sigma_plus;
	return value;
}

double Kamae2006_Secondary_Leptons::get(const PID& projectile, const TARGET& target, const double& T_n,
		const double& T_lepton) const {
	assert(projectile == PID(1, 1) || projectile == PID(2, 4));
	double sigma_pp = get_cparamlib_sigma(lepton, T_n / GeV, T_lepton / GeV);
	if (projectile.is_H() && target.is_H()) {
		return sigma_pp;
	} else if (projectile.is_He() && target.is_He()) {
		return sigma_pp * HeHe_correction * ((lepton.is_electron()) ? He_function(T_n, T_lepton) : 1);
	} else {
		return sigma_pp * He_correction * ((lepton.is_electron()) ? He_function(T_n, T_lepton) : 1);
	}
}

HuangPohl2007_Secondary_Leptons::HuangPohl2007_Secondary_Leptons(const PID& lepton) {
	assert(lepton.is_lepton());
	this->lepton = lepton;
	set_model_name("HuangPohl2007");
}

void HuangPohl2007_Secondary_Leptons::print() const {
	std::cout << "... use HuangPohl2007 lepton production model: " << std::endl;
}

std::shared_ptr<Secondary_Leptons> HuangPohl2007_Secondary_Leptons::clone() {
	init();
	return std::make_shared<HuangPohl2007_Secondary_Leptons>(*this);
}

void HuangPohl2007_Secondary_Leptons::init() {
	check_datafiles_exist();
	resize_sigma_grids();
	read_data_file();
}

double HuangPohl2007_Secondary_Leptons::get(const PID& projectile, const TARGET& target, const double& T_n,
		const double& T_lepton) const {
	if (target.is_He())
		return 0;
	if (projectile.is_H()) {
		return dsigma_dT_H.get_interpolated(T_lepton, T_n + proton_mass_c2);
	} else {
		return dsigma_dT_He.get_interpolated(T_lepton, T_n + proton_mass_c2);
	}
}

void HuangPohl2007_Secondary_Leptons::check_datafiles_exist() {
	assert(file_exist(eminus_p_datafile));
	assert(file_exist(eminus_he_datafile));
	assert(file_exist(eplus_p_datafile));
	assert(file_exist(eplus_he_datafile));
	assert(file_exist(prodxsec_p_datafile));
	assert(file_exist(prodxsec_he_datafile));
}

void HuangPohl2007_Secondary_Leptons::resize_sigma_grids() {
	dsigma_dT_H.set_size(T_lepton_size, E_proj_size);
	dsigma_dT_H.set_x_range(T_lepton_min, T_lepton_max);
	dsigma_dT_H.set_y_range(E_proj_min, E_proj_max);
	dsigma_dT_He.set_size(T_lepton_size, E_proj_size);
	dsigma_dT_He.set_x_range(T_lepton_min, T_lepton_max);
	dsigma_dT_He.set_y_range(E_proj_min, E_proj_max);
}

std::vector<double> read_spectra_file(const std::string& filename, const size_t& x_size, const size_t& y_size) {
	std::vector<double> v;
	char s[20];
	std::ifstream infile(filename, std::ios::in);
	assert(infile.is_open());
	for (size_t i = 0; i < x_size; ++i) {
		for (size_t j = 0; j < y_size; ++j) {
			infile.get(s, 16);
			s[11] = 'E';
			v.push_back(atof(s));
		}
		infile.get(*s);
	}
	infile.close();
	return v;
}

std::vector<double> read_production_file(const std::string& filename, const size_t& x_size) {
	std::vector<double> v;
	char s[20];
	std::ifstream infile(filename, std::ios::in);
	assert(infile.is_open());
	for (size_t i = 0; i < x_size; ++i) {
		infile.get(s, 16);
		s[11] = 'E';
		v.push_back(atof(s));
	}
	infile.close();
	return v;
}

void HuangPohl2007_Secondary_Leptons::read_data_file() {
	std::vector<double> eminus_p_spectra = read_spectra_file(eminus_p_datafile, T_lepton_size, E_proj_size);
	std::vector<double> eminus_he_spectra = read_spectra_file(eminus_he_datafile, T_lepton_size, E_proj_size);
	std::vector<double> eplus_p_spectra = read_spectra_file(eplus_p_datafile, T_lepton_size, E_proj_size);
	std::vector<double> eplus_he_spectra = read_spectra_file(eplus_he_datafile, T_lepton_size, E_proj_size);
	std::vector<double> prod_xsec_p = read_production_file(prodxsec_p_datafile, E_proj_size);
	std::vector<double> prod_xsec_he = read_production_file(prodxsec_he_datafile, E_proj_size);
	std::cout << "... reading model from data files" << std::endl;
	double units = mbarn / GeV;
	for (size_t ix = 0; ix < T_lepton_size; ++ix) {
		for (size_t iy = 0; iy < E_proj_size; ++iy) {
			if (lepton.is_electron()) {
				dsigma_dT_H.get(ix, iy) = eminus_p_spectra.at(ix * E_proj_size + iy) * prod_xsec_p.at(iy) * units;
				dsigma_dT_He.get(ix, iy) = eminus_he_spectra.at(ix * E_proj_size + iy) * prod_xsec_he.at(iy) * units;
			} else if (lepton.is_positron()) {
				dsigma_dT_H.get(ix, iy) = eplus_p_spectra.at(ix * E_proj_size + iy) * prod_xsec_p.at(iy) * units;
				dsigma_dT_He.get(ix, iy) = eplus_he_spectra.at(ix * E_proj_size + iy) * prod_xsec_he.at(iy) * units;
			}
		}
	}
	return;
}
