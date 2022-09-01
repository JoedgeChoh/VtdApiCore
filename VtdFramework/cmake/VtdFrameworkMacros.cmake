option(CODE_COVERAGE_PERMITTED "Permit or forbid any kind of code coverage generation. Generation needs to be enabled explicitly." OFF)
option(CODE_COVERAGE_ENABLE_ALL "Enable coverage generation for all targets where possible and permited." ON)
if(${CODE_COVERAGE_PERMITTED})
    include("${CMAKE_CURRENT_LIST_DIR}/Modules/CodeCoverage.cmake")

    add_custom_target(CodeCoverageTargets)
    add_custom_target(ListCodeCoverageTargets
        COMMAND ${CMAKE_COMMAND} -E echo "List of available code coverage targets: \"$<TARGET_PROPERTY:CodeCoverageTargets,COVERAGE_TARGETS>\"")
endif()

macro(setup_defaults)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release)
endmacro()

macro(set_default_build_type)
    # Set a default build type
    if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
      message(STATUS "Setting build type to 'Debug'")
      set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
      set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
        "MinSizeRel" "RelWithDebInfo")
    endif()
endmacro()

###################################
#find_vires_dependencies
###################################
macro(find_vires_dependencies)
    if(NOT ViresDependencies_ROOT)
        #Look for Vires Dependencies in the typical locations
        set(VIRES_DEPENDENCIES_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/.." ${ARGN})

        find_file(ViresDependencies_ROOT "ViresDependencies" ${VIRES_DEPENDENCIES_PATHS} NO_DEFAULT_PATH CACHE)

        if(NOT ViresDependencies_ROOT)
            message(SEND_ERROR "ViresDependencies not found in the search paths: \"${VIRES_DEPENDENCIES_PATHS}\".")
        else()
            message(STATUS "Found ViresDependencies at ${ViresDependencies_ROOT}. Setting CMakeModule path.")
            set(CMAKE_MODULE_PATH "${ViresDependencies_ROOT}/CMakeModules;${CMAKE_MODULE_PATH}" CACHE PATH "CMakeModule Path" FORCE)
        endif()
    endif()
endmacro()

macro(find_vires_dependencies_optional)	
    message(STATUS "Found ViresDependencies_ROOT is ${ViresDependencies_ROOT}.")
    if(NOT ViresDependencies_ROOT)
        #Look for Vires Dependencies in the typical locations
        set(VIRES_DEPENDENCIES_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/.." ${ARGN})

        find_file(ViresDependencies_ROOT "ViresDependencies" ${VIRES_DEPENDENCIES_PATHS} NO_DEFAULT_PATH CACHE)

        if(ViresDependencies_ROOT)
            message(STATUS "Found ViresDependencies at ${ViresDependencies_ROOT}.")
        endif()
    endif()

    if(ViresDependencies_ROOT)
        set(CMAKE_MODULE_PATH "${ViresDependencies_ROOT}/CMakeModules;${CMAKE_MODULE_PATH}" CACHE PATH "CMakeModule Path")
    else()
        set(CMAKE_MODULE_PATH "${VtdFramework_ROOT}/cmake/Modules;${CMAKE_MODULE_PATH}" CACHE PATH "CMakeModule Path")
    endif()
endmacro()

###################################
# Macro to get a list of all subdirectories and store them in
# result.

# Usage:
# subdirlist(MY_RESULT ${SOME_DIRECTORY})
###################################
macro(subdirlist result curdir)
  file(GLOB children RELATIVE ${curdir} ${curdir}/*)
  set(dirlist "")
  foreach(child ${children})
    if(IS_DIRECTORY ${curdir}/${child})
      list(APPEND dirlist ${child})
    endif()
  endforeach()
  set(${result} ${dirlist})
endmacro()

macro(optionally_add_subdirs default_on)
    subdirlist(SUBDIRS ${CMAKE_CURRENT_LIST_DIR})

    get_filename_component(DIR_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)

    option(${DIR_NAME}_ENABLE_ALL "Add all subdirectories of ${DIR_NAME}. Overrides specific settings." ${default_on})

    foreach(SUBDIR ${SUBDIRS})
    if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/${SUBDIR}/CMakeLists.txt)
        option(${DIR_NAME}_ENABLE_${SUBDIR} "Add ${SUBDIR}" OFF)

        if(${${DIR_NAME}_ENABLE_ALL})
            set(${DIR_NAME}_ENABLE_${SUBDIR} ${${DIR_NAME}_ENABLE_ALL} CACHE BOOL "Compile Plugin ${SUBDIR}" FORCE)
        endif()

        if(${${DIR_NAME}_ENABLE_${SUBDIR}})
            add_subdirectory(${SUBDIR})
        endif()
    endif()
    endforeach()
endmacro()

###################################
# collect_source_files, recursively adds files
# listed in FileList.txt files. Descends into all subdirectories.
# to ${TARGET_NAME_}_SOURCE_LIST
###################################
function(collect_source_files TARGET_NAME_ DIR)

    file(GLOB_RECURSE LIST_FILES ${DIR}/FileList.txt)

    foreach(LIST_FILE ${LIST_FILES})
        list (APPEND ${TARGET_NAME_}_SOURCE_LIST ${LIST_FILE})
        get_filename_component(LIST_FILE_PATH ${LIST_FILE} PATH)
        file(STRINGS ${LIST_FILE} FILE_LIST)

        foreach(FILE_NAME ${FILE_LIST})
            string(STRIP "${FILE_NAME}" FILE_NAME)
            string(LENGTH "${FILE_NAME}" FILE_NAME_LEN)
            string(SUBSTRING "${FILE_NAME}" 0 1 FIRST_CHAR)
            if(${FILE_NAME_LEN} GREATER 0 AND NOT ${FIRST_CHAR} STREQUAL "#")
                list (APPEND ${TARGET_NAME_}_SOURCE_LIST ${LIST_FILE_PATH}/${FILE_NAME})
            endif()
        endforeach()
    endforeach()

    set(${TARGET_NAME_}_SOURCE_LIST "${${TARGET_NAME_}_SOURCE_LIST}" PARENT_SCOPE)
endfunction()

###################################
# Function to return revision of the given working directory.
# Only supports Subversion for now. Can be subverted by setting Vtd_IGNORE_REVISIONS to ON
#
# Sets the variable ${prefix}_REVISION.
###################################
function(get_cvs_revision wc_path prefix)
    if(NOT ViresDependencies_ROOT)
        # build outside of Vires environment
        set(${prefix}_REVISION 0 PARENT_SCOPE)
        set(${prefix}_LAST_CHANGED_REVISION 0 PARENT_SCOPE)
        return()
    endif()

    find_package(Subversion)

    if(Vtd_IGNORE_REVISIONS)
        message(STATUS "Vtd_IGNORE_REVISIONS set. Setting ${prefix}_REVISION and ${prefix}_LAST_CHANGED_REVISION to 0.")
        set(${prefix}_REVISION 0 PARENT_SCOPE)
        set(${prefix}_LAST_CHANGED_REVISION 0 PARENT_SCOPE)
    elseif(NOT SUBVERSION_FOUND)
        message(WARNING "Subversion client could not be found. Cannot reliably determine ${prefix}_REVISION, setting to 0.")
        set(${prefix}_REVISION 0 PARENT_SCOPE)
        set(${prefix}_LAST_CHANGED_REVISION 0 PARENT_SCOPE)
    else()        
        Subversion_WC_INFO("${wc_path}" "${prefix}" IGNORE_SVN_FAILURE)

        if(${${prefix}_WC_REVISION})
            set(${prefix}_REVISION ${${prefix}_WC_REVISION} PARENT_SCOPE)
            set(${prefix}_LAST_CHANGED_REVISION ${${prefix}_WC_LAST_CHANGED_REV} PARENT_SCOPE)
        else()
            set(${prefix}_REVISION 0 PARENT_SCOPE)
            set(${prefix}_LAST_CHANGED_REVISION 0 PARENT_SCOPE)
            message(WARNING "Subversion client caused an error. Cannot reliably determine ${prefix}_REVISION and ${prefix}_LAST_CHANGED_REVISION, setting to 0.")
        endif()
    endif()

endfunction()

###################################
# Create a version header from input file ${input_file}
# and copy it to ${generated_file}
#
# Does two iterations of configure_file to allow replacing of project name before project version.
#
# e.g.
# Resolve @@PROJECT_NAME@_VERSION@ -> @MyProject_VERSION@ -> 1.2.3
###################################
function(create_version_header input_file generated_file)
    get_filename_component(input_file "${input_file}" ABSOLUTE) #读取输入路径的文件名
    get_filename_component(generated_file "${generated_file}" ABSOLUTE)
    
    configure_file("${input_file}" "${generated_file}.1" @ONLY)
    configure_file("${generated_file}.1" "${generated_file}" @ONLY)
    file(REMOVE ${generated_file}.1)
endfunction()

#########
# Read version string from target file and store in ${VersionFileContent}
#########
function(parse_version_file input_file)
    file(STRINGS ${input_file} tempVersionString)
    string(STRIP ${tempVersionString} tempVersionString)
    set(VersionFileContent ${tempVersionString} PARENT_SCOPE)
endfunction()

#
# Create a custom build target for documentation if the input flag is set to true
#
macro(add_doxygen_target_with_flag target_name input_doxy_file target_doxy_file flag)
    find_package(Doxygen)
    if(DOXYGEN_FOUND)
        configure_file(${input_doxy_file} ${target_doxy_file} @ONLY)

        if(${flag})
            set(TARGET_GROUP ALL)
        else()
            unset(TARGET_GROUP)
        endif()

        add_custom_target( ${target_name}_Doc ${TARGET_GROUP}
            ${DOXYGEN_EXECUTABLE} ${target_doxy_file}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating ${target_name} documentation with Doxygen" VERBATIM
        )
    endif(DOXYGEN_FOUND)
endmacro()

#
# Create a custom build target for documentation, and a build option to add the target
# to ALL.
#
# The build target will be called ${target_name}_Doc
# The build option will be called ${target_name}_DOC
#
macro(add_doxygen_target target_name input_doxy_file target_doxy_file)
    find_package(Doxygen)
    if(DOXYGEN_FOUND)
        option(${target_name}_DOC "Build ${target_name} documentation." off)
        configure_file(${input_doxy_file} ${target_doxy_file} @ONLY)

        if(${${target_name}_DOC})
            set(TARGET_GROUP ALL)
            message("TARGET_GROUP is ${TARGET_GROUP}")
        else()
            unset(TARGET_GROUP)
        endif()

        add_custom_target( ${target_name}_Doc ${TARGET_GROUP}
            ${DOXYGEN_EXECUTABLE} ${target_doxy_file}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating ${target_name} documentation with Doxygen" VERBATIM
        )
    else(DOXYGEN_FOUND)
        message("Doxygen need to be installed to generate the doxygen documentation")
    endif(DOXYGEN_FOUND)
endmacro()

#
# Append ${suffix} to a list of strings (e.g. paths)
#
# Replacement for CMake 3.12+ LIST(TRANSFORM ... APPEND ...)
#
# Usage: list_append(OUTPUT "/some/suffix" ${INPUT})
function(list_append output_list suffix input_list)
   set(listVar "")

   foreach(elem ${input_list})
      list(APPEND listVar "${elem}${suffix}")
   endforeach()

   set(${output_list} "${listVar}" PARENT_SCOPE)
endfunction()

# If given target ${vires_target_name} does not exist:
#  - Look for a ${vires_project_name}/CMakeLists.txt in the path:
#    ${CMAKE_CURRENT_SOURCE_DIR}/.. and optional search paths.
#
# If the project is found:
#  - Add first found path to build using add_subdirectory.
#  - set ${vires_project_name}_ROOT to the given path.
#
#   Usage: find_internal_project(vires_target_name vires_project_name [PATHS])
#
macro(find_internal_project vires_target_name vires_project_name)
if(NOT TARGET ${vires_target_name})
    set(SEARCHPATH_LIST ${ARGN})
    list(APPEND SEARCHPATH_LIST ${CMAKE_CURRENT_SOURCE_DIR}/..) #default path

    list_append(SEARCHPATH_LIST "/${vires_project_name}" ${SEARCHPATH_LIST})

    find_path(${vires_project_name}_ROOT "CMakeLists.txt" PATHS
            ${SEARCHPATH_LIST}
            NO_DEFAULT_PATH)

    if(NOT ${vires_project_name}_ROOT)
        message(SEND_ERROR "${vires_project_name} not found in the search paths: \"${SEARCHPATH_LIST}\". Try to specify ${vires_project_name}_ROOT manually.")
    else()
        add_subdirectory(${${vires_project_name}_ROOT} ${CMAKE_BINARY_DIR}/${vires_project_name})
        message(STATUS "Found ${vires_project_name} in ${${vires_project_name}_ROOT}")
    endif()

endif()
endmacro()

macro(debug_output_var var)
    message(WARNING "[DEBUG] ${var}: \"${${var}}\"")
endmacro()

function(setup_coverage_for_target)
    set(options)
    set(oneValueArgs
        TARGET
    )
    set(multiValueArgs
        COVERAGE_EXECUTABLES # Define executable targets that are used for generating coverage data. e.g. Test executables.
    )
    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(NOT ${CODE_COVERAGE_PERMITTED})
        return()
    endif()

    set(option_name "CODE_COVERAGE_ENABLE_${ARG_TARGET}")
    option(${option_name} "Enable code coverage for target \"${ARG_TARGET}\"" OFF)

    if(${option_name} OR ${CODE_COVERAGE_ENABLE_ALL})
        # Enable coverage generation for the target
        set(flags "${COVERAGE_COMPILER_FLAGS}")
        string(REPLACE " " ";" flags "${flags}")

        target_compile_options(${ARG_TARGET} PRIVATE ${flags})
        target_link_libraries(${ARG_TARGET} PUBLIC gcov)

        # Create targets which drives the executables for generating coverage data
        foreach(exe "${ARG_COVERAGE_EXECUTABLES}")
            # Add custom target for coverage generation
            set(name ${ARG_TARGET}_CoverageDriver_${exe})
            setup_target_for_coverage_lcov(
                NAME ${name}
                EXCLUDE "/usr/*" "${VtdFramework_ROOT}/../ViresDependencies/*" "${CMAKE_BINARY_DIR}/*"
                EXECUTABLE $<TARGET_FILE:${exe}>)
            # Aggregate coverage targets for the super build which generates all coverage data
            set_property(TARGET CodeCoverageTargets APPEND PROPERTY COVERAGE_TARGETS ${name})
            add_dependencies(CodeCoverageTargets ${name})
        endforeach()
    endif()
endfunction()
