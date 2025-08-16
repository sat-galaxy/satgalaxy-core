cmake_minimum_required(VERSION 3.10)

project(cadical)
include(../cmake/config.cmake)

set(CMAKE_CXX_STANDARD 11)



if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wno-error=date-time)
endif()

set(LIB_SOURCES
    "external/satgalaxy_cadical.cc"
    "src/solver.cpp"
    "src/internal.cpp"
    "src/external.cpp"
    "src/message.cpp"
    "src/report.cpp"
    "src/lookahead.cpp"
    "src/decompose.cpp"
    "src/clause.cpp"
    "src/collect.cpp"
    "src/propagate.cpp"
    "src/decide.cpp"
    "src/var.cpp"
    "src/proof.cpp"
    "src/arena.cpp"
    "src/analyze.cpp"
    "src/flags.cpp"
    "src/extend.cpp"
    "src/external_propagate.cpp"
    "src/minimize.cpp"
    "src/shrink.cpp"
    "src/reap.cpp"
    "src/solution.cpp"
    "src/ema.cpp"
    "src/probe.cpp"
    "src/deduplicate.cpp"
    "src/ternary.cpp"
    "src/watch.cpp"
    "src/config.cpp"
    "src/contract.cpp"
    "src/options.cpp"
    "src/version.cpp"
    "src/limit.cpp"
    "src/assume.cpp"
    "src/constrain.cpp"
    "src/lratbuilder.cpp"
    "src/stats.cpp"
    "src/queue.cpp"
    "src/score.cpp"
    "src/backtrack.cpp"
    "src/restart.cpp"
    "src/elim.cpp"
    "src/subsume.cpp"
    "src/instantiate.cpp"
    "src/flip.cpp"
    "src/rephase.cpp"
    "src/backward.cpp"
    "src/condition.cpp"
    "src/averages.cpp"
    "src/gates.cpp"
    "src/block.cpp"
    "src/phases.cpp"
    "src/reduce.cpp"
    "src/compact.cpp"
    "src/walk.cpp"
    "src/lucky.cpp"
    "src/util.cpp"
    "src/restore.cpp"
    "src/checker.cpp"
    "src/occs.cpp"
    "src/cover.cpp"
    "src/bins.cpp"
    "src/vivify.cpp"
    "src/transred.cpp"
    "src/lratchecker.cpp"
)



include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src)


# base library
add_library(cadical STATIC ${LIB_SOURCES})
target_compile_definitions(cadical PRIVATE -DVERSION="2.1.3"  -DQUIET -DNTRACING)

set_target_properties(cadical PROPERTIES OUTPUT_NAME "satgalaxy_cadical")

file(COPY external/ DESTINATION "${HEADER_OUTPUT_DIR}/satgalaxy"
     FILES_MATCHING PATTERN "*.h")
