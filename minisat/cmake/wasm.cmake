 # 设置 Emscripten 输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/dist)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/dist)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/dist)
set(CMAKE_EXECUTABLE_SUFFIX ".js") # 编译生成.html

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_WEBGL2=1 -s WASM=1 -s EXPORTED_RUNTIME_METHODS=['ccall','cwrap']  -s MODULARIZE=1 -s ALLOW_MEMORY_GROWTH=1")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_WEBGL2=1 -s WASM=1")
# # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_WEBGL2=1 -s WASM=1 -s EXPORTED_RUNTIME_METHODS=['ccall','cwrap']")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --bind")

    # set(CMAKE_EXECUTABLE_SUFFIX ".js")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s EXPORT_ES6=1 -s MODULARIZE=1 -s WASM=1 -s EXPORT_NAME='minisat' --emit-tsd minisat-wasm.d.ts")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --bind")
# 禁用 PIE 选项 (Emscripten 需要)
set(CMAKE_POSITION_INDEPENDENT_CODE OFF)

# 定义 Emscripten 宏
add_definitions(-DEMSCRIPTEN)

set(MINISAT_WASM_LIB_SOURCES
    minisat/utils/Options.cc
    minisat/core/Solver.cc
    minisat/simp/SimpSolver.cc
    minisat/external/wasm.cc
    )
add_executable(minisat-wasm ${MINISAT_WASM_LIB_SOURCES})
set_target_properties(minisat-wasm PROPERTIES
        LINK_FLAGS "-s WASM=1 -s EXPORT_NAME='minisat' --emit-tsd minisat-wasm.d.ts"
    )