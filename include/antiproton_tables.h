#ifndef INCLUDE_MODELS_ANTIPROTON_TABLES_H_
#define INCLUDE_MODELS_ANTIPROTON_TABLES_H_

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <limits>
#include <string>
#include <vector>

#include "interpolator.h"
#include "mks.h"
#include "utilities.h"

class antiproton_tables {
public:
	antiproton_tables(std::pair<size_t, size_t> sizes, const std::string& filename);
	antiproton_tables(std::pair<size_t, size_t> sizes);
	virtual ~antiproton_tables();
	double dsigma_dT(const double& T_proj_, const double& T_ap_, bool proj_is_H, bool target_is_H) const;
	void read_data_file(const std::string& filename, const double& energy_units, const double& units);

protected:
	using sigmas = std::vector<double>;
	size_t T_proj_size;
	size_t T_ap_size;
	std::string datafile;
	std::vector<double> T_proj;
	std::vector<double> T_ap;
	std::vector<sigmas> table;

	size_t get_channel_index(bool proj_is_H, bool target_is_H) const;
	double get_grid(const size_t& i, const size_t& j, const size_t& k) const;
};

/*double E_proj_min = 5.495408738576246 * GeV;
 double E_proj_max = 954992.5860214368 * GeV;
 size_t E_proj_size = 132;
 double T_ap_min = 0.01 * GeV;
 double T_ap_max = 1e3 * GeV;
 size_t T_ap_size = 251;
 grid2d dsigma_dT_pp;
 grid2d dsigma_dT_pHe;
 grid2d dsigma_dT_Hep;
 grid2d dsigma_dT_He2;*/

/*void ap_tables::init_grids() {
 dsigma_dT_pp.set_size(T_ap_size, E_proj_size);
 dsigma_dT_pp.set_x_range(T_ap_min, T_ap_max);
 dsigma_dT_pp.set_y_range(E_proj_min, E_proj_max);
 assert(file_exist(ap_datafile));
 std::vector<sigmas> ap_sigmas = read_data_file(ap_datafile);
 for (size_t i = 0; i < E_proj_size; ++i)
 for (size_t j = 0; j < T_ap_size; ++j) {
 auto s = ap_sigmas.at(j + i * T_ap_size);
 dsigma_dT_pp.get(j, i) = std::get<0>(s) * mbarn / GeV;
 dsigma_dT_pHe.get(j, i) = std::get<1>(s) * mbarn / GeV;
 dsigma_dT_Hep.get(j, i) = std::get<2>(s) * mbarn / GeV;
 dsigma_dT_He2.get(j, i) = std::get<3>(s) * mbarn / GeV;
 }
 }*/

#endif /* INCLUDE_MODELS_ANTIPROTON_TABLES_H_ */
