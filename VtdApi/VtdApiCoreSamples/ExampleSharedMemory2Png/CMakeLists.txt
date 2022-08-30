cmake_minimum_required(VERSION 3.5)

project(ExampleSharedMemory2Png)



find_package(VtdApi REQUIRED CONFIG PATHS "${VtdApi_ROOT}" "${CMAKE_CURRENT_SOURCE_DIR}/../../../VtdApi/cmake")


if(NOT VtdFramework_USE_PNG)
    message("VtdFramework_USE_PNG is OFF, cannot build ExampleSharedMemory2Png. Set the correct directory of PNG package.")
    return()
endif()

if(NOT VtdFramework_USE_JPEG)
    message("VtdFramework_USE_JPEG is OFF, cannot build ExampleSharedMemory2Png. Set the correct directory of JPEG package.")
    return()
endif()

set(ALL_SOURCES main.cpp)

add_executable(ExampleSharedMemory2Png ${ALL_SOURCES})
target_compile_options(${PROJECT_NAME} PRIVATE -Wall $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wextra> -pedantic -Wconversion -Wno-deprecated)
target_link_libraries(ExampleSharedMemory2Png VtdApiCore)
