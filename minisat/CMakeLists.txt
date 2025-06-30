cmake_minimum_required(VERSION 3.10)

project(minisat)
include(../cmake/config.cmake)

#--------------------------------------------------------------------------------------------------
# Configurable options:

option(USE_SORELEASE   "Use SORELEASE in shared library filename." ON)


#--------------------------------------------------------------------------------------------------
# Library version:

set(MINISAT_SOMAJOR   2)
set(MINISAT_SOMINOR   2)
set(MINISAT_SORELEASE 0)

# Compute VERSION and SOVERSION:
if (USE_SORELEASE)
  set(MINISAT_VERSION ${MINISAT_SOMAJOR}.${MINISAT_SOMINOR}.${MINISAT_SORELEASE})
else()
  set(MINISAT_VERSION ${MINISAT_SOMAJOR}.${MINISAT_SOMINOR})
endif()
set(MINISAT_SOVERSION ${MINISAT_SOMAJOR})



#--------------------------------------------------------------------------------------------------
# Dependencies:

include_directories(${minisat_SOURCE_DIR})


#--------------------------------------------------------------------------------------------------
# Compile flags:

add_definitions(-D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS)


#--------------------------------------------------------------------------------------------------
# Build Targets:


set(MINISAT_LIB_SOURCES
    minisat/utils/Options.cc
    minisat/core/Solver.cc
    minisat/external/satgalaxy_minisat.cc
    minisat/simp/SimpSolver.cc)

add_library(minisat STATIC ${MINISAT_LIB_SOURCES})


set_target_properties(minisat PROPERTIES OUTPUT_NAME "satgalaxy_minisat")

file(COPY minisat/external/ DESTINATION "${HEADER_OUTPUT_DIR}/satgalaxy"
     FILES_MATCHING PATTERN "*.h")
