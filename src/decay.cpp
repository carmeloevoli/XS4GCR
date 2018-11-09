#include "decay.h"

namespace DRAGON2 {

void DRAGON2_Decay_Chart::print() {
	std::cout << "Using DRAGON2 decay chart: REF" << std::endl;
}

DRAGON2_Decay_Chart::DRAGON2_Decay_Chart() {
	read_table("data/isotope_decays.txt");
}

void DRAGON2_Decay_Chart::add_unstable_isotope(std::string line) {
	std::istringstream ss(line);
	int A_, Z_;
	double tau_, tau_naked_;
	std::string mode_;
	ss >> A_ >> Z_ >> tau_ >> tau_naked_ >> mode_;
	decay_mode mode;
	if (mode_ == "B-")
		mode = BETA_MINUS;
	else if (mode_ == "B+")
		mode = BETA_PLUS;
	else if (mode_ == "ECB+")
		mode = ECMIXED_PLUS;
	else if (mode_ == "ECB-")
		mode = ECMIXED_MINUS;
	else if (mode_ == "EC")
		mode = EC;
	else {
		std::cerr << "Error: mode " << mode_ << "not found!";
		exit(1);
	}
	auto pid = PID(Z_, A_);
	decay_params params { tau_, tau_naked_, mode };
	auto ret = chart.insert(std::make_pair(pid, params));
	if (ret.second == false) {
		std::cout << "Warning: element " << pid << " already existed!\n";
	}
}

void DRAGON2_Decay_Chart::read_table(std::string filename) {
	std::string line;
	if (file_exist(filename)) {
		std::ifstream in(filename);
		while (std::getline(in, line))
			if (line.length() > 0 && line[0] != '#') {
				add_unstable_isotope(line);
			}
	}
}

std::shared_ptr<Decay_Chart> DRAGON2_Decay_Chart::clone() {
	return std::make_shared<DRAGON2_Decay_Chart>(*this);
}

double DRAGON2_Decay_Chart::get_halftime(PID particle) {
	auto it = chart.find(particle);
	if (it != chart.end()) {
		return it->second.tau_half_naked;
	} else {
		return -1;
	}
}

std::string DRAGON2_Decay_Chart::get_mode(PID particle) {
	auto it = chart.find(particle);
	if (it != chart.end()) {
		return str_mode(it->second.mode);
	} else {
		return str_mode(STABLE);
	}
}

} // namespace DRAGON2
