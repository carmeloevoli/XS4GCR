// Copyright (c) 2017 Carmelo Evoli - MIT License

#include <fstream>
#include <iomanip>
#include <limits>
#include <string>
#include <vector>

#include "XS4GCR/pid.h"
#include "XS4GCR/xs4gcr.h"

int main() {
    XS4GCR::XSECS xsec;
    xsec.set_secondary_nuclei("Evoli2018");
    auto x_in = xsec.create_secondary_nuclei();
    XS4GCR::TARGET H_ISM(1);

    //    double E = 10. * MKS::GeV;
    //    XS4GCR::channel ch(XS4GCR::C12, XS4GCR::B10);
    //    std::cout << E << " " << x_in->get(ch, H_ISM, E, true) << "\n";

    std::vector<XS4GCR::PID> particles;

    std::string filename = "data/crchart_Z28.txt";
    std::ifstream infile(filename.c_str());
    infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    int Z;
    int A;
    while (!infile.eof()) {
        infile >> Z;
        infile >> A;
        infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        auto pid = XS4GCR::PID(Z, A);
        particles.push_back(pid);
    }
    std::cout << " - read my particle chart with " << particles.size() << " nuclei\n";

    std::fstream txtfile;
    txtfile.open("crxsecs_fragmentation_Evoli2019_direct.txt", std::ios_base::out);
    txtfile.precision(3);

    double E_min = 10. * MKS::MeV;
    double E_max = 1. * MKS::TeV;
    size_t E_size = 5 * 32;

    XS4GCR::log_axis<double> E(E_min, E_max, E_size);

    txtfile << "0 0 0 0 ";
    for (size_t i = 0; i < E_size; ++i) {
        txtfile << std::scientific << E.at(i) / MKS::GeV;
        if (i < E_size - 1) txtfile << " ";
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
                    XS4GCR::channel ch(projectile, fragment);
                    txtfile << x_in->get(ch, H_ISM, E.at(i), false) / MKS::mbarn;
                    if (i < E_size - 1) txtfile << " ";
                }
                txtfile << "\n";
            }
        }
    }
    std::cout << " - computed " << counter << " reactions\n";
    return 0;
}
