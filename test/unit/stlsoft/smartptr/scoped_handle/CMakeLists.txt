if(CMAKE_CXX_COMPILER_ID STREQUAL "Borland" OR CMAKE_CXX_COMPILER_ID STREQUAL "Embarcadero")
	# Borland/Embarcadero-only scoped_handle
	add_subdirectory(test.unit.stlsoft.smartptr.scoped_handle.scoped_handle_borland)
endif()
add_subdirectory(test.unit.stlsoft.smartptr.scoped_handle.scoped_handle_cc)
