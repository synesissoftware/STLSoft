# STLSoft - TODO <!-- omit in toc -->

> **NOTE**: some of the following are very old, stretching back even into the 2000s, so this list will be updated a lot over the coming months. The most glaring of these is to ensure compatibility with C++14/17/20/23/26 as is necessary.


## Table of Contents <!-- omit in toc -->

- [1.11](#111)
  - [1.11.1](#1111)
  - [1.11.2](#1112)
  - [1.11.3](#1113)
  - [1.11.4](#1114)
  - [1.11.5](#1115)
  - [1.11.6](#1116)
  - [1.11.7](#1117)
  - [1.11.8](#1118)
  - [1.11.9](#1119)
  - [1.11.10](#11110)
  - [1.11.11](#11111)
- [1.12](#112)
- [Requires clarification by project maintainers](#requires-clarification-by-project-maintainers)
- [Abandoned](#abandoned)


## 1.11


### 1.11.1

* [x] ~~~CI: exercise **MFCSTL** on a Windows cell (drop / gate `CMAKE_DISABLE_FIND_PACKAGE_MFC`; confirm MSVC+MFC on the runner)~~~ - ✅;
* [x] ~~~ACESTL: implement `invoke_ACE_OS_snprintf` in terms of `stlsoft_C_snprintf()`~~~ - ✅;
* [x] ~~~CI: exercise **ATLSTL** on a Windows cell~~~ - ✅;
* [x] ~~~Unit/component tests — adopt **xTests** terse API throughout~~~;
* [ ] Remove **WTL**;
* [ ] Resolve finally the structure and semantics of the top-level execution scripts (**run_all_unit_tests.sh**, **run_all_scratch_tests.sh**, **run_all_examples.sh**, **execute_performance_tests.sh**, and Windows `.cmd` counterparts) on all platforms — discovery globs, execute-bit / artifact restore, zero-match failure, verbosity, and CI wiring;
* [ ] bring in some essential unit-tests from interal repo;


### 1.11.2

Dedicated increment: **test analysis and coverage only** — no other product changes in this release.

* [ ] Existing test consistency (deep analysis);
* [ ] Complete coverage of currently tested components (improvement / completion);
* [ ] Coverage of currently untested components;


### 1.11.3

* [ ] Remove defunct compilers;
* [ ] `invalid_integral_range_policy::operator()` — implement in terms of `stlsoft_C_snprintf()` (replace `::sprintf`);
* [ ] Canonicalise exception messages (consistency, lower-case, etc.);
* [ ] Rename HAS files under **include/stlsoft/internal/std/has/** to remove the trailing `_` (and disambiguate further if needed);
* [ ] Add **test.performance.stlsoft.util.bit_functions**;
* [ ] Take down https://github.com/synesissoftware/STLSoft-1.10-delta;


### 1.11.4

* [ ] `platformstl::FILE_stream` implemented in terms of **stlsoft/api/internal/memfns.h**;


### 1.11.5

* [ ] Find all `STLSOFT_USING_SAFE_STR_FUNCTIONS` and abstract call sites to worker functions;


### 1.11.6

* [ ] Flesh out declared-but-undefined `unixstl::system_traits` methods (Linux system calls; emulations/workarounds elsewhere) — see also [**KNOWN_ISSUES.md**](./KNOWN_ISSUES.md);


### 1.11.7

* [ ] Rename `include/*stl*/error` → `include/*stl*/diagnostics` (with deprecation aliases as needed);


### 1.11.8

* [ ] Move **include/stlsoft/util/string/**`*printf.h` into **api/internal** and deprecate the old headers;


### 1.11.9

* [ ] Centralise `mbstowcs` / `mbstowcs_s` and `wcstombs` / `wcstombs_s` in a single function;


### 1.11.10

* [ ] Have `basic_path_buffer` use pre and post eye-catchers (`STLSOFT_DEBUG`-only);


### 1.11.11

* [ ] Doxygen build (**Doxyfile**, **generate_doxygen.sh**) and deeper API documentation — see also [**KNOWN_ISSUES.md**](./KNOWN_ISSUES.md);


## 1.12

From **1.12** onwards, every new component or feature must ship with an **example**, **unit tests**, and a **blog entry** on the new Website (website work is contemporaneous with 1.12). See **oss-library-modernisation** (STLSoft 1.12+ feature completeness).

* [ ] Assess all **1.12** (separate internal repository) contents for inclusion, component by component;
* [ ] Inventory remaining C++11/14/17/20/23/26 gaps and record concrete per-standard fixes (see NOTE above);
* [ ] Further `system_traits` structural refactoring (CRTP common code; string abstraction into `stlsoft::`; safe-string sorting; `#make_writeable()` / `#make_readonly()`);
* [ ] `stlsoft::auto_buffer<>::copy_from()` — template across differing `V_internalSize`;
* [ ] Hash specialisations for all appropriate key types (incl. `stlsoft::basic_simple_string<>`, etc.);
* [ ] Syslog in variadic templates, a la `winstl::output_debug_line()`;
* [ ] Simple thread-pool (bring from **SS** work circa 2000);
* [ ] Bring in `platformstl::properties_file` from the unpublished 1.12 tree;
* [ ] Bring in `platformstl::temporary_directory_contents` from the unpublished 1.12 tree;
* [ ] Memory-mapped-file class minor issues;
* [ ] Deprecate various iterator types;
* [ ] Standard names of integer-to-string and string-to-integer (for multiple bases; may already be done — verify);
* [ ] Remove defunct / outmoded components;
* [ ] New Website (contemporaneous with 1.12);
* [ ] STLSoft-related blog posts on the new Website (focusing on new components);
* [ ] Set-up donation;
* [ ] Work out how to provide compiler/language-dialect compatibility reporting in an automated or semi-automated manner henceforth (replaces the retired manual matrix);


## Requires clarification by project maintainers

* [ ] Integrate **STLSoft**'s exception hierarchies with the new standard exception design — **1.12**; requires further elaboration by the project maintainer before implementation;


## Abandoned

* [-] ~~~custom radix in integer_to_string - abandoned for performance reasons, and obviated by new conversion functions (oct, dec, hex) in 1.10~~~ - ❌;
* [-] ~~~SourceSafe-era “do not branch the whole monorepo” note~~~ - ❌ (obsolete under Git; superseded by assessing the separate 1.12 internal repository for inclusion);
* [-] ~~~Manual C/C++ dialect compatibility matrix in **TODO.md**~~~ - ❌ (CI is the record of actively exercised builds; automated/semi-automated reporting deferred to **1.12**);
* [-] ~~~Migrate/deprecate **include/stlsoft/std/**`*` in parallel with `*printf.h`~~~ - ❌ (cut);


<!-- ########################### end of file ########################### -->
