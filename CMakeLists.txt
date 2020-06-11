project(XS4GCR Fortran C CXX)
cmake_minimum_required(VERSION 2.8)

set( CMAKE_VERBOSE_MAKEFILE off )
set( CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" )
set( CMAKE_fortran_COMPILER "gfortran" )
get_filename_component (Fortran_COMPILER_NAME ${CMAKE_Fortran_COMPILER} NAME)
set( CMAKE_C_COMPILER "gcc-9" )
set( CMAKE_CXX_COMPILER "g++-9" )
set( CMAKE_CXX_FLAGS "-O2 -ftree-vectorize -std=c++11" )
set( XS4GCR_INCLUDES )
set( XS4GCR_LIBRARIES )
option(BUILD_DOC "Build documentation" OFF)

# include
include_directories( "${CMAKE_SOURCE_DIR}/include" )

# cparamlib (provided)
add_subdirectory(libs/cparamlib)
list(APPEND XS4GCR_LIBRARIES cparamlib)
list(APPEND XS4GCR_INCLUDES libs/cparamlib/include)

# fortran codes (provided)
add_subdirectory(libs/external_codes)
list(APPEND XS4GCR_LIBRARIES external_codes)

# GSL (external)
find_package(GSL)
if(GSL_FOUND)
    set(HAVE_LIBGSL 1)
    list(APPEND XS4GCR_INCLUDES ${GSL_INCLUDE_DIR})
    list(APPEND XS4GCR_LIBRARIES ${GSL_LIBRARIES})
else(GSL_FOUND)
    message(FATAL_ERROR "Require GSL: set GSL_HOME")
endif(GSL_FOUND)

# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/doxygen/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")
	
	# note the option DOC to build the docs with make doc
	add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMENT "Generating API documentation with Doxygen" VERBATIM
	)
else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

# copy data files in build
file(GLOB XS4GCR_DATA "data/*.txt")
file(COPY ${XS4GCR_DATA} DESTINATION ${PROJECT_BINARY_DIR}/data)

# add source files
set( XS4GCR_SRCS
        src/antiprotons/antiproton_tables.cpp
        src/antiprotons/antiprotons.cpp
        src/antiprotons/DiMauro2015.cpp
        src/antiprotons/Duperray03.cpp
        src/antiprotons/TanNg83.cpp
        src/inelastic/inelastic.cpp
        src/inelastic/Tripathi99.cpp
        src/leptons/leptons.cpp
        src/spallation/Evoli2018.cpp
        src/spallation/fitting_functions.cpp
        src/spallation/ghost_tree.cpp
        src/spallation/spallation.cpp
        src/spallation/Webber2003_table.cpp
        src/decay.cpp
        src/grid.cpp
        src/protons.cpp
        src/utilities.cpp
        src/xs4gcr.cpp
        )

# make library
include_directories (include ${XS4GCR_INCLUDES})
add_library( XS4GCR ${XS4GCR_SRCS} ${XS4GCR_INCLUDES} )

# make executables
add_executable(xsec_inelastic examples/inelastic.cpp)
target_link_libraries (xsec_inelastic XS4GCR ${XS4GCR_LIBRARIES})

add_executable(xsec_secleptons examples/secleptons.cpp )
target_link_libraries (xsec_secleptons XS4GCR ${XS4GCR_LIBRARIES})

add_executable(xsec_secantiprotons examples/secantiprotons.cpp )
target_link_libraries (xsec_secantiprotons XS4GCR ${XS4GCR_LIBRARIES})

#add_executable(xsec_example4 examples/example4.cpp )
#target_link_libraries (xsec_example4 XS4GCR ${XS4GCR_LIBRARIES})

#add_executable(xsec_example5 examples/example5.cpp )
#target_link_libraries (xsec_example5 XS4GCR ${XS4GCR_LIBRARIES})

#add_executable(xsec_example6 examples/example6.cpp )
#target_link_libraries (xsec_example6 XS4GCR ${XS4GCR_LIBRARIES})

add_executable(sandbox examples/sandbox.cpp )
target_link_libraries (sandbox XS4GCR ${XS4GCR_LIBRARIES})

#add_executable(D2-table examples/D2-table.cpp )
#target_link_libraries (D2-table XS4GCR ${XS4GCR_LIBRARIES})

# show summary
message (STATUS "CMAKE_SYSTEM .......... = ${CMAKE_SYSTEM}")
message (STATUS "BUILD_SHARED_LIBS ..... = ${BUILD_SHARED_LIBS}")
message (STATUS "CMAKE_CXX_COMPILER .... = ${CMAKE_CXX_COMPILER}")
message (STATUS "CMAKE_CXX_FLAGS ....... = ${CMAKE_CXX_FLAGS}")
message (STATUS "CMAKE_INCLUDE_PATH .... = ${CMAKE_INCLUDE_PATH}")
message (STATUS "XS4GCR_INCLUDES ....... = ${XS4GCR_INCLUDES}")
message (STATUS "XS4GCR_LIBRARIES ...... = ${XS4GCR_LIBRARIES}")
