// Copyright (c) 2017 Carmelo Evoli - MIT License
#include "XS4GCR/inelastic/CROSEC.h"

#include <memory>

namespace XS4GCR {

CROSEC_Total_Inelastic::CROSEC_Total_Inelastic() { set_model_name("CROSEC"); }

void CROSEC_Total_Inelastic::print() const {
    std::cout << "# Using CROSEC total inelastic model:" << '\n';
    std::cout << "# REF1" << '\n';
}

std::shared_ptr<Total_Inelastic> CROSEC_Total_Inelastic::clone() {
    init();
    return std::make_shared<CROSEC_Total_Inelastic>(*this);
}

void CROSEC_Total_Inelastic::init() {
    assert(Utils::file_exist(data_filename));
    int ISS = -1;
    Utils::sigtap_cc(ISS);
}

double CROSEC_Total_Inelastic::set_energy_within_range(const double& T_n) const {
    if (T_n < T_n_min)
        return T_n_min;
    else if (T_n > T_n_max)
        return T_n_max;
    else
        return T_n;
}

double CROSEC_Total_Inelastic::get(const PID& projectile, const TARGET& target,
                                   const double& T_n) const {
    assert(projectile != PID(1, 1));
    double TA = projectile.get_A();
    double TZ = projectile.get_Z();  // target nucleus mass and charge numbers (4.0<=A2<=239.0)
    double T = set_energy_within_range(T_n) /
               cgs::MeV;  // projectile particle kinetic energy (MEV; 14(20)MEV<T<1TEV)
    double value = Utils::sighad_cc(IS, PA, PZ, TA, TZ, T) * cgs::mbarn;
    value *= (target.is_He()) ? 2.1 * pow(projectile.get_A(), .055) : 1;
    return value;
}

}  // namespace XS4GCR
