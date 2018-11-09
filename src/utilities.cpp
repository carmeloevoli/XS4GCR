#include "utilities.h"

namespace DRAGON2 {

size_t count_file_lines(const std::string& filename) {
	size_t count = 0;
	std::string line;
	std::ifstream file(filename.c_str());
	while (getline(file, line))
		count++;
	return count;
}

bool file_exist(const std::string& filename) {
	std::ifstream f(filename.c_str());
	return f.good();
}

double sighad_cc(int IS, double PA, double PZ, double TA, double TZ, double T) {
	return (sighad_(&IS, &PA, &PZ, &TA, &TZ, &T));
}

void sigtap_cc(int ISS) {
	sigtap2_(&ISS);
}

void set_sigma_cc() {
	int cdr = 99;
	set_sigma_(&cdr);
}

double wsigma_cc(int IZ, int IA, int JZ, int JA, double T_n) {
	double T_n_MeV = T_n / MeV;
	double cs_mb = wsigma_(&IZ, &IA, &JZ, &JA, &T_n_MeV);
	return cs_mb * mbarn;
}

double yieldx_cc(int IZ, int IA, int JZ, int JA, double T_n) {
	float cs_mb;
	float T_n_MeV = (float) T_n / MeV;
	yieldx_(&IZ, &IA, &JZ, &JA, &T_n_MeV, &cs_mb);
	return (double) cs_mb * mbarn;
}

double Ferrando1998_He2H(const double& T_n, const int& Z_I, const int& Z_F) {
        double T_GeV = (T_n / GeV < 1.51) ? T_n / GeV : 1.51;
        double Z = (Z_I < 26) ? Z_I : 26;
        double mu_E = 0.1601136 - 0.21994302 * T_GeV + 0.08903134 * T_GeV * T_GeV;
        double delta_E = 0.40183405 + 5.60541311 * T_GeV - 1.95868946 * T_GeV * T_GeV;
        double fZI_Z = -2.90627699 + 1.19911266 * std::log(Z);
        return std::exp(mu_E * std::pow(fabs(Z_I - Z_F - fZI_Z * delta_E), 1.43));
}

} // namespace DRAGON2
