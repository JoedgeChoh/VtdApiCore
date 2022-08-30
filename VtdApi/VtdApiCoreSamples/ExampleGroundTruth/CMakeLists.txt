cmake_minimum_required(VERSION 3.7)


project(ExampleGroundTruth LANGUAGES CXX)


find_package(VtdApi REQUIRED CONFIG PATHS "${VtdApi_ROOT}" "${CMAKE_CURRENT_SOURCE_DIR}/../../../VtdApi/cmake")

if(NOT VtdFramework_USE_HDF5)
    message("VtdFramework_USE_HDF5 is OFF, cannot build GroundTruthExample. Set the correct directory of HDF5 package.")
    return()
endif()


find_package(Boost 1.63 REQUIRED COMPONENTS system filesystem thread chrono)



add_subdirectory(logfile)
add_subdirectory(imagewriter)
add_subdirectory(DataFilter)

set(ALL_SOURCES main.cpp RdbCallback.cpp Mode1.cpp)

add_executable(${PROJECT_NAME} ${ALL_SOURCES})

target_compile_options(${PROJECT_NAME} PRIVATE -Wall $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wextra> -pedantic -Wconversion -Wno-deprecated)

target_link_libraries (${PROJECT_NAME} VtdApiCore VtdCore $<$<BOOL:${VtdFramework_USE_HDF5}>:VtdHdf5> ${Boost_LIBRARIES} logfile imagewriter DataFilter)

target_include_directories( ${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/headers)
