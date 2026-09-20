# FindACE.cmake
#
# Locates the ACE (Adaptive Communication Environment) headers and library.
#
# Sets:
#   ACE_FOUND
#   ACE_INCLUDE_DIRS
#   ACE_LIBRARIES
#
# Provides imported target:
#   ACE::ACE
#
# Optional hints (directory containing `ace/ACE.h`, or `include/ace/ACE.h`):
#   CMake/env ACE or ACE_ROOT


set(_ACE_INCLUDE_HINTS)
set(_ACE_LIBRARY_HINTS)

foreach(_ace_root IN ITEMS
	"${ACE}"
	"${ACE_ROOT}"
	"$ENV{ACE}"
	"$ENV{ACE_ROOT}"
)

	if(_ace_root)

		get_filename_component(_ace_root_abs "${_ace_root}" ABSOLUTE)

		list(APPEND _ACE_INCLUDE_HINTS
			"${_ace_root_abs}"
			"${_ace_root_abs}/include"
		)
		list(APPEND _ACE_LIBRARY_HINTS
			"${_ace_root_abs}"
			"${_ace_root_abs}/lib"
			"${_ace_root_abs}/ace"
		)
	endif()
endforeach()

find_path(ACE_INCLUDE_DIR
	NAMES
		ace/ACE.h
	HINTS
		${_ACE_INCLUDE_HINTS}
	DOC
		"Directory containing ace/ACE.h"
)

find_library(ACE_LIBRARY
	NAMES
		ACE
		ace
	HINTS
		${_ACE_LIBRARY_HINTS}
	DOC
		"ACE library"
)

unset(_ACE_INCLUDE_HINTS)
unset(_ACE_LIBRARY_HINTS)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(ACE
	REQUIRED_VARS
		ACE_LIBRARY
		ACE_INCLUDE_DIR
)

if(ACE_FOUND)

	set(ACE_INCLUDE_DIRS "${ACE_INCLUDE_DIR}")
	set(ACE_LIBRARIES "${ACE_LIBRARY}")

	if(NOT TARGET ACE::ACE)

		add_library(ACE::ACE UNKNOWN IMPORTED)
		set_target_properties(ACE::ACE
			PROPERTIES
				IMPORTED_LOCATION "${ACE_LIBRARY}"
				INTERFACE_INCLUDE_DIRECTORIES "${ACE_INCLUDE_DIR}"
		)
	endif()
endif()

mark_as_advanced(ACE_INCLUDE_DIR ACE_LIBRARY)


# ############################## end of file ############################# #
