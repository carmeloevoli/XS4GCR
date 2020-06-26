// Copyright (c) 2017 Carmelo Evoli - MIT License

#include <fstream>
#include <iomanip>
#include <limits>
#include <memory>
#include <string>
#include <vector>

#include "XS4GCR/pid.h"
#include "XS4GCR/xs4gcr.h"

void write_table(const std::shared_ptr<XS4GCR::Spallation>& sigma,
                 const std::shared_ptr<XS4GCR::CosmicRayChart>& chart, const std::string& filename,
                 bool doGhosts) {
    XS4GCR::TARGET H_ISM(1);

    std::fstream txtfile;
    txtfile.open(filename, std::ios_base::out);
    txtfile.precision(3);

    const double E_min = 10. * MKS::MeV;
    const double E_max = 1. * MKS::TeV;
    const size_t E_size = 5 * 32;
    const XS4GCR::log_axis<double> E(E_min, E_max, E_size);

    txtfile << "0 0 0 0 ";
    for (size_t i = 0; i < E_size; ++i) {
        txtfile << std::scientific << E.at(i) / MKS::GeV;
        if (i < E_size - 1) txtfile << " ";
    }
    txtfile << "\n";

    auto particles = chart->get_particle_list();

    size_t counter = 0;
    for (auto& projectile : particles) {
        for (auto& fragment : particles) {
            if (projectile.get_A() > fragment.get_A()) {
                counter++;
                txtfile << fragment.get_Z() << " " << fragment.get_A() << " ";
                txtfile << projectile.get_Z() << " " << projectile.get_A() << " ";
                for (size_t i = 0; i < E_size; ++i) {
                    XS4GCR::channel ch(projectile, fragment);
                    txtfile << sigma->get(ch, H_ISM, E.at(i), doGhosts) / MKS::mbarn;
                    if (i < E_size - 1) txtfile << " ";
                }
                txtfile << "\n";
            }
        }
    }
    std::cout << " - computed " << counter << " reactions\n";
}

int main() {
    XS4GCR::XSECS xsec;

    xsec.set_secondary_nuclei("Evoli2019");
    auto x_in = xsec.create_secondary_nuclei();

    auto crchart = xsec.create_decay_chart();

    write_table(x_in, crchart, "crxsecs_fragmentation_Evoli2019_direct.txt", false);
    write_table(x_in, crchart, "crxsecs_fragmentation_Evoli2019_cumulative.txt", true);
}
