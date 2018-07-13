#ifndef D2XSECS_ANTIPROTON_TABLES_H_
#define D2XSECS_ANTIPROTON_TABLES_H_

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
	antiproton_tables(std::pair<size_t, size_t> sizes, const std::string &filename);

	antiproton_tables(std::pair<size_t, size_t> sizes);

	virtual ~antiproton_tables();

	double dsigma_dT(const double &T_proj_, const double &T_ap_, bool proj_is_H, bool target_is_H) const;

	void read_data_file(const std::string &filename, const double &energy_units, const double &units);

protected:
	using sigmas = std::vector<double>;
	size_t T_proj_size;
	size_t T_ap_size;
	std::string datafile;
	std::vector<double> T_proj;
	std::vector<double> T_ap;
	std::vector<sigmas> table;

	size_t get_channel_index(bool proj_is_H, bool target_is_H) const;

	double get_grid(const size_t &i, const size_t &j, const size_t &k) const;
};

#endif /* D2XSECS_ANTIPROTON_TABLES_H_ */
