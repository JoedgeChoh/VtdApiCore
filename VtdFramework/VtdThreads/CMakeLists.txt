cmake_minimum_required(VERSION 3.5)

project(VtdFramework VERSION ${VtdFramework_VERSION} LANGUAGES CXX)

set(TARGET VtdThreads)

find_package(Boost 1.63 REQUIRED system thread chrono filesystem)


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
)

target_include_directories(${TARGET} PUBLIC  
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  
    $<INSTALL_INTERFACE:include>
)

target_compile_options(${TARGET} PRIVATE -Wall $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wextra> -pedantic $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wconversion>)

if(Linux)
    target_link_libraries(${TARGET} PRIVATE pthread)
elseif(Win32)
    message(FATAL_ERROR "Windows is not yet supported.")
endif()

target_link_libraries(${TARGET} PUBLIC VtdCore $<$<PLATFORM_ID:Linux>:rt> Boost::thread Boost::chrono Boost::system )

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
