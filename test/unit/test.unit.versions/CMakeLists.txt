define_automated_test_program(test.unit.versions entry.cpp)

if(HAS_ACE)

	target_link_libraries(test.unit.versions
		ACE::ACE
	)
endif()
