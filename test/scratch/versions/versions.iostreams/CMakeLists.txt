if(MFC_FOUND)

	# Includes <mfcstl/mfcstl.hpp> when **STLSOFT_HAS_MFC**. Save/restore
	# **CMAKE_MFC_FLAG** so later directories are unaffected.
	set(_stlsoft_cmake_mfc_flag_save "${CMAKE_MFC_FLAG}")

	stlsoft_prepare_mfc_target()
endif(MFC_FOUND)

define_example_program(test.scratch.versions.iostreams versions.cpp)

if(MFC_FOUND)

	set(CMAKE_MFC_FLAG "${_stlsoft_cmake_mfc_flag_save}")
	unset(_stlsoft_cmake_mfc_flag_save)
endif(MFC_FOUND)

if(HAS_ACE)

	target_link_libraries(test.scratch.versions.iostreams
		ACE::ACE
	)
endif()

if(HAS_woad)

	target_link_libraries(test.scratch.versions.iostreams
		woad::woad
	)
endif()

if(xTests_FOUND)

	target_link_libraries(test.scratch.versions.iostreams
		xTests::core
	)
endif()
