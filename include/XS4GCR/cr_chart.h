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
    virtual void init() = 0;
    virtual std::shared_ptr<CosmicRayChart> clone() = 0;

    double get_halftime(PID particle) const;
    std::string get_mode(PID particle) const;
    std::vector<PID> get_particle_list() const;

    struct decay_params {
        double tau_half;
        Decay_mode mode;
    };

   protected:
    std::map<PID, decay_params> m_chart;
};

class DefaultCosmicRayChart : public CosmicRayChart {
   public:
    DefaultCosmicRayChart();
    void print() override;
    void init() override;
    std::shared_ptr<CosmicRayChart> clone() override;

   protected:
    void add_isotope(const std::string& line);
    void read_table();

   protected:
    const std::string m_chart_filename = "data/crchart_Z28_2020.txt";
};

}  // namespace XS4GCR

#endif  // INCLUDE_XS4GCR_CR_CHART_H_
