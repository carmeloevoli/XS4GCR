#include "d2xsec.h"
#include "lis.h"

void get_fragmentation_timescale(std::string filename) {
    D2XSEC xsec;
    xsec.set_proton_xsecs("DRAGON2");
    auto x_pr = xsec.create_proton_xsecs();
    TARGET H_ISM(1), He_ISM(2);
    double n_gas = 1. / cm3;
    std::ofstream outfile(filename);
    outfile << std::scientific;
    for (double T = 0.1 * GeV; T < 1e4 * GeV; T *= 1.1) {
        double v = c_light * sqrt(1 - pow2(proton_mass_c2) / pow2(T + proton_mass_c2));
        double sigma_total = x_pr->get_inelastic(H_ISM, T) + f_He * x_pr->get_inelastic(He_ISM, T);
        double t_f = 1. / (v * n_gas * sigma_total);
        double t_f_H = 1. / (v * n_gas * x_pr->get_inelastic(H_ISM, T));
        outfile << T / GeV << " " << t_f / Myr  << " " << t_f_H / Myr << "\n";
    }
    outfile.close();
}

void get_secondary_production(std::string filename) {
    D2XSEC xsec;
    xsec.set_proton_xsecs("DRAGON2");
    auto x_pr = xsec.create_proton_xsecs();
    TARGET H_ISM(1), He_ISM(2);
    Ghelfi2016::H_LIS H_lis;
    std::ofstream outfile(filename);
    outfile << std::scientific;
    double q_p = 0;
    for (double T_sec = 0.1 * GeV; T_sec < 1e4 * GeV; T_sec *= 1.1) {
        for (double T_proj = T_sec; T_proj < 100 * TeV; T_proj *= 1.01) {
            double sigma_H = x_pr->get_inelastic(H_ISM, T_proj) / T_proj;
            sigma_H += f_He * x_pr->get_inelastic(He_ISM, T_proj) / T_proj;
            q_p += T_proj * H_lis.get(T_proj) * sigma_H;
        }
        q_p *= 4 * M_PI * log(1.01);
        outfile << T_sec / GeV << " " << q_p * (GeV * sec)  << "\n";
    }
    outfile.close();
}

int main() {
    get_fragmentation_timescale("output/xsec_frag_protons.txt");
    get_secondary_production("output/xsec_secondary_protons.txt");
    return 0;
}