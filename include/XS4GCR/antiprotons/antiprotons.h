// Copyright (c) 2017 Carmelo Evoli - MIT License
#ifndef INCLUDE_XS4GCR_ANTIPROTONS_ANTIPROTONS_H_
#define INCLUDE_XS4GCR_ANTIPROTONS_ANTIPROTONS_H_

#include <iostream>
#include <memory>
#include <string>

#include "DiMauro2015.h"
#include "Duperray03.h"
#include "TanNg83.h"
#include "XS4GCR/antiprotons/antiproton_tables.h"
#include "XS4GCR/grid.h"
#include "XS4GCR/mks.h"
#include "XS4GCR/pid.h"
#include "XS4GCR/utilities.h"

namespace XS4GCR {

enum generators { EPOS, SIBYLL, QGSJET, DIMAURO };

class Secondary_Antiprotons {
   public:
    virtual ~Secondary_Antiprotons() {}

    virtual void print() const = 0;

    virtual std::shared_ptr<Secondary_Antiprotons> clone() = 0;

    virtual double get(const PID &projectile, const TARGET &target, const double &T_n,
                       const double &T_ap) const = 0;

    double get_total_inelastic(const TARGET &target, const double &T_ap);

    double get_annihilating_inelastic(const TARGET &target, const double &T_ap);

    double get_non_annihilating_inelastic(const TARGET &target, const double &T_ap);

   protected:
    const double alpha = 1. / 3.;
    double a[4] = {-107.9, 29.43, -1.655, 189.9};
    double b[4] = {-100.5, 20.37, -1.182, 162.0};

    std::string model_name;

    inline void set_model_name(const std::string &m) { model_name = m; }
};

class TanNg1983_antiprotons : public Secondary_Antiprotons {
   public:
    TanNg1983_antiprotons();

    void print() const override;

    std::shared_ptr<Secondary_Antiprotons> clone() override;

    double get(const PID &projectile, const TARGET &target, const double &T_n,
               const double &T_ap) const override;
};

class DiMauro_Secondary_Antiprotons : public Secondary_Antiprotons {
   public:
    DiMauro_Secondary_Antiprotons();

    void print() const override;

    std::shared_ptr<Secondary_Antiprotons> clone() override;

    double get(const PID &projectile, const TARGET &target, const double &T_n,
               const double &T_ap) const override;
};

class Winkler2017_antiprotons : public Secondary_Antiprotons {
   public:
    Winkler2017_antiprotons();

    void print() const override;

    std::shared_ptr<Secondary_Antiprotons> clone() override;

    double get(const PID &projectile, const TARGET &target, const double &T_n,
               const double &T_ap) const override;

   private:
    antiproton_tables table;
    std::string data_filename;
};

class Feng2016_antiprotons : public Secondary_Antiprotons {
   public:
    explicit Feng2016_antiprotons(generators g);

    void print() const override;

    std::shared_ptr<Secondary_Antiprotons> clone() override;

    double get(const PID &projectile, const TARGET &target, const double &T_n,
               const double &T_ap) const override;

   private:
    generators generator;
    antiproton_tables table;
};

}  // namespace XS4GCR

#endif  // INCLUDE_XS4GCR_ANTIPROTONS_ANTIPROTONS_H_
