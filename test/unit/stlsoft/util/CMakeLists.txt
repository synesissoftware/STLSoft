add_subdirectory(bit_functions)
add_subdirectory(count_decimal_digits)
add_subdirectory(count_hexadecimal_digits)
if(X_CMAKE_CXX_FULLSTANDARD GREATER_EQUAL 2011)

	add_subdirectory(string_insertion)
endif()
add_subdirectory(string.snprintf)
add_subdirectory(string_switch)
add_subdirectory(true_typedef)

