list(APPEND X_GCC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED
	deprecated-volatile
)

define_automated_test_program(test.component.unixstl.performance.processtimes_counter entry.cpp)
