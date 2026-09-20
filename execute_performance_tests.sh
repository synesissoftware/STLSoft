#! /bin/bash

ScriptPath=$0
Dir=$(cd $(dirname "$ScriptPath"); pwd)
Basename=$(basename "$ScriptPath")
CMakeDir=${SIS_CMAKE_BUILD_DIR:-$Dir/_build}
[[ -n "$MSYSTEM" ]] && DefaultMakeCmd=mingw32-make.exe || DefaultMakeCmd=make
MakeCmd=${SIS_CMAKE_MAKE_COMMAND:-${SIS_CMAKE_COMMAND:-$DefaultMakeCmd}}
ProjectNameFile="$Dir/.sis/project_name.txt"
ProjectName=$(tr -d '[:space:]' < "$ProjectNameFile")

ExpandWidth=0
ListOnly=0
RunMake=1


# ##########################################################
# colours

if command -v tput > /dev/null; then

  SisClr_Blue=${FG_BLUE:-$(tput setaf 4)}
  SisClr_Red=${FG_BLUE:-$(tput setaf 1)}
  SisClr_Bold=${FD_BOLD:-$(tput bold)}
  SisClr_None=${FD_NONE:-$(tput sgr0)}
else

  SisClr_Blue=
  SisClr_Red=
  SisClr_Bold=
  SisClr_None=
fi


# ##########################################################
# command-line handling

while [[ $# -gt 0 ]]; do

  case $1 in
    --list-only|-l)

      ListOnly=1
      ;;
    --expand-width)

      shift
      ExpandWidth=$1
      ;;
    --no-make|-M)

      RunMake=0
      ;;
    --help)

      [ -f "$Dir/.sis/script_info_lines.txt" ] && cat "$Dir/.sis/script_info_lines.txt"
      cat << EOF
Runs all (matching) performance-test programs

$ScriptPath [ ... flags/options ... ]

Flags/options:

    behaviour:

    --expand-width <expand-width>
        subjects each performance test program's output to expand with the
        given <expand-width>

    -l
    --list-only
        lists the target programs but does not execute them

    -M
    --no-make
        does not execute CMake and make before running tests


    standard flags:

    --help
        displays this help and terminates

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

status=0

if [ $RunMake -ne 0 ]; then

  if [ $ListOnly -eq 0 ]; then
    echo "Executing build (via command \`$MakeCmd\`) and then running all ${ProjectName} performance test programs"

    mkdir -p $CMakeDir || exit 1

    cd $CMakeDir

    $MakeCmd
    status=$?

    cd ->/dev/null
  fi
else

  if [ ! -d "$CMakeDir" ] || [ ! -f "$CMakeDir/CMakeCache.txt" ] || [ ! -d "$CMakeDir/CMakeFiles" ]; then

    >&2 echo "$ScriptPath: cannot run in '--no-make' mode without a previous successful build step"

    exit 1
  fi
fi

if [ $status -eq 0 ]; then

  if [ $ListOnly -ne 0 ]; then

    echo "Listing all ${ProjectName} performance test programs"
  else

    echo "Running all ${ProjectName} performance test programs"
  fi

  for f in $(find "$CMakeDir" -type f '(' -name 'test_performance*' -o -name 'test.performance.*' ')' -exec test -x {} \; -print | sort)
  do

    if [ $ListOnly -ne 0 ]; then

      echo "would execute $SisClr_Blue$SisClr_Bold$f$SisClr_None:"

      continue
    fi

    echo
    echo "executing $SisClr_Blue$SisClr_Bold$f$SisClr_None:"

    if [ $ExpandWidth -ne 0 ]; then

      $f | expand -t $ExpandWidth
    else

      $f
    fi

    if [ $? -eq 0 ]; then

      :
    else

      status=$?

      break 1
    fi
  done
fi

exit $status


# ############################## end of file ############################# #
