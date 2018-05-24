project(D2XSECS Fortran C  CXX)
cmake_minimum_required(VERSION 2.8)

set( CMAKE_VERBOSE_MAKEFILE off )
set( CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" )
set( CMAKE_fortran_COMPILER "gfortran" )
get_filename_component (Fortran_COMPILER_NAME ${CMAKE_Fortran_COMPILER} NAME)
set( CMAKE_C_COMPILER "gcc" )
set( CMAKE_CXX_COMPILER "g++" )
set( CMAKE_CXX_FLAGS "-O2 -ftree-vectorize -std=c++11" )
set( D2XSEC_INCLUDES )
set( D2XSEC_LIBRARIES )

# download data files
message("-- Downloading data file from repository ~ 3 MB")
file(DOWNLOAD
        https://www.dropbox.com/s/rq11j6aqhuykxjd/data.tar.gz?dl=0
        ${CMAKE_BINARY_DIR}/data.tar.gz
        EXPECTED_MD5 e21706bf28af0504b0faae05c14b98cf)
message("-- Extracting data file")
execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf ${CMAKE_BINARY_DIR}/data.tar.gz WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

# include
include_directories( "${CMAKE_SOURCE_DIR}/include" )

# cparamlib (provided)
add_subdirectory(libs/cparamlib)
list(APPEND D2XSEC_LIBRARIES cparamlib)
list(APPEND D2XSEC_INCLUDES libs/cparamlib/include)

# fortran codes (provided)
add_subdirectory(libs/external_codes)
list(APPEND D2XSEC_LIBRARIES external_codes)

# GSL (external)
find_package(GSL)
if(GSL_FOUND)
    set(HAVE_LIBGSL 1)
    list(APPEND D2XSEC_INCLUDES ${GSL_INCLUDE_DIR})
    list(APPEND D2XSEC_LIBRARIES ${GSL_LIBRARIES})
else(GSL_FOUND)
    message(FATAL_ERROR "Require GSL: set GSL_HOME")
endif(GSL_FOUND)

# add source files
set( D2XSEC_SRCS
        src/d2xsec.cpp
        src/antiprotons.cpp
        src/decay.cpp
        src/grid.cpp
        src/inelastic.cpp
        src/leptons.cpp
        src/protons.cpp
        src/utilities.cpp
        src/TanNg83.cpp
        src/Tripathi99.cpp
        src/Duperray03.cpp
        src/DiMauro2015.cpp
        src/antiproton_tables.cpp
        )

# make library
include_directories (include ${D2XSEC_INCLUDES})
add_library( D2XSEC ${D2XSEC_SRCS} ${D2XSEC_INCLUDES} )

# make executables
add_executable(xsec_example1 examples/example1.cpp )
target_link_libraries (xsec_example1 D2XSEC ${D2XSEC_LIBRARIES})

add_executable(xsec_example2 examples/example2.cpp )
target_link_libraries (xsec_example2 D2XSEC ${D2XSEC_LIBRARIES})

add_executable(xsec_example3 examples/example3.cpp )
target_link_libraries (xsec_example3 D2XSEC ${D2XSEC_LIBRARIES})

# show summary
message (STATUS "CMAKE_SYSTEM .......... = ${CMAKE_SYSTEM}")
message (STATUS "BUILD_SHARED_LIBS ..... = ${BUILD_SHARED_LIBS}")
message (STATUS "CMAKE_CXX_COMPILER .... = ${CMAKE_CXX_COMPILER}")
message (STATUS "CMAKE_CXX_FLAGS ....... = ${CMAKE_CXX_FLAGS}")
message (STATUS "CMAKE_INCLUDE_PATH .... = ${CMAKE_INCLUDE_PATH}")
message (STATUS "D2XSEC_INCLUDES ....... = ${D2XSEC_INCLUDES}")
message (STATUS "D2XSEC_LIBRARIES ...... = ${D2XSEC_LIBRARIES}")
