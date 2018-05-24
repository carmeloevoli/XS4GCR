#include "antiproton_tables.h"

antiproton_tables::antiproton_tables(std::pair<size_t, size_t> sizes, const std::string& filename) :
		T_proj_size(sizes.first), T_ap_size(sizes.second), datafile(filename) {
	read_data_file(filename, GeV, mbarn / GeV);
}

antiproton_tables::antiproton_tables(std::pair<size_t, size_t> sizes) :
		T_proj_size(sizes.first), T_ap_size(sizes.second) {
}

antiproton_tables::~antiproton_tables() {
	T_proj.clear();
	T_ap.clear();
	table.clear();
}

double antiproton_tables::dsigma_dT(const double& T_proj_, const double& T_ap_, bool proj_is_H,
		bool target_is_H) const {
	if (T_proj_ < T_proj.front() || T_proj_ > T_proj.back())
		return 0;
	if (T_ap_ < T_ap.front() || T_ap_ > T_ap.back())
		return 0;

	size_t i = std::upper_bound(T_proj.begin(), T_proj.end(), T_proj_) - T_proj.begin() - 1;
	auto T_proj_unit = (T_proj_ - T_proj.at(i)) / (T_proj.at(i + 1) - T_proj.at(i));

	size_t j = std::upper_bound(T_ap.begin(), T_ap.end(), T_ap_) - T_ap.begin() - 1;
	auto T_ap_unit = (T_ap_ - T_ap.at(j)) / (T_ap.at(j + 1) - T_ap.at(j));

	size_t k = get_channel_index(proj_is_H, target_is_H);

	double target[2] = { T_proj_unit, T_ap_unit };
	double v_0[4] = { get_grid(i, j, k), get_grid(i, j + 1, k), get_grid(i + 1, j + 1, k), get_grid(i + 1, j, k) };

	return Interpolator<double>::Bilinear(target, v_0);
}

void antiproton_tables::read_data_file(const std::string& filename, const double& energy_units, const double& units) {
	assert(count_file_lines(filename) == T_proj_size * T_ap_size + 1);
	std::ifstream infile(filename, std::ios::in);
	assert(infile.is_open());
	infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	double x[6];
	size_t i = 0;
	while (infile >> x[0] >> x[1] >> x[2] >> x[3] >> x[4] >> x[5]) {
		sigmas s = { x[2] * units, x[3] * units, x[4] * units, x[5] * units };
		table.push_back(s);
		if (i % T_ap_size == 0)
			T_proj.push_back(x[0] * energy_units);
		if (i < T_ap_size)
			T_ap.push_back(x[1] * energy_units);
		++i;
	}
	infile.close();
}

size_t antiproton_tables::get_channel_index(bool proj_is_H, bool target_is_H) const {
	if (proj_is_H)
		return (target_is_H) ? 0 : 1;
	else
		return (target_is_H) ? 2 : 3;
}

double antiproton_tables::get_grid(const size_t& i, const size_t& j, const size_t& k) const {
	auto s = table.at(j + i * T_ap_size);
	return s.at(k);
}
