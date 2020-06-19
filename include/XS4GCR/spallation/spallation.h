// Copyright (c) 2017 Carmelo Evoli - MIT License
#ifndef INCLUDE_XS4GCR_SPALLATION_SPALLATION_H_
#define INCLUDE_XS4GCR_SPALLATION_SPALLATION_H_

#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "XS4GCR/pid.h"

namespace XS4GCR {

class Spallation {
   public:
    virtual void print() = 0;
    virtual std::shared_ptr<Spallation> clone() = 0;
    virtual double get(const channel& ch, const TARGET& target, const double& T_n,
                       bool do_ghosts = true) = 0;

    inline void set_model_name(const std::string& m) { model_name = m; }

    virtual ~Spallation() {}

   protected:
    std::string model_name;
};

}  // namespace XS4GCR

#endif  // INCLUDE_XS4GCR_SPALLATION_SPALLATION_H_
