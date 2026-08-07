# STLSoft - TODO <!-- omit in toc -->

> **NOTE**: some of the following are very old, stretching back even into the 2000s, so this list will be updated a lot over the coming months. The most glaring of these is to ensure compatibility with C++14/17/20/23/26 as is necessary.


## Table of Contents <!-- omit in toc -->

- [Functional improvements](#functional-improvements)
  - [Code changes (1.10.x)](#code-changes-110x)
  - [Code changes (1.11.x)](#code-changes-111x)
  - [Code changes (1.12+)](#code-changes-112)
  - [Abandoned TODOs](#abandoned-todos)
- [Performance improvements](#performance-improvements)
- [Packaging improvements](#packaging-improvements)
  - [Administrative (1.10.x)](#administrative-110x)
  - [Administrative (1.11.x)](#administrative-111x)
  - [Building/executing automated tests (1.11.x)](#buildingexecuting-automated-tests-111x)
  - [Administrative (1.12+)](#administrative-112)


## Functional improvements


### Code changes (1.10.x)

* [x] ~~~GitHub **README.md** badges - version, build, etc.~~~ - ✅;
* [-] ~~~STLSoft-related blog posts (focusing on new components)~~~ - ❌ (tracked under **Administrative (1.11.x)**);
* [-] ~~~fix Doxygen build~~~ - ❌ (tracked under **Administrative (1.11.x)**);
* [x] ~~~CMake~~~ - ✅;
* [ ] `invoke_ACE_OS_snprintf` should be implemented in terms of `stlsoft_C_snprintf()`;
* [ ] `invalid_integral_range_policy::operator ()` should be implemented in terms of `stlsoft_C_snprintf()`;
* [ ] `stlsoft::auto_buffer<>::copy_from()` should be template and work with other instances (with different `V_internalSize`);
* [ ] hash specialisations for all possible key types (incl. `stlsoft::basic_simple_string<>`, etc.);
* [x] ~~~final filesystem fixes (found during testing of [**recls**](https://github.com/synesissoftware/recls) 1.10's significantly improved functionality)~~~ - ✅;
* [x] ~~~apply `stlsoft::unit::string_insert()` to UNIXSTL/WinSTL `basic_path<>`~~~ - ✅;
* [x] ~~~C++ 11/14/17/20 compatibility - partial~~~ - ✅;
* [x] ~~~better documentation markup for `stlsoft::translate_thousands()`, `stlsoft::format_thousands()`, `stlsoft::integer_to_lc_string()`, `winstl::format_thousands()`, ...~~~ - ✅;
* [x] ~~~apply `stlsoft::string_insert()` to **WinSTL** time type shims~~~ - ✅;


### Code changes (1.11.x)

* [ ] find all `STLSOFT_USING_SAFE_STR_FUNCTIONS` and abstract all code to worker functions;
* [ ] integrate **STLSoft**'s exception-hierarchies with new standard exception design;
* [ ] C++ 11/14/17/20/23 compatibility - partial; further coming in 1.12;
* [ ] further system_traits refactoring:
  * [ ] joining common code via **CRTP**;
  * [ ] abstracting out string stuff (into `stlsoft::`);
  * [ ] sorting the "safe-string" stuff;
  * [ ] abstracted file-system operations such as `#make_writeable()` / `#make_readonly()`;
  * [x] ~~~**winstl/api/internal/get_home_directory_.h**~~~ - ✅;
  * [x] ~~~add `WINSTL_API_INTERNAL_System_get_home_directory_a_()` / `WINSTL_API_INTERNAL_System_get_home_directory_w_()`~~~ - ✅;
  * [x] ~~~tries first for `"USERPROFILE"` and then falls back to `"HOMEDRIVE"` and `"HOMEPATH"`~~~ - ✅;
  * [x] ~~~implement `winstl_C_get_home_directory_a()` / `winstl_C_get_home_directory_w()` (**winstl/system/directory_functions.h**) in terms of `WINSTL_API_INTERNAL_System_get_home_directory_a_()` / `WINSTL_API_INTERNAL_System_get_home_directory_w_()`~~~ - ✅;
  * [x] ~~~add **test.component.winstl.system.directory_functions**~~~ - ✅;
  * [x] ~~~implement **unixstl_C_get_home_directory_invoke_getenv_a_()** in terms of `WINSTL_API_INTERNAL_System_get_home_directory_a_()`~~~ - ✅;
* [ ] `platformstl::FILE_stream` implemented in terms of **stlsoft/api/internal/memfns.h**;
* [x] ~~~`unixstl::glob_sequence` add `skipHiddenFiles` and `skipHiddenDirs`~~~ - ✅;
* [x] ~~~`unixstl::readdir_sequence` add `skipHiddenFiles` and `skipHiddenDirs`~~~ - ✅;
* [x] ~~~standardise (via **INTERNAL**) of following~~~ - ✅:
  * [x] ~~~`ExpandEnvironmentStringsA/W()`~~~ - ✅;
  * [x] ~~~`GetEnvironmentVariableA/W()`~~~ - ✅;
  * [x] ~~~`GetModuleFileNameA/W()`~~~ - ✅;
  * [x] ~~~`GetSystemDirectoryA/W()`~~~ - ✅;
    * [x] ~~~needs to set `ERROR_INSUFFICIENT_BUFFER`~~~ - ✅;
  * [x] ~~~`GetWindowsDirectoryA/W()`~~~ - ✅;
    * [x] ~~~needs to set `ERROR_INSUFFICIENT_BUFFER`~~~ - ✅;


### Code changes (1.12+)

* [ ] C++ 11/14/17/20/23/26 compatibility — inventory remaining gaps and record concrete per-standard fixes here (partial work already tracked under **Code changes (1.11.x)**);
* [ ] syslog in variadic templates, a la `winstl::output_debug_line()`;
* [ ] Simple thread-pool (bring from **SS** work circa 2000);
* [ ] include/*stl*/error => include/*stl*/diagnostics;
* [ ] memory-mapped-file class minor issues;
* [ ] canonicalise all exception messages - consistency, lower-case, etc.;
* [ ] bring in `platformstl::properties_file` from 1.12 project;
* [ ] bring in `platformstl::temporary_directory_contents` from 1.12 project;
* [ ] move include/stlsoft/util/string/*printf.h code to api/internal, and deprecate;
* [ ] same with the include/stlsoft/std/* files;
* [ ] rename all HAS files to remove the trailing _ (as that _might_ conflict with actual symbols; in any case, have the header name exact). Maybe further disambiguate with has_file/... and has_construct/...;
* [ ] deprecate various iterator types ...;
* [ ] centralise `mbstowcs`/`mbstowcs_s` and `wcstombs`/`wcstombs_s` in single function;
* [ ] have `basic_path_buffer` use pre and post eye-catcher (`STLSOFT_DEBUG`-only);
* [ ] standard names of integer-to-string and string-to-integer to allow for coming enhancements for multiple bases;


### Abandoned TODOs

* [-] ~~~custom radix in integer_to_string - abandoned for performance reasons, and obviated by new conversion functions (oct, dec, hex) in 1.10~~~ - ❌;


## Performance improvements

* [x] ~~~optimise `char_traits<>` and/or `pod_fill_n()` block operations (e.g. in terms of `mem***()`)~~~ - ✅;
* [ ] **test.performance.stlsoft.util.bit_functions**;


## Packaging improvements


### Administrative (1.10.x)

* [x] ~~~GitHub **README.md** image features - version, build, etc.~~~ - ✅;
* [-] ~~~STLSoft 1.10-related blog posts (focusing on new components)~~~ - ❌ (tracked under **Administrative (1.11.x)**);
* [-] ~~~fix Doxygen build~~~ - ❌ (tracked under **Administrative (1.11.x)**);
* [x] ~~~CMake~~~ - ✅;


### Administrative (1.11.x)

* [x] ~~~flesh out [**README.md**](./README.md)~~~ - ✅;
* [x] ~~~convert to https://github.com/synesissoftware/STLSoft~~~ - ✅;
* [x] ~~~project documentation modernisation — **INSTALL.md**, **FAQ.md**, **EXAMPLES.md**, **KNOWN_ISSUES.md**, **HOW_YOU_CAN_HELP.md**, **AUTHORS.md**, **CHANGES.md**, **NEWS.md**~~~ - ✅;
* [x] ~~~modular GitHub Actions (**ci.yml** / **ci-cell.yml**, install-smoke, canonical push branches)~~~ - ✅;
* [x] ~~~`.sis/` project identity (**project_name.txt**, **script_info_lines.txt**) and helper-script **ProjectName** wiring~~~ - ✅;
* [x] ~~~**ctest_cmake.sh**; MSYS auto-MinGW in **prepare_cmake.sh**~~~ - ✅;
* [x] ~~~CMake **CMP0177**; **cmake/BuildType.cmake** default-type CACHE fix~~~ - ✅;
* [ ] take down https://github.com/synesissoftware/STLSoft-1.10-delta;
* [ ] fix Doxygen build (no **Doxyfile** / **generate_doxygen.sh** yet; deeper API docs still open — see [**KNOWN_ISSUES.md**](./KNOWN_ISSUES.md));
* [ ] STLSoft 1.11-related blog posts (focusing on new components);
* [ ] Website - currently http://stlsoft.org/ is *VERY* out of date;
* [ ] Set-up donation;
* [ ] Expand CI / local coverage beyond the default **C17** / **C++20** OS×compiler matrix (see dialect inventory below);


### Building/executing automated tests (1.11.x)

GitHub Actions (**ci.yml**) currently exercises the project default language levels (**C17** / **C++20** in **CMakeLists.txt**) on **clang**, **gcc**, **MinGW**, and **MSVC** across macOS, Linux, and Windows (plus install-smoke). The table below remains a manual dialect-compatibility inventory — cells are not all covered by CI.

| C++   | C   | Clang 15.0 (macOS, ARM64) | Clang 17.0 (macOS, x64) | GCC 11.4 (Linux)  | GCC 13.2 (Linux)  | GCC 14.2 (Linux)  | GCC 14.2 (MinGW, Windows) | Visual C++ 17.x (Windows) |
| ----- | --- | :-----------------------: | :---------------------: | :---------------: | :---------------: | :---------------: | :-----------------------: | :-----------------------: |
| 23    | 23  |                           | ✅                       |                   | ✅                 | ✅                 |                           |                           |
| 23    | 17  |                           | ✅                       |                   |                   |                   |                           |                           |
| 20    | 23  |                           | ✅                       |                   |                   |                   |                           |                           |
| 20    | 17  |                           | ✅                       | ✅                 | ✅                 | ✅                 | ✅                         | ✅                         |
| 20    | 11  |                           | ✅                       |                   |                   |                   |                           |                           |
| 20    | 99  |                           | ✅                       |                   |                   |                   |                           |                           |
| 20    | 90  |                           | ✅                       |                   |                   |                   |                           |                           |
| 17    | 17  |                           | ✅                       | ✅                 | ✅                 | ✅                 |                           | ✅                         |
| 17    | 11  |                           | ✅                       |                   |                   |                   | ✅                         |                           |
| 17    | 99  |                           | ✅                       |                   |                   |                   |                           |                           |
| 17    | 90  |                           | ✅                       |                   |                   |                   |                           |                           |
| 14    | 11  |                           | ✅                       | ✅                 | ✅                 | ✅                 | ✅                         | ✅                         |
| 14    | 99  |                           | ✅                       |                   |                   |                   |                           |                           |
| 14    | 90  |                           | ✅                       |                   |                   |                   |                           | ✅                         |
| 11    | 11  |                           | ✅                       | ✅                 | ✅                 | ✅                 | ✅                         | ✅                         |
| 11    | 99  |                           | ✅                       |                   |                   | ✅                 |                           |                           |
| 11    | 90  |                           | ✅                       |                   |                   |                   |                           |                           |
| 98    | 99  |                           | ✅                       | ✅                 | ✅                 | ✅                 | ✅                         | ✅                         |
| 98    | 90  |                           | ✅                       |                   | ❌                 | ❌                 |                           | ✅                         |


### Administrative (1.12+)

* [ ] DO NOT just branch over; instead, take each component at a time and consider files such as include/stlsoft/util/std/stdio_overload_detectors.hpp even still having a purpose - Maybe this is a 1.12 thing?;
* [-] ~~~VC++ common makefile(s) (legacy build trees removed; CMake-only)~~~ - ❌;


<!-- ########################### end of file ########################### -->
