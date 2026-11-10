# STLSoft - Exception Messages <!-- omit in toc -->

Strategy note for **STLSoft** (this tree, **STLSoft.b**) capturing every exception message literal in **include/**, classified by nature and assessed for "rightness". Survey date: 10th November 2026.

Paths are relative to **include/**. Sites throwing a given message more than once in one file are collapsed onto a single row listing all line numbers. Messages embedded in exception-class constructors are marked *(ctor)*; messages passed through `report_nonnormative_()` / `on_failure_()` forwarding helpers are marked *(fwd)*.


## Classification columns

* **E/F** — the nature of the failure:
  * **prog err** — programmer error: the caller violated a contract (bad index, bad key, bad parameter, unsupported-by-contract input);
  * **run cond** — runtime failure condition: the operating environment declined (open failed, allocation failed, enumeration failed, …);
* **Right?** — rightness of the message *as written*, independent of E/F:
  * **✅** — right: grammatical, appropriately specific, consistent with the dominant house form;
  * **⚠️** — questionable: case/style drift from the house form, borderline verbosity, or arguably misclassified exception type;
  * **❌** — wrong: grammar defect, redundancy, or misleading content — should be rewritten regardless of any wider normalisation.

The dominant house form observed across the tree is lowercase `"failed to <verb> <object>"` for **run cond**, and a terse lowercase noun phrase (`"index out of range"`) for **prog err**. Verdicts below judge each message against *its own* class's dominant form.


## comstl

| Site | Message | E/F | Right? | Notes |
| --- | --- | --- | --- | --- |
| comstl/collections/collection_sequence.hpp:354 | the enumerator does not provide the requested interface | run cond | ⚠️ | descriptive but not house form; lacks leading verb |
| comstl/collections/collection_sequence.hpp:363 | enumerator could not be elicited from the collection | run cond | ⚠️ | "could not" form; cf. house "failed to" |
| comstl/collections/safearray_sequence.hpp:299 | initialising safearray_sequence from safe array to incompatible type | prog err | ⚠️ | verbose; names the component (good) but gerund form is one-off |
| comstl/exception/variant_type_exception.hpp:123 *(ctor)* | VARIANT type exception | run cond | ❌ | names the exception class in the message; no other message does this |
| comstl/string/bstr.hpp:511, 556, 569, 589, 617 | failed to allocate string | run cond | ✅ | house form |
| comstl/string/bstr.hpp:600 | Position out of range | prog err | ⚠️ | sentence-case; "Position" cf. "index" everywhere else |
| comstl/util/acyclic_connector.hpp:404 | Could not acquire left-side identity | run cond | ⚠️ | "Could not" form |
| comstl/util/acyclic_connector.hpp:416 | Could not acquire right-side identity | run cond | ⚠️ | "Could not" form |
| comstl/util/GUID_functions.h:509 | comparison failed | run cond | ⚠️ | terse but vague; subject unclear at catch site |
| comstl/util/guid.hpp:402 | Could not allocate GUID | run cond | ⚠️ | "Could not" form |
| comstl/util/guid.hpp:431, 445 | Could not convert string to valid GUID | prog err | ⚠️ | "Could not" form; E/F borderline (bad input string vs data) |
| comstl/util/value_policies.hpp:183 | failed to copy BSTR | run cond | ✅ | house form |
| comstl/util/value_policies.hpp:235 | failed to copy OLE string | run cond | ✅ | house form |
| comstl/util/value_policies.hpp:286 | failed to copy VARIANT | run cond | ✅ | house form |
| comstl/util/value_policies.hpp:446 | failed to copy OLE string when copying STATSTG | run cond | ✅ | house form + context |
| comstl/util/value_policies.hpp:503 | failed to copy DVTARGETDEVICE when copying FORMATETC | run cond | ✅ | house form + context |
| comstl/util/variant.hpp:886 | support for comparison of variant type not currently supported | prog err | ❌ | redundant ("support for … not … supported"); ungrammatical |


## mfcstl

| Site | Message | E/F | Right? | Notes |
| --- | --- | --- | --- | --- |
| mfcstl/collections/CArray_adaptors.hpp:579, 592 | Invalid index specified | prog err | ⚠️ | sentence-case + "specified"; cf. CString twin below |
| mfcstl/collections/CString_adaptors.hpp:1433, 1443 | invalid index | prog err | ✅ | terse house form; case-pair inconsistency with CArray twin |


## platformstl

| Site | Message | E/F | Right? | Notes |
| --- | --- | --- | --- | --- |
| platformstl/filesystem/FILE_stream.hpp:313 *(fwd)* | failed to flush file | run cond | ✅ | house form |
| platformstl/filesystem/FILE_stream.hpp:346 *(fwd)* | failed to tell file position | run cond | ✅ | house form |
| platformstl/filesystem/FILE_stream.hpp:398, 431 *(fwd)* | failed to open/create file | run cond | ✅ | house form; slash compound is fine |
| platformstl/filesystem/FILE_stream.hpp:497 *(fwd)* | failed to write bytes to file | run cond | ✅ | house form |
| platformstl/filesystem/FILE_stream.hpp:527 *(fwd)* | failed to write multibyte string to file | run cond | ✅ | house form |
| platformstl/filesystem/FILE_stream.hpp:557 *(fwd)* | failed to write wide string to file | run cond | ✅ | house form |
| platformstl/filesystem/FILE_stream.hpp:573 *(fwd)* | failed to seek | run cond | ✅ | house form |
| platformstl/filesystem/file_lines.hpp:425 | file is binary (or unsupported text encoding) | run cond | ⚠️ | declarative, not verb-led; parenthetical detail is one-off |
| platformstl/system/environment_map.hpp:624 | variable does not exist | prog err | ⚠️ | declarative; arguably fine, but inconsistent with "out of range" family |
| platformstl/system/environment_map.hpp:697, 720 | Cannot set environment variable | run cond | ⚠️ | "Cannot" form |
| platformstl/system/environment_map.hpp:767, 823 | Cannot erase environment variable | run cond | ⚠️ | "Cannot" form |


## rangelib

| Site | Message | E/F | Right? | Notes |
| --- | --- | --- | --- | --- |
| rangelib/algorithms.hpp:1159, 1211 | Cannot determine maximum element of empty range | prog err | ⚠️ | "Cannot" form; correct condition (empty range is caller error) |
| rangelib/algorithms.hpp:1315, 1367 | Cannot determine minimum element of empty range | prog err | ⚠️ | as above |
| rangelib/integral_range.hpp:155, 167, 204, 220 | Invalid integral range [%ld, %ld), %ld (and %lu / %s variants) | prog err | ⚠️ | only printf-format parameterised messages in the tree; sentence-case |


## stlsoft

| Site | Message | E/F | Right? | Notes |
| --- | --- | --- | --- | --- |
| stlsoft/collections/array_view.hpp:418 | array view index out of range | prog err | ✅ | class-prefixed house form |
| stlsoft/collections/functions.hpp:140, 173 | invalid key | prog err | ✅ | terse house form |
| stlsoft/containers/fixed_array.hpp:880, 1219, 1238, 1617, 1636, 2020, 2039 | fixed array index out of range | prog err | ✅ | class-prefixed house form |
| stlsoft/containers/pod_vector.hpp:431 | pod vector index out of range | prog err | ✅ | class-prefixed house form |
| stlsoft/containers/static_array.hpp:792, 1007, 1022, 1267, 1282, 1534, 1549 | static array index out of range | prog err | ✅ | class-prefixed house form |
| stlsoft/conversion/char_conversions.hpp:315 | failed to convert multibyte string to wide string | run cond | ✅ | house form |
| stlsoft/conversion/char_conversions.hpp:452 | failed to convert wide string to multibyte string | run cond | ✅ | house form |
| stlsoft/conversion/truncation_cast.hpp:126 | Cast would result in truncation | prog err | ⚠️ | sentence-case one-off; type (`std::overflow_error`) is right |
| stlsoft/error/iteration_interruption.hpp:117 *(ctor)* | "" (provider returns "iteration interruption") | prog err | ⚠️ | only class storing empty message and overriding the provider |
| stlsoft/string/simple_string.hpp:2473, 2538, 2609, 2616, 2632, 2683 | `basic_simple_string#equal()` index out of range | prog err | ⚠️ | `#` qualifier is a Ruby-ism; backticks in a runtime string |
| stlsoft/string/simple_string.hpp:3060, 3081, 3105, 3133, 3663 | index out of range | prog err | ✅ | bare house form |
| stlsoft/string/static_string.hpp:2460, 2481 | at(): `index` out of range | prog err | ⚠️ | `():` qualifier + backticks; inconsistent with `#` form above |
| stlsoft/string/static_string.hpp:2505, 2533 | substr(): `pos` out of range | prog err | ⚠️ | as above |
| stlsoft/string/string_view.hpp:1688, 1711, 1738 | index out of range | prog err | ✅ | bare house form |
| stlsoft/util/exception_string_creator.hpp:482 | failed to convert wide string to multibyte string | run cond | ✅ | house form |


## unixstl

| Site | Message | E/F | Right? | Notes |
| --- | --- | --- | --- | --- |
| unixstl/dl/module.hpp:334, 337 | Cannot load module | run cond | ⚠️ | "Cannot" form; consistent with winstl twin |
| unixstl/filesystem/memory_mapped_file.hpp:191 *(fwd)* | Failed to open file for mapping | run cond | ⚠️ | sentence-case "Failed to" family |
| unixstl/filesystem/memory_mapped_file.hpp:202 *(fwd)* | Failed to determine mapped file size | run cond | ⚠️ | sentence-case |
| unixstl/filesystem/memory_mapped_file.hpp:227 *(fwd)* | Failed to map view of file | run cond | ⚠️ | sentence-case |
| unixstl/filesystem/path.hpp:1732 | could not determine the absolute path | run cond | ⚠️ | lowercase "could not"; article "the" is one-off |
| unixstl/filesystem/readonly_memory_mapped_file.hpp:415 *(fwd)* | Failed to open file for mapping | run cond | ⚠️ | sentence-case |
| unixstl/filesystem/readonly_memory_mapped_file.hpp:425 *(fwd)* | Failed to determine mapped file size | run cond | ⚠️ | sentence-case |
| unixstl/filesystem/readonly_memory_mapped_file.hpp:449 *(fwd)* | Failed to map view of file | run cond | ⚠️ | sentence-case |
| unixstl/filesystem/readdir_sequence.hpp:631 | failed to obtain full path of search directory | run cond | ✅ | house form |
| unixstl/filesystem/readdir_sequence.hpp:709 | failed to enumerate directory | run cond | ✅ | house form |
| unixstl/filesystem/readdir_sequence.hpp:881 | failed to complete directory enumeration | run cond | ✅ | house form |
| unixstl/synch/process_mutex.hpp:227 | Mutex lock failed | run cond | ⚠️ | capitalised "Mutex"; cf. lowercase siblings below |
| unixstl/synch/process_mutex.hpp:253 | Mutex try-lock failed | run cond | ⚠️ | as above |
| unixstl/synch/process_mutex.hpp:273 | Mutex unlock failed | run cond | ⚠️ | as above |
| unixstl/synch/process_mutex.hpp:325 | failed to set process-sharing attribute for PTHREADS mutex | run cond | ✅ | house form |
| unixstl/synch/process_mutex.hpp:339 | failed to set initialise PTHREADS mutex | run cond | ❌ | broken phrase "set initialise" |
| unixstl/synch/process_mutex.hpp:347 | failed to set recursive attribute to PTHREADS mutex | run cond | ✅ | house form |
| unixstl/synch/process_mutex.hpp:354 | failed to initialise PTHREADS mutex attributes | run cond | ✅ | house form |
| unixstl/synch/semaphore.hpp:221, 239 | semaphore wait failed | run cond | ⚠️ | "<noun> <verb> failed" form, not "failed to" |
| unixstl/synch/semaphore.hpp:261 | semaphore release failed | run cond | ⚠️ | as above |
| unixstl/synch/semaphore.hpp:296 | failed to create kernel semaphore object | run cond | ✅ | house form |
| unixstl/synch/thread_mutex.hpp:189 | Mutex lock failed | run cond | ⚠️ | capitalised "Mutex" |
| unixstl/synch/thread_mutex.hpp:215 | Mutex try-lock failed | run cond | ⚠️ | as above |
| unixstl/synch/thread_mutex.hpp:235 | Mutex unlock failed | run cond | ⚠️ | as above |
| unixstl/synch/thread_mutex.hpp:289 | failed to set initialise PTHREADS mutex | run cond | ❌ | broken phrase "set initialise" |
| unixstl/synch/thread_mutex.hpp:296 | failed to set recursive attribute to PTHREADS mutex | run cond | ✅ | house form |
| unixstl/synch/thread_mutex.hpp:303 | failed to initialise PTHREADS mutex attributes | run cond | ✅ | house form |
| unixstl/synch/tss_index.hpp:144 *(ctor)* | Failed to allocate a TSS key | run cond | ⚠️ | sentence-case + article "a" |
| unixstl/system/pid_sequence.hpp:346 | could not open '/proc' | run cond | ⚠️ | "could not" + quoted path; only quoted-token message |


## winstl

| Site | Message | E/F | Right? | Notes |
| --- | --- | --- | --- | --- |
| winstl/clipboard/clipboard_scope.hpp:403 | Cannot open clipboard | run cond | ⚠️ | "Cannot" form |
| winstl/clipboard/clipboard_scope.hpp:423 | Cannot empty clipboard | run cond | ⚠️ | as above |
| winstl/clipboard/clipboard_scope.hpp:434 | Cannot get clipboard owner | run cond | ⚠️ | as above |
| winstl/clipboard/clipboard_scope.hpp:449 | Cannot set clipboard data | run cond | ⚠️ | as above |
| winstl/clipboard/clipboard_scope.hpp:550 | Cannot get clipboard data | run cond | ⚠️ | as above |
| winstl/control_panel/applet_module.hpp:511 | Applet initialisation failed | run cond | ⚠️ | sentence-case "<noun> failed" |
| winstl/control_panel/applet_module.hpp:536 | Could not load the applet icon | run cond | ⚠️ | "Could not" + article |
| winstl/control_panel/applet_module.hpp:748 | Control panel entry point not found | run cond | ⚠️ | declarative, sentence-case |
| winstl/controls/listbox_const_iterator.hpp:216, 227, 400, 411 | external iterator invalidation: control contents may have been altered externally | run cond | ⚠️ | colon-compound; repeats the exception class name |
| winstl/conversion/char_conversions.hpp:235, 393 | failed to convert multibyte string to wide string | run cond | ✅ | house form |
| winstl/dl/module.hpp:392 | Cannot load module | run cond | ⚠️ | "Cannot" form; consistent with unixstl twin |
| winstl/dl/module.hpp:542 | Cannot get module path | run cond | ⚠️ | as above |
| winstl/filesystem/current_directory_scope.hpp:334 | could not determine current directory | run cond | ⚠️ | lowercase "could not" |
| winstl/filesystem/current_directory_scope.hpp:344 | could not change current directory | run cond | ⚠️ | as above |
| winstl/filesystem/file_functions.hpp:240 | File does not exist | run cond | ⚠️ | declarative, sentence-case |
| winstl/filesystem/file_functions.hpp:250 | Cannot read in files larger than 4GB | run cond | ❌ | thrown as `std::out_of_range` — type/message mismatch; "read in" awkward |
| winstl/filesystem/file_functions.hpp:269 | Read operation failed | run cond | ⚠️ | sentence-case "<noun> failed" |
| winstl/filesystem/findfile_sequence.hpp:1612 | Could not execute search | run cond | ⚠️ | "Could not" form; type is `access_exception` (questionable) |
| winstl/filesystem/memory_mapped_file.hpp:256 *(fwd)* | Failed to open file for mapping | run cond | ⚠️ | sentence-case |
| winstl/filesystem/memory_mapped_file.hpp:270 *(fwd)* | Failed to determine mapped file size | run cond | ⚠️ | sentence-case |
| winstl/filesystem/memory_mapped_file.hpp:282 *(fwd)* | Requested region exceeds the available address space | prog err | ⚠️ | sentence-case; correct E/F (caller-supplied region) |
| winstl/filesystem/memory_mapped_file.hpp:292 *(fwd)* | Region out of range | prog err | ⚠️ | sentence-case |
| winstl/filesystem/memory_mapped_file.hpp:318 *(fwd)* | Region size too large | prog err | ⚠️ | sentence-case |
| winstl/filesystem/memory_mapped_file.hpp:373 *(fwd)* | Failed to open file mapping | run cond | ⚠️ | sentence-case; cf. ":256" twin ("for mapping" vs "mapping") |
| winstl/filesystem/memory_mapped_file.hpp:418, 424 *(fwd)* | Failed to map view of file | run cond | ⚠️ | sentence-case |
| winstl/filesystem/path.hpp:1998 | could not determine the absolute path | run cond | ⚠️ | identical to unixstl twin (consistent) |
| winstl/memory/shell_allocator.hpp:226 | failed to retrieve the shell allocator | run cond | ✅ | house form |
| winstl/registry/reg_key_sequence.hpp:769, 787, 806, 955 | failed to take duplicate of key | run cond | ✅ | house form |
| winstl/registry/reg_value_sequence.hpp:733, 751, 770, 919 | failed to take duplicate of key | run cond | ✅ | house form |
| winstl/registry/util/shared_handles.hpp:271 | registry contents changed | run cond | ⚠️ | declarative; terse but not house form |
| winstl/registry/util/shared_handles.hpp:291 | could not register change notification | run cond | ⚠️ | lowercase "could not" |
| winstl/shims/access/string/time.hpp:171, 207 | failed to convert date/time | run cond | ✅ | house form |
| winstl/shims/conversion/to_DATE/SYSTEMTIME.hpp:147 | failed to convert time value | run cond | ✅ | house form |
| winstl/shims/conversion/to_FILETIME/SYSTEMTIME.hpp:133 | failed to convert time value | run cond | ✅ | house form |
| winstl/shims/conversion/to_SYSTEMTIME/DATE.hpp:143 | failed to convert time value | run cond | ✅ | house form |
| winstl/shims/conversion/to_SYSTEMTIME/FILETIME.hpp:133 | failed to convert time value | run cond | ✅ | house form |
| winstl/synch/event.hpp:177 | event set operation failed | run cond | ⚠️ | "<noun> failed" form |
| winstl/synch/event.hpp:193 | event reset operation failed | run cond | ⚠️ | as above |
| winstl/synch/event.hpp:227, 244 | failed to create kernel event object | run cond | ✅ | house form |
| winstl/synch/event.hpp:338 | event wait failed | run cond | ⚠️ | "<noun> failed" form |
| winstl/synch/exceptions.hpp:437 *(ctor)* | invalid wait handle | prog err | ✅ | terse house form |
| winstl/synch/exceptions.hpp:514 *(ctor)* | duplicate wait handles | prog err | ✅ | terse house form |
| winstl/synch/exceptions.hpp:558 *(ctor)* | too many wait handles | prog err | ✅ | terse house form |
| winstl/synch/process_mutex.hpp:288, 328 | mutex wait failed | run cond | ⚠️ | "<noun> failed" form; lowercase here, capitalised in unixstl twins |
| winstl/synch/process_mutex.hpp:355 | mutex release failed | run cond | ⚠️ | as above |
| winstl/synch/process_mutex.hpp:415, 434 | failed to create kernel mutex object | run cond | ✅ | house form |
| winstl/synch/process_mutex.hpp:453, 472 | failed to open kernel mutex object | run cond | ✅ | house form |
| winstl/synch/semaphore.hpp:223, 242 | semaphore wait failed | run cond | ⚠️ | "<noun> failed" form |
| winstl/synch/semaphore.hpp:270, 301 | semaphore release failed | run cond | ⚠️ | as above |
| winstl/synch/semaphore.hpp:367, 392 | failed to create kernel semaphore object | run cond | ✅ | house form |
| winstl/synch/tss_index.hpp:232 | could not allocate a TSS key | run cond | ⚠️ | lowercase "could not" + article; cf. unixstl ctor twin (sentence-case) |
| winstl/system/console_colour_scope.hpp:172 | Could not retrieve console buffer information | run cond | ⚠️ | "Could not" form |
| winstl/system/console_colour_scope.hpp:180 | Could not set console text attributes | run cond | ⚠️ | as above |
| winstl/system/pid_sequence.hpp:332 | Failed to enumerate processes | run cond | ⚠️ | sentence-case |
| winstl/system/process_module_sequence.hpp:268 | Failed to enumerate processes | run cond | ⚠️ | sentence-case |
| winstl/system/temporary_file_name.hpp:201, 266 | could not elicit temporary directory | run cond | ⚠️ | lowercase "could not" |
| winstl/system/temporary_file_name.hpp:220, 285 | could not elicit temporary file name | run cond | ⚠️ | as above |
| winstl/system/version_info.hpp:1337, 1427 | Could not obtain executing module path | run cond | ⚠️ | "Could not" form |
| winstl/system/version_info.hpp:1358, 1394, 1448, 1480 | Could not elicit version information from module | run cond | ⚠️ | "Could not" form |
| winstl/time/comparison_functions.h:575, 603, 647, 692, 737 | failed to convert time value | run cond | ✅ | house form |
| winstl/time/localisation_functions.h:343, 387 | failed to convert time value | run cond | ✅ | house form |
| winstl/time/time_cast.hpp:182, 206 | failed to convert time value | run cond | ✅ | house form |
| winstl/window/zorder_iterator.hpp:360 | z-order search failed: window has been destroyed | run cond | ⚠️ | colon-compound (one of only two) |


## Message-free exception types

| Type / site | E/F | Right? | Notes |
| --- | --- | --- | --- |
| `out_of_memory_exception` (FILE_stream.hpp, memory_mapped_file.hpp ×2, readdir_sequence.hpp) | run cond | ✅ | identified by `STLSoftProjectIdentifier_*` / `STLSoftLibraryIdentifier_*` enums, not strings — deliberate design |
| `missing_entry_point_exception(functionName, sc)` (winstl/dl/dl_call.hpp:656; unixstl/dl/dl_call.hpp:359) | run cond | ✅ | function name carried as field |
| `invalid_calling_convention_exception(s)` (winstl/dl/dl_call.hpp:711) | prog err | ✅ | description carried as field |
| `winstl_exception(le)` status-only (winstl/filesystem/findfile_sequence.hpp:1166) | run cond | ⚠️ | no message at all — catch site learns nothing beyond the status code |
| `throw_policies.hpp` families (inetstl, unixstl, winstl) | n/a | ✅ | message forwarded from caller by design |
| `rangelib/integral_range.hpp` `thrown_type(message)` sites | prog err | ✅ | formatted from the `s_format` / `s_fmtfmt` strings above |


## Inconsistency summary

1. **Case** — sentence-case (`"Failed to enumerate processes"`, `"Position out of range"`, `"Invalid index specified"`) vs lowercase (`"failed to take duplicate of key"`, `"invalid index"`), split roughly evenly across ~200 sites; worst pairs share identical semantics (`"Invalid index specified"` vs `"invalid index"`; capitalised `"Mutex lock failed"` adjacent to lowercase `"failed to set recursive attribute …"` in the same file);
2. **Verb form** — five conventions coexist for the same run-cond meaning: `"failed to X"` (dominant), `"Failed to X"`, `"Cannot X"`, `"Could not X"`, `"could not X"`; e.g. `"Could not elicit version information from module"` vs `"could not elicit temporary file name"`;
3. **Qualifier syntax (prog err)** — `#` (`` `basic_simple_string#equal()` ``) vs `():` (`at(): \`index\``) vs class prefix (`"fixed array index out of range"`) vs bare (`"index out of range"`); backticks appear in runtime strings only in stlsoft/string;
4. **Grammar defects (❌)** — `"failed to set initialise PTHREADS mutex"` ×2 (unixstl/synch/process_mutex.hpp:339, thread_mutex.hpp:289); `"support for comparison of variant type not currently supported"` (comstl/util/variant.hpp:886); `"VARIANT type exception"` names the exception class in its own message (comstl/exception/variant_type_exception.hpp:123);
5. **Type/message mismatch (❌)** — `"Cannot read in files larger than 4GB"` thrown as `std::out_of_range` (winstl/filesystem/file_functions.hpp:250);
6. **Form outliers** — empty stored message with provider override (stlsoft/error/iteration_interruption.hpp); two colon-compound sentences (listbox_const_iterator, zorder_iterator); one quoted token (`"could not open '/proc'"`); one parenthetical (`"file is binary (or unsupported text encoding)"`); printf-format strings (rangelib/integral_range.hpp);
7. **Twin drift** — cross-platform twin components mostly agree (`"Cannot load module"`, `"could not determine the absolute path"`) but TSS-key messages diverge (`"Failed to allocate a TSS key"` ctor vs `"could not allocate a TSS key"` throw-site), and unixstl capitalises `"Mutex … failed"` where winstl lowercases `"mutex … failed"`.


## Verdict tallies

| Verdict | Count (unique messages) | Share |
| --- | --- | --- |
| ✅ right | ~50 | ~35% |
| ⚠️ questionable | ~85 | ~60% |
| ❌ wrong | 5 | ~4% |


## Recommendation

Adopt one house form per class and normalise in a single dedicated pass (not mixed into feature work):

* **run cond** — lowercase `"failed to <verb> <object>"` (already the plurality and the form of the newest code);
* **prog err** — bare or class-prefixed lowercase noun phrase (`"index out of range"`, `"fixed array index out of range"`); drop `#` / `():` qualifiers and backticks;
* fix the five ❌ messages immediately, independently of the wider pass;
* leave `integral_range` printf formats and the identifier-based `out_of_memory_exception` alone — they are deliberate designs, not drift.


<!-- ########################### end of file ########################### -->
