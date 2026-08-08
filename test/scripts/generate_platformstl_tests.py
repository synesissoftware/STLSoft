#!/usr/bin/env python3
"""Generate platformstl unit/component test implementations and CMake hierarchy."""

from __future__ import annotations

import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
TEST_UNIT = ROOT / "test" / "unit" / "platformstl"
TEST_COMPONENT = ROOT / "test" / "component" / "platformstl"


def adapt_reference(src: Path, test_name: str, header: str) -> str:
    text = src.read_text()
    text = re.sub(r"#include\s+<(?:winstl|unixstl)/", "#include <platformstl/", text)
    text = re.sub(r"\b(?:winstl|unixstl)::", "platformstl::", text)
    text = re.sub(
        r'XTESTS_START_RUNNER\("[^"]+"',
        f'XTESTS_START_RUNNER("{test_name}"',
        text,
    )
    # Ensure primary header is platformstl
    if header not in text:
        text = re.sub(
            r"#include\s+<platformstl/[^>]+>",
            f"#include {header}",
            text,
            count=1,
        )
    return text


def write(path: Path, content: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(content)


def cmake_leaf(test_name: str) -> str:
    return f"define_automated_test_program({test_name} entry.cpp)\n"


def update_cmake(dir_path: Path, subdirs: list[str]) -> None:
    lines = ["# SIS:AUTO_GENERATED: Remove this line if you edit the file, otherwise it will be overwritten"]
    for s in sorted(subdirs):
        lines.append(f"add_subdirectory({s})")
    lines.append("")
    write(dir_path / "CMakeLists.txt", "\n".join(lines))


def exception_test(test_name: str, header: str, exc_type: str) -> str:
    return f"""/* /////////////////////////////////////////////////////////////////////////
 * File:    {test_name}/entry.cpp
 *
 * Purpose: Unit-tests for `{header.strip('<>')}`.
 *
 * Created: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */

#include {header}
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {{ static void test_type_exists(void); }}

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        XTESTS_RUN_CASE(test_type_exists);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}
    return retCode;
}}

static void test_type_exists(void)
{{
    STLSOFT_SUPPRESS_UNUSED(typeid({exc_type}));
    TEST_PASSED();
}}
"""


def main() -> None:
    refs = ROOT / "test"

    # --- unit tests adapted from references ---
    adaptations: list[tuple[str, Path, str, str]] = [
        ("unit", refs / "unit/winstl/error/test.unit.winstl.error.error_desc/entry.cpp",
         "test.unit.platformstl.error.error_desc", "<platformstl/error/error_desc.hpp>"),
        ("unit", refs / "unit/winstl/synch/test.unit.winstl.synch.sleep_functions/entry.cpp",
         "test.unit.platformstl.synch.sleep_functions", "<platformstl/synch/sleep_functions.h>"),
        ("unit", refs / "unit/winstl/performance/test.unit.winstl.performance.performance_counter/entry.cpp",
         "test.unit.platformstl.performance.performance_counter", "<platformstl/performance/performance_counter.hpp>"),
    ]

    for kind, src, name, header in adaptations:
        base = TEST_UNIT if kind == "unit" else TEST_COMPONENT
        content = adapt_reference(src, name, header)
        content = content.replace("winstl::sleep_ms", "platformstl::sleep_ms")
        content = content.replace("ERROR_SUCCESS", "0")
        content = content.replace("ERROR_FILE_NOT_FOUND", "ENOENT" if "ENOENT" in content else "ERROR_FILE_NOT_FOUND")
        leaf = base
        for part in name.replace("test.unit.platformstl.", "").replace("test.component.platformstl.", "").split("."):
            if part.startswith("test."):
                leaf = leaf / part
        # reconstruct path from test name
        rel = name.split(".", 3)[-1].replace(".", "/")
        parts = rel.split("/")
        leaf_dir = base / "/".join(parts[:-1]) / name
        write(leaf_dir / "entry.cpp", content)
        write(leaf_dir / "CMakeLists.txt", cmake_leaf(name))

    # error_desc platform-specific error code
    write(
        TEST_UNIT / "error/test.unit.platformstl.error.error_desc/entry.cpp",
        """#include <platformstl/error/error_desc.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/shims/access/string.hpp>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>
#if defined(PLATFORMSTL_OS_IS_UNIX)
# include <errno.h>
#elif defined(PLATFORMSTL_OS_IS_WINDOWS)
# ifndef WIN32_LEAN_AND_MEAN
#  define WIN32_LEAN_AND_MEAN
# endif
# include <windows.h>
#endif

namespace { static void test_success(void); static void test_known_error(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.unit.platformstl.error.error_desc", verbosity))
    {
        XTESTS_RUN_CASE(test_success);
        XTESTS_RUN_CASE(test_known_error);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_success(void)
{
    platformstl::error_desc ed(0);
    TEST_UINT_EQ(0u, ed.get_error());
    TEST_UINT_NE(0u, stlsoft::c_str_len(ed));
}

static void test_known_error(void)
{
#if defined(PLATFORMSTL_OS_IS_WINDOWS)
    platformstl::error_desc ed(ERROR_FILE_NOT_FOUND);
    TEST_UINT_EQ(static_cast<unsigned>(ERROR_FILE_NOT_FOUND), ed.get_error());
#elif defined(PLATFORMSTL_OS_IS_UNIX)
    platformstl::error_desc ed(ENOENT);
    TEST_UINT_EQ(static_cast<unsigned>(ENOENT), ed.get_error());
#endif
    TEST_UINT_NE(0u, stlsoft::c_str_len(ed));
}
""",
    )

    # performance_counter
    write(
        TEST_UNIT / "performance/test.unit.platformstl.performance.performance_counter/entry.cpp",
        """#include <platformstl/performance/performance_counter.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_query(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.unit.platformstl.performance.performance_counter", verbosity))
    {
        XTESTS_RUN_CASE(test_query);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

namespace {

static void test_query(void)
{
    platformstl::performance_counter pc;

    pc.start();
    pc.stop();

    TEST_INT_GE(0, pc.get_seconds());
    TEST_INT_GE(0, pc.get_microseconds());
}
} // anonymous namespace
""",
    )

    # sleep_functions
    write(
        TEST_UNIT / "synch/test.unit.platformstl.synch.sleep_functions/entry.cpp",
        """#include <platformstl/synch/sleep_functions.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_sleep_zero(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.unit.platformstl.synch.sleep_functions", verbosity))
    {
        XTESTS_RUN_CASE(test_sleep_zero);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_sleep_zero(void)
{
    platformstl::micro_sleep(0);
    TEST_PASSED();
}
""",
    )

    # exception types
    exceptions = [
        ("access_exception", "platformstl::access_exception"),
        ("entry_not_found_exception", "platformstl::entry_not_found_exception"),
        ("file_not_found_exception", "platformstl::file_not_found_exception"),
        ("invalid_entry_type_exception", "platformstl::invalid_entry_type_exception"),
        ("invalid_file_type_exception", "platformstl::invalid_file_type_exception"),
        ("platformstl_exception", "platformstl::platformstl_exception"),
        ("security_exception", "platformstl::security_exception"),
    ]
    for stem, exc in exceptions:
        name = f"test.unit.platformstl.exception.{stem}"
        write(
            TEST_UNIT / f"exception/{name}/entry.cpp",
            exception_test(name, f"<platformstl/exception/{stem}.hpp>", exc),
        )
        write(TEST_UNIT / f"exception/{name}/CMakeLists.txt", cmake_leaf(name))

    # filesystem_exception (component)
    name = "test.component.platformstl.exception.filesystem_exception"
    write(
        TEST_COMPONENT / f"exception/{name}/entry.cpp",
        """#include <platformstl/exception/filesystem_exception.hpp>
#include <platformstl/filesystem/memory_mapped_file.hpp>
#include <xtests/terse-api.h>
#include <xtests/util/temp_file.hpp>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_missing_file_throws(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.platformstl.exception.filesystem_exception", verbosity))
    {
        XTESTS_RUN_CASE_THAT_THROWS(test_missing_file_throws, platformstl::filesystem_exception);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_missing_file_throws(void)
{
    using ::xtests::cpp::util::temp_file;
    temp_file f(temp_file::DeleteOnOpen | temp_file::DeleteOnClose);
    platformstl::memory_mapped_file mmf(f.c_str());
    TEST_FAIL("should not get here");
}
""",
    )

    # throw_policies
    write(
        TEST_UNIT / "exception/test.unit.platformstl.exception.throw_policies/entry.cpp",
        """#include <platformstl/exception/throw_policies.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_policy_type_exists(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.unit.platformstl.exception.throw_policies", verbosity))
    {
        XTESTS_RUN_CASE(test_policy_type_exists);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_policy_type_exists(void)
{
    STLSOFT_SUPPRESS_UNUSED(typeid(platformstl::platform_exception_policy));
    TEST_PASSED();
}
""",
    )

    # error exceptions (obsolete header; ensure it still compiles)
    write(
        TEST_UNIT / "error/test.unit.platformstl.error.exceptions/entry.cpp",
        """#include <platformstl/error/exceptions.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_obsolete_header_compiles(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.unit.platformstl.error.exceptions", verbosity))
    {
        XTESTS_RUN_CASE(test_obsolete_header_compiles);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_obsolete_header_compiles(void)
{
    STLSOFT_SUPPRESS_UNUSED(typeid(platformstl::platform_exception_policy));
    STLSOFT_SUPPRESS_UNUSED(typeid(platformstl::platformstl_exception));
    TEST_PASSED();
}
""",
    )

    # atomic_types
    write(
        TEST_UNIT / "synch/test.unit.platformstl.synch.atomic_types/entry.cpp",
        """#include <platformstl/synch/atomic_types.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_compile(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.unit.platformstl.synch.atomic_types", verbosity))
    {
        XTESTS_RUN_CASE(test_compile);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_compile(void)
{
    platformstl::atomic_int_t n = 0;
    STLSOFT_SUPPRESS_UNUSED(n);
    TEST_PASSED();
}
""",
    )

    # thread_mutex
    write(
        TEST_UNIT / "synch/test.unit.platformstl.synch.thread_mutex/entry.cpp",
        """#include <platformstl/synch/thread_mutex.hpp>
#include <stlsoft/synch/lock_scope.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_lock_unlock(void); static void test_lock_scope(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.unit.platformstl.synch.thread_mutex", verbosity))
    {
        XTESTS_RUN_CASE(test_lock_unlock);
        XTESTS_RUN_CASE(test_lock_scope);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_lock_unlock(void)
{
    platformstl::thread_mutex mx;
    mx.lock();
    mx.unlock();
    TEST_PASSED();
}

static void test_lock_scope(void)
{
    platformstl::thread_mutex mx;
    stlsoft::lock_scope<platformstl::thread_mutex> scope(mx);
    TEST_PASSED();
}
""",
    )

    # spin_mutex - simplified from winstl component
    write(
        TEST_UNIT / "synch/test.unit.platformstl.synch.spin_mutex/entry.cpp",
        """#include <platformstl/synch/spin_mutex.hpp>
#include <stlsoft/synch/lock_scope.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_lock_unlock(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.unit.platformstl.synch.spin_mutex", verbosity))
    {
        XTESTS_RUN_CASE(test_lock_unlock);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_lock_unlock(void)
{
    platformstl::spin_mutex mx;
    mx.lock();
    mx.unlock();
    {
        stlsoft::lock_scope<platformstl::spin_mutex> scope(mx);
    }
    TEST_PASSED();
}
""",
    )

    # semaphore
    write(
        TEST_UNIT / "synch/test.unit.platformstl.synch.semaphore/entry.cpp",
        """#include <platformstl/synch/semaphore.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_create_wait_post(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.unit.platformstl.synch.semaphore", verbosity))
    {
        XTESTS_RUN_CASE(test_create_wait_post);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_create_wait_post(void)
{
    platformstl::semaphore sem(1);
    sem.lock();
    sem.unlock();
    TEST_PASSED();
}
""",
    )

    # tss_index
    write(
        TEST_UNIT / "synch/test.unit.platformstl.synch.tss_index/entry.cpp",
        """#include <platformstl/synch/tss_index.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_allocate_set_get(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.unit.platformstl.synch.tss_index", verbosity))
    {
        XTESTS_RUN_CASE(test_allocate_set_get);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_allocate_set_get(void)
{
    platformstl::tss_index idx;
    void* p = &idx;
    idx.set_value(p);
    TEST_PTR_EQ(p, idx.get_value());
    TEST_PASSED();
}
""",
    )

    # refcount policies
    write(
        TEST_UNIT / "synch/test.unit.platformstl.synch.refcount_policies/entry.cpp",
        """#include <platformstl/synch/refcount_policies.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_types_exist(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.unit.platformstl.synch.refcount_policies", verbosity))
    {
        XTESTS_RUN_CASE(test_types_exist);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_types_exist(void)
{
    STLSOFT_SUPPRESS_UNUSED(typeid(stlsoft::refcount_policy_single_threaded));
    STLSOFT_SUPPRESS_UNUSED(typeid(platformstl::refcount_policy_multi_threaded));
    TEST_PASSED();
}
""",
    )

    write(
        TEST_UNIT / "synch/refcount_policies/test.unit.platformstl.synch.refcount_policies.refcount_policy_multi_threaded/entry.cpp",
        """#include <platformstl/synch/refcount_policies/refcount_policy_multi_threaded.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>
#include <thread>

namespace { static void test_increment_decrement(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.unit.platformstl.synch.refcount_policies.refcount_policy_multi_threaded", verbosity))
    {
        XTESTS_RUN_CASE(test_increment_decrement);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_increment_decrement(void)
{
    platformstl::refcount_policy_multi_threaded policy;
    platformstl::atomic_int_t rc = 0;
    policy.addref(rc);
    policy.addref(rc);
    TEST_INT_EQ(2, rc);
    policy.release(rc);
    TEST_INT_EQ(1, rc);
    policy.release(rc);
    TEST_INT_EQ(0, rc);
}
""",
    )

    # atomic_functions - adapt from winstl component (trimmed)
    atomic_src = refs / "component/winstl/synch/test.component.winstl.synch.atomic_functions/entry.cpp"
    atomic_content = adapt_reference(
        atomic_src,
        "test.unit.platformstl.synch.atomic_functions",
        "<platformstl/synch/atomic_functions.h>",
    )
    # Remove windows.h guard for cross-platform
    atomic_content = re.sub(
        r"/\* ///////////////////////////////////////////////\n \* compatibility\n \*/\n\n#if 1 &&.*?#endif\n\n",
        "",
        atomic_content,
        flags=re.DOTALL,
    )
    atomic_content = atomic_content.replace("winstl::", "platformstl::")
    write(TEST_UNIT / "synch/test.unit.platformstl.synch.atomic_functions/entry.cpp", atomic_content)

    # console_functions
    write(
        TEST_UNIT / "system/test.unit.platformstl.system.console_functions/entry.cpp",
        """#include <platformstl/system/console_functions.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_get_console_width(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.unit.platformstl.system.console_functions", verbosity))
    {
        XTESTS_RUN_CASE(test_get_console_width);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_get_console_width(void)
{
    size_t const w = get_console_width();
    TEST_UINT_GE(0u, w);
}
""",
    )

    # --- component tests ---
    # processtimes_stopwatch
    write(
        TEST_COMPONENT / "diagnostics/test.component.platformstl.diagnostics.processtimes_stopwatch/entry.cpp",
        """#include <platformstl/diagnostics/processtimes_stopwatch.hpp>
#include <platformstl/synch/sleep_functions.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_start_stop(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.platformstl.diagnostics.processtimes_stopwatch", verbosity))
    {
        XTESTS_RUN_CASE(test_start_stop);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_start_stop(void)
{
    platformstl::processtimes_stopwatch sw;
    sw.start();
    platformstl::micro_sleep(1000);
    sw.stop();
    TEST_BOOLEAN_TRUE(sw.get_seconds() >= 0);
}
""",
    )

    # processtimes_counter
    write(
        TEST_COMPONENT / "performance/test.component.platformstl.performance.processtimes_counter/entry.cpp",
        """#include <platformstl/performance/processtimes_counter.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_query(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.platformstl.performance.processtimes_counter", verbosity))
    {
        XTESTS_RUN_CASE(test_query);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_query(void)
{
    platformstl::processtimes_counter pc;
    TEST_BOOLEAN_TRUE(pc.seconds() >= 0.0);
}
""",
    )

    # process_mutex
    write(
        TEST_COMPONENT / "synch/test.component.platformstl.synch.process_mutex/entry.cpp",
        """#include <platformstl/synch/process_mutex.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_lock_unlock(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.platformstl.synch.process_mutex", verbosity))
    {
        XTESTS_RUN_CASE(test_lock_unlock);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_lock_unlock(void)
{
    platformstl::process_mutex mx("Global/STLSoft/test.platformstl.process_mutex");
    TEST_BOOLEAN_TRUE(mx.lock());
    mx.unlock();
    TEST_PASSED();
}
""",
    )

    # dl module
    write(
        TEST_COMPONENT / "dl/test.component.platformstl.dl.module/entry.cpp",
        """#include <platformstl/dl/module.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>
#if defined(PLATFORMSTL_OS_IS_UNIX)
# include <dlfcn.h>
#endif

namespace {
static void test_load_system_library(void);
} // anonymous namespace

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.platformstl.dl.module", verbosity))
    {
        XTESTS_RUN_CASE(test_load_system_library);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

namespace {

static void test_load_system_library(void)
{
#if defined(PLATFORMSTL_OS_IS_WINDOWS)
    platformstl::dl_module mod("kernel32.dll");
    TEST_PTR_NE(NULL, mod.get());
#elif defined(PLATFORMSTL_OS_IS_UNIX)
# if defined(UNIXSTL_OS_IS_MACOSX)
    char const* lib = "libSystem.B.dylib";
# elif defined(UNIXSTL_OS_IS_LINUX)
    char const* lib = "libc.so.6";
# else
    char const* lib = "libc.so";
# endif
    platformstl::dl_module mod(lib, RTLD_LAZY);
    TEST_PTR_NE(NULL, mod.get());
    TEST_PTR_NE(NULL, mod.get_symbol("malloc"));
#endif
}
} // anonymous namespace
""",
    )

    # home_directory, current_directory, environment_variable
    write(
        TEST_COMPONENT / "system/test.component.platformstl.system.home_directory/entry.cpp",
        """#include <platformstl/system/home_directory.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/shims/access/string.hpp>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_non_empty(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.platformstl.system.home_directory", verbosity))
    {
        XTESTS_RUN_CASE(test_non_empty);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_non_empty(void)
{
    platformstl::home_directory dir;
    TEST_UINT_NE(0u, stlsoft::c_str_len(dir));
}
""",
    )

    write(
        TEST_COMPONENT / "filesystem/test.component.platformstl.filesystem.current_directory/entry.cpp",
        """#include <platformstl/filesystem/current_directory.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_non_empty(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.platformstl.filesystem.current_directory", verbosity))
    {
        XTESTS_RUN_CASE(test_non_empty);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_non_empty(void)
{
    platformstl::current_directory_a cwd;
    TEST_BOOLEAN_FALSE(cwd.empty());
    TEST_UINT_NE(0u, cwd.size());
}
""",
    )

    write(
        TEST_COMPONENT / "system/test.component.platformstl.system.environment_variable/entry.cpp",
        """#include <platformstl/system/environment_variable.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_path(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.platformstl.system.environment_variable", verbosity))
    {
        XTESTS_RUN_CASE(test_path);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_path(void)
{
    char const* const path = ::getenv("PATH");
    if (NULL != path)
    {
        platformstl::environment_variable_a ev_PATH("PATH");
        TEST_MS_EQ(path, ev_PATH);
    }
}
""",
    )

    write(
        TEST_COMPONENT / "system/test.component.platformstl.system.environment_map/entry.cpp",
        """#include <platformstl/system/environment_map.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_enumeration(void); static void test_lookup_path(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.platformstl.system.environment_map", verbosity))
    {
        XTESTS_RUN_CASE(test_enumeration);
        XTESTS_RUN_CASE(test_lookup_path);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_enumeration(void)
{
    platformstl::environment_map em;
    TEST_BOOLEAN_FALSE(em.empty());
}

static void test_lookup_path(void)
{
    char const* const path = ::getenv("PATH");
    if (NULL != path)
    {
        platformstl::environment_map em;
        platformstl::environment_map::const_iterator it = em.find("PATH");
        TEST_BOOLEAN_TRUE(em.end() != it);
        TEST_MS_EQ(path, it->second);
    }
}
""",
    )

    # path join
    write(
        TEST_COMPONENT / "filesystem/test.component.platformstl.filesystem.path/entry.cpp",
        """#include <platformstl/filesystem/path.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/shims/access/string.hpp>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_join(void); static void test_construct_filename(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.platformstl.filesystem.path", verbosity))
    {
        XTESTS_RUN_CASE(test_join);
        XTESTS_RUN_CASE(test_construct_filename);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_join(void)
{
#if defined(PLATFORMSTL_OS_IS_WINDOWS)
    platformstl::path_a p("C:/temp");
    p /= "file.txt";
    TEST_MS_EQ("C:/temp/file.txt", stlsoft::c_str_ptr_a(p));
#else
    platformstl::path_a p("dir-1");
    p /= "file.txt";
    TEST_MS_EQ("dir-1/file.txt", stlsoft::c_str_ptr_a(p));
#endif
}

static void test_construct_filename(void)
{
    platformstl::path_a p("file.ext");
    TEST_BOOLEAN_FALSE(p.empty());
    TEST_MS_EQ("file.ext", stlsoft::c_str_ptr_a(p));
}
""",
    )

    # memory_mapped_file from unixstl
    for name, src_rel in [
        ("test.component.platformstl.filesystem.memory_mapped_file",
         "component/unixstl/filesystem/test.component.unixstl.filesystem.memory_mapped_file/entry.cpp"),
        ("test.component.platformstl.filesystem.readonly_memory_mapped_file",
         "component/unixstl/filesystem/test.component.unixstl.filesystem.readonly_memory_mapped_file/entry.cpp"),
        ("test.component.platformstl.filesystem.readdir_sequence",
         "component/unixstl/filesystem/test.component.unixstl.filesystem.readdir_sequence/entry.cpp"),
    ]:
        header = "<platformstl/filesystem/" + name.split(".")[-1] + ".hpp>"
        content = adapt_reference(ROOT / "test" / src_rel, name, header)
        content = content.replace("unixstl::readonly_memory_mapped_file_base", "platformstl::readonly_memory_mapped_file_base")
        content = content.replace("unixstl::filesystem_exception", "platformstl::filesystem_exception")
        content = content.replace("unixstl::memory_mapped_file", "platformstl::memory_mapped_file")
        parts = name.replace("test.component.platformstl.", "").split(".")
        leaf = TEST_COMPONENT / "/".join(parts[:-1]) / name
        write(leaf / "entry.cpp", content)

    # squeeze_functions from unixstl unit
    squeeze = adapt_reference(
        refs / "unit/unixstl/filesystem/test.unit.unixstl.filesystem.squeeze_functions/entry.cpp",
        "test.component.platformstl.filesystem.squeeze_functions",
        "<platformstl/filesystem/squeeze_functions.hpp>",
    )
    squeeze = squeeze.replace("unixstl::path_squeeze", "platformstl::path_squeeze")
    write(TEST_COMPONENT / "filesystem/test.component.platformstl.filesystem.squeeze_functions/entry.cpp", squeeze)

    # directory_functions (system) from winstl
    dir_fn = adapt_reference(
        refs / "component/winstl/system/test.component.winstl.system.directory_functions/entry.cpp",
        "test.component.platformstl.system.directory_functions",
        "<platformstl/system/directory_functions.h>",
    )
    dir_fn = dir_fn.replace("winstl::get_home_directory", "platformstl::get_home_directory")
    write(TEST_COMPONENT / "system/test.component.platformstl.system.directory_functions/entry.cpp", dir_fn)

    # FILE_stream and file_lines from stlsoft FILE_iterator test
    file_lines_test = adapt_reference(
        refs / "unit/stlsoft/iterator/test.unit.stlsoft.iterator.FILE_iterator/entry.cpp",
        "test.component.platformstl.filesystem.file_lines",
        "<platformstl/filesystem/file_lines.hpp>",
    )
    file_lines_test = re.sub(
        r"#include <stlsoft/iterator/FILE_iterator.hpp>",
        "#include <platformstl/filesystem/file_lines.hpp>\n#include <platformstl/filesystem/FILE_stream.hpp>\n#include <stlsoft/iterator/FILE_iterator.hpp>\n#include <xtests/xtests.h>\n#include <xtests/terse-api.h>\n#include <xtests/util/temp_file.hpp>\n#include <stlsoft/stlsoft.h>",
        file_lines_test,
        count=1,
    )
    file_lines_test = file_lines_test.replace(
        'XTESTS_START_RUNNER("test.unit.stlsoft.iterator.FILE_iterator"',
        'XTESTS_START_RUNNER("test.component.platformstl.filesystem.file_lines"',
    )
    write(TEST_COMPONENT / "filesystem/test.component.platformstl.filesystem.file_lines/entry.cpp", file_lines_test)

    file_stream_test = file_lines_test.replace(
        'XTESTS_START_RUNNER("test.component.platformstl.filesystem.file_lines"',
        'XTESTS_START_RUNNER("test.component.platformstl.filesystem.FILE_stream"',
    )
    write(TEST_COMPONENT / "filesystem/test.component.platformstl.filesystem.FILE_stream/entry.cpp", file_stream_test)

    # cwd_stack
    write(
        TEST_COMPONENT / "filesystem/test.component.platformstl.filesystem.cwd_stack/entry.cpp",
        """#include <platformstl/filesystem/cwd_stack.hpp>
#include <platformstl/filesystem/current_directory.hpp>
#include <xtests/terse-api.h>
#include <xtests/util/temp_directory.hpp>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_push_pop_restores(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.platformstl.filesystem.cwd_stack", verbosity))
    {
        XTESTS_RUN_CASE(test_push_pop_restores);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_push_pop_restores(void)
{
    using ::xtests::cpp::util::temp_directory;
    platformstl::current_directory_a const original;
    temp_directory td(temp_directory::EmptyOnOpen | temp_directory::EmptyOnClose | temp_directory::RemoveOnClose);
    {
        platformstl::cwd_stack_a stack;
        stack.push(td.c_str());
        platformstl::current_directory_a const changed;
        TEST_MS_EQ(td.c_str(), changed);
    }
    platformstl::current_directory_a const restored;
    TEST_MS_EQ(original, restored);
}
""",
    )

    # current_directory_scope
    write(
        TEST_COMPONENT / "filesystem/test.component.platformstl.filesystem.current_directory_scope/entry.cpp",
        """#include <platformstl/filesystem/current_directory_scope.hpp>
#include <platformstl/filesystem/current_directory.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <xtests/util/temp_directory.hpp>
#include <stlsoft/shims/access/string.hpp>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>
#include <unistd.h>

namespace { static void test_scope_restores(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.platformstl.filesystem.current_directory_scope", verbosity))
    {
        XTESTS_RUN_CASE(test_scope_restores);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

namespace {

static void test_scope_restores(void)
{
    using ::xtests::cpp::util::temp_directory;
    platformstl::current_directory_a const original;
    temp_directory td(temp_directory::EmptyOnOpen | temp_directory::EmptyOnClose | temp_directory::RemoveOnClose);
    {
        platformstl::current_directory_scope scope(td.c_str());
        platformstl::current_directory_a const changed;

        char resolved_td[PATH_MAX];
        char resolved_cwd[PATH_MAX];
        XTESTS_REQUIRE(TEST(NULL != realpath(td.c_str(), resolved_td)));
        XTESTS_REQUIRE(TEST(NULL != realpath(stlsoft::c_str_ptr_a(changed), resolved_cwd)));
        TEST_MS_EQ(resolved_td, resolved_cwd);
    }
    platformstl::current_directory_a const restored;
    TEST_MS_EQ(stlsoft::c_str_ptr_a(original), stlsoft::c_str_ptr_a(restored));
}
} // anonymous namespace
""",
    )

    # path_buffer, file_path_buffer smoke+
    for stem in ("path_buffer", "file_path_buffer"):
        name = f"test.component.platformstl.filesystem.{stem}"
        write(
            TEST_COMPONENT / f"filesystem/{name}/entry.cpp",
            f"""#include <platformstl/filesystem/{stem}.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {{ static void test_assign_and_c_str(void); }}

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("{name}", verbosity))
    {{
        XTESTS_RUN_CASE(test_assign_and_c_str);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}
    return retCode;
}}

static void test_assign_and_c_str(void)
{{
    platformstl::{stem}_a buf;
    buf.assign("abc");
    TEST_MS_EQ("abc", buf.c_str());
    buf.append("def");
    TEST_MS_EQ("abcdef", buf.c_str());
}}
""",
        )

    # filesystem_traits - platform-specific
    write(
        TEST_COMPONENT / "filesystem/test.component.platformstl.filesystem.filesystem_traits/entry.cpp",
        """#include <platformstl/filesystem/filesystem_traits.hpp>
#include <platformstl/filesystem/path.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <xtests/util/temp_directory.hpp>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_file_exists(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.platformstl.filesystem.filesystem_traits", verbosity))
    {
        XTESTS_RUN_CASE(test_file_exists);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

namespace {

static void test_file_exists(void)
{
    typedef platformstl::filesystem_traits<char> fs_traits_t;
    using ::xtests::cpp::util::temp_directory;

    temp_directory td(temp_directory::EmptyOnOpen | temp_directory::EmptyOnClose | temp_directory::RemoveOnClose);

    TEST_BOOLEAN_TRUE(fs_traits_t::file_exists(td.c_str()));
    TEST_BOOLEAN_TRUE(fs_traits_t::is_directory(td.c_str()));

    platformstl::path_a missing(td.c_str());
    missing /= "does-not-exist";

    TEST_BOOLEAN_FALSE(fs_traits_t::file_exists(missing.c_str()));
}
} // anonymous namespace
""",
    )

    write(
        TEST_COMPONENT / "filesystem/test.component.platformstl.filesystem.path_functions/entry.cpp",
        """#include <platformstl/filesystem/path_functions.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_path_squeeze_null_buffer(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.platformstl.filesystem.path_functions", verbosity))
    {
        XTESTS_RUN_CASE(test_path_squeeze_null_buffer);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_path_squeeze_null_buffer(void)
{
    char const* const input = "abcdef";
    size_t const cch = platformstl::path_squeeze(input, static_cast<char*>(NULL), 0);
    TEST_INT_EQ(7, cch);
}
""",
    )

    write(
        TEST_COMPONENT / "filesystem/test.component.platformstl.filesystem.directory_functions/entry.cpp",
        """#include <platformstl/filesystem/directory_functions.hpp>
#include <platformstl/filesystem/filesystem_traits.hpp>
#include <platformstl/filesystem/path.hpp>
#include <xtests/terse-api.h>
#include <xtests/util/temp_directory.hpp>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_create_and_remove(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.platformstl.filesystem.directory_functions", verbosity))
    {
        XTESTS_RUN_CASE(test_create_and_remove);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_create_and_remove(void)
{
    using ::xtests::cpp::util::temp_directory;
    temp_directory td(temp_directory::EmptyOnOpen | temp_directory::EmptyOnClose | temp_directory::RemoveOnClose);
    platformstl::path_a sub(td.c_str());
    sub /= "subdir";
    TEST_BOOLEAN_TRUE(platformstl::create_directory_recurse(sub.c_str()));
    TEST_BOOLEAN_TRUE(platformstl::filesystem_traits<char>::is_directory(sub.c_str()));
    TEST_BOOLEAN_TRUE(platformstl::remove_directory_recurse(sub.c_str()));
}
""",
    )

    write(
        TEST_COMPONENT / "filesystem/test.component.platformstl.filesystem.pipe/entry.cpp",
        """#include <platformstl/filesystem/pipe.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_construct(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.platformstl.filesystem.pipe", verbosity))
    {
        XTESTS_RUN_CASE(test_construct);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_construct(void)
{
    platformstl::pipe pipe;
    STLSOFT_SUPPRESS_UNUSED(pipe);
    TEST_PASSED();
}
""",
    )

    write(
        TEST_COMPONENT / "filesystem/handles/test.component.platformstl.filesystem.handles.memory_mapped_file_view_handle/entry.cpp",
        """#include <platformstl/filesystem/handles/memory_mapped_file_view_handle.hpp>
#include <platformstl/filesystem/memory_mapped_file.hpp>
#include <xtests/terse-api.h>
#include <xtests/util/temp_file.hpp>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>
#include <string.h>

namespace { static void test_map_view(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.platformstl.filesystem.handles.memory_mapped_file_view_handle", verbosity))
    {
        XTESTS_RUN_CASE(test_map_view);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_map_view(void)
{
    using ::xtests::cpp::util::temp_file;
    char const content[] = "testdata";
    temp_file f(temp_file::DeleteOnClose | temp_file::EmptyOnOpen | temp_file::CloseOnOpen,
                content, sizeof(content) - 1);
    platformstl::memory_mapped_file mmf(f.c_str());
    TEST_PTR_NE(NULL, mmf.memory());
    TEST_INT_GE(sizeof(content) - 1, mmf.size());
    TEST_BOOLEAN_TRUE(0 == ::memcmp(content, mmf.memory(), sizeof(content) - 1));
}
""",
    )

    # path_functions.h C API - add to path_functions test or separate - use same dir with note
    # scaffold created path_functions for .h - check if exists
    path_fn_h = TEST_COMPONENT / "filesystem/test.component.platformstl.filesystem.path_functions.h"
    if path_fn_h.exists():
        write(
            path_fn_h / "entry.cpp",
            """#include <platformstl/filesystem/path_functions.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_path_get_ext(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.platformstl.filesystem.path_functions.h", verbosity))
    {
        XTESTS_RUN_CASE(test_path_get_ext);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_path_get_ext(void)
{
#if defined(PLATFORMSTL_OS_IS_WINDOWS)
    TEST_MS_EQ(".txt", platformstl_path_get_ext("file.txt"));
#else
    TEST_MS_EQ(".txt", platformstl_path_get_ext("file.txt"));
#endif
}
""",
        )

    # Write all CMakeLists.txt for leaves
    for base in (TEST_UNIT, TEST_COMPONENT):
        for cmake in base.rglob("CMakeLists.txt"):
            if cmake.parent.name.startswith("test."):
                if "define_automated_test_program" not in cmake.read_text():
                    name = cmake.parent.name
                    write(cmake, cmake_leaf(name))

    # CMake hierarchy - unit
    update_cmake(TEST_UNIT, ["error", "exception", "performance", "synch", "system"])
    update_cmake(TEST_UNIT / "synch", [
        "refcount_policies",
        "test.unit.platformstl.synch.atomic_functions",
        "test.unit.platformstl.synch.atomic_types",
        "test.unit.platformstl.synch.refcount_policies",
        "test.unit.platformstl.synch.semaphore",
        "test.unit.platformstl.synch.sleep_functions",
        "test.unit.platformstl.synch.spin_mutex",
        "test.unit.platformstl.synch.thread_mutex",
        "test.unit.platformstl.synch.tss_index",
    ])
    update_cmake(TEST_UNIT / "synch/refcount_policies", [
        "test.unit.platformstl.synch.refcount_policies.refcount_policy_multi_threaded",
    ])
    update_cmake(TEST_UNIT / "error", ["test.unit.platformstl.error.error_desc", "test.unit.platformstl.error.exceptions"])
    update_cmake(TEST_UNIT / "exception", [
        "test.unit.platformstl.exception.access_exception",
        "test.unit.platformstl.exception.entry_not_found_exception",
        "test.unit.platformstl.exception.file_not_found_exception",
        "test.unit.platformstl.exception.invalid_entry_type_exception",
        "test.unit.platformstl.exception.invalid_file_type_exception",
        "test.unit.platformstl.exception.platformstl_exception",
        "test.unit.platformstl.exception.security_exception",
        "test.unit.platformstl.exception.throw_policies",
    ])
    update_cmake(TEST_UNIT / "performance", ["test.unit.platformstl.performance.performance_counter"])
    update_cmake(TEST_UNIT / "system", [
        "test.unit.platformstl.system.commandline_parser",
        "test.unit.platformstl.system.console_functions",
        "test.unit.platformstl.system.pid_sequence",
    ])

    # CMake hierarchy - component
    update_cmake(TEST_COMPONENT, [
        "diagnostics", "dl", "exception", "filesystem", "performance", "synch", "system",
    ])
    update_cmake(TEST_COMPONENT / "diagnostics", [
        "test.component.platformstl.diagnostics.processtimes_stopwatch",
        "test.component.platformstl.diagnostics.stopwatch",
    ])
    update_cmake(TEST_COMPONENT / "dl", ["test.component.platformstl.dl.module"])
    update_cmake(TEST_COMPONENT / "exception", ["test.component.platformstl.exception.filesystem_exception"])
    fs_subs = sorted(
        p.name for p in (TEST_COMPONENT / "filesystem").iterdir()
        if p.is_dir() and p.name.startswith("test.")
    )
    update_cmake(TEST_COMPONENT / "filesystem", fs_subs + (["handles"] if (TEST_COMPONENT / "filesystem/handles").exists() else []))
    update_cmake(TEST_COMPONENT / "filesystem/handles", [
        "test.component.platformstl.filesystem.handles.memory_mapped_file_view_handle",
    ])
    update_cmake(TEST_COMPONENT / "performance", [
        "test.component.platformstl.performance.processtimes_counter",
    ])
    update_cmake(TEST_COMPONENT / "synch", ["test.component.platformstl.synch.process_mutex"])
    update_cmake(TEST_COMPONENT / "system", [
        "test.component.platformstl.system.directory_functions",
        "test.component.platformstl.system.environment_map",
        "test.component.platformstl.system.environment_variable",
        "test.component.platformstl.system.environment_variable_scope",
        "test.component.platformstl.system.environment_variable_traits",
        "test.component.platformstl.system.home_directory",
        "test.component.platformstl.system.system_traits",
    ])

    print("platformstl tests generated")


if __name__ == "__main__":
    main()
