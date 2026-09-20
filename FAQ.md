# STLSoft - FAQ <!-- omit in toc -->

The FAQ list is under (constant) development. If you post a question on
[GitHub Issues](https://github.com/synesissoftware/STLSoft/issues)
it will be used to create one.


## Table of Contents <!-- omit in toc -->

- [Q1: "How do I build STLSoft?"](#q1-how-do-i-build-stlsoft)
- [Q2: "How do I install STLSoft?"](#q2-how-do-i-install-stlsoft)
- [Q3: "How do I use STLSoft?"](#q3-how-do-i-use-stlsoft)
- [Q4: "Does STLSoft have unit-tests?"](#q4-does-stlsoft-have-unit-tests)
- [Q5: "Is STLSoft still relevant given the widespread support for 'Modern C++'?"](#q5-is-stlsoft-still-relevant-given-the-widespread-support-for-modern-c)


# FAQs: <!-- omit in toc -->


## Q1: "How do I build STLSoft?"

You don't — for ordinary use.

**STLSoft** is 100% header-only, so application code only needs to `#include` the requisite headers. We recommend defining an environment variable such as `STLSOFT` so that you can point projects at new versions without disruption.

Building the project's own examples and tests is optional and is done via **CMake** (see [INSTALL.md](./INSTALL.md)).


## Q2: "How do I install STLSoft?"

Basically, there are three ways:

1. As downloaded archive, using environment variables;
2. Cloning project, using environment variables;
3. Cloning project, installing via **CMake**;

Option 3 is recommended.

See [INSTALL.md](./INSTALL.md) for details of these options.


## Q3: "How do I use STLSoft?"

Assuming you've installed it using environment variables (as per instructions in [Q2](#q2-how-do-i-install-stlsoft)), then:

* in your IDE settings, add the include directory `$(STLSOFT)/include`; or
* in your makefiles, add the include directory `-I$STLSOFT/include` (**UNIX**) or `-I%STLSOFT%/include` (**Windows**);

If you installed via **CMake**, consumers may instead use `find_package(STLSoft REQUIRED)` and link to `STLSoft::STLSoft`.


## Q4: "Does STLSoft have unit-tests?"

Yes. The **1.11** tree includes a large suite of component- and unit-tests exercised via **CMake** / **CTest** and [**xTests**](https://github.com/synesissoftware/xTests). See [INSTALL.md](./INSTALL.md) for the first-time install ordering (**STLSoft** without tests → **xTests** → **STLSoft** with tests) that avoids a circular dependency.


## Q5: "Is STLSoft still relevant given the widespread support for 'Modern C++'?"

This is a good question. The Synesis open-source libraries — including
[**b64**](https://github.com/synesissoftware/b64),
[**FastFormat**](https://github.com/synesissoftware/FastFormat),
[**Pantheios**](https://github.com/synesissoftware/Pantheios),
[**recls**](https://github.com/synesissoftware/recls),
[**shwild**](https://github.com/synesissoftware/shwild),
and more — continue to be maintained in light of contemporary C++ practice, while still supporting a wide range of compilers and platforms. That work informs the future of **STLSoft**, which may mean further investment in the existing 1.x stream or, eventually, a 2.x stream less burdened by historical compiler-feature detection.


<!-- ########################### end of file ########################### -->
