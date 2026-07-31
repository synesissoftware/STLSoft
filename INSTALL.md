# STLSoft - Installation and Use <!-- omit in toc -->


## Table of Contents <!-- omit in toc -->

- [Installing](#installing)
  - [As downloaded archive, using environment variables](#as-downloaded-archive-using-environment-variables)
  - [Cloning project, using environment variables](#cloning-project-using-environment-variables)
  - [Cloning project, installing via CMake](#cloning-project-installing-via-cmake)
- [Use of environment variables in other open-source projects](#use-of-environment-variables-in-other-open-source-projects)
- [Understanding the top-level project build scripts](#understanding-the-top-level-project-build-scripts)


> **IMPORTANT**: If you are installing **STLSoft** for the **first time** and are opting for [Cloning project, installing via CMake](#cloning-project-installing-via-cmake), you **must** specify `-E` and `-T`, as described in detail below.


## Installing

There are three options for installing **STLSoft**, depending on how you obtain it. The recommended way is to [clone and install via CMake](#cloning-project-installing-via-cmake).


### As downloaded archive, using environment variables

If you obtain the latest release as an archive from the [**STLSoft** GitHub Releases](https://github.com/synesissoftware/STLSoft/releases) page (legacy archives may also still appear on [SourceForge](https://sourceforge.net/projects/stlsoft/)):

1. Download the latest distribution, e.g. [**STLSoft-1.11.1-rc5.zip**](https://github.com/synesissoftware/STLSoft/archive/refs/tags/1.11.1-rc5.zip);

2. Unzip it to a directory of your choice, as in:

```bash
$ mkdir -p ~/open-source
$ cd ~/open-source
$ unzip STLSoft-1.11.1-rc5.zip
```

3. Define an environment variable `STLSOFT`, whose value is the directory in which you unzipped it, e.g. `STLSOFT=~/open-source/STLSoft-1.11.1-rc5`, and then specify `$(STLSOFT)/include` (**UNIX**) or `%STLSOFT%\include` (**Windows**) in your project files and makefiles;


### Cloning project, using environment variables

If you clone the project from https://github.com/synesissoftware/STLSoft:

1. Clone, as in;

```bash
$ mkdir -p ~/open-source
$ cd ~/open-source
$ git clone -b master https://github.com/synesissoftware/STLSoft
```

2. Define an environment variable `STLSOFT`, whose value is the directory in which you cloned it, e.g. `STLSOFT=~/open-source/STLSoft`, and then specify `$(STLSOFT)/include` (**UNIX**) or `%STLSOFT%\include` (**Windows**) in your project files and makefiles;


### Cloning project, installing via CMake

1. Clone, as in;

```bash
$ mkdir -p ~/open-source
$ cd ~/open-source
$ git clone -b master https://github.com/synesissoftware/STLSoft
```

2. "Prepare" the **CMake** build context:

```bash
$ cd ~/open-source/STLSoft
$ ./prepare_cmake.sh -m -v
```

> **IMPORTANT**: If you are installing **STLSoft** _for the first time_, you **must** also specify that you do _not_ want to run tests by specifying the flags `-E` and `-T` to **prepare_cmake.sh**, otherwise you will end up with a circular dependency on **xTests** (which depends on **STLSoft**), as in:
>
> ```bash
> $ ./prepare_cmake.sh -E -T
> ```
>
> Use the `'--help'` flag for the full usage of this script.
>
> To build and exercise the **STLSoft** unit-tests and you are installing **STLSoft** _for the first time_, then you must do the following steps:
> 1. Configure and install **STLSoft** _without_ tests, by specifying flags `-E` and `-T`;
> 2. Configure, build, and install **xTests**;
> 3. Configure, build, and install **STLSoft** _with_ tests, by specifying `-m` (and `-v`, if you wish) and by _not_ specifying flags `-E` and `-T`;


3. Install the **CMake** build artefacts such that they are available for use _and_ that **STLSoft** may be found by other **CMake**-based installations:

```bash
$ cd ~/open-source/STLSoft
$ sudo cmake --install ${SIS_CMAKE_BUILD_DIR:-./_build} --config Release
```


----


## Use of environment variables in other open-source projects

Unless you are certain that your projects, and all the projects upon which they depend, all use **STLSoft** via **CMake** then it is recommended that you define an `STLSOFT` environment variable.

For example, if you're using **UNIX** and you install to
**/usr/local/stlsoft/STLSoft-1.11.1-rc5**
then you should set the environment variable `STLSOFT` to
**/usr/local/stlsoft/STLSoft-1.11.1-rc5**
in which case the file `stlsoft/stlsoft.h`, for example, will be located in `/usr/local/stlsoft/STLSoft-1.11.1-rc5/include/stlsoft/stlsoft.h`.

Conversely, if you're using **Windows** and you install to
**C:\3pty\STLSoft\STLSoft-1.11.1-rc5**
then you should set the environment variable `STLSOFT` to
**C:\3pty\STLSoft\STLSoft-1.11.1-rc5**
in which case the file `stlsoft/stlsoft.h`, for example, will be located in `C:\3pty\STLSoft\STLSoft-1.11.1-rc5\include\stlsoft\stlsoft.h`.

The makefiles / project files of several other open-source projects expect this symbol, including:

| Project       | Project home                                     |
| ------------- | ------------------------------------------------ |
| b64           | https://github.com/synesissoftware/b64           |
| CLASP         | https://github.com/synesissoftware/CLASP         |
| cstring       | https://github.com/synesissoftware/cstring       |
| Diagnosticism | https://github.com/synesissoftware/Diagnosticism |
| FastFormat    | https://github.com/synesissoftware/FastFormat    |
| libCLImate    | https://github.com/synesissoftware/libCLImate    |
| Pantheios     | https://github.com/synesissoftware/Pantheios     |
| recls         | https://github.com/synesissoftware/recls         |
| shwild        | https://github.com/synesissoftware/shwild        |
| VOLE          | https://github.com/synesissoftware/VOLE          |
| xTests        | https://github.com/synesissoftware/xTests        |

**NOTE**: If you're using **STLSoft** on `UNIX`, you might want to apply `dos2unix` over all the files before using it. You *must* do this if you're using the **SunPro C compiler** - this action is carried out automatically, for example, by the **Pantheios** makefile(s).


----


## Understanding the top-level project build scripts

This project comes with a number of scripts useful for building with **CMake**, as follows:

| Script | Purpose |
| ------ | ------- |
| **prepare_cmake.sh** | Creates/reinitialises the **CMake** build script(s).<br/><br/>This is the primary script, and is used to generate all the **CMake** build artefacts. We recommend that you use the command as follows:<br/><br/>&nbsp;&nbsp;&nbsp;&nbsp;`./prepare_cmake.sh -m -v`.<br/><br/>The flag `-m` executes a build upon successful generation, and the flag `-v` generates verbose makefile(s). Use `./prepare_cmake.sh --help` for further information. |
| **build_cmake.sh** | Executes **CMake**-generated artefacts to (re)build the project.<br/><br/>Meaningful only once `prepare_cmake.sh` has been run to generate the **CMake** build artefacts.<br/><br/>Use `./build_cmake.sh --help` for further information. |
| **clean_cmake.sh** | Executes **CMake**-generated artefacts to clean the project.<br/><br/>Meaningful only once `prepare_cmake.sh` has been run and a build has been run.<br/><br/>Use `./clean_cmake.sh --help` for further information. |
| **run_all_examples.sh** | Runs all (matching) example programs.<br/><br/>Performs a build and then recursively runs executables under the examples tree. See also [**EXAMPLES.md**](./EXAMPLES.md).<br/><br/>Use `./run_all_examples.sh --help` for further information. |
| **run_all_unit_tests.sh** | Runs all (matching) unit-test programs.<br/><br/>Performs a build and then recursively runs executable programs matching the shell patterns `test_*` and `test.*`.<br/><br/>Use `./run_all_unit_tests.sh --help` for further information. |
| **remove_cmake_artefacts.sh** | Removes all known **CMake** artefacts.<br/><br/>Removes known **CMake** build artefacts from the build directory (currently `./_build`) to prepare for complete regeneration using `prepare_cmake.sh`.<br/><br/>Use `./remove_cmake_artefacts.sh --help` for further information. |


<!-- ########################### end of file ########################### -->

