define_automated_test_program(test.unit.winstl.memory.netapi_allocator entry.cpp)

if(WIN32)

	target_link_libraries(test.unit.winstl.memory.netapi_allocator
		netapi32
	)
endif()
