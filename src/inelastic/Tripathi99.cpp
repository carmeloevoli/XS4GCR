#include "Tripathi99.h"

namespace Tripathi99 {

double get_wilson_rms_radius(const int& A) {
	double factor = std::sqrt(5. / 3.) * MKS::fm;

	double radius;
	if (A > 26) {
		radius = factor * (0.84 * pow((double) A, 1. / 3.) + 0.55);
	} else {
		std::vector<double> r = { 0.0, 0.85, 2.095, 1.976, 1.671, 1.986, 2.57, 2.41, 2.23, 2.519, 2.45, 2.42, 2.471,
				2.440, 2.58, 2.611, 2.730, 2.662, 2.727, 2.9, 3.040, 2.867, 2.969, 2.94, 3.075, 3.11, 3.06 };
		radius = factor * r.at(A);
	}
	return radius;
}

double get_wilson_radius(const int& A) {
	double r_0 = 0.85 * MKS::fm;
	double r = get_wilson_rms_radius(A);
	return 1.29 * std::sqrt(r * r - r_0 * r_0);
}

double inelastic_sigma(int A_p, int Z_p, int A_t, int Z_t, double T_n) {
	assert(A_p > 0 && A_t > 0);
	const double r_0 = 1.1 * MKS::fm;
	double f_A = pow2(A_p) + pow2(A_t) + 2 * A_p * A_t * (1. + T_n / MKS::proton_mass_c2);
	double E_cm_mev = MKS::proton_mass_c2 * std::sqrt(f_A);
	E_cm_mev /= MKS::MeV;
	double Tn_mev = T_n / MKS::MeV;

	if (E_cm_mev <= (0.8 + 0.04 * Z_t) * A_p) {
		return 0.;
	}

	double r_rms_p = get_wilson_rms_radius(A_p);
	double r_rms_t = get_wilson_rms_radius(A_t);
	double r_p = 1.29 * r_rms_p;
	double r_t = 1.29 * r_rms_t;
	double Radius = (r_p + r_t) / MKS::fm;
	Radius += 1.2 * (pow(A_p, 1. / 3.) + pow(A_t, 1. / 3.)) / pow(E_cm_mev, 1. / 3.);
	double B = 1.44 * Z_p * Z_t / Radius;

	double D = 2.05;
	double T_1 = 40;
	double G;
	if ((A_t == 1 && Z_t == 1) || (A_p == 1 && Z_p == 1)) {
		T_1 = 23.0;
		D = 1.85 + 0.16 / (1. + exp((500. - Tn_mev) / 200.));
	} else if ((A_t == 1 && Z_t == 0) || (A_p == 1 && Z_p == 0)) {
		T_1 = 18.0;
		D = 1.85 + 0.16 / (1. + exp((500. - Tn_mev) / 200.));
	} else if ((A_t == 2 && Z_t == 1) || (A_p == 2 && Z_p == 1)) {
		T_1 = 23.0;
		D = 1.65 + 0.1 / (1. + exp((500. - Tn_mev) / 200.));
	} else if ((A_t == 3 && Z_t == 2) || (A_p == 3 && Z_p == 2)) {
		T_1 = 40.0;
		D = 1.55;
	} else if (A_p == 4 && Z_p == 2) {
		if (A_t == 4 && Z_t == 2) {
			T_1 = 40.0;
			G = 300.0;
		} else if (Z_t == 4) {
			T_1 = 25.0;
			G = 300.0;
		} else if (Z_t == 7) {
			T_1 = 40.0;
			G = 500.0;
		} else if (Z_t == 13) {
			T_1 = 25.0;
			G = 300.0;
		} else if (Z_t == 26) {
			T_1 = 40.0;
			G = 300.0;
		} else {
			T_1 = 40.0;
			G = 75.0;
		}
		D = 2.77 - 8e-3 * A_t + 1.8e-5 * pow2(A_t) - 0.8 / (1. + exp((250. - Tn_mev) / G));
	} else if (A_t == 4 && Z_t == 2) {
		if (A_p == 4 && Z_p == 2) {
			T_1 = 40.0;
			G = 300.0;
		} else if (Z_p == 4) {
			T_1 = 25.0;
			G = 300.0;
		} else if (Z_p == 7) {
			T_1 = 40.0;
			G = 500.0;
		} else if (Z_p == 13) {
			T_1 = 25.0;
			G = 300.0;
		} else if (Z_p == 26) {
			T_1 = 40.0;
			G = 300.0;
		} else {
			T_1 = 40.0;
			G = 75.0;
		}
		D = 2.77 - 8e-3 * A_t + 1.8e-5 * pow2(A_t) - 0.8 / (1. + exp((250. - Tn_mev) / G));
	}

	double C_E = D * (1 - exp(-Tn_mev / T_1));
	C_E -= 0.292 * exp(-Tn_mev / 792.) * std::cos(0.229 * pow(Tn_mev, 0.453));

	double S = pow(A_p, 1. / 3.) * pow(A_t, 1. / 3.);
	S /= pow(A_p, 1. / 3.) + pow(A_t, 1. / 3.);

	double delta_E = 0;
	double X_1 = 0;
	delta_E = 1.85 * S;
	delta_E += 0.16 * S / pow(E_cm_mev, 1. / 3.);
	delta_E -= C_E;
	if (A_t >= A_p) {
		delta_E += 0.91 * (A_t - 2. * Z_t) * Z_p / A_t / A_p;
		X_1 = 2.83 - 3.1e-2 * A_t + 1.7e-4 * A_t * A_t;
	} else {
		delta_E += 0.91 * (A_p - 2. * Z_p) * Z_t / A_t / A_p;
		X_1 = 2.83 - 3.1e-2 * A_p + 1.7e-4 * A_p * A_p;
	}

	double S_L = 1.2 + 1.6 * (1 - exp(-Tn_mev / 15));
	double X_m = 1 - X_1 * exp(-Tn_mev / X_1 / S_L);

	double R_c = 1.0;
	if (A_p == 1 && Z_p == 1) {
		if (A_t == 2 && Z_t == 1)
			R_c = 13.5;
		else if (A_t == 3 && Z_t == 2)
			R_c = 21.0;
		else if (A_t == 4 && Z_t == 2)
			R_c = 27.0;
		else if (Z_t == 3)
			R_c = 2.2;
	} else if (A_t == 1 && Z_t == 1) {
		if (A_p == 2 && Z_p == 1)
			R_c = 13.5;
		else if (A_p == 3 && Z_p == 2)
			R_c = 21.0;
		else if (A_p == 4 && Z_p == 2)
			R_c = 27.0;
		else if (Z_p == 3)
			R_c = 2.2;
	} else if (A_p == 2 && Z_p == 1) {
		if (A_t == 2 && Z_t == 1)
			R_c = 13.5;
		else if (A_t == 4 && Z_t == 2)
			R_c = 13.5;
		else if (A_t == 12 && Z_t == 6)
			R_c = 6.0;
	} else if (A_t == 2 && Z_t == 1) {
		if (A_p == 2 && Z_p == 1)
			R_c = 13.5;
		else if (A_p == 4 && Z_p == 2)
			R_c = 13.5;
		else if (A_p == 12 && Z_p == 6)
			R_c = 6.0;
	} else if ((A_p == 4 && Z_p == 2 && (Z_t == 73 || Z_t == 79)) || (A_t == 4 && Z_t == 2 && (Z_p == 73 || Z_p == 79)))
		R_c = 0.6;

	double value = M_PI * pow2(r_0);
	value *= pow2(pow(A_p, 1. / 3.) + pow(A_t, 1. / 3.) + delta_E);
	value *= (1. - R_c * B / E_cm_mev) * X_m;
	return std::max(0., value);
}

} /* namespace Tripathi99 */

