
if(HAS_ACE)

	add_subdirectory(acestl)
endif(HAS_ACE)
if(_BUILD_AS_WIN32)

	add_subdirectory(comstl)
endif(_BUILD_AS_WIN32)
if(_BUILD_AS_UNIX OR _BUILD_AS_WIN32)

	add_subdirectory(inetstl)
endif(_BUILD_AS_UNIX OR _BUILD_AS_WIN32)
if(MFC_FOUND)

	add_subdirectory(mfcstl)
endif(MFC_FOUND)
add_subdirectory(platformstl)
add_subdirectory(stlsoft)
if(_BUILD_AS_UNIX)
	add_subdirectory(unixstl)
endif(_BUILD_AS_UNIX)
if(_BUILD_AS_WIN32)
	add_subdirectory(winstl)
endif(_BUILD_AS_WIN32)

add_subdirectory(test.unit.versions)


# ############################## end of file ############################# #

