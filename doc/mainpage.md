# STLSoft {#mainpage}

**STLSoft** is a suite of **C** and **C++** libraries that provides STL extensions, general-purpose utility components, and facades over operating-system and technology-specific APIs. It is robust, lightweight, and cross-platform.

The overarching characteristic of **STLSoft** is that it is *lightweight*. The libraries are **100% header-only**: all components are defined entirely within header files, so users need only `#include` the requisite files to access the functionality. **STLSoft** is *not* a framework; each component is as thin as possible for its given function, intended as a building block for higher-level software.


## Components

The components are organised as *sub-projects* (technology / platform facets), each rooted at its own header directory:

| Sub-project | Header | Summary |
| ----------- | ------ | ------- |
| **ACESTL** | `<acestl/acestl.hpp>` | Components for the **ACE** framework |
| **ATLSTL** | `<atlstl/atlstl.hpp>` | Components for the **Active Template Library (ATL)** |
| **COMSTL** | `<comstl/comstl.h>` | Components for the **Component Object Model (COM)** |
| **InetSTL** | `<inetstl/inetstl.h>` | Components for internet APIs |
| **MFCSTL** | `<mfcstl/mfcstl.hpp>` | Components for the **Microsoft Foundation Classes (MFC)** |
| **PlatformSTL** | `<platformstl/platformstl.h>` | Platform-selected facades over **UnixSTL** or **WinSTL** |
| **STLSoft** | `<stlsoft/stlsoft.h>` | General-purpose components and base-level features |
| **UnixSTL** | `<unixstl/unixstl.h>` | Components for **Unix** operating-system APIs |
| **WinSTL** | `<winstl/winstl.h>` | Components for **Windows** operating-system APIs |

Many functional areas (for example **filesystem**, **dl**, and **memory**) appear in more than one sub-project with *intersecting conformance*: similar components are structurally compatible, without being related by type, only to the degree of the intersection of their functionality.


## Quick start

Include the requisite header(s) and use the component; there is nothing to link:

```cpp
#include <stlsoft/memory/auto_buffer.hpp>

#include <stdlib.h>
#include <string.h>

int main()
{
    // up to 128 chars on the stack; beyond that, on the heap
    stlsoft::auto_buffer<char, 128> buff(10);

    ::memset(&buff[0], '1', buff.size());

    buff.resize(1000, '2');

    return EXIT_SUCCESS;
}
```

Consumer **CMake** projects may use `find_package(STLSoft)` and link
`STLSoft::STLSoft`. Otherwise, define an environment variable `STLSOFT` and
add `$(STLSOFT)/include` to the include path. See
[INSTALL.md](https://github.com/synesissoftware/STLSoft/blob/master/INSTALL.md)
for build and install instructions, and
[EXAMPLES.md](https://github.com/synesissoftware/STLSoft/blob/master/EXAMPLES.md)
for the catalogue of example programs.


## Related projects

Projects that depend on **STLSoft**:

| Project | Use |
| ------- | --- |
| [b64](https://github.com/synesissoftware/b64) | C++ API is implemented in terms of **STLSoft** |
| [Pantheios](https://github.com/synesissoftware/Pantheios) | Logging API library |
| [shwild](https://github.com/synesissoftware/shwild) | Optional dependency (`USE_STLSOFT_PKG`) |
| [xTests](https://github.com/synesissoftware/xTests) | Testing library; used for the **STLSoft** unit and component tests |


<!-- ########################### end of file ########################### -->
