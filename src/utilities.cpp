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

} // namespace DRAGON2
