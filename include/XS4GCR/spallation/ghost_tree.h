// Copyright (c) 2017 Carmelo Evoli - MIT License
#ifndef INCLUDE_XS4GCR_SPALLATION_GHOST_TREE_H_
#define INCLUDE_XS4GCR_SPALLATION_GHOST_TREE_H_

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "XS4GCR/pid.h"
#include "XS4GCR/utilities.h"

namespace XS4GCR {

using Parent = std::pair<PID, double>;
using Child = PID;
using Parents = std::vector<Parent>;
using Tree = std::map<Child, Parents>;

class GhostTree {
   public:
    GhostTree();
    explicit GhostTree(std::string filename_);
    virtual ~GhostTree();
    size_t n_parents(PID child);
    void read_ghosts();
    void plot_ghosts();

    bool is_present(PID child) { return !(tree.find(child) == tree.end()); }

    Parents& get_parents(PID child) { return tree.at(child); }

   protected:
    std::string filename;
    Tree tree;
};

}  // namespace XS4GCR

#endif  // INCLUDE_XS4GCR_SPALLATION_GHOST_TREE_H_
