set(LIB_OUTPUT_DIR  ${CMAKE_CURRENT_BINARY_DIR}/lib)
# 设置所有配置的输出目录
foreach(config DEBUG RELEASE RELWITHDEBINFO MINSIZEREL)
    string(TOUPPER ${config} config_upper)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${config_upper} ${LIB_OUTPUT_DIR})
endforeach()