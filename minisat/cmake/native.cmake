
set(MINISAT_LIB_SOURCES
    minisat/utils/Options.cc
    minisat/core/Solver.cc
    minisat/external/minisat_port.cc
    minisat/simp/SimpSolver.cc)

add_library(minisat-lib-static STATIC ${MINISAT_LIB_SOURCES})
add_library(minisat-lib-shared SHARED ${MINISAT_LIB_SOURCES})


set_target_properties(minisat-lib-static PROPERTIES OUTPUT_NAME "minisat")
set_target_properties(minisat-lib-shared
  PROPERTIES
    OUTPUT_NAME "minisat" 
    VERSION ${MINISAT_VERSION}
    SOVERSION ${MINISAT_SOVERSION})


#--------------------------------------------------------------------------------------------------
# Installation targets:


    install(TARGETS minisat-lib-static minisat-lib-shared
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib)

    install(DIRECTORY minisat/mtl minisat/utils minisat/core minisat/simp minisat/external
            DESTINATION include/minisat
            FILES_MATCHING PATTERN "*.h")
