#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "VtdApiCore" for configuration "Debug"
set_property(TARGET VtdApiCore APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(VtdApiCore PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libVtdApiCore-d.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS VtdApiCore )
list(APPEND _IMPORT_CHECK_FILES_FOR_VtdApiCore "${_IMPORT_PREFIX}/lib/libVtdApiCore-d.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
