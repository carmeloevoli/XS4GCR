#ifndef INCLUDE_GRID_H_
#define INCLUDE_GRID_H_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "axis.h"
#include "mks.h"
#include "pid.h"
#include "utilities.h"

class grid {
public:
	grid() {
	}
	virtual ~grid() {
		sigma.clear();
	}
	size_t get_size() const {
		return x.get_size();
	}
	double get_x(size_t ix) const {
		return x.get_min() * pow(x.get_ratio(), (double) ix);
	}
	double &get(size_t ix) {
		return sigma[ix];
	}
	const double &get(size_t ix) const {
		return sigma[ix];
	}
	double get_value(size_t ix) {
		return sigma[ix];
	}
	void set_size(const size_t& x_size_) {
		x.set_size(x_size_);
		sigma.resize(x_size_);
	}
	void set_x_range(const double& min_, const double& max_) {
		x.set_range(min_, max_);
	}
	double getlog(const size_t& ix) const;
	double get_interpolated(const double& x_) const;

protected:
	std::vector<double> sigma;
	log_axis<double> x;
};

class grid2d {
public:
	grid2d() {
	}
	virtual ~grid2d() {
		sigma.clear();
	}
	size_t get_size() const {
		return x.get_size() * y.get_size();
	}
	double get_x(size_t ix) const {
		return x.get_min() * pow(x.get_ratio(), (double) ix);
	}
	double get_y(size_t iy) const {
		return y.get_min() * pow(y.get_ratio(), (double) iy);
	}
	double &get(size_t ix, size_t iy) {
		return sigma[ix * y.get_size() + iy];
	}
	const double &get(size_t ix, size_t iy) const {
		return sigma[ix * y.get_size() + iy];
	}
	double get_value(size_t ix, size_t iy) {
		return sigma[ix * y.get_size() + iy];
	}
	void set_x_range(const double& min_, const double& max_) {
		x.set_range(min_, max_);
	}
	void set_y_range(const double& min_, const double& max_) {
		y.set_range(min_, max_);
	}
	void set_size(const size_t& x_size_, const size_t& y_size_) {
		x.set_size(x_size_);
		y.set_size(y_size_);
		sigma.resize(x_size_ * y_size_);
	}
	double getlog(const size_t& i, const size_t& j) const;
	double get_interpolated(const double& x_, const double& y_) const;

protected:
	std::vector<double> sigma;
	log_axis<double> x;
	log_axis<double> y;
};

#endif /* INCLUDE_GRID_H_ */
