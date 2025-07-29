cmake_minimum_required(VERSION 3.10)

project(picosat)
include(../cmake/config.cmake)
option(USE_LOG "Add low level logging code" OFF)
option(USE_STATS "Enable expensive stats" OFF)
option(USE_TRACE "Enable trace generation" OFF)
include(CheckSymbolExists)
check_symbol_exists(getrusage "sys/resource.h" HAVE_GETRUSAGE)

if(NOT HAVE_GETRUSAGE)
    add_definitions(-DNGETRUSAGE)
endif()

if(USE_LOG)
    add_definitions(-DLOGGING)
endif()

if(USE_STATS)
    add_definitions(-DSTATS)
endif()

if(USE_TRACE)
    add_definitions(-DTRACE)
endif()


add_definitions(-DGALAXY_CORE -DERRORJMP)


set(LIB_SOURCES
    external/satgalaxy_picosat.c
    picosat.c)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR})



# base library
add_library(picosat STATIC ${LIB_SOURCES})
set_target_properties(picosat PROPERTIES OUTPUT_NAME "satgalaxy_picosat")

file(COPY external/ DESTINATION "${HEADER_OUTPUT_DIR}/satgalaxy"
     FILES_MATCHING PATTERN "*.h")
