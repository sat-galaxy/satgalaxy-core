cmake_minimum_required(VERSION 3.10)

project(glucose)
include(../cmake/config.cmake)

option(BUILD_SHARED_LIBS OFF "True for building shared object")

set(CMAKE_CXX_FLAGS "-std=c++11")

add_definitions(-DGALAXY_CORE)



# Basic Library
set(lib_srcs
    utils/Options.cc
    core/Solver.cc
    core/Solver.h
    external/glucose_port.cc
    core/lcm.cc
    simp/SimpSolver.cc)

message(${lib_srcs})




if(BUILD_SHARED_LIBS)
    set(lib_type "SHARED")
else()
    set(lib_type "STATIC")
endif()


include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR})


# base library
add_library(glucose ${lib_type} ${lib_srcs})


