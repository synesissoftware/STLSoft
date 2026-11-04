
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

	if(MFC_FOUND)

		# Includes <mfcstl/mfcstl.hpp> when **STLSOFT_HAS_MFC**.
		# Save/restore **CMAKE_MFC_FLAG** so later directories are
		# unaffected.
		set(_stlsoft_cmake_mfc_flag_save "${CMAKE_MFC_FLAG}")

		stlsoft_prepare_mfc_target()
	endif(MFC_FOUND)

	define_example_program(test.scratch.versions.format versions.cpp)

	if(MFC_FOUND)

		set(CMAKE_MFC_FLAG "${_stlsoft_cmake_mfc_flag_save}")
		unset(_stlsoft_cmake_mfc_flag_save)
	endif(MFC_FOUND)

	if(HAS_ACE)

		target_link_libraries(test.scratch.versions.format
			ACE::ACE
		)
	endif()

	if(HAS_woad)

		target_link_libraries(test.scratch.versions.format
			woad::woad
		)
	endif()
endif()

