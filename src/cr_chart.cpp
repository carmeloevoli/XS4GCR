// Copyright (c) 2017 Carmelo Evoli - MIT License
#include "XS4GCR/cr_chart.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

namespace XS4GCR {

void DefaultCosmicRayChart::print() { std::cout << "Using default decay chart" << std::endl; }

DefaultCosmicRayChart::DefaultCosmicRayChart() {
    assert(Utils::file_exist(m_chart_filename));
    read_table();
}

void DefaultCosmicRayChart::read_table() {
    std::string line;
    if (Utils::file_exist(m_chart_filename)) {
        std::ifstream in(m_chart_filename);
        while (std::getline(in, line))
            if (line.length() > 0 && line[0] != '#') {
                add_isotope(line);
            }
    }
}

void DefaultCosmicRayChart::add_isotope(const std::string& line) {
    std::istringstream ss(line);
    int A;
    int Z;
    std::string name;
    std::string mode;
    double tau;
    ss >> Z >> A >> name >> mode >> tau;
    Decay_mode decay_mode;
    if (mode == "STABLE") {
        decay_mode = STABLE;
    } else if (mode == "BETA-") {
        decay_mode = BETA_MINUS;
    } else if (mode == "BETA+") {
        decay_mode = BETA_PLUS;
    } else if (mode == "BETA-FED") {
        decay_mode = BETA_MINUS_FED;
    } else if (mode == "BETA+FED") {
        decay_mode = BETA_PLUS_FED;
    } else {
        std::cerr << "Error: mode " << mode << "not found!";
        exit(1);
    }
    auto pid = PID(Z, A);
    decay_params params{tau, decay_mode};
    auto ret = m_chart.insert(std::make_pair(pid, params));
    if (ret.second == false) {
        std::cout << "Warning: element " << pid << " already existed!\n";
    }
}

std::shared_ptr<CosmicRayChart> DefaultCosmicRayChart::clone() {
    return std::make_shared<DefaultCosmicRayChart>(*this);
}

double DefaultCosmicRayChart::get_halftime(PID particle) const {
    auto it = m_chart.find(particle);
    if (it != m_chart.end()) {
        return it->second.tau_half;
    } else {
        std::cout << "Particle " << particle << " not found.\n";
        return -1;
    }
}

std::string DefaultCosmicRayChart::get_mode(PID particle) const {
    auto it = m_chart.find(particle);
    if (it != m_chart.end()) {
        auto mode = it->second.mode;
        if (mode == BETA_MINUS) {
            return "B-";
        } else if (mode == BETA_MINUS_FED) {
            return "B-FED";
        } else if (mode == BETA_PLUS) {
            return "B+";
        } else if (mode == BETA_PLUS_FED) {
            return "B+FED";
        } else {
            return "STABLE";
        }
    } else {
        std::cout << "Particle " << particle << " not found.\n";
        return "none";
    }
}

}  // namespace XS4GCR
