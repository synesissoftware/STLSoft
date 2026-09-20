# FindATL.cmake
#
# Detects Microsoft Active Template Library (ATL) headers for MSVC on
# Windows (not MinGW / Borland).
#
# Sets:
#   ATL_FOUND
#   ATL_HAVE_ATL   (CACHE; true when atlbase.h is usable)
#
# There is no stock CMake FindATL; this mirrors FindMFC's Windows-only
# check. ATL is typically header-available with the VC ATL component and
# needs no extra link flags for compile-only / version smoke use.


set(ATL_FOUND FALSE)

# Only attempt when the toolset has a chance of shipping atlbase.h:
if(WIN32 AND NOT UNIX AND NOT BORLAND AND NOT MINGW)

	if(NOT DEFINED ATL_HAVE_ATL)

		include(CheckIncludeFileCXX)

		check_include_file_cxx("atlbase.h" ATL_HAVE_ATL)
	endif()

	if(ATL_HAVE_ATL)

		set(ATL_FOUND TRUE)
	endif()
endif()

mark_as_advanced(ATL_HAVE_ATL)


# ############################## end of file ############################# #
