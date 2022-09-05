
find_path(VtdFramework_ROOT "CMakeLists.txt" PATHS "${CMAKE_CURRENT_LIST_DIR}/.." NO_DEFAULT_PATH)
if(EXISTS ${VtdFramework_ROOT}/CMakeLists.txt)
    # Internal builds only.
    if(NOT TARGET VtdCore)
    	add_subdirectory(${VtdFramework_ROOT} "${CMAKE_BINARY_DIR}/VtdFramework")
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

    include("${CMAKE_CURRENT_LIST_DIR}/VtdFrameworkMacros.cmake")

    find_vires_dependencies_optional()

    if(ViresDependencies_ROOT) #internal build
        if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
            set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install CACHE PATH "Overridden default install prefix" FORCE)
        endif()
    endif()

    find_package(Boost 1.63 REQUIRED COMPONENTS system thread chrono filesystem regex)
    # find_package(TinyXML REQUIRED)

    find_package(JPEG QUIET)
    if(JPEG_FOUND)
        option(VtdFramework_USE_JPEG "JPEG Support" ON)
    else()
        option(VtdFramework_USE_JPEG "JPEG Support" OFF)
        message("VtdFramework_USE_JPEG is switched off as JPEG package is missing.")
    endif()

    find_package(PNG QUIET)
    if(PNG_FOUND)
        option(VtdFramework_USE_PNG "Support PNG" ON)
    else()
        option(VtdFramework_USE_PNG "Support PNG" OFF)
        message("VtdFramework_USE_PNG is switched off as PNG package is missing.")
    endif()

    set(HDF5_USE_STATIC_LIBRARIES ON)
    find_package(HDF5 QUIET)
    if(HDF5_FOUND)
        option(VtdFramework_USE_HDF5 "Support HDF5" ON)
    else()
        option(VtdFramework_USE_HDF5 "Support HDF5" OFF)
        message("Build HDF5 is switched off as HDF5 package is missing.")
    endif()    

    include("${CMAKE_CURRENT_LIST_DIR}/VtdFrameworkTargets.cmake")
    check_required_components("VtdFramework")
endif()
