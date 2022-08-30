
find_path(VtdApi_ROOT "CMakeLists.txt" PATHS "${CMAKE_CURRENT_LIST_DIR}/.." NO_DEFAULT_PATH)
if(EXISTS ${VtdApi_ROOT}/CMakeLists.txt)
    # Internal builds only.
    if(NOT TARGET VtdApiCore)
    	add_subdirectory(${VtdApi_ROOT} "${CMAKE_BINARY_DIR}/VtdApi")
    endif()
else()
    

    include(CMakeFindDependencyMacro)

    find_package(VtdFramework CONFIG REQUIRED PATHS "${VtdFramework_ROOT}" "${CMAKE_CURRENT_LIST_DIR}" "${CMAKE_CURRENT_LIST_DIR}/../../VtdFramework/cmake")

    include("${CMAKE_CURRENT_LIST_DIR}/VtdApiTargets.cmake")
    check_required_components("VtdApi")
endif()
