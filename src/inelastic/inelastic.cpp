#include "inelastic.h"
#include "Tripathi99.h"

namespace DRAGON2 {

Letaw1983_Total_Inelastic::Letaw1983_Total_Inelastic() {
	set_model_name("Letaw1983");
}

void Letaw1983_Total_Inelastic::print() const {
	std::cout << "Using Letaw1983 total inelastic model: Letaw et al. 1983, ApJS, 51, 271" << std::endl;
}

std::shared_ptr<Total_Inelastic> Letaw1983_Total_Inelastic::clone() {
	return std::make_shared<Letaw1983_Total_Inelastic>(*this);
}

double Letaw1983_Total_Inelastic::get(const PID& projectile, const TARGET& target, const double& T_n) const {
	assert(projectile != PID(1, 1));
	double value = 45 * mbarn * pow(projectile.get_A(), 0.7);
	value *= (1.0 + 0.016 * sin(5.3 - 2.63 * log(projectile.get_A())));
	if (T_n < 5.0 * GeV)
		value *= 1.0 - 0.62 * exp(-T_n / 0.2 / GeV) * sin(1.58 / pow(T_n / GeV, 0.28));
	if (projectile.with_Z(2))
		value *= 0.8;
	if (projectile.with_Z(4))
		value *= 1.0 + 0.75 * exp(-T_n / 0.075 / GeV);
	return value;
}

/* Tripathi99 Total Inelastic */

Tripathi99_Total_Inelastic::Tripathi99_Total_Inelastic() {
	set_model_name("Tripathi+99");
}

void Tripathi99_Total_Inelastic::print() const {
	std::cout << "# Using Tripathi+99 total inelastic model:" << std::endl;
	std::cout << "# REF1" << std::endl;
}

std::shared_ptr<Total_Inelastic> Tripathi99_Total_Inelastic::clone() {
	return std::make_shared<Tripathi99_Total_Inelastic>(*this);
}

double Tripathi99_Total_Inelastic::get(const PID& projectile, const TARGET& target, const double& T_n) const {
	assert(projectile != PID(1, 1));
	int A_p = (target.is_H()) ? 1 : 4;
	int Z_p = (target.is_H()) ? 1 : 2;
	int A_t = projectile.get_A();
	int Z_t = projectile.get_Z();

	return Tripathi99::inelastic_sigma(A_p, Z_p, A_t, Z_t, T_n);
}

/* CROSEC Total Inelastic */

CROSEC_Total_Inelastic::CROSEC_Total_Inelastic() {
	set_model_name("CROSEC");
}

void CROSEC_Total_Inelastic::print() const {
	std::cout << "# Using CROSEC total inelastic model:" << '\n';
	std::cout << "# REF1" << '\n';
}

std::shared_ptr<Total_Inelastic> CROSEC_Total_Inelastic::clone() {
	init();
	return std::make_shared<CROSEC_Total_Inelastic>(*this);
}

void CROSEC_Total_Inelastic::init() {
	assert(file_exist(data_filename));
	int ISS = -1;
	sigtap_cc(ISS);
}

double CROSEC_Total_Inelastic::set_energy_within_range(const double& T_n) const {
	if (T_n < T_n_min)
		return T_n_min;
	else if (T_n > T_n_max)
		return T_n_max;
	else
		return T_n;
}

double CROSEC_Total_Inelastic::get(const PID& projectile, const TARGET& target, const double& T_n) const {
	assert(projectile != PID(1, 1));
	double TA = projectile.get_A(), TZ = projectile.get_Z(); // target nucleus mass and charge numbers (4.0<=A2<=239.0)
	double T = set_energy_within_range(T_n) / MeV; // projectile particle kinetic energy (MEV; 14(20)MEV<T<1TEV)
	double value = sighad_cc(IS, PA, PZ, TA, TZ, T) * mbarn;
	value *= (target.is_He()) ? 2.1 * pow(projectile.get_A(), .055) : 1;
	return value;
}

} // namespace DRAGON2
