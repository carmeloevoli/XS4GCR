// Copyright (c) 2017 Carmelo Evoli - MIT License
#ifndef INCLUDE_XS4GCR_NUCLEILIST_H_
#define INCLUDE_XS4GCR_NUCLEILIST_H_

#include "XS4GCR/pid.h"

namespace XS4GCR {

static const auto electron = XS4GCR::PID(-1, 0);
static const auto positron = XS4GCR::PID(1, 0);
static const auto H1 = XS4GCR::PID(1, 1);
static const auto H2 = XS4GCR::PID(1, 2);
static const auto He3 = XS4GCR::PID(2, 3);
static const auto He4 = XS4GCR::PID(2, 4);
static const auto Li6 = XS4GCR::PID(3, 6);
static const auto Li7 = XS4GCR::PID(3, 7);
static const auto Be7 = XS4GCR::PID(4, 7);
static const auto Be9 = XS4GCR::PID(4, 9);
static const auto Be10 = XS4GCR::PID(4, 10);
static const auto B10 = XS4GCR::PID(5, 10);
static const auto B11 = XS4GCR::PID(5, 11);
static const auto C11 = XS4GCR::PID(6, 11);
static const auto C12 = XS4GCR::PID(6, 12);

static const auto H_ISM = TARGET(TARGET::GasType::H);
static const auto He_ISM = TARGET(TARGET::GasType::He);

}  // namespace XS4GCR

#endif
