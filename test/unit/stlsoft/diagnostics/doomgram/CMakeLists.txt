
if(CMAKE_COMPILER_IS_GNUCC AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "13.0")
	list(APPEND X_GCC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED
		maybe-uninitialized
	)
endif()

define_automated_test_program(test.unit.stlsoft.diagnostics.doomgram entry.cpp)

