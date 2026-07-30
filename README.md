# STLSoft 1.11 <!-- omit in toc -->

*... robust, lightweight, cross-platform, template software ...*


![C](https://img.shields.io/badge/C-00599C?style=flat&logo=c&logoColor=white)
![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=flat&logo=c%2B%2B&logoColor=white)
[![License](https://img.shields.io/badge/License-BSD_3--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)
[![GitHub release](https://img.shields.io/github/v/release/synesissoftware/STLSoft.svg)](https://github.com/synesissoftware/STLSoft/releases/latest)
[![Last Commit](https://img.shields.io/github/last-commit/synesissoftware/STLSoft)](https://github.com/synesissoftware/STLSoft/commits/master)
[![CMake on multiple platforms](https://github.com/synesissoftware/STLSoft/actions/workflows/ci.yml/badge.svg)](https://github.com/synesissoftware/STLSoft/actions/workflows/ci.yml)


## Table of Contents <!-- omit in toc -->

* [Introduction](#introduction)
* [Installation](#installation)
* [Components](#components)
	* [Subprojects](#subprojects)
	* [Libraries](#libraries)
* [Examples](#examples)
* [Project Information](#project-information)
	* [Where to get help](#where-to-get-help)
	* [Contribution guidelines](#contribution-guidelines)
	* [Dependencies](#dependencies)
		* [Test-only dependencies](#test-only-dependencies)
	* [Related projects](#related-projects)
	* [License](#license)


## Introduction

**STLSoft** is a suite of C and C++ libraries that provides:
* STL extensions;
* General-purpose utility components;
* Facades over operating-system and technology-specific APIs.

The overarching characteristic of STLSoft is that it is *lightweight*. That sounds great, but what does it actually mean? Specifically, the **STLSoft** libraries share the following characteristics:

* "**100% header-only**" - all components within the libraries are entirely defined within header files, meaning that users need only `#include` the requisite files to access the functionality;
* "**Intersecting Conformance**" -  similar, but not-identical, components from different projects (e.g. **UNIXSTL** and **WinSTL**) are _structurally conformant_ (they share compatible syntax, and corresponding semantics, without being related by type) only to the degree of the intersection of identical functionality, rather than employing significant additional functionality to achieve total structural conformance. For example, though both the `unixstl::filesystem_traits` and `winstl::filesystem_traits` traits classes provide the `stat()` and `fstat()` operations, `lstat()` is provided only by the former;
* **Maximum Cohesion with Minimal Coupling** - achieved by extensive use of generalising mechanisms, such as "*shims*", e.g. types that manipulate character strings are able to interact with arbitrary string types, not just `char const*` and `std::string`;
* **Very High Efficiency** - along with *Robustness*, all components in the libraries are implemented with a view to maximum _Efficiency_. This is aided by the extensive use of efficient utility classes, such as `stlsoft::auto_buffer` and `stlsoft::scoped_handle`;

**NOTE**: It is important to understand that _**STLSoft** is not a framework_. Each library component is as "thin" as possible to provide its given function. The intent is that STLSoft components are used as building blocks for writing higher level components - applications, classes, libraries, servers. **STLSoft** has been used extensively in the development of software in all these guises.


## Installation

There are three main ways to install **STLSoft**:

1. As downloaded archive, then using environment variables;
2. Cloning project, then using environment variables;
3. Cloning project, then installing via CMake;

Option 3 is recommended.

See [INSTALL.md](./INSTALL.md) for details of these options, and also for an explanation of the top-level build scripts in the project.

> **IMPORTANT**: If you are installing **STLSoft** _for the first time_ you **must** do the **CMake**-based build step specifying that you do _not_ want to run tests - by specifying the flags `-E` and `-T` to **prepare_cmake.sh** - otherwise you will end up with a circular dependency on **xTests** (which depends on **STLSoft**). [INSTALL.md](./INSTALL.md) explains this in detail.


## Components

The components in **STLSoft** are provided in _sub-projects_, and in _libraries_.


### Subprojects

The following significant sub-projects are provided:

* **STLSoft** - general-purpose components and base-level features;
* **ACESTL** - components to do with **ACE** framework;
* **COMSTL** - components to do with **Component Object Model (COM)**;
* **MFCSTL** - components to do with **Microsoft Foundation Classes (MFC)**;
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

Examples are provided in the ```examples``` directory, along with a markdown description for each. A detailed list TOC of them is provided in [EXAMPLES.md](./EXAMPLES.md).


## Project Information

### Where to get help

[GitHub Page](https://github.com/synesissoftware/STLSoft "GitHub Page")


### Contribution guidelines

Defect reports, feature requests, and pull requests are welcome on https://github.com/synesissoftware/STLSoft.

If you'd like to help out with the project, please raise an issue via [GitHub Issues Page](https://github.com/synesissoftware/STLSoft/issues "GitHub Issues Page") - you'll be very welcome!


### Dependencies

There are no dependencies for installation and use of **STLSoft**.


#### Test-only dependencies

The component-/unit-tests depend on the **xTests** project:

* [xTests](http://github.com/synesissoftware/xTests/)


### Related projects

Projects that depend on **STLSoft** - though for some it is only for test - include:

* [**b64**](https://github.com/synesissoftware/b64)
* [**cstring**](https://github.com/synesissoftware/cstring)
* [**Diagnosticism**](https://github.com/synesissoftware/Diagnosticism)
* [**FastFormat**](https://github.com/synesissoftware/FastFormat)
* [**libpath**](https://github.com/synesissoftware/libpath)
* [**Pantheios**](https://github.com/synesissoftware/Pantheios)
* [**recls**](https://github.com/synesissoftware/recls)
* [**shwild**](https://github.com/synesissoftware/shwild)
* [**UNIXem**](https://github.com/synesissoftware/UNIXem)
* [**xTests**](https://github.com/synesissoftware/xTests)


### License

**STLSoft** is released under the 3-clause BSD license. See [LICENSE](./LICENSE) for details.


<!-- ########################### end of file ########################### -->
