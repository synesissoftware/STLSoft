if(X_CMAKE_CXX_FULLSTANDARD GREATER_EQUAL 2011)

	if(UNIX)

		add_subdirectory(dl_call)
	endif(UNIX)
endif()
