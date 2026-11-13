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
| [comstl/collections/collection_sequence.hpp:354](../include/comstl/collections/collection_sequence.hpp#L354) | the enumerator does not provide the requested interface | run cond | ⚠️ | descriptive but not house form; lacks leading verb |
| [comstl/collections/collection_sequence.hpp:363](../include/comstl/collections/collection_sequence.hpp#L363) | enumerator could not be elicited from the collection | run cond | ⚠️ | "could not" form; cf. house "failed to" |
| [comstl/collections/safearray_sequence.hpp:299](../include/comstl/collections/safearray_sequence.hpp#L299) | initialising safearray_sequence from safe array to incompatible type | prog err | ⚠️ | verbose; names the component (good) but gerund form is one-off |
| [comstl/exception/variant_type_exception.hpp:123](../include/comstl/exception/variant_type_exception.hpp#L123)*(ctor)* | VARIANT type exception | run cond | ❌ | names the exception class in the message; no other message does this |
| [comstl/string/bstr.hpp:511](../include/comstl/string/bstr.hpp#L511), [556](../include/comstl/string/bstr.hpp#L556), [569](../include/comstl/string/bstr.hpp#L569), [589](../include/comstl/string/bstr.hpp#L589), [617](../include/comstl/string/bstr.hpp#L617) | failed to allocate string | run cond | ✅ | house form |
| [comstl/string/bstr.hpp:600](../include/comstl/string/bstr.hpp#L600) | Position out of range | prog err | ⚠️ | sentence-case; "Position" cf. "index" everywhere else |
| [comstl/util/acyclic_connector.hpp:404](../include/comstl/util/acyclic_connector.hpp#L404) | Could not acquire left-side identity | run cond | ⚠️ | "Could not" form |
| [comstl/util/acyclic_connector.hpp:416](../include/comstl/util/acyclic_connector.hpp#L416) | Could not acquire right-side identity | run cond | ⚠️ | "Could not" form |
| [comstl/util/GUID_functions.h:509](../include/comstl/util/GUID_functions.h#L509) | comparison failed | run cond | ⚠️ | terse but vague; subject unclear at catch site |
| [comstl/util/guid.hpp:402](../include/comstl/util/guid.hpp#L402) | Could not allocate GUID | run cond | ⚠️ | "Could not" form |
| [comstl/util/guid.hpp:431](../include/comstl/util/guid.hpp#L431), [445](../include/comstl/util/guid.hpp#L445) | Could not convert string to valid GUID | prog err | ⚠️ | "Could not" form; E/F borderline (bad input string vs data) |
| [comstl/util/value_policies.hpp:183](../include/comstl/util/value_policies.hpp#L183) | failed to copy BSTR | run cond | ✅ | house form |
| [comstl/util/value_policies.hpp:235](../include/comstl/util/value_policies.hpp#L235) | failed to copy OLE string | run cond | ✅ | house form |
| [comstl/util/value_policies.hpp:286](../include/comstl/util/value_policies.hpp#L286) | failed to copy VARIANT | run cond | ✅ | house form |
| [comstl/util/value_policies.hpp:446](../include/comstl/util/value_policies.hpp#L446) | failed to copy OLE string when copying STATSTG | run cond | ✅ | house form + context |
| [comstl/util/value_policies.hpp:503](../include/comstl/util/value_policies.hpp#L503) | failed to copy DVTARGETDEVICE when copying FORMATETC | run cond | ✅ | house form + context |
| [comstl/util/variant.hpp:886](../include/comstl/util/variant.hpp#L886) | support for comparison of variant type not currently supported | prog err | ❌ | redundant ("support for … not … supported"); ungrammatical |


## mfcstl

| Site | Message | E/F | Right? | Notes |
| --- | --- | --- | --- | --- |
| [mfcstl/collections/CArray_adaptors.hpp:579](../include/mfcstl/collections/CArray_adaptors.hpp#L579), [592](../include/mfcstl/collections/CArray_adaptors.hpp#L592) | Invalid index specified | prog err | ⚠️ | sentence-case + "specified"; cf. CString twin below |
| [mfcstl/collections/CString_adaptors.hpp:1433](../include/mfcstl/collections/CString_adaptors.hpp#L1433), [1443](../include/mfcstl/collections/CString_adaptors.hpp#L1443) | invalid index | prog err | ✅ | terse house form; case-pair inconsistency with CArray twin |


## platformstl

| Site | Message | E/F | Right? | Notes |
| --- | --- | --- | --- | --- |
| [platformstl/filesystem/FILE_stream.hpp:313](../include/platformstl/filesystem/FILE_stream.hpp#L313)*(fwd)* | failed to flush file | run cond | ✅ | house form |
| [platformstl/filesystem/FILE_stream.hpp:346](../include/platformstl/filesystem/FILE_stream.hpp#L346)*(fwd)* | failed to tell file position | run cond | ✅ | house form |
| [platformstl/filesystem/FILE_stream.hpp:398](../include/platformstl/filesystem/FILE_stream.hpp#L398), [431](../include/platformstl/filesystem/FILE_stream.hpp#L431)*(fwd)* | failed to open/create file | run cond | ✅ | house form; slash compound is fine |
| [platformstl/filesystem/FILE_stream.hpp:497](../include/platformstl/filesystem/FILE_stream.hpp#L497)*(fwd)* | failed to write bytes to file | run cond | ✅ | house form |
| [platformstl/filesystem/FILE_stream.hpp:527](../include/platformstl/filesystem/FILE_stream.hpp#L527)*(fwd)* | failed to write multibyte string to file | run cond | ✅ | house form |
| [platformstl/filesystem/FILE_stream.hpp:557](../include/platformstl/filesystem/FILE_stream.hpp#L557)*(fwd)* | failed to write wide string to file | run cond | ✅ | house form |
| [platformstl/filesystem/FILE_stream.hpp:573](../include/platformstl/filesystem/FILE_stream.hpp#L573)*(fwd)* | failed to seek | run cond | ✅ | house form |
| [platformstl/filesystem/file_lines.hpp:425](../include/platformstl/filesystem/file_lines.hpp#L425) | file is binary (or unsupported text encoding) | run cond | ⚠️ | declarative, not verb-led; parenthetical detail is one-off |
| [platformstl/system/environment_map.hpp:624](../include/platformstl/system/environment_map.hpp#L624) | variable does not exist | prog err | ⚠️ | declarative; arguably fine, but inconsistent with "out of range" family |
| [platformstl/system/environment_map.hpp:697](../include/platformstl/system/environment_map.hpp#L697), [720](../include/platformstl/system/environment_map.hpp#L720) | Cannot set environment variable | run cond | ⚠️ | "Cannot" form |
| [platformstl/system/environment_map.hpp:767](../include/platformstl/system/environment_map.hpp#L767), [823](../include/platformstl/system/environment_map.hpp#L823) | Cannot erase environment variable | run cond | ⚠️ | "Cannot" form |


## rangelib

| Site | Message | E/F | Right? | Notes |
| --- | --- | --- | --- | --- |
| [rangelib/algorithms.hpp:1159](../include/rangelib/algorithms.hpp#L1159), [1211](../include/rangelib/algorithms.hpp#L1211) | Cannot determine maximum element of empty range | prog err | ⚠️ | "Cannot" form; correct condition (empty range is caller error) |
| [rangelib/algorithms.hpp:1315](../include/rangelib/algorithms.hpp#L1315), [1367](../include/rangelib/algorithms.hpp#L1367) | Cannot determine minimum element of empty range | prog err | ⚠️ | as above |
| [rangelib/integral_range.hpp:155](../include/rangelib/integral_range.hpp#L155), [167](../include/rangelib/integral_range.hpp#L167), [204](../include/rangelib/integral_range.hpp#L204), [220](../include/rangelib/integral_range.hpp#L220) | Invalid integral range [%ld, %ld), %ld (and %lu / %s variants) | prog err | ⚠️ | only printf-format parameterised messages in the tree; sentence-case |


## stlsoft

| Site | Message | E/F | Right? | Notes |
| --- | --- | --- | --- | --- |
| [stlsoft/collections/array_view.hpp:418](../include/stlsoft/collections/array_view.hpp#L418) | array view index out of range | prog err | ✅ | class-prefixed house form |
| [stlsoft/collections/functions.hpp:140](../include/stlsoft/collections/functions.hpp#L140), [173](../include/stlsoft/collections/functions.hpp#L173) | invalid key | prog err | ✅ | terse house form |
| [stlsoft/containers/fixed_array.hpp:880](../include/stlsoft/containers/fixed_array.hpp#L880), [1219](../include/stlsoft/containers/fixed_array.hpp#L1219), [1238](../include/stlsoft/containers/fixed_array.hpp#L1238), [1617](../include/stlsoft/containers/fixed_array.hpp#L1617), [1636](../include/stlsoft/containers/fixed_array.hpp#L1636), [2020](../include/stlsoft/containers/fixed_array.hpp#L2020), [2039](../include/stlsoft/containers/fixed_array.hpp#L2039) | fixed array index out of range | prog err | ✅ | class-prefixed house form |
| [stlsoft/containers/pod_vector.hpp:431](../include/stlsoft/containers/pod_vector.hpp#L431) | pod vector index out of range | prog err | ✅ | class-prefixed house form |
| [stlsoft/containers/static_array.hpp:792](../include/stlsoft/containers/static_array.hpp#L792), [1007](../include/stlsoft/containers/static_array.hpp#L1007), [1022](../include/stlsoft/containers/static_array.hpp#L1022), [1267](../include/stlsoft/containers/static_array.hpp#L1267), [1282](../include/stlsoft/containers/static_array.hpp#L1282), [1534](../include/stlsoft/containers/static_array.hpp#L1534), [1549](../include/stlsoft/containers/static_array.hpp#L1549) | static array index out of range | prog err | ✅ | class-prefixed house form |
| [stlsoft/conversion/char_conversions.hpp:315](../include/stlsoft/conversion/char_conversions.hpp#L315) | failed to convert multibyte string to wide string | run cond | ✅ | house form |
| [stlsoft/conversion/char_conversions.hpp:452](../include/stlsoft/conversion/char_conversions.hpp#L452) | failed to convert wide string to multibyte string | run cond | ✅ | house form |
| [stlsoft/conversion/truncation_cast.hpp:126](../include/stlsoft/conversion/truncation_cast.hpp#L126) | Cast would result in truncation | prog err | ⚠️ | sentence-case one-off; type (`std::overflow_error`) is right |
| [stlsoft/error/iteration_interruption.hpp:117](../include/stlsoft/error/iteration_interruption.hpp#L117)*(ctor)* | "" (provider returns "iteration interruption") | run cond | ⚠️ | only class storing empty message and overriding the provider |
| [stlsoft/string/simple_string.hpp:2473](../include/stlsoft/string/simple_string.hpp#L2473), [2538](../include/stlsoft/string/simple_string.hpp#L2538), [2609](../include/stlsoft/string/simple_string.hpp#L2609), [2616](../include/stlsoft/string/simple_string.hpp#L2616), [2632](../include/stlsoft/string/simple_string.hpp#L2632), [2683](../include/stlsoft/string/simple_string.hpp#L2683) | `basic_simple_string#equal()` index out of range | prog err | ⚠️ | `#` qualifier is a Ruby-ism; backticks in a runtime string |
| [stlsoft/string/simple_string.hpp:3060](../include/stlsoft/string/simple_string.hpp#L3060), [3081](../include/stlsoft/string/simple_string.hpp#L3081), [3105](../include/stlsoft/string/simple_string.hpp#L3105), [3133](../include/stlsoft/string/simple_string.hpp#L3133), [3663](../include/stlsoft/string/simple_string.hpp#L3663) | index out of range | prog err | ✅ | bare house form |
| [stlsoft/string/static_string.hpp:2460](../include/stlsoft/string/static_string.hpp#L2460), [2481](../include/stlsoft/string/static_string.hpp#L2481) | at(): `index` out of range | prog err | ⚠️ | `():` qualifier + backticks; inconsistent with `#` form above |
| [stlsoft/string/static_string.hpp:2505](../include/stlsoft/string/static_string.hpp#L2505), [2533](../include/stlsoft/string/static_string.hpp#L2533) | substr(): `pos` out of range | prog err | ⚠️ | as above |
| [stlsoft/string/string_view.hpp:1688](../include/stlsoft/string/string_view.hpp#L1688), [1711](../include/stlsoft/string/string_view.hpp#L1711), [1738](../include/stlsoft/string/string_view.hpp#L1738) | index out of range | prog err | ✅ | bare house form |
| [stlsoft/util/exception_string_creator.hpp:482](../include/stlsoft/util/exception_string_creator.hpp#L482) | failed to convert wide string to multibyte string | run cond | ✅ | house form |


## unixstl

| Site | Message | E/F | Right? | Notes |
| --- | --- | --- | --- | --- |
| [unixstl/dl/module.hpp:334](../include/unixstl/dl/module.hpp#L334), [337](../include/unixstl/dl/module.hpp#L337) | Cannot load module | run cond | ⚠️ | "Cannot" form; consistent with winstl twin |
| [unixstl/filesystem/memory_mapped_file.hpp:191](../include/unixstl/filesystem/memory_mapped_file.hpp#L191)*(fwd)* | Failed to open file for mapping | run cond | ⚠️ | sentence-case "Failed to" family |
| [unixstl/filesystem/memory_mapped_file.hpp:202](../include/unixstl/filesystem/memory_mapped_file.hpp#L202)*(fwd)* | Failed to determine mapped file size | run cond | ⚠️ | sentence-case |
| [unixstl/filesystem/memory_mapped_file.hpp:227](../include/unixstl/filesystem/memory_mapped_file.hpp#L227)*(fwd)* | Failed to map view of file | run cond | ⚠️ | sentence-case |
| [unixstl/filesystem/path.hpp:1732](../include/unixstl/filesystem/path.hpp#L1732) | could not determine the absolute path | run cond | ⚠️ | lowercase "could not"; article "the" is one-off |
| [unixstl/filesystem/readonly_memory_mapped_file.hpp:415](../include/unixstl/filesystem/readonly_memory_mapped_file.hpp#L415)*(fwd)* | Failed to open file for mapping | run cond | ⚠️ | sentence-case |
| [unixstl/filesystem/readonly_memory_mapped_file.hpp:425](../include/unixstl/filesystem/readonly_memory_mapped_file.hpp#L425)*(fwd)* | Failed to determine mapped file size | run cond | ⚠️ | sentence-case |
| [unixstl/filesystem/readonly_memory_mapped_file.hpp:449](../include/unixstl/filesystem/readonly_memory_mapped_file.hpp#L449)*(fwd)* | Failed to map view of file | run cond | ⚠️ | sentence-case |
| [unixstl/filesystem/readdir_sequence.hpp:631](../include/unixstl/filesystem/readdir_sequence.hpp#L631) | failed to obtain full path of search directory | run cond | ✅ | house form |
| [unixstl/filesystem/readdir_sequence.hpp:709](../include/unixstl/filesystem/readdir_sequence.hpp#L709) | failed to enumerate directory | run cond | ✅ | house form |
| [unixstl/filesystem/readdir_sequence.hpp:881](../include/unixstl/filesystem/readdir_sequence.hpp#L881) | failed to complete directory enumeration | run cond | ✅ | house form |
| [unixstl/synch/process_mutex.hpp:227](../include/unixstl/synch/process_mutex.hpp#L227) | Mutex lock failed | run cond | ⚠️ | capitalised "Mutex"; cf. lowercase siblings below |
| [unixstl/synch/process_mutex.hpp:253](../include/unixstl/synch/process_mutex.hpp#L253) | Mutex try-lock failed | run cond | ⚠️ | as above |
| [unixstl/synch/process_mutex.hpp:273](../include/unixstl/synch/process_mutex.hpp#L273) | Mutex unlock failed | run cond | ⚠️ | as above |
| [unixstl/synch/process_mutex.hpp:325](../include/unixstl/synch/process_mutex.hpp#L325) | failed to set process-sharing attribute for PTHREADS mutex | run cond | ✅ | house form |
| [unixstl/synch/process_mutex.hpp:339](../include/unixstl/synch/process_mutex.hpp#L339) | failed to set initialise PTHREADS mutex | run cond | ❌ | broken phrase "set initialise" |
| [unixstl/synch/process_mutex.hpp:347](../include/unixstl/synch/process_mutex.hpp#L347) | failed to set recursive attribute to PTHREADS mutex | run cond | ✅ | house form |
| [unixstl/synch/process_mutex.hpp:354](../include/unixstl/synch/process_mutex.hpp#L354) | failed to initialise PTHREADS mutex attributes | run cond | ✅ | house form |
| [unixstl/synch/semaphore.hpp:221](../include/unixstl/synch/semaphore.hpp#L221), [239](../include/unixstl/synch/semaphore.hpp#L239) | semaphore wait failed | run cond | ⚠️ | "<noun> <verb> failed" form, not "failed to" |
| [unixstl/synch/semaphore.hpp:261](../include/unixstl/synch/semaphore.hpp#L261) | semaphore release failed | run cond | ⚠️ | as above |
| [unixstl/synch/semaphore.hpp:296](../include/unixstl/synch/semaphore.hpp#L296) | failed to create kernel semaphore object | run cond | ✅ | house form |
| [unixstl/synch/thread_mutex.hpp:189](../include/unixstl/synch/thread_mutex.hpp#L189) | Mutex lock failed | run cond | ⚠️ | capitalised "Mutex" |
| [unixstl/synch/thread_mutex.hpp:215](../include/unixstl/synch/thread_mutex.hpp#L215) | Mutex try-lock failed | run cond | ⚠️ | as above |
| [unixstl/synch/thread_mutex.hpp:235](../include/unixstl/synch/thread_mutex.hpp#L235) | Mutex unlock failed | run cond | ⚠️ | as above |
| [unixstl/synch/thread_mutex.hpp:289](../include/unixstl/synch/thread_mutex.hpp#L289) | failed to set initialise PTHREADS mutex | run cond | ❌ | broken phrase "set initialise" |
| [unixstl/synch/thread_mutex.hpp:296](../include/unixstl/synch/thread_mutex.hpp#L296) | failed to set recursive attribute to PTHREADS mutex | run cond | ✅ | house form |
| [unixstl/synch/thread_mutex.hpp:303](../include/unixstl/synch/thread_mutex.hpp#L303) | failed to initialise PTHREADS mutex attributes | run cond | ✅ | house form |
| [unixstl/synch/tss_index.hpp:144](../include/unixstl/synch/tss_index.hpp#L144)*(ctor)* | Failed to allocate a TSS key | run cond | ⚠️ | sentence-case + article "a" |
| [unixstl/system/pid_sequence.hpp:346](../include/unixstl/system/pid_sequence.hpp#L346) | could not open '/proc' | run cond | ⚠️ | "could not" + quoted path; only quoted-token message |


## winstl

| Site | Message | E/F | Right? | Notes |
| --- | --- | --- | --- | --- |
| [winstl/clipboard/clipboard_scope.hpp:403](../include/winstl/clipboard/clipboard_scope.hpp#L403) | Cannot open clipboard | run cond | ⚠️ | "Cannot" form |
| [winstl/clipboard/clipboard_scope.hpp:423](../include/winstl/clipboard/clipboard_scope.hpp#L423) | Cannot empty clipboard | run cond | ⚠️ | as above |
| [winstl/clipboard/clipboard_scope.hpp:434](../include/winstl/clipboard/clipboard_scope.hpp#L434) | Cannot get clipboard owner | run cond | ⚠️ | as above |
| [winstl/clipboard/clipboard_scope.hpp:449](../include/winstl/clipboard/clipboard_scope.hpp#L449) | Cannot set clipboard data | run cond | ⚠️ | as above |
| [winstl/clipboard/clipboard_scope.hpp:550](../include/winstl/clipboard/clipboard_scope.hpp#L550) | Cannot get clipboard data | run cond | ⚠️ | as above |
| [winstl/control_panel/applet_module.hpp:511](../include/winstl/control_panel/applet_module.hpp#L511) | Applet initialisation failed | run cond | ⚠️ | sentence-case "<noun> failed" |
| [winstl/control_panel/applet_module.hpp:536](../include/winstl/control_panel/applet_module.hpp#L536) | Could not load the applet icon | run cond | ⚠️ | "Could not" + article |
| [winstl/control_panel/applet_module.hpp:748](../include/winstl/control_panel/applet_module.hpp#L748) | Control panel entry point not found | run cond | ⚠️ | declarative, sentence-case |
| [winstl/controls/listbox_const_iterator.hpp:216](../include/winstl/controls/listbox_const_iterator.hpp#L216), [227](../include/winstl/controls/listbox_const_iterator.hpp#L227), [400](../include/winstl/controls/listbox_const_iterator.hpp#L400), [411](../include/winstl/controls/listbox_const_iterator.hpp#L411) | external iterator invalidation: control contents may have been altered externally | run cond | ⚠️ | colon-compound; repeats the exception class name |
| [winstl/conversion/char_conversions.hpp:235](../include/winstl/conversion/char_conversions.hpp#L235), [393](../include/winstl/conversion/char_conversions.hpp#L393) | failed to convert multibyte string to wide string | run cond | ✅ | house form |
| [winstl/dl/module.hpp:392](../include/winstl/dl/module.hpp#L392) | Cannot load module | run cond | ⚠️ | "Cannot" form; consistent with unixstl twin |
| [winstl/dl/module.hpp:542](../include/winstl/dl/module.hpp#L542) | Cannot get module path | run cond | ⚠️ | as above |
| [winstl/filesystem/current_directory_scope.hpp:334](../include/winstl/filesystem/current_directory_scope.hpp#L334) | could not determine current directory | run cond | ⚠️ | lowercase "could not" |
| [winstl/filesystem/current_directory_scope.hpp:344](../include/winstl/filesystem/current_directory_scope.hpp#L344) | could not change current directory | run cond | ⚠️ | as above |
| [winstl/filesystem/file_functions.hpp:240](../include/winstl/filesystem/file_functions.hpp#L240) | File does not exist | run cond | ⚠️ | declarative, sentence-case |
| [winstl/filesystem/file_functions.hpp:250](../include/winstl/filesystem/file_functions.hpp#L250) | Cannot read in files larger than 4GB | run cond | ❌ | thrown as `std::out_of_range` — type/message mismatch; "read in" awkward |
| [winstl/filesystem/file_functions.hpp:269](../include/winstl/filesystem/file_functions.hpp#L269) | Read operation failed | run cond | ⚠️ | sentence-case "<noun> failed" |
| [winstl/filesystem/findfile_sequence.hpp:1612](../include/winstl/filesystem/findfile_sequence.hpp#L1612) | Could not execute search | run cond | ⚠️ | "Could not" form; type is `access_exception` (questionable) |
| [winstl/filesystem/memory_mapped_file.hpp:256](../include/winstl/filesystem/memory_mapped_file.hpp#L256)*(fwd)* | Failed to open file for mapping | run cond | ⚠️ | sentence-case |
| [winstl/filesystem/memory_mapped_file.hpp:270](../include/winstl/filesystem/memory_mapped_file.hpp#L270)*(fwd)* | Failed to determine mapped file size | run cond | ⚠️ | sentence-case |
| [winstl/filesystem/memory_mapped_file.hpp:282](../include/winstl/filesystem/memory_mapped_file.hpp#L282)*(fwd)* | Requested region exceeds the available address space | prog err | ⚠️ | sentence-case; correct E/F (caller-supplied region) |
| [winstl/filesystem/memory_mapped_file.hpp:292](../include/winstl/filesystem/memory_mapped_file.hpp#L292)*(fwd)* | Region out of range | prog err | ⚠️ | sentence-case |
| [winstl/filesystem/memory_mapped_file.hpp:318](../include/winstl/filesystem/memory_mapped_file.hpp#L318)*(fwd)* | Region size too large | prog err | ⚠️ | sentence-case |
| [winstl/filesystem/memory_mapped_file.hpp:373](../include/winstl/filesystem/memory_mapped_file.hpp#L373)*(fwd)* | Failed to open file mapping | run cond | ⚠️ | sentence-case; cf. ":256" twin ("for mapping" vs "mapping") |
| [winstl/filesystem/memory_mapped_file.hpp:418](../include/winstl/filesystem/memory_mapped_file.hpp#L418), [424](../include/winstl/filesystem/memory_mapped_file.hpp#L424)*(fwd)* | Failed to map view of file | run cond | ⚠️ | sentence-case |
| [winstl/filesystem/path.hpp:1998](../include/winstl/filesystem/path.hpp#L1998) | could not determine the absolute path | run cond | ⚠️ | identical to unixstl twin (consistent) |
| [winstl/memory/shell_allocator.hpp:226](../include/winstl/memory/shell_allocator.hpp#L226) | failed to retrieve the shell allocator | run cond | ✅ | house form |
| [winstl/registry/reg_key_sequence.hpp:769](../include/winstl/registry/reg_key_sequence.hpp#L769), [787](../include/winstl/registry/reg_key_sequence.hpp#L787), [806](../include/winstl/registry/reg_key_sequence.hpp#L806), [955](../include/winstl/registry/reg_key_sequence.hpp#L955) | failed to take duplicate of key | run cond | ✅ | house form |
| [winstl/registry/reg_value_sequence.hpp:733](../include/winstl/registry/reg_value_sequence.hpp#L733), [751](../include/winstl/registry/reg_value_sequence.hpp#L751), [770](../include/winstl/registry/reg_value_sequence.hpp#L770), [919](../include/winstl/registry/reg_value_sequence.hpp#L919) | failed to take duplicate of key | run cond | ✅ | house form |
| [winstl/registry/util/shared_handles.hpp:271](../include/winstl/registry/util/shared_handles.hpp#L271) | registry contents changed | run cond | ⚠️ | declarative; terse but not house form |
| [winstl/registry/util/shared_handles.hpp:291](../include/winstl/registry/util/shared_handles.hpp#L291) | could not register change notification | run cond | ⚠️ | lowercase "could not" |
| [winstl/shims/access/string/time.hpp:171](../include/winstl/shims/access/string/time.hpp#L171), [207](../include/winstl/shims/access/string/time.hpp#L207) | failed to convert date/time | run cond | ✅ | house form |
| [winstl/shims/conversion/to_DATE/SYSTEMTIME.hpp:147](../include/winstl/shims/conversion/to_DATE/SYSTEMTIME.hpp#L147) | failed to convert time value | run cond | ✅ | house form |
| [winstl/shims/conversion/to_FILETIME/SYSTEMTIME.hpp:133](../include/winstl/shims/conversion/to_FILETIME/SYSTEMTIME.hpp#L133) | failed to convert time value | run cond | ✅ | house form |
| [winstl/shims/conversion/to_SYSTEMTIME/DATE.hpp:143](../include/winstl/shims/conversion/to_SYSTEMTIME/DATE.hpp#L143) | failed to convert time value | run cond | ✅ | house form |
| [winstl/shims/conversion/to_SYSTEMTIME/FILETIME.hpp:133](../include/winstl/shims/conversion/to_SYSTEMTIME/FILETIME.hpp#L133) | failed to convert time value | run cond | ✅ | house form |
| [winstl/synch/event.hpp:177](../include/winstl/synch/event.hpp#L177) | event set operation failed | run cond | ⚠️ | "<noun> failed" form |
| [winstl/synch/event.hpp:193](../include/winstl/synch/event.hpp#L193) | event reset operation failed | run cond | ⚠️ | as above |
| [winstl/synch/event.hpp:227](../include/winstl/synch/event.hpp#L227), [244](../include/winstl/synch/event.hpp#L244) | failed to create kernel event object | run cond | ✅ | house form |
| [winstl/synch/event.hpp:338](../include/winstl/synch/event.hpp#L338) | event wait failed | run cond | ⚠️ | "<noun> failed" form |
| [winstl/synch/exceptions.hpp:437](../include/winstl/synch/exceptions.hpp#L437)*(ctor)* | invalid wait handle | prog err | ✅ | terse house form |
| [winstl/synch/exceptions.hpp:514](../include/winstl/synch/exceptions.hpp#L514)*(ctor)* | duplicate wait handles | prog err | ✅ | terse house form |
| [winstl/synch/exceptions.hpp:558](../include/winstl/synch/exceptions.hpp#L558)*(ctor)* | too many wait handles | prog err | ✅ | terse house form |
| [winstl/synch/process_mutex.hpp:288](../include/winstl/synch/process_mutex.hpp#L288), [328](../include/winstl/synch/process_mutex.hpp#L328) | mutex wait failed | run cond | ⚠️ | "<noun> failed" form; lowercase here, capitalised in unixstl twins |
| [winstl/synch/process_mutex.hpp:355](../include/winstl/synch/process_mutex.hpp#L355) | mutex release failed | run cond | ⚠️ | as above |
| [winstl/synch/process_mutex.hpp:415](../include/winstl/synch/process_mutex.hpp#L415), [434](../include/winstl/synch/process_mutex.hpp#L434) | failed to create kernel mutex object | run cond | ✅ | house form |
| [winstl/synch/process_mutex.hpp:453](../include/winstl/synch/process_mutex.hpp#L453), [472](../include/winstl/synch/process_mutex.hpp#L472) | failed to open kernel mutex object | run cond | ✅ | house form |
| [winstl/synch/semaphore.hpp:223](../include/winstl/synch/semaphore.hpp#L223), [242](../include/winstl/synch/semaphore.hpp#L242) | semaphore wait failed | run cond | ⚠️ | "<noun> failed" form |
| [winstl/synch/semaphore.hpp:270](../include/winstl/synch/semaphore.hpp#L270), [301](../include/winstl/synch/semaphore.hpp#L301) | semaphore release failed | run cond | ⚠️ | as above |
| [winstl/synch/semaphore.hpp:367](../include/winstl/synch/semaphore.hpp#L367), [392](../include/winstl/synch/semaphore.hpp#L392) | failed to create kernel semaphore object | run cond | ✅ | house form |
| [winstl/synch/tss_index.hpp:232](../include/winstl/synch/tss_index.hpp#L232) | could not allocate a TSS key | run cond | ⚠️ | lowercase "could not" + article; cf. unixstl ctor twin (sentence-case) |
| [winstl/system/console_colour_scope.hpp:172](../include/winstl/system/console_colour_scope.hpp#L172) | Could not retrieve console buffer information | run cond | ⚠️ | "Could not" form |
| [winstl/system/console_colour_scope.hpp:180](../include/winstl/system/console_colour_scope.hpp#L180) | Could not set console text attributes | run cond | ⚠️ | as above |
| [winstl/system/pid_sequence.hpp:332](../include/winstl/system/pid_sequence.hpp#L332) | Failed to enumerate processes | run cond | ⚠️ | sentence-case |
| [winstl/system/process_module_sequence.hpp:268](../include/winstl/system/process_module_sequence.hpp#L268) | Failed to enumerate processes | run cond | ⚠️ | sentence-case |
| [winstl/system/temporary_file_name.hpp:201](../include/winstl/system/temporary_file_name.hpp#L201), [266](../include/winstl/system/temporary_file_name.hpp#L266) | could not elicit temporary directory | run cond | ⚠️ | lowercase "could not" |
| [winstl/system/temporary_file_name.hpp:220](../include/winstl/system/temporary_file_name.hpp#L220), [285](../include/winstl/system/temporary_file_name.hpp#L285) | could not elicit temporary file name | run cond | ⚠️ | as above |
| [winstl/system/version_info.hpp:1337](../include/winstl/system/version_info.hpp#L1337), [1427](../include/winstl/system/version_info.hpp#L1427) | Could not obtain executing module path | run cond | ⚠️ | "Could not" form |
| [winstl/system/version_info.hpp:1358](../include/winstl/system/version_info.hpp#L1358), [1394](../include/winstl/system/version_info.hpp#L1394), [1448](../include/winstl/system/version_info.hpp#L1448), [1480](../include/winstl/system/version_info.hpp#L1480) | Could not elicit version information from module | run cond | ⚠️ | "Could not" form |
| [winstl/time/comparison_functions.h:575](../include/winstl/time/comparison_functions.h#L575), [603](../include/winstl/time/comparison_functions.h#L603), [647](../include/winstl/time/comparison_functions.h#L647), [692](../include/winstl/time/comparison_functions.h#L692), [737](../include/winstl/time/comparison_functions.h#L737) | failed to convert time value | run cond | ✅ | house form |
| [winstl/time/localisation_functions.h:343](../include/winstl/time/localisation_functions.h#L343), [387](../include/winstl/time/localisation_functions.h#L387) | failed to convert time value | run cond | ✅ | house form |
| [winstl/time/time_cast.hpp:182](../include/winstl/time/time_cast.hpp#L182), [206](../include/winstl/time/time_cast.hpp#L206) | failed to convert time value | run cond | ✅ | house form |
| [winstl/window/zorder_iterator.hpp:360](../include/winstl/window/zorder_iterator.hpp#L360) | z-order search failed: window has been destroyed | run cond | ⚠️ | colon-compound (one of only two) |


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
