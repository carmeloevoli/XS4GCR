#include "Webber2003_table.h"

namespace DRAGON2 {

channel convert_id(const int& id_) {
	int id = id_;
	int A_i = id / 1000000;
	id -= A_i * 1000000;
	int Z_i = id / 10000;
	id -= Z_i * 10000;
	int A_f = id / 100;
	id -= A_f * 100;
	int Z_f = id;
	assert(id - Z_f == 0);
	return channel(PID(Z_i, A_i), PID(Z_f, A_f));
}

Webber2003_table::Webber2003_table() {
}

double Webber2003_table::get(const channel& ch, const double& T_n) {
	if (spallation_map.find(ch) == spallation_map.end()) {
		return -1;
	} else {
		assert(spallation_map.count(ch) == 1);
		return get_from_grid(ch, T_n);
	}
}

double Webber2003_table::get_from_grid(const channel& ch, const double& T_n) {
	if (T_n > T_n_grid.back()) {
		return spallation_map.at(ch).back();
	} else if (T_n >= T_n_grid.front()) {
		size_t i = std::upper_bound(T_n_grid.begin(), T_n_grid.end(), T_n) - T_n_grid.begin();
		LinearInterpol<double> L(T_n_grid.at(i - 1), T_n_grid.at(i), spallation_map.at(ch).at(i - 1),
				spallation_map.at(ch).at(i));
		return L.get(T_n);
	} else
		return -1;
}

void Webber2003_table::read_data_file() {
	std::ifstream data_file(data_filename.c_str());
	assert(data_file.is_open());
	std::string line;
	while (std::getline(data_file, line)) {
		std::istringstream is(line);
		std::vector<double> row((std::istream_iterator<double>(is)), std::istream_iterator<double>());
		int id = (int) row.at(0);
		if (id == 0) {
			std::copy(row.begin() + 1, row.end(), std::back_inserter(T_n_grid));
			for (auto& x : T_n_grid)
				x *= MKS::MeV;
		} else {
			channel ch = convert_id(id);
			if (ch.first.get_A() < 18) {
				std::vector<double> v;
				std::copy(row.begin() + 1, row.end(), std::back_inserter(v));
				for (auto& x : v)
					x *= MKS::mbarn;
				spallation_map[ch] = v;
			}
		}
	}
}

} // namespace DRAGON2

