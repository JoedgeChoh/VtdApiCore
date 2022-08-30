cmake_minimum_required(VERSION 3.5)

SET(TARGET VtdFramework_TEST)

collect_source_files(${TARGET} src)

add_executable(${TARGET} ${${TARGET}_SOURCE_LIST})

find_package(GTest REQUIRED)

target_include_directories(${TARGET} PRIVATE
    src
    ../inc
    ../src
)

target_link_libraries (${TARGET} PRIVATE
    GTest::GTest GTest::Main
    )

add_test(NAME ${TARGET} COMMAND ${TARGET} --gtest_output=xml:${TARGET}TestResult.xml)
