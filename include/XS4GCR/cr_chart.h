// Copyright (c) 2017 Carmelo Evoli - MIT License
#ifndef INCLUDE_XS4GCR_CR_CHART_H_
#define INCLUDE_XS4GCR_CR_CHART_H_

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "XS4GCR/pid.h"
#include "XS4GCR/utilities.h"

namespace XS4GCR {

class CosmicRayChart {
   public:
    enum Decay_mode { STABLE, BETA_MINUS, BETA_PLUS, BETA_MINUS_FED, BETA_PLUS_FED };

    virtual ~CosmicRayChart() = default;

    virtual void print() = 0;
    virtual std::shared_ptr<CosmicRayChart> clone() = 0;
    virtual double get_halftime(PID particle) const = 0;
    virtual std::string get_mode(PID particle) const = 0;
};

class DefaultCosmicRayChart : public CosmicRayChart {
   public:
    DefaultCosmicRayChart();
    void print() override;
    std::shared_ptr<CosmicRayChart> clone() override;
    double get_halftime(PID particle) const override;
    std::string get_mode(PID particle) const override;

    struct decay_params {
        double tau_half;
        Decay_mode mode;
    };

   protected:
    void add_isotope(const std::string& line);
    void read_table();

    const std::string m_chart_filename = "data/crchart_Z28_2020.txt";
    std::map<PID, decay_params> m_chart;
};

}  // namespace XS4GCR

#endif  // INCLUDE_XS4GCR_CR_CHART_H_
