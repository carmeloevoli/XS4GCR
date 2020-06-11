// Copyright (c) 2017 Carmelo Evoli - MIT License
#ifndef INCLUDE_XS4GCR_SPALLATION_EVOLI2019_H_
#define INCLUDE_XS4GCR_SPALLATION_EVOLI2019_H_

#include <memory>
#include <string>

#include "XS4GCR/spallation/fit_data.h"
#include "XS4GCR/spallation/fitting_functions.h"
#include "XS4GCR/spallation/ghost_tree.h"
#include "XS4GCR/spallation/spallation.h"

namespace XS4GCR {

class Evoli2019_Spallation : public Spallation {
   public:
    Evoli2019_Spallation();
    void print() override;
    std::shared_ptr<Spallation> clone() override;
    double get(const channel& ch, const TARGET& target, const double& T_n,
               bool do_ghosts = true) override;

   protected:
    void init();
    double direct(const channel& ch, const double& T_n);
    double with_ghosts(const channel& ch, const double& T_n);
    double bestfit_normalization(const channel& ch);
    std::string ghostlist_filename = "data/ghost_list.txt";
    std::string paramsfit_filename = "data/Evoli2019_fragmentation_fitparams.txt";
    std::string fitdata_filename = "data/xsecs_data_GALPROP.txt";
    FittingFunctions fittingFunctions;
    GhostTree ghostTree;
    FitData fitData;
};

}  // namespace XS4GCR

#endif  // INCLUDE_XS4GCR_SPALLATION_EVOLI2019_H_
