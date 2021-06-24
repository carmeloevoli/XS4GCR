// Copyright (c) 2017 Carmelo Evoli - MIT License
#ifndef INCLUDE_XS4GCR_SPALLATION_FITTING_FUNCTIONS_H_
#define INCLUDE_XS4GCR_SPALLATION_FITTING_FUNCTIONS_H_

#include <algorithm>
#include <cassert>
#include <map>
#include <string>
#include <vector>

#include "XS4GCR/cgs.h"
#include "XS4GCR/pid.h"
#include "XS4GCR/utilities.h"

namespace XS4GCR {

class SigmaFunction {
   public:
    explicit SigmaFunction(double E_th, double sigma_0, double Gamma, double M, double sigma_1,
                           double xi, double Delta);
    virtual ~SigmaFunction();

    double get(const double& T) const;

   protected:
    double sigma_le(const double& T) const;
    double sigma_he(const double& T) const;
    double E_th;
    double sigma_0;
    double Gamma;
    double M;
    double sigma_1;
    double xi;
    double Delta;
};

class FittingFunctions {
   public:
    FittingFunctions();
    explicit FittingFunctions(const std::string& filename);
    double get(const channel& ch, const double& T_n) const;
    virtual ~FittingFunctions();

    bool is_present(channel ch) const { return !(functions.find(ch) == functions.end()); }

   private:
    void read_data_file();

   protected:
    double T_h = 2. * cgs::GeV;
    std::string data_filename;
    std::map<channel, SigmaFunction> functions;
};

}  // namespace XS4GCR

#endif  // INCLUDE_XS4GCR_SPALLATION_FITTING_FUNCTIONS_H_
