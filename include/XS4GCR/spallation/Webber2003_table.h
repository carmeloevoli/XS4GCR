// Copyright (c) 2017 Carmelo Evoli - MIT License
#ifndef INCLUDE_XS4GCR_SPALLATION_WEBBER2003_TABLE_H_
#define INCLUDE_XS4GCR_SPALLATION_WEBBER2003_TABLE_H_

#include <algorithm>
#include <cassert>
#include <iterator>
#include <map>
#include <string>
#include <vector>

#include "XS4GCR/mks.h"
#include "XS4GCR/pid.h"
#include "XS4GCR/utilities.h"

namespace XS4GCR {

class Webber2003_table {
   public:
    Webber2003_table();
    double get(const channel& ch, const double& T_n);

   private:
    void read_data_file();
    double get_from_grid(const channel& ch, const double& T_n);

   protected:
    std::string data_filename = "data/xsec_spallation_Webber2003.txt";
    std::vector<double> T_n_grid;
    std::map<channel, std::vector<double> > spallation_map;
    size_t n_headers = 4;
    size_t n_reactions = 4657;
    size_t Tn_size = 41;
    double Tn_min = 0.01 * MKS::GeV;
    double Tn_max = 10 * MKS::GeV;
};

}  // namespace XS4GCR

#endif  // INCLUDE_XS4GCR_SPALLATION_WEBBER2003_TABLE_H_
