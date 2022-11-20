
find_path(VtdApi_ROOT "CMakeLists.txt" PATHS "${CMAKE_CURRENT_LIST_DIR}/.." NO_DEFAULT_PATH)
if(EXISTS ${VtdApi_ROOT}/CMakeLists.txt)
    # Internal builds only.
    if(NOT TARGET VtdApiCore)
    	add_subdirectory(${VtdApi_ROOT} "${CMAKE_BINARY_DIR}/VtdApi")
    endif()
else()
    
####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was Config.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

    include(CMakeFindDependencyMacro)

    find_package(VtdFramework CONFIG REQUIRED PATHS "${VtdFramework_ROOT}" "${CMAKE_CURRENT_LIST_DIR}" "${CMAKE_CURRENT_LIST_DIR}/../../VtdFramework/cmake")

    include("${CMAKE_CURRENT_LIST_DIR}/VtdApiTargets.cmake")
    check_required_components("VtdApi")
endif()
