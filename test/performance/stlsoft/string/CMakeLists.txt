if(X_CMAKE_CXX_FULLSTANDARD GREATER_EQUAL 2011)

	add_subdirectory(c_string)
	add_subdirectory(simple_string.compare)
	add_subdirectory(simple_string.op_eq)
	add_subdirectory(string_tokeniser)
	add_subdirectory(string_tokeniser.comparator)
endif()


# ############################## end of file ############################# #

