define_automated_test_program(test.component.inetstl.network.connection entry.cpp)

target_link_libraries(test.component.inetstl.network.connection
	wininet
)
