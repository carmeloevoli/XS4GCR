#ifndef INCLUDE_WEBBER2003_TABLE_H_
#define INCLUDE_WEBBER2003_TABLE_H_

#include <algorithm>
#include <cassert>
#include <iterator>
#include <map>
#include <string>
#include <vector>

#include "pid.h"
#include "mks.h"
#include "utilities.h"

namespace DRAGON2 {

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
    double Tn_min = 0.01 * GeV;
    double Tn_max = 10 * GeV;
};

} // namespace DRAGON2

#endif /* INCLUDE_WEBBER2003_TABLE_H_ */
