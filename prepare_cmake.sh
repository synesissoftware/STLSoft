#! /bin/bash

ScriptPath=$0
Dir=$(cd $(dirname "$ScriptPath"); pwd)
Basename=$(basename "$ScriptPath")
CMakeDir=${SIS_CMAKE_BUILD_DIR:-$Dir/_build}
if [[ -n "$MSYSTEM" ]]; then

  DefaultMakeCmd=mingw32-make.exe
  MinGW=1
else

  DefaultMakeCmd=make
fi
MakeCmd=${SIS_CMAKE_MAKE_COMMAND:-${SIS_CMAKE_COMMAND:-$DefaultMakeCmd}}
ProjectNameFile="$Dir/.sis/project_name.txt"
ProjectName=$(tr -d '[:space:]' < "$ProjectNameFile")


Configuration=Release
ExamplesDisabled=0
MSVC_MT=0
MinGW="${MinGW:=0}"
NO_ACE=0
NO_cstring=0
NO_shwild=0
RunMake=0
TestingDisabled=0
USE_UNIXem=0
VerboseMakefile=0


# ##########################################################
# command-line handling

while [[ $# -gt 0 ]]; do

  case $1 in
    --cmake-verbose-makefile|-v)

      VerboseMakefile=1
      ;;
    --debug-configuration|-d)

      Configuration=Debug
      ;;
    --disable-examples|-E)

      ExamplesDisabled=1
      ;;
    --disable-testing|-T)

      TestingDisabled=1
      ;;
    --mingw)

      MinGW=1
      ;;
    --msvc-mt)

      MSVC_MT=1
      ;;
    --no-ace)

      NO_ACE=1
      ;;
    --no-cstring)

      NO_cstring=1
      ;;
    --no-shwild)

      NO_shwild=1
      ;;
    --run-make|-m)

      RunMake=1
      ;;
    --use-unixem)

      USE_UNIXem=1
      ;;
    --help)

      [ -f "$Dir/.sis/script_info_lines.txt" ] && cat "$Dir/.sis/script_info_lines.txt"
      cat << EOF
Creates/reinitialises the CMake build script(s)

$ScriptPath [ ... flags/options ... ]

IMPORTANT: If you have not previously performed a CMake installation of xTests, the library that STLSoft uses for its own tests, you MUST specify the -E and -T flags. Once you have installed STLSoft, you can then configure/build/install STLSoft, and then come back and prepare STLSoft without -E/-T and exercise its examples and tests.

Flags/options:

    behaviour:

    -v
    --cmake-verbose-makefile
        configures CMake to run verbosely (by setting CMAKE_VERBOSE_MAKEFILE
        to be ON)

    -d
    --debug-configuration
        use Debug configuration (by setting CMAKE_BUILD_TYPE=Debug). Default
        is to use Release

    -E
    --disable-examples
        disables building of examples (by setting BUILD_EXAMPLES=OFF)

    -T
    --disable-testing
        disables building of tests (by setting BUILD_TESTING=OFF). This is
        necessary, for example, when installing on a system that does not
        (yet) have xTests - which itself depends on STLSOFT - installed

    --mingw
        uses explicitly the "MinGW Makefiles" generator

    --msvc-mt
        when using Visual C++ (MSVC), the static runtime library will be
        selected; the default is the dynamic runtime library. Has no effect
        when not using Visual C++

    --no-ace
        suppresses discovery of ACE (ACESTL examples/tests will not be built)

    --no-cstring
        suppresses discovery of cstring package

    --no-shwild
        suppresses discovery of shwild package

    -m
    --run-make
        executes make after a successful running of CMake

    --use-unixem
      when building on Windows, use the UNIXem library and define the
      preprocessor symbol _STLSOFT_FORCE_ANY_COMPILER so as to emulate and
      exercise UNIXSTL, not WinSTL (or COMSTL, etc.). Has no effect when not
      executing on Windows


    standard flags:

    --help
        displays this help and terminates

