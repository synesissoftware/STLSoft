define_example_program(test.scratch.versions.iostreams versions.cpp)

if(HAS_ACE)

	target_link_libraries(test.scratch.versions.iostreams
		ACE::ACE
	)
endif()
