#include "d2xsec.h"

std::shared_ptr<Total_Inelastic> D2XSEC::create_total_inelastic() {
	if (total_inelastic_model == "Letaw83") {
		total_inelastic = std::make_shared<Letaw1983_Total_Inelastic>();
	} else if (total_inelastic_model == "Tripathi99") {
		total_inelastic = std::make_shared<Tripathi99_Total_Inelastic>();
	} else if (total_inelastic_model == "CROSEC") {
		total_inelastic = std::make_shared<CROSEC_Total_Inelastic>();
	} else {
		return nullptr;
	}
	total_inelastic->print();
	return total_inelastic->clone();
}

std::shared_ptr<Proton_Xsecs> D2XSEC::create_proton_xsecs() {
	if (proton_xsecs_model == "DRAGON2") {
		proton_xsecs = std::make_shared<DRAGON2_Proton_Xsecs>();
	} else {
		assert(proton_xsecs_model == "DRAGON2");
	}
	proton_xsecs->print();
	return proton_xsecs->clone();
}

std::shared_ptr<Secondary_Leptons> D2XSEC::create_secondary_leptons(const PID& lepton) {
	if (secondary_leptons_model == "Kamae2006") {
		secondary_leptons = std::make_shared<Kamae2006_Secondary_Leptons>(lepton);
	} else if (secondary_leptons_model == "HuangPohl2007") {
		secondary_leptons = std::make_shared<HuangPohl2007_Secondary_Leptons>(lepton);
	} else {
		assert(secondary_leptons_model == "Kamae2006");
		return 0;
	}
	secondary_leptons->print();
	return secondary_leptons->clone();
}

std::shared_ptr<Secondary_Antiprotons> D2XSEC::create_secondary_antiprotons(generators g) {
	if (secondary_antiprotons_model == "TanNg83") {
		secondary_antiprotons = std::make_shared<TanNg1983_antiprotons>();
	} else if (secondary_antiprotons_model == "DiMauro2015") {
		secondary_antiprotons = std::make_shared<DiMauro_Secondary_Antiprotons>();
	} else if (secondary_antiprotons_model == "Winkler2017") {
		secondary_antiprotons = std::make_shared<Winkler2017_antiprotons>();
	} else if (secondary_antiprotons_model == "Feng2016") {
		secondary_antiprotons = std::make_shared<Feng2016_antiprotons>(EPOS);
	} else {
		assert(secondary_antiprotons_model == "TanNg83");
		return 0;
	}
	secondary_antiprotons->print();
	return secondary_antiprotons->clone();
}

/*std::shared_ptr<Decay_Chart> D2XSEC::create_decay_chart() {
 decay_chart = std::make_shared<DRAGON2_Decay_Chart>();
 decay_chart->print();
 return decay_chart->clone();
 }*/
