cmake_minimum_required(VERSION 3.5)

set(TARGET ExampleVtdEncryptionPlugin)

add_library(${TARGET} SHARED ExampleVtdEncryptionPlugin.cpp)

target_link_libraries(${TARGET} PUBLIC VtdEncryption OpenSSL::Crypto)

if("${USE_CXX11_ABI}" STREQUAL "ON")
    set(${TARGET}_SUFFIX ".so.cxx11")
else()
	set(${TARGET}_SUFFIX ".so.cxx98")
endif()

set_target_properties(${TARGET} PROPERTIES
    SUFFIX "${${TARGET}_SUFFIX}"
)

if(VtdFramework_TEST)

    find_package(GTest)
    if(GTest_FOUND OR TARGET GTest::GTest)
        add_executable(${TARGET}_Test ExampleVtdEncryptionPluginTest.cpp)

        target_link_libraries(${TARGET}_Test PRIVATE ${TARGET} GTest::GTest GTest::Main)

        add_test(NAME ${TARGET} COMMAND ${TARGET} --gtest_output=xml:${TARGET}TestResult.xml)
    endif()
endif()





