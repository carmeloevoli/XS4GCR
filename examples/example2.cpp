#include "d2xsec.h"
#include "pid.h"

int main(/* Get production cross-section on H or He for electrons or positrons */) {
	D2XSEC xsec;
	xsec.set_secondary_leptons("Kamae2006"); // alternative model: HuangPohl2007
	PID electron(-1, 0), positron(1, 0);
    PID H(1, 1), He(2, 4);
    TARGET H_ISM(1), He_ISM(2);

    auto x_leptons = xsec.create_secondary_leptons(positron);

	double T_n_proj = 100 * GeV;
	double T_lepton = 10 * GeV;

	std::cout << T_lepton / GeV << " ";
	std::cout << x_leptons->get(H, He_ISM, T_n_proj, T_lepton) / (mbarn / GeV) << " ";
	std::cout << x_leptons->get(He, He_ISM, T_n_proj, T_lepton) / (mbarn / GeV) << "\n";
}