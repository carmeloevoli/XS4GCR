#ifndef _XSEC_H
#define _XSEC_H

#include <iostream>
#include <memory>
#include <string>

#include "decay.h"
#include "antiprotons.h"
#include "inelastic.h"
#include "leptons.h"
#include "spallation.h"
#include "protons.h"

namespace DRAGON2 {

class D2XSEC {
public:
	D2XSEC() {
	}

	virtual ~D2XSEC() {
	}

	std::shared_ptr<Total_Inelastic> create_total_inelastic();
	std::shared_ptr<Proton_Xsecs> create_proton_xsecs();
	std::shared_ptr<Secondary_Antiprotons> create_secondary_antiprotons(generators g = EPOS);
	std::shared_ptr<Secondary_Leptons> create_secondary_leptons(const PID &lepton);
	std::shared_ptr<Decay_Chart> create_decay_chart();
	std::shared_ptr<Spallation> create_secondary_nuclei();

	inline void set_total_inelastic(const std::string &model_name) {
		total_inelastic_model = model_name;
	}

	inline void set_proton_xsecs(const std::string &model_name) {
		proton_xsecs_model = model_name;
	}

	inline void set_secondary_antiprotons(const std::string &model_name) {
		secondary_antiprotons_model = model_name;
	}

	inline void set_secondary_leptons(const std::string &model_name) {
		secondary_leptons_model = model_name;
	}

	inline void set_secondary_nuclei(const std::string &model_name) {
		secondary_nuclei_model = model_name;
	}

private:
	std::string total_inelastic_model = "DRAGON2";
	std::string secondary_antiprotons_model = "DiMauro15";
	std::string proton_xsecs_model = "DRAGON2";
	std::string secondary_leptons_model = "Kamae2006";
	std::string secondary_nuclei_model = "Webber1993";

	std::shared_ptr<Total_Inelastic> total_inelastic;
	std::shared_ptr<Proton_Xsecs> proton_xsecs;
	std::shared_ptr<Secondary_Leptons> secondary_leptons;
	std::shared_ptr<Secondary_Antiprotons> secondary_antiprotons;
	std::shared_ptr<Decay_Chart> decay_chart;
	std::shared_ptr<Spallation> secondary_nuclei;
};

} // namespace DRAGON2

#endif
