list(APPEND X_GCC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED
	uninitialized
)

define_example_program(sap_cast main.cpp)
