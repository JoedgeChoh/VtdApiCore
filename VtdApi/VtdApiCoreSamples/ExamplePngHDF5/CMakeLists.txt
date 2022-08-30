cmake_minimum_required(VERSION 3.5)


project(ExamplePngHDF5)

find_package(VtdApi REQUIRED CONFIG PATHS "${VtdApi_ROOT}" "${CMAKE_CURRENT_SOURCE_DIR}/../../../VtdApi/cmake")

if(NOT VtdFramework_USE_HDF5)
    message("VtdFramework_USE_HDF5 is OFF, cannot build ExamplePngHDF5. Set the correct directory of HDF5 package.")
    return()
endif()

if(NOT VtdFramework_USE_PNG)
    message("VtdFramework_USE_PNG is OFF, cannot build ExamplePngHDF5. Set the correct directory of PNG package.")
    return()
endif()

set(ALL_SOURCES main.cpp ExamplePngHDF5.cpp)


add_executable(${PROJECT_NAME} ${ALL_SOURCES})
target_compile_options(${PROJECT_NAME} PRIVATE -Wall $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wextra> -pedantic -Wconversion -Wno-deprecated)
target_link_libraries (${PROJECT_NAME} VtdApiCore)
