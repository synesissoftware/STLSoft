define_automated_test_program(test.unit.platformstl.synch.atomic_functions.C entry.c)
if(UNIX)

	target_compile_options(test.unit.platformstl.synch.atomic_functions.C PRIVATE -pthread)
	target_compile_definitions(test.unit.platformstl.synch.atomic_functions.C PRIVATE _REENTRANT)
	target_link_options(test.unit.platformstl.synch.atomic_functions.C PRIVATE -pthread)
endif()


# ############################## end of file ############################# #

