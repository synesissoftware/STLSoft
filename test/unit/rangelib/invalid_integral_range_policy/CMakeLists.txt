# Apple Clang is not in RangeLib's recognised-compiler list.
list(APPEND X_GCC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED
	deprecated-declarations
)

define_automated_test_program(test.unit.rangelib.invalid_integral_range_policy entry.cpp)

# NOTE: because RangeLib is moribund, we force any compiler rather than
# expend the effort to add Apple Clang to RangeLib's recognised-compiler
# list
target_compile_definitions(test.unit.rangelib.invalid_integral_range_policy
	PRIVATE
		_STLSOFT_FORCE_ANY_COMPILER
)
