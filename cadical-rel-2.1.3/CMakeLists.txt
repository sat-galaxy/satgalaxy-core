cmake_minimum_required(VERSION 3.10)

project(cadical)
include(../cmake/config.cmake)


set(CMAKE_CXX_FLAGS "-std=c++11")

add_definitions(-DGALAXY_CORE -DVERSION="2.1.3" -DERRORJUMP)

include(CheckSymbolExists)

check_symbol_exists(putc_unlocked "stdio.h" HAVE_PUTC_UNLOCKED)
check_symbol_exists(isatty "unistd.h" HAVE_ISATTY)
check_symbol_exists(closefrom "unistd.h" HAVE_CLOSEFROM)

if(NOT HAVE_PUTC_UNLOCKED)
    add_definitions(-DNUNLOCKED)
endif()
if(NOT HAVE_ISATTY)
    add_definitions(-DNISATTY)
endif()
if(NOT HAVE_CLOSEFROM)
    add_definitions(-DNCLOSEFROM)
endif()


aux_source_directory(src LIB_SOURCES)

list(REMOVE_ITEM LIB_SOURCES
    "src/cadical.cpp"
    "src/mobical.cpp"
    "src/signal.cpp"
)
list(APPEND LIB_SOURCES
    "external/satgalaxy_cadical.cc"
)


include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src)


# base library
add_library(cadical STATIC ${LIB_SOURCES})
set_target_properties(cadical PROPERTIES OUTPUT_NAME "satgalaxy_cadical")

file(COPY external/ DESTINATION "${HEADER_OUTPUT_DIR}/satgalaxy"
     FILES_MATCHING PATTERN "*.h")
