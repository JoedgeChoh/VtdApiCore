cmake_minimum_required(VERSION 3.5)

set(TARGET ExampleVtdEncryption)
project(${TARGET})

if(NOT CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message("${TARGET} is only supported on Linux and will not be built.")
    return()
endif()

set(OPENSSL_USE_STATIC_LIBS FALSE)

find_package(OpenSSL COMPONENTS Crypto)
if(NOT OPENSSL_CRYPTO_LIBRARY)
    message("${TARGET} can not be built without OpenSSL and its Crypto component and will not be built.")
    return()
endif()



find_package(VtdFramework REQUIRED CONFIG PATHS "${VtdFramework_ROOT}" "${CMAKE_CURRENT_SOURCE_DIR}/../../../VtdFramework/cmake")


add_executable(${TARGET} main.cpp)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wextra> -pedantic -Wconversion -Wno-deprecated)

target_link_libraries(${TARGET} VtdEncryption)

add_subdirectory(ExampleVtdEncryptionPlugin)
add_dependencies(${TARGET} ExampleVtdEncryptionPlugin) #since we are not linking the plugin, but it still must be built.

configure_file(testFiles/test.xml ExampleVtdEncryptionPlugin/test.xml COPYONLY)
configure_file(testFiles/pub.pem ExampleVtdEncryptionPlugin/pub.pem COPYONLY)
configure_file(testFiles/demo.html ExampleVtdEncryptionPlugin/demo.html COPYONLY)
configure_file(testFiles/demo.html demo.html COPYONLY)
configure_file(testFiles/pub.pem pub.pem COPYONLY)
