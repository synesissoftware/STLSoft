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
  - [1.11.12](#11112)
  - [Cross-publish to STLSoft-1.11](#cross-publish-to-stlsoft-111)
- [1.12](#112)
- [1.13](#113)
- [Requires clarification by project maintainers](#requires-clarification-by-project-maintainers)
- [Abandoned](#abandoned)


## 1.11


### 1.11.1

Released 21st October 2026 (`43541c13`). Unmet items moved to **1.11.3** and **1.12**.

* [x] ~~~CI: exercise **MFCSTL** on a Windows cell (drop / gate `CMAKE_DISABLE_FIND_PACKAGE_MFC`; confirm MSVC+MFC on the runner)~~~ - ✅;
* [x] ~~~ACESTL: implement `invoke_ACE_OS_snprintf` in terms of `stlsoft_C_snprintf()`~~~ - ✅;
* [x] ~~~CI: exercise **ATLSTL** on a Windows cell~~~ - ✅;
* [x] ~~~Unit/component tests — adopt **xTests** terse API throughout~~~ - ✅;
* [x] ~~~Bring in the Resizeable Buffer concept (**CONCEPTS.md**)~~~ - ✅;


### 1.11.2

Released 25th October 2026 (`17526622`). The planned test-coverage mission and the pre-release gate moved to **1.11.3**.

* [x] ~~~`auto_buffer` GCC 12+ `-Wfree-nonheap-object` on the external-buffer `delete`~~~ - ✅;
* [x] ~~~xTests null-ptr macros~~~ - ✅;
* [x] ~~~alpha/beta/rc nomenclature throughout the repo~~~ - ✅;
* [x] ~~~**ACE** / **ATL** / **MFC** cells build the whole tree and run only their extra programs~~~ - ✅;
* [x] ~~~`strnistrn` correctness fix and `c_string` unit tests~~~ - ✅;


### 1.11.3

Open increment. On the **STLSoft** clone, `dev` / `1_12` already stamp `_STLSOFT_VER_1_11_3` (27th October 2026) with an empty **CHANGES.md** section.

* [ ] `invalid_integral_range_policy::operator()` — implement in terms of `stlsoft_C_snprintf()` (replace `::sprintf`);
* [x] ~~~Add **test.performance.stlsoft.util.bit_functions**~~~ - ✅;
* [ ] Take down https://github.com/synesissoftware/STLSoft-1.10-delta;
* [ ] Complete coverage of currently tested components (improvement / completion);
* [ ] Coverage of currently untested components. Some previously unreleased tests landed in **1.11.1**. The remaining candidate tree is `test-coverage` (about 662 new entries, **TESTING.md**, **TESTING-C.md**, and **test/scripts** generators). That branch predates **1.11.1-rc10** and still uses the old `test.<kind>.*` directory names; rebase it before any merge;
* [ ] Land **path-classify**: **include/platformstl/filesystem/path_classify_functions.h**, the unixstl/winstl UNC / `\\?\` / `\\.\` / ASCII drive-letter fixes, and the unit tests. Cherry onto this line from the **STLSoft.b** local `path-classify` tip (`18035dbe`); the `ss/path-classify` tip predates **1.11.2**;
* [ ] Land **path-classify.full** after **path-classify**: callers prefer `path_is_*`, deprecation-warning suppression, and removal of `get_root_len_` (R24, already done on that branch). Same tip on both clones (`4d907dcd`), and that tip also predates **1.11.2**;

Must resolve before finalising the **1.11.3** release:

* [ ] **CMake scripts:** Diff all CMake script files (**CMakeLists.txt**, **\*.cmake**) since **1.11.1-rc4**; discuss each change — likely adding comments in the scripts and/or notes in the project documentation guidelines — so the newer techniques are clearly explained;
* [ ] **Build helper scripts:** Thorough review of the build helper scripts (especially the run scripts) and the means by which executable files are identified; separate those aspects correctly and clearly. Same concern applies across other SIS freelib projects. Scope includes discovery globs, execute-bit / artifact restore, zero-match failure, verbosity, and CI wiring for **run_all_unit_tests.sh**, **run_all_scratch_tests.sh**, **run_all_examples.sh**, **execute_performance_tests.sh**, and Windows `.cmd` counterparts;
* [ ] **CI configuration:** Thorough review of **ci.yml** and **ci-cell.yml** — identify and separate the various aspects correctly and clearly. Same concern applies across other SIS freelib projects;
* [ ] Resizeable Buffer — follow-ups deferred from the **1.11.1** concept/implementation lock (do **not** reopen C1–C5, D1–D4, G2, G3, G5–G7 without cause; gold contract is **CONCEPTS.md** — *The Resizeable Buffer concept* and *Contract for traits overloads that take an `rb`*; helper **stlsoft/util/resizeable_buffer_helpers.hpp**; exemplar `rb` overloads include `get_current_process_path(rb)` and winstl `get_module_directory(rb)`):
  * [ ] **G1** — unixstl `system_traits::expand_environment_strings` is **declare-only** (ANSI + wide; both the C-string `(src, buffer, cch)` and `rb` overloads have no definitions in **include/unixstl/system/system_traits.hpp**); WinSTL already implements both (incl. an `rb` overload); callers such as **include/platformstl/filesystem/cwd_stack.hpp** invoke it and will fail to link on UNIX if used — **either** implement (gold probe-then-fill; env/expansion demand must account for trailing NUL; resize failure → `ENOMEM`; unit/component tests) **or** undeclare/remove the stubs and fix/guard callers; same gap is noted under **1.11.6**;
  * [ ] **G4** — settle **caller empty-`rb` policy**: whether traits `rb` overloads require / document that callers always pass an empty buffer (`0 == rb.size()`) versus allowing a pre-sized/`capacity`-bearing `rb` (today gold probes with a null buffer + zero capacity and only resizes when `rb.size() < cchRequired`; some older `rb` overloads still probe via `0 == rb.size() ? NULL : &rb[0]`) — record the decision in **CONCEPTS.md** and align overload docs/impls/tests to it;
  * [ ] **C6** — Resizeable Buffer is **structurally typed** only: look-alike types can compile without honouring trailing-NUL / `size()`-includes-NUL invariants; **path_buffer** / **file_path_buffer** remain documented non-models in **CONCEPTS.md** — decide whether to add debug asserts (e.g. trailing NUL when `!empty()`), concept-check helpers, and/or harden docs/tests so misuse is caught;
  * [ ] **C7** — gold probe-then-fill has **no retry** if the required size changes between the null probe and the fill (TOCTOU on env/cwd/path); rare in practice — either document as accepted limitation in **CONCEPTS.md** or add a bounded grow-and-retry loop with tests;
  * [ ] **P1** — several winstl `system_traits` `rb` overloads (e.g. `get_module_filename`, `get_home_directory`, `expand_environment_strings`) always perform a **second** fill API call even when the first call already succeeded with `rb.size() >= cchRequired`; prefer returning the first-call result when the buffer was already large enough (no behaviour change on the normative path) — measure/guard with existing unit coverage;
  * [ ] **P2** — unixstl `filesystem_traits` `rb` path helpers (notably relative `get_full_path_name(rb)`) **query twice** and/or allocate heavy scratch (`path_max()`-sized `auto_buffer`, large stack cwd) — reduce duplicate work (compute once into scratch then copy, or reuse probe data) without changing the public contract; add/extend component tests under **test/component/unixstl/filesystem/filesystem_traits/**;
  * [ ] **P3** — `ensure_dir_end(rb)` grows by exactly **+1**, which forces a heap realloc when an `auto_buffer` is already on its internal array boundary; internal callers often avoid the `rb` form for this reason — consider amortized growth or document that pointer/`&sz[0]` forms remain preferred for hot paths; cover with unit tests if behaviour changes;


### 1.11.4

* [ ] `platformstl::FILE_stream` implemented in terms of **stlsoft/api/internal/memfns.h**;
* [ ] Existing test consistency (deep analysis);


### 1.11.5

* [ ] Find all `STLSOFT_USING_SAFE_STR_FUNCTIONS` and abstract call sites to worker functions;
* [ ] Centralise `mbstowcs` / `mbstowcs_s` and `wcstombs` / `wcstombs_s` in a single function;


### 1.11.6

* [ ] Flesh out declared-but-undefined `unixstl::system_traits` methods (Linux system calls; emulations/workarounds elsewhere) — see also [**KNOWN_ISSUES.md**](./KNOWN_ISSUES.md):
  * [ ] `expand_environment_strings` (ANSI + wide; C-string and `rb` overloads) — implement or undeclare; full pickup brief under **1.11.3** Resizeable Buffer **G1**;


### 1.11.7

* [ ] Review the relationship between **include/*stl*/error** and **include/*stl*/diagnostics**, and retain or consolidate only distinct responsibilities;
* [ ] Rename `include/*stl*/error` → `include/*stl*/diagnostics` (with deprecation aliases as needed);


### 1.11.8

* [ ] Move **include/stlsoft/util/string/**\***printf.h** into **api/internal** and deprecate the old headers;
* [ ] All precondition enforcements => \pre;
* [ ] All \pre => precondition enforcements;


### 1.11.9

* [ ] Recognise the Tiny C Compiler for C translation units (**include/stlsoft/internal/cccap/tinycc.h**). Cherry the recognition from `ss/tcc`; the rest of that branch predates **1.11.1**;


### 1.11.10

* [ ] Have `basic_path_buffer` use pre and post eye-catchers (`STLSOFT_DEBUG`-only);
* [ ] Canonicalise exception messages (consistency, lower-case, etc.);
* [ ] Rename HAS files under **include/stlsoft/internal/std/has/** to remove the trailing `_` (and disambiguate further if needed);


### 1.11.11

* [ ] Deeper API documentation on top of the Doxygen build that landed in **1.11.1** (**Doxyfile**, **generate_doxygen.sh**, **doc/mainpage.md**) — see also [**KNOWN_ISSUES.md**](./KNOWN_ISSUES.md);
* [ ] Remove defunct compilers;
* [ ] Remove **WTL**;


### 1.11.12

Misc:
* [ ] Bring in **include/stlsoft/string/trim_functions.h** and **test/unit/stlsoft/string/trim_functions** from `mwsis/trim_functions` (on the **STLSoft** clone);
* [ ] Bring in the `memchr` / `memcmp` and ASCII case-fold performance work for `strnchr`, `strnicmp`, `strnistrn`, and `strnstrn`, plus **test.performance.stlsoft.string.c_string**, from `mwsis/mem-fns` (on the **STLSoft** clone). The `strnistrn` correctness fix is already in **1.11.2**;

Normalise C API (and related C-facing) identifier prefixes. **House rule**
(documented in **c-cpp-standards** → *STLSoft C API identifier prefixes*):

* **Functions**, **types**, and **enumerators** — lowercase `<subproject>_C_`;
* **Macros** — ALL_UPPERCASE (including the project key);
* Do not introduce mixed forms such as `WinSTL_C_` / `STLSoft_C_`;
* When renaming, retain older public names (deprecated wrappers or
  documentation-hidden `#define` aliases) until at least **STLSoft 1.13**.

The **1.11** prefix work is complete. Removal of the deprecated aliases is **1.13**.

* [x] ~~~Establish and document the rule (see **c-cpp-standards**)~~~ - ✅;
* [x] ~~~Rename `STLSoft_C_string_copy*` / `STLSoft_C_string_copy_with_nul*` → `stlsoft_C_*` in **include/stlsoft/string/copy_functions.h** and all call sites (deprecated wrappers retained until at least **1.13**)~~~ - ✅;
* [x] ~~~Rename `WinSTL_C_FileInformation_*` → `winstl_C_*` in **include/winstl/filesystem/file_information_functions.h** and call sites (deprecated wrappers retained until at least **1.13**)~~~ - ✅;
* [x] ~~~Rename path-classify `PathType` enumerators: `WinSTL_C_PathType_*` → `winstl_C_PathType_*`, and `UNIXSTL_C_PathType_*` → `unixstl_C_PathType_*` (legacy names retained as documentation-hidden macros until at least **1.13**)~~~ - ✅;
* [x] ~~~Rename path-classify impl macros `WINSTL_C_PATH_CLASSIFY_IMPL_*` / `UNIXSTL_C_PATH_CLASSIFY_IMPL_*` to lowercase~~~ - ❌ (ALL_UPPERCASE macros are house style; no rename);
* [x] ~~~Decide policy for `STLSOFT_C_AUTO_BUFFER_*` / `STLSOFT_C_CAST`~~~ - ❌ (ALL_UPPERCASE is the house form; keep);



### Cross-publish to STLSoft-1.11

When tip **1.11** is finally complete, cross-publish into the versioned line **[synesissoftware/STLSoft-1.11](https://github.com/synesissoftware/STLSoft-1.11)** (not done for the interim VOLE / historical-consumer recognition work — that line was left unpushed on purpose).

The **`prospective-msvc`** branch is absent from both the **STLSoft** and **STLSoft.b** clones. Recover the warn-not-error forward-warning before this cross-publish.

* [ ] Cross-publish the completed tip **1.11** tree into **STLSoft-1.11**, including the unknown-newer Visual C++ warn-not-error forward-warning from the **`prospective-msvc`** branch (and any related recognition / semi-freeze messaging needed for historical consumers);


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
* [ ] Bring in the remaining CONCEPTS documentation:
  * [ ] auto-buffer;
  * [ ] string-access shims;
  * [ ] Null Object (variable);
  * [ ] Externals (esp. not introducing sub-project's headers proper);
  * [ ] Conformance: Structural, Semantic, Intersecting;
* [ ] Bring in **include/stlsoft/diagnostics/par_strip.hpp** (example, unit test, and performance test) from `par_strip`. Cherry the component; that branch predates **1.11.1-rc10**;
* [ ] `exception_string` `swap()`, ADL `swap` tests, and gated `std::swap` specialisations, from `1_12.std-swap` on the **STLSoft** clone;
* [ ] Memory-mapped-file class minor issues;
* [ ] Deprecate various iterator types;
* [ ] Standard names of integer-to-string and string-to-integer (for multiple bases; may already be done — verify);
* [ ] Remove defunct / outmoded components;
* [ ] New Website (contemporaneous with 1.12);
* [ ] STLSoft-related blog posts on the new Website (focusing on new components);
* [ ] Set-up donation;
* [ ] Work out how to provide compiler/language-dialect compatibility reporting in an automated or semi-automated manner henceforth (replaces the retired manual matrix);


## 1.13

* [ ] Remove deprecated mixed-case C API wrappers and enumerator aliases (`STLSoft_C_*`, `WinSTL_C_*`, `UNIXSTL_C_PathType_*`, and any later-deprecated forms);


## Requires clarification by project maintainers

* [ ] Integrate **STLSoft**'s exception hierarchies with the new standard exception design — **1.12**; requires further elaboration by the project maintainer before implementation;


## Abandoned

* [x] ~~~custom radix in integer_to_string - abandoned for performance reasons, and obviated by new conversion functions (oct, dec, hex) in 1.10~~~ - ❌;
* [x] ~~~SourceSafe-era “do not branch the whole monorepo” note~~~ - ❌ (obsolete under Git; superseded by assessing the separate 1.12 internal repository for inclusion);
* [x] ~~~Manual C/C++ dialect compatibility matrix in **TODO.md**~~~ - ❌ (CI is the record of actively exercised builds; automated/semi-automated reporting deferred to **1.12**);
* [x] ~~~Migrate/deprecate **include/stlsoft/std/**`*` in parallel with `*printf.h`~~~ - ❌ (cut);


<!-- ########################### end of file ########################### -->
