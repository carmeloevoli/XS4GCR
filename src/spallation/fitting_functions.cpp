#include "fitting_functions.h"

namespace DRAGON2 {

SigmaFunction::SigmaFunction(double E_th, double sigma_0, double Gamma, double M, double sigma_1,
		double xi, double Delta) {
	this->E_th = E_th;
	this->sigma_0 = sigma_0;
	this->Gamma = Gamma;
	this->M = M;
	this->sigma_1 = sigma_1;
	this->xi = xi;
	this->Delta = Delta;
}

SigmaFunction::~SigmaFunction() {
}

double SigmaFunction::sigma_le(const double& T) const {
	double le = sigma_0 * pow2(Gamma) * pow2(T - E_th);
	le /= pow2(pow2(T) - pow2(M)) + pow2(Gamma * M);
	return le;
}

double SigmaFunction::sigma_he(const double& T) const {
	const double T_h = 2. * MKS::GeV;
	double he = sigma_1 * std::pow(1. - E_th / T, xi);
	he *= 1. + Delta / (1. + pow2(T_h / T));
	return he;
}

double SigmaFunction::get(const double& T) const {
	double value = 0;
	if (T > E_th) {
		value = sigma_he(T);
		if (sigma_0 > 0.)
			value += sigma_le(T);
	}
	return value;
}

FittingFunctions::FittingFunctions() {
	data_filename = "data/Evoli2019_fragmentation_fitparams.txt";
}

FittingFunctions::FittingFunctions(const std::string& filename) {
	data_filename = filename;
	read_data_file();
}

FittingFunctions::~FittingFunctions() {
}

void FittingFunctions::read_data_file() {
	std::ifstream infile(data_filename.c_str());
	infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	int Z_p, A_p, Z_c, A_c, counter = 0;
	double E_th, sigma_0, M, Gamma, sigma_1, xi, Delta, sigma_ratio;
	while (infile >> Z_p >> A_p >> Z_c >> A_c >> E_th >> sigma_0 >> M >> Gamma >> sigma_1 >> xi
			>> Delta >> sigma_ratio) {
		PID child(Z_c, A_c);
		PID parent(Z_p, A_p);
		SigmaFunction function { E_th * MKS::MeV, sigma_0 * MKS::mbarn, Gamma * MKS::MeV, M
				* MKS::MeV, sigma_1 * MKS::mbarn, xi, Delta };
		if (!is_present(channel(parent, child)))
			functions.insert(std::make_pair(channel(parent, child), function));
	}
	infile.close();
	std::cout << " - read fit parameters of " << functions.size() << " channels.\n";
}

double FittingFunctions::get(const channel& ch, const double& T_n) const {
	auto it = functions.find(ch);
	if (it != functions.end()) {
		return (it->second).get(T_n);
	} else {
		return -1;
	}
}

} // namespace DRAGON2
