#ifndef D2XSECS_XSEC_INELASTIC_H
#define D2XSECS_XSEC_INELASTIC_H

#include <cmath>
#include <iostream>
#include <map>
#include <memory>
#include <string>

#include "grid.h"
#include "mks.h"
#include "pid.h"
#include "utilities.h"

namespace DRAGON2 {

class Total_Inelastic {
public:
    virtual ~Total_Inelastic() {
    }

    virtual void print() const = 0;

    virtual std::shared_ptr<Total_Inelastic> clone() = 0;

    virtual double get(const PID &projectile, const TARGET &target, const double &T_n) const = 0;

protected:
    std::string model_name;

    inline void set_model_name(const std::string &m) {
        model_name = m;
    }
};

class Letaw1983_Total_Inelastic : public Total_Inelastic {
public:
    Letaw1983_Total_Inelastic();

    void print() const override;

    std::shared_ptr<Total_Inelastic> clone() override;

    double get(const PID &projectile, const TARGET &target, const double &T_n) const override;
};

class Tripathi99_Total_Inelastic : public Total_Inelastic {
public:
    Tripathi99_Total_Inelastic();

    void print() const override;

    std::shared_ptr<Total_Inelastic> clone() override;

    double get(const PID &projectile, const TARGET &target, const double &T_n) const override;
};

class CROSEC_Total_Inelastic : public Total_Inelastic {
public:
    CROSEC_Total_Inelastic();

    void print() const override;

    std::shared_ptr<Total_Inelastic> clone() override;

    double get(const PID &projectile, const TARGET &target, const double &T_n) const override;

protected:
    void init();

    double set_energy_within_range(const double &T_n) const;

    std::string data_filename = "data/barpol.txt";
    int IS = 2; // calculation of non-elastic cross-sections
    double PA = 1, PZ = 1; // projectile mass and charge numbers (for pions PA<0.2)
    double T_n_min = 20. * MeV, T_n_max = TeV;
};

} // namespace DRAGON2

#endif
