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

  # TEMPORARY (file_lines.perf): optional substring filter, e.g.
  # SIS_PERFTESTS_MATCH=file_lines to skip stopwatch while hunting.
  Match=${SIS_PERFTESTS_MATCH:-}

  for f in $(find "$CMakeDir" -type f '(' -name 'test_performance*' -o -name 'test.performance.*' ')' -exec test -x {} \; -print | sort)
  do

    if [ -n "$Match" ] && [[ "$f" != *"$Match"* ]]; then

      continue
    fi

    if [ $ListOnly -ne 0 ]; then

      echo "would execute $SisClr_Blue$SisClr_Bold$f$SisClr_None:"

      continue
    fi

    echo
    echo "executing $SisClr_Blue$SisClr_Bold$f$SisClr_None:"

    # TEMPORARY (file_lines.perf): size / imports and a cwd breadcrumb so a
    # silent child death still leaves something to cat. Capture child_ec
    # before any other command overwrites $?.
    ls -la "$f" || true
    if command -v objdump >/dev/null 2>&1; then

      objdump -p "$f" 2>/dev/null | grep -i "DLL Name" || true
    fi
    rm -f file_lines.perf.trace.txt

    if [ $ExpandWidth -ne 0 ]; then

      $f | expand -t $ExpandWidth
      child_ec=${PIPESTATUS[0]}
    else

      $f
      child_ec=$?
    fi

    echo "child-exit=$child_ec"
    if [ -f file_lines.perf.trace.txt ]; then

      echo "breadcrumb:"
      cat file_lines.perf.trace.txt
    else

      echo "breadcrumb: (none)"
    fi

    # TEMPORARY (file_lines.perf): 127 + no breadcrumb => PE loader / DLL
    # search. Dump PATH, probe MinGW runtimes, copy them beside the exe,
    # and retry once.
    if [ $child_ec -eq 127 ]; then

      echo "dll-hunt: PATH=$PATH"
      if command -v g++ >/dev/null 2>&1; then

        echo "dll-hunt: g++=$(command -v g++)"
        echo "dll-hunt: libstdc++=$(g++ -print-file-name=libstdc++-6.dll)"
        echo "dll-hunt: libgcc=$(g++ -print-file-name=libgcc_s_seh-1.dll)"
      fi
      for d in /mingw64/bin /ucrt64/bin; do

        if [ -d "$d" ]; then

          ls -la "$d"/libstdc++*.dll "$d"/libgcc_s*.dll "$d"/libwinpthread*.dll 2>/dev/null || true
        fi
      done
      if command -v cygcheck >/dev/null 2>&1; then

        cygcheck "$f" || true
      fi

      exe_dir=$(dirname "$f")
      for dll in libgcc_s_seh-1.dll libstdc++-6.dll libwinpthread-1.dll; do

        for d in /mingw64/bin /ucrt64/bin; do

          if [ -f "$d/$dll" ]; then

            cp -f "$d/$dll" "$exe_dir/"
            echo "dll-hunt: copied $d/$dll -> $exe_dir/"
          fi
        done
      done
      rm -f file_lines.perf.trace.txt
      $f
      child_ec=$?
      echo "child-exit-after-dll-copy=$child_ec"
      if [ -f file_lines.perf.trace.txt ]; then

        echo "breadcrumb-after-dll-copy:"
        cat file_lines.perf.trace.txt
      else

        echo "breadcrumb-after-dll-copy: (none)"
      fi
    fi

    if [ $child_ec -eq 0 ]; then

      :
    else

      status=$child_ec

      break 1
    fi
  done
fi

exit $status


# ############################## end of file ############################# #
