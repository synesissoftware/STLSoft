define_example_program(test.scratch.versions.stdio versions.c)

if(HAS_woad)

	target_link_libraries(test.scratch.versions.stdio
		woad::woad
	)
endif()

if(xTests_FOUND)

	target_link_libraries(test.scratch.versions.stdio
		xTests::core
	)
endif()
