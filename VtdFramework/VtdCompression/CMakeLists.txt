cmake_minimum_required(VERSION 3.5)

project(VtdCompression VERSION ${VtdFramework_VERSION} LANGUAGES CXX)

set(TARGET VtdCompression)

find_package(Lz4)
if(NOT Lz4_FOUND)
    message("Lz4 library is not found. VtdCompression is not built.")
    return()
endif()

find_package(ZLIB)
if(NOT ZLIB_FOUND)
    message("ZLIB library is not found. VtdCompression is not built.")
    return()
endif()

collect_source_files(${TARGET} include)
collect_source_files(${TARGET} src)

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

target_link_libraries(${TARGET} PUBLIC Lz4::Lz4)
target_link_libraries(${TARGET} PUBLIC ZLIB::ZLIB)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    option(USE_CXX11_ABI OFF "See GCC's libstdc++ Dual-ABI")
    target_compile_definitions(${TARGET} PUBLIC _GLIBCXX_USE_CXX11_ABI=$<BOOL:${USE_CXX11_ABI}>)
endif()

target_compile_options(${TARGET} PRIVATE -Wall $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wextra> -pedantic $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wconversion>)


target_compile_definitions(${TARGET} PUBLIC
    $<$<CONFIG:Debug>:VTD_DEBUG>
)

target_link_libraries( ${TARGET} PUBLIC
    VtdCore
)

target_link_libraries( ${TARGET} PRIVATE
    $<$<PLATFORM_ID:Linux>:rt>
)

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
