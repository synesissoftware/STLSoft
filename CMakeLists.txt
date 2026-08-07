
# ######################################################################## #
# File:     /CMakeLists.txt
#
# Purpose:  Top-level CMake lists file for STLSoft
#
# Created:  31st March 2021
# Updated:  7th August 2026
#
# ######################################################################## #


# ##########################################################
# CMake

cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.31")
	cmake_policy(SET CMP0177 NEW)
endif()

# require out-of-source builds
file(TO_CMAKE_PATH "${CMAKE_CURRENT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")

	message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

# directory for CMake specific extensions and source files.
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})


# ##########################################################
# project

project(STLSoft
	DESCRIPTION "STLSoft is a suite of libraries that provide STL extensions and facades over operating-system and technology-specific APIs."
	HOMEPAGE_URL "https://github.com/synesissoftware/STLSoft"
	LANGUAGES C CXX
)

string(TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWER)
string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER)

# handle version number
set(RX_PROJ_TAG "${PROJECT_NAME_UPPER}")
set(RX_WS "[ \t]")
file(READ "${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME_LOWER}/${PROJECT_NAME_LOWER}.h" _header_file)
string(REGEX MATCH "#${RX_WS}*define${RX_WS}+_?${RX_PROJ_TAG}_VER_MAJOR${RX_WS}+([0-9]+)" MAJOR_DUMMY ${_header_file})
set(_VERSION_MAJOR ${CMAKE_MATCH_1})
string(REGEX MATCH "#${RX_WS}*define${RX_WS}+_?${RX_PROJ_TAG}_VER_MINOR${RX_WS}+([0-9]+)" MINOR_DUMMY ${_header_file})
set(_VERSION_MINOR ${CMAKE_MATCH_1})
string(REGEX MATCH "#${RX_WS}*define${RX_WS}+_?${RX_PROJ_TAG}_VER_(PATCH|REVISION)${RX_WS}+([0-9]+)" PATCH_DUMMY ${_header_file})
set(_VERSION_PATCH ${CMAKE_MATCH_2})

# set project version number here
set(PROJECT_VERSION_MAJOR ${_VERSION_MAJOR})
set(PROJECT_VERSION_MINOR ${_VERSION_MINOR})
set(PROJECT_VERSION_PATCH ${_VERSION_PATCH})
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

# adhere strictly to C and C++ standards plus extensions. These are actually
# useless since we do not compile anything; they merely state our intention.
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON) # GNU extensions and POSIX standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

if(MSVC)

	if(MSVC_VERSION LESS 1800)

		add_compile_options("/wd4996")
	endif()

	if(MSVC_VERSION LESS 1930)

		set(CMAKE_C_STANDARD 90)
		set(CMAKE_CXX_STANDARD 98)
	endif()

	if(MSVC_USE_MT)

		set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
	endif(MSVC_USE_MT)
else(MSVC)

	if(MSVC_USE_MT)

		# this here just to absorb warning about not using `MSVC_USE_MT` (to
		# enable **prepare_cmake.sh** to be simple)
	endif(MSVC_USE_MT)
endif(MSVC)

if(WIN32)

	find_package(MFC QUIET)
endif(WIN32)

if(MFC_FOUND)

	# Shared MFC (/MD + _AFXDLL) unless the project is configured for the
	# static CRT (**MSVC_USE_MT**), in which case static MFC is required.
	#
	# **CMAKE_MFC_FLAG** / **_AFXDLL** are applied only to MFC-consuming
	# targets (see **test/unit/mfcstl** and **test.unit.versions**). Setting
	# them project-wide would force every subsequent MSVC executable to link
	# MFC. Without them on those targets, `find_package(MFC)` can succeed
	# while mfcstl tests fail to link — the historical GHA failure mode.

	if(MSVC_USE_MT)

		set(STLSOFT_MFC_FLAG 1)
		set(STLSOFT_MFC_SHARED OFF)

		message("-- using Microsoft Foundation Classes (static; MSVC_USE_MT)")
	else(MSVC_USE_MT)

		set(STLSOFT_MFC_FLAG 2)
		set(STLSOFT_MFC_SHARED ON)

		message("-- using Microsoft Foundation Classes (shared)")
	endif(MSVC_USE_MT)

	add_compile_definitions(STLSOFT_HAS_MFC)
