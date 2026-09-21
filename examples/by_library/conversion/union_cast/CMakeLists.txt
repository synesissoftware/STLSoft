
list(APPEND X_GCC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED
	uninitialized
	unused-variable
)

define_example_program(union_cast main.cpp)
