#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "VtdApiCore" for configuration "Release"
set_property(TARGET VtdApiCore APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(VtdApiCore PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libVtdApiCore.so.2022.1.34890"
  IMPORTED_SONAME_RELEASE "libVtdApiCore.so.2022.1.34890"
  )

list(APPEND _IMPORT_CHECK_TARGETS VtdApiCore )
list(APPEND _IMPORT_CHECK_FILES_FOR_VtdApiCore "${_IMPORT_PREFIX}/lib/libVtdApiCore.so.2022.1.34890" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
