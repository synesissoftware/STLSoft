# MFC link settings must be in scope before leaf targets call
# define_automated_test_program() (see stlsoft_prepare_mfc_target).
# **CMAKE_MFC_FLAG** is a normal variable and would otherwise leak to later
# sibling directories after this **add_subdirectory** returns.
set(_stlsoft_cmake_mfc_flag_save "${CMAKE_MFC_FLAG}")

stlsoft_prepare_mfc_target()

add_subdirectory(memory)

set(CMAKE_MFC_FLAG "${_stlsoft_cmake_mfc_flag_save}")
unset(_stlsoft_cmake_mfc_flag_save)
