cmake_minimum_required(VERSION 3.5)

project(VtdFramework VERSION ${VtdFramework_VERSION} LANGUAGES CXX)

set(TARGET VtdHdf5)

include_directories(/usr/include/hdf5/serial)
if(CMAKE_CXX_COMPILER_ID MATCHES GNU AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.8.1)
    option(VtdFramework_USE_HDF5 "Use HDF5" OFF)
    message("VtdHdf5 requires GCC 4.8.1 or higher.")
    return()
endif()

set(HDF5_USE_STATIC_LIBRARIES ON)
find_package(HDF5 COMPONENTS CXX HL)

if(HDF5_FOUND)
    option(VtdFramework_USE_HDF5 "Use HDF5" ON)
else()
    option(VtdFramework_USE_HDF5 "Use HDF5" OFF)
    message("VtdFramework_USE_HDF5 is switched off as HDF5 package is missing.")
endif() 
mark_as_advanced(VtdFramework_USE_HDF5)

if(NOT VtdFramework_USE_HDF5)
    message("VtdFramework_USE_HDF5 is switched off. VtdHDF5 is not built")
    return()
endif()

collect_source_files(${TARGET} src)
collect_source_files(${TARGET} include)

if(VtdFramework_BUILD_SHARED)
    add_library(${TARGET} SHARED ${${TARGET}_SOURCE_LIST})
else()
    add_library(${TARGET} STATIC ${${TARGET}_SOURCE_LIST})
    set_property(TARGET ${TARGET} PROPERTY POSITION_INDEPENDENT_CODE True)
endif()

set_target_properties(${TARGET} PROPERTIES
    VERSION ${PROJECT_VERSION}
    DEBUG_POSTFIX "-d"
    CXX_STANDARD "11"
    CXX_REQUIRED TRUE
)

#only supported for cmake 3.8+, TODO: Find which features are required by Hdf5
#target_compile_features(${TARGET} PUBLIC cxx_std_11)
target_include_directories(${TARGET} PUBLIC  
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  
    $<INSTALL_INTERFACE:include>
)

target_compile_options(${TARGET} PRIVATE -Wall $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wextra> -pedantic $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wconversion>)

target_compile_definitions(${TARGET} PUBLIC
    HDF_ENABLED
)

target_link_libraries(${TARGET} PRIVATE $<$<PLATFORM_ID:Linux>:rt>)
# target_link_libraries(${TARGET} PUBLIC VtdCore VtdToolkit VtdThreads hdf5::hdf5-static hdf5::hdf5_hl-static)
target_link_libraries(${TARGET} PUBLIC VtdCore VtdToolkit VtdThreads ${HDF5_LIBRARIES})

set(GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")

if(BUILD_TESTING AND VtdFramework_TEST)
    add_subdirectory(test)
endif()

## Documentation
set(VtdFramework_FILES "${VtdFramework_FILES} ${${TARGET}_SOURCE_LIST}" PARENT_SCOPE)

## package creation:
if(VtdFramework_INSTALL)
    install(TARGETS ${TARGET}
        EXPORT VtdFramework
        DESTINATION lib
    )
    install(DIRECTORY include/ DESTINATION include 
        FILES_MATCHING PATTERN "*.h"
        PATTERN ".svn" EXCLUDE
    )
endif()
