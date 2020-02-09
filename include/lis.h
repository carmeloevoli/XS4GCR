#ifndef INCLUDE_LIS_H_
#define INCLUDE_LIS_H_

namespace Ghelfi2016 {

class LIS {
public:
	virtual ~LIS() {
	}
	virtual void init() = 0;
	double get(const double& T_n) const {
		double log_J_LIS = 0;
		if (T_n < T_threshold) {
			for (size_t i = 0; i < c.size(); i++) {
				double log_T_i = pow(log10(T_n / MKS::GeV) / log10(T_threshold / MKS::GeV), (double) i);
				log_J_LIS += c.at(i) * log_T_i;
			}
		} else {
			double log_T = log10(T_n / T_threshold);
			log_J_LIS = c_tilde.at(0) - c_tilde.at(1) * log_T;
		}
		return pow(10., log_J_LIS) / (MKS::GeV * MKS::mt2 * MKS::sec * MKS::sr);
	}
protected:
	std::vector<double> c;
	std::vector<double> c_tilde;
	double T_threshold = 0;
};

class H_LIS: public LIS {
public:
	H_LIS() {
		init();
	}
	void init() {
		c = {+3.606565e+00, -5.082805e+00, -3.042630e+00, -2.501190e+00, +1.827880e+00,
			+1.398976e+00, -7.028454e-01, +1.997827e+01, +2.885280e+00, -7.560171e+01,
			+3.405332e+00, +1.168359e+02, -3.274338e+01, -6.947553e+01, +3.535965e+01};
		c_tilde = {-3.850699e+00, +2.703917e+00};
		T_threshold = 800. * MKS::GeV;
	}
};

class He_LIS: public LIS {
public:
	He_LIS() {
		init();
	}
	void init() {
		c = {+2.376233e+00, -5.306384e+00, -3.119940e+00, -2.281441e+00, +4.055121e+00,
			+7.473942e+00, -8.053260e+00, -1.916564e+01, +1.766888e+01, +3.293412e+01,
			-2.955671e+01, -3.064750e+01, +2.792617e+01, +1.090915e+01, -1.019233e+01};
		c_tilde = {-4.978057e+00, +2.713877e+00};
		T_threshold = 800. * MKS::GeV;
	}
};

}
/* namespace Ghelfi2016 */

#endif /* INCLUDE_LIS_H_ */
