# STLSoft <!-- omit in toc -->

… robust, lightweight, cross-platform, template software …


![C](https://img.shields.io/badge/C-00599C?style=flat&logo=c&logoColor=white)
![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=flat&logo=c%2B%2B&logoColor=white)
[![License](https://img.shields.io/badge/License-BSD_3--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)
[![GitHub release](https://img.shields.io/github/v/release/synesissoftware/STLSoft.svg)](https://github.com/synesissoftware/STLSoft/releases/latest)
[![Last Commit](https://img.shields.io/github/last-commit/synesissoftware/STLSoft)](https://github.com/synesissoftware/STLSoft/commits/master)
[![CI](https://github.com/synesissoftware/STLSoft/actions/workflows/ci.yml/badge.svg)](https://github.com/synesissoftware/STLSoft/actions/workflows/ci.yml)


## Table of Contents <!-- omit in toc -->

- [Introduction](#introduction)
- [Installation](#installation)
- [Components](#components)
  - [Subprojects](#subprojects)
  - [Libraries](#libraries)
- [Examples](#examples)
- [Project Information](#project-information)
  - [Where to get help](#where-to-get-help)
  - [Contribution guidelines](#contribution-guidelines)
  - [Dependencies](#dependencies)
  - [Related projects](#related-projects)
  - [License](#license)


## Introduction

**STLSoft** is a suite of C and C++ libraries (currently the **1.11** line) that provides:

* STL extensions;
* general-purpose utility components;
* facades over operating-system and technology-specific APIs;

The overarching characteristic of **STLSoft** is that it is *lightweight*. Specifically, the libraries share the following characteristics:

* **100% header-only** — all components are entirely defined within header files, so users need only `#include` the requisite files to access the functionality;
* **Intersecting Conformance** — similar, but not identical, components from different sub-projects (e.g. **UnixSTL** and **WinSTL**) are *structurally conformant* (compatible syntax and corresponding semantics, without being related by type) only to the degree of the intersection of identical functionality, rather than employing significant additional functionality to achieve total structural conformance. For example, though both `unixstl::filesystem_traits` and `winstl::filesystem_traits` provide `stat()` and `fstat()`, `lstat()` is provided only by the former;
* **Maximum Cohesion with Minimal Coupling** — achieved by extensive use of generalising mechanisms such as *shims*; e.g. types that manipulate character strings can interact with arbitrary string types, not just `char const*` and `std::string`;
* **Very High Efficiency** — along with *Robustness*, components are implemented with a view to maximum *Efficiency*, aided by efficient utility classes such as `stlsoft::auto_buffer` and `stlsoft::scoped_handle`;

**NOTE**: **STLSoft** is *not* a framework. Each library component is as thin as possible for its given function. The intent is that **STLSoft** components are used as building blocks for higher-level software — applications, classes, libraries, servers. **STLSoft** has been used extensively in all these guises.

Further reading: [FAQ.md](./FAQ.md), [INSTALL.md](./INSTALL.md), [http://www.stlsoft.org/](http://www.stlsoft.org/).


## Installation

Detailed instructions — via **CMake**, and via environment variables (archive or clone) — are provided in the accompanying [INSTALL.md](./INSTALL.md) file, including an explanation of the top-level build scripts.

In short, there are three main ways to install **STLSoft**:

1. As a downloaded archive, then using environment variables;
2. Cloning the project, then using environment variables;
3. Cloning the project, then installing via **CMake**;

Option 3 is recommended.

> **IMPORTANT**: If you are installing **STLSoft** *for the first time*, you **must** do the **CMake**-based prepare step specifying that you do *not* want to run tests — by passing the flags `-E` and `-T` to **prepare_cmake.sh** — otherwise you will hit a circular dependency on **xTests** (which depends on **STLSoft**). [INSTALL.md](./INSTALL.md) explains the full first-time ordering.


## Components

The components in **STLSoft** are organised as *sub-projects* (technology / platform facets) that share *libraries* (functional areas). Many libraries appear in more than one sub-project with *intersecting conformance* — for example **filesystem** and **dl** under **PlatformSTL**, **UnixSTL**, and **WinSTL**.


### Subprojects

The following significant sub-projects are provided:

* **STLSoft** — general-purpose components and base-level features, such as `stlsoft::auto_buffer<>`, `stlsoft::scoped_handle<>`, and `STLSOFT_ASSERT()`;
* **ACESTL** — components for the **ACE** framework, such as `acestl::message_queue_sequence<>`;
* **ATLSTL** — components for the **Active Template Library (ATL)**, such as `atlstl::get_MemberValue()`;
* **COMSTL** — components for the **Component Object Model (COM)**, such as `comstl::interface_cast` and `comstl::enumerator_sequence<>`;
* **InetSTL** — components for internet APIs, such as `inetstl::session` and `inetstl::ftpdir_sequence`;
* **MFCSTL** — components for the **Microsoft Foundation Classes (MFC)**, such as `mfcstl::CArray_cadaptor<>`;
* **PlatformSTL** — platform-selected facades over **UnixSTL** or **WinSTL** (by structural conformance), such as `platformstl::readdir_sequence` and `platformstl::stopwatch`;
* **UnixSTL** — components for **Unix** operating-system APIs, such as `unixstl::glob_sequence` and `unixstl::dl_call()`;
* **WinSTL** — components for **Windows** operating-system APIs, such as `winstl::clipboard_scope` and `winstl::findfile_sequence`;


### Libraries

The significant libraries include (examples are illustrative, not exhaustive):

* **algorithms** — POD and unordered-sequence algorithms, such as `stlsoft::pod_copy_n()` and `stlsoft::find_first_duplicate()`;
* **automation** — **ATL** Automation property and enumerator helpers, such as `atlstl::get_MemberValue()`;
* **clipboard** — Windows clipboard RAII and enumeration, such as `winstl::clipboard_scope`;
* **collections** — sequence and veneer adaptors (arrays, COM enumerators, ACE queues, MFC containers), such as `stlsoft::array_view<>` and `comstl::enumerator_sequence<>`;
* **containers** — general- and special-purpose containers, such as `stlsoft::frequency_map<>` and `stlsoft::unicode_point_map`;
* **controls** — STL sequences over Win32 common controls, such as `winstl::listview_sequence`;
* **conversion** — casts and converters, such as `stlsoft::sap_cast<>()`, `stlsoft::format_bytes()`, and `comstl::interface_cast`;
* **diagnostics** — stopwatches, timing histograms, and debug emitters, such as `platformstl::stopwatch` and `stlsoft::doomgram`;
* **dl** — dynamic-library loading and invocation (**Unix** and **Windows**), such as `platformstl::dl_module` and `winstl::dl_call()`;
* **filesystem** — directory/glob sequences, paths, and mapped files, such as `platformstl::readdir_sequence`, `unixstl::glob_sequence`, and `platformstl::memory_mapped_file`;
* **functional** — function/method adaptors and predicates, such as `stlsoft::noop_function`;
* **iterator** — output and transforming iterators, such as `stlsoft::FILE_iterator` and `stlsoft::string_concatenator_iterator`;
* **locale** — scoped C locale changes, such as `stlsoft::locale_scope`;
* **memory** — buffers and allocators, such as `stlsoft::auto_buffer<>` and `comstl::task_allocator<>`;
* **meta** — compile-time type traits and selectors, such as `stlsoft::is_same_type<>`;
* **network** — internet/ACE session and connection facades, such as `inetstl::session` and `inetstl::connection`;
* **performance** — performance counters (often aliased to platform stopwatches), such as `platformstl::performance_counter`;
* **process** — Windows process-creation helpers, such as `winstl::create_process()`;
* **quality** — contract-enforcement and coverage macros, such as `STLSOFT_COVER_MARK_LINE()`;
* **reactor** — **ACE** reactor custom-event handling, such as `acestl::custom_event_handler`;
* **registry** — Windows registry keys, values, and sequences, such as `winstl::reg_key` and `winstl::reg_value_sequence`;
* **resource** — Windows resource-loading helpers, such as `winstl::load_custom_resource()`;
* **security** — COM/Win security initialisation and token/ACL views, such as `comstl::CoInitSecurity()` and `winstl::token_information<>`;
* **shell** — Windows Shell helpers, such as `winstl::browse_for_folder()`;
* **shims** — generalising access, attribute, and logical shims (overloads across sub-projects), such as `stlsoft::c_str_ptr()` and `stlsoft::get_ptr()`;
* **smartptr** — scoped and reference-counted handles, such as `stlsoft::scoped_handle<>` and `stlsoft::ref_ptr<>`;
* **speech** — lightweight SAPI helpers, such as `comstl::sapi_speak()`;
* **string** — lightweight strings, views, and tokenisers, such as `stlsoft::basic_simple_string<>` and `stlsoft::string_tokeniser<>`;
* **synch** — mutexes, spin locks, and lock scopes, such as `platformstl::thread_mutex` and `stlsoft::lock_scope<>`;
* **system** — environment, home directory, and process-id sequences, such as `platformstl::home_directory` and `platformstl::pid_sequence`;
* **time** — time formatting and comparison helpers, such as `stlsoft::fast_strftime()`;
* **typelib** — COM type-library helpers, such as `comstl::TypeInfo_resource_scope`;
* **view** — transforming views, such as `stlsoft::member_selector_view<>`;


## Examples

Examples are provided in the `examples` directory, along with a markdown description for each. A detailed catalogue is in [EXAMPLES.md](./EXAMPLES.md). After a **CMake** build, `./run_all_examples.sh` exercises matching example programs (see [INSTALL.md](./INSTALL.md)).


## Project Information


### Where to get help

* [GitHub Page](https://github.com/synesissoftware/STLSoft);
* [GitHub Issues](https://github.com/synesissoftware/STLSoft/issues);
* [FAQ.md](./FAQ.md);
* [HOW_YOU_CAN_HELP.md](./HOW_YOU_CAN_HELP.md);
* [KNOWN_ISSUES.md](./KNOWN_ISSUES.md);
* [http://www.stlsoft.org/](http://www.stlsoft.org/);


### Contribution guidelines

Defect reports, feature requests, and pull requests are welcome on https://github.com/synesissoftware/STLSoft.

If you'd like to help out with the project, please raise an issue via [GitHub Issues](https://github.com/synesissoftware/STLSoft/issues) — you'll be very welcome! See also [HOW_YOU_CAN_HELP.md](./HOW_YOU_CAN_HELP.md).


### Dependencies

| Dependency | Role | Required? |
| ---------- | ---- | --------- |
| — | Installation and use of **STLSoft** (100% header-only) | ✅ None |
| [**xTests**](https://github.com/synesissoftware/xTests) | Component- / unit-tests (`BUILD_TESTING`) | ⚪ Tests only |


### Related projects

Projects that depend on **STLSoft** — though for some it is only for tests — include:

* [**2be**](https://github.com/synesissoftware/2be) (tests only);
* [**b64**](https://github.com/synesissoftware/b64) (C++ API only);
* [**CLASP**](https://github.com/synesissoftware/CLASP);
* [**cstring**](https://github.com/synesissoftware/cstring) (tests only);
* [**Diagnosticism**](https://github.com/synesissoftware/Diagnosticism) (tests only);
* [**FastFormat**](https://github.com/synesissoftware/FastFormat);
* [**libCLImate**](https://github.com/synesissoftware/libCLImate);
* [**libpath**](https://github.com/synesissoftware/libpath) (tests only);
* [**Pantheios**](https://github.com/synesissoftware/Pantheios);
* [**Pantheios.Extras.DiagUtil**](https://github.com/synesissoftware/Pantheios.Extras.DiagUtil);
* [**Pantheios.Extras.Main**](https://github.com/synesissoftware/Pantheios.Extras.Main);
* [**Pantheios.Extras.xHelpers**](https://github.com/synesissoftware/Pantheios.Extras.xHelpers);
* [**recls**](https://github.com/synesissoftware/recls);
* [**shwild**](https://github.com/synesissoftware/shwild) (C++ API only);
* [**UNIXem**](https://github.com/synesissoftware/UNIXem);
* [**VOLE**](https://github.com/synesissoftware/VOLE) (tests only);
* [**xTests**](https://github.com/synesissoftware/xTests);


### License

**STLSoft** is released under the 3-clause BSD license. See [LICENSE](./LICENSE) for details.


<!-- ########################### end of file ########################### -->
