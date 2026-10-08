@ECHO OFF

SETLOCAL ENABLEDELAYEDEXPANSION ENABLEEXTENSIONS

SET ScriptPath=%~n0[%~x0]
SET ScriptDir=%~dp0

IF DEFINED SIS_CMAKE_BUILD_DIR (

    SET CMakeDir=%SIS_CMAKE_BUILD_DIR%
) ELSE (

    SET CMakeDir=%ScriptDir%_build
)

SET ExpandWidth=0
SET GapGroups=0
SET ListOnly=0
SET RunMake=1

SET BuildConfig=Release
IF DEFINED CMAKE_BUILD_TYPE SET BuildConfig=%CMAKE_BUILD_TYPE%


:: #########################################################
:: command-line handling

:parse_args
IF "%~1"=="" GOTO args_done

IF /I "%~1"=="--help" GOTO show_help
IF /I "%~1"=="--expand-width" (
    SHIFT
    IF "%~1"=="" (
        ECHO %ScriptPath%: --expand-width requires an argument 1>&2
        EXIT /B 1
    )
    SET ExpandWidth=%~1
    GOTO next_arg
)
IF /I "%~1"=="--gap-groups" (
    SET GapGroups=1
    GOTO next_arg
)
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

ECHO %ScriptPath%: unrecognised argument '%~1'; use --help for usage 1>&2
EXIT /B 1

:next_arg
SHIFT
GOTO parse_args

:args_done


:: #########################################################
:: main()

IF %GapGroups% NEQ 0 (
    SET SIS_PERFTESTS_GROUPGAPS=1
)

SET status=0

IF %RunMake% NEQ 0 (
    IF %ListOnly% EQU 0 (
        ECHO Executing build and then running all performance test programs
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
    IF %ListOnly% NEQ 0 (
        ECHO Listing all performance test programs
    ) ELSE (
        ECHO Running all performance test programs
    )

    FOR /F "usebackq delims=" %%f IN (`DIR /A:-D /B /S "%CMakeDir%" 2^>NUL ^| FINDSTR /I /R "test[._]performance[._].*\.exe$"`) DO (
        IF !ListOnly! NEQ 0 (
            ECHO would execute %%f:
        ) ELSE (
            ECHO.
            ECHO executing %%f:
            IF !ExpandWidth! NEQ 0 (
                ECHO %ScriptPath%: --expand-width is not supported on Windows; running without tab expansion 1>&2
            )
            CALL "%%f"
            IF ERRORLEVEL 1 (
                SET status=1
                GOTO performance_done
            )
        )
    )
)

:performance_done
IF !status! NEQ 0 (
    ENDLOCAL
    EXIT /B 1
)
ENDLOCAL
EXIT /B 0


:: #########################################################
:: helpers

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
ECHO Runs all (matching) performance-test programs
ECHO.
ECHO %ScriptPath% [ ... flags/options ... ]
ECHO.
ECHO Flags/options:
ECHO.
ECHO     behaviour:
ECHO.
ECHO     --expand-width ^<expand-width^>
ECHO         subjects each performance test program's output to tab expansion
ECHO         with the given width (Unix shell script only)
ECHO.
ECHO     --gap-groups
ECHO         sets SIS_PERFTESTS_GROUPGAPS=1 so performance programs emit a
ECHO         blank line between scenario groups on a TTY, or a visible
ECHO         tab+hyphen rule when stdout is not a TTY (e.g. CI)
ECHO.
ECHO     -l
ECHO     --list-only
ECHO         lists the target programs but does not execute them
ECHO.
ECHO     -M
ECHO     --no-make
ECHO         does not execute CMake and make before running tests
ECHO.
ECHO     standard flags:
ECHO.
ECHO     --help
ECHO         displays this help and terminates
EXIT /B 0


:: ############################# end of file ############################ ::
