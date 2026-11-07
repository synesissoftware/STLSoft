if(CMAKE_CXX_STANDARD LESS 17)
	# std::auto_ptr removed in C++17
	add_subdirectory(auto_ptr)
endif()
add_subdirectory(fundamental)
add_subdirectory(shared_ptr)
add_subdirectory(unique_ptr)
