// Copyright (c) 2017 Carmelo Evoli - MIT License
#include "XS4GCR/antiprotons/TanNg83.h"

#include "XS4GCR/cgs.h"
namespace TanNg83 {

#define LIMIT 10000
#define KEY 3
#define EPSREL 1e-3

double sigma_invariant(const double& sqrt_s, const double& X_r, const double& p_T) {
    double value = 0;
    if (X_r <= 1) {
        double A = 3.95 / cgs::GeV_c;
        A *= std::exp(-2.76 * X_r);
        double B = 40.5 / pow2(cgs::GeV_c);
        B *= std::exp(-3.21 * X_r) * std::pow(X_r, 2.13);
        double f = 2.10 * std::pow(1 - X_r, 7.80);
        if (X_r <= 0.5) f += 3.34 * std::exp(-17.6 * X_r);
        f *= cgs::mbarn * pow3(cgs::c_light) / pow2(cgs::GeV);
        value = f * std::exp(-(A * p_T + B * p_T * p_T));
    }
    return value;
}

double sigma_func(double eta, void* params) {
    double* db_params = (double*)params;
    double sqrt_s = db_params[0];
    double s = sqrt_s * sqrt_s;
    double E_ap = db_params[1];
    double p_ap = db_params[2];

    double gamma_cm = sqrt_s / 2 / cgs::proton_mass_c2;
    double betagamma_cm = std::sqrt(s - 4 * pow2(cgs::proton_mass_c2)) / 2. / cgs::proton_mass_c2;
    double E_ap_cm = gamma_cm * E_ap - betagamma_cm * p_ap * cgs::c_light * std::tanh(eta);
    double X_r = 2 * sqrt_s * E_ap_cm;
    X_r /= s - 8 * pow2(cgs::proton_mass_c2);
    double p_T = p_ap / std::cosh(eta);

    return (X_r > 1) ? 0 : sigma_invariant(sqrt_s, X_r, p_T) / pow2(std::cosh(eta));
}

double dsigma_dT(double T_p, double T_ap) {
    double result = 0;
    double error = 0;
    double s = 2 * T_p * cgs::proton_mass_c2 + 4 * cgs::proton_mass_c2 * cgs::proton_mass_c2;
    double sqrt_s = std::sqrt(s);
    double p_ap = std::sqrt(T_ap * T_ap + 2 * cgs::proton_mass_c2 * T_ap) / cgs::c_light;
    if (sqrt_s > 4 * cgs::proton_mass_c2) {
        gsl_integration_workspace* w = gsl_integration_workspace_alloc(LIMIT);
        double params[3] = {sqrt_s, (T_ap + cgs::proton_mass_c2), p_ap};
        gsl_function F;
        F.function = &sigma_func;
        F.params = &params;
        gsl_integration_qagiu(&F, 0., 0., EPSREL, LIMIT, w, &result, &error);
        gsl_integration_workspace_free(w);
    }
    double neutron_factor = 2.3;
    return neutron_factor * 2 * M_PI * p_ap * result / pow2(cgs::c_light);
}

} /* namespace TanNg83 */
