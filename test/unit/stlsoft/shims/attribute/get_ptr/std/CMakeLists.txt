# SIS:AUTO_GENERATED: Remove this line if you edit the file, otherwise it will be overwritten
if(CMAKE_CXX_STANDARD LESS 17)
	# std::auto_ptr removed in C++17
	add_subdirectory(test.unit.stlsoft.shims.attribute.get_ptr.std.auto_ptr)
endif()
add_subdirectory(test.unit.stlsoft.shims.attribute.get_ptr.std.fundamental)
add_subdirectory(test.unit.stlsoft.shims.attribute.get_ptr.std.shared_ptr)
add_subdirectory(test.unit.stlsoft.shims.attribute.get_ptr.std.unique_ptr)