endif(MFC_FOUND)


# ##########################################################
# dependencies, includes, options

# ################################################
# includes - 1

include(BuildType)
include(LanguageFullVersion)
include(TargetMacros)


# ################################################
# dependencies, features, and options

# ######################################
# options

option(BUILD_EXAMPLES "Build examples" ON)

option(BUILD_TESTING "Build tests" ON)


# ######################################
# features


# ######################################
# dependencies
#
# required:
# - (STLSoft) - required (to exist only) for testing;
# - xTests - required for testing;
#
# optional:
# - ACE - enables ACESTL examples/tests when found (NO_ACE / --no-ace suppresses);
# - cstring - facilitates some C tests;
# - shwild - enhances xTests for testing;
# - UNIXem - required for examples/testing on Windows if USE_UNIXEM and WIN32 are defined;


# ############################
# ACE
#
# Discovery (when NO_ACE is not set): find_package(ACE) via cmake/FindACE.cmake
# (system packages such as libace-dev, or ACE / ACE_ROOT hints).

set(HAS_ACE OFF)

if(NOT NO_ACE)

	find_package(ACE QUIET)

	if(ACE_FOUND)

		set(HAS_ACE ON)

		add_compile_definitions(STLSOFT_HAS_ACE)

		message("-- ACE found")
	endif()
endif()


# ############################
# STLSoft
#
# Since we use xTests for testing, and it relies in turn on STLSoft, we must
# detect a CMake installation of STLSoft in order to run testing.
#
# (This implication, therefore, is that first-time installation of
# STLSoft/xTests must follow the sequence:
#  1. Configure/build/install STLSoft **without** tests;
#  2. Configure/build/install xTests;
#  3. Configure/build/install STLSoft in full;
# )

if(BUILD_TESTING)

	find_package(STLSoft REQUIRED)

	if(NOT STLSoft_FOUND)

		message(FATAL_ERROR "No existing installation of STLSoft was found, which means you are not able to configure CMake with testing enabled, because STLSoft's component/unit tests are implemented in terms of xTests, which itself relies on STLSoft. Instead, you must perform an initial CMake configuration and installation with testing disabled (-DBUILD_TESTING:BOOL=OFF, or passing --disable-testing to prepare_cmake.sh), and then configure and install xTests, whereupon you will be free to (re)configure STLSoft for testing.")
	else()

		message("-- CMake package STLSoft found (version ${STLSoft_VERSION}) - required only to enable xTests package; the current project's header files will be used for all compilation")
	endif()
endif(BUILD_TESTING)


# ############################
# shwild

if(NOT (NO_SHWILD))

	if(BUILD_TESTING)

		set(shwild_REQUIRED_VERSION_ 0.12.6)

		find_package(shwild ${shwild_REQUIRED_VERSION_} QUIET)

		if(shwild_FOUND)

			message("-- CMake package shwild found (version ${shwild_VERSION}; ${shwild_REQUIRED_VERSION_} requested)")

			add_compile_definitions(XTESTS_USE_SHWILD)
		endif(shwild_FOUND)
	endif(BUILD_TESTING)
endif()


# ############################
# cstring

if(NOT (NO_CSTRING))

	if(BUILD_TESTING)

		set(cstring_REQUIRED_VERSION_ 4.0)

		find_package(cstring ${cstring_REQUIRED_VERSION_} QUIET)

		if(cstring_FOUND)

			message("-- CMake package cstring found (version ${cstring_VERSION}; ${cstring_REQUIRED_VERSION_} requested)")

			add_compile_definitions(STLSOFT_HAS_CSTRING)
		endif(cstring_FOUND)
	endif(BUILD_TESTING)
endif()


# ############################
# UNIXem

if((USE_UNIXEM) AND (WIN32))

	if((BUILD_EXAMPLES) OR (BUILD_TESTING))

		set(UNIXem_REQUIRED_VERSION_ 1.12.7)

		find_package(UNIXem ${UNIXem_REQUIRED_VERSION_} REQUIRED)

		message("-- CMake package UNIXem found (version ${UNIXem_VERSION}; ${UNIXem_REQUIRED_VERSION_} requested)")

		add_compile_definitions(_STLSOFT_FORCE_ANY_COMPILER)
		add_compile_definitions(STLSOFT_HAS_UNIXEM)
	endif()
