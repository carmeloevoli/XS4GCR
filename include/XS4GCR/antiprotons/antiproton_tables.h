// Copyright (c) 2017 Carmelo Evoli - MIT License
#ifndef INCLUDE_XS4GCR_ANTIPROTONS_ANTIPROTON_TABLES_H_
#define INCLUDE_XS4GCR_ANTIPROTONS_ANTIPROTON_TABLES_H_

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <limits>
#include <string>
#include <utility>
#include <vector>

#include "XS4GCR/interpolator.h"
#include "XS4GCR/utilities.h"

namespace XS4GCR {

class antiproton_tables {
   public:
    antiproton_tables(std::pair<size_t, size_t> sizes, const std::string &filename);

    explicit antiproton_tables(std::pair<size_t, size_t> sizes);

    virtual ~antiproton_tables();

    double dsigma_dT(const double &T_proj_, const double &T_ap_, bool proj_is_H,
                     bool target_is_H) const;

    void read_data_file(const std::string &filename, const double &energy_units,
                        const double &units);

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

}  // namespace XS4GCR

#endif  // INCLUDE_XS4GCR_ANTIPROTONS_ANTIPROTON_TABLES_H_
