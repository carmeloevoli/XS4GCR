// Copyright (c) 2017 Carmelo Evoli - MIT License
#ifndef INCLUDE_XS4GCR_INELASTIC_INELASTIC_H_
#define INCLUDE_XS4GCR_INELASTIC_INELASTIC_H_

#include <cmath>
#include <iostream>
#include <map>
#include <memory>
#include <string>

#include "XS4GCR/grid.h"
#include "XS4GCR/mks.h"
#include "XS4GCR/pid.h"
#include "XS4GCR/utilities.h"

namespace XS4GCR {

class Total_Inelastic {
   public:
    virtual ~Total_Inelastic() {}

    virtual void print() const = 0;

    virtual std::shared_ptr<Total_Inelastic> clone() = 0;

    virtual double get(const PID &projectile, const TARGET &target, const double &T_n) const = 0;

   protected:
    std::string model_name;

    inline void set_model_name(const std::string &m) { model_name = m; }
};

}  // namespace XS4GCR

#endif  // INCLUDE_XS4GCR_INELASTIC_INELASTIC_H_
