#! /bin/bash

# ##########################################################
# functions - 1

sis_cmake_is_truey() {
  case "$(printf '%s' "${1:-}" | tr '[:upper:]' '[:lower:]')" in

    1|ok|on|true|yes|y)

      return 0
    ;;
    *)

      return 1
      ;;
  esac
}


# ##########################################################
# constants and variables

Basename=$(basename "$0")
Dir=$(cd "$(dirname "$0")" && pwd)
CMakeDir=${SIS_CMAKE_BUILD_DIR:-$Dir/_build}
ProjectNameFile="$Dir/.sis/project_name.txt"
ProjectName=$(tr -d '[:space:]' < "$ProjectNameFile")
ScriptPath=$0

AlwaysUseColours=${SIS_CMAKE_ALWAYS_USE_COLOURS:-${SIS_ALWAYS_USE_COLOURS:-0}}
ListOnly=0
RunMake=1
SisUseColours=0
SkipInteractive=0


# ##########################################################
# colours
#
# Enable when tput is available and either:
#   - AlwaysUseColours is set (overrides NO_COLOR; may set TERM if
#     empty/dumb), or
#   - NO_COLOR is unset, stdout is a TTY, and TERM is not dumb (union of
#     collect-c's "TERM set + TTY" and cstring's "TTY" — empty TERM on a
#     TTY is OK).

SisClr_Blue=
SisClr_Bold=
SisClr_Green=
SisClr_None=
SisClr_Red=
SisClr_Yellow=

for arg in "$@"; do

  case $arg in
    --always-use-colors|--always-use-colours|-A)

      AlwaysUseColours=1
      ;;
  esac
done

if command -v tput >/dev/null 2>&1; then

  if [ $AlwaysUseColours -ne 0 ]; then

    if [ -z "${TERM:-}" ] || [ "$TERM" = "dumb" ]; then

      TERM=xterm-256color
    fi

    SisUseColours=1
  elif [ -z "${NO_COLOR:-}" ] && [ -t 1 ] && [ "${TERM:-}" != "dumb" ]; then

    SisUseColours=1
  fi
fi

if [ $SisUseColours -ne 0 ]; then

  SisClr_Blue=${FG_BLUE:-$(tput setaf 4)}
  SisClr_Bold=${FD_BOLD:-$(tput bold)}
  SisClr_Green=${FG_GREEN:-$(tput setaf 2)}
  SisClr_None=${FD_NONE:-$(tput sgr0)}
  SisClr_Red=${FG_RED:-$(tput setaf 1)}
  SisClr_Yellow=${FG_YELLOW:-$(tput setaf 3)}
fi

CMakeDirClr="${SisClr_Blue}${SisClr_Bold}${CMakeDir}${SisClr_None}"
ProjectNameClr="${SisClr_Blue}${SisClr_Bold}${ProjectName}${SisClr_None}"
ScriptPathClr="${SisClr_Blue}${SisClr_Bold}${ScriptPath}${SisClr_None}"


# ##########################################################
# functions - 2

sis_cmake_build() {

  local config="${SIS_CMAKE_CONFIG:-Release}"
  local args=(--build "$CMakeDir")
  if [ -f "$CMakeDir/CMakeCache.txt" ] && grep -q '^CMAKE_CONFIGURATION_TYPES:' "$CMakeDir/CMakeCache.txt" 2>/dev/null; then

    args+=(--config "$config")
  fi
  if [ "$#" -gt 0 ]; then

    local t
    for t in "$@"; do

      args+=(--target "$t")
    done
  fi

  cmake "${args[@]}"
}

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

# Examples listed in .github/ci_skip_interactive_examples.txt require an
# interactive desktop (GUI dialogs, etc.) and would hang a headless CI run.
is_skipped_interactive_example()
{
  local name f_norm line line_stem skip_file="$Dir/.github/ci_skip_interactive_examples.txt"

  [ $SkipInteractive -ne 0 ] || return 1

  if [ ! -f "$skip_file" ]; then

    >&2 echo "${ScriptPathClr}: --skip-interactive: skip list not found at '$skip_file'"

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
    --always-use-colors|--always-use-colours|-A)

      # AlwaysUseColours=1 - this is handled by the for loop above
      ;;
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

${ScriptPath} [ ... flags/options ... ]

Flags/options:

    behaviour:

    -A
    --always-use-colors
    --always-use-colours
        forces use of colours even when stdout is not a TTY

    -l
    --list-only
        lists the target programs but does not execute them

    -M
    --no-make
        does not execute a build before running programs

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

      >&2 echo "${ScriptPathClr}: unrecognised argument '${SisClr_Red}${SisClr_Bold}$1${SisClr_None}'; use --help for usage"

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

    echo
    echo "Executing build of ${ProjectNameClr} (via cmake --build) and then running all example programs"

    mkdir -p "$CMakeDir" || exit 1

    if [ ! -f "$CMakeDir/CMakeCache.txt" ]; then

      >&2 echo "${ScriptPathClr}: '${CMakeDirClr}' is not configured; use prepare_cmake.sh first"

      exit 1
    fi

    sis_cmake_build
    status=$?
  fi
else

  if [ ! -d "$CMakeDir" ] || [ ! -f "$CMakeDir/CMakeCache.txt" ]; then

    >&2 echo "${ScriptPathClr}: cannot run in '--no-make' mode without a previous successful configure/build"

    exit 1
  fi
fi

if [ $status -eq 0 ]; then

  if [ $ListOnly -ne 0 ]; then

    echo
    echo "Listing all ${ProjectNameClr} example programs"
  else

    echo
    echo "Running all ${ProjectNameClr} example programs"
  fi

  # Examples that require human input may honour SIS_EXAMPLE_SMOKE for a
  # no-arg built-in tmpfile demo (see example.c.cstring_vector).
  export SIS_EXAMPLE_SMOKE=1

  if [ ! -d "$CMakeDir/examples" ]; then

    >&2 echo "${ScriptPathClr}: examples build tree not found at '${CMakeDirClr}/examples'"

    exit 1
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

    >&2 echo "${ScriptPathClr}: no matching executable example programs under '${CMakeDirClr}/examples' (execute bits missing after artifact download?)"

    if [ $ListOnly -eq 0 ]; then

      status=1
    fi
  fi

  for f in "${ExamplePrograms[@]}"
  do

    fClr="${SisClr_Blue}${SisClr_Bold}${f}${SisClr_None}"

    if is_skipped_interactive_example "$f"; then

      if [ $ListOnly -ne 0 ]; then

        echo "would skip ${fClr} (interactive; --skip-interactive)"
      else

        echo
        echo "skipping ${fClr} (interactive; --skip-interactive)"
      fi

      continue
    fi

    if [ $ListOnly -ne 0 ]; then

      echo "would execute ${fClr}:"

      continue
    fi

    echo
    echo "executing ${fClr}:"

    if "$f"; then

      :
    else

      status=$?

      break 1
    fi
  done
fi

exit $status


# ############################## end of file ############################# #
