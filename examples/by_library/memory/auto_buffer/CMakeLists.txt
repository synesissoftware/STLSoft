list(APPEND X_GCC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED
	unused-variable
)

list(APPEND X_MSVC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED
	4189
)

define_example_program(auto_buffer main.cpp)
