#ifndef INCLUDE_DUPERRAY03_H_
#define INCLUDE_DUPERRAY03_H_

#include <cassert>
#include <iostream>
#include "gsl/gsl_integration.h"
#include "mks.h"
#include "utilities.h"

namespace Duperray03 {

double dsigma_dT(double T_p, double T_ap);

double sigma_invariant(const double& sqrt_s, const double& X_r, const double& p_T);

} /* namespace Duperray03 */

#endif /* INCLUDE_DUPERRAY03_H_ */
