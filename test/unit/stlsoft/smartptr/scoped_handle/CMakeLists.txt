list(APPEND X_GCC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED
	unused-function
)

define_automated_test_program(test.unit.stlsoft.smartptr.scoped_handle entry.cpp)
add_subdirectory(test.unit.stlsoft.smartptr.scoped_handle.scoped_handle_cc)
if(CMAKE_CXX_COMPILER_ID STREQUAL "Borland" OR CMAKE_CXX_COMPILER_ID STREQUAL "Embarcadero")
	# Borland/Embarcadero-only scoped_handle
	add_subdirectory(test.unit.stlsoft.smartptr.scoped_handle.scoped_handle_borland)
endif()
