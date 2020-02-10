#include "d2xsec.h"
#include <fstream>
#include <iomanip>

using namespace DRAGON2;

int main() {
	D2XSEC xsec;
	xsec.set_secondary_nuclei("Evoli2018");
	auto x_in = xsec.create_secondary_nuclei();
	TARGET H_ISM(1);

	std::vector<PID> particles = { Fe56, S32, Si28, Mg24, Ne20, O18, O17, O16, N15, N14, C14, C13,
			C12, B11, B10, Be10, Be9, Be7, Li7, Li6, He4, He3 };

	std::fstream txtfile;
	txtfile.open("crxsecs_fragmentation_Evoli2019_direct.txt", std::ios_base::out);
	txtfile.precision(3);

	double E_min = 10. * MKS::MeV;
	double E_max = 1. * MKS::TeV;
	size_t E_size = 5 * 32;

	log_axis<double> E(E_min, E_max, E_size);

	std::cout << E.get_ratio() << "\n";

	txtfile << "0 0 0 0 ";
	for (size_t i = 0; i < E_size; ++i) {
		txtfile << std::scientific << E.at(i) / MKS::GeV;
		if (i < E_size - 1)
			txtfile << " ";
	}
	txtfile << "\n";

	int counter = 0;
	for (auto& projectile : particles) {
		for (auto& fragment : particles) {
			if (projectile.get_A() > fragment.get_A()) {
				counter++;
				txtfile << projectile.get_Z() << " " << projectile.get_A() << " "
						<< fragment.get_Z() << " " << fragment.get_A() << " ";
				for (size_t i = 0; i < E_size; ++i) {
					channel ch(projectile, fragment);
					txtfile << x_in->get(ch, H_ISM, E.at(i), false) / MKS::mbarn;
					if (i < E_size - 1)
						txtfile << " ";
				}
				txtfile << "\n";
			}
		}
	}
	std::cout << counter << "\n";
		return 0;
	}
