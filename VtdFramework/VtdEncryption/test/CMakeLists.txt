cmake_minimum_required(VERSION 3.5)

SET(TARGET VtdEncryption_Test)

add_executable(${TARGET} ./src/main.cpp ./src/VtdEncryptionTest.cpp)

target_include_directories(${TARGET} PUBLIC ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/inc)

find_package(GTest REQUIRED)

target_compile_definitions(${TARGET} PUBLIC
    $<$<CONFIG:Debug>:VTD_DEBUG>
    $<$<PLATFORM_ID:Linux>:VTD_OS_LINUX>
    $<$<PLATFORM_ID:Windows>:VTD_OS_WINDOWS>
)

target_link_libraries (${TARGET} PRIVATE VtdEncryption GTest::GTest GTest::Main)

add_test(NAME ${TARGET} COMMAND ${TARGET} --gtest_output=xml:${TARGET}TestResult.xml)
