#! /bin/bash

ScriptPath=$0
Dir=$(cd $(dirname "$ScriptPath"); pwd)
Basename=$(basename "$ScriptPath")
CMakeDir=${SIS_CMAKE_BUILD_DIR:-$Dir/_build}
[[ -n "$MSYSTEM" ]] && DefaultMakeCmd=mingw32-make.exe || DefaultMakeCmd=make
MakeCmd=${SIS_CMAKE_MAKE_COMMAND:-${SIS_CMAKE_COMMAND:-$DefaultMakeCmd}}
ProjectNameFile="$Dir/.sis/project_name.txt"
ProjectName=$(tr -d '[:space:]' < "$ProjectNameFile")

ListOnly=0
RunMake=1
SkipInteractive=0


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
# helpers

example_stem()
{
  local p="${1//\\//}"

  p="${p##*/}"

  case "$p" in
    *.exe|*.EXE) p="${p%.*}" ;;
  esac

  echo "$p"
}

names_match()
{
  local a b

  a=$(echo "$1" | tr '[:upper:]' '[:lower:]')
  b=$(echo "$2" | tr '[:upper:]' '[:lower:]')

  [ "$a" = "$b" ]
}

is_skipped_interactive_example()
{
  local name f_norm line line_stem skip_file="$Dir/.github/ci_skip_interactive_examples.txt"

  [ $SkipInteractive -ne 0 ] || return 1

  if [ ! -f "$skip_file" ]; then

    >&2 echo "$ScriptPath: --skip-interactive: skip list not found at '$skip_file'"

    return 1
  fi

  f_norm="${1//\\//}"
  name=$(example_stem "$f_norm")

  while IFS= read -r line || [ -n "$line" ]; do

    line="${line//$'\r'/}"

    case "$line" in
      ''|\#*) continue ;;
    esac

    line_stem=$(example_stem "$line")

    if names_match "$name" "$line_stem"; then

      return 0
    fi
  done < "$skip_file"

  return 1
}


# ##########################################################
# command-line handling

while [[ $# -gt 0 ]]; do

  case $1 in
    --list-only|-l)

      ListOnly=1
      ;;
    --no-make|-M)

      RunMake=0
      ;;
    --skip-interactive)

      SkipInteractive=1
      ;;
    --help)

      [ -f "$Dir/.sis/script_info_lines.txt" ] && cat "$Dir/.sis/script_info_lines.txt"
      cat << EOF
Runs all (matching) example programs

$ScriptPath [ ... flags/options ... ]

Flags/options:

    behaviour:

    -l
    --list-only
        lists the target programs but does not execute them

    -M
    --no-make
        does not execute CMake and make before running examples

    --skip-interactive
        skips examples listed in .github/ci_skip_interactive_examples.txt
        (GUI / desktop-interactive programs unsuitable for headless CI;
        list stems or names, e.g. shell_functions or shell_functions.exe)


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

    echo "Executing build (via command \`$MakeCmd\`) and then running all ${ProjectName} example programs"

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

  if [ ! -d "$CMakeDir/examples" ]; then

    >&2 echo "$ScriptPath: examples build tree not found at '$CMakeDir/examples'"

    exit 1
  fi

  if [ $ListOnly -ne 0 ]; then

    echo "Listing all ${ProjectName} example programs"
  else

    echo "Running all ${ProjectName} example programs"
  fi

  # Exclude CMake / build artefacts that can become +x after artifact restore.
  ExamplePrograms=( $(find "$CMakeDir/examples" -type f \
    ! -path '*/CMakeFiles/*' \
    ! -name '*.a' \
    ! -name '*.cmake' \
    ! -name '*.d' \
    ! -name '*.lib' \
    ! -name '*.log' \
    ! -name '*.o' \
    ! -name '*.obj' \
    ! -name '*.pdb' \
    ! -name 'CMakeLists.txt' \
    ! -name 'CTestTestfile.cmake' \
    ! -name 'Makefile' \
    ! -name 'cmake_install.cmake' \
    -exec test -x {} \; -print | sort) )

  echo "discovered ${#ExamplePrograms[@]} example program(s)"

  if [ ${#ExamplePrograms[@]} -eq 0 ]; then

    >&2 echo "$ScriptPath: no matching executable example programs under '$CMakeDir/examples' (execute bits missing after artifact download?)"

    if [ $ListOnly -eq 0 ]; then

      status=1
    fi
  fi

  for f in "${ExamplePrograms[@]}"
  do

    if is_skipped_interactive_example "$f"; then

      if [ $ListOnly -ne 0 ]; then

        echo "would skip $SisClr_Blue$SisClr_Bold$f$SisClr_None (interactive; --skip-interactive)"

      else

        echo
        echo "skipping $SisClr_Blue$SisClr_Bold$f$SisClr_None (interactive; --skip-interactive)"
      fi

      continue
    fi

    if [ $ListOnly -ne 0 ]; then

      echo "would execute $SisClr_Blue$SisClr_Bold$f$SisClr_None:"

      continue
    fi

    echo
    echo "executing $SisClr_Blue$SisClr_Bold$f$SisClr_None:"

    if $f; then

      :
    else

      status=$?

      break 1
    fi
  done
fi

exit $status


# ############################## end of file ############################# #
