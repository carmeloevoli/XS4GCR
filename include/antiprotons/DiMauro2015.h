#ifndef INCLUDE_DIMAURO15_H_
#define INCLUDE_DIMAURO15_H_

#include <cassert>
#include <cmath>
#include <iostream>
#include "gsl/gsl_integration.h"
#include "mks.h"
#include "utilities.h"

namespace DiMauro2015 {

double dsigma_dT(double T_p, double T_ap);

double sigma_invariant(const double &sqrt_s, const double &X_r, const double &p_T);

} /* namespace DiMauro2015 */

#endif /* INCLUDE_DIMAURO15_H_ */
