# **STLSoft** Changes <!-- omit in toc -->


## 1.11.1-rc5 - 2nd August 2026

* Fixed `stlsoft::basic_simple_string<>#resize()` — expanding a non-empty string no longer over-reads the source buffer (MinGW unit-test segfault in **test.unit.stlsoft.string.simple_string**);
* Converted **CHANGES.txt** to **CHANGES.md** and removed **HISTORY.md**;
* Project documentation modernisation — **README.md**, **FAQ.md**, **INSTALL.md**, **EXAMPLES.md**, **KNOWN_ISSUES.md**, **TODO.md**, **HOW_YOU_CAN_HELP.md**, **AUTHORS.md**; repository URLs **STLSoft-1.11** → **STLSoft**;
* **EXAMPLES.md** — replaced “T.B.C.” placeholders with concrete summaries;
* **README.md** — fleshed out Components (sub-projects / libraries); CI badge targets **ci.yml**; badge set standardised;
* CI (**ci.yml**) — concurrency cancel-in-progress; branch triggers include **dev** / **rc*** / **update**; matrix cell order;
* CMake — minimum version **3.20**; **BUILD_TESTING** option; project homepage URL; patch/revision version regex;
* Project boilerplate — **.gitattributes**, **.vimrc**, **.vscode/settings.json**;
* **test.unit.versions** — aligned with **1.11.1-rc5** (**_STLSOFT_VER_1_11_1_RC5**);


## 1.11.1-rc4 - 29th July 2026

* Added GitHub Actions CI (**.github/workflows/ci.yml**) on macOS, Linux, and Windows with **clang**, **gcc**, **MinGW**, and **Visual C++** (**cl**);
* CI jobs: six independent **ci-cell.yml** reusable workflows (build + parallel run sub-jobs per compiler/OS) plus **install-smoke**;
* MSVC CI disables **find_package(MFC)** (**CMAKE_DISABLE_FIND_PACKAGE_MFC**) — GHA has MFC headers but not **_AFXDLL** / **/MD** linkage for mfcstl tests;
* Visual C++ 18.x recognition in **stlsoft.h** (for current MSVC toolsets on **windows-latest**);
* Fixed **winstl::codepage_sequence::data()** — now returns **m_cpids.data()** (was missing **return**);
* Fixed **winstl_C_printf_debug_string()** — compare buffer length via **STLSOFT_C_CAST(int, STLSOFT_NUM_ELEMENTS(msg))** (signed/unsigned comparison with **/WX**);
* Clang cccap: 64-bit sized types use **`long long`** (not **`__INT64_TYPE__`**) so they stay distinct from **`long`** on Linux LP64 — fixes redefinition of overloads guarded by **STLSOFT_CF_LONG_DISTINCT_INT_TYPE** (e.g. **try_parse_to**);
* Allocators: reject element counts above **max_size()** before **`n * sizeof(T)`** (fixes GCC **`-Werror=alloc-size-larger-than=`**); **pid_sequence** avoids **`size() - 1`** underflow when eliding PIDs;
* **test.unit.versions** — aligned with **1.11.1-rc4** (**_STLSOFT_VER_1_11_1_RC4**);
* MinGW compatibility in **winstl/util/struct_comparers.hpp** — omit **NETWORK_APP_INSTANCE_EA**, **POWER_LIMIT_VALUE**, **SHUFFLE_FILE_DATA** byte comparers when **STLSOFT_MINGW** is defined;
* Test/example runner scripts — **--unit-only** / **--component-only** on **run_all_unit_tests.sh**; new **run_all_examples.sh** / **.cmd**; **run_all_unit_tests.cmd**, **run_all_scratch_tests.cmd**, and **execute_performance_tests.cmd** aligned with shell counterparts;
* code generation scripts;


## 1.11.1-rc3 - 23rd August 2025

* Added `platformstl::pid_sequence` / `unixstl::pid_sequence`;
* Added `winstl_C_printf_debug_string()` in **winstl/diagnostics/printf_debug_line.h**;
* Added `winstl::codepage_sequence`;
* Added Window write-to-console functions;
* More examples;
* More tests;
* Corrected some minor defects around language version detection;
* Compatibility/corrections in string-to-integer functions;
* Canonicalise example programs source names;
* Backwards compatibility (partial) for Visual C++ back to v10;
* Project boilerplate;


## 1.11.1-rc2 - 31st May 2025

* Added `stlsoft::member_selector_view<>` (alpha version), for span-compatibility in **recls**;
* Change semantics of `stlsoft::auto_buffer<>#resize()` the size of external allocation is maintained such that shrinking and then regrowing may be done within the existing allocation;
* InetSTL / UNIXSTL / WinSTL architecture discrimination canonicalised, expanded, and corrected;
* Substantial refactoring and testing of `winstl::filesystem_traits<>`;
* Significant improvements to compatibility with different C and C++ language versions (C90, C99, C11, C17, C23, C++98, C++11, C++14, C++17, C++20, C++23) - detailed in TODO.md;
* Added compatibility with latest Visual C++ (`_MSC_VER` == 1944);
* **test.component.inetstl.util.uds_helpers** now works correctly for both Linux and macOS;
* Brought over several test programs exercising C APIs;
* **run_all_scratch_tests.sh** now accepts '--verbosity' option;


## 1.11.1-rc1 - 6th May 2025

* Various CMake improvements;
* MinGW compatibility;
* **UNIXem** compatibility;
* Windows compatibility;


## 1.11.1-beta9 - 5th May 2025

* `stlsoft::basic_string_view` fixed defect in comparison;
* **example.platformstl.filesystem.readdir_sequence** minor fix;


## 1.11.1-beta8 - 3rd May 2025

* Added skipping of hidden directories and files to `unixstl::glob_sequence` and `unixstl::readdir_sequence`;
* Various example improvements;
* Updated **TODO.md** with structure and items;


## 1.11.1-beta7 - 30th April 2025

* Support for searching of devices on the file system, primarily concerning `unixstl::glob_sequence` and `unixstl::readdir_sequence`;


## 1.11.1-beta6 - 28th April 2025

* Visual C++ compatibility (including _MSC_VER 1943);
* CMake / UNIXem compatibility;
* Refactored / enhanced retrieval of home-directory, including, for Windows, trying first for `"USERPROFILE"` and then falls back to `"HOMEDRIVE"` and `"HOMEPATH"`;
* **prepare_cmake.sh** / **CMakeLists.txt** : + added '--no-shwild' / `CMAKE_NO_SHWILD`;
* Added **test.component.winstl.system.directory_functions**;


## 1.11.1-beta5 - 26th April 2025

* Added `platformstl::environment_variable_scope`;
* Added more unit-tests;
* MinGW compatibility;
* `stlsoft::basic_static_string<>` minor fix;
* Miscellaneous fixes;


## 1.11.1-beta4 - 22nd April 2025

* `unixstl::glob_sequence` now can search for sockets, in addition to files and directories;
* `stlsoft::cmdargs` added missing member types;


## 1.11.1-beta3 - 16th April 2025

* Added specialisations of `integral_traits<>` for integer specialisations of `true_typedef<>`;
* Applied `printf()` format attributes throughout;
* Defect fix(es) to `unixstl::path_squeeze<>()` / `winstl::path_squeeze<>()`;
* MinGW compatibility;
* Wholesale trivial/minor tidying;


## 1.11.1-beta2 - 23rd February 2025

* `unixstl::readdir_sequence` now can search for sockets, in addition to files and directories;
* added **inetstl/util/uds_helpers.h** that provides Unix Domain Sockets helper functions;
* GCC (11) compatibility around use of `__builtin_is_constant_evaluated` (when not C++20);
* **InetSTL** improved compatibility with macOS / Linux;


## 1.11.1-beta1 - 31st December 2024

* Command-line handling components minor improvements and unit-testing;
* Visual C++ compatibility (including _MSC_VER 1942);
* MinGW compatibility;
* Miscellaneous backwards-compatibility fixes;
* Miscellaneous (near) final fixes and tidying;


## 1.11.1-alpha28 - 28th December 2024

* substantial reworking of abstraction of memory functions, resulting in performance improvements across numerous components, `stlsoft::auto_buffer<>` in particular;
* MinGW compatibility;
* miscellaneous generalisation of code and dependencies;
* added more test programs;


## 1.11.1-alpha27 - 19th December 2024

* added `stlsoft::doomgram` and `stlsoft::gram_scope` (from old research repo(s));
* added **include/stlsoft/diagnostics/gram_utils.hpp**, including `stlsoft::gram_to_strip()`;
* added `stlsoft::count_hexadecimal_digits()`, and refactored `stlsoft::count_digits()` into `stlsoft::count_decimal_digits()`;
* added **unixstl/time/comparison_functions.h**, including `unixstl_C_compare_timevals()` / `unixstl::compare()`;
* added `winstl_C_difference_in_microseconds_QPC()` and `winstl_C_absolute_difference_in_microseconds_QPC()`;
* `winstl::micro_sleep()` (and `winstl_C_micro_sleep()`) now implemented in terms of active methods for accurate behaviour in small durations (0 < delay_us <= 250000);
* added `#pause()` and `#unpause()` to stopwatch types (incl. `stlsoft::std_chrono_hrc_stopwatch`, `unixstl::stopwatch()`, `winstl::stopwatch()`);
* added `#get_kernel_nanoseconds()`, `#get_user_nanoseconds()`, `#get_nanoseconds()` to `unixstl::stopwatch()`;
* added `#cbegin()` / `#cend()` and `#crbegin()` / `#crend()` methods to `stlsoft::auto_buffer<>`;
* separated Windows-specific `platformstl::readdir_sequence` into `winstl::readdir_sequence`;
* added **test.component.platformstl.diagnostics.stopwatch**;
* added **test.performance.stlsoft.count_digits**;
* added **test.performance.stlsoft.doomgram**;
* added **test.performance.stlsoft.gram_utils**;
* added **test.scratch.winstl.micro_sleep**;
* added **test.unit.stlsoft.diagnostics.doomgram**;
* added **test.unit.stlsoft.diagnostics.gram_scope**;
* added **test.unit.stlsoft.util.count_decimal_digits**;
* added **test.unit.stlsoft.util.count_hexadecimal_digits**;
* added **test.unit.winstl.conversion.number.grouping_functions**;
* **run_all_unit_tests.sh** now respects environment variables `XTESTS_VERBOSITY` and `TEST_VERBOSITY`;
* miscellaneous minor/trivial improvements;


## 1.11.1-alpha26 - 23rd November 2024

* added `stlsoft::integral_traits<>` (**stlsoft/traits/integral_traits.hpp**);
* added `stlsoft::unicode_point_map`;
* added **test.unit.stlsoft.limits.integral_limits**;
* added **test.unit.stlsoft.traits.integral_traits**;
* minor tidying to CMake facilities;


## 1.11.1-alpha25 - 18th November 2024

* added MSVC MT support;
* added and applied macro `STLSOFT_IS_CONSTANT_EVALUATED()`, in particular to `stlsoft::auto_buffer<>`;
* include ordering (around api/internal / api/external helper headers);
* copy-paste typos;
* made consistent include ordering (around api/internal / api/external helper headers);


## 1.11.1-alpha24 - 4th November 2024

* `frequency_map` : ~ now default-specialised on `frequency_map_traits_unordered` when compiling with C++11+;
* **test.performance.stlsoft.frequency_map** : ~ improved reporting of results ; ~ now uses `stlsoft::std_chrono_hrc_stopwatch`;


## 1.11.1-alpha23 - 28th October 2024

* `platformstl::basic_file_lines<>` now supports move semantics;
* Fix to definition of `STLSOFT_MESSAGE_ASSERT()` (for Clang);
* **dev/bin/batch_compile_check** now supports '--counts' flag;
* Minor improvements of ./CMakeLists.txt;


## 1.10.12 - 28th October 2024

* project boilerplate updated (in line with STLSoft-1.11);


## 1.11.1-alpha22 - 26th October 2024

* Single fix to default definition of `STLSOFT_FALLTHROUGH()`;


## 1.11.1-alpha21 - 25th October 2024

* Added and applied macro `STLSOFT_FALLTHROUGH()`;
* Added unit-tests for allocator types;


## 1.11.1-alpha20 - 23rd October 2024

* Version change only;


## 1.11.1-alpha19 - 23rd October 2024

* Fixes to (new functionality in) `stlsoft::auto_buffer<>`;
* Fix for (compile-time) defect in `winstl::basic_path<>`;
* Fix for defect in `winstl::basic_reg_key<>`;
* MinGW compatibility in **winstl/internal/windows_version_.h**;
* MinGW compatibility in **winstl/system/console_functions.h**;
* Necessary warning suppression in `stlsoft::basis_simple_string<>`;
* Trivial warning fix in `winstl::readonly_memory_mapped_file<>`;
* Added **test.unit.stlsoft.traits.integral_printf_format_traits**;
* Brought over **test.unit.winstl.registry.reg_value**;
* Added **test.unit.winstl.registry.reg_value_sequence**;
* GCC warnings;
* CMake build scripts minor fixes;


## 1.11.1-alpha18 - 15th October 2024

* Legacy (pre VS-2022) Visual C++ compatibility;
* Win32 compatibity;


## 1.11.1-alpha17 - 13th October 2024

* `stlsoft::frequency_map<>` enhancements;
* `unixstl::glob_sequence` enhancements;
* Fixes and enhancement to `dl_call<>()` (both UNIXSTL and WinSTL);
* BREAKING CHANGE: Prospective compatibility with C++20 reserved word `module` (both UNIXSTL and WinSTL) by renaming existing `module` class to `dl_module`;
* GCC 11 compatibility;
* GCC 14 compatibility;
* MinGW-64 compatibility;
* VC++ 17 compatibility;
* General improvements and simplification for compatibility with C++11 - C++20;
* CMake build files improvements;
* Misc. minor fixes and enhancements;
* Misc. code canonicalisation;
* Bringing into repo existing (older) test and example programs;


## 1.11.1-alpha16 - 1st October 2024

* `auto_buffer` improvements;
* `constexpr` applications;
* Time function enhancements;
* Brought over previously unreleased example and test programs;
* Significant simplification of CMake support;
* Boilerplate file improvements;
* Miscellaneous improvements;


## 1.11.1-alpha15 - 2nd September 2024

* Windows ARM64 architecture support;
* Windows 10/11 operating system detection support;
* significant simplification of CMake support;
* minor additions/enhancements to scratch tests;
* miscellaneous fixes;


## 1.11.1-alpha14 - 21st August 2024

* VC++ 17 latest (`_MSC_VER`==1941) compatibility;


## 1.11.1-alpha13 - 4th August 2024

* added `platformstl::isatty()` (and `platformstl::platformstl_C_isatty_fd()` and `platformstl::platformstl_C_isatty_stm()`), `unixstl::isatty()` (and `unixstl::unixstl_C_isatty_fd()` and `unixstl::unixstl_C_isatty_stm()`), `winstl::isatty()` (and `winstlstl::winstlstl_C_isatty_fd()` and `winstlstl::winstlstl_C_isatty_stm()`);


## 1.11.1-alpha12 - 3rd August 2024

* `unixstl::readdir_sequence` no longer uses `stlsoft::basic_static_string<>`;
* simplifying CMake compatibility;
* VC++17 compatibility;
* minor fixes;
* now depends on xTests 0.24+;


## 1.11.1-alpha11 - 16th July 2024

* CMake compatibility fixes;


## 1.11.1-alpha10 - 14th July 2024

* Fixing upper limit to **xTests** version as <0.23, in anticipation of imminent changes to **xTests**;
* Compatibility with latest VC++ 17 (with Visual Studio 2022 version 17.10.1, _MSC_FULL_VER=194033811);


## 1.11.1-alpha9 - 9th July 2024

* Missing fix to `stlsoft::basic_simple_string`'s `#assign()`;


## 1.11.1-alpha8 - 9th July 2024

* Added `platformstl::get_home_directory()` and related functions;
* GCC compatibility improvements;
* CMake improvements;
* Boilerplate file improvements;
* More examples and test programs;


## 1.11.1-alpha7 - 5th May 2024

* Visual C++ (17) compatibility;
* Windows compatibility for CMake;
* Miscellaneous changes;


## 1.11.1-alpha6 - 29th March 2024

* added unit-test projects **test.unit.stlsoft.conversion.number.group_functions** and **test.unit.stlsoft.conversion.integer_to_lc_string**;
* partial merge of forthcoming branch 'ss/simple_string-null_object';


## 1.11.1-alpha5 - 29th March 2024

* various GCC-11 compatibility fixes;


## 1.11.1-alpha4 - 18th March 2024

* `stlsoft::basic_simple_string<>` now has `#equal()`;
* added 'stlsoft::std_chrono_hrc_stopwatch' stopwatch type;
* various performance improvements;


## 1.11.1-alpha3 - 16th March 2024

* `stlsoft::basic_simple_string<>` now has `#contains()`;
* `stlsoft::basic_static_string<>` now has `#contains()`;
* wholesale automated layout canonicalisation;


## 1.11.1-alpha2 - 1st March 2024

* True-Typedef supports stream-insertion (`operator <<()`):;
* added `stlsoft::write_string<>()`;
* miscellaneous fixes (including C++14/17/20 compatibility);


## 1.11.1-alpha1 - 20th February 2024

* added `stlsoft::integer_to_base32_string<>()` integer to Base-32-string conversion;
* added `stlsoft::integer_to_base36_string<>()` integer to Base-36-string conversion;
* `stlsoft::basic_simple_string<>` now has `#starts_with()` and `#ends_with()`;
* `stlsoft::basic_static_string<>` now has `#starts_with()` and `#ends_with()`;
* `stlsoft::basic_static_string<>` now has `#substr()`;
* `stlsoft::basic_static_string<>` now has `#front()` and `#back()`;
* `stlsoft::basic_static_string<>` consistently and correctly throws exceptions on any operations that would cause exceeding of internal storage;
* improvement to string insertion helper `string_insert()` to work with stream types that do and do not provide `sentry`;
* added **test.unit.unixstl.filesystem.path** unit-test project;


## 1.10.11 - 16th February 2024

* project boilerplate;
* corrected inappropriate use of `ss_typename_param_k`;


## 1.10.10 - 16th February 2024

* further tranche of stream insertion operator implementations;
* fixes and enhancements to `stlsoft::util::string_insert`;
* added `stlsoft::meta::hash_sentry` meta-type;
* added test.unit.unixstl.filesystem.path test project;


## 1.10.9 - 12th February 2024

* stlsoft::frequency_map uses traits to select between ordered and unordered representation;
* added test.unit.stlsoft.containers.frequency_map project;
* C++98 compatibility;


## 1.10.8 - 6th February 2024

* added dev/bin/batch_compile_check;
* language compatibility fix;
* iterator definition fixes (related to C++17 deprecation of std::iterator);


## 1.10.7 - 30th January 2024

* enhanced stream insertion operators, when used with types descended from `std::basic_ios<>`, to observe width and alignment for `stlsoft::basic_shim_string<>`, `stlsoft::basic_simple_string<>`, `stlsoft::basic_static_string`, `stlsoft::basic_string_view`, `stlsoft::stlsoft_C_string_slice_m_t`/`stlsoft::stlsoft_C_string_slice_w_t`;
* refactored (almost) all direct calls to disparate parts of the `printf()`-family to use the STLSoft abstractions;
* wholesale refinement of whitespace around conditional control statements;
* large number of minor and trivial tidyings;


## 1.10.6 - 28th January 2024

* simplification and improvement of CMake handling;
* dependency on xTests is now optional (in prepare_cmake.sh);
* now depends on xTests 0.21.2;
* CMake C language now C11;
* fixed defect in `stlsoft::pod_vector`;


## 1.10.5 - 18th January 2024

* C++20 and C17 compatibility changes, including `std::allocator_traits`, allocator hints, tightening rules on anonymous enums;
* brought over (from internal repository) more unit tests, for: `pod_vector`, `auto_buffer`, `shim_string`, `simple_string`, `static_string`;
* stlsoft::pod_vector now default-initialses elements in size-constructor;


## 1.10.4 - 16th January 2024

* C++17 compatibility, including: allocators, binders, auto_ptr;
* unixstl::semaphore now fully implemented on Mac OSX;
* unixstl::synchronisation_exception modern C++ compatibility;
* added supporting test (for unixstl::semaphore);
* marked relevant files with 'STLSOFT:DEPRECATED' and 'STLSOFT:FILE_NOT_SELF_SUFFICIENT' to simplify automated compatibility checks;


## 1.10.3 - 12th January 2024

* warnings fix (Issue 14);
* include/unixstl/filesystem/path_functions/classify_functions_X_.h - GCC / Clang warning;
* include/winstl/filesystem/path_functions/classify_functions_X_.h - GCC / Clang warning;
* fixed sub-project versions (Issue 15);
* include/comstl/comstl.h - ~ fixed sub-project version;
* include/inetstl/inetstl.h - ~ fixed sub-project version;
* include/unixstl/unixstl.h - ~ fixed sub-project version;
* include/winstl/winstl.h - ~ fixed sub-project version;
* include/stlsoft/conversion/sas_to_string.hpp - typo;
* include/stlsoft/util/std/iterator_helper.hpp - typo;
* include/winstl/filesystem/path.hpp - typo;
* minor fixes to project boilerplate;


## 1.10.2 - 3rd January 2024

* include/comstl/collections/safearray_sequence.hpp - defect fix in `safearray_sequence.empty()`;
* include/unixstl/filesystem/filesystem_traits.hpp - removing unused / repetitive code;
* include/unixstl/filesystem/readdir_sequence.hpp - various fixes, including significant defect whereby path would not be updated correctly (leading to FH exhaustion with recls);
* include/winstl/filesystem/filesystem_traits.hpp - removing unused / repetitive code;
* MinGW 64-bit compatibility improvements;
* large number of trivial / whitespace consistency fixes;


## 1.9.136 - 15th December 2023

* lots of changes to standardise the library boilerplate;
* porting back significant and necessary fixes from STLSoft-1.10;


## 1.10.1 - 13th December 2023

* CMake support;


## 1.10.1 beta 33 - 26th April 2021

* Clang compatibility;


## 1.10.1 beta 32 - 26th April 2021

* GCC/Clang compatibility;


## 1.10.1 beta 31 - 2nd April 2021

* Clang compatibility;
* provision for customising inline (in C compilation);
* warnings;


## 1.10.1 beta 30 - 29th March 2021

* Clang compatibility;
* warnings;


## 1.10.1 beta 29 - 16th February 2021

* a whole lot of Clang- and GCC-compatibility;


## 1.10.1 beta 28 - 18th January 2021

* added character-array overloads of fast_strftime();
* WinSTL hard link information functions now work for directories as well as files;
* various defect fixes;


## 1.10.1 beta 27 - 10th January 2021

