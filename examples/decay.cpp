// Copyright (c) 2017 Carmelo Evoli - MIT License

#include <memory>

#include "XS4GCR/pid.h"
#include "XS4GCR/xs4gcr.h"

/**
 * @example decay.cpp
 *
 * In this example the decay properties of a
 * nuclear species are displayed.
 *
 * @see https://arxiv.org/abs/1711.09616
 */

/**
 * @brief Display half-life in year and decay mode
 *
 * @param particle identifier
 */
void print_decay_properties(std::shared_ptr<XS4GCR::CosmicRayChart> decays, XS4GCR::PID particle) {
    if (decays->get_halftime(particle) > 0) {
        auto mode = decays->get_mode(particle);
        auto tau_kyr = decays->get_halftime(particle) / cgs::kyr;
        std::cout << particle << " decays in " << tau_kyr << " kyr";
        std::cout << " with mode " << decays->get_mode(particle) << "\n";
    } else {
        std::cout << particle << " is stable.\n";
    }
}

/**
 * @brief Main function for example5
 */
int main() {
    XS4GCR::XSECS xsec;
    auto decays = xsec.create_decay_chart();
    XS4GCR::PID Be10 = XS4GCR::PID(4, 10);
    XS4GCR::PID B10 = XS4GCR::PID(5, 10);
    print_decay_properties(decays, Be10);
    print_decay_properties(decays, B10);
}
