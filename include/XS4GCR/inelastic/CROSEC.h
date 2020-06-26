// Copyright (c) 2017 Carmelo Evoli - MIT License
#ifndef INCLUDE_XS4GCR_INELASTIC_CROSEC_H_
#define INCLUDE_XS4GCR_INELASTIC_CROSEC_H_

#include <memory>
#include <string>

#include "XS4GCR/inelastic/inelastic.h"
#include "XS4GCR/pid.h"

namespace XS4GCR {

class CROSEC_Total_Inelastic : public Total_Inelastic {
   public:
    CROSEC_Total_Inelastic();

    void print() const override;

    std::shared_ptr<Total_Inelastic> clone() override;

    double get(const PID &projectile, const TARGET &target, const double &T_n) const override;

   protected:
    void init();

    double set_energy_within_range(const double &T_n) const;

    const std::string data_filename = "data/barpol.txt";
    const int IS = 2;  // calculation of non-elastic cross-sections
    double PA = 1;
    double PZ = 1;  // projectile mass and charge numbers (for pions PA<0.2)
    double T_n_min = 20. * MKS::MeV;
    double T_n_max = MKS::TeV;
};

}  // namespace XS4GCR

#endif  // INCLUDE_XS4GCR_INELASTIC_CROSEC_H_
