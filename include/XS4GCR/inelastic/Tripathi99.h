// Copyright (c) 2017 Carmelo Evoli - MIT License
#ifndef INCLUDE_XS4GCR_INELASTIC_TRIPATHI99_H_
#define INCLUDE_XS4GCR_INELASTIC_TRIPATHI99_H_

#include <memory>

#include "XS4GCR/inelastic/inelastic.h"

namespace Tripathi99 {

double inelastic_sigma(int A_p, int Z_p, int A_t, int Z_t, double T_n);

}  // namespace Tripathi99

namespace XS4GCR {

class Tripathi99_Total_Inelastic : public Total_Inelastic {
   public:
    Tripathi99_Total_Inelastic();

    void print() const override;

    std::shared_ptr<Total_Inelastic> clone() override;

    double get(const PID &projectile, const TARGET &target, const double &T_n) const override;
};

}  // namespace XS4GCR

#endif  // INCLUDE_XS4GCR_INELASTIC_TRIPATHI99_H_
