cmake_minimum_required(VERSION 2.6)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(cparamlib STATIC
    src/antinue.c
    src/antinumu.c
    src/elec.c
    src/gamma.c
    src/nue.c
    src/numu.c
    src/posi.c
    src/sigma.c
)

SET_TARGET_PROPERTIES(cparamlib PROPERTIES COMPILE_FLAGS "-O2")
