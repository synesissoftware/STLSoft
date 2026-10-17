list(APPEND X_GCC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED
	missing-field-initializers
)

define_example_program(test.scratch.stlsoft.member_selector_view main.cpp)
