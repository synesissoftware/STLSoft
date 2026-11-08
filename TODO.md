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
  - [1.11.13](#11113)
  - [1.11.14](#11114)
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

* [x] Coverage of currently untested components — **bulk expansion landed in 1.11.1-rc6** (~640 new test programs);
* [x] ~~~`auto_buffer` GCC 12+ `-Wfree-nonheap-object` on the external-buffer `delete`~~~ - ✅;
* [x] ~~~xTests null-ptr macros~~~ - ✅;
* [x] ~~~alpha/beta/rc nomenclature throughout the repo~~~ - ✅;
* [x] ~~~**ACE** / **ATL** / **MFC** cells build the whole tree and run only their extra programs~~~ - ✅;
* [x] ~~~`strnistrn` correctness fix and `c_string` unit tests~~~ - ✅;


### 1.11.3

Released 27th October 2026. Coverage, **path-classify**, the CMake / helper-script / CI review, and the Resizeable Buffer follow-ups moved to **1.11.4**.

* [x] ~~~Add **test.performance.stlsoft.util.bit_functions**~~~ - ✅;
* [x] ~~~`HAS_<Pkg>` / `HAS_<PKG>` for detected Synesis packages; drop `STLSOFT_HAS_CSTRING` and `STLSOFT_HAS_UNIXEM`~~~ - ✅;
* [x] ~~~Opt-in **woad** (`--use-woad`) and coloured **test.scratch.versions.iostreams**~~~ - ✅;
* [x] ~~~ASCII case-fold and `memchr` / `memcmp` in the counted-string functions; **strategy/performance/C_STRING.md**~~~ - ✅;
* [x] ~~~Subproject root headers require **STLSoft** 1.11.2 or later~~~ - ✅;


### 1.11.4

Released 29th October 2026. `STLSOFT_USING_SAFE_STR_FUNCTIONS` worker abstraction and `platformstl::FILE_stream` in terms of **stlsoft/api/internal/memfns.h** moved to **1.11.5**.

* [x] ~~~Unit tests for the extant `mbstowcs` / `wcstombs` call sites: `multibyte2wide` / `wide2multibyte`, wide `exception_string_creator`, the `error_desc_w` fallback, the `ACE_Time_Value` wide shims, the `std::exception` wide shims, and the `std::type_info` wide shims~~~ - ✅;
* [x] ~~~`stlsoft_C_mbstowcs()` / `stlsoft_C_wcstombs()` contract (destination capacity, source limit, secure CRT) and **test.unit.stlsoft.string.encoding**. Call sites are not switched yet~~~ - ✅;
* [x] ~~~Wide `error_desc` fallback and both wide `invoke_ACE_OS_snprintf()` overloads call `stlsoft_C_mbstowcs()`~~~ - ✅;
* [x] ~~~`multibyte2wide` / `wide2multibyte` call `stlsoft_C_mbstowcs()` / `stlsoft_C_wcstombs()`~~~ - ✅;
* [x] ~~~`std::exception` and `std::type_info` wide shims call `stlsoft_C_mbstowcs()`. Their private `mbstowcs_()` / `mbstowcs_len()` helpers are removed~~~ - ✅;
* [x] ~~~`system_traits<wchar_t>::get_environment_variable()` and `unixstl_C_get_home_directory_w()` call `stlsoft_C_mbstowcs()` / `stlsoft_C_wcstombs()`~~~ - ✅;
* [x] ~~~Centralise `mbstowcs` / `mbstowcs_s` and `wcstombs` / `wcstombs_s` in `stlsoft_C_mbstowcs()` / `stlsoft_C_wcstombs()`. `wide_to_multibyte_or_throw_()` was the last call site outside the encoding headers~~~ - ✅;
* [x] ~~~Apply **woad** colours (as in **test.scratch.versions.iostreams**) to **test.scratch.versions.stdio**~~~ - ✅;
* [x] ~~~`invalid_integral_range_policy::operator()` — implement in terms of `stlsoft_C_snprintf()` (replace `::sprintf`)~~~ - ✅;
* [x] ~~~Output-iterator `deref_proxy` copy constructors, so C++11 and C++14 do not warn `-Wdeprecated-copy` when copy assignment is deleted~~~ - ✅;
* [x] ~~~**.dev/bin/batch_compile_check** — `-fsyntax-only`, separate C and C++ language versions, `-j`, skip-marker scan, Windows prelude, and a failing exit status with a `FAIL:` list~~~ - ✅;
* [x] ~~~**.dev/bin/check_unit_test_names.rb** — project-relative `File:` labels, runner names from the test directory, `--project-root`, and one CI job~~~ - ✅;


### 1.11.5

The enumerator-comma fix, the CMake program-name generator, the secure-CRT worker functions, the `STLSOFT_API_EXTERNAL_*` / `STLSOFT_API_INTERNAL_*` revisions, and the `<subproject>_C_` renames are in the tree. The items below remain.

* [x] ~~~Verify every `STLSOFT_SUPPRESS_UNUSED` of a destination-capacity parameter (`cchDest`, `cchSrc`, and the same pattern) before **1.11.5** is finished. For each site, decide whether that parameter belongs in the contract or the call is passing a size the callee ignores. Start with the new workers in **include/stlsoft/string/encoding/** (`stlsoft_C_mbstowcs`, `stlsoft_C_wcstombs`) and **include/stlsoft/string/c_string/** (`stlsoft_C_wcscpy`, `stlsoft_C_wcsncpy`) and then the same pattern in every other SIS C/C++ project~~~ - ✅;
* [x] ~~~`string_concatenation_flags` enumerators arrayed (`None`, then `, AlwaysSeparate`) to avoid a trailing comma~~~ - ✅;
* [x] ~~~**.dev/bin/generate_cmakelists.rb** 0.2.0 names generated programs by the xTests `__FILE__` rule (`--mode modern` default, `--mode legacy`, `--dry-run`) and was applied to the nineteen **examples** programs and the eleven performance / scratch targets that omitted a directory~~~ - ✅;
* [x] ~~~Find all `STLSOFT_USING_SAFE_STR_FUNCTIONS` and abstract call sites to worker functions~~~ - ✅;
* [x] ~~~`platformstl::FILE_stream` implemented in terms of **stlsoft/api/internal/memfns.h**~~~ - ✅;
* [x] ~~~Survey and improve API(External) functions~~~ - ✅;
* [x] ~~~Survey and improve API(Internal) functions~~~ - ✅;


### 1.11.6

* \<none>


### 1.11.7

* [x] ~~~Canonicalise C-language test/example program names to **`subject.C`** (suffix, not infix `.C.`); update inventories after the rename;~~~ - ✅;
* [x] ~~~WinSTL / COMSTL / ATLSTL / MFCSTL — Windows CI verification of new suites~~~ - ✅;


### 1.11.8

* [x] ~~~Replace the duplicated ASCII case-fold helpers with one shared pair: `stlsoft_C_strnicmp_fold_char_m_()` / `stlsoft_C_strnistrn_fold_char_m_()`, and `stlsoft_C_strnicmp_fold_char_w_()` / `stlsoft_C_strnistrn_fold_char_w_()`~~~ - ✅;
* [X] ~~~Have `basic_path_buffer` use pre and post eye-catchers (`STLSOFT_DEBUG`-only)~~~ - ❌ (it's deprecated and going to be removed in future version);
* [X] ~~~Rename HAS files under **include/stlsoft/internal/std/has/** to remove the trailing `_` (and disambiguate further if needed)~~~ - ❌ (no need, because these are all internal);
* [x] ~~~`STLSOFT_CF_PRAGMA_ONCE_SUPPORT` => `STLSOFT_PPF_pragma_once_SUPPORT`~~~ - ✅;
* [ ] Move **include/stlsoft/util/string/**\***printf.h** into **api/internal** and deprecate the old headers;
* [ ] Apply **woad** colours (as in **test.scratch.versions.iostreams**) to **test.scratch.versions.format**;


### 1.11.9

* [ ] Exception messages (consistency):
  * [ ] Identify those that pertain to programmer error (invalid use) vs runtime conditions, as the former should be more "precise" (e.g. include construct names) and the latter should be more "readable";
  * [ ] Punctuation;
  * [ ] Case;
  * [ ] " : " clausing;
* [ ] Correct/ensure (and write coding guidelines for) test-function naming;
* [ ] Review the relationship between **include/\*stl\*/error** and **include/\*stl\*/diagnostics**, and retain or consolidate only distinct responsibilities;
* [ ] All precondition enforcements => \pre;
* [ ] All \pre => precondition enforcements;


### 1.11.10

* [ ] Make **include/stlsoft/api/external** the lowest layer of abstraction: no `STLSOFT_API_EXTERNAL_*` alias may be implemented in terms of an `stlsoft_C_*` function (e.g. `STLSOFT_API_EXTERNAL_string_strnicmp` / `STLSOFT_API_EXTERNAL_string_wcsnicmp` currently fall back to `stlsoft_C_strnicmp` / `stlsoft_C_wcsnicmp`, which inverts the layering). Where the platform lacks a function, leave the alias undefined and put the portable fallback in **include/stlsoft/api/internal**, then fix the consumers (`stricmp` / `wcsicmp` have no portable fallback at all, and the `lstrcmpiA` / `lstrcmpiW` fallbacks need `<windows.h>`) - ⏸️ deferred;
* [ ] **include/stlsoft/conversion/byte_format_functions.hpp** known / suspected issues in `format_bytes()` (unit tests landed in **test.unit.stlsoft.conversion.byte_format_functions**; none of these is pinned by a test yet):
  * [x] ~~~the line-separator copy uses `STLSOFT_API_EXTERNAL_memfns_memcpy()` rather than `STLSOFT_API_INTERNAL_memfns_memcpy()`, so a `nullptr` `lineSeparator` with `groupsPerLine > 0` calls `memcpy(buff, nullptr, 0)` (the case the internal adaptation exists for)~~~ - ✅;
  * a `nullptr` `lineSeparator` with `groupsPerLine > 0` drops the group separator at each wrap point, so the last group of a line runs into the first of the next; the documented "no line separation is done" does not state this, so decide the intended behaviour, document it, and add tests;
  * [x] ~~~`cb == 0` returns 0 without writing a terminating NUL (in `STLSOFT_DEBUG` builds the buffer is left filled with `'~'`), whereas every other sufficient-buffer path terminates; decide and document the contract, then test it~~~ - ✅ (now terminates when `cchBuff != 0`; documented; tested);
  * [x] ~~~`format_hex_uint256()` and `format_hex_uint128()` declare `char buff[16]` (documentation only, but wrong: 64 and 32 characters are written)~~~ - ✅;
  * [x] ~~~the `STLSOFT_CONVERSION_BYTE_FORMAT_FUNCTIONS_USE_SPRINTF` path is untested, as are the `requestUppercaseAlpha` / `highByteFirst` variants, which `format_bytes()` hard-codes to `false`~~~ - ✅ (**test.unit.stlsoft.conversion.byte_format_functions.sprintf**; `impl::format_hex_uint8()` to `format_hex_uint64()` with both flags, and `impl::format_hex_uint128()` / `impl::format_hex_uint256()` with `highByteFirst == false`);
  * [x] ~~~`impl::format_hex_uint128()` and `impl::format_hex_uint256()` swap their halves when `highByteFirst` is `true`, so the output is not in byte order, unlike `format_hex_uint16()` to `format_hex_uint64()`~~~ - ✅ (fixed; **test.unit.stlsoft.conversion.byte_format_functions** covers both orders);
  * [x] ~~~the exact-fit case (`size == cchBuff`) writes no terminating NUL, so the size-query idiom (query with `nullptr`, allocate `n`, call again) yields an unterminated string; decide and document the contract (document that a C string needs `size + 1`, or make success strict), then update the exact-fit test accordingly;~~~ - ✅ (contract documented — NUL written only when `size < cchBuff`; tests **test_format_bytes_BUFFER_EXACT_PLUS_NUL** / **test_format_bytes_BUFFER_EXACT_NO_NUL**);
  * [x] ~~~**suspected one-byte overflow** in the `STLSOFT_CONVERSION_BYTE_FORMAT_FUNCTIONS_USE_SPRINTF` path: each `stlsoft_C_snprintf()` is passed `cchBuff` rather than the remaining capacity, so for the last group the terminating NUL is written at `buff[size]`, which is `buff[cchBuff]` on an exact fit. Found by reading, not yet reproduced; confirm with an AddressSanitizer run of **test.unit.stlsoft.conversion.byte_format_functions.sprintf** (the exact-fit test should trip it), then pass the remaining capacity;~~~ - ✅ (obviated: `snprintf` now formats into a local `hex_[65]` scratch and the digits are copied into the caller buffer, so no NUL is ever written into it);
  * the `size` arithmetic mixes `int` `groupsPerLine` with `ss_size_t` operands (safe as written, since every use is guarded by `groupsPerLine >= 1` and `-1` deliberately never matches `groupIndex`; comment the convention), and `numGroups * (…)` can overflow on 32-bit for very large `cb`; add an overflow guard;
* [ ] C-API prefix follow-ups noticed while checking retained wrappers:
  * [ ] Generated docs omit the retained `comstl__*` / `winstl__*` function wrappers because they sit in `STLSOFT_DOCUMENTATION_SKIP_SECTION`. The compiler message names the `*_C_*` successor. Decide whether a documentation-only `\deprecated` declaration should appear in the generated API;
  * [x] ~~~`BSTR_compare()` documents equality as "lexicographically equal than"~~~ - ✅;
  * [x] ~~~Search the other Synesis projects for calls to the deprecated STLSoft C API spellings (`comstl__*`, `winstl__*`, `inetstl_c_*`, and the other `<subproject>__` / `<subproject>_c_` function names retained until 1.13) and retarget them to the `*_C_*` successors. Record any obsolete `#define` aliases separately; those stay until their own pass~~~ - ✅ (no other project uses the obsolete macros; **cstring** calls `comstl_C_CoTaskMemGetSize`, **recls** calls `inetstl_C_sockaddr_un_init_from_path`);
* [ ] OLE-string C API, noticed while renaming `comstl_C_olestring_*`:
  * [ ] `comstl_C_olestring_create_a()` sizes the buffer as `cch + 1` after `MultiByteToWideChar` has already included the NUL in `cch`, so it allocates one extra character compared with `comstl_C_olestring_create_w()`. If the second conversion returns 0 it still returns that buffer with a leading NUL rather than freeing it and returning NULL;
  * [ ] `comstl_C_olestring_destroy()` asserts `CoTaskMemDidAlloc` and therefore rejects NULL, while `CoTaskMemFree(NULL)` is a no-op. The assert text says "non-COM string";
  * [x] ~~~`comstl_C_olestring_create_w()` calls `stlsoft_C_wcscpy()` rather than branching on `STLSOFT_USING_SAFE_STR_FUNCTIONS`~~~ - ✅;
* [ ] Error-info C API, noticed while renaming `comstl_C_set_error_info_*`:
  * [ ] `comstl_C_set_error_info_w_()` stores each `ICreateErrorInfo` setter's `HRESULT` over the previous one. A later success hides an earlier failure, and `SetErrorInfo` then publishes the partial object;
  * [ ] `comstl_C_set_error_info_a_helper_()` leaves its `CoTaskMemAlloc` block allocated when `MultiByteToWideChar` fails. `comstl_C_set_error_info_a_()` frees it; any other caller would leak;
  * [ ] The C functions that take a help file reject NULL, and there is no public C function for description + source + GUID alone. The C++ three-argument `set_error_info` calls `comstl_C_set_error_info_a_` / `comstl_C_set_error_info_w_` directly;
  * [ ] `comstl_C_EXCEPINFO_free()` asserts `NULL != pxi` and then dereferences `pxi`. A release build does not reject NULL;
* [ ] COM task-memory, refcount, and stream C API, noticed while renaming:
  * [ ] `comstl_C_CoTaskMemGetSize()` returns 0 when `CoGetMalloc` fails, the same value as a zero-length block. `comstl_C_CoTaskMemDidAlloc()` returns -1 in that case, the same value as "cannot determine". `comstl_C_olestring_destroy()` treats -1 as allocated (`0 != -1`) and still calls `CoTaskMemFree`;
  * [ ] `comstl_C_addref()` asserts a non-null pointer and documents `\pre`. `comstl_C_release()` says the pointer cannot be null and does not assert, so a null pointer is a release-build crash;
  * [ ] `comstl_C_get_stream_size()` does not document its pointers. A failed `Stat` leaves `*psize` unchanged. **refcount_functions.h** and **stream_functions.h** describe themselves as C++ only, while both publish a C API;
* [ ] Unix-domain socket helper, noticed while renaming `inetstl_C_sockaddr_un_init_from_path`:
  * [ ] A NULL `path` is treated as `""`. The contract does not say so;
  * [ ] A path that exactly fills `sun_path` is stored without a terminating NUL. The public text only lists the too-long `EINVAL` cases, and the first `EINVAL` line has an unclosed backtick;
  * [ ] The function documentation uses `@param` while the file block uses `\brief`;
* [ ] Combo-box, list-box, and edit C API, noticed while renaming `winstl_C_combobox_*`, `winstl_C_listbox_*`, and `winstl_C_edit_*`:
  * [ ] `winstl_C_combobox_gettext()` and `winstl_C_listbox_gettext()` are documented as the ambient encoding, but the buffer parameter is `LPCSTR`. `CB_GETLBTEXT` and `LB_GETTEXT` write through that pointer. The `_a` and `_w` forms take a non-const `ws_char_*_t*`;
  * [ ] The `combobox_insertstring` and `listbox_insertstring` string templates always call the ANSI overload. The `addstring` templates dispatch on the pointer type from `c_str_ptr`, so a wide string passed to an insert template is treated as ANSI;
  * [ ] `winstl_C_edit_getline_a()` and `winstl_C_edit_getline_w()` store `cchBuffer` in the first word of `buffer` (the `EM_GETLINE` contract) and do not say so. The control does not NUL-terminate the line, and `cchBuffer` is cast to `int` with no check that the buffer is at least `sizeof(int)`;
  * [ ] `winstl_C_combobox_getitemdata()` and `winstl_C_listbox_getitemdata()` return `ws_dword_t`, so `CB_ERR` / `LB_ERR` (`-1`) collides with a stored value of `0xFFFFFFFF`;
* [ ] Control-creation C API, noticed while renaming `winstl_C_CreateStatic*`, `winstl_C_CreateEdit*`, and `winstl_C_CreateCheckbox*`:
  * [ ] `winstl_C_setchildfont_()` discards both windows. The commented body would send `WM_SETFONT` to the parent, using the child's font, which is the reverse of giving the child the parent's font. Only the static creators call it;
  * [ ] `winstl_C_CreateEditA()`, `winstl_C_CreateEditW()`, `winstl_C_CreateCheckboxA()`, and `winstl_C_CreateCheckboxW()` mask the caller style with `0xFFFF`, so high-word window styles such as `WS_BORDER`, `WS_VSCROLL`, `WS_GROUP`, and `WS_DISABLED` are discarded. Nothing in the contract says so;
  * [ ] Every function's documentation comment is an empty brief plus `\ingroup`;
  * [ ] The first `CreateEdit` template is missing the `(` after the function name, so that overload is ill-formed;
  * [ ] The C++ `CreateStaticFrame` overloads default `id` to `-1`. `winstl_C_control_creation_functions_Id2HMENU_()` then passes that as `HMENU`, so the control id is `0xFFFF` rather than "no id";
* [ ] Shell-memory C API, noticed while renaming `winstl_C_SHMem*`:
  * [ ] `winstl_C_SHMemFree()` and `winstl_C_SHMemRealloc()` say they use the shell allocator to allocate a block;
  * [ ] `winstl_C_SHMemGetSize()` returns 0 when `SHGetMalloc` fails, the same value as a zero-length block. `winstl_C_SHMemDidAlloc()` returns -1 in that case;
  * [ ] `Alloc`, `Free`, and `Realloc` say "shell allocator". `GetSize`, `DidAlloc`, and `HeapMinimise` say "COM task allocator". All six call `SHGetMalloc`. `GetSize` also spells it "alloctor", and `HeapMinimise` says "as as per";
  * [ ] When `winstl_C_SHMemRealloc()` fails it returns NULL and the original block is still allocated. The contract does not say so;
* [ ] Window message and creation C API, noticed while renaming `winstl_C_SendMessage*` and `winstl_C_CreateWindow*`:
  * [ ] None of `winstl_C_SendMessage()`, `winstl_C_SendMessageA()`, or `winstl_C_SendMessageW()` has a documentation comment. The C++ `SendMessageA` and `SendMessageW` overloads are compiled only when the namespace is enabled and the compiler is not Borland. There is no C++ unsuffixed `SendMessage`;
  * [ ] None of the `winstl_C_CreateWindow*` functions has a documentation comment. The file brief says "Control creation functions"; the purpose line says window creation. The C++ `CreateWindowA`, `CreateWindowW`, `CreateWindow`, and `CreateWindowEx` overloads are commented out; only `CreateWindowExA` and `CreateWindowExW` are compiled;
  * [x] ~~~**font_functions.h** said its purpose was "Error functions"~~~ - ✅ (now "Window font functions");
* [ ] Font, GDI, menu, scale, and text-metrics C API, noticed while renaming:
  * [ ] `winstl_C_get_LOGBRUSH()` names its brush `hpal`. `winstl_C_get_LOGFONT()` names its font `hpal`;
  * [ ] The six `winstl_C_get_*` GDI functions, the three menu functions, the four `winstl_C_calc_*` functions, and the three `winstl_C_get_textmetrics*` functions have no documentation comments. `get_object_helper()` turns a zero `GetObject` result into a value-initialised description, so failure looks like an empty object;
  * [ ] `winstl_C_IsMenuItemChecked()` returns FALSE when `GetMenuItemInfo` fails, the same result as an unchecked item. None of the three menu functions zeroes `MENUITEMINFO` before use;
  * [ ] `winstl_C_get_textmetrics_a()` and `winstl_C_get_textmetrics_w()` return a zero `TEXTMETRIC` when `GetTextMetrics` fails. The contract does not say so;
  * [ ] `winstl_C_calc_RECT_width()` and `winstl_C_calc_RECT_height()` return `right - left` and `bottom - top`, which are negative when the rectangle is inverted;
  * [ ] The C++ `treeview_getchilditem`, `treeview_getrootitem`, and `treeview_getcaretitem` call `winstl_C_treeview_getnextitem` directly, rather than the C functions of the same role;
* [ ] bring in some essential unit-tests from internal repo;


### 1.11.11



### 1.11.12

* [ ] Resizeable Buffer — follow-ups deferred from the **1.11.1** concept/implementation lock (do **not** reopen C1–C5, D1–D4, G2, G3, G5–G7 without cause; gold contract is **CONCEPTS.md** — *The Resizeable Buffer concept* and *Contract for traits overloads that take an `rb`*; helper **stlsoft/util/resizeable_buffer_helpers.hpp**; exemplar `rb` overloads include `get_current_process_path(rb)` and winstl `get_module_directory(rb)`):
  * [ ] **G1** — unixstl `system_traits::expand_environment_strings` is **declare-only** (ANSI + wide; both the C-string `(src, buffer, cch)` and `rb` overloads have no definitions in **include/unixstl/system/system_traits.hpp**); WinSTL already implements both (incl. an `rb` overload); callers such as **include/platformstl/filesystem/cwd_stack.hpp** invoke it and will fail to link on UNIX if used — **either** implement (gold probe-then-fill; env/expansion demand must account for trailing NUL; resize failure → `ENOMEM`; unit/component tests) **or** undeclare/remove the stubs and fix/guard callers; same gap is noted under **1.11.6**;
  * [ ] **G4** — settle **caller empty-`rb` policy**: whether traits `rb` overloads require / document that callers always pass an empty buffer (`0 == rb.size()`) versus allowing a pre-sized/`capacity`-bearing `rb` (today gold probes with a null buffer + zero capacity and only resizes when `rb.size() < cchRequired`; some older `rb` overloads still probe via `0 == rb.size() ? NULL : &rb[0]`) — record the decision in **CONCEPTS.md** and align overload docs/impls/tests to it;
  * [ ] **C6** — Resizeable Buffer is **structurally typed** only: look-alike types can compile without honouring trailing-NUL / `size()`-includes-NUL invariants; **path_buffer** / **file_path_buffer** remain documented non-models in **CONCEPTS.md** — decide whether to add debug asserts (e.g. trailing NUL when `!empty()`), concept-check helpers, and/or harden docs/tests so misuse is caught;
  * [ ] **C7** — gold probe-then-fill has **no retry** if the required size changes between the null probe and the fill (TOCTOU on env/cwd/path); rare in practice — either document as accepted limitation in **CONCEPTS.md** or add a bounded grow-and-retry loop with tests;
  * [ ] **P1** — several winstl `system_traits` `rb` overloads (e.g. `get_module_filename`, `get_home_directory`, `expand_environment_strings`) always perform a **second** fill API call even when the first call already succeeded with `rb.size() >= cchRequired`; prefer returning the first-call result when the buffer was already large enough (no behaviour change on the normative path) — measure/guard with existing unit coverage;
  * [ ] **P2** — unixstl `filesystem_traits` `rb` path helpers (notably relative `get_full_path_name(rb)`) **query twice** and/or allocate heavy scratch (`path_max()`-sized `auto_buffer`, large stack cwd) — reduce duplicate work (compute once into scratch then copy, or reuse probe data) without changing the public contract; add/extend component tests under **test/component/unixstl/filesystem/filesystem_traits/**;
  * [ ] **P3** — `ensure_dir_end(rb)` grows by exactly **+1**, which forces a heap realloc when an `auto_buffer` is already on its internal array boundary; internal callers often avoid the `rb` form for this reason — consider amortized growth or document that pointer/`&sz[0]` forms remain preferred for hot paths; cover with unit tests if behaviour changes;


### 1.11.13

* [ ] Deeper API documentation on top of the Doxygen build that landed in **1.11.1** (**Doxyfile**, **generate_doxygen.sh**, **doc/mainpage.md**) — see also [**KNOWN_ISSUES.md**](./KNOWN_ISSUES.md);


### 1.11.14

Misc:
* [x] ~~~Bring in the `memchr` / `memcmp` and ASCII case-fold performance work for `strnchr`, `strnicmp`, `strnistrn`, and `strnstrn`, plus **test.performance.stlsoft.string.c_string**~~~ - ✅;

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

* [ ] Land **path-classify**: **include/platformstl/filesystem/path_classify_functions.h**, the unixstl `path_classify_root` / `path_is_absolute` exposure (R13), and the platformstl unit tests. (The unixstl/winstl UNC / `\\?\` / `\\.\` / ASCII drive-letter fixes, `numDotsDirectoryParts`, the R9 documentation, and the unixstl/winstl host test suites landed in **1.11.7**.) Cherry onto this line from the **STLSoft.b** local `path-classify` tip (`18035dbe`); the `ss/path-classify` tip predates **1.11.2**;
* [ ] Land **path-classify.full** after **path-classify**: callers prefer `path_is_*`, deprecation-warning suppression, and removal of `get_root_len_` (R24, already done on that branch). Same tip on both clones (`4d907dcd`), and that tip also predates **1.11.2**;


* [ ] Take down https://github.com/synesissoftware/STLSoft-1.10-delta;
* [ ] Bring in **include/stlsoft/string/trim_functions.h** and **test/unit/stlsoft/string/trim_functions** from `mwsis/trim_functions` (on the **STLSoft** clone);
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
* [ ] Search, by several different means, for existing facilities worth future blog posts and articles on stlsoft.org. Starting candidates include:
  * [ ] fast string-searching functions;
  * [ ] fine-grained microsecond wait on Windows (`winstl::micro_sleep()`);
  * [ ] the fast integer-to-string functions;
  * [ ] `doomgram`;
  * [ ] `par_strip`;
  * [ ] ... and many more ...;
* [ ] Set-up donation;
* [ ] Work out how to provide compiler/language-dialect compatibility reporting in an automated or semi-automated manner henceforth (replaces the retired manual matrix);

* [ ] Flesh out declared-but-undefined `unixstl::system_traits` methods (Linux system calls; emulations/workarounds elsewhere) — see also [**KNOWN_ISSUES.md**](./KNOWN_ISSUES.md):
  * [ ] `expand_environment_strings` (ANSI + wide; C-string and `rb` overloads) — implement or undeclare; full pickup brief under **1.11.4** Resizeable Buffer **G1**;

* [ ] **Build helper scripts:** Thorough review of the build helper scripts (especially the run scripts) and the means by which executable files are identified; separate those aspects correctly and clearly. Same concern applies across other SIS freelib projects. Scope includes discovery globs, execute-bit / artifact restore, zero-match failure, verbosity, and CI wiring for **run_all_unit_tests.sh**, **run_all_scratch_tests.sh**, **run_all_examples.sh**, **execute_performance_tests.sh**, and Windows `.cmd` counterparts;
* [ ] **CMake scripts:** Diff all CMake script files (**CMakeLists.txt**, **\*.cmake**) since **1.11.1-rc4**; discuss each change — likely adding comments in the scripts and/or notes in the project documentation guidelines — so the newer techniques are clearly explained;
* [ ] **CI configuration:** Thorough review of **ci.yml** and **ci-cell.yml** — identify and separate the various aspects correctly and clearly. Same concern applies across other SIS freelib projects;

* [ ] Existing test consistency (deep analysis) — many new tests are compile-verified or smoke-level; behavioural depth still to be improved;
* [ ] Complete coverage of currently tested components (improvement / completion);
* [ ] Complete coverage of currently untested components (improvement / completion);
* [ ] Coverage of currently untested components. Some previously unreleased tests landed in **1.11.1**. The remaining candidate tree is `test-coverage` (about 662 new entries, **TESTING.md**, **TESTING-C.md**, and **test/scripts** generators). That branch predates **1.11.1-rc10** and still uses the old `test.<kind>.*` directory names; rebase it before any merge;
* [ ] STLSoft — deepen behavioural tests for the ~100 compile-only scaffolds; remove or fix vestigial targets;


## 1.13

* [ ] Remove deprecated mixed-case C API wrappers and enumerator aliases (`STLSoft_C_*`, `WinSTL_C_*`, `UNIXSTL_C_PathType_*`, and any later-deprecated forms);
* [ ] Recognise the Tiny C Compiler for C translation units (**include/stlsoft/internal/cccap/tinycc.h**). Cherry the recognition from `ss/tcc`; the rest of that branch predates **1.11.1**;
* [ ] Remove **WTL**;
* [ ] Remove defunct compilers;
* [ ] Rename `include/*stl*/error` → `include/*stl*/diagnostics` (with deprecation aliases as needed);


## Requires clarification by project maintainers

* [ ] Integrate **STLSoft**'s exception hierarchies with the new standard exception design — **1.12**; requires further elaboration by the project maintainer before implementation;


## Abandoned

* [x] ~~~custom radix in integer_to_string - abandoned for performance reasons, and obviated by new conversion functions (oct, dec, hex) in 1.10~~~ - ❌;
* [x] ~~~SourceSafe-era “do not branch the whole monorepo” note~~~ - ❌ (obsolete under Git; superseded by assessing the separate 1.12 internal repository for inclusion);
* [x] ~~~Manual C/C++ dialect compatibility matrix in **TODO.md**~~~ - ❌ (CI is the record of actively exercised builds; automated/semi-automated reporting deferred to **1.12**);
* [x] ~~~Migrate/deprecate **include/stlsoft/std/**`*` in parallel with `*printf.h`~~~ - ❌ (cut);


<!-- ########################### end of file ########################### -->
