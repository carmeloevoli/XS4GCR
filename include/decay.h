#ifndef INCLUDE_DECAY_H_
#define INCLUDE_DECAY_H_

#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <vector>

#include "pid.h"
#include "utilities.h"

namespace DRAGON2 {

class Decay_Chart {
public:
	enum decay_mode {
		STABLE, EC, BETA_MINUS, BETA_PLUS, ECMIXED_PLUS, ECMIXED_MINUS
	};

	std::string str_mode(decay_mode mode) {
		if (mode == EC)
			return "EC";
		else if (mode == BETA_MINUS)
			return "B-";
		else if (mode == BETA_PLUS)
			return "B+";
		else if (mode == ECMIXED_PLUS)
			return "ECB+";
		else if (mode == ECMIXED_MINUS)
			return "ECB-";
		else
			return "stable";
	}

	virtual ~Decay_Chart() {
	}

	virtual void print() = 0;
	virtual std::shared_ptr<Decay_Chart> clone() = 0;
	virtual double get_halftime(PID particle) = 0;
	virtual std::string get_mode(PID particle) = 0;
};

class DRAGON2_Decay_Chart: public Decay_Chart {
public:
	DRAGON2_Decay_Chart();
	void print() override;
	std::shared_ptr<Decay_Chart> clone() override;
	double get_halftime(PID particle) override;
	std::string get_mode(PID particle) override;

	struct decay_params {
		double tau_half;
		double tau_half_naked;
		decay_mode mode;
	};

protected:
	void add_unstable_isotope(std::string line);
	void read_table(std::string filename);

	std::string table_filename = "data/isotope_decays.txt";
	std::map<PID, decay_params> chart;
};

} // namespace DRAGON2

#endif
