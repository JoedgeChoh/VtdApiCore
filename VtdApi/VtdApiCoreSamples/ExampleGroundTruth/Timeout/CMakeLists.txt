cmake_minimum_required(VERSION 3.7)

if(NOT TARGET VtdApiCore)
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../VtdApi/cmake")
    find_package(VtdApi REQUIRED)
    find_package(VtdFramework REQUIRED)
endif()

project(Timeout VERSION 1.0.0 LANGUAGES CXX)

set(ALL_SOURCES src/Timeout.cpp)

set_target_properties(${TARGET}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/test
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/test
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin
)

add_library(${PROJECT_NAME} STATIC ${ALL_SOURCES})

target_link_libraries (${PROJECT_NAME} VtdApiCore)

target_include_directories( ${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
