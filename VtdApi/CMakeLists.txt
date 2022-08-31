cmake_minimum_required(VERSION 3.5)

file(STRINGS "Version" VersionFileContent)
message("STRINGS is ${VersionFileContent}")

project(VtdApi VERSION ${VersionFileContent} LANGUAGES CXX)
message("ProjectVersion is ${${PROJECT_NAME}_VERSION} ")
message("CMAKE_CURRENT_LIST_DIR is ${CMAKE_CURRENT_LIST_DIR}")
# message("VtdFramework_ROOT is ${VtdFramework_ROOT}")
find_package(VtdFramework CONFIG HINTS ${VtdFramewoVtdFramework_ROOTrk_ROOT} ${CMAKE_CURRENT_LIST_DIR}/../VtdFramework/cmake)
# 
# add_subdirectory(VtdApiCore)    
# 
# if(ENABLE_VtdApiCore_SAMPLES)
#     message(WARNING "ENABLE_VtdApiCore_SAMPLES will be ignored in future versions, use VtdApiCore_ENABLE_SAMPLES instead.")
#     option(VtdApiCore_ENABLE_SAMPLES "Build VtdApiCore Samples" ${ENABLE_VtdApiCore_SAMPLES})
# else()
#     option(VtdApiCore_ENABLE_SAMPLES "Build VtdApiCore Samples" OFF)
# endif()
# 
# if(VtdApiCore_ENABLE_SAMPLES)
#     add_subdirectory(VtdApiCoreSamples)
# endif()
# 
# include(CMakePackageConfigHelpers)
# 
# export(EXPORT VtdApi FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake")
# install(EXPORT VtdApi FILE ${PROJECT_NAME}Targets.cmake DESTINATION "cmake")
# install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake" DESTINATION "cmake")
# 
# write_basic_package_version_file(
#     "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake" COMPATIBILITY SameMajorVersion
# )
# configure_package_config_file(
#     "${CMAKE_CURRENT_LIST_DIR}/cmake/Config.cmake.in"
#     "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
#     INSTALL_DESTINATION "cmake"
# )
# 
# configure_file("cmake/Config.cmake.in" "${CMAKE_CURRENT_LIST_DIR}/cmake/VtdApiConfig.cmake" @ONLY)
# install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake" "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake" DESTINATION "cmake")
# 
# include(${CMAKE_CURRENT_LIST_DIR}/cmake/CPackConfig.cmake)
# include(CPack)
