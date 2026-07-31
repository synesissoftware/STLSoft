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

The components in **STLSoft** are provided in _sub-projects_, and in _libraries_.


### Subprojects

The following significant sub-projects are provided:

* **STLSoft** - general-purpose components and base-level features;
* **ACESTL** - components to do with **ACE** framework;
* **ATLSTL** - components to do with **Active Template Library (ATL)**;
* **COMSTL** - components to do with **Component Object Model (COM)**;
* **InetSTL** - components to do with **internet APIs**;
* **MFCSTL** - components to do with **Microsoft Foundation Classes (MFC)**;
* **PlatformSTL** - components that provide platform-related elements, from **UnixSTL** or **WinSTL** as appropriate, according to structural conformance;
* **UnixSTL** - components to do with **Unix** operating system APIs;
* **WinSTL** - components to do with **Windows** operating system APIs;


### Libraries

The significant libraries include:

* **algorithms** - T.B.C.
* **automation** - T.B.C.
* **clipboard** - T.B.C.
* **collections** - T.B.C.
* **containers** - general- and special-purpose containers, such as `stlsoft::frequency_map<>`;
* **controls** - T.B.C.
* **conversion** - T.B.C.
* **diagnostics** - T.B.C.
* **dl** - dynamic-library loading and invocation (for both **Unix** and **Windows**);
* **filesystem** - T.B.C.
* **function_adaptors** - T.B.C.
* **functional** - T.B.C.
* **iterator** - T.B.C.
* **locale** - T.B.C.
* **memory** - T.B.C.
* **meta** - T.B.C.
* **network** - T.B.C.
* **performance** - T.B.C.
* **process** - T.B.C.
* **quality** - T.B.C.
* **reactor** - T.B.C.
* **registry** - T.B.C.
* **resource** - T.B.C.
* **security** - T.B.C.
* **shell** - T.B.C.
* **shims** - T.B.C.
* **smartptr** - T.B.C.
* **speech** - T.B.C.
* **string** - T.B.C.
* **synch** - T.B.C.
* **system** - T.B.C.
* **time** - T.B.C.
* **typelib** - T.B.C.
* **view** - T.B.C.

As **STLSoft** approaches an official release we will provide increasing information on the above _sub-projects_ and _libraries_.


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
