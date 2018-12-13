#ifndef INCLUDE_EVOLI2018_TABLE_H_
#define INCLUDE_EVOLI2018_TABLE_H_

#include <algorithm>
#include <cassert>
#include <map>
#include <string>
#include <vector>

#include "pid.h"
#include "mks.h"
#include "utilities.h"

namespace DRAGON2 {

class SigmaFunction {
public:
	explicit SigmaFunction(double E_th, double sigma_0, double Gamma, double M, double sigma_1,
			double xi, double Delta);
	virtual ~SigmaFunction();

	double get(const double& T) const;

protected:
	double sigma_le(const double& T) const;
	double sigma_he(const double& T) const;
	double E_th;
	double sigma_0;
	double Gamma;
	double M;
	double sigma_1;
	double xi;
	double Delta;
};

class Evoli2018_table {
public:
	Evoli2018_table();
	Evoli2018_table(const std::string& filename);
	double get(const channel& ch, const double& T_n) const;
	virtual ~Evoli2018_table();

private:
	void read_data_file();

	bool is_present(channel ch) const {
		return !(functions.find(ch) == functions.end());
	}

protected:
	double T_h = 2. * GeV;
	std::string data_filename;
	std::map<channel, SigmaFunction> functions;
};

} // namespace DRAGON2

#endif /* INCLUDE_EVOLI2018_TABLE_H_ */
