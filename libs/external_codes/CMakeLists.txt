cmake_minimum_required(VERSION 2.6)

#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(external_codes STATIC
    crosec94.f
    webber93.f
    silberger99.f
)

SET_TARGET_PROPERTIES(external_codes PROPERTIES COMPILE_FLAGS "-O2")
