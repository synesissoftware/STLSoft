list(APPEND X_MSVC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED
	4702
)
define_automated_test_program(test.component.winstl.filesystem.memory_map_functions.C entry.c)
