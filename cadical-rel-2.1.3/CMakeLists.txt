cmake_minimum_required(VERSION 3.10)

project(cadical)


set(CMAKE_CXX_FLAGS "-std=c++11")

add_definitions(-DGALAXY_CORE -DVERSION="2.1.3" -DNBUILD)

include(CheckSymbolExists)

# set(CMAKE_REQUIRED_FLAGS "-D_GNU_SOURCE")
check_symbol_exists(putc_unlocked "stdio.h" HAVE_PUTC_UNLOCKED)
unset(CMAKE_REQUIRED_FLAGS)

if(NOT HAVE_PUTC_UNLOCKED)
    add_definitions(-DNUNLOCKED)
endif()


aux_source_directory(src LIB_SOURCES)

list(REMOVE_ITEM LIB_SOURCES
    "src/cadical.cpp" 
    "src/mobical.cpp"
    "src/signal.cpp"
)


include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src)


# base library
add_library(cadical STATIC ${LIB_SOURCES})
set_target_properties(cadical PROPERTIES OUTPUT_NAME "satgalaxy_cadical")

file(COPY external/ DESTINATION "${HEADER_OUTPUT_DIR}/satgalaxy"
     FILES_MATCHING PATTERN "*.h")