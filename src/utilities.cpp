// Copyright (c) 2017 Carmelo Evoli - MIT License
#include "XS4GCR/utilities.h"

#include <fstream>
#include <string>

namespace XS4GCR {

size_t count_file_lines(const std::string& filename) {
    size_t count = 0;
    std::string line;
    std::ifstream file(filename.c_str());
    while (getline(file, line)) count++;
    return count;
}

bool file_exist(const std::string& filename) {
    std::ifstream f(filename.c_str());
    return f.good();
}

int str_to_Z(const std::string& Z_str) {
    if (Z_str == "H")
        return 1;
    else if (Z_str == "He")
        return 2;
    else if (Z_str == "Li")
        return 3;
    else if (Z_str == "Be")
        return 4;
    else if (Z_str == "B")
        return 5;
    else if (Z_str == "C")
        return 6;
    else if (Z_str == "N")
        return 7;
    else if (Z_str == "O")
        return 8;
    else if (Z_str == "F")
        return 9;
    else if (Z_str == "Ne")
        return 10;
    else if (Z_str == "Na")
        return 11;
    else if (Z_str == "Mg")
        return 12;
    else if (Z_str == "Al")
        return 13;
    else if (Z_str == "Si")
        return 14;
    else if (Z_str == "P")
        return 15;
    else if (Z_str == "S")
        return 16;
    else if (Z_str == "Cl")
        return 17;
    else if (Z_str == "Ar")
        return 18;
    else if (Z_str == "K")
        return 19;
    else if (Z_str == "Ca")
        return 20;
    else if (Z_str == "Sc")
        return 21;
    else if (Z_str == "Ti")
        return 22;
    else if (Z_str == "V")
        return 23;
    else if (Z_str == "Cr")
        return 24;
    else if (Z_str == "Mn")
        return 25;
    else if (Z_str == "Fe")
        return 26;
    else if (Z_str == "Co")
        return 27;
    else if (Z_str == "Ni")
        return 28;
    else if (Z_str == "Cu")
        return 29;
    else if (Z_str == "Zn")
        return 30;
    else {
        assert(Z_str == "H");
        return -1;
    }
}

double sighad_cc(int IS, double PA, double PZ, double TA, double TZ, double T) {
    return (sighad_(&IS, &PA, &PZ, &TA, &TZ, &T));
}

void sigtap_cc(int ISS) { sigtap2_(&ISS); }

void set_sigma_cc() {
    int cdr = 99;
    set_sigma_(&cdr);
}

double wsigma_cc(int IZ, int IA, int JZ, int JA, double T_n) {
    double T_n_MeV = T_n / MKS::MeV;
    double cs_mb = wsigma_(&IZ, &IA, &JZ, &JA, &T_n_MeV);
    return cs_mb * MKS::mbarn;
}

double yieldx_cc(int IZ, int IA, int JZ, int JA, double T_n) {
    float cs_mb;
    float T_n_MeV = static_cast<float>(T_n) / MKS::MeV;
    yieldx_(&IZ, &IA, &JZ, &JA, &T_n_MeV, &cs_mb);
    return cs_mb * MKS::mbarn;
}

double Ferrando1998_He2H(const double& T_n, const int& Z_I, const int& Z_F) {
    double T_GeV = (T_n / MKS::GeV < 1.51) ? T_n / MKS::GeV : 1.51;
    double Z = (Z_I < 26) ? Z_I : 26;
    double mu_E = 0.1601136 - 0.21994302 * T_GeV + 0.08903134 * T_GeV * T_GeV;
    double delta_E = 0.40183405 + 5.60541311 * T_GeV - 1.95868946 * T_GeV * T_GeV;
    double fZI_Z = -2.90627699 + 1.19911266 * std::log(Z);
    return std::exp(mu_E * std::pow(fabs(Z_I - Z_F - fZI_Z * delta_E), 1.43));
}

}  // namespace XS4GCR