* added string access shims for std::chrono type(s);
* some GCC compatibility tweaks;


## 1.10.1 beta 26 - 4th January 2021

* added (UNIXSTL and WinSTL) Path Classification API (from 1.12 work), which work with Windows UNC and long-path root designators and all slash conventions;
* added (UNIXSTL and WinSTL) path parsing function - include/???stl/filesystem/path_parse_functions.h, presenting a consistent set of functions centralised from disparate parts of the libraries;
* BREAKING CHANGES: (UNIXSTL and WinSTL) basic_path<> methods get_file() and get_ext() now return slices, and get_ext() changed semantics to include '.';
* (UNIXSTL and WinSTL) basic_path<> added move semantics and get_location() method and made swap() method public, as well as numerous defect fixes and consistency improvements implemented in terms of new Path Classification API;
* (UNIXSTL and WinSTL) filesystem_traits<> added path classification and path parsing methods, as well as numerous defect fixes;
* updated copyright info for all files, from Synesis Software to Synesis Information Systems;
* stlsoft::basic_path_buffer<> added resize(), back(), front() methods;
* added added stlsoft_C_(str|wcs)nicmp();
* raw (C) string slice types moved out of stlsoft:: namespace in C++;
* C++14 compatibility;
* a whole lot of work to reduce dependencies;
* many improvements to GCC compatibility;
* all uses of memcpy() and memset() now in terms of abstractions (in stlsoft/api/internal/memfns.h);
* BREAKING CHANGES: ~ abstracted out string-handling from *stl::system_traits<> into stlsoft::c_string_traits<>, and removed several unused (and sketchy) functions;


## 1.10.1 beta 25 - 14th December 2020

* added two more files missing from beta 23 - D'oh!;


## 1.10.1 beta 24 - 13th December 2020

* added file unixstl/filesystem/path_buffer.hpp missing from beta 23;


## 1.10.1 beta 23 - 13th December 2020

* basic_file_path_buffer<> is now deprecated in all projects, and all dependent components are modified to use other facilities;
* added platformstl::environment_variable<> class template;
* added (in)equality operators for stlsoft::error_desc;
* added stlsoft::basic_path_buffer<> component, as an alternative to basic_file_path_buffer<>;
* stlsoft::auto_buffer<> class template copy_from() method, and ctor and resize() method that take value for initialisation of (new) elements;
* added stlsoft::strnpbrkn()/wcsnpbrkn() (and added stlsoft_C_(str|wcs)npbrkn());
* added move constructor to unixstl::module and winstl::module;
* large number of new methods and defect fixes in (platformstl|unixstl|winstl)::filesystem_traits;
* large number of new methods and defect fixes in (platformstl|unixstl|winstl)::system_traits;


## 1.10.1 beta 22 - 29th November 2020

* added stlsoft::string_to_integer_range();
* added stlsoft::strnchr(), stlsoft::strnistrn(), stlsoft::strnstrn() C-style string search functions;
* added move constructor to stlsoft::auto_buffer<>;
* added move constructor for stlsoft::scoped_handle<>;
* added move constructor for stlsoft::(basic_)simple_string<>;
* winstl::output_debug_line() overloads expanded to 16-parameters, and changed to use variadic templates where supported;
* stlsoft::split() functions enhanced to: return vector of arbitrary length; allow heterogeneous types for the split elements;
* stlsoft::string_switch() split into two overloads to handle property and unambiguously flag enums, regular enums, and enum classes;
* significant, BREAKING changes to stlsoft::try_parse_to() overloads to avoid ambiguity;
* changed significantly the way in which stlsoft::cstring_maker works, and adjusted all dependent code;
* various additions for compatibility with std::string_view (which is very similar to stlsoft::string_view);
* fixed case of a bunch of headers;


## 1.10.1 beta 21 - 27th July 2020

* VC++ 15/16 compatibility;
* fixed unixstl::readdir_sequence::empty();


## 1.9.135 - 27th July 2020

* VC++ 15/16 compatibility;
* fixed unixstl::readdir_sequence::empty();


## 1.10.1 beta 20 - 4th July 2020

* fixed detecton of shared_ptr and unique_ptr;


## 1.10.1 beta 19 - 4th July 2020

* added stlsoft::t2w, stlsoft::w2t, stlsoft::t2a, stlsoft::a2t for upcoming Pantheios release;
* added stream insertion operator (generic) for string slice types;
* added compatibility with Visual C++ 15.x and 16.x;
* added support for the ARM architecture (christopherplawrence);


## 1.9.134 - 4th July 2020

* added compatibility with Visual C++ 15.x and 16.x;
* added stlsoft::t2w, stlsoft::w2t, stlsoft::t2a, stlsoft::a2t for upcoming Pantheios release;


## 1.9.133 - 13th June 2020

* Add support for the ARM architecture when doing Android NDK GCC compilation;


## 1.10.1 beta 18 - 31st October 2019

* added stlsoft/system/environment/functions.hpp to enhances stlsoft::environment_variable_exists() with string access shims to support arbitrary string type;
* remove vestigial (and erroneous) winstl/string/spin_policies.hpp;
* various documentation fixes;


## 1.10.1 beta 17 - 24th October 2019

* GCC 8 compatibility;
* GCC 9 compatibility;
* implemented WinSTL_C_FileInformation_get_SECURITY_DESCRIPTOR_w();
* improved documentation;


## 1.10.1 beta 16 - 13th October 2019

* added stlsoft_C_environment_variable_exists_a() / environment_variable_exists() (from STLSoft 1.10-alpha);
* added stlsoft::count_bits(int) overload;
* added cbegin(), cend(), crbegin(), crend() to platformstl::environment_map;
* significant additions and removals of WinSTL file creation functions;
* added WinSTL security functions (from STLSoft 1.10-alpha);
* recognising Mac OSX architecture as UNIX;
* canonicalising '\file' description sections;
* suppresses deprecation warning from reporting use of deprecated functions inside other deprecated functions;


## 1.9.132 - 11th October 2019

* GCC 4.8, 4.9 compatibility;
* PlatformSTL now recognises Mac OSX as UNIX implicitly;
* fixed up project files (README, NEWS, etc.);


## 1.10.1 beta 15 - 13th September 2019

* added stlsoft::fast_strftime() and stlsoft::fast_wcsftime() as drop-in replacements for std::strftime() and std::wcsftime();
* added get_ptr() shim overload for std::shared_ptr and std::unique_ptr;
* added stlsoft::get_top() attribute shim;
* stlsoft::basic_string_view<>::substr();
* added winstl_C_format_message_strerror_w();
* removed stlsoft::literal_cast<>;
* various portability improvements to newer compilers;


## 1.10.1 beta 14 - 4th August 2019

* added SECURITY_DESCRIPTOR helpers();
* stlsoft::w2m and stlsoft::m2w now more general;


## 1.10.1 beta 13 - 16th April 2019

* fixed STLSOFT_ALWAYS_FALSE() / STLSOFT_ALWAYS_TRUE();
* platformstl::FILE_stream : ~ fixing character-encoding function selection defect;
* canonicalising source file structure;


## 1.10.1 beta 12 - 26th December 2018

* added sas_to_string() (and related) functions;
* added stlsoft::errno_exception (from 1.12 branch);
* added stlsoft::locale_scope;
* STLSoft's struct tm String Access Shims now work for arbitrary locale;
* UNIXSTL's timeval String Access Shims now work for arbitrary locale;


## 1.10.1 beta 11 - 22nd December 2018

* stlsoft::ref_ptr : + borrow(); + own();
* winstl::environment_variable : + data(); + equal(); + equal_ignore_case(); + exists(); + operators ==() and !=();


## 1.10.1 beta 10 - 20th December 2018

* winstl::process_mutex() now takes an optional EVENT handle which will be signalled if the mutex experiences an abandoned acquire;
* special_string_instance now provides generic (SAS) (in)equality operators automatically;
* try_parse_to_bool() semantics firmed up;


## 1.10.1 beta 9 - 12th June 2018

* Borland compatibility;


## 1.10.1 beta 8 - 11th June 2018

* fixing break to UNIX-compatibility introduced in beta-6/7;


## 1.10.1 beta 7 - 9th June 2018

* auto_buffer<> now supports limited form of pointer arithmethic via operator -();
* added subscript operator for auto_array_destructor<>;
* VC++ 14.1x compatibility;
* refactoring of copy-proscriptions;


## 1.10.1 beta 6 - 9th June 2018

* refactored in terms of external API;
* removed empty/meaningless "compatibility" sections;
* canonicalising proscribed construction methods;
* simplifying, and prospective changes (for getting to 1.12);


## 1.10.1 beta 5 - 15th May 2017

* enhanced STLSOFT_SUPPRESS_UNUSED() to work with rvalues;


## 1.10.1 beta 3 - 19th February 2017

* a whole bunch of non-functional changes to make the codebase more consistent and amenable to further automatic instrumentation by script auto-validation script compatibility, and ensure all files have full inclusion control;
* fixing get_FILE_ptr() shim namespace issues;
* winstl::token_information has additional compatibility up to W8/Svr12, and now defaults to throwing instances of winstl::security_exception;


## 1.10.1 beta 2 - 28th January 2017

* work on STLSoft integer_to_string functions to loosen non-array forms' preconditions, reduce dependencies in rest of codebase to integer_to_decimal_string()-only;
* filesystem_traits - refactored is_dots() and starts_with_dots() to accomodate GCC 4.9 pedanticism;
* exposing unixstl/winstl types spin_mutex_no_yield and spin_mutex_yield to platformstl namespace;
* a large number of changes to improve compatibility with UNIX, Clang, GCC, and MinGW;
* hiding/suppressing unused typedefs;


## 1.10.1 beta 1 - 14th January 2017

* too many changes to list here - it's a new world! (Bit of a shame it took 10 years to get here :$);
* in summary:;
* major reworking of exceptions hierarchy, including provision of project and library identifiers, status-code, and message translation;
* several new special-string-instance types, including home_directory, host_name, temporary_directory, temporary_file_name;
* new string access shims, for types including timeval, type_info;
* new attribute shims, including: get_synch_handle, get_FILE_ptr;
* new logical shims, including: is_empty, is_null;
* new high-performance conversion functions (based around the extant technology in stlsoft::integer_to_string()): integer_to_decimal_string(), integer_to_hexadecimal_string(), integer_to_octal_string(), integer_to_lc_string(), integer_to_zero_padded_decimal_string();
* new conversion parsing functions: string_to_bool(), string_to_integer();
* new scoped_method class template;
* new scoped_lambda class template;
* new bit-testing functions;
* substantially improved atomic function support;
* substantially improved spin_mutex class templates and policies;
* new diagnostic stopwatch classes and logging functions;
* new platformstl::file_stream_base class template and policies;
* new string slice classes that are compatible (but do not depend on) other Synesis projects (such as FastFormat and Pantheios);
* new time comparison functions and operators, conversion cast and functions, elicitation functions, modification functions, and validation functions;
* ... and many many other improvements and additions ..;


## 1.9.131 - 2nd November 2016

* added ss_typename_void_k;


## 1.9.130 - 1st October 2016

* minor tidyings;


## 1.9.129 - 17th July 2016

* minor tidyings STLSoft;
* stlsoft/internal/cccap/borland.h:;
* added STLSOFT_CF_FUNC_SYMBOL_SUPPORT;
* stlsoft/stlsoft.h:;
* added discrimination of STLSOFT_CF_FUNC_SYMBOL_SUPPORT WinSTL;
* winstl/filesystem/file_path_buffer.hpp:;
* added capacity();
* fix to copy-ctor;


## 1.9.126 - 4th May 2016

* improvements to Windows Registry library;


## 1.9.125 - 14th February 2016

* various minor warnings / compiler compatibilities;


## 1.9.124 - 15th November 2015

* MSVC++ does not support __func__;


## 1.9.123 - 15th November 2015

* added STLSOFT_NOEXCEPT;
* changed no-throw declaration from stlsoft_throw_0() to STLSOFT_NOEXCEPT;
* STLSOFT_CF_EXPLICIT_KEYWORD_SUPPORT => STLSOFT_CF_explicit_KEYWORD_SUPPORT;
* STLSOFT_CF_MUTABLE_KEYWORD_SUPPORT => STLSOFT_CF_mutable_KEYWORD_SUPPORT;
* STLSOFT_CF_BUILTIN_nullptr_SUPPORT => STLSOFT_CF_nullptr_KEYWORD_SUPPORT;
* STLSOFT_CF_OVERRIDE_KEYWORD_SUPPORT => STLSOFT_CF_override_KEYWORD_SUPPORT;
* STLSOFT_CF_constexpr_KEYWORD_SUPPORT;
* STLSOFT_CF_final_KEYWORD_SUPPORT;
* added token_information<>::get(), token_information<>::size();
* correct use of deallocate();


## 1.9.122 - 1st November 2015

* added STLSOFT_PRETTY_FUNCTION_SYMBOL;
* now prefers __func__ over __FUNCTION__ for STLSOFT_FUNCTION_SYMBOL;
* added (recognition of) support for nullptr;
* added (recognition of) support for static_assert;
* added ss_override_k / STLSOFT_CF_OVERRIDE_KEYWORD_SUPPORT;
* added STLSOFT_DEBUG;
* Clang compatibility;
* Windows-emulation compatibility;
* replaced dodgy use of memset();
* forward compatibility with 1.10+;


## 1.9.121 - 26th September 2015

* stlsoft/conversion/char_conversions.hpp:;
* stlsoft/conversion/truncation_test.hpp:;
* stlsoft/internal/cccap/clang.h:;
* stlsoft/util/integral_printf_traits.hpp:;
* stlsoft/util/limit_traits.h:;
* stlsoft/util/std/iterator_helper.hpp:;
* Clang-compatibility;
* winstl/util/struct_initialisers.hpp:;
* VC++ 11/12/14 compatibility;


## 1.9.120 - 9th September 2015

