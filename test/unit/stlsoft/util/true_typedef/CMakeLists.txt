
if(X_CMAKE_CXX_FULLSTANDARD LESS 2011)

	list(APPEND X_GCC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED
		local-type-template-args
		unused-local-typedef
	)
endif()

define_automated_test_program(test.unit.stlsoft.util.true_typedef entry.cpp)
