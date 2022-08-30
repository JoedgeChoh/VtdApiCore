cmake_minimum_required(VERSION 3.5)

project(VtdFramework VERSION ${VtdFramework_VERSION} LANGUAGES CXX)

set(TARGET VtdToolkit)

collect_source_files(${TARGET} src/Common)
collect_source_files(${TARGET} src/${CMAKE_SYSTEM_NAME}) #platform specific code
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
)

target_include_directories(${TARGET} PUBLIC  
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  
    $<INSTALL_INTERFACE:include>
)

find_package(PNG 1.5)
if(PNG_FOUND)
    option(VtdFramework_USE_PNG "" ON)
else()
    option(VtdFramework_USE_PNG "" OFF)
    message("Couldn't find PNG package version => 1.5.")
endif()

if(VtdFramework_USE_PNG)
    target_link_libraries(${TARGET} PUBLIC PNG::PNG)
    target_compile_definitions(${TARGET} PUBLIC PNG_ENABLED)
else()
    message("PNG features are turned off.")
endif()

        
find_package(JPEG 62)
if(JPEG_FOUND)    
    option(VtdFramework_USE_JPEG "" ON)
else()
    option(VtdFramework_USE_JPEG "" OFF)
    message("Couldn't find JPEG package. JPEG features are turned off.")
endif()

if(VtdFramework_USE_JPEG)
    if(NOT TARGET JPEG::JPEG)
        add_library(JPEG::JPEG UNKNOWN IMPORTED)
        set_target_properties(JPEG::JPEG PROPERTIES
            IMPORTED_LOCATION "${JPEG_LIBRARIES}"
            INTERFACE_INCLUDE_DIRECTORIES "${JPEG_INCLUDE_DIR}"
        )
    endif()
    target_link_libraries(${TARGET} PUBLIC JPEG::JPEG)    
    target_compile_definitions(${TARGET} PUBLIC JPEG_ENABLED)
else()
    message("JPEG features are turned off.")
endif()

target_compile_options(${TARGET} PRIVATE -Wall $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wextra> -pedantic $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wconversion>)

if(Linux)
    target_link_libraries(${TARGET} PRIVATE pthread)
elseif(Win32)
    message(FATAL_ERROR "Windows is not yet supported.")
endif()

find_package(Boost 1.63 REQUIRED COMPONENTS system filesystem thread chrono REQUIRED)

target_link_libraries(${TARGET} PUBLIC VtdCore)

target_link_libraries(${TARGET} PRIVATE Boost::system Boost::filesystem Boost::thread Boost::chrono)

#TODO: Due to circular dependencies this is being deactivated for now, and will be replaced by a better solution later on.
#TODO: To write images into HDF files please use the WriteHdf5Image class from VtdHdf5 directly
#if(VtdFramework_USE_HDF5) # VtdHdf5 and Hdf5 Libraries don't compile on GCC 4.4.1 and below
#    target_link_libraries(${TARGET} PRIVATE VtdHdf5)
#endif()

if(BUILD_TESTING AND VtdFramework_TEST)
    setup_coverage_for_target(
        TARGET ${TARGET}
        COVERAGE_EXECUTABLES ${TARGET}_TEST
    )

    add_subdirectory(test)
endif()

set(GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")

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

