


# Apply MFC link settings for targets created in the current directory
# scope. Call before define_automated_test_program /
# define_example_program when the target includes MFC headers.
# **CMAKE_MFC_FLAG** is read at add_executable() time (Visual Studio
# generators); **_AFXDLL** is required for shared MFC on Make/Ninja+cl
# as well.
macro(stlsoft_prepare_mfc_target)

	if(NOT MFC_FOUND)

		message(FATAL_ERROR "stlsoft_prepare_mfc_target() requires MFC_FOUND")
	endif()

	set(CMAKE_MFC_FLAG ${STLSOFT_MFC_FLAG})

	if(STLSOFT_MFC_SHARED)

		add_compile_definitions(_AFXDLL)
	endif()
endmacro(stlsoft_prepare_mfc_target)


function(define_automated_test_program program_name entry_point_source_name)

	add_executable(${program_name}
		${entry_point_source_name}
	)

	# Prefer this tree's headers over any installed STLSoft. On Apple Clang,
	# /usr/local/include is searched before -isystem paths, so includes that
	# arrive only via imported deps (e.g. xTests) can otherwise shadow us.
	set_property(TARGET ${program_name} PROPERTY NO_SYSTEM_FROM_IMPORTED TRUE)
	target_include_directories(${program_name}
		BEFORE PRIVATE
			${CMAKE_SOURCE_DIR}/include
	)

	target_link_libraries(${program_name}
		$<$<BOOL:${cstring_FOUND}>:cstring::core>
		$<$<BOOL:${shwild_FOUND}>:shwild::core>
		$<$<BOOL:${UNIXem_FOUND}>:UNIXem::UNIXem>
		$<$<BOOL:${xTests_FOUND}>:xTests::core>
	)

	if(WIN32)

		target_link_libraries(${program_name}
			ws2_32
			wsock32
		)
	endif()

	# Automated tests always link xTests (C++). Use the C++ driver so a
	# C-only compiler such as TinyCC is not invoked as the linker.
	set_property(TARGET ${program_name} PROPERTY LINKER_LANGUAGE CXX)

	set(X_GCC_CUSTOM_WARNINGS_ "")

	if(X_GCC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED)
		foreach(warning ${X_GCC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED})

			list(APPEND X_GCC_CUSTOM_WARNINGS_ "-Wno-${warning}")
		endforeach()
	endif()

	set(X_MSVC_CUSTOM_WARNINGS_ "")

	if(X_MSVC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED)
			foreach(warning ${X_MSVC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED})

					list(APPEND X_MSVC_CUSTOM_WARNINGS_ "/wd${warning}")
			endforeach()
	endif()

	target_compile_options(${program_name}
		PRIVATE
			$<$<OR:$<COMPILE_LANG_AND_ID:C,GNU,Clang,AppleClang>,$<COMPILE_LANG_AND_ID:CXX,GNU,Clang,AppleClang>>:
				-Werror -Wall -Wextra -pedantic

				${GCC_WARN_NO_cxx11_long_long}
				${X_GCC_CUSTOM_WARNINGS_}
			>
			$<$<COMPILE_LANG_AND_ID:CXX,Clang,AppleClang>:
				-Wno-unused-lambda-capture
			>
			$<$<COMPILE_LANG_AND_ID:C,TinyCC>:
				-Wall
			>
			$<$<OR:$<COMPILE_LANG_AND_ID:C,MSVC>,$<COMPILE_LANG_AND_ID:CXX,MSVC>>:
				/WX /W4

				${X_MSVC_CUSTOM_WARNINGS_}
			>
	)
endfunction(define_automated_test_program)


function(define_example_program program_name entry_point_source_name)

	add_executable(${program_name}
		${entry_point_source_name}
	)

	# Prefer this tree's headers over any installed STLSoft. On Apple Clang,
	# /usr/local/include is searched before -isystem paths, so includes that
	# arrive only via imported deps (e.g. xTests) can otherwise shadow us.
	set_property(TARGET ${program_name} PROPERTY NO_SYSTEM_FROM_IMPORTED TRUE)
	target_include_directories(${program_name}
		BEFORE PRIVATE
			${CMAKE_SOURCE_DIR}/include
	)

	target_link_libraries(${program_name}
		$<$<BOOL:${shwild_FOUND}>:shwild::core>
		$<$<BOOL:${cstring_FOUND}>:cstring::core>
		$<$<BOOL:${UNIXem_FOUND}>:UNIXem::UNIXem>
	)

	if(WIN32)

		target_link_libraries(${program_name}
			ws2_32
			wsock32
		)
	endif()

	set(X_GCC_CUSTOM_WARNINGS_ "")

	if(X_GCC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED)
		foreach(warning ${X_GCC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED})

			list(APPEND X_GCC_CUSTOM_WARNINGS_ "-Wno-${warning}")
		endforeach()
	endif()

	set(X_MSVC_CUSTOM_WARNINGS_ "")

	if(X_MSVC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED)
			foreach(warning ${X_MSVC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED})

					list(APPEND X_MSVC_CUSTOM_WARNINGS_ "/wd${warning}")
			endforeach()
	endif()

	target_compile_options(${program_name}
		PRIVATE
			$<$<OR:$<COMPILE_LANG_AND_ID:C,GNU,Clang,AppleClang>,$<COMPILE_LANG_AND_ID:CXX,GNU,Clang,AppleClang>>:
				-Werror -Wall -Wextra -pedantic

				${GCC_WARN_NO_cxx11_long_long}
				${X_GCC_CUSTOM_WARNINGS_}
			>
			$<$<COMPILE_LANG_AND_ID:CXX,Clang,AppleClang>:
				-Wno-unused-lambda-capture
			>
			$<$<COMPILE_LANG_AND_ID:C,TinyCC>:
				-Wall
			>
			$<$<OR:$<COMPILE_LANG_AND_ID:C,MSVC>,$<COMPILE_LANG_AND_ID:CXX,MSVC>>:
				/WX /W4

				${X_MSVC_CUSTOM_WARNINGS_}
			>
	)
endfunction(define_example_program)


# ############################## end of file ############################# #

