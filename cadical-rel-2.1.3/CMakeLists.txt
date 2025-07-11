cmake_minimum_required(VERSION 3.10)

project(cadical)


set(CMAKE_CXX_FLAGS "-std=c++11")

add_definitions(-DGALAXY_CORE -DVERSION="2.1.3")


aux_source_directory(src LIB_SOURCES)

list(REMOVE_ITEM LIB_SOURCES
    "src/cadical.cpp"
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src)


# base library
add_library(cadical STATIC ${LIB_SOURCES})
set_target_properties(cadical PROPERTIES OUTPUT_NAME "satgalaxy_cadical")

file(COPY external/ DESTINATION "${HEADER_OUTPUT_DIR}/satgalaxy"
     FILES_MATCHING PATTERN "*.h")