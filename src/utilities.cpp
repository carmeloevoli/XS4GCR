// Copyright (c) 2017 Carmelo Evoli - MIT License
#include "XS4GCR/utilities.h"

#include <fstream>
#include <iostream>
#include <string>

#include "XS4GCR/cgs.h"

namespace Utils {

double ISimpsonsLog(std::vector<double> x, std::vector<double> f) {
    const double size = f.size();
    const double h = std::log(x[1] / x[0]);
    double I = x.front() * f.front() + x.back() * f.back();
    for (size_t i = 1; i < size - 1; i++) {
        if (i % 2 == 0)
            I += 2. * x.at(i) * f.at(i);
        else
            I += 4. * x.at(i) * f.at(i);
    }
    I *= h / 3.;
    return I;
}

std::vector<double> LinAxis(const double& min, const double& max, const size_t& size) {
    if (!(min < max)) throw std::invalid_argument("min must be smaller than max");
    if (!(size > 1)) throw std::invalid_argument("size must be larger than 1");

    const double dx = (max - min) / (double)(size - 1);
    std::vector<double> v(size);
    for (size_t i = 0; i < size; ++i) {
        const auto value = min + dx * i;
        v[i] = value;
    }
    return v;
}

std::vector<double> LogAxis(const double& min, const double& max, const size_t& size) {
    if (!(min < max)) throw std::invalid_argument("min must be smaller than max");
    if (!(size > 1)) throw std::invalid_argument("size must be larger than 1");

    const double delta_log = std::exp(std::log(max / min) / (size - 1));
    std::vector<double> v(size);
    for (size_t i = 0; i < size; ++i) {
        const auto value = std::exp(std::log(min) + (double)i * std::log(delta_log));
        v[i] = value;
    }
    return v;
}

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
    if (Z_str == "H") {
        return 1;
    } else if (Z_str == "He") {
        return 2;
    } else if (Z_str == "Li") {
        return 3;
    } else if (Z_str == "Be") {
        return 4;
    } else if (Z_str == "B") {
        return 5;
    } else if (Z_str == "C") {
        return 6;
    } else if (Z_str == "N") {
        return 7;
    } else if (Z_str == "O") {
        return 8;
    } else if (Z_str == "F") {
        return 9;
    } else if (Z_str == "Ne") {
        return 10;
    } else if (Z_str == "Na") {
        return 11;
    } else if (Z_str == "Mg") {
        return 12;
    } else if (Z_str == "Al") {
        return 13;
    } else if (Z_str == "Si") {
        return 14;
    } else if (Z_str == "P") {
        return 15;
    } else if (Z_str == "S") {
        return 16;
    } else if (Z_str == "Cl") {
        return 17;
    } else if (Z_str == "Ar") {
        return 18;
    } else if (Z_str == "K") {
        return 19;
    } else if (Z_str == "Ca") {
        return 20;
    } else if (Z_str == "Sc") {
        return 21;
    } else if (Z_str == "Ti") {
        return 22;
    } else if (Z_str == "V") {
        return 23;
    } else if (Z_str == "Cr") {
        return 24;
    } else if (Z_str == "Mn") {
        return 25;
    } else if (Z_str == "Fe") {
        return 26;
    } else if (Z_str == "Co") {
        return 27;
    } else if (Z_str == "Ni") {
        return 28;
    } else if (Z_str == "Cu") {
        return 29;
    } else if (Z_str == "Zn") {
        return 30;
    } else {
        assert(Z_str == "H");
        return -1;
    }
}

std::string Z_to_str(const int& Z) {
    if (Z == 1) {
        return "H";
    } else if (Z == 2) {
        return "He";
    } else if (Z == 3) {
        return "Li";
    } else if (Z == 4) {
        return "Be";
    } else if (Z == 5) {
        return "B";
    } else if (Z == 6) {
        return "C";
    } else if (Z == 7) {
        return "N";
    } else if (Z == 8) {
        return "O";
    } else if (Z == 9) {
        return "F";
    } else if (Z == 10) {
        return "Ne";
    } else if (Z == 11) {
        return "Na";
    } else if (Z == 12) {
        return "Mg";
    } else if (Z == 13) {
        return "Al";
    } else if (Z == 14) {
        return "Si";
    } else if (Z == 15) {
        return "P";
    } else if (Z == 16) {
        return "S";
    } else if (Z == 17) {
        return "Cl";
    } else if (Z == 18) {
        return "Ar";
    } else if (Z == 19) {
        return "K";
    } else if (Z == 20) {
        return "Ca";
    } else if (Z == 21) {
        return "Sc";
    } else if (Z == 22) {
        return "Ti";
    } else if (Z == 23) {
        return "V";
    } else if (Z == 24) {
        return "Cr";
    } else if (Z == 25) {
        return "Mn";
    } else if (Z == 26) {
        return "Fe";
    } else if (Z == 27) {
        return "Co";
    } else if (Z == 28) {
        return "Ni";
    } else if (Z == 29) {
        return "Cu";
    } else if (Z == 30) {
        return "Zn";
    } else {
        assert(Z == 1);
        return "none";
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
    double T_n_MeV = T_n / cgs::MeV;
    double cs_mb = wsigma_(&IZ, &IA, &JZ, &JA, &T_n_MeV);
    return cs_mb * cgs::mbarn;
}

double yieldx_cc(int IZ, int IA, int JZ, int JA, double T_n) {
    float cs_mb;
    float T_n_MeV = static_cast<float>(T_n) / cgs::MeV;
    yieldx_(&IZ, &IA, &JZ, &JA, &T_n_MeV, &cs_mb);
    return cs_mb * cgs::mbarn;
}

double Ferrando1998_He2H(const double& T_n, const int& Z_I, const int& Z_F) {
    double T_GeV = (T_n / cgs::GeV < 1.51) ? T_n / cgs::GeV : 1.51;
    double Z = (Z_I < 26) ? Z_I : 26;
    double mu_E = 0.1601136 - 0.21994302 * T_GeV + 0.08903134 * T_GeV * T_GeV;
    double delta_E = 0.40183405 + 5.60541311 * T_GeV - 1.95868946 * T_GeV * T_GeV;
    double fZI_Z = -2.90627699 + 1.19911266 * std::log(Z);
    return std::exp(mu_E * std::pow(fabs(Z_I - Z_F - fZI_Z * delta_E), 1.43));
}

}  // namespace Utils
