// Copyright (c) 2017 Carmelo Evoli - MIT License
#ifndef INCLUDE_XS4GCR_ANTIPROTONS_TANNG83_H_
#define INCLUDE_XS4GCR_ANTIPROTONS_TANNG83_H_

#include <cassert>
#include <iostream>

#include "XS4GCR/utilities.h"
#include "gsl/gsl_integration.h"

namespace TanNg83 {

double dsigma_dT(double T_p, double T_ap);

double sigma_invariant(const double& sqrt_s, const double& X_r, const double& p_T);

} /* namespace TanNg83 */

#endif  // INCLUDE_XS4GCR_ANTIPROTONS_TANNG83_H_
