#include "Duperray03.h"

namespace Duperray03 {

#define LIMIT 10000
#define KEY 3
#define EPSREL 1e-3

static double C[11] = { 0, 0.16990, 10.28, 2.269, 3.707, 0.009205, 0.4812, 3.3600, 0.063940, -0.1824, 2.4850 };
static double A_He = 4;

double sigma_in() {
	double sigma_0 = 45 * std::pow(A_He, 0.7);
	sigma_0 *= 1 + 0.016 * std::sin(5.3 - 2.63 * std::log(A_He));
	return sigma_0;
}

double sigma_invariant(const double &sqrt_s, const double &X_r, const double &p_T) { // TODO check units
	double sqrt_s_GeV = sqrt_s / GeV;
	double p_T_GeVc = p_T / GeV_c;
	double value = sigma_in();
	value *= std::pow(A_He, C[1] * std::log(sqrt_s_GeV / C[2]) * p_T_GeVc);
	value *= std::pow(1. - X_r, C[3] * std::log(sqrt_s_GeV));
	value *= std::exp(-C[4] * X_r);
	value *= C[5] * std::pow(sqrt_s_GeV, C[6]) * std::exp(-C[7] * p_T_GeVc)
			+ C[8] * std::pow(sqrt_s_GeV, C[9]) * std::exp(-C[10] * p_T_GeVc * p_T_GeVc);
	return max(value, 0.) * mbarn * pow3(c_light) / pow2(GeV);
}

double sigma_func(double eta, void *params) {
	double *db_params = (double *) params;
	double sqrt_s = db_params[0];
	double s = sqrt_s * sqrt_s;
	double E_ap = db_params[1];
	double p_ap = db_params[2];

	double gamma_cm = sqrt_s / 2 / proton_mass_c2;
	double betagamma_cm = std::sqrt(s - 4 * proton_mass_c2_2) / 2 / proton_mass_c2;
	double E_ap_cm = gamma_cm * E_ap - betagamma_cm * p_ap * c_light * std::tanh(eta);
	double X_r = 2 * sqrt_s * E_ap_cm;
	X_r /= s - 8 * proton_mass_c2_2;
	double p_T = p_ap / std::cosh(eta);

	return (X_r > 1) ? 0 : sigma_invariant(sqrt_s, X_r, p_T) / pow2(std::cosh(eta));
}

double dsigma_dT(double T_n, double T_ap) {
	double result = 0, error = 0;
	double s = 2 * T_n * proton_mass_c2 + 4 * proton_mass_c2 * proton_mass_c2;
	double sqrt_s = std::sqrt(s);
	double p_ap = std::sqrt(T_ap * T_ap + 2 * proton_mass_c2 * T_ap) / c_light;
	if (sqrt_s > 4 * proton_mass_c2) {
		gsl_integration_workspace *w = gsl_integration_workspace_alloc(LIMIT);
		double params[3] = { sqrt_s, (T_ap + proton_mass_c2), p_ap };
		gsl_function F;
		F.function = &sigma_func;
		F.params = &params;
		gsl_integration_qagiu(&F, 0., 0., EPSREL, LIMIT, w, &result, &error);
		gsl_integration_workspace_free(w);
	}
	double neutron_factor = 2.3;
	return neutron_factor * 2 * M_PI * p_ap * result / pow2(c_light);
}

} /* namespace Duperray03 */
