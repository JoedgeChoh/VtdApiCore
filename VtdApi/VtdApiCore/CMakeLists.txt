cmake_minimum_required(VERSION 3.5)

project(VtdApiCore VERSION ${VtdApi_VERSION} LANGUAGES CXX)

set(TARGET VtdApiCore)

#Additional build settings
option(${TARGET}_BUILD_SHARED "Build as shared lib." OFF) #VtdApi builds as shared lib per default.
option(${TARGET}_TEST "Build unit tests" OFF)

collect_source_files(${TARGET} ./inc)
collect_source_files(${TARGET} ./src)

if(${TARGET}_BUILD_SHARED)
    add_library(${TARGET} SHARED ${${TARGET}_SOURCE_LIST})
else()
    add_library(${TARGET} STATIC ${${TARGET}_SOURCE_LIST})
    set_property(TARGET ${TARGET} PROPERTY POSITION_INDEPENDENT_CODE ON)
endif()

set(GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")

get_cvs_revision(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_NAME})
set(${TARGET}_VERSION_HEADER "${GENERATED_DIR}/inc/${TARGET}/Version.h")
create_version_header("${VtdFramework_ROOT}/cmake/Version.h.in" ${${TARGET}_VERSION_HEADER})

target_include_directories(${TARGET} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>  
    $<BUILD_INTERFACE:${GENERATED_DIR}/inc>
    $<INSTALL_INTERFACE:include>
)

set_target_properties(${TARGET} PROPERTIES
    VERSION ${PROJECT_VERSION}
    DEBUG_POSTFIX "-d"
)

target_compile_options(${TARGET} PRIVATE -Wall $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wextra> -pedantic -Wconversion)

target_link_libraries(${TARGET} PUBLIC
    VtdCore VtdToolkit VtdMath VtdNetwork VtdThreads
)

## Documentation
set(DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/Documentation")
string(REPLACE ";" " " DOXYGEN_INPUT "${${TARGET}_SOURCE_LIST};${${TARGET}_VERSION_HEADER}")
set(DOXYGEN_EXCLUDE "${CMAKE_CURRENT_LIST_DIR}/inc/sigslot/sigslot.h")
set(DOXYGEN_IMAGE_PATHS ${CMAKE_CURRENT_LIST_DIR}/Documentation/images)
add_doxygen_target(${TARGET} "${VtdFramework_ROOT}/cmake/Doxyfile.in" ${GENERATED_DIR}/${TARGET}Doxyfile)

## package creation:

install(TARGETS ${TARGET}
    EXPORT VtdApi
    ARCHIVE DESTINATION lib 
    LIBRARY DESTINATION lib
)
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Documentation/html DESTINATION doc/${PROJECT_NAME} OPTIONAL)
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Documentation/images DESTINATION doc/${PROJECT_NAME} OPTIONAL)
install(DIRECTORY inc/ DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)
install(FILES ${${TARGET}_VERSION_HEADER} DESTINATION include)

if(${TARGET}_TEST)
   setup_coverage_for_target(
        TARGET ${TARGET}
        COVERAGE_EXECUTABLES VtdApiTest
    )

    enable_testing()
    add_subdirectory(test)
endif()

