define_automated_test_program(test.component.unixstl.synch.tss_index entry.cpp)
target_compile_options(test.component.unixstl.synch.tss_index PRIVATE -pthread -Wno-deprecated-copy)
target_compile_definitions(test.component.unixstl.synch.tss_index PRIVATE _REENTRANT)
target_link_options(test.component.unixstl.synch.tss_index PRIVATE -pthread)
