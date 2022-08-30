cmake_minimum_required(VERSION 3.5)

SET(TARGET VtdCompression_Test)

collect_source_files(${TARGET} ./src)

add_executable(${TARGET} ${${TARGET}_SOURCE_LIST})

target_include_directories(${TARGET} PUBLIC ${CMAKE_SOURCE_DIR}/inc)

find_package(GTest REQUIRED)

target_link_libraries (${TARGET} PRIVATE GTest::GTest GTest::Main VtdCompression)

add_test(NAME ${TARGET} COMMAND ${TARGET} --gtest_output=xml:${TARGET}TestResult.xml)
