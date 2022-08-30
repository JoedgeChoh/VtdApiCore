cmake_minimum_required(VERSION 3.5)

SET(TARGET VtdApiTest)

collect_source_files(${TARGET} ./src)

find_vires_dependencies_optional()

find_package(GTest REQUIRED)
find_package(Boost 1.63 REQUIRED)

add_executable(${TARGET} ${${TARGET}_SOURCE_LIST} )

target_link_libraries (${TARGET} PRIVATE
    VtdApiCore 
    GTest::GTest 
    GTest::Main 
    GMock::GMock 
    GMock::Main Boost::File 
    Boost::Chrono Boost::Thread)

add_test(NAME ${TARGET} COMMAND ${TARGET} --gtest_output=xml:${TARGET}TestResult.xml)