IMPORTANT: If you have not previously performed a CMake installation of xTests, the library that STLSoft uses for its own tests, you MUST specify the -E and -T flags. Once you have installed STLSoft, you can then configure/build/install STLSoft, and then come back and prepare STLSoft without -E/-T and exercise its examples and tests.

EOF

      exit 0
      ;;
    *)

      >&2 echo "$ScriptPath: unrecognised argument '$1'; use --help for usage"

      exit 1
      ;;
  esac

  shift
done


# ##########################################################
# main()

mkdir -p $CMakeDir || exit 1

cd $CMakeDir

echo "Executing CMake for ${ProjectName} (in ${CMakeDir})"

if [ $ExamplesDisabled -eq 0 ]; then CMakeBuildExamplesFlag="ON" ; else CMakeBuildExamplesFlag="OFF" ; fi
if [ $MSVC_MT -eq 0 ]; then CMakeMsvcMtFlag="OFF" ; else CMakeMsvcMtFlag="ON" ; fi
if [ $NO_ACE -eq 0 ]; then CMakeNoACE="OFF" ; else CMakeNoACE="ON" ; fi
if [ $NO_cstring -eq 0 ]; then CMakeNoCstring="OFF" ; else CMakeNoCstring="ON" ; fi
if [ $NO_shwild -eq 0 ]; then CMakeNoShwild="OFF" ; else CMakeNoShwild="ON" ; fi
if [ $TestingDisabled -eq 0 ]; then CMakeBuildTestingFlag="ON" ; else CMakeBuildTestingFlag="OFF" ; fi
if [ $USE_UNIXem -ne 0 ]; then CMakeUSE_UNIXem="ON" ; else CMakeUSE_UNIXem="OFF" ; fi
if [ $VerboseMakefile -eq 0 ]; then CMakeVerboseMakefileFlag="OFF" ; else CMakeVerboseMakefileFlag="ON" ; fi

if [ $MinGW -ne 0 ]; then

  cmake \
    -DBUILD_EXAMPLES:BOOL=$CMakeBuildExamplesFlag \
    -DBUILD_TESTING:BOOL=$CMakeBuildTestingFlag \
    -DCMAKE_BUILD_TYPE=$Configuration \
    -DNO_ACE:BOOL=$CMakeNoACE \
    -DNO_CSTRING:BOOL=$CMakeNoCstring \
    -DNO_SHWILD:BOOL=$CMakeNoShwild \
    -DUSE_UNIXEM:BOOL=$CMakeUSE_UNIXem \
    -G "MinGW Makefiles" \
    -S $Dir \
    -B $CMakeDir \
    || (cd ->/dev/null ; exit 1)
else

  cmake \
    -DBUILD_EXAMPLES:BOOL=$CMakeBuildExamplesFlag \
    -DBUILD_TESTING:BOOL=$CMakeBuildTestingFlag \
    -DCMAKE_BUILD_TYPE=$Configuration \
    -DCMAKE_VERBOSE_MAKEFILE:BOOL=$CMakeVerboseMakefileFlag \
    -DMSVC_USE_MT:BOOL=$CMakeMsvcMtFlag \
    -DNO_ACE:BOOL=$CMakeNoACE \
    -DNO_CSTRING:BOOL=$CMakeNoCstring \
    -DNO_SHWILD:BOOL=$CMakeNoShwild \
    -DUSE_UNIXEM:BOOL=$CMakeUSE_UNIXem \
    -S $Dir \
    -B $CMakeDir \
    || (cd ->/dev/null ; exit 1)
fi

status=0

if [ $RunMake -ne 0 ]; then

  echo "Executing build for ${ProjectName} (via command \`$MakeCmd\`)"

  $MakeCmd
  status=$?
fi

cd ->/dev/null

if [ $VerboseMakefile -ne 0 ]; then

  echo -e "contents of $CMakeDir:"
  ls -al $CMakeDir
fi

exit $status


# ############################## end of file ############################# #