* stlsoft/memory/auto_buffer.hpp:;
* optimised swap() method (when swapping between to instances using internal buffer);
* comstl/conversion/interface_cast.hpp:;
* VC++ 14 compatibility;
* platformstl/system/console_functions.h;
* unixstl/system/console_functions.h;
* unixstl_C_get_console_width() / unixstl::get_console_width();
* winstl/conversion/char_conversions.hpp:;
* added t2m and m2t in multibyte compilations;
* winstl/toolhelp/*.hpp:;
* widestring-compatible;


## 1.9.119 - 26th August 2015

* Visual C++ 14 (Visual Studio 2015) compatibility;
* compatibility with GCC 4.x's LLVM library;
* 64-bit compatibility fixes;
* various fixes for increased compiler pedanticism;
* corrections to ensure that all .h files are C-compatible;
* forward-compatibility (to STLSoft 1.12) for numerous macros;


## 1.9.118 - 31st May 2014

* added Visual C++ 12 (VS 2013) compatibility;
* added struct initialisers for CONSOLE_SCREEN_BUFFER_INFO & CONSOLE_SCREEN_BUFFER_INFOEX;
* added second overload of winstl::filesystem_traits::ensure_dir_end() that takes a pointer to a length-added counter variable;
* added forward-compatibility with STLSoft 1.10's substantially enhanced and expanded synchronisation exception hierarchy to Synchronisation Library types;
* added winstl::system_traits::get_home_directory() (although it's only operative in 1.10+ or when using 1.10 alpha with 1.9);
* various minor fixes;
* various minor changes;
* stlsoft/internal/cccap/borland.h:;
* stlsoft/internal/cccap/como.h:;
* stlsoft/internal/cccap/dmc.h:;
* stlsoft/internal/cccap/gcc.h:;
* stlsoft/internal/cccap/intel.h:;
* stlsoft/internal/cccap/msvc.h:;
* stlsoft/internal/cccap/mwerks.h:;
* stlsoft/internal/cccap/sunpro.h:;
* stlsoft/internal/cccap/unknown.h:;
* stlsoft/internal/cccap/vectorc.h:;
* stlsoft/internal/cccap/watcom.h:;
* tidying up use of non-standard names;
* stlsoft/stlsoft.h:;
* stlsoft/string/split_functions.hpp:;
* layout changes;
* acestl/acestl.hpp:;
* atlstl/atlstl.hpp:;
* comstl/comstl.h:;
* dotnetstl/dotnetstl.hpp:;
* dotnetstl/string/string_accessor.hpp:;
* fixed missing qualification of IntPtr;
* inetstl/inetstl.h:;
* mfcstl/mfcstl.hpp:;
* wtlstl/wtlstl.hpp:;
* unixstl/filesystem/glob_sequence.hpp:;
* implementation function unused-parameter warning suppressed;
* unixstl/filesystem/readdir_sequence.hpp:;
* unixstl/synch/process_mutex.hpp:;
* unixstl/synch/semaphore.hpp:;
* unixstl/synch/thread_mutex.hpp:;
* changed case in exception message;
* unixstl/unixstl.h:;
* winstl/error/error_desc.hpp:;
* adjustments for improving compiler compatibility;
* now more flexibly handles different error constant types (with meta-logic to enforce integral type are not too-large for represenation);
* winstl/error/error_functions.h:;
* fixed counting defect, whereby some strings end up being oversized;
* winstl/filesystem/filesystem_traits.hpp:;
* added second overload of ensure_dir_end() that takes a pointer to a length-added counter variable;
* winstl/filesystem/findfile_sequence.hpp:;
* minor correction to documentation markup;
* winstl/registry/reg_key.hpp:;
* winstl/registry/reg_key_sequence.hpp:;
* winstl/registry/reg_value_sequence.hpp:;
* winstl/shims/access/string/time.hpp:;
* rearrangement;
* winstl/synch/event.hpp:;
* winstl/synch/process_mutex.hpp:;
* winstl/synch/semaphore.hpp:;
* winstl/synch/tss_index.hpp:;
* forward-compatibility with STLSoft 1.10's substantially enhanced and expanded synchronisation exception hierarchy;
* winstl/system/system_traits.hpp:;
* added get_home_directory() (though only operative in 1.10 or 1.9 + 1.10 alpha);
* added get_home_directory() (although it's only operative in 1.10+ or when using 1.10 alpha with 1.9);
* winstl/time/conversion_functions.h:;
* corrected pre-conditions;
* winstl/util/struct_initialisers.hpp:;
* added in CONSOLE_SCREEN_BUFFER_INFO;
* added in CONSOLE_SCREEN_BUFFER_INFOEX;
* winstl/winstl.h:;


## 1.9.117 - 16th February 2013

* added Visual C++ 11 compatibility;
* various minor changes;
* stlsoft/stlsoft.h:;
* stlsoft/util/std/iterator_helper.hpp:;
* stlsoft/util/std/library_discriminator.hpp:;
* stlsoft/string/char_traits.hpp:;
* defect fix;
* winstl/error/error_desc.hpp:;
* trivial correction;
* winstl/filesystem/directory_functions.hpp:;
* propagates failed sub-directory removal up to caller;
* fixing up of documentation of callback function semantics;
* winstl/system/console_functions.h:;
* fixing doc;
* winstl/system/environment_variable.hpp:;
* trivial tightening of pointer null;


## 1.9.116 - 19th August 2012

* fixed defect in winstl::pipe::close_write();
* various other minor warning suppression and reformatting;
* stlsoft/util/sign_traits.hpp:;
* VC++ 6 compatibility (with short);
* unixstl/filesystem/readdir_sequence.hpp:;
* semantically-meaningless reformatting (to ease diffs with STLSoft 1.10 version);
* winstl/filesystem/pipe.hpp:;
* fixed defective close_write();
* winstl/time/format_functions.hpp:;
* avoid truncation warning;


## 1.9.115 - 31st July 2012

* stlsoft::integer_to_string() new overloads with out-parameter as pointer; deprecated overloads with out-parameter as reference;
* winstl::integral_printf_traits added octal_format_a/w(), hexadecimal_format_a/w(), decimal_format_a/w(); deprecated format_a/w() and hex_format_a/w() methods, and size_min, size_max, and size member constants;
* Windows 7-compatibility for winstl::drophandle_sequence;
* winstl::spin_mutex now uses SwitchToThread if _WIN32_WINNT >= 0x0400;
* added winstl::added GetTimeFormat_msExA/W() by which custom time markers can be specified;
* stlsoft/conversion/integer_to_string.hpp:;
* added overloads taking pointer out-parameter (for retrieval of written length);
* deprecated overloads taking reference out-parameter (for retrieval of written length);
* preparation for fwd-compatible changes;
* stlsoft/internal/cccap/msvc.h:;
* support for static_assert (VC++ 10+);
* added STLSOFT_MSVC_VER;
* recognition of 'long long' support for VC++8+;
* stlsoft/internal/head_version.h:;
* stlsoft/internal/lead_version.h:;
* added head and lead version for STLSoft 1.9;
* stlsoft/stlsoft.h:;
* added remove_const_ptr();
* added apply_const_ptr();
* added inclusions for stlsoft/internal/head_version.h, which defines STLSOFT_HEAD_VER;
* added inclusions for stlsoft/internal/lead_version.h, which defines STLSOFT_LEAD_VER;
* now uses static_assert (in STLSOFT_STATIC_ASSERT()), when supported;
* stlsoft/string/split_functions.hpp:;
* moved worker functions into nested namespace stlsoft::ximpl_split_functions;
* stlsoft/string/view_slice_functions.hpp:;
* GCC compatibility (because of duff shims/template handling);
* stlsoft/util/integral_printf_traits.hpp:;
* size_min, size_max, and size member constants are now deprecated;
* moved integral_printf_traits_base into internal namespace ximpl_integral_printf_traits;
* added octal_format_a();
* added octal_format_w();
* added hexadecimal_format_a();
* added hexadecimal_format_w();
* deprecated hex_format_a();
* deprecated hex_format_w();
* added decimal_format_a();
* added decimal_format_w();
* deprecated format_a();
* deprecated format_w();
* winstl/conversion/char_conversions.hpp:;
* workaround for compatibility with ATL::CComBSTR (and other types that do not precisely convert to C const*);
* winstl/shell/drophandle_sequence.hpp:;
* changed to be compatible (and work!) with Windows 7(+);
* corrected formerly impotent contract enforcement;
* winstl/synch/spin_mutex.hpp:;
* now yields via SwitchToThread() if _WIN32_WINNT >= 0x0400;
* winstl/time/format_functions.hpp:;
* added GetTimeFormat_msExA/W() by which custom time markers can be specified;
* forward compatibility with STLSoft 1.10+ integer to string conversions;


## 1.9.114 - 4th June 2012

* added unixstl::filesystem_traits::is_socket(char_type const*) method;
* added unixstl::filesystem_traits::is_link(char_type const*) method;
* added unixstl::filesystem_traits::is_socket(stat_data_type const*) method;
* added unixstl::filesystem_traits::find_next_path_name_separator() method;
* added unixstl::filesystem_traits::find_last_path_name_separator() method;
* unixstl::filesystem_traits::get_full_path_name() now canonicalises '.'/'..'-trailing paths;
* unixstl::readdir_sequence.hpp now includes directory name in thrown exception;
* unixstl/filesystem/filesystem_traits.hpp:;
* canonicalised '.' and '..'-trailing paths;
* refactored get_full_path defect() logic;
* fixed defect whereby too much of a source string was being copied over into buffer (leading to a seg-fault on UNIX);
* added is_socket(char_type const*);
* added is_link(char_type const*);
* added is_socket(stat_data_type const*);
* added find_next_path_name_separator();
* added find_last_path_name_separator();
* unixstl/filesystem/glob_sequence.hpp:;
* refactored way in which patterns and directories are pre-parsed;
* unixstl/filesystem/readdir_sequence.hpp:;
* readdir_sequence_exception now has a Directory property;
* now includes directory name in thrown exception;
* minor compatibility fixes;


## 1.9.113 - 4th June 2012

* Intel C/C++ 12 support;
* support for STLSOFT_COMPILE_VERBOSE; deprecation of _STLSOFT_COMPILE_VERBOSE;
* fixed unixstl::filesystem_traits::broken get_current_directory();
* fixed unixstl::filesystem_traits::broken invalid_file_handle_value();
* fixed unixstl::filesystem_traits::is_file() / is_directory() / is_link();
* numerous improvements to unixstl::filesystem_traits::glob_sequence;
* unixstl::readdir_sequence correction to elide sockets from search results;
* winstl/time/conversion_functions.h renaming (and deprecation) of non-standard C function names;
* stlsoft/internal/cccap/gcc.h:;
* added STLSOFT_GCC_VER;
* stlsoft/shims/access/string/std/exception.hpp:;
* strengthened contract of implementation function;
* stlsoft/stlsoft.h:;
* reworking of use of STLSOFT_COMPILE_VERBOSE; deprecation of _STLSOFT_COMPILE_VERBOSE;
* stlsoft/string/special_string_instance.hpp:;
* trivial change;
* stlsoft/util/std/library_discriminator.hpp:;
* unixstl/filesystem/filesystem_traits.hpp:;
* fixed broken get_current_directory();
* corrected return value of invalid_file_handle_value() : now returns -1, rather than 0;
* corrected inappropriate flag testing to identify files/directories/links;
* unixstl/filesystem/glob_sequence.hpp:;
* correct elision (or not) of dots directories, based on whether pattern contains wildcards and on whether matchPeriod is specified;
* fixed defect;
* simplified implementation, and now elides non-directory, non-file types (e.g. sockets);
* no longer specifies noSort by default;
* removed some dead code;
* clarified user-definable feature selection instructions;
* correct handling of UNIXSTL_GLOB_SEQUENCE_DONT_TRUST_MARK;
* changed internal API;
* corrected rarely encountered defect in eliding dots directories;
* fixed erroneous 1-param ctor;
* minor refactoring;
* unixstl/filesystem/readdir_sequence.hpp:;
* forward compatibility;
* correction for presence of sockets (non-Windows only);
* winstl/registry/reg_key.hpp:;
* const-correctness on REG_MULTI_SZ values;
* winstl/time/conversion_functions.h:;
* conversion of deprecated winstl__??? form to winstl_C_??? form;
* trivial formatting changes;
* added documentation markup;
* winstl/winstl.h:;
* Intel C/C++ 12 compatibility;


## 1.9.112 - 7th February 2012

* added winstl_C_format_message_strerror_a(), an analogue of strerror() for Windows API "error" codes;
* adjusted discrimination of exception-support macros, based on presence of GCC compiler's __EXCEPTIONS symbol;
* minor VC++ compatibility fix for stlsoft/shims/access/string/std/exception.hpp;
* stlsoft/internal/cccap/gcc.h:;
* stlsoft/shims/access/string/std/exception.hpp:;
* VC++-compatibility;
* winstl/error/error_functions.h:;


## 1.9.111 - 30th November 2011

* fix for GCC 4.5+ unixstl::filesystem_traits;
* unixstl/filesystem/filesystem_traits.hpp:;
* filesystem_traits::create_directory() 1-parameter overload now passes mode to 2-parameter overload;


## 1.9.110 - 25th November 2011

* fix for GCC 4.5+ unixstl::filesystem_traits;
* added result_code_type to both unixstl::system_traits and winstl::system_traits;
* correction(s)/enhancement(s) to which of MFCSTL's string access shim headers are automatically included;
* added discrimination of new pre-processor symbol PLATFORMSTL_NO_PLATFORM_NAMESPACE, to ease dependent library implementation;
* avoidance of false memory-leak reports in use of stlsoft::truncation_test;
* stlsoft/conversion/truncation_test.hpp:;
* workaround to avoid false memory-leak reports in certain circumstances (seen when using platformstl::file_lines);
* mfcstl/shims/access/string.hpp:;
* added inclusion for #include <mfcstl/shims/access/string/CException.hpp>;
* corrected inclusions to #include <mfcstl/shims/access/string/cwnd.hpp>;
* mfcstl/shims/access/string/cwnd.hpp:;
* corrected defects in definitions of CWnd-related overloads of c_str_len() shims;
* platformstl/platformstl.h:;
* added discrimination of PLATFORMSTL_NO_PLATFORM_NAMESPACE;
* unixstl/filesystem/filesystem_traits.hpp:;
* fix for GCC 4.5+ issue (returning NULL for file-handle type (int));
* unixstl/system/system_traits.hpp:;
* added result_code_type (as we're trying to remove the presence of the misleading word "error" as much as possible);
* winstl/system/system_traits.hpp:;


## 1.9.109 - 13th August 2011

* added rbegin()/rend() to stlsoft::frequency_map<>;
* added push_n() to stlsoft::frequency_map<>;
* refactored throw statement(s) in terms of STLSOFT_THROW_X() throughout;
* added reset() method to stlsoft::shared_ptr<>;
* added various STLSoft deprecation macros;
* added is_path_rooted(), is_path_absolute(), and is_path_UNC() methods to unixstl::filesystem_traits<>;
* added two-parameters overloads of is_path_rooted(), is_path_absolute(), and is_path_UNC() methods to winstl::filesystem_traits<>;
* include/winstl/error/error_functions.h: substantial refactoring of format_message()-family of functions (and their C analogues);
* include/stlsoft/containers/frequency_map.hpp:;
* added push_n() (rudimentary implementation);
* trivial changes;
* added rbegin()/rend();
* include/stlsoft/conversion/truncation_cast.hpp:;
* include/stlsoft/error/throw_policies.hpp:;
* refactored throw statement(s) in terms of STLSOFT_THROW_X();
* include/stlsoft/functional/composite_predicates.hpp:;
* trivial formatting changes;
* documentation changes;
* include/stlsoft/smartptr/shared_ptr.hpp:;
* added reset() method;
* include/stlsoft/stlsoft.h:;
* added STLSOFT_DECLARE_DEPRECATION();
* added STLSOFT_DECLARE_DEPRECATION_MESSAGE();
* added STLSOFT_DECLARE_FUNCTION_DEPRECATION();
* added STLSOFT_DECLARE_FUNCTION_DEPRECATION_IN_FAVOUR_OF();
* added STLSOFT_DECLARE_MACRO_DEPRECATION();
* added STLSOFT_DECLARE_MACRO_DEPRECATION_IN_FAVOUR_OF();
* include/stlsoft/string/string_view.hpp:;
* include/comstl/collections/enumeration_policies.hpp:;
* include/comstl/error/bad_interface_cast.hpp:;
* include/comstl/string/bstr.hpp:;
* include/comstl/util/value_policies.hpp:;
* include/comstl/util/variant.hpp:;
* include/rangelib/algorithms.hpp:;
* include/rangelib/integral_range.hpp:;
* include/unixstl/filesystem/directory_functions.hpp:;
* "safe string" compatibility;
* include/unixstl/filesystem/filesystem_traits.hpp:;
* added is_path_rooted() method;
* added is_path_absolute() method;
* added is_path_UNC() method;
* widestring uses iswalpha();
* simplification/separation of Windows-emulation code;
* corrected maximum-path length calculation(s);
* include/unixstl/system/system_traits.hpp:;
* added implementations of str_n_compare_no_case() when emulating UNIX on Windows;
* include/winstl/error/error_desc.hpp:;
* reimplemented to new overload of format_message(), specifying flags to more precisely control behaviour;
* use of FORMAT_MESSAGE_IGNORE_INSERTS to resolve strings with inserts;
* application of new STLSoft deprecation features;
* include/winstl/error/error_functions.h:;
* renamed winstl_C_fmtmsg_find_last_good_a/w__ to winstl_C_fmtmsg_elide_message_a/w_;
* added winstl_C_format_message_from_module_to_allocated_buffer_a();
* added winstl_C_format_message_from_module_to_allocated_buffer();
* added new overload of format_message();
* applying new deprecation macros;
* conditional elision of period;
* deprecated functions;
* reimplementing in terms of new functions;
* added winstl_C_FormatMessageA_INVOKE_for_alloc_();
* added winstl_C_FormatMessageW_INVOKE_for_alloc_();
* winstl_C_FormatMessageA_INVOKE_in_buffer_();
* winstl_C_FormatMessageW_INVOKE_in_buffer_();
* include/winstl/error/exceptions.hpp:;
* uses new format_message() function(s);
* include/winstl/filesystem/directory_functions.hpp:;
* include/winstl/filesystem/file_path_buffer.hpp:;
* trivial change;
* include/winstl/filesystem/filesystem_traits.hpp:;
* added two-parameter overload of is_path_absolute();
* added two-parameter overload of is_path_rooted();
* added two-parameter overload of is_path_UNC();
* refactored internal implementation methods;
* include/winstl/filesystem/memory_mapped_file.hpp:;
* VC++ 9 compatibility;
* corrected behaviour (and updated class invariant) for non-exception compilation;
* now initialises m_lastStatusCode, so can be used in invariant;
* removed all possible uses of word 'error' and replaced with 'status code';
* include/winstl/shims/access/string/time.hpp:;
* avoiding warnings (due to compiler not being able to see that STLSOFT_THROW_X() actually throws an exception, so the subsequent return is fatuous);
* include/winstl/system/system_traits.hpp:;
* pedantic change from HINSTANCE to HMODULE;
* include/winstl/winstl.h:;
* now issues #error if compiling with WIN64 defined absent definition of _WIN64;


## 1.9.108 - 31st January 2011

* changed erroneously named new unixstl::/winstl::filesystem_traits method's name from invalid_handle_value() to invalid_file_handle_value();
* added third, defaulted, template parameter to stlsoft::frequency_map for specification of predicate;
* include/stlsoft/containers/frequency_map.hpp:;
* added third, defaulted, template parameter, allowing specification of predicate;
* include/unixstl/filesystem/filesystem_traits.hpp:;
* changed erroneously named new method's name from invalid_handle_value() to invalid_file_handle_value();
* include/winstl/filesystem/filesystem_traits.hpp:;


## 1.9.107 - 30th January 2011

* added data() member to stlsoft::multibyte2wide and stlsoft::wide2multibyte;
* added data() member to winstl::multibyte2wide and winstl::wide2multibyte;
* improved performance of of c_str_len(_a|_w)() shim overloads of stlsoft::multibyte2wide and stlsoft::wide2multibyte;
* improved performance of of c_str_len(_a|_w)() shim overloads of winstl::multibyte2wide and winstl::wide2multibyte;
* added equal() method and operator ==/!=() non-member functions to unixstl::memory_mapped_file;
* added equal() method and operator ==/!=() non-member functions to winstl::memory_mapped_file;
* added non-member unixstl::swap() function for unixstl::memory_mapped_file;
* added non-member platformstl::swap() function for platformstl::memory_mapped_file;
* changed definition of unixstl::memory_mapped_file::size_type to be size_t;
* added invalid_handle_value() method to unixstl::filesystem_traits<>;
* added invalid_handle_value() method to winstl::filesystem_traits<>;
* added added get_file_size(stat_data_type const&) and get_file_size(stat_data_type const*) overloads to unixstl::filesystem_traits<>;
* added added get_file_size(stat_data_type const&) and get_file_size(stat_data_type const*) overloads to winstl::filesystem_traits<>;
* reduced dependencies on other string access shim overloads in winstl::error_desc;
* stlsoft/collections/associative_mapped_type_detector.hpp:;
* stlsoft/collections/collections.hpp:;
* stlsoft/containers/array_policies.hpp:;
* stlsoft/string/char_traits.hpp:;
* stlsoft/util/std/algorithm.hpp:;
* stlsoft/exceptions/active_end_iterator_exhaustion.hpp:;
* stlsoft/exceptions/contract_violation.hpp:;
* stlsoft/exceptions/external_iterator_invalidation.hpp:;
* stlsoft/exceptions/iteration_interruption.hpp:;
* stlsoft/exceptions/unrecoverable.hpp:;
* stlsoft/function_adaptors/ref2ptr.hpp:;
* stlsoft/functional/access_predicates.hpp:;
* trivial formatting changes;
* stlsoft/conversion/char_conversions.hpp:;
* added data() member;
* added size() member, which returns length of contents, not length of buffer (was off by 1);
* improved performance of c_str_len(_a|_w)() shim overloads;
* stlsoft/iterators/c_str_inserter.hpp:;
* documentation improvement;
* comstl/interface/bad_interface_cast.hpp:;
* comstl/interface/interface_cast.hpp:;
* comstl/interface/interface_traits.hpp:;
* unixstl/filesystem/filesystem_traits.hpp:;
* added invalid_handle_value() method;
* added get_file_size(stat_data_type const&) and get_file_size(stat_data_type const*) overloads;
* unixstl/filesystem/memory_mapped_file.hpp:;
* adds equal() method;
* adds operator ==() non-member function;
* adds operator !=() non-member function;
* adds swap() non-member function (in unixstl namespace);
* size_type is not defined to be size_t, which affects only the case of a 32-bit architecture on which the compiler supports 64-bit integers; the effect is to move runtime failures to compile-time (since it's not possible to map a range of memory whose size exceeds 32-bits on a 32-bit system);
* unixstl/synch/exceptions.hpp:;
* winstl/clipboard/exceptions.hpp:;
* winstl/control_panel/exceptions.hpp:;
* winstl/registry/defs.hpp:;
* winstl/registry/exceptions.hpp:;
* winstl/registry/shared_handles.hpp:;
* winstl/shell/memory_functions.h:;
* winstl/synch/exceptions.hpp:;
* winstl/synch/functions.hpp:;
* winstl/time/format_functions.h:;
* winstl/toolhelp/exceptions.hpp:;
* winstl/toolhelp/sequence_value_traits.hpp:;
* winstl/conversion/char_conversions.hpp:;
* winstl/error/error_desc.hpp:;
* reduced the amount of dependencies on other string access shim overloads;
* winstl/filesystem/filesystem_traits.hpp:;
* winstl/filesystem/memory_mapped_file.hpp:;
* added equal() method, and operator ==/!= non-member operators;
* added swap() in winstl namespace;


## 1.9.106 - 28th December 2010

* workaround for Intel compile error;
* include/winstl/error/exceptions.hpp:;


## 1.9.105 - 27th December 2010

* several new minor facilities in stlsoft::frequency_map;
* improved compiler-compatibility in stlsoft::multibyte2wide and stlsoft::wide2multibyte;
* WinSTL now recognises Win64 architecture when _WIN64 is defined even when WIN64 is not;
* stlsoft/containers/frequency_map.hpp:;
* added member function operator +=();
* added non-member function operator +();
* added total() method;
* added class invariant and enforcements;
* stlsoft/conversion/char_conversions.hpp:;
* GCC compatibility;
* stlsoft/shims/access/string/std/exception.hpp:;
* suppressed trivial unused warning;
* unixstl/filesystem/path.hpp:;
* minor refactoring, to avoid use of str_n_copy() and str_cat();
* unixstl/filesystem/readdir_sequence.hpp:;
* refactored to remove use of str_n_copy();
* winstl/filesystem/path.hpp:;
* trivial refactoring;
* winstl/window/functions.h:;
* VC++/-Wp64 warning suppression;
* winstl/winstl.h:;
* now recognises _WIN64 (without WIN64) when defining architecture as WINSTL_OS_IS_WIN64, and emits a pragma message nag (for supporting compilers);


## 1.9.104 - 22nd November 2010

* refactored wide string exception string access shim functions, to avoid so-called "deprecated" (standard) functions when using VC++;
* expanded internal buffers of shim strings for exception string access shims, from 10 to 100;
* include/stlsoft/shims/access/string/std/exception.hpp:;
* refactored wide-string string access shim functions, to avoid so-called "deprecated" (standard) functions when using VC++;


## 1.9.103 - 21st November 2010

* changed mechanism of discriminating Dinkumware standard library versions;
* added typedefs for path_a and path_w to introduce them into the platformstl namespace;
* include/platformstl/filesystem/path.hpp:;
* include/stlsoft/util/std/library_discriminator.hpp:;
* changed mechanism of discriminating Dinkumware standard library versions: for versions with VC++ 7.0+ the library pre-processor symbol _CPPLIB_VER is the trusted authority;


## 1.9.102 - 8th November 2010

* added wide string string access shims for std::exception;
* fixed infinite-recursion defects in ambient shim function definitions;
* other compatibility fixes;
* include/stlsoft/shims/access/string/std/exception.hpp:;
* include/stlsoft/util/std/library_discriminator.hpp:;
* fixed VC9 (in)compatibility (which occurred only when including <functional> *before* STLSoft header files);
* include/winstl/error/error_functions.h:;
* fixed incorrectly specified obsolete symbols;


## 1.9.101 - 30th September 2010

* stlsoft::transform_iterator can now support transformation to types that do not support default construction;
* fixed defect in stlsoft::transform_iterator;
* platformstl::basic_file_lines refactored, and exception-safety enhanced;
* winstl::memory_mapped_file refactored in preparation for substantial enhancement in 1.10; also no longer supports compilers that do not have native 64-bit integers;
* stlsoft/iterators/transform_iterator.hpp:;
* can now support transformation to types that do not support default construction;
* fixed nasty as anything defect in decrement operator;
* stlsoft/string/cstring_functions.hpp:;
* string_dup now responds robustly when out of memory used with a compiler that doesn't throw bad_alloc;
* stlsoft/string/simple_string.hpp:;
* string_traits<> specialisation for basic_simple_string now works with any basic_simple_string<C, T, A> specialisation permutation, rather than just basic_simple_string<C>;
* fix to defect in assign(cc*, size_t);
* platformstl/filesystem/file_lines.hpp:;
* trivial changes, ready for 1.10 changes;
* simplified refactoring, readying for 1.10;
* exception-safety correction;
* getting ready for major refactoring in 1.10;
* winstl/error/error_functions.h:;
* added character-encoding independent symbols;
* conversion of deprecated winstl__??? form to winstl_C_??? form;
* winstl/filesystem/memory_mapped_file.hpp:;
* no longer supports compilers that do not have native 64-bit integers;
* final refactoring, ready for splitting in STLSoft 1.10;
* now allows for offset+requestSize for both 32-bit and 64-bit operation;
* benign change of casting syntax, in order to support forthcoming separation into (C) source files in STLSoft 1.10;
* winstl/system/console_functions.h:;
* benign changes to winstl_C_get_console_width() to aid debugging;
* winstl/winstl.h:;
* added INVALID_SET_FILE_POINTER;


## 1.9.100 - 12th August 2010

* added stlsoft/iterators/common/string_concatenation_flags.hpp;
* string_concatenator_iterator now strictly skips separator insertion for empty elements if no flags are specified, and always inserts separator if string_concatenation_flags::AlwaysSeparate is specified;
* added performance_counter_init::get_period_and_restart() method;
* added STLSOFT_CC_CDECL_VALUE, STLSOFT_CC_FASTCALL_VALUE, STLSOFT_CC_STDCALL_VALUE;
* special_string_instance now uses atomic_int_type;
* string_tokeniser iterator dereference operator changed to disallow return of mutable instance;
* string_view has improved comparison algorithm;
* added 3-, 4-, and 5-parameter overloads of stlsoft::minimum() and stlsoft::maximum();
* various fixes and enhancements to platformstl::file_lines;
* added size() and empty() methods to winstl::environment_variable;
* implemented winstl::system_traits::str_n_compare_no_case();
* stlsoft/algorithms/pod.hpp:;
* refactored, to remove inappropriate constraints;
* stlsoft/iterators/common/string_concatenation_flags.hpp:;
* stlsoft/iterators/string_concatenator_iterator.hpp:;
* now strictly skips separator insertion for empty elements if no flags are specified, and always inserts separator if string_concatenation_flags::AlwaysSeparate is specified;
* stlsoft/performance/performance_counter_init.hpp:;
* added get_period_and_restart() method;
* stlsoft/stlsoft.h:;
* added STLSOFT_CC_CDECL_VALUE;
* added STLSOFT_CC_FASTCALL_VALUE;
* added STLSOFT_CC_STDCALL_VALUE;
* stlsoft/string/special_string_instance.hpp:;
* minor change to avoid possible undefined-behaviour;
* stlsoft/string/string_tokeniser.hpp:;
* iterator dereference operator changed to disallow return of mutable instance;
* stlsoft/string/string_view.hpp:;
* improved comparison algorithm;
* performance improvement in equal(class_type const&) method;
* stlsoft/util/constraints.hpp:;
* compiler compatibility;
* compatibility;
* workaround for pedantic warnings;
* stlsoft/util/minmax.hpp:;
* 3-, 4-, and 5-parameter overloads;
* comstl/util/rot_functions.h:;
* trivial commenting changes;
* platformstl/filesystem/file_lines.hpp:;
* 64-bit compatibility;
* corrects the determination of whether to discard the mapping to work on the first non-empty string, since it will fault if the first line in a mapped file is empty but any others are not;
* conversion constructor is now explicit;
* added private declaration of constructor template to prevents the conversion constructor from being invoked on an instance of a different specialisation;
* allows wider range of string types to be used, in particular those that are copy-constructible but do not provide assign() methods;
* unixstl/dl/module.hpp:;
* includes STLSoft's main shims header, to at least allow GCC to see std::string arguments without hassle;
* added typedefs to make compatible with get_module_handle() shim (not yet complete for UNIXSTL);
* surrounding template methods with #ifdefs;
* throw() for unload() method(s);
* unixstl/filesystem/filesystem_traits.hpp:;
* GCC (on Windows) compatibility;
* added missing member constant pathComparisonIsCaseSensitive to specialisations;
* unixstl/filesystem/path.hpp:;
* ensures push_ext() is wide-string compatible;
* winstl/dl/module.hpp:;
* documentation markup;
* winstl/filesystem/absolute_path.hpp:;
* winstl/filesystem/current_directory.hpp:;
* winstl/system/module_directory.hpp:;
* winstl/system/module_filename.hpp:;
* winstl/filesystem/filesystem_traits.hpp:;
* winstl/filesystem/path.hpp:;
* winstl/system/console_functions.h:;
* winstl__get_console_width() => winstl_C_get_console_width();
* winstl__get_console_window() => winstl_C_get_console_window();
* minor improvements to use of casts;
* winstl/system/environment_variable.hpp:;
* added size() method;
* added empty() method;
* winstl/system/searchpath_sequence.hpp:;
* winstl/system/system_directory.hpp:;
* added atomic_int_type;
* winstl/system/system_traits.hpp:;
* implementation(s) of str_n_compare_no_case();
* winstl/system/windows_directory.hpp:;
* winstl/winstl.h:;
* added ws_intptr_t;
* added ws_sintptr_t;
* added ws_uintptr_t;


## 1.9.99 - 21st June 2010

* added filesystem_traits::str_fs_compare() (UNIXSTL & WinSTL);
* added filesystem_traits::str_fs_n_compare() (UNIXSTL & WinSTL);
* added str_n_compare_no_case declaration to system_traits (UNIXSTL & WinSTL);
* added assoc_select_first() and assoc_select_second() creator functions for associative_select_iterator;
* incorporated Manfred Ehrhart's fixes for associative_select_iterator;
* Borland/GCC-compatibility fixes;
* GCC-compatibility fixes;
* nullptr support correction for VC++;
* various minor fixes;
* stlsoft/error/error_desc.hpp:;
* stlsoft/string/special_string_instance.hpp:;
* stlsoft/filesystem/read_line.hpp:;
* required disambiguation, via separating readers from implementation;
* stlsoft/internal/cccap/msvc.h:;
* stlsoft/iterators/associative_select_iterator.hpp:;
* added assoc_select_first() function;
* added assoc_select_second() function;
* removed the need to be explicit, to allow for assignment-syntax initialisation;
* incorporate (after inexcusable delay) Manfred Ehrhart's fixes, addressing inappropriate member type and defect in select_second();
* unixstl/filesystem/directory_functions.hpp:;
* improved documentation for remove_directory_recurse();
* unixstl/filesystem/filesystem_traits.hpp:;
* added filesystem_traits::str_fs_compare();
* added filesystem_traits::str_fs_n_compare();
* unixstl/system/system_traits.hpp:;
* added str_n_compare_no_case declaration to system_traits;
* winstl/conversion/char_conversions.hpp:;
* winstl/filesystem/directory_functions.hpp:;
* winstl/filesystem/filesystem_traits.hpp:;
* winstl/filesystem/findvolume_sequence.hpp:;
* adds missing inclusion of shims header file(s);
* winstl/system/system_traits.hpp:;
* documentation markup;


## 1.9.98 - 7th June 2010

* added range overload of stlsoft::read_line(), so can read lines from an iterator range;
* added nullptr (C++0x) support for VC++ 10;
* added swap() method to stlsoft::basic_shim_string;
* added 3, 4, 5, and 6-split overloads to stlsoft::split();
* added sized-string ctor, data() and size() methods, and string access shims (to simplify xTests-based unit-testing, if nothing else) to stlsoft::exception_string;
* added VARIANT_BOOL overload to comstl::method_cast();
* added platformstl::file_lines empty() method;
* separated PlatformSTL's atomic types into separate file platformstl/synch/atomic_types.h;
* separated UNIXSTL's atomic types into separate file unixstl/synch/atomic_types.h;
* separated WinSTL's atomic types into separate file winstl/synch/atomic_types.h;
* fixed winstl::memory_mapped_file to handle case where an offset is specified but there are 0 remaining bytes in the file to be mapped at that location: constructs an instance with 0 size;
* fixed potential memory leak of format-message-string if windows_exception creation throws an exception;
* moved COMSTL_CCH_GUID to comstl/comstl.h from comstl/shims/access/string/guid.hpp;
* adjusted winstl::drophandle_sequence for Win64 compatibility;
* adjusted winstl::version_info for Win64 compatibility;
* various components no longer rely on operator += of exception_string type, in preparation for 1.10 versions;
* stlsoft/containers/frequency_map.hpp:;
* documentation markup;
* stlsoft/error/error_desc.hpp:;
* forwards and backwards compatibility with basic_shim_string;
* stlsoft/filesystem/read_line.hpp:;
* added range overload of read_line();
* stlsoft/internal/cccap/msvc.h:;
* stlsoft/smartptr/ref_ptr.hpp:;
* formatting;
* stlsoft/string/shim_string.hpp:;
* stlsoft/string/shim_string_vc5_.hpp:;
* added swap() method;
* stlsoft/string/split_functions.hpp:;
* added 5 and 6 split overloads;
* added 3 and 4 split overloads;
* stlsoft/util/exception_string.hpp:;
* removed all mutating methods and several constructors, to simplify exception_string: all dependent code should now use exception_string_creator;
* added sized-string constructor;
* string access shims (useful for unit-testing, if nothing else);
* added data();
* now all member and non-member functions are defined in terms of char_type;
* added size() method;
* stlsoft/util/forward_enums.hpp:;
* changed all double underscores;
* comstl/comstl.h:;
* added COMSTL_PTR_2_REF();
* comstl/conversion/interface_cast.hpp:;
* comstl/conversion/method_cast.hpp:;
* added VARIANT_BOOL overload;
* comstl/error/excepinfo_functions.h:;
* comstl/shims/access/string/variant.hpp:;
* comstl/util/variant.hpp:;
* bstr_functions.h -> BSTR_functions.h;
* comstl/shims/access/string/guid.hpp:;
* comstl/string/bstr.hpp:;
* comstl/util/guid.hpp:;
* adds missing include (to stlsoft/util/std_swap.hpp);
* platformstl/filesystem/file_lines.hpp:;
* added empty() method;
* platformstl/synch/atomic_functions.h:;
* corrected include guard symbols;
* platformstl/synch/atomic_types.h:;
* unixstl/error/exceptions.hpp:;
* no longer relies on operator += of exception_string type, in preparation for 1.10 versions;
* unixstl/synch/atomic_functions.h:;
* unixstl/synch/atomic_types.h:;
* winstl/dl/dl_call.hpp:;
* winstl/error/exceptions.hpp:;
* preparation for STLSoft 1.10;
* whitespace;
* fixed potential memory leak if exception-creation throws an exception;
* winstl/filesystem/memory_mapped_file.hpp:;
* now handles case where an offset is specified but there are 0 remaining bytes in the file to be mapped at that location: constructs an instance with 0 size;
* winstl/performance/threadtimes_counter.hpp:;
* winstl/system/system_version.hpp:;
* winstl/shell/drophandle_sequence.hpp:;
* winstl/system/version_info.hpp:;
* Win64 compatibility;
* winstl/synch/atomic_functions.h:;
* winstl/synch/atomic_types.h:;
* winstl/synch/spin_mutex.hpp:;
* atomic_int_type is now winstl::atomic_int_t, rather than ws_sint32_t;


## 1.9.97 - 4th April 2010

* added stlsoft::copy_preinc() and stlsoft::copy_postinc() algorithms;
* added str_set() method to unixstl::/winstl::system_traits;
* added unixstl/shims/conversion/to_uint64/stat.hpp;
* added missing widestring specialisation of inetstl::filesystem_traits::is_path_name_separator();
* stlsoft::basic_error_desc synthesises widestring functionality if wcserror() is not available;
* exposes widestring version of platformstl::system_traits from UNIXSTL;
* comstl::variant compatibility with exception-support disabled;
* removed erroneous definitions of strtol(), strtoul(), strtod();
* added missing 'mode' parameter to unixstl::module::load(), and uses 'mode' parameter passed to constructor template;
* typename corrections to platformstl::basic_file_path_buffer and platformstl::basic_path;
* improved discrimination of Visual C++ 9 / 10;
* fixed defective arithmetic in unixstl::/winstl::memory_mapped_file;
* refactored implementation of winstl::reg_key::create_key() to avoid infinite loop faults;
* stlsoft/algorithms/debug.hpp:;
* copy_preinc();
* copy_postinc();
* stlsoft/error/error_desc.hpp:;
* synthesises widestring functionality - in terms of strerror() - if not available as wcserror (or "safe string" equivalent);
* stlsoft/std/cstdlib.hpp:;
* removed erroneous definitions of strtol(), strtoul(), strtod(): they used string access shims to elicit the string form of their arguments, and returned a pointer into the parsed string (which may no longer exist by the time the function returns);
* added strtol(char const*, ...) and strtol(wchar_t const*, ...);
* added strtoul(char const*, ...) and strtoul(wchar_t const*, ...);
* added strtod(char const*, ...) and strtod(wchar_t const*, ...);
* stlsoft/util/std/library_discriminator.hpp:;
* better discrimination of VC++ 9 & 10;
* comstl/collections/enumerator_sequence.hpp:;
* minor warning workaround;
* comstl/util/variant.hpp:;
* compatibility with exception-support disabled;
* inetstl/filesystem/filesystem_traits.hpp:;
* added missing is_path_name_separator for wide specialisation;
* platformstl/filesystem/file_path_buffer.hpp:;
* platformstl/filesystem/path.hpp:;
* correct use of typename to indicate dependent types in default template arguments;
* platformstl/system/system_traits.hpp:;
* exposes wide version from UNIXSTL;
* unixstl/dl/module.hpp:;
* added missing 'mode' parameter to load();
* used 'mode' parameter passed to constructor template;
* unixstl/filesystem/memory_mapped_file.hpp:;
* fixed defective arithmetic when validating non-0 request size;
* unixstl/filesystem/path_functions.hpp:;
* refactored implementation;
* unixstl/shims/conversion/to_uint64/stat.hpp:;
* unixstl/synch/atomic_functions.h:;
* unixstl/synch/util/features.h:;
* preparation for future refinement;
* unixstl/system/system_traits.hpp:;
* str_set() method;
* other widestring compatibility changes;
* winstl/filesystem/memory_mapped_file.hpp:;
* winstl/filesystem/path_functions.hpp:;
* minor restructuring;
* winstl/registry/reg_key.hpp:;
* refactored implementation of create_key() to avoid infinite loop fault in case of passing string types of non-matching character encodings;
* winstl/system/system_traits.hpp:;


## 1.9.96 - 10th March 2010

* Visual C++ 10 compatibility;
* include/stlsoft/internal/cccap/msvc.h:;
* VC++ 10 compatibility;
* include/stlsoft/stlsoft.h:;
* Visual C++ 10 support;
* include/stlsoft/util/std/iterator_helper.hpp:;
* added support for Dinkumware 10 (as well as making explicit support for Dinkumware 8 & 9);
* include/stlsoft/util/std/library_discriminator.hpp:;
* refactored Dinkumware detection, to discriminate 8, 9 and 10;


## 1.9.95 - 7th March 2010

* minor interface modifications to comstl::com_exception;
* include/comstl/error/exceptions.hpp:;
* added get_hr();
* deprecated hr();


## 1.9.94 - 5th March 2010

* corrected omission of inline from swap for unixstl::memory_mapped_file;
* corrected omission of inline from swap for winstl::memory_mapped_file;
* include/unixstl/filesystem/memory_mapped_file.hpp:;
* include/winstl/filesystem/memory_mapped_file.hpp:;


## 1.9.93 - 15th February 2010

* STLSOFT_CF_NAMESPACE_SUPPORT is now only defined in C++ compilation units;
* added WINSTL_CONST_MAX_PATH, which is now used instead of _MAX_PATH throughout winstl;
* include/stlsoft/internal/cccap/borland.h:;
* include/stlsoft/internal/cccap/como.h:;
* include/stlsoft/internal/cccap/dmc.h:;
* include/stlsoft/internal/cccap/gcc.h:;
* include/stlsoft/internal/cccap/intel.h:;
* include/stlsoft/internal/cccap/msvc.h:;
* include/stlsoft/internal/cccap/mwerks.h:;
* include/stlsoft/internal/cccap/unknown.h:;
* include/stlsoft/internal/cccap/vectorc.h:;
* include/stlsoft/internal/cccap/watcom.h:;
* include/comstl/error/errorinfo_desc.hpp:;
* cast change;
* include/winstl/winstl.h:;
* added WINSTL_CONST_MAX_PATH;
* include/winstl/filesystem/file_path_buffer.hpp:;
* include/winstl/filesystem/filesystem_traits.hpp:;
* include/winstl/filesystem/findvolume_sequence.hpp:;
* include/winstl/filesystem/path.hpp:;
* include/winstl/shell/browse_for_folder.hpp:;
* include/winstl/shell/drophandle_sequence.hpp:;
* include/winstl/shell/file_operations.hpp:;
* include/winstl/system/searchpath_sequence.hpp:;
* include/winstl/system/system_traits.hpp:;
* include/winstl/system/version_info.hpp:;
* now uses WINSTL_CONST_MAX_PATH;


## 1.9.92 - 11th February 2010

* added inetstl::filesystem_traits<>::is_path_name_separator();
* inetstl/filesystem/filesystem_traits.hpp:;
* added is_path_name_separator();


## 1.9.91 - 2nd February 2010

* introducing unixstl::/winstl::remove_directory_recurse() into platformstl namespace;
* removal of dependency on so-called "unsafe" string functions;
* elimination of calls to memcpy() in path classes;
* throwing of exception in make_absolute() if failed to get full path;
* platformstl/filesystem/directory_functions.hpp:;
* unixstl/filesystem/path.hpp:;
* elimination of calls to memcpy();
* winstl/filesystem/directory_functions.hpp:;
* winstl/filesystem/path.hpp:;


## 1.9.90 - 21st January 2010

* fixed defect in unixstl::filesystem_traits<>::get_full_path_name() when passed ".";
* header ordering workaround for GCC 3.4's strange COM headers on Windows;
* include/unixstl/filesystem/filesystem_traits.hpp:;
* fixed defect in get_full_path_name() when passed ".";
* include/winstl/winstl.h:;
* header ordering, for GCC 3.4;


## 1.9.89 - 19th January 2010

* include/stlsoft/error/error_desc.hpp:;
* fixed defective stream inserter definition ACESTL:;
* include/acestl/reactor/custom_event_handler.hpp:;
* corrected warning suppression push-pop UNIXSTL:;
* include/unixstl/filesystem/filesystem_traits.hpp:;
* include/unixstl/filesystem/glob_sequence.hpp:;
* include/unixstl/filesystem/path_functions.hpp:;
* include/unixstl/filesystem/readdir_sequence.hpp:;
* include/unixstl/system/system_traits.hpp:;
* safe string compatibility;


## 1.9.88 - 12th January 2010

* stlsoft/internal/cccap/unknown.h:;
* changed to "modern" form of feature discrimination mechanisms;
* stlsoft/conversion/truncation_test.hpp:;
* truncation_test is now a function template (rather than a macro to an internal function);
* stlsoft/internal/cccap/msvc.h:;
* C compatibility fixes;
* stlsoft/util/std/iterator_helper.hpp:;
* compatibility between reverse_iterator and const_reverse_iterator COMSTL:;
* comstl/comstl.h:;
* comstl/error/errorinfo_functions.h:;
* compatibility with GCC 3.4;
* comstl/util/rot_functions.h:;
* conversion of deprecated comstl__??? form to comstl_C_??? form;
* comstl/util/variant.hpp:;
* added ctors for unsigned integral types;
* full handling of integers MFCSTL:;
* mfcstl/shims/access/string/cwnd.hpp:;
* removing use of reserved symbols UNIXSTL:;
* unixstl/filesystem/file_path_buffer.hpp:;
* added max_size() static method;
* unixstl/filesystem/path.hpp:;
* changed max_size() method to be static WinSTL:;
* winstl/controls/listview_sequence.hpp:;
* introduction of lvs_string_t from global namespace (where it should not be defined) to the winstl namespace (where it should be);
* winstl/error/exceptions.hpp:;
* added winstl::access_exception;
* winstl/filesystem/file_path_buffer.hpp:;
* winstl/filesystem/findfile_sequence.hpp:;
* added throwOnAccessFailure search flag, along with supporting code;
* winstl/filesystem/path.hpp:;
* changed max_size() method to be static;
* winstl/performance/threadtimes_counter.hpp:;
* refactored in preparation of throwing of exceptions when timing information cannot be elicited;
* winstl/shims/access/string/HWND.hpp:;
* removing use of reserved symbols;
* winstl/winstl.h:;
* added MAKEINTRESOURCEA;
* added MAKEINTRESOURCEW;


## 1.9.87 - 11th August 2009

* trivial formatting changes;


## 1.9.86 - 24th July 2009

* include/acestl/acestl.hpp:;
* include/atlstl/atlstl.hpp:;
* include/comstl/comstl.h:;
* include/dotnetstl/dotnetstl.hpp:;
* include/inetstl/inetstl.h:;
* include/mfcstl/mfcstl.hpp:;
* include/unixstl/unixstl.h:;
* include/winstl/error/error_desc.hpp:;
* include/winstl/winstl.h:;
* include/wtlstl/wtlstl.hpp:;
* minor documentation change STLSoft:;
* include/stlsoft/functional/method_adaptors.hpp:;
* thiscall overloads of mem_fun_ref() and mem_fun_ref_void();
* include/stlsoft/internal/cccap/borland.h:;
* include/stlsoft/internal/cccap/como.h:;
* include/stlsoft/internal/cccap/dmc.h:;
* include/stlsoft/internal/cccap/mwerks.h:;
* include/stlsoft/internal/cccap/vectorc.h:;
* include/stlsoft/internal/cccap/watcom.h:;
* added compiler feature symbol STLSOFT_CF_THISCALL_SUPPORTED;
* include/stlsoft/internal/cccap/gcc.h:;
* include/stlsoft/internal/cccap/msvc.h:;
* trivial formatting changes;
* include/stlsoft/internal/cccap/intel.h:;
* changed compiler discrimination features to STLSoft 1.10 mode;
* include/stlsoft/smartptr/scoped_handle_borland_.hpp:;
* Borland 5.5(.1) compatibility PlatformSTL:;


## 1.9.85 - 16th June 2009

* added merge() and swap() to stlsoft::frequence_map class template;
* winstl::listview_sequence::value_type::string_type (aka lvs_string_t) is now overrideable via the preprocessor, in preparation for future expansion of flexibility;
* atlstl/window/enhanced_window.hpp:;
* refactored child dialog handle elicitation to single private method, in preparation of future increased flexibility;
* stlsoft/containers/frequency_map.hpp:;
* added merge() method, which adds the entries and counts to the map;
* added swap();
* changed default count type to unsigned int for VC++ pre-7.0, to avoid incompatibilities with other libraries;
* stlsoft/error/error_desc.hpp:;
* nothrow on get_description() and c_str();
* winstl/controls/listview_sequence.hpp:;
* lvs_string_t may now be overridden via the pre-processor, in preparation for future expansion of flexibility;


## 1.9.84 - 23rd May 2009

* fixed defect in winstl::basic_reg_key::set_value() for REG_MULTI_SZ values (widestring only);
* "safe string" library and widestring support for stlsoft::basic_error_desc;
* various 64-bit LP64 compatibility changes;
* include/comstl/comstl.h:;
* documentation enhancements;
* include/stlsoft/error/error_desc.hpp:;
* "safe string" library support;
* widestring support;
* include/stlsoft/memory/auto_buffer.hpp:;
* include/stlsoft/string/string_traits.hpp:;
* include/stlsoft/util/integral_printf_traits.hpp:;
* include/stlsoft/util/limit_traits.h:;
* include/stlsoft/util/sign_traits.hpp:;
* 64-bit (LP64) compatibility;
* include/winstl/registry/reg_key.hpp:;
* fixed defect in set_value_() overload for REG_MULTI_SZ values (widestring only);


## 1.9.83 - 19th May 2009

* fixed defects in winstl::basic_reg_value::value_sz()/value_multi_sz();
* fixed defects in exception-safety in winstl::basic_reg_value and winstl::basic_reg_key;
* various minor fixes and documentation mods;
* include/winstl/registry/reg_key.hpp:;
* corrected exception-safety defect (by reversing the order of m_name and m_hkey);
* added required dependency on <functional>;
* documentation simplification;
* include/winstl/registry/reg_traits.hpp:;
* added reg_dup_key();
* deprecated key_dup();
* linearising behaviour between operating systems;
* tightening type-conversions;
* include/winstl/registry/reg_value.hpp:;
* modifications to value_multi_sz() and value_sz() to avoid possible race conditions (with registry changes made by other processes);


## 1.9.82 - 15th May 2009

* added winstl::reg_traits<>::reg_delete_tree();
* added IOStreams compatibility for winstl::findfile_sequence::value_type;
* include/winstl/filesystem/findfile_sequence.hpp:;
* added compatibility with IOStreams;
* include/winstl/registry/reg_traits.hpp:;
* added reg_delete_tree();


## 1.9.81 - 7th May 2009

* now recognises __func__, provided by Sun Pro, via STLSOFT_CF_func_SYMBOL_SUPPORT;
* abstracts __FUNCTION__ support to STLSOFT_FUNCTION_SYMBOL;
* include/stlsoft/internal/cccap/obsolete.h:;
* include/stlsoft/internal/cccap/sunpro.h:;
* added __func__ support detection;
* include/stlsoft/stlsoft.h:;
* added __func__ support detection, via STLSOFT_CF_func_SYMBOL_SUPPORT;
* added symbol for __FUNCTION__ or equivalent: STLSOFT_FUNCTION_SYMBOL;


## 1.9.80 - 6th May 2009

* now recognises support for variadic macros and #pragma once for later versions of Borland C/C++;
* SunPro compatibility improvements for UNIXSTL synchronisation components;
* fixes to defects in stlsoft::basic_simple_string at() and 5-parameter compare() methods;
* basic_path class templates (both UNIXSTL and WinSTL versions) now implement assignment operator differently to avoid possibilities of infinite loops (which can happen when a type with an opposing string encoding is used);
* correction to stlsoft::auto_buffer to ensure allocators are involved in swap() operations;
* correction to struct in_addr string access shims for compatibility with big-endian architectures;
* various changes for compatibility with "safe string" library;
* include/stlsoft/algorithms/std/alt.hpp:;
* "safe string" library compatibility (via a workaround that just ignores it wrt std::find());
* include/stlsoft/internal/cccap/borland.h:;
* STLSOFT_CF_PRAGMA_ONCE_SUPPORT support;
* STLSOFT_CF_SUPPORTS_VARIADIC_MACROS support;
* include/stlsoft/iterators/null_output_iterator.hpp:;
* suppression of compiler warning;
* include/stlsoft/memory/auto_buffer.hpp:;
* now swaps allocators;
* include/stlsoft/string/simple_string.hpp:;
* more "safe string" compatibility;
* fixed defective 5-parameter compare() method;
* fixed defect in non-mutating version of at(), whereby specifying the index == length did not throw, but returned a reference to the terminating nul character (which is what the subscript operator should do (and does do));
* include/stlsoft/string/split_functions.hpp:;
* trivial formatting change;
* include/inetstl/shims/access/string/std/in_addr.hpp:;
* use of ntohl(), so compatible with big-endian as well as little;
* compatibility with "safe string" library;
* include/unixstl/filesystem/path.hpp:;
* changed implementation of generic operator =() in order to avoid possibilities of infinite loops (which can happen when a type with an opposing string encoding is used);
* trivial documentation markup changes;
* include/unixstl/synch/process_mutex.hpp:;
* SunPro support (partially complete);
* include/unixstl/synch/thread_mutex.hpp:;
* include/winstl/filesystem/path.hpp:;


## 1.9.79 - 2nd May 2009

* UNIX compatibility for InetSTL;
* "safe string" library compatibility for InetSTL;
* include/inetstl/inetstl.h:;
* include/inetstl/error/exceptions.hpp:;
* include/inetstl/filesystem/filesystem_traits.hpp:;
* include/inetstl/filesystem/findfile_sequence.hpp:;
* include/inetstl/filesystem/ftpdir_sequence.hpp:;
* include/inetstl/filesystem/functionals.hpp:;
* include/inetstl/filesystem/searchspec_sequence.hpp:;
* include/inetstl/network/connection.hpp:;
* include/inetstl/network/session.hpp:;
* UNIX compatibility;
* include/inetstl/shims/access/string/std/in_addr.hpp:;
* compatibility with "safe string" library;


## 1.9.78 - 27th April 2009

* fixed serious defect in atlstl::copy_enumerator_impl::Reset();
* stlsoft::shared_ptr now works correctly if fails to allocate counter variable in conditions where exception handling is not supported;
* stlsoft::c_str_data_a(struct fm const*) now correctly handles case where tm pointer is NULL;
* corrected behaviour of get_environment_variable for both UNIXSTL and WinSTL system_traits traits classes;
* various compiler compatibility fixes;
* various documentation corrections;
* stlsoft/iterators/ostream_iterator.hpp:;
* documentation corrections;
* stlsoft/shims/access/string/std/time.hpp:;
* c_str_data_a(struct tm const* t) now correctly handles NULL tm pointer;
* stlsoft/smartptr/shared_ptr.hpp:;
* now correctly handles failure to allocate the shared counter, even when compiling absent exceptions;
* atlstl/automation/enumerators.hpp:;
* fixed defect in Reset() - which did nothing! - that was introduced in STLSoft 1.9.1 beta 5 (!) upon transcription from the original, correct, Synesis Software proprietary source;
* minor documentation fixes;
* unixstl/filesystem/filesystem_traits.hpp:;
* removal of dependency of str(n)cpy()/wcs(n)cpy(), which causes VC++ 8+ to carp about "safety";
* unixstl/system/system_traits.hpp:;
* corrected behaviour of get_environment_variable();
* winstl/filesystem/memory_mapped_file.hpp:;
* CodeWarrior compatibility;
* winstl/system/system_traits.hpp:;


## 1.9.77 - 9th March 2009

* corrected invalid invariants in memory_mapped_file classes in UNIXSTL and WinSTL;
* include/unixstl/filesystem/memory_mapped_file.hpp:;
* fixed invalid invariant;
* include/winstl/filesystem/memory_mapped_file.hpp:;


## 1.9.76 - 6th March 2009

* added swap() methods to memory_mapped_file classes in UNIXSTL and WinSTL;
* corrected defect in VC++ detection of bad_alloc support (which only affects VC++ 6 or earlier);
* include/stlsoft/internal/cccap/msvc.h:;
* corrected detection of bad_alloc support;
* include/unixstl/filesystem/memory_mapped_file.hpp:;
* added swap() method, and std::swap() overload;
* include/winstl/filesystem/memory_mapped_file.hpp:;


## 1.9.75 - 26th February 2009

* tidied up COMSTL documentation;
* tidied up scoped_handle use in winstl::memory_mapped_file;
* added checks to detect at compile time accidental use of &stat_data with winstl::filesystem_traits<>::get_file_size();
* fixed defect in winstl::basic_reg_value::value_sz(), whereby the nul-terminator is included in the resultant string length;
* tidied up winstl::basic_path, and added max_size() method;
* tidied up winstl::basic_commandline_parser, added substring-constructor, and changed subscript operator to allow indexing (but not use) of the end element;
* include/comstl/collections/collection_sequence.hpp:;
* include/comstl/collections/enumeration_policies.hpp:;
* include/comstl/collections/enumerator_sequence.hpp:;
* include/comstl/util/value_policies.hpp:;
* enhanced documentation markup;
* include/winstl/filesystem/filesystem_traits.hpp:;
* added private method declarations to prevent accidental use of get_file_size(HANDLE) as if it was get_file_size(&stat_data);
* include/winstl/filesystem/memory_mapped_file.hpp:;
* tidied up use of scoped_handle for compilers that struggle with it;
* include/winstl/filesystem/path.hpp:;
* added max_size() method;
* minor documentation markup enhancements;
* added precondition enforcement onto push() method;
* moved implementation of push(char_type*) into push_() worker method, in preparation for using ptr+len in public methods;
* include/winstl/registry/reg_value.hpp:;
* fixed defect in value_sz() method, whereby the resultant string length erroneously included the nul-terminator;
* include/winstl/system/commandline_parser.hpp:;
* removed \brief documentation markup tags;
* added additional ctor, taking length;
* renamed all internal member types to have trailing underscore;
* changed subscript operator to be able to index (but not use) the end element;


## 1.9.74 - 13th February 2009

* further implementation of special Borland version of stlsoft::scoped_handle;
* further workarounds to Borland code generation defects in stlsoft::basic_simple_string and platformstl::basic_file_lines;
* include/stlsoft/smartptr/scoped_handle_borland_.hpp:;
* implementation for scoped_handle<void>;
* include/stlsoft/string/simple_string.hpp:;
* insertion of non-functioning code to cause Borland 6.1.x to generate correct code (in Pantheios, amongst others);
* include/platformstl/filesystem/file_lines.hpp:;
* workaround for Borland code generation defect;


## 1.9.73 - 3rd February 2009

* added partial support for Borland 5.9.x and 6.1.x; to support use of Borland with Pantheios;
* re-applied VC++ 7.1 workaround eroneously removed in 1.9.70;
* include/stlsoft/stlsoft.h:;
* support for Borland 5.9.x and 6.1.x;
* include/stlsoft/smartptr/scoped_handle.hpp:;
* proper support for Borland, via a separate implementation (in stlsoft/smartptr/scoped_handle_borland_.hpp);
* include/stlsoft/smartptr/scoped_handle_borland_.hpp:;
* include/winstl/filesystem/findfile_sequence.hpp:;
* workaround for VC++ 7.1 defect (requiring length() to return size_t, not member type size_type);


## 1.9.72 - 1st February 2009

* added char_copy() methods to filesystem_traits classes in UNIXSTL, as part of move away from "unsafe" string functions;
* fixed defect in winstl::squeeze_path() whereby wrong length is returned if buffer size is < 5 and the file length < buffer size;
* removes unwanted trailing slash in application directory from winstl::basic_searchpath_sequence;
* further work to remove dependency on "unsafe" string functions;
* include/comstl/shims/access/string/guid.hpp:;
* modified symbols that broke reserved naming rules;
* include/inetstl/filesystem/filesystem_traits.hpp:;
* added str_n_compare();
* tidied up asserts;
* removed dependency on "unsafe" string library functions;
* include/inetstl/filesystem/findfile_sequence.hpp:;
* added optional length parameter to get_directory();
* include/unixstl/filesystem/file_path_buffer.hpp:;
* tidying up;
* include/unixstl/filesystem/filesystem_traits.hpp:;
* tidying up, and removal of declarations of functions (from wide char specialisation) that are not implemented;
* include/unixstl/filesystem/path.hpp:;
* removal of dependency on so-called "unsafe" string functions;
* simplification of implementation;
* include/unixstl/system/system_traits.hpp:;
* added char_copy();
* include/winstl/error/exceptions.hpp:;
* minor mods;
* include/winstl/filesystem/findvolume_sequence.hpp:;
* removed dependency on "unsafe" string functions;
* include/winstl/filesystem/path.hpp:;
* simplification;
* include/winstl/filesystem/path_functions.hpp:;
* fixed defect whereby if buffer size is < 5 and the file length < buffer size, the wrong length is returned;
* now implemented in terms of system_traits<>::char_copy();
* include/winstl/system/searchpath_sequence.hpp:;
* no longer dependent on "safe" string library;
* removes unwanted trailing slash on application directory;
* include/winstl/system/system_traits.hpp:;


## 1.9.71 - 28th January 2009

* fixed DMC++ incompatibility introduced in 1.9.70;
* include/winstl/filesystem/findfile_sequence.hpp:;
* added workaround for missing CO_E_PATHTOOLONG on DMC++;


## 1.9.70 - 25th January 2009

* improved stlsoft::find_next_token() function templates to ensure that all empty fields are reported to caller;
* added char_copy() methods to filesystem_traits classes in InetSTL and WinSTL, as part of move away from "unsafe" string functions;
* minor enhancements to platformstl::readdir_sequence, to disambiguate constructor overloads;
* removed all "unsafe" string functions from winstl::basic_findfile_sequence class template and supporting components;
* improved winstl::basic_path class template to ensure proper behaviour in corner cases of use of push() and pop() methods;
* include/stlsoft/string/tokeniser_functions.hpp:;
* fixed benign defects in find_next_token() overloads, whereby certain empty fields were not reported to caller;
* documentation enhancements;
* adding in more pre-condition enforcements;
* include/inetstl/filesystem/filesystem_traits.hpp:;
* char_copy() operations;
* include/platformstl/filesystem/readdir_sequence.hpp:;
* separation and disambiguation of constructor overloads;
* include/winstl/filesystem/findfile_sequence.hpp:;
* added defaulted parameter to get_directory() to retrieve the directory length;
* replaced all instances of so-called "unsafe" string functions with system_traits::char_copy();
* include/winstl/filesystem/path.hpp:;
* various fixes to push() and push_sep();
* corrected defects in pop(), seen in root directory paths, and paths involving UNC;
* include/winstl/system/system_traits.hpp:;
* added char_copy() to system_traits specialisations;
* trivial documentation markup modifications;


## 1.9.69 - 23rd January 2009

* improved robustness of winstl::path_squeeze;
* more "Safe String" library compatibility changes;
* include/winstl/filesystem/path.hpp:;
* now implemented in terms of memcpy(), rather than strcpy(), strcat(), etc;
* include/winstl/filesystem/path_functions.hpp:;
* making robust in light of corner cases;
* include/winstl/string/resource_string.hpp:;
* removal of unnecessary string access shim;


## 1.9.68 - 19th January 2009

* fix defect, and updated docs, for stlsoft::must_init utility class template;
* include/stlsoft/util/must_init.hpp:;
* fixed ambiguous operator +() bug;
* documentation fixes;


## 1.9.67 - 17th January 2009

* compatibility with GCC on Fedora on PPC;
* correction of semantics of null_allocator;
* include/stlsoft/stlsoft.h:;
* minor mods to documentation markup;
* include/stlsoft/internal/cccap/gcc.h:;
* PowerPC (Fedora Linux) compatibility fix (thanks to Sergey Nikulov);
* include/stlsoft/memory/null_allocator.hpp:;
* when exception support is enabled it throws std::bad_alloc; otherwise, requesting memory from it is a contract violation;


## 1.9.66 - 4th January 2009

* compatibility with GCC 4.3's pedantic precedence warnings;
* compatibility with SunPro compiler for limit_traits;
* include/stlsoft/internal/cccap/sunpro.h:;
* correcting Jon's surname;
* include/stlsoft/stlsoft.h:;
* include/stlsoft/util/limit_traits.h:;
* compatibility with SunPro compiler;


## 1.9.65 - 1st January 2009

* "Safe String" library compatibility changes;
* include/winstl/filesystem/filesystem_traits.hpp:;
* removal of dependency of str(n)cpy()/wcs(n)cpy(), which causes VC++ 8+ to carp about "safety";
* removal of dependency of strcpy()/wcscpy(), which causes VC++ 8+ to carp about "safety";
* include/winstl/synch/process_mutex.hpp:;
* trivial documentation modification;


## 1.9.64 - 28th December 2008

* fix to string access shims for VARIANT;
* include/comstl/shims/access/string/variant.hpp:;
* fixed defect seen with Borland, whereby conversion to multibyte string in c_str_VARIANT_proxy_a's implicit conversion operator was not carried out;


## 1.9.63 - 9th December 2008

* optimised stlsoft::basic_string_view::reserve();
* enhanced compatibility for stlsoft::fixed_array_?d class templates;
* stlsoft/containers/fixed_arrays.hpp:;
* compatibility with VC++ /Za option for fixed arrays;
* stlsoft/string/simple_string.hpp:;
* optimised reserve() method so that it now does not alloc new buffer if requested size is less than current capacity;


## 1.9.62 - 1st December 2008

* fixed defect in interface_cast<> and try_interface_cast<>;
* improved compatibility with Visual C++ 9;
* speculative support for Intel C/C++ 11.0;
* fixed defect in winstl::to_SYSTEMTIME(DATE) overload;
* comstl/conversion/interface_cast.hpp:;
* fixed reference leak in smart pointer forms of interface_cast() and try_interface_cast();
* comstl/conversion/method_cast.hpp:;
* minor tidying;
* stlsoft/internal/cccap/msvc.h:;
* now correctly determines that VC++ 9 requires STLSOFT_CF_FUNCTION_SIGNATURE_FULL_ARG_QUALIFICATION_REQUIRED;
* stlsoft/stlsoft.h:;
* speculatively supports Intel C/C++ 11.0;
* winstl/shims/conversion/to_SYSTEMTIME/DATE.hpp:;
* fixed defect - initialising unknown name - in non-exception mode;


## 1.9.61 - 19th November 2008

* better compatibility with SAPI.h for COMSTL's sapi_util.hpp;
* documentation markup improvements for a number of files;
* stlsoft/iterators/filter_iterator.hpp:;
* fixed up incorrect fwd-include guards;
* stlsoft/string/shim_string.hpp:;
* stlsoft/string/split_functions.hpp:;
* removed unnecessary iterator declaration;
* improved documentation markup;
* comstl/speech/sapi_util.hpp:;
* compatibility with sapi.h;
* mfcstl/shims/attribute/get_synch_handle.hpp:;
* documentation markup improvements;


## 1.9.60 - 27th October 2008

* added stlsoft::apply_const();
* added stlsoft/conversion/m2w.hpp;
* stlsoft/stlsoft.h:;
* stlsoft/conversion/m2w.hpp: provides access to stlsoft::m2w converter class;


## 1.9.59 - 25th October 2008

* change in ATLSTL's property method helpers to avoid infinite loop in Visual C++ 6 problem when implementing property puts to CComBSTR;
* fixed compile error with GCC when using VARIANTs in C compilation units;
* atlsoft/automation/property_method_helpers.hpp:;
* fixed infinite loop defect in put_MemberValue(..., CComVariant const&, ...); now assigns directly and handles case whereby assignment fail;
* comstl/comstl.h:;
* refactored way in which VARIANT-manipulation macros are defined for C compilation to fix compile errors with GCC;


## 1.9.58 - 16th October 2008

* fixed major defect introduced in 1.9.52 to WinSTL's time string access shims;
* fixed minor defects in COMSTL's VARIANT string access shims;
* fixed defect in documentation generation whereby examples were omitted;
* reduced compilation dependencies in STLSoft's time string access shims;
* stlsoft/shims/access/string/time.hpp:;
* reduced include dependencies;
* comstl/shims/access/string/variant.hpp:;
* passed VARIANT_ALPHABOOL to all variant conversion routines;
* fixed defect whereby widestring and multibyte string lengths were assumed to be equal (by c_str_len_w() and c_str_len_a() being implemented in terms of c_str_len());
* winstl/shims/access/string/time.hpp:;
* fixed defect whereby last character of converted date is truncated;


## 1.9.57 - 10th October 2008

* addition of missing const_reference member type in various Windows controls collection classes;
* C / C++ compatibility fixes for COMSTL;
* fix of minor non-standard name in winstl::int_to_string() supporting class;
* a large number of files were altered in minor ways, to do with whitespace and the placement of * and & symbols;
* several files' documentation markup was cleaned up;
* comstl/comstl.h:;
* added the macros COMSTL_ACCESS_VARIANT_MEM_BYPTR(), COMSTL_ACCESS_VARIANT_MEM_BYREF(), COMSTL_ACCESS_VARIANT_vt_BYPTR(), COMSTL_ACCESS_VARIANT_vt_BYREF(), COMSTL_ACCESS_VARIANT_decVal_BYPTR(), and COMSTL_ACCESS_VARIANT_decVal_BYREF(), which abstract the access of VARIANT members between C (incl. Standard C) and C++;
* comstl/util/DECIMAL_functions.h:;
* comstl/util/VARIANT_functions.h:;
* compatibility with Standard-C compilation (where anonymous unions and structures are not valid);
* winstl/conversion/int_to_string.hpp:;
* rename of non-standard symbol;
* winstl/controls/combobox_sequence.hpp:;
* winstl/controls/edit_line_sequence.hpp:;
* winstl/controls/listbox_data_sequence.hpp:;
* winstl/controls/listbox_sequence.hpp:;
* added const_reference member type;


## 1.9.56 - 1st October 2008

* a large number of minor enhancements to the documentation markup;
* fixes to defects to include guards in UNIXSTL;
* unixstl/filesystem/memory_mapped_file.hpp:;
* unixstl/performance/performance_counter.hpp:;
* unixstl/performance/processtimes_counter.hpp:;
* tidied up includes for UNIX emulation on Win32;
* fixed defect in forward-include guards for sys/mman.h, sys/resource.h and sys/time.h;
* unixstl/synch/sleep_functions.h:;


## 1.9.55 - 27th September 2008

* corrected defects in stlsoft::wide2multibyte and stlsoft::multibyte2wide conversion classes;
* fixes to various x64 defects related to use of inappropriate calling convention specifiers with use of dl_call;
* sundry other modifications in internal pre-processor facilities and small improvements to Watcom compatibility;
* stlsoft/stlsoft.h:;
* added internal pre-processor facilities;
* winstl/conversion/char_conversions.hpp;
* corrected defective effective size() method (inherited from parent) of multibyte2wide and wide2multibyte class templates, by hiding parent and defining in-class version of method;
* some Watcom compatibility;
* winstl/dl/dl_call.hpp:;
* winstl/system/pid_sequence.hpp:;
* winstl/system/process_module_sequence.hpp:;
* ensuring x64 compatibility with use of dl_call;
* winstl/filesystem/memory_mapped_file.hpp:;
* winstl/registry/reg_value.hpp:;
* winstl/registry/util/shared_handles.hpp:;
* fixes to x64 defects (contributed by Austin Ziegler);


## 1.9.54 - 15th September 2008

* added stlsoft::exception_string::truncate() method;
* removed dependency of UDATE for to_FILETIME() and to_SYSTEMTIME() shim overloads for DATE type;
* stlsoft/util/exception_string.hpp:;
* added truncate() method;
* winstl/shims/conversion/to_FILETIME.hpp:;
* winstl/shims/conversion/to_FILETIME/DATE.hpp:;
* removed dependency of to_FILETIME(DATE const&) on UDATE;
* winstl/shims/conversion/to_SYSTEMTIME.hpp:;
* winstl/shims/conversion/to_SYSTEMTIME/DATE.hpp:;
* removed dependency of to_SYSTEMTIME(DATE const&) on UDATE;


## 1.9.53 - 14th September 2008

* changed definition of STLSOFT_STATIC_ASSERT() to work with GCC;
* defect defect in pre-condition enforcement of winstl::system_traits::expand_environment_strings();
* stlsoft/stlsoft.h:;
* changed definition of STLSOFT_STATIC_CAST() for GCC, since GCC allows an array dimension of -1;
* winstl/system/system_traits.hpp:;
* fixed defective pre-condition enforcement of expand_environment_strings();


## 1.9.52 - 11th September 2008

* fix for warnings in 64-bit compilation (VC9) in WinSTL string access shims for SYSTEMTIME; also added extra safeguard against external race condition;
* winstl/shims/access/string/time.hpp;
* fixed up 64-bit compiler warnings, by applying suitable unsigned->signed casts;
* added in safeguard for unlikely case of changing date/time pictures mid call;


## 1.9.51 - 7th September 2008

* workaround for defective exception-throwing behaviour of stlsoft::conversion_error with VC6;
* fixed defect in WinSTL string access shims for SYSTEMTIME that faults when asked to process an invalid time value;
* stlsoft/error/conversion_error.hpp;
* fixed defect whereby the VC++ 6 compiler that causes the throwing of any derived class to cause an ICE;
* winstl/shims/access/string/time.hpp;
* fixed defect whereby failure to convert, due to invalid date, results in fault in shim string;


## 1.9.50 - 3rd September 2008

* added stlsoft character conversion typedefs m2w, w2m, t2m, m2t;
* fix for VC++ 6 defect in requiring return code after exception throw;
* stlsoft/conversion/char_conversions.hpp:;
* added typedefs m2w, w2m, t2m, m2t;
* stlsoft/conversion/w2m.hpp;
* includes stlsoft/conversion/char_conversions.hpp;


## 1.9.49 - 2nd September 2008

* fix for DMC++ defect in winstl::reg_value function template definition;
* added winstl character conversion typedefs m2w, w2m, t2m, m2t;
* winstl/conversion/char_conversions.hpp:;
* added typedefs m2w, w2m, t2m, m2t;
* winstl/conversion/w2m.hpp;
* includes winstl/conversion/char_conversions.hpp;
* winstl/registry/reg_key.hpp:;


## 1.9.48 - 23rd August 2008

* added comstl/util/CY_functions.h;
* added comstl/util/DECIMAL_functions.h;
* added comstl/util/VARIANT_functions.h;
* added comstl::variant conversion constructor for DECIMAL;
* fixed bug in stlsoft::trim_all();
* added winstl::basic_error_desc<>::empty();
* stlsoft/containers/frequency_map.hpp;
* addition of bool_type member type;
* stlsoft/containers/unsorted_map.hpp;
* addition of class_type member type;
* stlsoft/string/shim_string.hpp;
* increased internal memory buffer of basic_shim_string by 1, so that users do not need to specify a number inclusive of the terminating nul character;
* stlsoft/string/trim_functions.hpp;
* fixed bug in trim_all() whereby the right iterator could be before the left;
* comstl/util/variant.hpp;
* added conversion constructor for DECIMAL;
* implemented equal();
* comstl/util/CY_functions.h;
* CY_compare();
* comstl/util/DECIMAL_functions.h;
* DECIMAL_compare();
* comstl/util/VARIANT_functions.h;
* VARIANT_equal();
* winstl/error/error_desc.hpp;
* added bool_type member type;
* added empty() method;


## 1.9.47 - 12th August 2008

* enhancement of stlsoft::read_line() function template to work with various line-termination sequences;
* enhancement of fixed array classes to allow zero size;
* winstl::clipboard_format_sequence enhancements to iterator type profile;
* winstl::clipboard_scope defect fix and documentation enhancement;
* syntactic modification of contract enforcement statements to a large number of components to address warnings with GCC 4.3 in pedantic mode;
* stlsoft/containers/fixed_array.hpp;
* fixed array classes now can be of zero size;
* stlsoft/containers/static_array.hpp - GCC 4.3 pedantic warnings;
* stlsoft/conversion/union_cast.hpp - GCC 4.3 pedantic warnings;
* rewrote stlsoft::read_line(), which can now use any combination of the line termination sequences CR, LF and CR+LF. stlsoft::read_line() is now found in stlsoft/filesystem/read_line.hpp;
* stlsoft/filesystem/io_functions.hpp now includes stlsoft/filesystem/read_line.hpp;
* stlsoft/string/char_traits.hpp - GCC 4.3 pedantic warnings;
* acestl/collections/message_queue_sequence.hpp - GCC 4.3 pedantic warnings;
* acestl/reactor/custom_event_handler.hpp - GCC 4.3 pedantic warnings;
* comstl/collections/enumerator_sequence.hpp - GCC 4.3 pedantic warnings;
* comstl/string/bstr.hpp - GCC 4.3 pedantic warnings;
* inetstl/filesystem/findfile_sequence.hpp - GCC 4.3 pedantic warnings;
* mfcstl/collections/clist_adaptors.hpp - GCC 4.3 pedantic warnings;
* rangelib/integral_range.hpp - GCC 4.3 pedantic warnings;
* winstl::clipboard_format_sequence::const_iterator now properly defined according to rules outlined in Extended STL, vol 1 (winstl/clipboard/clipboard_format_sequence.hpp);
* winstl::clipboard_scope defect in deallocation function fixed, and documentation markup improved to make clear the full semantics;
* winstl/controls/listbox_const_iterator.hpp - GCC 4.3 pedantic warnings;
* winstl/controls/listbox_data_const_iterator.hpp - GCC 4.3 pedantic warnings;
* winstl/filesystem/findfile_sequence.hpp - GCC 4.3 pedantic warnings;
* winstl/filesystem/findvolume_sequence.hpp - GCC 4.3 pedantic warnings;
* winstl/security/acl_sequence.hpp - GCC 4.3 pedantic warnings;
* winstl/shell/drophandle_sequence.hpp - GCC 4.3 pedantic warnings;
* winstl/toolhelp/sequence_base.hpp - GCC 4.3 pedantic warnings;
* winstl/window/zorder_iterator.hpp - GCC 4.3 pedantic warnings;


## 1.9.46 - 11th August 2008

* defect fixes to stlsoft::pod_vector;
* reduced coupling, and increased functionality, of stlsoft::format_bytes();
* sundry compatibility improvements;
* stlsoft::file_lines() changed slightly to ensure correct behaviour on Windows platforms when emulating UNIX;
* stlsoft::std_fill_n() now eschews use of std::fill_n() when used with Microsoft's Safe String library;
* stlsoft::pod_vector<> defects fixed:;
* fix for assert in copy-ctor when copying empty object;
* fix for failure to write value_type() into 1-parameter resize();
* fixed defect in resize() when moving from 0 != size() to 0 == size();
* fixed defect in range insert;
* fixed defect in erase();
* renamed internal type buffer_type to buffer_type_;
* stlsoft::format_bytes() rewritten to use custom hex formatting instead of stdio formatting functions;
* winstl__FormatMessageA/W__buff_inst() altered for 64-bit compatibility;


## 1.9.45 - 8th June 2008

* enhancement to stlsoft::to_uint64 conversion shim for ULARGE_INTEGER;
* more Win-64 compatibility changes;
* fixes to winstl::basic_path class template;
* inetstl/filesystem/filesystem_traits.hpp - 64-bit compatibility;
* winstl/shims/conversion/to_uint64/ULARGE_INTEGER.hpp - added overloads for ULARGE_INTEGER to stlsoft::to_uint64 conversion shim;
* winstl/filesystem/filesystem_traits.hpp - get_full_path_name() sets last error to ERROR_FILENAME_EXCED_RANGE when path is too long for GetFullPathNameA() (since that does not set it);
* winstl/filesystem/path.hpp -;
* fix to push() to ensure that ambient slash flavour is used;
* make_absolute() now throws an exception if get_full_path_name() does not succeed;
* fix to canonicalise() for empty paths;
* fix to canonicalise() for paths that contain drive and top-slash only;


## 1.9.44 - 1st June 2008

* bug fix in winstl/shims/access/string/LSA_UNICODE_STRING.hpp, required for newly released flecxx library;
* winstl/shims/access/string/LSA_UNICODE_STRING.hpp - removed trailing slash in two of the shim functions;


## 1.9.43 - 31st May 2008

* more Win64-compatibility modifications;
* more Safe String library modifications;
* expanded the stlsoft::get_FILE_ptr attribute shim for MFC's CStdioFile;
* stlsoft/conversion/char_conversions.hpp - Safe String compatibility;
* stlsoft/string/trim_functions.hpp - Safe String compatibility, and removal of dependency on soon-to-be-obselete STLSoft standard emulation functions (as they'll be handed off to the soon-to-be-released flecxx library; see http://flecxx.org/);
* stlsoft/util/constraints.hpp - elimination of warnings for some highly pedantic compiler modes;
* comstl/collections/enumerator_sequence.hpp - Win64 compatibility;
* comstl/string/bstr.hpp - Win64 compatibility;
* mfcstl/shims/attribute/get_FILE_ptr.hpp;
* winstl/clipboard/clipboard_scope.hpp - tightening up of exception handling code;


## 1.9.42 - 17th May 2008

* more Win64-compatibility modifications;
* more Safe String library modifications;
* comstl/string/olestring_functions.h - Safe String library compatibility modifications, using wcscpy_s() instead of wcscpy();
* inetstl/filesystem/findfile_sequence.hpp - minor warning suppression;
* winstl/window/functions.h - rewrote GetWindowLong()/SetWindowLong() use to common functions winstl__get_window_sptrint_() and winstl__set_window_sptrint_();


## 1.9.41 - 13th May 2008

* bug fix for GCC compilation on PowerPC that was broken with 1.9.40;


## 1.9.40 - 13th May 2008

* significant refactoring of compiler-capability discrimination for GCC and VC++;
* compatibility fixes for SunPro compilers;
* bug fix in integral_printf_traits (introduced in 1.9.39);
* include/stlsoft/internal/cccap/gcc.h: significant refactoring;
* include/stlsoft/internal/cccap/msvc.h: significant refactoring;
* include/stlsoft/internal/cccap/obsolete.h: defines old symbols in terms of new; to be #included by all refactored compiler capability discrimination files while rest of codebase is not up to date;
* stlsoft/string/split_functions.hpp: now defines STLSOFT_STRING_SPLIT_FUNCTIONS_CANNOT_USE_STATIC_ARRAY when using SunPro;
* stlsoft/util/integral_printf_traits.hpp: fixed bug in 64-bit specialisations that was introduced in 1.9.39;


## 1.9.39 - 11th May 2008

* another tranche of changes for Win64 support;
* added STLSOFT_WARN_64, to apply to variables whose sizes will be different between Win32 and Win64, to elicit warnings from VC++ (stlsoft/stlsoft.h);
* stlsoft::truncation_test: suppression of 4267 warning in VC++ for the final conversion, since it's already been determined by the test that the conversion is valid (stlsoft/conversion/truncation_test.hpp);
* adjustment of winstl::BOOL2bool() for -Wp64 compilation (winstl/winstl.h);
* Windows Registry Library: change of result type from ws_long_t to LONG, to avoid unnecessary conversions and Win32/64 warnings (winstl/registry/reg_traits.hpp);
* winstl::system_traits<>::get_locale_info(): change of cchData param from int_type to int to avoid unnecessary conversions and Win32/64 warnings (winstl/system/system_traits.hpp);
* Windows Window Library: wholesale change from use of ws_long_t to ws_sptrint_t to ensure that the window style functions are 32 and 64-bit compatible (winstl/window/functions.h);
* winstl::set_window_icon(): suppression of 4267 warning in VC++ for what appears to be a compiler bug in interpretation of the conversion to LPARAM in this function (winstl/window/functions.h);


## 1.9.38 - 4th May 2008

* another tranche of changes for Win64 support;
* discrimination of PLATFORMSTL_ARCH_IS_**** symbols: PLATFORMSTL_ARCH_IS_X86 PLATFORMSTL_ARCH_IS_IA64 PLATFORMSTL_ARCH_IS_X64 PLATFORMSTL_ARCH_IS_INTEL PLATFORMSTL_ARCH_IS_POWERPC PLATFORMSTL_ARCH_IS_ALPHA PLATFORMSTL_ARCH_IS_HPPA PLATFORMSTL_ARCH_IS_SPARC;


## 1.9.37 - 3rd May 2008

* first tranche of changes for Win64 support;
* cs_sptrint_t and cs_uptrint_t integer types that are the same size as the pointers of the ambient architecture;
* platformstl/synch/atomic_functions.h now discriminates on PLATFORMSTL_OS_IS_WINDOWS instead of PLATFORMSTL_OS_IS_WINDOWS;
* platformstl/synch/atomic_functions.h now discriminates on WINSTL_ARCH_IS_X86, WINSTL_ARCH_IS_IA64 and WINSTL_ARCH_IS_X64 instead of _M_IX86, _M_IA64 and _M_X64;
* added UNIXSTL_ARCH_IS_X86, UNIXSTL_ARCH_IS_IA64 and UNIXSTL_ARCH_IS_X64 architecture discrimination symbols;
* added WINSTL_OS_IS_WIN32 and WINSTL_OS_IS_WIN64 operating system discrimination symbols;
* added WINSTL_ARCH_IS_X86, WINSTL_ARCH_IS_IA64 and WINSTL_ARCH_IS_X64 architecture discrimination symbols;
* winstl/synch/atomic_functions.h refactored to use new symbols;
* winstl/filesystem/filesystem_traits.hpp refactored to use new symbols;
* winstl/system/system_traits.hpp refactored to use new symbols;


## 1.9.36 - 30th April 2008

* added support for FreeBSD operating system;


## 1.9.35 - 29th April 2008

* added value_multi_sz() to winstl::reg_value;
* refactored exception handling in basic_reg_key::reg_class() to avoid spurious compiler warnings about unreachable branches;


## 1.9.34 - 25th April 2008

* renamed winstl::get_hwnd attribute shim to winstl::get_HWND;
* minor adjustments to Sun Pro support;
* library feature discrimination symbol cleanup;
* refactored error/exception handling in Windows Registry library;
* STLSOFT_CF_BIDIRECTIONAL_ITERATOR_SUPPORT changed to STLSOFT_LF_BIDIRECTIONAL_ITERATOR_SUPPORT in all files;
* renamed all get_hwnd() attribute shims to get_HWND();
* include/stlsoft/internal/cccap/sunpro.h: adjustments to detect _BOOL and _WCHAR_T for the bool and wchar_t types support;
* include/stlsoft/internal/cccap/sunpro.h: adjustment to integral size detection: now simply searches for _LP64 or __LP64__ for LP64, otherwise assumes int & long are 4-bytes;
* include/stlsoft/internal/cccap/sunpro.h: fix to known bug in Sun Pro C++ library headers - <cwchar> is introduced to ensure it is included before <stdio.h>;
* stlsoft::auto_buffer::allocate_() 1-param overload implemented in terms of the 2-param version;
* fix to comstl::co_create_instance(), to directly assign between ref_ptr instances via set(), rather than copy constructors;
* winstl::key_not_duplicated_exception exception class to Windows Registry library;
* error/exception handling for all the following classes in the Windows;
* winstl::basic_reg_key;
* winstl::basic_reg_key_sequence;
* winstl::basic_reg_value;
* winstl::basic_reg_value_sequence;


## 1.9.33 - 25th April 2008

* added support for the SunPro C and C++ compilers;
* various mods to ensure headers are self-contained when used with Windows "lean and mean" suppression symbols;
* STLSOFT_STRINGIZE_w_() now defined in terms of STLSOFT_STRINGIZE_a() for Sun Pro C and Borland;
* Sun Pro C and Sun Pro C++ compatibility;
* stlsoft::fixed_array_?d::swap() methods now implemented in terms of new private get_allocator_() method;
* STLSOFT_CF_BIDIRECTIONAL_ITERATOR_SUPPORT removed from all the compiler capability files;
* stlsoft::member_selector_iterator.hpp now compatible with Sun Pro C++ when used in the -library=libCstd;
* stlsoft/memory/allocator_features.hpp now compatible with Sun Pro C++ when used in the -library=libCstd;
* stlsoft/memory/auto_buffer.hpp now compatible with Sun Pro C++ when used in the -library=libCstd;
* stlsoft/shims/access/string/std/c_string.h now compatible with Sun Pro C++;
* stlsoft/string/simple_string.hpp now compatible with Sun Pro C++;
* stlsoft/util/integral_printf_traits.hpp now compatible with Sun Pro C++;
* correction to definition of stlsoft::integral_printf_traits<ss_uint8_t>;
* stlsoft/util/std/iterator_helper.hpp now compatible with Sun Pro C++;
* stlsoft/util/std/library_discriminator.hpp now compatible with Sun Pro C++;
* comstl::enumerator_sequence<>::quanta();
* comstl/error/errorinfo_functions.h includes oaidl.h and oleauto.h;
* comstl/internal/interface_traits_std.hpp includes oaidl.h;
* comstl/util/initialisers.hpp includes ole2.h;
* unixstl/unixstl.h now compatible with Sun Pro C++;
* correction to return type of winstl__combobox_getitemdata();
* correction to return type of winstl__listbox_getitemdata();
* renamed listbox_operation_traits to listbox_data_sequence_traits (in winstl/controls/listbox_data_sequence.hpp);
* renamed listbox_operation_traits to listbox_sequence_traits (in winstl/controls/listbox_sequence.hpp);
* made winstl/error/exceptions.hpp self-contained when used with Windows "lean and mean" suppression symbols;
* marked winstl/shims/access/string/lsa_unicode_string.hpp as not for unit-test (since the unit-test programs do not #include <ntsecapi.h>);


## 1.9.32 - 22nd April 2008

* fix for VC++ 8/9 linker error in the allocator_selector;
* refactoring of string access shim headers for lightweight compilation;
* refactoring of string access shim headers in light of Windows "lean and mean" disabling symbols (e.g. NOUSER, NOWINOFFSETS);


## 1.9.31 - 13th April 2008

* exception hierarchy refactoring;
* bug fix to stlsoft::must_init;
* new STLSoft-root exception: stlsoft::project_exception;
* fixes to stlsoft::must_init for built-in types to support assignment;


## 1.9.30 - 3rd April 2008

* tidying of distribution;


## 1.9.29 - 3rd March 2008

* more preparation for safe string library compatibility;


## 1.9.28 - 24th March 2008

* enhancement to winstl::reg_key class;
* preparation for safe string library compatibility;
* bug fix for C-compilation in winstl/controls/functions.h;
* stlsoft/internal/safestr.h;
* correction to winstl/controls/functions.h;
* improved error handling in winstl::reg_key;
* winstl::reg_key new methods: has_sub_key() and has_value();
* winstl::reg_traits now inherits from winstl::system_traits;
* winstl::window_traits now inherits from winstl::system_traits;


## 1.9.27 - 17th March 2008

* support for Visual C++ 9 (Visual C++ 2008);
* fixed pre-processor typo that breaks GCC -pedantic;
* added item-data functions for list-/combo-boxes;
* added support for Visual C++ 9.0 (Visual C++ 2008);
* fix for pre-processor typo in unixstl::filesystem_traits, which is breaking -pendantic GCC compilation;
* added item-data functions for list-/combo-boxes: listbox_getitemdata() and combobox_getitemdata();


## 1.9.26 - 15th March 2008

* definition, where appropriate, of STLSOFT_CF_FUNCTION_SYMBOL_SUPPORT, denoting that a particular compiler supports the __FUNCTION__ pre-processor symbol;
* stlsoft/internal/cccap/borland.h;
* stlsoft/internal/cccap/como.h;
* stlsoft/internal/cccap/dmc.h;
* stlsoft/internal/cccap/gcc.h;
* stlsoft/internal/cccap/intel.h;
* stlsoft/internal/cccap/msvc.h;
* stlsoft/internal/cccap/mwerks.h;
* stlsoft/internal/cccap/unknown.h;
* stlsoft/internal/cccap/vectorc.h;
* stlsoft/internal/cccap/watcom.h;


## 1.9.25 - 9th March 2008

* wholesale increase of use of forward include guards, to reduce compilation times;


## 1.9.24 - 8th March 2008

* finishing up some missed std::swap refactoring;
* stlsoft/collections/array_view.hpp now uses std_swap;
* stlsoft/string/string_view.hpp now uses std_swap;
* unixstl/filesystem/glob_sequence.hpp now uses std_swap;
* unixstl/filesystem/path.hpp now uses std_swap;


## 1.9.23 - 20th February 2008

* fix for minor compiler compatibility issue;
* STLSOFT_CF_EXCEPTION_SUPPORT was being defined for Metrowerks CodeWarrior in C compilation units. This is now corrected;


## 1.9.22 - 8th February 2008

* refactored unixstl/synch/util/features.h;
* adjusted the PThreads discrimination in unixstl/synch/util/features.h to not be affected by the inclusion of pthread.h (which seems to be included by <string> on UNIX with GCC !?);
* minor warning suppression in winstl/filesystem/memory_mapped_file.hpp;
* minor warning-avoidance refactoring in winstl/system/console_colour_scope.hpp;


## 1.9.21 - 5th February 2008

* fixed a bug in platformstl/synch/util/features.h;
* platformstl/synch/util/features.h was erroneously #including unixstl/synch/sleep_functions.h, rather than unixstl/synch/util/features.h;


## 1.9.20 - 3rd February 2008

* added new stlsoft::singlethreaded_tss_index synchronisation utility class;
* new stlsoft::singlethreaded_tss_index class (stlsoft/synch/singlethreaded_tss_index.hpp), which is interface-compatible with unixstl::tss_index and winstl::tss_index, for single-threaded contexts;


## 1.9.19 - 2nd February 2008

* enhancement of SAPI utility header for COMSTL;
* comstl/speech/sapi_util.hpp now introduces the SPEAKFLAGS enumerators into the global namespace, to be compatible with the SAPI headers;


## 1.9.18 - 27th January 2008

* enhancement of STLSoft's integral_printf_trait component to support Pantheios 1.0.1 beta 91;
* release of SAPI utility header for COMSTL;
* added hex_format_a/w() methods to integral_printf_traits;
* comstl/speech/sapi_util.hpp, which abstracts away the definitions of the SAPI interfaces and constants, for those compilers that do not have the headers supplied;


## 1.9.17 - 5th January 2008

* bug fix for UNIXSTL on Leopard/GCC 4.0.1;
* Fixed new incompatibility in the definition of UNIXSTL_ASSERT for the Mac OS-X platform, evinced with Leopard and GCC 4.0.1;


## 1.9.16 - 29th December 2007

* bug fix in stlsoft::printf_traits;
* bug fix in winstl::GetTimeFormat_msA/W;
* other minor bug fixes;
* minor feature enhancements & refactoring;
* new stlsoft::integral_printf_traits traits class, which fixes the bug in stlsoft::printf_traits whereby integers used the %ld and %lu;
* now uses new symbols _STLSOFT_SIZEOF_CHAR, _STLSOFT_SIZEOF_SHORT, _STLSOFT_SIZEOF_INT, _STLSOFT_SIZEOF_LONG and _STLSOFT_SIZEOF_LONG_LONG;
* added symbol PLATFORMSTL_OS_IS_WIN64;
* added symbol PLATFORMSTL_OS_IS_WINDOWS;
* refactoring of stlsoft::auto_destructor::get mutating/non-mutating overloads;
* refactoring of stlsoft::auto_array_destructor::get mutating/non-mutating overloads;
* refactoring of stlsoft::proxy_ptr::get mutating/non-mutating overloads;
* refactoring of stlsoft::ref_ptr::get mutating/non-mutating overloads;
* refactoring of stlsoft::shared_ptr::get mutating/non-mutating overloads;
* refactoring of comstl::interface_ptr::get mutating/non-mutating overloads;
* platformstl/synch/tss_index.hpp now properly includes the tss_exception symbol into the platformstl namespace;
* bug fix to winstl::GetTimeFormat_msA/W, whereby 24hr format was always used, regardless of the locale settings;


## 1.9.15 - 24th December 2007

* minor bug fix for C compilation;
* previous versions of STLSoft defined STLSOFT_CF_EXCEPTION_SUPPORT and STLSOFT_CF_RTTI_SUPPORT for some compilers in C compilation, notably GCC. This was causing problems with the (soon-to-be-released) xTests and flecxx libraries, and is now fixed;


## 1.9.14 - 23rd December 2007

* updated stlsoft version (_STLSOFT_VER) missing in 1.9.13;


## 1.9.13 - 20th December 2007

* features enhancements to fixed array classes;
* stlsoft::fixed_array_?d::get_allocator() method for all 4 classes;
* stlsoft::fixed_array_?d::fixed_array_?d() overloads taking allocator;


## 1.9.12 - 19th December 2007

* features enhancements to fixed array classes;
* stlsoft::fixed_array_?d::data() (mutating form) methods for all 4 classes;
* stlsoft::fixed_array_?d::swap() methods for all 4 classes;
* fix to stlsoft::stl_collection_tag, to derive it from stlsoft::collection_tag;


## 1.9.11 - 17th December 2007

* minor modifications and bug-fixes;
* discrimination of RTTI support, in the form of the symbol STLSOFT_CF_RTTI_SUPPORT, which will be defined when support is enabled. This is required for the new xTests project (which will be released in January 2008);
* stlsoft::cmdargs class has significant breaking changes:;
* added has_option() method;
* added has_value() method;
* removed m_ from public fields of cmdargs::option class;
* removed m_ from public fields of cmdargs::value class;
* renamed m_value member of cmdargs::value to name;
* stlsoft::must_init has had numerous fixes;
* fixed bug, that manifests in widestring compilation, in stlsoft/filesystem/searchspec_sequence.hpp;


## 1.9.10 - 10th December 2007

* bug fix for recls (http://recls.org/);
* minor feature enhancements;
* basic_static_string::pop_back();
* fixed bug, that manifests in widestring compilation, in stlsoft/filesystem/searchspec_sequence.hpp;
* mfcstl/mfcstl.hpp now #includes atlstr.h if _MFC_VER >= 0x0700;
* platformstl::environment_variable_traits now works on Win32 when synthesising UNIX;


## 1.9.9 - 19th November 2007

* shim fixes in UNIXSTL;
* added all missing string access shims to unixstl/filesystem/current_directory_scope.hpp;
* added all missing string access shims to unixstl/filesystem/file_path_buffer.hpp;


## 1.9.8 - 18th November 2007

* compatibility with Borland C/C++ 5.82 (Turbo C++); now supports VOLE;
* comstl/collections/collection_sequence.hpp has a #define hack, to make retrievalQuanta a pre-processor replacement rather than a member constant, which avoids the erroneous compiler error with Borland C/C++ 5.82;
* comstl/collections/enumerator_sequence.hpp has a #define hack, to make retrievalQuanta a pre-processor replacement rather than a member constant, which avoids the erroneous compiler error with Borland C/C++ 5.82;
* winstl/filesystem/filesystem_traits.hpp - only uses truncation testing in 64-bit compilations;
* winstl/system/system_traits.hpp - only uses truncation testing in 64-bit compilations;


## 1.9.7 - 16th November 2007

* now supports x64 Windows 64-bit compilation (though it may not be perfect);
* now supports Borland Turbo C++ v5.82, though it is known not to be perfect STLSoft:;
* the POD algorithms - stlsoft/algorithms/pod.hpp - can now be forced to accept non-POD types. The symbols, and the algorithms they apply to, are: _STLSOFT_POD_COPY_ALLOW_NON_POD - stlsoft::pod_copy() _STLSOFT_POD_COPY_N_ALLOW_NON_POD - stlsoft::pod_copy_n() _STLSOFT_POD_MOVE_ALLOW_NON_POD - stlsoft::pod_move() _STLSOFT_POD_MOVE_N_ALLOW_NON_POD - stlsoft::pod_move_n() _STLSOFT_POD_FILL_N_ALLOW_NON_POD - stlsoft::pod_fill_n() This can be appropriate when, say, dealing with a struct that has some simple constructors;
* stlsoft::get_FILE_ptr shim UNIXSTL:;
* unixstl::memory_mapped_file now allows for specifying offset and request size. WinSTL:;
* winstl::to_DATE conversion shim, with overloads for DATE, UDATE, FILETIME, and SYSTEMTIME PlatformSTL:;
* platformstl::file_lines class - provides efficient representation of all the files in a text file; defaults to using string views for all the lines, so there's at most one copy operation from the memory-mapped file used to perform the initial load;


## 1.9.6 - 25th September 2007

* rbegin() and rend() for comstl::ccombstr_veneer;
* comstl::EXCEPINFO_free();
* rbegin() and rend() for comstl::bstr STLSoft;
* front() and back() for stlsoft::auto_buffer (but note: it's still *NOT* a container!);
* find() and count() for stlsoft::frequency_map WinSTL;
* winstl::memory_mapped_file now takes offset+range;
* unixstl::glob_sequence fix in is_valid() (fixes bug seen in Ubuntu 64-bit);


## 1.9.5 - 4th August 2007

* STLSOFT_CF_CDECL_SUPPORTED, in anticipation of changes to support 64-bit (x64) compilation;
* comstl::bstr::attach() method;
* comstl::bstr::bstr(C const* s, int len) - fixed bug whereby if len is less than the actual length of s, actual length is used;
* correction to signature of winstl::basic_reg_key:: template<...> create_key: H& param is now H const&;
* corrected pre-condition enforcements of winstl::system_traits::get_environment_variable winstl::system_traits::get_module_directory winstl::system_traits::get_module_filename winstl::system_traits::get_system_directory winstl::system_traits::get_windows_directory;


## 1.9.4 - 2nd August 2007

* detection of compiler support for __VA_ARGS__, via the STLSOFT_CF_SUPPORTS_VARIADIC_MACROS;


## 1.9.3 - 29th July 2007

* 3 and 4 parameter versions of stlsoft::all_of composite predicate creator functions;
* 3 and 4 parameter versions of stlsoft::any_of composite predicate creator functions;
* new shim: stlsoft::to_uint64 conversion shim;
* degenerate overload (uint64_t);
* WIN32_FIND_DATA overload;


## 1.9.2 - 2nd June 2007

* HICON2LRESULT type converter;
* LRESULT2HICON type converter;
* winstl::basic_reg_key::create_key() static method, to create a key;
* new shim: winstl::get_HKEY;
* bug fix to operator /=() for winstl::basic_path and unixstl::basic_path;


## 1.9.1, version released with Extended STL, volume 1 - 30th April 2007

* stlsoft/fixed_array.hpp: function call operator now implemented in terms of at_unchecked();
* comstl::bstr: bug fix in constructors taking C-string range, where range is larger than the string;
* rangelib/algorithms.hpp: bug fix in r_equal(), r_exists_if(), r_find_if();


## 1.9.1 beta 48 - 12th April 2007

* resource_type (and const_resource_type, for some) member type for: stlsoft::ptr_proxy stlsoft::ref_ptr stlsoft::shared_ptr comstl::bstr comstl::guid inetstl::connection inetstl::session unixstl::process_mutex unixstl::semaphore unixstl::thread_mutex winstl::module winstl::reg_key winstl::reg_key_sequence winstl::reg_value_sequence winstl::event winstl::process_mutex winstl::semaphore;
* added operator () to fixed arrays (stlsoft/container/fixed_array.hpp) (as requested/persuaded by Neal Becker);
* fixed bug in rangelib::r_exists() (Thanks to Yakov Markovitch);


## 1.9.1 beta 47 - 6th April 2007

* stlsoft::any_of() and stlsoft::all_of() composite predicate creator functions;
* binary forms of stlsoft::ptr_fun and stlsoft::ptr_fun_void;
* element_type and resource_type member types for stlsoft::ref_ptr;
* atlstl::generic_automation_collection now supports Count property;
* comstl::com_SUCCEEDED and comstl::com_S_OK predicate function adaptors (comstl/functional/com_predicate_adaptors.hpp);
* comstl::bstr now has additional members:;
* ctor: bstr(bstr const& rhs, size_type pos, size_type len);
* assign(const_iterator from, const_iterator to);
* detach();
* append() overloads, and operator +=() overloads;
* subscript operator;
* begin()/end() methods;
* acestl::custom_event_handler::has_custom_event(long) renamed to acestl::custom_event_handler::has_custom_events(long). The old name is retained for backwards compatibility, but is deprecated;
* comstl::variant::QueryInterfaceValue() fixed;
* inetstl::basic_findfile_sequence bug with VC++ 8 now fixed;
* winstl::basic_findfile_sequence bug with VC++ 8 now fixed;
* winstl::basic_findvolume_sequence bug with VC++ 8 now fixed;


## 1.9.1 beta 46 - 13th March 2007

* wholesale lexical changes (e.g. "char const *x" => "char const* x");


## 1.9.1 beta 45 - 12th March 2007

* comstl::collection_sequence:;
* const_iterator and const_pointer member types;
* comstl::enumerator_sequence:;
* comstl::variant:;
* constructor taking a variant and a VARTYPE to which to change on copy;
* unixstl::basic_path:;
* empty();
* has_sep();
* winstl::basic_path:;
* winstl::basic_findfile_sequence:;
* relativePath flag, which causes entries to have a relative path;
* platformstl::readdir_sequence:;
* fixed element reference category (is By-Value Temporary);
* correctly returns entry full path only if fullPath flag is specified, rather than (absolutePath | fullPath);
* winstl::reg_key:;
* can now copy an empty instance (previously threw an exception);
* winstl::reg_value:;


## 1.9.1 beta 44 - 22nd February 2007

* distribution is now rooted under stlsoft-X.Y, e.g. stlsoft-1.9.1-beta44;


## 1.9.1 beta 43 - 22nd January 2007

* comstl::co_create_instance() overloads now have a third, defaulted, member, for creation context. This is required for the new VOLE project, which will be released tomorrow;
* mfcstl::CArray_cadaptor and mfcstl::CArray_iadaptor now support <, <=, >, and >= comparison, in addition to ==, !=;
* string access shims for UDATE;
* winstl::to_FILETIME support for DATE and UDATE;
* winstl::to_SYSTEMTIME support for DATE and UDATE;
* stlsoft::get_ptr overload for std::auto_ptr slightly modified;
* winstl/shims/access/string.hpp now includes winstl/shims/access/string/time.hpp;


## 1.9.1 beta 42 - 15th January 2007

* refactored atomic integer support on UNIX:;
* Now only supports if for Mac OS-X, Win32 (when emulated, of course), and if UNIXSTL_FORCE_ATOMIC_INTEGER_OPERATIONS is defined, allowing the user to decide for themselves whether or not to use (non-portable) facilities such as asm/atomic.h;
* unixstl/synch/util/features.h;


## 1.9.1 beta 41 - 14th January 2007

* refactored sized-integer detection:;
* The symbols STLSOFT_CF_8BIT_INT_EXTENDED_TYPE_IS_DISTINCT STLSOFT_CF_16BIT_INT_EXTENDED_TYPE_IS_DISTINCT STLSOFT_CF_32BIT_INT_EXTENDED_TYPE_IS_DISTINCT are removed. Instead use STLSOFT_CF_CHAR_DISTINCT_INT_TYPE STLSOFT_CF_SHORT_DISTINCT_INT_TYPE STLSOFT_CF_INT_DISTINCT_INT_TYPE;
* The symbols STLSOFT_CF_INT_DISTINCT_TYPE STLSOFT_CF_LONG_DISTINCT_TYPE are deprecated. Instead use STLSOFT_CF_INT_DISTINCT_INT_TYPE STLSOFT_CF_LONG_DISTINCT_INT_TYPE;
* The following symbols are added (and propagated through the codebase): STLSOFT_CF_CHAR_DISTINCT_INT_TYPE STLSOFT_CF_SHORT_DISTINCT_INT_TYPE STLSOFT_CF_INT_DISTINCT_INT_TYPE STLSOFT_CF_LONG_DISTINCT_INT_TYPE STLSOFT_CF_LONG_LONG_DISTINCT_INT_TYPE;
* A few last workarounds to ensure complete build/run of the unit-tests with DMC++;
* C compilation included in Unit-test builds;
* ensuring that all .h files are C-compilation compatible;
* stlsoft::limit_traits<bool> specialisation;
* stlsoft::sign_traits<long> and <unsigned long> specialisations;
* winstl::get_kernel_handle attribute shim overloads for winstl::event, winstl::process_mutex and winstl::semaphore;
* winstl::get_kernel_handle attribute shim overload for MFC types (in mfcstl/shims/attribute/get_kernel_handle.hpp);
* winstl/time/format_functions.h => winstl/time/format_functions.hpp;
* removed (almost) all of the previously deprecated __STLSOFT* symbols, __STLSOFT_COMPILER_IS_BORLAND __STLSOFT_COMPILER_IS_COMO __STLSOFT_COMPILER_IS_DMC __STLSOFT_COMPILER_IS_INTEL __STLSOFT_COMPILER_IS_GCC __STLSOFT_COMPILER_IS_MSVC __STLSOFT_COMPILER_IS_MWERKS __STLSOFT_COMPILER_IS_VECTORC __STLSOFT_COMPILER_IS_WATCOM __STLSOFT_COMPILER_IS_UNKNOWN __STLSOFT_COMPILER_LABEL_STRING __STLSOFT_COMPILER_VERSION_STRING __STLSOFT_DOCUMENTATION_SKIP_SECTION __STLSOFT_CF_STATIC_ASSERT_SUPPORT __STLSOFT_CF_EXCEPTION_SUPPORT __STLSOFT_CF_FUNCTION_SIGNATURE_FULL_ARG_QUALIFICATION_REQUIRED __STLSOFT_CF_NAMESPACE_SUPPORT __STLSOFT_CF_TEMPLATE_SUPPORT __STLSOFT_CF_EXCEPTION_SIGNATURE_SUPPORT __STLSOFT_CF_THROW_BAD_ALLOC __STLSOFT_CF_NOTHROW_BAD_ALLOC __STLSOFT_CF_TEMPLATE_CLASS_DEFAULT_FUNDAMENTAL_ARGUMENT_SUPPORT __STLSOFT_CF_TEMPLATE_CLASS_DEFAULT_CLASS_ARGUMENT_SUPPORT __STLSOFT_CF_MEMBER_TEMPLATE_FUNCTION_SUPPORT __STLSOFT_CF_MEMBER_TEMPLATE_CTOR_SUPPORT __STLSOFT_CF_MEMBER_TEMPLATE_RANGE_METHOD_SUPPORT __STLSOFT_CF_MEMBER_TEMPLATE_CLASS_SUPPORT __STLSOFT_CF_TEMPLATE_SPECIALISATION_SYNTAX __STLSOFT_CF_TEMPLATE_PARTIAL_SPECIALISATION_SUPPORT __STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT __STLSOFT_CF_std_NAMESPACE __STLSOFT_CF_std_char_traits_AVAILABLE __STLSOFT_CF_ALLOCATOR_ALLOCATE_HAS_HINT __STLSOFT_CF_ALLOCATOR_DEALLOCATE_HAS_OBJECTCOUNT __STLSOFT_CF_BIDIRECTIONAL_ITERATOR_SUPPORT __STLSOFT_CF_EXPLICIT_KEYWORD_SUPPORT __STLSOFT_CF_MUTABLE_KEYWORD_SUPPORT __STLSOFT_CF_TYPENAME_PARAM_KEYWORD_SUPPORT __STLSOFT_CF_TYPENAME_TYPE_KEYWORD_SUPPORT __STLSOFT_CF_TYPENAME_TYPE_DEF_KEYWORD_SUPPORT __STLSOFT_CF_TYPENAME_TYPE_MIL_KEYWORD_SUPPORT __STLSOFT_CF_MOVE_CONSTRUCTOR_SUPPORT __STLSOFT_CF_KOENIG_LOOKUP_SUPPORT __STLSOFT_CF_TEMPLATE_TEMPLATE_SUPPORT __STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT __STLSOFT_CF_VENEER_SUPPORT __STLSOFT_CF_TEMPLATE_SHIMS_NOT_SUPPORTED __STLSOFT_CF_NEGATIVE_MODULUS_POSITIVE_GIVES_NEGATIVE_RESULT;


## 1.9.1 beta 40 - 6th January 2007

* stlsoft::format_thousands() grouping function template, e.g. char result[101]; stlsoft::format_thousands(result, STLSOFT_NUM_ELEMENTS(result), "2;3", 987654321); assert(0 == ::strcmp(result, "9876,54,321"));
* stlsoft::truncation_test() function suite; this is necessary to support the new VOLE library (see http://vole.sourceforge.net/);
* stlsoft::truncation_cast() cast function template (implemented in terms of stlsoft::truncation_test());
* all sub-project namespace-specific size_t and ptrdiff_t references are removed. This fixes conflicts when using using directives (though that's never recommended for application code);
* stlsoft::must_init now has all built-in operators overloaded, e.g. you stlsoft::must_init<int> i(10); i = i + 10;
* all remaining in-header unit-test blocks are removed into separate headers;


## 1.9.1 beta 39 - 5th January 2007

* oaidl interfaces to comstl/internal/interface_traits_std.hpp;
* stream inserter for comstl::bstr;
* fix to winstl/system/console_functions.h to ensure C compatibility;
* fix to winstl/time/format_functions.h to fix bug with 24-hr time picture elements (HH);


## 1.9.1 beta 38 - 3rd January 2007

* stlsoft/filesystem/io_functions.hpp, which defines the function template read_line, used to read a line of text from a FILE* stream, e.g. FILE *stm = . . .; std::string str; while (stlsoft::read_line(stm, str)) { ::fprintf(stdout, "line: %.*s\n", int(str.size()), str.data()); };
* stlsoft::ptr_ifun() indirection function pointer adaptor creator functions - used with std::for_each if you are storing a sequence of X but your function acts on X*, e.g. class X; void modX(X *); std::vector<X> vecx; std::for_each(vecx.begin(), vecx.end(), stlsoft::ptr_ifun(modX));
* reinstatement of the "remove from scope" technique, in the guise of the STLSOFT_REMOVE_FROM_SCOPE(name) macro, which removes a name from the current scope (and any enclosed scopes). Defined in stlsoft/util/remove_from_scope.hpp;
* added winstl::listview_sequence_item::state();
* stlsoft/function_adaptors/ref2ptr.hpp => stlsoft/functional/indirect_function_adaptors.hpp;
* winstl/clipboard/exceptions.hpp => winstl/clipboard/error/exceptions.hpp;
* 360+ other files are modified in comments only - for auto-documentation purposes only;
* stlsoft::error_desc now works with stream inserters with all compilers;
* stlsoft::ref2ptr() indirection function pointer adaptor creator functions are deprecated, in favour of stlsoft::ptr_ifun() creator functions;
* comstl::errorinfo_desc now works with stream inserters with all compilers;
* fixed compilation problem with unixstl/dl/dl_call.hpp with GCC 4.x;


## 1.9.1 beta 37 - 30th December 2006

* stlsoft::equal_handle function class - this is dead and gone;
* stlsoft/container_veneers.hpp - this is obsolete; it points to correct #include;
* stlsoft/handle_access.hpp - this is dead and gone;
* stlsoft/skip_iterator.hpp - this is going into research section; maybe 1.10;
* mfcstl/cstring_veneer.hpp - this is obsolete; it points to correct #include;
* winstl/handle_access.hpp - this is dead and gone;
* winstl/windows.hpp - this is going into a research section; maybe 1.10;
* fixed bug in stlsoft::scoped_handle<void>::detach();
* stlsoft/container_access.hpp => stlsoft/collections/functions.hpp;
* stlsoft/c_str_ptr_inserter.hpp => stlsoft/iterators/c_str_inserter.hpp;
* stlsoft/iterator.hpp => stlsoft/util/std/iterator_helper.hpp;
* stlsoft/ptr_proxy.hpp => stlsoft/smartptr/ptr_proxy.hpp;
* stlsoft/unary_function_output_iterator_adaptor.hpp => stlsoft/iterators/unary_function_output_iterator_adaptor.hpp;
* stlsoft/unittest.hpp => unittest/unittest.hpp;
* stlsoft/collections/collections.hpp renamed to stlsoft/collections/util/collections.hpp;
* stlsoft/functional/access_predicates.hpp renamed to stlsoft/functional/equal_ptr.hpp;
* winstl/functions.h => winstl/obsolete/functions.h;
* winstl/winstl_int_to_string.h => winstl/conversion/int_to_string.hpp;
* winstl::get_console_window() moved from winstl/functions.h => winstl/system/console_functions.h;
* winstl/registry/defs.hpp => winstl/registry/util/defs.hpp;
* winstl/registry/exceptions.hpp => winstl/registry/error/exceptions.hpp;
* winstl/registry/shared_handles.hpp => winstl/registry/util/shared_handles.hpp;


## 1.9.1 beta 36 - 28th December 2006

* unittest cases for unixstl::memory_mapped_file WinSTL;
* winstl::memory_mapped_file can now be constructed from a wide string, in addition to a multibyte string. It can also be constructed from any type for which the stlsoft::c_str_ptr string access shim returns a wide string, in addition to any type for which the stlsoft::c_str_ptr string access shim returns a multibyte string;
* unittest cases for winstl::memory_mapped_file;


## 1.9.1 beta 35 - 27th December 2006

* stlsoft::do_initialisation_never array initialisation policy, which stipulates that no initialisation whatsoever be performed on array elements;
* stlsoft::scoped_handle now supports indirect cleanup functions. In other words, if you have a handle type handle_t, you can pass either a cleanup function taking handle_t - e.g. handle_close(handle_t ); - or a cleanup function taking a pointer to handle_t - e.g. handle_close_set_null(handle_t *);
* replacement of all stlsoft::throw_x() with STLSOFT_THROW_X() STLSoft;
* stlsoft::fixed_array_1d/2d/3d/4d classes now capable of doing *no* initialisation of their elements, by specifying the new policy stlsoft::do_initialisation_never;
* stlsoft::static_array_1d/2d/3d/4d classes now capable of doing *no* initialisation of their elements, by specifying the new policy stlsoft::do_initialisation_never UNIXSTL;
* refactoring of #includes in unixstl/synch/thread_mutex.hpp;


## 1.9.1 beta 34 - 24th December 2006

* replacement of all per-component exception throwing mechanisms with stlsoft::throw_x() utility function STLSoft;
* deprecation of stlsoft::cwd_stack::is_empty() method;
* removal of stlsoft::is_empty logical shim for stlsoft::searchspec_sequence ACESTL;
* corrected bug in acestl::message_queue_sequence::empty();
* corrections to stlsoft::is_empty logical shim for ACE_Message_Queue ATLSTL;
* corrections to #includes in atlstl/window/window.hpp COMSTL;
* deprecation of stlsoft::is_empty logical shim for interface casts;
* deprecation of stlsoft::is_empty logical shim for comstl::interface_ptr InetSTL;
* removal of stlsoft::is_empty logical shim for inetstl::basic_findfile_sequence;
* removal of stlsoft::is_empty logical shim for inetstl::searchspec_sequence WinSTL;
* deprecation of stlsoft::is_empty logical shim for winstl::basic_findfile_sequence;
* deprecation of stlsoft::is_empty logical shim for winstl::basic_findvolume_sequence;
* stlsoft::is_empty logical shim overloads for ACE_String_Base MFCSTL;
* stlsoft::is_empty logical shim overloads for MFC array containers;
* stlsoft::is_empty logical shim overloads for MFC list containers;
* stlsoft::is_empty logical shim overloads for MFC CString STLSoft;
* stlsoft::cwd_stack::empty() method;
* stlsoft::get_ptr attribute shim overloads for stlsoft::ptr_proxy;
* stlsoft::conversion_error exception class;
* stlsoft::wide2multibyte and stlsoft::multibyte2wide now throw an instance of stlsoft::conversion_error exception if the conversion fails (when exception handling support is on);
* stlsoft::is_empty logical shim overload for standard containers WinSTL;
* winstl::conversion_error exception class;
* winstl::wide2multibyte and winstl::multibyte2wide now throw an instance of winstl::conversion_error exception if the conversion fails (when exception handling support is on);
* winstl::to_FILETIME conversion shim;
* winstl::to_SYSTEMTIME conversion shim;


## 1.9.1 beta 33 - 13th December 2006

* all comstl__??? functions are no longer in the comstl namespace (when in C++ compilation); their non comstl__-prefixed equivalents remain in the comstl namespace. For example, the full name of the comstl::comstl__set_error_info_description_w() function is now comstl__set_error_info_description_w() whether in C or C++; the name of comstl::set_error_info_description_w() remains as it was;
* comstl::IDispatchImpl4;
* comstl::try_interface_cast;


## 1.9.1 beta 32 - 6th December 2006

* fixed unixstl/unixstl.h (in)compatibility with C compilation;
* fixed platformstl/platformstl.h (in)compatibility with C compilation;


## 1.9.1 beta 31 - 6th December 2006

* comstl/interface/bad_interface_cast.hpp -> comstl/error/bad_interface_cast.hpp;
* comstl/interface/interface_cast.hpp -> comstl/conversion/interface_cast.hpp;
* comstl/interface/interface_traits.hpp -> comstl/util/interface_traits.hpp;
* comstl::interface_ptr is now deprecated, in favour of stlsoft::ref_ptr;
* comstl::co_create_instance() overloads now also take (a reference to) an instance of stlsof::ref_ptr<I>;
* comstl::interface_cast<>() function templates that cast between instances of the stlsoft::ref_ptr<> "smart pointer" wrappers;
* stlsoft::ref_ptr now takes a third (defaulted) template parameter, which defines the (intermediate) up-cast type when converting from concrete type to interface type;
* stlsoft::ref_ptr::set() method, to facilitate modification of an already constructed instance. (Previously the user was obliged to assign from a temporary instance.);
* winstl::get_kernel_handle shim (winstl/shims/attribute/get_kernel_handle.hpp);
* winstl::get_synch_handle shim (winstl/shims/attribute/get_synch_handle.hpp);
* winstl::event's member type handle_type renamed to synch_handle_type;
* winstl::process_mutex's member type handle_type renamed to synch_handle_type;
* winstl::semaphore's member type handle_type renamed to synch_handle_type;
* winstl/synch/functions.hpp -> winstl/synch/wait_functions.hpp;
* winstl::WaitForMultipleObjects() function suite renamed winstl::wait_for_multiple_objects(), and now implemented in terms of new winstl::get_synch_handle shim;


## 1.9.1 beta 30 - 2nd December 2006

* UNIXSTL components spin_mutex and the atomic_???() function suite are now compatible with both architectures (PPC + Intel) on MAC OSX;


## 1.9.1 beta 29 - 27th November 2006

* atlstl::Window class - a string access shim-aware enhancement to ATLs' Window class;
* COMSTL value policies throw exceptions if fail to copy;
* UNIXSTL and WinSTL spin_mutex is made into a template, and takes a policy that determines whether it yields on the spin. Use spin_mutex_yield for yielding, spin_mutex_no_yield for no yielding. spin_mutex is now a typedef for spin_mutex_no_yield. The old behaviour can be obtained by #define-ing the symbol STLSOFT_OLD_SPIN_MUTEX_BEHAVIOUR, in which case spin_mutex is a typedef for spin_mutex_yield;
* WinSTL's pid_sequence and process_module_sequence classes have been rendered slightly more efficient;


## 1.9.1 beta 28 - 29th October 2006

* stlsoft::a2w() and stlsoft::w2a() char conversion functions (functionally the same as the WinSTL ones);
* fixed bug in winstl/shims/access/string/time.hpp that breaks Pantheios in UNICODE builds;


## 1.9.1 beta 27 - 22nd October 2006

* stlsoft::trip_bool class template;
* stlsoft/functional/function_adaptors.hpp does not include stlsoft/functional/method_adaptors.hpp for GCC < 3.3;
* minor general changes in makefile structure;
* fixed for UNIX makefiles;


## 1.9.1 beta 26 - 21st October 2006

* stlsoft::scoped_handle<void> specialisation for scoping APIs with 0 params;
* string access shims (in InetSTL) for struct in_addr;
* VC5 compatibility in ~50 files. (You may find it strange that VC5 compat is even an issue, but we have some older products that require VC5 compilation, and we want to put Pantheios into it. So, STLSoft has to be made to work with it ...);
* fix to stlsoft::integer_to_string() overloads to handle (unsigned) long in addition to all the others;


## 1.9.1 beta 25 - 5th October 2006

* fixed #include omission stlsoft/conversion/byte_format_functions.hpp;
* fixed method omissions in stlsoft::special_string_instance_1;
* fixed bug in comstl::IDispatchImpl3::Invoke();
* winstl/util/struct_initialisers.hpp now handles case where WIN32_LEAN_AND_MEAN may have been defined;


## 1.9.1 beta 24 - 24th September 2006

* stlsoft::basic_shim_string::internal_size();
* unixstl::process_mutex now allows for wrapping of an externally created pthread_mutex_t*;
* unixstl::thread_mutex now allows for wrapping of an externally created pthread_mutex_t*;
* fix minor bug in stlsoft::c_str_data_a(struct tm const *t) (located in stlsoft/shims/access/string/std/time.hpp) that resulted in heap allocation every time;
* fixed bug that prevented C-only compilation of platformstl/platformstl.h;
* unixstl/synch/atomic_functions.h now contains various feature detection symbols, e.g. UNIXSTL_HAS_ATOMIC_PREINCREMENT, UNIXSTL_HAS_ATOMIC_PREADD;
* tidying up of exception-safety in unixstl::process_mutex;
* introduction of exception throwing in unixstl::thread_mutex, to be conformant with unixstl::process_mutex;
* unixstl::spin_mutex now discriminates on the (new) symbol UNIXSTL_HAS_ATOMIC_WRITE;
* platformstl/synch/atomic_functions.h now contains various feature detection symbols, e.g. PLATFORMSTL_HAS_ATOMIC_PREINCREMENT, PLATFORMSTL_HAS_ATOMIC_PREADD;


## 1.9.1 beta 23 - 17th September 2006

* mfcstl/collections/clist_adaptors.hpp: mfcstl::CList_iadaptor replaces the old mfcstl::list_adaptor class template;
* a whole load more directory changes. Very few now remain, and 1.9.1 proper is very close;


## 1.9.1 beta 22 - 13th September 2006

* the following files were "moved" into stlsoft/util: options_verifier.hpp printf_traits.hpp true_typedef.hpp argument_proxies.hpp compiler_optimisation_traits.hpp constraints.hpp limit_traits.h sign_traits.hpp size_traits.hpp static_initialisers.hpp;
* the following files were "moved" into stlsoft/obsolete: first_class_promoter.hpp explicit_inheritance_veneer.hpp;
* fix of version numbers in stlsoft/stlsoft.h;


## 1.9.1 beta 21 - 7th September 2006

* fix bug in stlsoft::member_selector_iterator (which crops up when compiling Pantheios with Visual C++ 8);


## 1.9.1 beta 20 - 2nd September 2006

* comstl::bstr (comstl/string/bstr.hpp) - facade for BSTR;
* comstl::variant (comstl/util/variant.hpp) - facade for VARIANT;
* comstl::bstr_compare();
* new overloads of comstl::co_create_instance(), which takes a string, and attempts to resolve it with CLSIDFromProgID(), or CLSIDFromString();
* winstl::reg_get_dword_value() - retrieves a DWORD value from a reg key;


## 1.9.1 beta 19 - 9th August 2006

* dotnetstl::check_cast custom cast function template (dotnetstl/conversion/check_cast.hpp);


## 1.9.1 beta 18 - 7th August 2006

* stlsoft/string/special_string_instance.hpp: string access shims for stlsoft::special_string_instance_1 class template are now defined;
* atlstl/automation/automation_collections.hpp: atlstl::generic_automation_collection (and atlstl::generic_collection_base) now both can accept a template param for the (dual) interface from which they inherit - they used to inherit from IDispatch;


## 1.9.1 beta 17 - 5th August 2006

* winstl/controls/dialog_functions.hpp: winstl::dialog_button_id_check unary function class;
* The method form of atlstl::get_MemberValue() now is a bit more flexible, in that the returned type and the method return value may be different (but must still be compatible);
* rangelib::integral_range now accepts [from,to) where to < from, and swaps the increment (if +ve) accordingly;
* big changes to winstl/util/struct_initialisers, which now cater to a large number of the Win32 API structures. (More to be added later, once I've written a Ruby script to do the rest automatically.);
* winstl::load_text_file() now throws an exception if the file cannot be opened;


## 1.9.1 beta 16 - 25th July 2006

* stlsoft::byte_format() - powerful binary=>text formatting function;
* winstl::console_colour_scope - scoping class for Win32 console soon to be released; http://pantheios.org/);
* acestl::message_queue_sequence uses optimised scatter/slice IO technique described in "Extended STL, volume 1" (to be published at the end of the year, or early 2007), for faster processing of block copy operations;


## 1.9.1 beta 15 - 18th July 2006

* More directory changes, particularly for the Template Meta-programming library;
* New container class: platformstl::cwd_stack - which is used to store current working directory checkpoints (via push(), and restore them via pop() - future enhancements to internals are planned, but interface likely to remain unchanged;
* A whole host of algorithms that've been hiding in the research branch for over a year are now brought into the main trunk, under include/stlsoft/algorithms/..;


## 1.9.1 beta 14 - 15th July 2006

* More directory refactoring, particularly for the string access shims, <project>/shims/access/string.hpp;
* Function/method pointer adaptors now cope with void/non-void return, const/non-const methods, and cdecl/fastcall/stdcall calling conventions Note: Please make sure that you delete directory include/stlsoft/typefixer;


## 1.9.1 beta 13 - 12th July 2006

* A massive amount of refactoring of the string access shims and their documentation;
* unixstl::module / winstl::module get_handle() method removed, replaced with get_module_handle();
* unixstl::process_mutex now throws exceptions (when compiled with exception-handling on) if any of the PThreads methods fail;


## 1.9.1 beta 12 - 8th July 2006

* stlsoft::special_string_instance, which supports the "Special String Instance" pattern (see online docs for expl);
* unixstl::current_directory, winstl::current_directory, winstl::absolute_path, winstl::module_directory, winstl::module_filename, winstl::system_directory, winstl::windows_directory, are no longer separate classes, but rather specialisations (with different policies, as appropriate) of stlsoft::special_string_instance;
* stlsoft::is_same_type now works correctly in all circumstances with Borland, thanks to some work by Pablo Aguilar;
* unixstl::system_traits (unixstl/system/system_traits.hpp), containing non file-system related elements previously in unixstl::filesystem_traits;
* winstl::system_traits (winstl/system/system_traits.hpp), containing non file-system related elements previously in winstl::filesystem_traits;
* unixstl::filesystem_traits (unixstl/filesystem/filesystem_traits.hpp) now derives from unixstl::system_traits;
* winstl::filesystem_traits (winstl/filesystem/filesystem_traits.hpp) now derives from winstl::system_traits;
* lots and lots more directory re-arrangements, and addition of "better" documentation (to be seen currently at http://stlsoft.org/doc-1.9);


## 1.9.1 beta 11 - 25th June 2006

* no changes;


## 1.9.1 beta 10 - 18th June 2006

* stlsoft/string/copy_functions.hpp;
* atlstl::SupportErrorInfoImpl5 class template;
* platformstl/path_functions.hpp;
* unixstl/path_functions.hpp;
* winstl/path_functions.hpp;
* platformstl/sleep_functions.h;
* unixstl/sleep_functions.h;
* winstl/sleep_functions.h;
* unixstl::basic_file_path_buffer::copy() method;
* winstl::basic_file_path_buffer::copy() method;
* unixstl::filesystem_traits methods: str_pbrk(), str_end(), is_root_designator(), and various feature adjustments;
* unixstl::basic_path methods: clear(), operator [], copy();
* winstl::basic_path methods: clear(), operator [], copy();
* winstl::basic_findfile_sequence: new flags skipHiddenFiles and skipHiddenDirs;
* atlstl/string_access.hpp - bug fix in shim using declarations;
* stlsoft/system/commandline_parser.hpp - minor bug fix;


## 1.9.1 beta 9 - 11th June 2006

* no changes;


## 1.9.1 beta 8 - 7th June 2006

* no changes;


## 1.9.1 beta 7 - 1st June 2006

* no changes;


## 1.9.1 beta 6 - 28th May 2006

* atlstl::IDispatch2 and atlstl::IDispatch3 class templates (atlstl/multiple_dispatch.hpp);
* atlstl::get_ConstantValue() (atlstl/property_method_helpers.hpp);
* comstl::set_error_info() overloads;
* unixstl::dl_call() now can work with arbitrary types (by specialising unixstl::is_valid_dl_call_arg;
* winstl::dl_call() now can work with arbitrary types (by specialising winstl::is_valid_dl_call_arg;
* winstl::basic_path::pop_ext();
* WinSTL Control Panel library:;
* winstl/control_panel/functions.h;
* winstl/control_panel/exceptions.hpp;
* winstl/control_panel/applet_module.hpp;
* winstl::applet_module;
* winstl::applet;
* WinSTL ToolHelp library (written by Pablo Aguilar):;
* winstl::heap_sequence (winstl/toolhelp/heap_sequence.hpp);
* winstl::module_sequence (winstl/toolhelp/module_sequence.hpp);
* winstl::process_sequence (winstl/toolhelp/process_sequence.hpp);
* winstl::thread_sequence (winstl/toolhelp/thread_sequence.hpp);
* winstl::module::get();
* winstl::basic_reg_key_sequence::get();
* winstl::basic_reg_value_sequence::get();
* more shims for stlsoft::basic_simple_string;
* more shims for stlsoft/time_string_access.hpp;
* stlsoft::string_concatenator_iterator now works with Borland;


## 1.9.1 beta 5 - 28th March 2006

* a heap of memory-related components now reside in /memory/ sub-directory, e.g. comstl/task_allocator.hpp => comstl/memory/task_allocator.hpp;
* same goes for many exceptions, e.g. stlsoft/contract_violation.hpp => stlsoft/exceptions/contract_violation.hpp;
* same goes for some containers, e.g. stlsoft/frequency_map.hpp => stlsoft/containers/frequency_map.hpp;
* same goes for WinSTL Registry library, which now resides in winstl/registry, e.g. winstl/registry/reg_key_sequence.hpp;
* stlsoft::ref2ptr generator function for function object classes that translate a reference into a pointer;
* a lot more function object classes and utilities will be incorporated when writing of the second volume of Extended STL commences in earnest;
* stlsoft::contiguous_diluter_iterator (stlsoft/iterators/contiguous_diluter_iterator.hpp) - "de-refines" iterators;
* stlsoft::null_output_iterator (stlsoft/iterators/null_output_iterator.hpp) - exactly what it says on the tin. ;-);
* stlsoft::unsorted_map (stlsoft/containers/unsorted_map.hpp) - a map that preserves the order of insertion;
* atlstl/automation_collections.hpp - COM collection helper classes. Still a bit of a work in progress;
* atlstl/enumerators.hpp - one of the useful Synesis enumerator templates moved over. There'll be more to come on this one;
* atlstl/property_method_helpers.hpp - more helpers, for getting prop value from result of a method call on self, or member;
* atlstl/support_error_info.hpp - new SupportErrorInfoImpl4 class template;
* comstl/acyclic_connector.hpp - comstl::acyclic_connector class template for allowing communication between two COM objects while avoiding a ref-count cycle;
* comstl/interface_function.h - useful functions brought over from Synesis COM libs;
* winstl::netapi_allocator (winstl/memory/netapi_allocator.hpp) - an allocator that wraps the Windows Network Buffer API;
* stlsoft/ref_ptr.hpp - an important fix that facilitates more safe heterogeneous assignment;
* winstl::event - no throws if event cannot be created (unless not compiling with exception-handling on);
* WinSTL Registry library has had a major reworking;


## 1.9.1 beta 4 - 31st January 2006

* stlsoft::charset_tokeniser (stlsoft/charset_tokeniser.hpp) - a "refinement" of stlsoft::string_tokeniser, making it easy to tokenise using charsets (a la strtok()) without the mess of using custom comparators with string_tokeniser (which can be something of a drag);
* comstl::cloneable_cloning_policy (comstl/enumeration_policies.hpp) - a policy that enables comstl::enumerator_sequence to be used with enumerators that may, or may not, be cloneable;
* winstl::listbox_const_iterator (winstl/listbox_const_iterator.hpp) - an iterator class that is used in the refactored versions of winstl::listbox_sequence and winstl::combobox_sequence;
* winstl::shell_delete() function suite;
* stlsoft/tokeniser_functions.hpp => stlsoft/tokenising/tokeniser_functions.hpp;
* stlsoft::string_tokeniser (stlsoft/string_tokeniser.hpp);
* now uses c_str_data() and c_str_len() shims, rather than c_str_ptr();
* new skip_blank_tokens, that supercedes string_tokeniser_ignore_blanks;
* string_tokeniser_ignore_blanks deprecated;
* lots of general tidying up;
* comstl::enumerator_sequence now properly handles enumerators that may or may not be cloneable, by deferring a Clone() until the second time the sequence needs to be enumerated;
* inetstl::basic_findfile_sequence - moved exception policy to third template parameter, rather than second;
* winstl/listbox_sequence.hpp => winstl/controls/listbox_sequence.hpp;
* winstl/combobox_sequence.hpp => winstl/controls/combobox_sequence.hpp;
* winstl/shell_browse.hpp => winstl/shell/browse_for_folder.hpp. winstl::shell_browse() => winstl::browse_for_folder();
* comstl::degenerate_cloning_policy;


## 1.9.1 beta 3 - 20th January 2006

* stlsoft/collections.hpp: contains new collection concept tags;
* stlsoft::external_iterator_invalidation (stlsoft/exceptions/external_iterator_invalidation.hpp): new exception class for representing iterator interruption by external agents;
* stlsoft::iteration_interruption (stlsoft/exceptions/iteration_interruption.hpp): a new exception class that acts as the base for iterator interruption;
* stlsoft::adapted_iterator_traits (stlsoft/adapted_iterator_traits.hpp): an omniscient iterator adaptor class that can detect iterator category, mutability, and element reference category (a new concept that is introduced in "Extended STL");
* stlsoft::filter_iterator (stlsoft/filter_iterator.hpp): an iterator adaptor class that can be used to filter out elements based on a predicate;
* stlsoft/transform_filter_iterator.hpp and stlsoft/filter_transform_iterator.hpp: contains creator functions for mixing filter_iterator and transform_iterator iterator adaptors;
* several new components for detecting standard library features, and assisting stlsoft\util\std\dinkumware_iterator_traits.hpp stlsoft\util\std\iterator_category_limiters.hpp stlsoft\util\std\stdio_overload_detectors.hpp;
* inetstl::basic_ftpdir_sequence (inetstl/ftpdir_sequence.hpp): a new collection class that provides a vector-like interface over the contents of an FTP server directory; implemented in terms of inetstl::basic_findfile_sequence;
* mfcstl::CString_cadaptor and mfcstl::CString_iadaptor (mfcstl/cstring_adaptors.hpp): class and instance adaptors for CString, dragging it kicking and screaming into conformance with std::basic_string;
* rangelib::range_exception and rangelib::empty_range_exception (rangelib/exceptions.hpp): new exception classes used by RangeLib components;
* rangelib::filter_sequence (rangelib/filtered_sequence.hpp): a new creator function that returns an instance of range_lib::filtered_range specialised with a rangelib::sequence_range applied to the given STL sequence;
* rangelib::iterator_range (rangelib/iterator_range.hpp): a new class that adapts a pair of iterators to the Range concept;
* winstl::child_window_sequence (winstl/child_window_sequence.hpp): a new class that presents an STL collection over the set of child windows of a given window;
* stlsoft::auto_buffer has the 2nd and 3rd template parameters reversed. The internal array size parameter is now 2nd, and the allocator parameter is now 3rd. All STLSoft components are updated accordingly. Backwards compatibility is provided in the form of stlsoft::auto_buffer_old;
* stlsoft::proxy_ptr is renamed to stlsoft::ptr_proxy. The old form is available for backwards compatibility;
* winstl::window_peer_sequence is now implemented in terms of new zorder_sequence_base, as discussed in the chapter "Travelling Back and Forth on the Z-Plane" from "Extended STL";
* mfcstl::cstring_veneer (mfcstl_cstring_veneer.h) is now deprecated, in favour of the new mfcstl::CString_cadaptor;
* stlsoft/filter_iterator.hpp => stlsoft/iterators/filter_iterator.hpp;
* stlsoft/member_traits.hpp => stlsoft/meta/member_traits.hpp;
* stlsoft/type_traits.hpp => stlsoft/meta/base_type_traits.hpp;
* stlsoft_array_proxy.h => stlsoft/array_proxy.hpp;
* stlsoft_container_base.h => stlsoft/obsolete/container_base.hpp;
* stlsoft_proxy_ptr.h => stlsoft/ptr_proxy.hpp;


## 1.9.1 beta 2 - 27th December 2005

* stlsoft::exception_string class. (Replaces simple_string in exception classes);
* stlsoft::string_concatenator_iterator;
* stlsoft::tref_reverse_iterator;


## 1.9.1 beta 1 - 20th December 2005

* includes alpha version of new XMLSTL sub-project;
* (nearly) completes the change of directory structure, e.g. from winstl_shell_allocator.h => winstl/shell_allocator.hpp;
* several new components;
* STLSOFT_CDECL_VALUE (1), STLSOFT_FASTCALL_VALUE(2) and STLSOFT_STDCALL_VALUE (3) to stlsoft.h;
* More operating systems detected in unixstl.h;
* Operating system family detection in unixstl.h;
* stlsoft::active_end_iterator_exhaustion (stlsoft/exceptions/active_end_iterator_exhaustion.hpp);
* stlsoft::ostream_iterator (stlsoft/iterators/ostream_iterator.hpp) - an enhancement to std::ostream_iterator, which supports prefix and suffix;
* stlsoft::transform_iterator.hpp (stlsoft/iterators/transform_iterator.hpp);
* comstl/stream_functions.h;
* mfcstl::CArray_cadaptor / mfcstl::CArray_iadaptor - class and instance adaptors for the MFC CArray family of containers to STL interfaces;
* platformstl::environment_map (platformstl/environment_map.hpp);
* winstl::dl_call() - Extremely powerful Dynamic Library Function invocation;
* winstl/console_functions.h;
* unixstl::dl_call() - Extremely powerful Dynamic Library Function invocation;
* dotnetstl/string_access.hpp and dotnetstl/string_accessor.hpp have been updated to support VC++ 8 hat syntax;
* stlsoft::ref_ptr now supports equality comparison;
* stlsoft::shared_ptr::use_count();
* stlsoft::shared_ptr contract enforcements;
* winstl::pid_sequence now supports reverse iteration;
* winstl::process_module_sequence now supports reverse iteration;
* stlsoft::string_tokeniser::const_iterator declared as forward iterator;
* winstl/find_file_sequence.hpp - fix for bug when zero-length sub-path matched;


<!-- ########################### end of file ########################### -->
