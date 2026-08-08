define_automated_test_program(test.component.unixstl.synch.process_mutex entry.cpp)
target_compile_options(test.component.unixstl.synch.process_mutex PRIVATE -pthread)
target_compile_definitions(test.component.unixstl.synch.process_mutex PRIVATE _REENTRANT)
target_link_options(test.component.unixstl.synch.process_mutex PRIVATE -pthread)
