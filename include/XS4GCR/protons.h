// Copyright (c) 2017 Carmelo Evoli - MIT License
#ifndef INCLUDE_XS4GCR_PROTONS_H_
#define INCLUDE_XS4GCR_PROTONS_H_

#include <map>
#include <memory>
#include <string>

#include "XS4GCR/mks.h"
#include "XS4GCR/pid.h"
#include "XS4GCR/utilities.h"

namespace XS4GCR {

class Proton_Xsecs {
   public:
    virtual ~Proton_Xsecs() {}

    virtual void print() const = 0;

    virtual std::shared_ptr<Proton_Xsecs> clone() = 0;

    virtual double get_inelastic(const TARGET &target, const double &T_n) const = 0;

   protected:
    std::string model_name;

    inline void set_model_name(const std::string &m) { model_name = m; }
};

class DRAGON2_Proton_Xsecs : public Proton_Xsecs {
   public:
    DRAGON2_Proton_Xsecs();

    void print() const override;

    std::shared_ptr<Proton_Xsecs> clone() override;

    double get_inelastic(const TARGET &target, const double &T_n) const override;

   private:
    double T_threshold = 0.2797 * MKS::GeV;
};

}  // namespace XS4GCR

#endif  // INCLUDE_XS4GCR_PROTONS_H_
