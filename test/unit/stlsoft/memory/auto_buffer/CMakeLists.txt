
if(MSVC)

	if(MSVC_VERSION LESS 1930)

		list(APPEND X_MSVC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED
			4702
		)
	endif()
endif(MSVC)

define_automated_test_program(test.unit.stlsoft.memory.auto_buffer entry.cpp)

