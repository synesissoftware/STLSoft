define_automated_test_program(test.unit.winstl.performance.multimedia_counter entry.cpp)

if(WIN32)

	target_link_libraries(test.unit.winstl.performance.multimedia_counter
		winmm
	)
endif()
