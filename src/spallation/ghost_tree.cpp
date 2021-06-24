// Copyright (c) 2017 Carmelo Evoli - MIT License
#include "XS4GCR/spallation/ghost_tree.h"

#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <utility>

namespace XS4GCR {

GhostTree::GhostTree() {}

GhostTree::GhostTree(std::string filename_) : filename(filename_) {
    read_ghosts();
    // plot_ghosts();
}

GhostTree::~GhostTree() {}

bool GhostTree::isGhost(double tau_value, std::string tau_units) const {
    double halfLife = tau_value;
    if (tau_units == "ms")
        halfLife *= 1e-3 * cgs::sec;
    else if (tau_units == "s")
        halfLife *= cgs::sec;
    else if (tau_units == "m")
        halfLife *= 60. * cgs::sec;
    else if (tau_units == "h")
        halfLife *= 3600. * cgs::sec;
    else if (tau_units == "d")
        halfLife *= 24. * 3600. * cgs::sec;
    else if (tau_units == "y")
        halfLife *= cgs::year;
    else
        assert(tau_units == "s");
    return halfLife < halfLife_max;
}

void GhostTree::read_ghosts() {
    std::ifstream infile(filename.c_str());
    infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string Z_c_str;
    std::string Z_p_str;
    std::string tau_units;
    int Z_c;
    int A_c;
    int Z_p;
    int A_p;
    size_t counter = 0;
    double branching;
    double tau_value;
    while (infile >> Z_p_str >> A_p >> Z_c_str >> A_c >> branching >> tau_value >> tau_units) {
        if (isGhost(tau_value, tau_units)) {
            Z_c = Utils::str_to_Z(Z_c_str);
            Z_p = Utils::str_to_Z(Z_p_str);
            counter++;
            Child child(Z_c, A_c);
            Parent parent = std::make_pair(PID(Z_p, A_p), branching / 100.);
            if (is_present(child)) {
                tree.at(child).push_back(parent);
            } else {
                Parents parents;
                parents.push_back(parent);
                tree.insert(std::make_pair(child, parents));
            }
        }
    }
    infile.close();
    std::cout << " - read " << counter << " ghost reactions\n";
}

void GhostTree::plot_ghosts() const {
    for (auto& node : tree) {
        std::cout << node.first << " <- ";
        for (auto& parent : node.second)
            std::cout << parent.first << " % " << parent.second << " | ";
        std::cout << "\n";
    }
}

size_t GhostTree::n_parents(PID child) {
    if (is_present(child)) {
        return tree.at(child).size();
    } else {
        return 0;
    }
}

}  // namespace XS4GCR
