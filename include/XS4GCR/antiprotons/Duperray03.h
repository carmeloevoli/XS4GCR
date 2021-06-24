// Copyright (c) 2017 Carmelo Evoli - MIT License
#ifndef INCLUDE_XS4GCR_ANTIPROTONS_DUPERRAY03_H_
#define INCLUDE_XS4GCR_ANTIPROTONS_DUPERRAY03_H_

#include <cassert>
#include <cmath>
#include <iostream>

#include "XS4GCR/utilities.h"
#include "gsl/gsl_integration.h"

namespace Duperray03 {

double dsigma_dT(double T_p, double T_ap);

double sigma_invariant(const double& sqrt_s, const double& X_r, const double& p_T);

} /* namespace Duperray03 */

#endif  // INCLUDE_XS4GCR_ANTIPROTONS_DUPERRAY03_H_
