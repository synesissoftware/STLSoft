define_automated_test_program(test.unit.rangelib.invalid_integral_range_policy entry.cpp)

# NOTE: because RangeLib is moribund, we force any compiler rather than
# expend the effort to add Apple Clang to RangeLib's recognised-compiler
# list
target_compile_definitions(test.unit.rangelib.invalid_integral_range_policy
	PRIVATE
		_STLSOFT_FORCE_ANY_COMPILER
)
