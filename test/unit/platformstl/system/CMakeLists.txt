add_subdirectory(commandline_parser)
add_subdirectory(console_functions)
add_subdirectory(console_functions.C)
# unixstl::pid_sequence is Linux/macOS only. Under UNIXem, PlatformSTL selects
# the UNIX arm but those OS APIs are absent — skip on that cell only.
if(NOT USE_UNIXEM)

	add_subdirectory(pid_sequence)
endif()
