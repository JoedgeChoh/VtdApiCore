cmake_minimum_required(VERSION 3.5)

SET(TARGET UnitTestVtdToolkit)

collect_source_files(${TARGET} ./src)

add_executable(${TARGET} ${${TARGET}_SOURCE_LIST})

target_include_directories(${TARGET} PUBLIC ${CMAKE_SOURCE_DIR}/inc)

find_package(GTest REQUIRED)

target_compile_definitions(${TARGET} PUBLIC
    $<$<CONFIG:Debug>:VTD_DEBUG>
    $<$<PLATFORM_ID:Linux>:VTD_OS_LINUX>
    $<$<PLATFORM_ID:Windows>:VTD_OS_WINDOWS>
)

target_link_libraries (${TARGET} PRIVATE VtdToolkit GTest::GTest GTest::Main)

add_test(NAME ${TARGET} COMMAND ${TARGET} --gtest_output=xml:${TARGET}TestResult.xml)
