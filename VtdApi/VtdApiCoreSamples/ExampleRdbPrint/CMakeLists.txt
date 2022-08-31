cmake_minimum_required(VERSION 3.5)

project(ExampleRdbPrint)

find_package(VtdApi REQUIRED CONFIG PATHS "${VtdApi_ROOT}" "${CMAKE_CURRENT_SOURCE_DIR}/../../../VtdApi/cmake")

# set( ALL_SOURCES
#     main.cpp
#     ExampleRdbPrint.cpp)
# 
# add_executable(${PROJECT_NAME} ${ALL_SOURCES})
# target_compile_options(${PROJECT_NAME} PRIVATE -Wall $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wextra> -pedantic -Wconversion -Wno-deprecated)
# target_link_libraries (${PROJECT_NAME} VtdApiCore)





