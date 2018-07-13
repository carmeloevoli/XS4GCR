#ifndef INCLUDE_PROTONS_H_
#define INCLUDE_PROTONS_H_

#include <cmath>
#include <iostream>
#include <map>
#include <memory>
#include <string>

#include "grid.h"
#include "mks.h"
#include "pid.h"
#include "Tripathi99.h"
#include "utilities.h"

class Proton_Xsecs {
public:
	virtual ~Proton_Xsecs() {
	}

	virtual void print() const = 0;

	virtual std::shared_ptr<Proton_Xsecs> clone() = 0;

	virtual double get_inelastic(const TARGET &target, const double &T_n) const = 0;

protected:
	std::string model_name;

	inline void set_model_name(const std::string &m) {
		model_name = m;
	}
};

class DRAGON2_Proton_Xsecs: public Proton_Xsecs {
public:
	DRAGON2_Proton_Xsecs();

	void print() const override;

	std::shared_ptr<Proton_Xsecs> clone() override;

	double get_inelastic(const TARGET &target, const double &T_n) const override;

private:
	double T_threshold = 0.2797 * GeV;
};

#endif /* INCLUDE_PROTONS_H_ */
