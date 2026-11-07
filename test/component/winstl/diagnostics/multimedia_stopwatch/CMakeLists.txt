define_automated_test_program(test.component.winstl.diagnostics.multimedia_stopwatch entry.cpp)

if(WIN32)

	target_link_libraries(test.component.winstl.diagnostics.multimedia_stopwatch
		winmm
	)
endif()
