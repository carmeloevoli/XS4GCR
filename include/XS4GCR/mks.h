// Copyright (c) 2017 Carmelo Evoli - MIT License
#ifndef INCLUDE_XS4GCR_MKS_H_
#define INCLUDE_XS4GCR_MKS_H_

#include <cmath>
#define pow2(A) ((A) * (A))
#define pow3(A) ((A) * (A) * (A))
#define pow4(A) ((A) * (A) * (A) * (A))
#define pow5(A) ((A) * (A) * (A) * (A) * (A))

namespace MKS {

// MKS units
static const double meter = 1;
static const double kilogram = 1;
static const double second = 1;
static const double ampere = 1;
static const double kelvin = 1;
static const double mole = 1;
static const double steradian = 1;
static const double joule = kilogram * pow2(meter) / pow2(second);
static const double tesla = kilogram / ampere / pow2(second);
static const double coulomb = ampere * second;

// derived units
static const double centimeter = 1e-2 * meter;
static const double kilometer = 1e3 * meter;
static const double gram = 1e-3 * kilogram;
static const double erg = 1e-7 * joule;
static const double gauss = 1e-4 * tesla;
static const double microgauss = 1e-6 * gauss;
static const double nanogauss = 1e-9 * gauss;
static const double fm = 1e-15 * meter;
static const double barn = 1e-28 * pow2(meter);
static const double mbarn = 1e-3 * barn;

// abbreviations
static const double sec = second;
static const double K = kelvin;
static const double kg = kilogram;
static const double cm = centimeter;
static const double km = kilometer;
static const double cm2 = cm * cm;
static const double cm3 = cm * cm * cm;
static const double mt = meter;
static const double mt2 = meter * meter;
static const double mt3 = meter * meter * meter;
static const double muG = microgauss;
static const double nG = nanogauss;
static const double sr = steradian;

// physical constants
static const double c_light = 2.99792458e10 * centimeter / second;
static const double c_squared = c_light * c_light;
static const double proton_mass = 1.67262158e-24 * gram;
static const double proton_mass_c = proton_mass * c_light;
static const double proton_mass_c2 = proton_mass * c_squared;
static const double proton_mass_c2_2 = proton_mass_c2 * proton_mass_c2;
static const double neutron_mass = 1.67492735e-24 * gram;
static const double neutron_mass_c2 = neutron_mass * c_squared;
static const double electron_mass = 9.10938291e-28 * gram;
static const double electron_mass_c2 = electron_mass * gram;
static const double electron_radius = 2.8179403227e-15 * meter;
static const double sun_mass = 1.989e30 * kg;
static const double h_planck = 6.62607004e-34 * pow2(meter) * kg / sec;
static const double k_boltzmann = 1.3806488e-23 * joule / kelvin;
static const double elementary_charge = 1.60217662e-19 * coulomb;
static const double vacuum_permeability = 4e-7 * M_PI * tesla * meter / ampere;

// electron volt
static const double electronvolt = 1.60217657e-19 * joule;
static const double kiloelectronvolt = 1e3 * electronvolt;
static const double megaelectronvolt = 1e6 * electronvolt;
static const double gigaelectronvolt = 1e9 * electronvolt;
static const double teraelectronvolt = 1e12 * electronvolt;
static const double petaelectronvolt = 1e15 * electronvolt;
static const double exaelectronvolt = 1e18 * electronvolt;
static const double eV = electronvolt;
static const double keV = kiloelectronvolt;
static const double MeV = megaelectronvolt;
static const double GeV = gigaelectronvolt;
static const double GeV_2 = GeV * GeV;
static const double TeV = teraelectronvolt;
static const double PeV = petaelectronvolt;
static const double EeV = exaelectronvolt;
static const double keV_c = keV / c_light;
static const double MeV_c = MeV / c_light;
static const double GeV_c = GeV / c_light;
static const double TeV_c = TeV / c_light;
static const double PeV_c = PeV / c_light;
static const double EeV_c = EeV / c_light;

// time
static const double year = 3.15569e7 * second;
static const double kiloyear = 1e3 * year;
static const double megayear = 1e6 * year;
static const double gigayear = 1e9 * year;
static const double kyr = kiloyear;
static const double Myr = megayear;
static const double Gyr = gigayear;

// parsec
static const double parsec = 3.0856775807e18 * centimeter;
static const double kiloparsec = 1e3 * parsec;
static const double megaparsec = 1e6 * parsec;
static const double gigaparsec = 1e9 * parsec;
static const double pc = parsec;
static const double kpc = kiloparsec;
static const double Mpc = megaparsec;
static const double Gpc = gigaparsec;

// useful quantities
static const double He_correction_xsec = pow(4.0, 2.0 / 3.0);
static const double f_He = 0.11;

}  // namespace MKS

#endif  // INCLUDE_XS4GCR_MKS_H_
