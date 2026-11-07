define_automated_test_program(test.unit.winstl.system.version_info entry.cpp)

if(WIN32)
	target_link_libraries(test.unit.winstl.system.version_info
		Version
	)
endif()
