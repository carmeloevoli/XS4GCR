#include "ghost_tree.h"

namespace DRAGON2 {

GhostTree::GhostTree() {
}

GhostTree::GhostTree(std::string filename_) :
		filename(filename_) {
	read_ghosts();
	plot_ghosts();
}

GhostTree::~GhostTree() {
}

void GhostTree::read_ghosts() { // TODO add a minimum time
	std::ifstream infile(filename.c_str());
	infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::string Z_c_str, Z_p_str;
	int Z_c, A_c, Z_p, A_p, counter = 0;
	double branching, decay_time;
	while (infile >> Z_p_str >> A_p >> Z_c_str >> A_c >> branching >> decay_time) {
		Z_c = str_to_Z(Z_c_str);
		Z_p = str_to_Z(Z_p_str);
		counter++;
		Child child(Z_c, A_c);
		Parent parent = std::make_pair(PID(Z_p, A_p), branching / 100.);
		if (is_present(child)) {
			tree.at(child).push_back(parent);
		} else {
			Parents parents { parent };
			tree.insert(std::make_pair(child, parents));
		}
	}
	infile.close();
	std::cout << " - read " << counter << " ghost reactions!\n";
}

void GhostTree::plot_ghosts() {
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

} // namespace DRAGON2
