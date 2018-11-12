#ifndef INCLUDE_UTILITIES_H_
#define INCLUDE_UTILITIES_H_

#include <cmath>
#include <fstream>
#include <string>

#include "mks.h"

namespace DRAGON2 {

template<class T>
const T& max(const T& a, const T& b) {
	return (a < b) ? b : a;
}

template<class T>
const T& min(const T& a, const T& b) {
	return (a < b) ? a : b;
}

template<typename T>
class LinearInterpol {
public:
	LinearInterpol(T xa_, T xb_, T ya_, T yb_) :
			xa(xa_), xb(xb_), ya(ya_), yb(yb_) {
	}
	virtual ~LinearInterpol() {
	}
	T get(const T& x) {
		return (ya + (yb - ya) * (x - xa) / (xb - xa));

	}
	T getLog(const T& x) {
		T value = (ya + (yb - ya) * std::log(x / xa) / std::log(xb / xa));
		return std::exp(value);
	}
protected:
	T xa;
	T xb;
	T ya;
	T yb;
};

template<typename T>
class BiLinear_Interpol {
public:
	BiLinear_Interpol() {
	}
	void set_xy(const T& x1_, const T& x2_, const T& y1_, const T& y2_) {
		x1 = x1_;
		x2 = x2_;
		y1 = y1_;
		y2 = y2_;
	}
	void set_q(const T& q11_, const T& q21_, const T& q12_, const T& q22_) {
		q11 = q11_;
		q21 = q21_;
		q12 = q12_;
		q22 = q22_;
	}
	virtual ~BiLinear_Interpol() {
	}
	T get(const T&x, const T&y) const {
		T x2x1, y2y1, x2x, y2y, yy1, xx1;
		x2x1 = x2 - x1;
		y2y1 = y2 - y1;
		x2x = x2 - x;
		y2y = y2 - y;
		yy1 = y - y1;
		xx1 = x - x1;
		T q = q11 * x2x * y2y + q21 * xx1 * y2y + q12 * x2x * yy1 + q22 * xx1 * yy1;
		return 1.0 / (x2x1 * y2y1) * q;
	}
protected:
	T x1 = 0, x2 = 0;
	T y1 = 0, y2 = 0;
	T q11 = 0, q21 = 0, q12 = 0, q22 = 0;
};

bool file_exist(const std::string& filename);

size_t count_file_lines(const std::string& filename);

extern "C" double sighad_(int*, double*, double*, double*, double*, double*);
double sighad_cc(int IS, double PA, double PZ, double TA, double TZ, double T);

extern "C" void sigtap2_(int*);
void sigtap_cc(int);

extern "C" void set_sigma_(int*);
void set_sigma_cc();

extern "C" double wsigma_(int*, int*, int*, int*, double*);
double wsigma_cc(int IZ, int IA, int JZ, int JA, double T_n);

extern "C" void yieldx_(int*, int*, int*, int*, float*, float*);
double yieldx_cc(int IZ, int IA, int JZ, int JA, double T_n);

double Ferrando1998_He2H(const double& T_n, const int& Z_I, const int& Z_F);

} // namespace DRAGON2

#endif /* INCLUDE_UTILITIES_H_ */
