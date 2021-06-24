// Copyright (c) 2017 Carmelo Evoli - MIT License
#include "XS4GCR/antiprotons/DiMauro2015.h"

#include <algorithm>

#include "XS4GCR/cgs.h"
namespace DiMauro2015 {

#define LIMIT 10000
#define EPSREL 1e-3

class sigma_total {
   public:
    sigma_total() {}

    virtual ~sigma_total() {}

    double get(const double &s_GeV) {
        return Zt + Bt * pow2(log(s_GeV / smt)) + Y1t * pow(smt / s_GeV, eta1t) -
               Y2t * pow(smt / s_GeV, eta2t);
    }

   private:
    double Zt = 33.44;
    double Mt = 2.06;
    double Y1t = 13.53;
    double Y2t = 6.38;
    double eta1t = 0.324;
    double eta2t = 0.324;
    double mp = 0.938;  // proton_mass_c2 / GeV;
    double pi_hbar_c__mbarn_2 =
        1.22327;  // M_PI * pow2(h_planck / 2. / M_PI * c_light / sqrt(mbarn)) / pow2(GeV);
    double smt = pow2(2 * mp + Mt);
    double Bt = pi_hbar_c__mbarn_2 / pow2(Mt);
};

class sigma_elastic {
   public:
    sigma_elastic() {}

    virtual ~sigma_elastic() {}

    double get(const double &s_GeV) {
        return Ze + Be * pow(log(s_GeV / sme), 2.) + Y1e * pow(sme / s_GeV, eta1e) -
               Y2e * pow(sme / s_GeV, eta2e);
    }

   private:
    double pi_hbar_c__mbarn_2 =
        1.22327;        // M_PI * pow2(h_planck / 2. / M_PI * c_light / sqrt(mbarn)) / pow2(GeV);
    double mp = 0.938;  // proton_mass_c2 / GeV;
    double Ze = 144.98;
    double Me = 3.06;
    double sme = pow2(2 * mp + Me);
    double Be = pi_hbar_c__mbarn_2 / pow2(Me);
    double Y1e = 2.64;
    double Y2e = 137.27;
    double eta1e = 1.57;
    double eta2e = -4.65 * 1e-3;
};

class fitting_func {
   public:
    fitting_func() {}

    ~fitting_func() {}

    double get(const double &X_r, const double &sqrt_s_GeV, const double &p_T_GeV) {
        double value = pow(1. - X_r, C1) * exp(-C2 * X_r);
        value *= C3 * pow(sqrt_s_GeV, C4) * exp(-C5 * p_T_GeV) +
                 C6 * pow(sqrt_s_GeV, C7) * exp(-C8 * p_T_GeV * p_T_GeV);
        return value;
    }

   private:
    double C1 = 4.49878e+00;
    double C2 = 3.40740e+00;
    double C3 = 9.41840e-03;
    double C4 = 4.44547e-01;
    double C5 = 3.50178e+00;
    double C6 = 6.22119e-02;
    double C7 = -2.47658e-01;
    double C8 = 2.57568e+00;
};

double sigma_invariant(const double &sqrt_s, const double &X_r, const double &p_T) {
    double value = 0;
    if (X_r <= 1) {
        sigma_total sigmatot;
        sigma_elastic sigmaele;
        fitting_func func;
        double sqrt_s_GeV = std::min(sqrt_s / cgs::GeV, 1e3);
        double p_T_GeVc = std::min(p_T / cgs::GeV_c, 1e3);
        double sigma_inelastic = sigmatot.get(pow2(sqrt_s_GeV)) - sigmaele.get(pow2(sqrt_s_GeV));
        value = sigma_inelastic * func.get(X_r, sqrt_s_GeV, p_T_GeVc);
    }
    return std::max(value, 0.) * cgs::mbarn * pow3(cgs::c_light) / pow2(cgs::GeV);
}

double sigma_func(double eta, void *params) {
    double *db_params = (double *)params;
    double sqrt_s = db_params[0];
    double s = sqrt_s * sqrt_s;
    double E_ap = db_params[1];
    double p_ap = db_params[2];

    double gamma_cm = sqrt_s / 2 / cgs::proton_mass_c2;
    double betagamma_cm = std::sqrt(s - 4 * pow2(cgs::proton_mass_c2)) / 2 / cgs::proton_mass_c2;
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
        gsl_integration_workspace *w = gsl_integration_workspace_alloc(LIMIT);
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

} /* namespace DiMauro2015 */
