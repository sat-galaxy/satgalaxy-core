cmake_minimum_required(VERSION 3.10)


add_executable(minisat_example minisat.cc)
include_directories(${HEADER_OUTPUT_DIR})
add_dependencies(minisat_example minisat)
target_link_libraries(minisat_example PRIVATE minisat)
add_custom_command(
    TARGET minisat_example
    POST_BUILD
    COMMAND $<TARGET_FILE:minisat_example>
    COMMENT "Running minisat_example after build"
)



