cmake_minimum_required(VERSION 3.10)

project(picosat)
include(../cmake/config.cmake)

set(CMAKE_CXX_FLAGS "-std=c++11")

add_definitions(-DGALAXY_CORE)


set(LIB_SOURCES
    external/satgalaxy_picosat.c
    picosat.c)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR})

if(WIN32)
    add_definitions(-DNGETRUSAGE -DNALLSIGNALS)
endif(WIN32)


# base library
add_library(picosat STATIC ${LIB_SOURCES})
set_target_properties(picosat PROPERTIES OUTPUT_NAME "satgalaxy_picosat")

file(COPY external/ DESTINATION "${HEADER_OUTPUT_DIR}/satgalaxy"
     FILES_MATCHING PATTERN "*.h")
