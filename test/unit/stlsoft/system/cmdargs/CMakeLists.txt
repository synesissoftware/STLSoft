
if((MSVC) AND (MSVC_VERSION GREATER_EQUAL 1914))

	add_compile_options("/Zc:strictStrings-")
endif()

list(APPEND X_GCC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED
	"writable-strings"
	"write-strings"
)
define_automated_test_program(test.unit.stlsoft.system.cmdargs entry.cpp)
