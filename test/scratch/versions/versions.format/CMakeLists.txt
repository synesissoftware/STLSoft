
# only for toolchains known to provide `std::format` (C++20 or later)
set(_has_std_format FALSE)

if(CMAKE_CXX_STANDARD GREATER_EQUAL 20)

	if(MSVC)

		# VS 2019 16.10
		if(MSVC_VERSION GREATER_EQUAL 1929)

			set(_has_std_format TRUE)
		endif()
	elseif(CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")

		# Xcode 16 (libc++ 17)
		if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 16)

			set(_has_std_format TRUE)
		endif()
	elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")

		if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 17)

			set(_has_std_format TRUE)
		endif()
	elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")

		if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 13)

			set(_has_std_format TRUE)
		endif()
	endif()
endif()

if(_has_std_format)

	define_example_program(test.scratch.versions.format versions.cpp)

	if(HAS_ACE)

		target_link_libraries(test.scratch.versions.format
			ACE::ACE
		)
	endif()
endif()