endif()


# ############################
# xTests

if(BUILD_TESTING)

	set(xTests_REQUIRED_VERSION_ 0.26.4)

	find_package(xTests ${xTests_REQUIRED_VERSION_} REQUIRED)

	message("-- CMake package xTests found (version ${xTests_VERSION}; ${xTests_REQUIRED_VERSION_} requested)")
endif(BUILD_TESTING)


# ################################################
# includes - 2

include(CMakePackageConfigHelpers)
if(BUILD_TESTING)

	include(CTest)
endif(BUILD_TESTING)
include(GNUInstallDirs)


# ##########################################################
# targets

# ################################################
# custom definitions

if(UNIX)

	set(_BUILD_AS_UNIX 1)

	message("-- Operating system Unix")
else(UNIX)

	if(WIN32)

		if(USE_UNIXEM)

			set(_BUILD_AS_UNIX 1)

			message("-- Operating system Unix (synthesised on Windows)")
		else(USE_UNIXEM)

			set(_BUILD_AS_WIN32 1)

			message("-- Operating system Windows")
		endif(USE_UNIXEM)
	else(WIN32)

		message("-- Operating system unknown")
	endif(WIN32)
endif(UNIX)


# ################################################
# main libraries


# ################################################
# examples

if(BUILD_EXAMPLES)

	message("-- enabled building of examples ...")

	add_subdirectory(examples)
else(BUILD_EXAMPLES)

	message("-- disabled building of examples - define BUILD_EXAMPLES to enable")
endif(BUILD_EXAMPLES)


# ################################################
# tests

if(BUILD_TESTING)

	message("-- enabled building of tests ...")

	add_subdirectory(test)
else(BUILD_TESTING)

	message("-- disabled building of tests - define BUILD_TESTING to enable")
endif(BUILD_TESTING)


# ##########################################################
# build


add_library(STLSoft INTERFACE)

target_include_directories(STLSoft INTERFACE
	$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)


# ##########################################################
# install

# this does not actually install anything...
install(TARGETS STLSoft
	EXPORT project-targets
	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# ... and we have to manually copy the header files.
foreach(ITEM
	acestl
	atlstl
	comstl
	inetstl
	mfcstl
	platformstl
	rangelib
	stlsoft
	unixstl
	winstl
	wtlstl
)

	install(
		DIRECTORY ${CMAKE_SOURCE_DIR}/include/${ITEM}/
		DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${ITEM}/
		FILES_MATCHING
		PATTERN "*.h*"
	)
endforeach()


# ##########################################################
# export

set(EXPORT_NAME ${PROJECT_NAME_LOWER})

configure_package_config_file(
	${CMAKE_CURRENT_SOURCE_DIR}/cmake/${EXPORT_NAME}-config.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/cmake/${EXPORT_NAME}-config.cmake
	INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/${EXPORT_NAME}/cmake
)

write_basic_package_version_file(
	${CMAKE_CURRENT_BINARY_DIR}/cmake/${EXPORT_NAME}-config-version.cmake
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY AnyNewerVersion
)

#[====[
export(EXPORT project-targets
	FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/${EXPORT_NAME}-targets.cmake"
	NAMESPACE "${PROJECT_NAME}::"
)
#]====]

# install stlsoft-targets.cmake        => /usr/local/lib/cmake/stlsoft
install(EXPORT project-targets
	NAMESPACE "${PROJECT_NAME}::"
	FILE "${EXPORT_NAME}-targets.cmake"
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${EXPORT_NAME}
)

# install stlsoft-config-version.cmake => /usr/local/lib/cmake/stlsoft
# install stlsoft-config.cmake         => /usr/local/lib/cmake/stlsoft
install(FILES
	"${CMAKE_CURRENT_BINARY_DIR}/cmake/${EXPORT_NAME}-config.cmake"
	"${CMAKE_CURRENT_BINARY_DIR}/cmake/${EXPORT_NAME}-config-version.cmake"
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${EXPORT_NAME}
)


# ##########################################################
# completion

message(NOTICE "Generating CMake build scripts for ${PROJECT_NAME} ${PROJECT_VERSION}, for C${CMAKE_C_STANDARD} C++${CMAKE_CXX_STANDARD}, with build type ${CMAKE_BUILD_TYPE}")


# ############################## end of file ############################# #

