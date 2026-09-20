if(MFC_FOUND)

	# **test.unit.versions** includes <mfcstl/mfcstl.hpp> when
	# **STLSOFT_HAS_MFC**. Save/restore **CMAKE_MFC_FLAG** so later
	# directories are unaffected.
	set(_stlsoft_cmake_mfc_flag_save "${CMAKE_MFC_FLAG}")

	stlsoft_prepare_mfc_target()
endif(MFC_FOUND)

define_automated_test_program(test.unit.versions entry.cpp)

if(MFC_FOUND)

	set(CMAKE_MFC_FLAG "${_stlsoft_cmake_mfc_flag_save}")
	unset(_stlsoft_cmake_mfc_flag_save)
endif(MFC_FOUND)

if(HAS_ACE)

	target_link_libraries(test.unit.versions
		ACE::ACE
	)
endif()
