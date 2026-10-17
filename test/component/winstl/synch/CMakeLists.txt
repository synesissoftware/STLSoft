add_subdirectory(test.component.winstl.synch.atomic_functions.C)
add_subdirectory(test.component.winstl.synch.process_mutex)

if(X_CMAKE_CXX_FULLSTANDARD GREATER_EQUAL 2011)

	add_subdirectory(atomic_functions)
	add_subdirectory(spin_mutex)
endif()
