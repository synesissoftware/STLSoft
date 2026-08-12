# SIS:AUTO_GENERATED: Remove this line if you edit the file, otherwise it will be overwritten
define_automated_test_program(test.unit.platformstl.synch.C.atomic_functions entry.c)
if(UNIX)
	target_compile_options(test.unit.platformstl.synch.C.atomic_functions PRIVATE -pthread)
	target_compile_definitions(test.unit.platformstl.synch.C.atomic_functions PRIVATE _REENTRANT)
	target_link_options(test.unit.platformstl.synch.C.atomic_functions PRIVATE -pthread)
endif()
