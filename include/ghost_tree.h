#ifndef INCLUDE_GHOST_TREE_H_
#define INCLUDE_GHOST_TREE_H_

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "pid.h"
#include "utilities.h"

namespace DRAGON2 {

using Parent = std::pair<PID, double>;
using Child = PID;
using Parents = std::vector<Parent>;
using Tree = std::map<Child, Parents>;

class GhostTree {
public:
	GhostTree();
	GhostTree(std::string filename_);
	virtual ~GhostTree();
	size_t n_parents(PID child);
	void read_ghosts();
	void plot_ghosts();

	bool is_present(PID child) {
		return !(tree.find(child) == tree.end());
	}

	Parents& get_parents(PID child) {
		return tree.at(child);
	}

protected:
	std::string filename;
	Tree tree;
};

} // namespace DRAGON2

#endif /* INCLUDE_GHOST_TREE_H_ */
