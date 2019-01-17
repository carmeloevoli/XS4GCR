#ifndef INCLUDE_SPALLATION_EVOLI2018_H_
#define INCLUDE_SPALLATION_EVOLI2018_H_

#include "ghost_tree.h"
#include "spallation.h"
#include "fit_data.h"
#include "fitting_functions.h"

namespace DRAGON2 {

class Evoli2018_Spallation: public Spallation {
public:
	Evoli2018_Spallation();
	void print() override;
	std::shared_ptr<Spallation> clone() override;
	double get(const channel& ch, const TARGET& target, const double& T_n, bool do_ghosts = true) override;

protected:
	void init();
	double direct(const channel& ch, const double& T_n);
	double with_ghosts(const channel& ch, const double& T_n);
	double bestfit_normalization(const channel& ch);
	std::string ghostlist_filename = "data/ghost_list.txt";
	std::string paramsfit_filename = "data/spallatation_fit_params.txt";
	std::string fitdata_filename = "data/xsecs_data_GALPROP.txt";
	FittingFunctions fittingFunctions;
	GhostTree ghostTree;
	FitData fitData;
};

} // namespace DRAGON2


#endif /* INCLUDE_SPALLATION_EVOLI2018_H_ */
