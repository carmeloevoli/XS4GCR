#ifndef D2XSECS_ANTIPROTONS_H_
#define D2XSECS_ANTIPROTONS_H_

#include <iostream>
#include <memory>
#include <string>

#include "grid.h"
#include "mks.h"
#include "antiproton_tables.h"
#include "TanNg83.h"
#include "DiMauro2015.h"
#include "Duperray03.h"
#include "pid.h"
#include "utilities.h"

enum generators {
    EPOS, SIBYLL, QGSJET, DIMAURO
};

class Secondary_Antiprotons {
public:
    virtual ~Secondary_Antiprotons() {
    }

    virtual void print() const = 0;

    virtual std::shared_ptr<Secondary_Antiprotons> clone() = 0;

    virtual double get(const PID &projectile, const TARGET &target, const double &T_n, const double &T_ap) const = 0;

    double get_total_inelastic(const TARGET &target, const double &T_ap);

    double get_annihilating_inelastic(const TARGET &target, const double &T_ap);

    double get_non_annihilating_inelastic(const TARGET &target, const double &T_ap);

protected:
    const double alpha = 1. / 3.;
    double a[4] = {-107.9, 29.43, -1.655, 189.9};
    double b[4] = {-100.5, 20.37, -1.182, 162.0};

    std::string model_name;

    inline void set_model_name(const std::string &m) {
        model_name = m;
    }
};

class TanNg1983_antiprotons : public Secondary_Antiprotons {
public:
    TanNg1983_antiprotons();

    void print() const override;

    std::shared_ptr<Secondary_Antiprotons> clone() override;

    double get(const PID &projectile, const TARGET &target, const double &T_n, const double &T_ap) const override;
};

class DiMauro_Secondary_Antiprotons : public Secondary_Antiprotons {
public:
    DiMauro_Secondary_Antiprotons();

    void print() const override;

    std::shared_ptr<Secondary_Antiprotons> clone() override;

    double get(const PID &projectile, const TARGET &target, const double &T_n, const double &T_ap) const override;
};

class Winkler2017_antiprotons : public Secondary_Antiprotons {
public:
    Winkler2017_antiprotons();

    void print() const override;

    std::shared_ptr<Secondary_Antiprotons> clone() override;

    double get(const PID &projectile, const TARGET &target, const double &T_n, const double &T_ap) const override;

private:
    antiproton_tables table;
    std::string data_filename;
};

class Feng2016_antiprotons : public Secondary_Antiprotons {
public:
    Feng2016_antiprotons(generators g);

    void print() const override;

    std::shared_ptr<Secondary_Antiprotons> clone() override;

    double get(const PID &projectile, const TARGET &target, const double &T_n, const double &T_ap) const override;

private:
    generators generator;
    antiproton_tables table;
};

#endif /* INCLUDE_ANTIPROTONS_H_ */