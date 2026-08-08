# SIS:AUTO_GENERATED: Remove this line if you edit the file, otherwise it will be overwritten
add_subdirectory(exception)
if(_BUILD_AS_WIN32)

	add_subdirectory(filesystem)
endif(_BUILD_AS_WIN32)
add_subdirectory(shims)
