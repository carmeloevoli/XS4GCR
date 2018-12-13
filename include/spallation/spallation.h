#ifndef INCLUDE_SPALLATION_H_
#define INCLUDE_SPALLATION_H_

#include <cassert>
#include <iostream>
#include <memory>
#include <vector>
#include <utility>

#include "pid.h"
#include "utilities.h"
//#include "Webber2003_table.h"

namespace DRAGON2 {

class Spallation {
public:
	virtual void print() = 0;
	virtual std::shared_ptr<Spallation> clone() = 0;
	virtual double get(const channel& ch, const TARGET& target, const double& T_n, bool do_ghosts = true) = 0;

	inline void set_model_name(const std::string& m) {
		model_name = m;
	}

	virtual ~Spallation() {
	}

protected:
	std::string model_name;
};

class Webber1993_Spallation: public Spallation {
public:
	Webber1993_Spallation();
	void init();
	void print() override;
	std::shared_ptr<Spallation> clone() override;
	double get(const channel& ch, const TARGET& target, const double& T_n, bool do_ghosts = true) override;

protected:
	double direct(const channel& ch, const double& T_n);
};

} // namespace DRAGON2

#endif /* INCLUDE_SPALLATION_H_ */
