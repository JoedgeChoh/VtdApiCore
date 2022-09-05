#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "VtdCore" for configuration "Debug"
set_property(TARGET VtdCore APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(VtdCore PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libVtdCore-d.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS VtdCore )
list(APPEND _IMPORT_CHECK_FILES_FOR_VtdCore "${_IMPORT_PREFIX}/lib/libVtdCore-d.a" )

# Import target "VtdMath" for configuration "Debug"
set_property(TARGET VtdMath APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(VtdMath PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libVtdMath-d.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS VtdMath )
list(APPEND _IMPORT_CHECK_FILES_FOR_VtdMath "${_IMPORT_PREFIX}/lib/libVtdMath-d.a" )

# Import target "VtdNetwork" for configuration "Debug"
set_property(TARGET VtdNetwork APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(VtdNetwork PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libVtdNetwork-d.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS VtdNetwork )
list(APPEND _IMPORT_CHECK_FILES_FOR_VtdNetwork "${_IMPORT_PREFIX}/lib/libVtdNetwork-d.a" )

# Import target "VtdToolkit" for configuration "Debug"
set_property(TARGET VtdToolkit APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(VtdToolkit PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libVtdToolkit-d.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS VtdToolkit )
list(APPEND _IMPORT_CHECK_FILES_FOR_VtdToolkit "${_IMPORT_PREFIX}/lib/libVtdToolkit-d.a" )

# Import target "VtdThreads" for configuration "Debug"
set_property(TARGET VtdThreads APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(VtdThreads PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libVtdThreads-d.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS VtdThreads )
list(APPEND _IMPORT_CHECK_FILES_FOR_VtdThreads "${_IMPORT_PREFIX}/lib/libVtdThreads-d.a" )

# Import target "VtdHdf5" for configuration "Debug"
set_property(TARGET VtdHdf5 APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(VtdHdf5 PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libVtdHdf5-d.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS VtdHdf5 )
list(APPEND _IMPORT_CHECK_FILES_FOR_VtdHdf5 "${_IMPORT_PREFIX}/lib/libVtdHdf5-d.a" )

# Import target "VtdCompression" for configuration "Debug"
set_property(TARGET VtdCompression APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(VtdCompression PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libVtdCompression-d.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS VtdCompression )
list(APPEND _IMPORT_CHECK_FILES_FOR_VtdCompression "${_IMPORT_PREFIX}/lib/libVtdCompression-d.a" )

# Import target "VtdEncryption" for configuration "Debug"
set_property(TARGET VtdEncryption APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(VtdEncryption PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libVtdEncryption-d.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS VtdEncryption )
list(APPEND _IMPORT_CHECK_FILES_FOR_VtdEncryption "${_IMPORT_PREFIX}/lib/libVtdEncryption-d.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
