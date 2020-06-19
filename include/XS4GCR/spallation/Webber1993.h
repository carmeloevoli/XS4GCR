// Copyright (c) 2017 Carmelo Evoli - MIT License
#ifndef INCLUDE_XS4GCR_SPALLATION_WEBBER1993_H_
#define INCLUDE_XS4GCR_SPALLATION_WEBBER1993_H_

#include <memory>

#include "XS4GCR/spallation/spallation.h"

namespace XS4GCR {

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

#endif  // INCLUDE_XS4GCR_SPALLATION_WEBBER1993_H_
