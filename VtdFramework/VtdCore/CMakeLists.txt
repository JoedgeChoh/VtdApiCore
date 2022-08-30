cmake_minimum_required(VERSION 3.5)

project(VtdCore VERSION ${VtdFramework_VERSION} LANGUAGES CXX)

set(TARGET VtdCore)

set(GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")

create_version_header("${CMAKE_CURRENT_LIST_DIR}/../cmake/Version.h.in" "${GENERATED_DIR}/inc/${TARGET}/Version.h")

# Dependencies
find_package(Boost 1.63 REQUIRED COMPONENTS thread chrono filesystem)
find_package(TinyXML REQUIRED)

collect_source_files(${TARGET} include)
collect_source_files(${TARGET} src/Common)
collect_source_files(${TARGET} src/${CMAKE_SYSTEM_NAME}) #platform specific code

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
    $<BUILD_INTERFACE:${GENERATED_DIR}/inc>  
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  
    $<INSTALL_INTERFACE:include>
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    option(USE_CXX11_ABI OFF "See GCC's libstdc++ Dual-ABI")
    target_compile_definitions(${TARGET} PUBLIC _GLIBCXX_USE_CXX11_ABI=$<BOOL:${USE_CXX11_ABI}>)
endif()

target_compile_options(${TARGET} PRIVATE -Wall $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wextra> -pedantic $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wconversion>)

target_compile_definitions(${TARGET} PUBLIC
    $<$<CONFIG:Debug>:VTD_DEBUG>
    $<$<PLATFORM_ID:Linux>:VTD_OS_LINUX>
    $<$<PLATFORM_ID:Windows>:VTD_OS_WINDOWS>
)

target_link_libraries( ${TARGET} PRIVATE
    $<$<PLATFORM_ID:Linux>:rt>
)

target_link_libraries(${TARGET} PUBLIC TinyXML::Static Boost::chrono Boost::filesystem Boost::thread)

## Documentation
set(VtdFramework_FILES "${VtdFramework_FILES} ${${TARGET}_SOURCE_LIST}" PARENT_SCOPE)

## Testing:
if(BUILD_TESTING AND VtdFramework_TEST)
    setup_coverage_for_target(
        TARGET ${TARGET}
        COVERAGE_EXECUTABLES ${TARGET}_TEST
    )

    add_subdirectory(test)
endif()

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
