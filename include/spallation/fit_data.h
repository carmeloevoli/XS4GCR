#ifndef INCLUDE_SPALLATION_FIT_DATA_H_
#define INCLUDE_SPALLATION_FIT_DATA_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "pid.h"
#include "mks.h"

namespace DRAGON2 {

class FitData {
public:
	FitData() {
	}

	FitData(const std::string& fname) : filename(fname) {
		read_data();
		std::cout << channel_exists(std::make_pair(O16, C12)) << "\n";
		auto d = get_data(std::make_pair(O16, C12));
		for (auto& d_ : d)
			std::cout << d_.T / GeV << " " << d_.sigma / mbarn << "\n";
		std::cout << channel_exists(std::make_pair(N14, He4)) << "\n";
	}

	virtual ~FitData() {
	}

	struct data_struct {
		channel ch;
		double T;
		double sigma;
		double sigma_err;
	};

	void read_data() {
		int Z_i, A_i, Z_f, A_f;
		double T, s, serr;
		std::string label;
		std::ifstream datafile(filename.c_str());
		while (datafile >> Z_i >> A_i >> Z_f >> A_f >> T >> s >> serr >> label) {
			auto ch = std::make_pair(PID(Z_i, A_i), PID(Z_f, A_f));
			data_struct data { ch, T * GeV, s * mbarn, serr * mbarn };
			Data.push_back(data);
		}
		datafile.close();
		std::cout << " - read " << Data.size() << " data points\n";
	}

	bool channel_exists(const channel& ch) {
		size_t counter = 0;
		for (auto& data : Data)
			if (data.ch == ch)
				counter++;
		return counter > 0;
	}

	std::vector<data_struct> get_data(const channel& ch) {
		std::vector<data_struct> v;
		for (auto data : Data)
			if (data.ch == ch)
				v.push_back(data);
		assert(v.size() > 0);
		return v;
	}

protected:
	std::string filename;
	std::vector<data_struct> Data;
};

} // namespace DRAGON2

#endif /* INCLUDE_SPALLATION_FIT_DATA_H_ */
