# STLSoft Examples <!-- omit in toc -->

| Name | Source & Description | Platform | Summary |
| ---- | -------------------- | -------- | ------- |
| **By concept**: | | | |
| **time_functions** | [by_concept/string_access_shims/time_functions](./examples/by_concept/string_access_shims/time_functions/main.cpp) | * | Format time-related types via string-access shims (e.g. `struct tm`, `std::chrono`) |
| | | | |
| **By project**: | | | |
| **comstl** | [by_project/comstl](./examples/by_project/comstl/main.cpp) | Windows | Shows numerous cooperating components in **COMSTL** |
| | | | |
| **home_directory** | [by_project/platformstl/system/home_directory](./examples/by_project/platformstl/system/home_directory/main.cpp) | * | Illustrates use of `platformstl::home_directory` |
| **readdir_sequence** | [by_project/platformstl/filesystem/readdir_sequence](./examples/by_project/platformstl/filesystem/readdir_sequence/main.cpp) | * | List filesystem entries with `platformstl::readdir_sequence` |
| | | | |
| **dl_call** | [by_project/unixstl/dl/dl_call](./examples/by_project/unixstl/dl/dl_call/main.cpp) | Unix | Call functions in shared libraries via `unixstl::dl_call` |
| **glob_sequence** | [by_project/unixstl/filesystem/glob_sequence](./examples/by_project/unixstl/filesystem/glob_sequence/main.cpp) | Unix | List selected filesystem entries with `unixstl::glob_sequence` |
| **home_directory** | [by_project/unixstl/system/home_directory](./examples/by_project/unixstl/system/home_directory/main.cpp) | Unix | Illustrates use of `unixstl::home_directory` |
| **readdir_sequence** | [by_project/unixstl/filesystem/readdir_sequence](./examples/by_project/unixstl/filesystem/readdir_sequence/main.cpp) | Unix | List filesystem entries with `unixstl::readdir_sequence` |
| | | | |
| **C.output_debug_line** | [by_project/winstl/diagnostics/C.output_debug_line](./examples/by_project/winstl/diagnostics/C.output_debug_line/main.c) | Windows | Emit debug strings with the C API `winstl_C_diagnostics_output_debug_line_*` |
| **codepages** | [by_project/winstl/i18n/codepages](./examples/by_project/winstl/i18n/codepages/main.cpp) | Windows | Enumerate system code pages with `winstl::codepage_sequence` |
| **dl_call** | [by_project/winstl/dl/dl_call](./examples/by_project/winstl/dl/dl_call/main.cpp) | Windows | Call functions in DLLs via `winstl::dl_call` |
| **findfile_sequence** | [by_project/winstl/filesystem/findfile_sequence](./examples/by_project/winstl/filesystem/findfile_sequence/main.cpp) | Windows | List selected filesystem entries with `winstl::findfile_sequence` |
| **home_directory** | [by_project/winstl/system/home_directory](./examples/by_project/winstl/system/home_directory/main.cpp) | Windows | Illustrates use of `winstl::home_directory` |
| **output_debug_line** | [by_project/winstl/diagnostics/output_debug_line](./examples/by_project/winstl/diagnostics/output_debug_line/main.cpp) | Windows | Emit concatenating debug lines with `winstl::diagnostics::output_debug_line` |
| **printf_debug_string** | [by_project/winstl/diagnostics/printf_debug_string](./examples/by_project/winstl/diagnostics/printf_debug_string/main.c) | Windows | `printf`-style debug output with `winstl_C_printf_debug_string` |
| **readdir_sequence** | [by_project/winstl/filesystem/readdir_sequence](./examples/by_project/winstl/filesystem/readdir_sequence/main.cpp) | Windows | List filesystem entries with `winstl::readdir_sequence` |
| | | | |
| **By library**: | | | |
| **creation_functions** | [by_library/com_utility/creation_functions](./examples/by_library/com_utility/creation_functions/main.cpp) | Windows | Create COM objects with **COMSTL** creation helpers and `interface_cast` |
| **rot_functions** | [by_library/com_utility/rot_functions](./examples/by_library/com_utility/rot_functions/main.cpp) | Windows | Manipulate the COM Running Object Table with **COMSTL** ROT helpers |
| | | | |
| **unicode_point_map** | [by_library/containers/unicode_point_map](./examples/by_library/containers/unicode_point_map/main.cpp) | * | Illustrates use of `stlsoft::unicode_point_map` |
| | | | |
| **interface_cast** | [by_library/conversion/interface_cast](./examples/by_library/conversion/interface_cast/main.cpp) | Windows | Query COM interfaces with `comstl::interface_cast` helpers |
| **sap_cast** | [by_library/conversion/sap_cast](./examples/by_library/conversion/sap_cast/main.cpp) | * | Size-aware pointer casts with `stlsoft::sap_cast` |
| **union_cast** | [by_library/conversion/union_cast](./examples/by_library/conversion/union_cast/main.cpp) | * | Same-size type punning with `stlsoft::union_cast` |
| | | | |
| **processtimes_stopwatch** | [by_library/diagnostics/processtimes_stopwatch](./examples/by_library/diagnostics/processtimes_stopwatch/main.cpp) | * | Measure process CPU time with `platformstl::processtimes_stopwatch` |
| **stopwatch** | [by_library/diagnostics/stopwatch](./examples/by_library/diagnostics/stopwatch/main.cpp) | * | Measure elapsed wall time with `platformstl::stopwatch` |
| | | | |
| **auto_buffer** | [by_library/memory/auto_buffer](./examples/by_library/memory/auto_buffer/main.cpp) | * | Illustrates use of `stlsoft::auto_buffer` |
| **com_memory_functions** | [by_library/memory/com_memory_functions](./examples/by_library/memory/com_memory_functions/main.cpp) | Windows | Inspect COM task-allocator blocks with **COMSTL** memory helpers |
| **heapwalk_sequence** | [by_library/memory/heapwalk_sequence](./examples/by_library/memory/heapwalk_sequence/main.cpp) | Windows | List heap allocations with `winstl::heapwalk_sequence` |
| | | | |
| **pid_sequence** | [by_library/system/pid_sequence](./examples/by_library/system/pid_sequence/main.cpp) | * | List process IDs with `platformstl::pid_sequence` |
| | | | |
| **clipboard_format_sequence** | [by_library/windows_clipboard/clipboard_format_sequence](./examples/by_library/windows_clipboard/clipboard_format_sequence/main.cpp) | Windows | Enumerate clipboard formats with `winstl::clipboard_format_sequence` |
| **clipboard_scope** | [by_library/windows_clipboard/clipboard_scope](./examples/by_library/windows_clipboard/clipboard_scope/main.cpp) | Windows | Open/set clipboard contents with `winstl::clipboard_scope` |
| | | | |
| **windows_control_panel** | [by_library/windows_control_panel/windows_control_panel](./examples/by_library/windows_control_panel/windows_control_panel/main.cpp) | Windows | Enumerate Control Panel applets with `winstl::applet_module` |
| | | | |
| **enum_values** | [by_library/windows_registry/enum_values](./examples/by_library/windows_registry/enum_values/main.cpp) | Windows | Enumerate registry values with `winstl::reg_value_sequence` |
| **registry_functions** | [by_library/windows_registry/registry_functions](./examples/by_library/windows_registry/registry_functions/main.cpp) | Windows | Read registry string values with `winstl::reg_get_string_value` |
| | | | |
| **memory_functions** | [by_library/windows_shell/memory_functions](./examples/by_library/windows_shell/memory_functions/main.cpp) | Windows | Allocate/free shell memory with **WinSTL** shell memory helpers |
| | | | |
| **module_sequence** | [by_library/windows_toolhelp/module_sequence](./examples/by_library/windows_toolhelp/module_sequence/main.cpp) | Windows | List process modules with `winstl::module_sequence` |
| **process_sequence** | [by_library/windows_toolhelp/process_sequence](./examples/by_library/windows_toolhelp/process_sequence/main.cpp) | Windows | List processes with `winstl::process_sequence` |
| | | | |
| **shell_functions** | [by_library/windows_shell/shell_functions](./examples/by_library/windows_shell/shell_functions/main.cpp) | Windows | Browse for folders and related shell operations with **WinSTL** shell helpers |


<!-- ########################### end of file ########################### -->
