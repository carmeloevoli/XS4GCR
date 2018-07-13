#ifndef INCLUDE_DECAY_H_
#define INCLUDE_DECAY_H_

#include <iostream>
#include <memory>

#include "pid.h"

class Decay_Chart {
public:
	enum decay_mode {
		STABLE, EC, BETA, ECMIXED
	};

	virtual ~Decay_Chart() {
	}

	virtual void print() = 0;

	virtual std::shared_ptr<Decay_Chart> clone() = 0;

	virtual double get_halftime(PID particle) = 0;

	virtual decay_mode get_mode(PID particle) = 0;
};

class DRAGON2_Decay_Chart: public Decay_Chart {
public:
	void print() override;

	std::shared_ptr<Decay_Chart> clone() override;

	double get_halftime(PID particle) override;

	decay_mode get_mode(PID particle) override;

private:
	PID Li6 = PID(3, 4);
};

#endif
