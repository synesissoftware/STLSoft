# SIS:AUTO_GENERATED: Remove this line if you edit the file, otherwise it will be overwritten
if(CMAKE_CXX_STANDARD LESS 17)
	# std::auto_ptr removed in C++17
	add_subdirectory(test.unit.stlsoft.shims.logical.is_null.std.auto_ptr)
endif()
add_subdirectory(test.unit.stlsoft.shims.logical.is_null.std.pointer)
add_subdirectory(test.unit.stlsoft.shims.logical.is_null.std.shared_ptr)
add_subdirectory(test.unit.stlsoft.shims.logical.is_null.std.unique_ptr)
