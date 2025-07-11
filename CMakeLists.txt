cmake_minimum_required(VERSION 3.10)
project(satgalaxy-core LANGUAGES CXX C)
include(cmake/config.cmake)


add_subdirectory(minisat)
add_subdirectory(glucose-4.2.1)
add_subdirectory(cadical-rel-2.1.3)
add_subdirectory(picosat-960)
add_subdirectory(examples)


