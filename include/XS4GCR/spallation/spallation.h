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
#include "XS4GCR/utilities.h"
//  #include "Webber2003_table.h"

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

class Webber1993_Spallation : public Spallation {
   public:
    Webber1993_Spallation();
    void init();
    void print() override;
    std::shared_ptr<Spallation> clone() override;
    double get(const channel& ch, const TARGET& target, const double& T_n,
               bool do_ghosts = true) override;

   protected:
    double direct(const channel& ch, const double& T_n);
};

}  // namespace XS4GCR

#endif  // INCLUDE_XS4GCR_SPALLATION_SPALLATION_H_
