
if(X_CMAKE_CXX_FULLSTANDARD GREATER_EQUAL 2011)

	add_subdirectory(atomic_functions)
	add_subdirectory(spin_mutex)
endif()
