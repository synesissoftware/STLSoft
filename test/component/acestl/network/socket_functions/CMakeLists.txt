define_automated_test_program(test.component.acestl.network.socket_functions entry.cpp)

target_link_libraries(test.component.acestl.network.socket_functions
	ACE::ACE
)
