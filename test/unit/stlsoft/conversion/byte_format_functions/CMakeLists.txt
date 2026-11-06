define_automated_test_program(test.unit.stlsoft.conversion.byte_format_functions entry.cpp)

# The same source, built with the sprintf()-based implementation of
# format_bytes() selected.
define_automated_test_program(test.unit.stlsoft.conversion.byte_format_functions.sprintf entry.cpp)

target_compile_definitions(test.unit.stlsoft.conversion.byte_format_functions.sprintf
	PRIVATE
		STLSOFT_CONVERSION_BYTE_FORMAT_FUNCTIONS_USE_SPRINTF
)
