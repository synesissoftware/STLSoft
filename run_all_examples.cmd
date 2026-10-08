@ECHO OFF

SETLOCAL ENABLEDELAYEDEXPANSION ENABLEEXTENSIONS

SET ScriptPath=%~n0[%~x0]
SET ScriptDir=%~dp0

IF DEFINED SIS_CMAKE_BUILD_DIR (

    SET CMakeDir=%SIS_CMAKE_BUILD_DIR%
) ELSE (

    SET CMakeDir=%ScriptDir%_build
)

SET ListOnly=0
SET RunMake=1
SET SkipInteractive=0

SET BuildConfig=Release
IF DEFINED CMAKE_BUILD_TYPE SET BuildConfig=%CMAKE_BUILD_TYPE%


:: #########################################################
:: command-line handling

:parse_args
IF "%~1"=="" GOTO args_done

IF /I "%~1"=="--help" GOTO show_help
IF /I "%~1"=="-l" (
    SET ListOnly=1
    GOTO next_arg
)
IF /I "%~1"=="--list-only" (
    SET ListOnly=1
    GOTO next_arg
)
IF /I "%~1"=="-M" (
    SET RunMake=0
    GOTO next_arg
)
IF /I "%~1"=="--no-make" (
    SET RunMake=0
    GOTO next_arg
)
IF /I "%~1"=="--skip-interactive" (
    SET SkipInteractive=1
    GOTO next_arg
)

ECHO %ScriptPath%: unrecognised argument '%~1'; use --help for usage 1>&2
EXIT /B 1

:next_arg
SHIFT
GOTO parse_args

:args_done


:: #########################################################
:: main()

SET status=0

IF %RunMake% NEQ 0 (
    IF %ListOnly% EQU 0 (
        ECHO Executing build and then running all example programs
        CALL :do_build
        IF ERRORLEVEL 1 SET status=1
    )
) ELSE (
    IF NOT EXIST "%CMakeDir%\CMakeCache.txt" (
        ECHO %ScriptPath%: cannot run in '--no-make' mode without a previous successful build step 1>&2
        EXIT /B 1
    )
)

IF %status% EQU 0 (
    IF NOT EXIST "%CMakeDir%\examples" (
        ECHO %ScriptPath%: examples build tree not found at '%CMakeDir%\examples' 1>&2
        ENDLOCAL
        EXIT /B 1
    )

    IF %ListOnly% NEQ 0 (
        ECHO Listing all example programs
    ) ELSE (
        ECHO Running all example programs
    )

    FOR /F "usebackq delims=" %%f IN (`DIR /A:-D /B /S "%CMakeDir%\examples\*.exe" 2^>NUL`) DO (
        CALL :is_skipped_interactive "%%~nxf"
        IF !skip_example! EQU 1 (
            IF !ListOnly! NEQ 0 (
                ECHO would skip %%f: (interactive; --skip-interactive)
            ) ELSE (
                ECHO.
                ECHO skipping %%f: (interactive; --skip-interactive)
            )
        ) ELSE IF !ListOnly! NEQ 0 (
            ECHO would execute %%f:
        ) ELSE (
            ECHO.
            ECHO executing %%f:
            CALL "%%f"
            IF ERRORLEVEL 1 (
                SET status=1
                GOTO examples_done
            )
        )
    )
)

:examples_done
IF !status! NEQ 0 (
    ENDLOCAL
    EXIT /B 1
)
ENDLOCAL
EXIT /B 0


:: #########################################################
:: helpers

:is_skipped_interactive
SET skip_example=0
IF %SkipInteractive% EQU 0 EXIT /B 0
IF NOT EXIST "%ScriptDir%.github\ci_skip_interactive_examples.txt" EXIT /B 0
SET "exe_name=%~n1"
FOR /F "usebackq eol=# tokens=1" %%s IN ("%ScriptDir%.github\ci_skip_interactive_examples.txt") DO (
    SET "skip_name=%%s"
    SET "skip_name=!skip_name: =!"
    IF /I "!skip_name!"=="%exe_name%" SET skip_example=1
    IF /I "!skip_name!"=="%~nx1" SET skip_example=1
)
EXIT /B 0

:do_build
IF DEFINED SIS_CMAKE_MAKE_COMMAND (
    PUSHd "%CMakeDir%"
    CALL %SIS_CMAKE_MAKE_COMMAND%
    SET build_status=!ERRORLEVEL!
    POPD
    EXIT /B !build_status!
)
IF EXIST "%CMakeDir%\Makefile" (
    PUSHd "%CMakeDir%"
    IF DEFINED MSYSTEM (
        mingw32-make.exe
    ) ELSE (
        make
    )
    SET build_status=!ERRORLEVEL!
    POPD
    EXIT /B !build_status!
)
cmake --build "%CMakeDir%" --config %BuildConfig%
EXIT /B %ERRORLEVEL%


:show_help
IF EXIST "%ScriptDir%.sis\script_info_lines.txt" (
    type "%ScriptDir%.sis\script_info_lines.txt"
)
ECHO.
ECHO Runs all (matching) example programs
ECHO.
ECHO %ScriptPath% [ ... flags/options ... ]
ECHO.
ECHO Flags/options:
ECHO.
ECHO     behaviour:
ECHO.
ECHO     -l
ECHO     --list-only
ECHO         lists the target programs but does not execute them
ECHO.
ECHO     -M
ECHO     --no-make
ECHO         does not execute CMake and make before running examples
ECHO.
ECHO     --skip-interactive
ECHO         skips examples listed in .github/ci_skip_interactive_examples.txt
ECHO         (GUI / desktop-interactive programs unsuitable for headless CI)
ECHO.
ECHO     standard flags:
ECHO.
ECHO     --help
ECHO         displays this help and terminates
EXIT /B 0


:: ############################# end of file ############################ ::
