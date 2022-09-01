cmake_minimum_required(VERSION 3.5)

file(STRINGS "Version" VersionFileContent)

project(VtdFramework VERSION ${VersionFileContent} LANGUAGES CXX)

include(cmake/VtdFrameworkMacros.cmake)

#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)

message("CMAKE_BINARY_DIR2 is ${CMAKE_BINARY_DIR}")
message("CMAKE_INSTALL_PREFIX is ${CMAKE_INSTALL_PREFIX}")
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install CACHE PATH "Overridden default install prefix" FORCE)
endif()
message("CMAKE_INSTALL_PREFIX  is overridden by ${CMAKE_INSTALL_PREFIX}")

set(VtdFramework_ROOT ${CMAKE_CURRENT_LIST_DIR})
set_default_build_type() # 设置默认cmake_build_type=debug
find_vires_dependencies_optional()
setup_defaults()  

include(CTest)

option(VtdFramework_INSTALL "Should VtdFramework be included in the install set" ON)
option(VtdFramework_BUILD_SHARED "Build shared libraries" OFF)
option(VtdFramework_TEST "Build Testing" OFF)
message("VtdFramework_INSTALL is ${VtdFramework_INSTALL}")
mark_as_advanced(VtdFramework_INSTALL) # 将已知变量标记为高级变量

add_subdirectory(VtdCore)
add_subdirectory(VtdMath)
add_subdirectory(VtdNetwork)
add_subdirectory(VtdToolkit)
add_subdirectory(VtdThreads)
add_subdirectory(VtdHdf5)
add_subdirectory(VtdCompression)  

option(VtdFramework_ENABLE_VtdEncryption "Should the VtdEncryption library be built" ON)
if(VtdFramework_ENABLE_VtdEncryption)
    add_subdirectory(VtdEncryption)  
endif()

## Documentation
set(DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/Documentation")
# 将读取文件信息中的“；”替换为空格作为doxygen模块的输入
string(REPLACE ";" " " DOXYGEN_INPUT "${VtdFramework_FILES}")
message("DOXYGEN_EXCLUDE is ${DOXYGEN_EXCLUDE}")
message("DOXYGEN_IMAGE_PATHS is ${DOXYGEN_IMAGE_PATHS}")
message("HTML_EXTRA_STYLESHEET is ${HTML_EXTRA_STYLESHEET}")
message("HTML_EXTRA_FILES is ${HTML_EXTRA_FILES}")
message("HTML_EXTRA_STYLESHEET is ${HTML_EXTRA_STYLESHEET}")
message("DOXYGEN_OUTPUT_DIRECTORY is ${DOXYGEN_OUTPUT_DIRECTORY}")

add_doxygen_target(VtdFramework "${VtdFramework_ROOT}/cmake/Doxyfile.in" ${DOXYGEN_OUTPUT_DIRECTORY}/VtdFrameworkDoxyfile)

## Deployment

if(VtdFramework_INSTALL)
    include(CMakePackageConfigHelpers)

    set(EXPORT_NAME VtdFramework)

    export(EXPORT ${EXPORT_NAME} FILE "${CMAKE_CURRENT_BINARY_DIR}/VtdFrameworkTargets.cmake")
    # 生成包的版本文件
    write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/VtdFrameworkConfigVersion.cmake" COMPATIBILITY SameMajorVersion
    )
    # 生成包的配置文件
    configure_package_config_file(
        "cmake/Config.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/VtdFrameworkConfig.cmake"
        INSTALL_DESTINATION "cmake"
    )
    message("CMAKE_CURRENT_LIST_DIR is ${CMAKE_CURRENT_LIST_DIR}")
    configure_file("cmake/Config.cmake.in" "${CMAKE_CURRENT_LIST_DIR}/cmake/VtdFrameworkConfig.cmake" @ONLY)

    # Install documentation (optional)
    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Documentation/html DESTINATION doc/${PROJECT_NAME} OPTIONAL
            PATTERN ".svn" EXCLUDE)
    
    install(EXPORT VtdFramework FILE VtdFrameworkTargets.cmake DESTINATION "cmake")
    install(FILES 
        "${CMAKE_CURRENT_BINARY_DIR}/VtdFrameworkMacros.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/VtdFrameworkConfig.cmake" 
        "${CMAKE_CURRENT_BINARY_DIR}/VtdFrameworkConfigVersion.cmake" 
    DESTINATION "cmake")


    include(${CMAKE_CURRENT_LIST_DIR}/cmake/CPackConfig.cmake)
    include(CPack)

#BEGIN: legacy, should be removed after all plugins use their own version headers, doxyfiles, etc.!
    configure_file("cmake/VtdFrameworkMacros.cmake" "${CMAKE_CURRENT_BINARY_DIR}/VtdFrameworkMacros.cmake" COPYONLY)
    configure_file("cmake/Version.h.in" "${CMAKE_CURRENT_BINARY_DIR}/cmake/Version.h.in" COPYONLY)
    configure_file("cmake/Doxyfile.in" "${CMAKE_CURRENT_BINARY_DIR}/cmake/Doxyfile.in" COPYONLY)
    configure_file("cmake/Config.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/cmake/Config.cmake.in" COPYONLY)
#END legacy

endif()

## Testing:
if(BUILD_TESTING AND VtdFramework_TEST)
    setup_coverage_for_target(
        TARGET ${TARGET}
        COVERAGE_EXECUTABLES ${TARGET}_TEST
    )

    enable_testing()
    add_subdirectory(test)
endif()
