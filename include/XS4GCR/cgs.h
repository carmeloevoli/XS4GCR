// Copyright (c) 2017 Carmelo Evoli - MIT License
#ifndef INCLUDE_XS4GCR_CGS_H_
#define INCLUDE_XS4GCR_CGS_H_

#include <cmath>
#define pow2(A) ((A) * (A))
#define pow3(A) ((A) * (A) * (A))
#define pow4(A) ((A) * (A) * (A) * (A))
#define pow5(A) ((A) * (A) * (A) * (A) * (A))

namespace cgs {

// cgs units

static const double centimeter = 1;
static const double gram = 1;
static const double second = 1;
static const double erg = 1;
static const double kelvin = 1;
static const double steradian = 1;
static const double gauss = 1;

// derived units
static const double meter = 1e2 * centimeter;
static const double fm = 1e-13 * centimeter;
static const double barn = 1e-24 * pow2(centimeter);
static const double mbarn = 1e-3 * barn;

// abbreviations
static const double sec = second;
static const double K = kelvin;
static const double cm = centimeter;
static const double m = meter;
static const double sr = steradian;

// physical constants
static const double c_light = 2.99792458e10 * centimeter / second;
static const double c_squared = c_light * c_light;
static const double proton_mass = 1.67262158e-24 * gram;
static const double proton_mass_c = proton_mass * c_light;
static const double proton_mass_c2 = proton_mass * c_squared;
static const double neutron_mass = 1.67492735e-24 * gram;
static const double neutron_mass_c2 = neutron_mass * c_squared;
static const double electron_mass = 9.10938291e-28 * gram;
static const double electron_mass_c2 = electron_mass * gram;
static const double electron_radius = 2.8179403227e-13 * centimeter;

// electron volt
static const double electronvolt = 1.60217657e-12 * erg;
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
static const double TeV = teraelectronvolt;
static const double PeV = petaelectronvolt;
static const double keV_c = keV / c_light;
static const double MeV_c = MeV / c_light;
static const double GeV_c = GeV / c_light;
static const double TeV_c = TeV / c_light;
static const double PeV_c = PeV / c_light;

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

}  // namespace cgs

#endif  // INCLUDE_XS4GCR_CGS_H_
