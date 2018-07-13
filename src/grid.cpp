#include "grid.h"

namespace DRAGON2 {

double grid::getlog(const size_t& ix) const {
	double value = sigma[ix];
	return (value > 0) ? log(value) : -100.0;
}

double grid::get_interpolated(const double& x_) const {
	if (x_ < x.get_min() || x_ > x.get_max()) {
		return 0;
	} else {
		size_t i = x.get_idx(x_);
		Linear_Interpol<double> L(log(x.at(i)), log(x.at(i + 1)), getlog(i), getlog(i + 1));
		return L.get(x_);
	}
}

double grid2d::getlog(const size_t& ix, const size_t& iy) const {
	double value = sigma[ix * y.get_size() + iy];
	return (value > 0) ? log(value) : -100.0;
}

double grid2d::get_interpolated(const double& x_, const double& y_) const {
	if (x_ < x.get_min() || x_ > x.get_max())
		return 0;
	else if (y_ < y.get_min() || y_ > y.get_max())
		return 0;
	else {
		size_t i = x.get_idx(x_);
		size_t j = y.get_idx(y_);
		BiLinear_Interpol<double> B;
		B.set_xy(log(x.at(i)), log(x.at(i + 1)), log(y.at(j)), log(y.at(j + 1)));
		B.set_q(getlog(i, j), getlog(i + 1, j), getlog(i, j + 1), getlog(i + 1, j + 1));
		return exp(B.get(log(x_), log(y_)));
	}
}

} // namespace DRAGON2
