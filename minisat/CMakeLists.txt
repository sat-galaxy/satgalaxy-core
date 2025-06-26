cmake_minimum_required(VERSION 3.10)

project(minisat)

#--------------------------------------------------------------------------------------------------
# Configurable options:

option(STATIC_BINARIES "Link binaries statically." ON)
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


if(CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    message(STATUS "Building for WebAssembly (Emscripten)")
    include(cmake/wasm.cmake)
else()
    message(STATUS "Building for native platform")
    include(cmake/native.cmake)
endif()

