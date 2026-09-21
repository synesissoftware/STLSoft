#!/usr/bin/env python3
"""Generate UnixSTL unit/component tests with meaningful assertions."""

from __future__ import annotations

import os
from pathlib import Path

from canonical_entry import forward_decls_from_impl_block, render_cpp

ROOT = Path(__file__).resolve().parents[2]
TEST_UNIT = ROOT / "test" / "unit" / "unixstl"
TEST_COMPONENT = ROOT / "test" / "component" / "unixstl"

EXISTING = {
    "test.unit.unixstl.filesystem.path",
    "test.unit.unixstl.filesystem.squeeze_functions",
    "test.unit.unixstl.shims.access.string.timeval",
    "test.component.unixstl.dl.dl_call",
    "test.component.unixstl.filesystem.glob_sequence",
    "test.component.unixstl.filesystem.memory_mapped_file",
    "test.component.unixstl.filesystem.readdir_sequence",
    "test.component.unixstl.filesystem.readonly_memory_mapped_file",
    "test.component.unixstl.system.environment_variable",
}

# (area_path, kind, header, extra_cmake)
TESTS: list[tuple[str, str, str, str]] = [
    # time
    ("time/comparison_functions", "unit", "<unixstl/time/comparison_functions.h>", ""),
    # diagnostics
    ("diagnostics/stopwatch", "component", "<unixstl/diagnostics/stopwatch.hpp>", ""),
    ("diagnostics/processtimes_stopwatch", "component", "<unixstl/diagnostics/processtimes_stopwatch.hpp>", ""),
    # performance (typedef aliases)
    ("performance/performance_counter", "component", "<unixstl/performance/performance_counter.hpp>", ""),
    ("performance/processtimes_counter", "component", "<unixstl/performance/processtimes_counter.hpp>", ""),
    # dl
    ("dl/module", "component", "<unixstl/dl/module.hpp>", "if(UNIX)\n\t"),
    # exception
    ("exception/unixstl_exception", "unit", "<unixstl/exception/unixstl_exception.hpp>", ""),
    ("exception/throw_policies", "unit", "<unixstl/exception/throw_policies.hpp>", ""),
    ("exception/access_exception", "unit", "<unixstl/exception/access_exception.hpp>", ""),
    ("exception/entry_not_found_exception", "unit", "<unixstl/exception/entry_not_found_exception.hpp>", ""),
    ("exception/filesystem_exception", "unit", "<unixstl/exception/filesystem_exception.hpp>", ""),
    ("exception/file_not_found_exception", "unit", "<unixstl/exception/file_not_found_exception.hpp>", ""),
    ("exception/invalid_entry_type_exception", "unit", "<unixstl/exception/invalid_entry_type_exception.hpp>", ""),
    ("exception/invalid_file_type_exception", "unit", "<unixstl/exception/invalid_file_type_exception.hpp>", ""),
    ("exception/operating_environment_exception", "unit", "<unixstl/exception/operating_environment_exception.hpp>", ""),
    ("exception/security_exception", "unit", "<unixstl/exception/security_exception.hpp>", ""),
    # filesystem
    ("filesystem/path_classify_functions", "unit", "<unixstl/filesystem/path_classify_functions.h>", ""),
    ("filesystem/path_parse_functions", "unit", "<unixstl/filesystem/path_parse_functions.h>", ""),
    ("filesystem/filesystem_traits", "unit", "<unixstl/filesystem/filesystem_traits.hpp>", ""),
    ("filesystem/functionals", "unit", "<unixstl/filesystem/functionals.hpp>", ""),
    ("filesystem/path_buffer", "unit", "<unixstl/filesystem/path_buffer.hpp>", ""),
    ("filesystem/file_path_buffer", "unit", "<unixstl/filesystem/file_path_buffer.hpp>", ""),
    ("filesystem/path_functions", "unit", "<unixstl/filesystem/path_functions.hpp>", ""),
    ("filesystem/current_directory", "component", "<unixstl/filesystem/current_directory.hpp>", ""),
    ("filesystem/current_directory_scope", "component", "<unixstl/filesystem/current_directory_scope.hpp>", ""),
    ("filesystem/directory_functions", "component", "<unixstl/filesystem/directory_functions.hpp>", ""),
    ("filesystem/pipe", "component", "<unixstl/filesystem/pipe.hpp>", ""),
    ("filesystem/memory_map_functions", "component", "<unixstl/filesystem/memory_map_functions.h>", ""),
    ("filesystem/handles/memory_mapped_file_view_handle", "component", "<unixstl/filesystem/handles/memory_mapped_file_view_handle.hpp>", ""),
    # shims
    ("shims/access/string/dirent", "unit", "<unixstl/shims/access/string/dirent.hpp>", ""),
    ("shims/conversion/to_uint64/stat", "unit", "<unixstl/shims/conversion/to_uint64/stat.hpp>", ""),
    # synch
    ("synch/atomic_types", "unit", "<unixstl/synch/atomic_types.h>", ""),
    ("synch/atomic_functions", "component", "<unixstl/synch/atomic_functions.h>", ""),
    ("synch/common", "unit", "<unixstl/synch/common.hpp>", ""),
    ("synch/exceptions", "unit", "<unixstl/synch/exceptions.hpp>", ""),
    ("synch/spin_mutex_policies", "unit", "<unixstl/synch/spin_mutex_policies.hpp>", ""),
    ("synch/spin_mutex", "component", "<unixstl/synch/spin_mutex.hpp>", ""),
    ("synch/thread_mutex", "component", "<unixstl/synch/thread_mutex.hpp>", ""),
    ("synch/process_mutex", "component", "<unixstl/synch/process_mutex.hpp>", ""),
    ("synch/semaphore", "component", "<unixstl/synch/semaphore.hpp>", ""),
    ("synch/sleep_functions", "component", "<unixstl/synch/sleep_functions.h>", ""),
    ("synch/tss_index", "component", "<unixstl/synch/tss_index.hpp>", ""),
    # system
    ("system/system_traits", "unit", "<unixstl/system/system_traits.hpp>", ""),
    ("system/directory_functions", "component", "<unixstl/system/directory_functions.h>", ""),
    ("system/console_functions", "component", "<unixstl/system/console_functions.h>", ""),
    ("system/home_directory", "component", "<unixstl/system/home_directory.hpp>", ""),
    ("system/pid_sequence", "component", "<unixstl/system/pid_sequence.hpp>", ""),
]


def test_name(area: str, kind: str) -> str:
    return f"test.{kind}.unixstl.{area.replace('/', '.')}"


def test_body(area: str, kind: str, header: str, name: str) -> str:
    """Return entry.cpp content with meaningful tests per component."""
    bodies = _TEST_BODIES.get(area)
    if bodies:
        return _wrap_entry(name, header, bodies)
    return _wrap_entry(name, header, _default_body(area))


def _wrap_entry(name: str, header: str, body: str) -> str:
    kind_label = "Component" if "component" in name else "Unit"
    funcs = forward_decls_from_impl_block(body) or ["TEST_smoke"]
    if not forward_decls_from_impl_block(body):
        body = _default_body(name.split(".")[-1])
    return render_cpp(
        test_name=name,
        purpose=f"{kind_label}-tests for UnixSTL `{header.strip('<>')}`.",
        includes=[
            header,
            "<xtests/xtests.h>",
            "<xtests/terse-api.h>",
            "<stlsoft/stlsoft.h>",
            "<stdlib.h>",
        ],
        test_functions=funcs,
        implementations=body,
    )


def _main_cases(body: str) -> str:
    import re
    cases = re.findall(r"static void (test_\w+)\(", body)
    if not cases:
        cases = re.findall(r"static void (TEST_\w+)\(", body)
    return "\n".join(f"        XTESTS_RUN_CASE({c});" for c in cases)


# Per-area test implementations
_TEST_BODIES: dict[str, str] = {}


def _default_body(area: str) -> str:
    return f"""static void TEST_smoke()
{{
    TEST_PASSED();
}}
"""


def _reg(area: str, body: str) -> None:
    _TEST_BODIES[area] = body


_reg(
    "time/comparison_functions",
    """
static void test_equal_timevals()
{
    struct timeval lhs = { 100, 500 };
    struct timeval rhs = { 100, 500 };

    TEST_INT_EQ(0, unixstl::compare(lhs, rhs));
    TEST_INT_EQ(0, unixstl::compare(&lhs, &rhs));
}

static void test_lhs_before_rhs()
{
    struct timeval lhs = { 100, 0 };
    struct timeval rhs = { 101, 0 };

    TEST_INT_EQ(-1, unixstl::compare(lhs, rhs));
}

static void test_lhs_after_rhs()
{
    struct timeval lhs = { 200, 1000 };
    struct timeval rhs = { 199, 999999 };

    TEST_INT_EQ(+1, unixstl::compare(lhs, rhs));
}

static void test_microsecond_difference()
{
    struct timeval lhs = { 1, 0 };
    struct timeval rhs = { 1, 42 };

    TEST_INT_EQ(-1, unixstl::compare(lhs, rhs));
}
""",
)

_reg(
    "diagnostics/stopwatch",
    """
#include <unistd.h>

static void test_static_interval_helpers()
{
    unixstl::stopwatch::epoch_type start = { 10, 0 };
    unixstl::stopwatch::epoch_type end   = { 12, 500000 };

    TEST_INT_EQ(2, unixstl::stopwatch::get_seconds(start, end));
    TEST_INT_EQ(2500, unixstl::stopwatch::get_milliseconds(start, end));
    TEST_INT_EQ(2500000, unixstl::stopwatch::get_microseconds(start, end));
}

static void test_start_stop_elapsed()
{
    unixstl::stopwatch sw;

    sw.start();
    ::usleep(50000);
    sw.stop();

    TEST_INT_GE(0, sw.get_seconds());
    TEST_INT_GE(40000, sw.get_microseconds());
}

static void test_pause_unpause()
{
    unixstl::stopwatch sw;

    sw.start();
    ::usleep(20000);
    sw.pause();
    ::usleep(50000);
    sw.unpause();
    ::usleep(20000);
    sw.stop();

    unixstl::stopwatch::interval_type const us = sw.get_microseconds();

    TEST_INT_GE(30000, us);
    TEST_INT_LT(90000, us);
}

static void test_restart_and_stop_get()
{
    unixstl::stopwatch sw;

    sw.start();
    ::usleep(10000);
    sw.stop();

    unixstl::stopwatch::interval_type const first = sw.stop_get_microseconds_and_restart();

    TEST_INT_GE(5000, first);

    ::usleep(10000);
    sw.stop();

    TEST_INT_GE(5000, sw.get_microseconds());
}
""",
)

_reg(
    "diagnostics/processtimes_stopwatch",
    """
static void test_process_time_increases_with_work()
{
    unixstl::processtimes_stopwatch sw;

    sw.start();

    volatile unsigned long n = 0;
    for (unsigned i = 0; i != 1000000; ++i)
    {
        n += i;
    }

    sw.stop();

    TEST_INT_GE(0, sw.get_user_microseconds());
    TEST_INT_GE(0, sw.get_kernel_microseconds());
    TEST_INT_GE(0, sw.get_microseconds());
    STLSOFT_SUPPRESS_UNUSED(n);
}

static void test_total_is_sum_of_user_and_kernel()
{
    unixstl::processtimes_stopwatch sw;

    sw.start();
    volatile unsigned long n = 0;
    for (unsigned i = 0; i != 500000; ++i) { n += i; }
    sw.stop();

    unixstl::processtimes_stopwatch::interval_type const total = sw.get_period_count();
    unixstl::processtimes_stopwatch::interval_type const sum =
        sw.get_user_period_count() + sw.get_kernel_period_count();

    TEST_INT_EQ(sum, total);
    STLSOFT_SUPPRESS_UNUSED(n);
}
""",
)

_reg(
    "performance/performance_counter",
    """
#include <unistd.h>

static void test_is_stopwatch_alias()
{
    unixstl::performance_counter pc;

    pc.start();
    ::usleep(10000);
    pc.stop();

    TEST_INT_GE(0, pc.get_microseconds());
}
""",
)

_reg(
    "performance/processtimes_counter",
    """
static void test_is_processtimes_stopwatch_alias()
{
    unixstl::processtimes_counter pc;

    pc.start();
    volatile unsigned long n = 0;
    for (unsigned i = 0; i != 100000; ++i) { n += i; }
    pc.stop();

    TEST_INT_GE(0, pc.get_user_microseconds());
    STLSOFT_SUPPRESS_UNUSED(n);
}
""",
)

_reg(
    "dl/module",
    """
#include <dlfcn.h>

static void test_load_self_and_lookup_main()
{
    void* h = ::dlopen(NULL, RTLD_LAZY);

    XTESTS_REQUIRE(TEST(NULL != h));

    void* sym = unixstl::dl_module::get_symbol(h, "main");

    TEST_PTR_NE(NULL, sym);

    unixstl::dl_module::unload(h);
}

static void test_raii_module_loads_libc()
{
#if defined(UNIXSTL_OS_IS_MACOSX)
    char const* lib = "libSystem.B.dylib";
#elif defined(UNIXSTL_OS_IS_LINUX)
    char const* lib = "libc.so.6";
#else
    char const* lib = "libc.so";
#endif

    unixstl::dl_module m(lib, RTLD_LAZY);

    TEST_PTR_NE(NULL, m.get());

    void* sym = m.get_symbol("malloc");
    TEST_PTR_NE(NULL, sym);
}

static void test_get_module_handle_shim()
{
#if defined(UNIXSTL_OS_IS_MACOSX)
    char const* lib = "libSystem.B.dylib";
#elif defined(UNIXSTL_OS_IS_LINUX)
    char const* lib = "libc.so.6";
#else
    char const* lib = "libc.so";
#endif

    unixstl::dl_module m(lib, RTLD_LAZY);

    TEST_PTR_EQ(m.get(), unixstl::get_module_handle(m));
}
""",
)

_reg(
    "exception/unixstl_exception",
    """
static void test_status_code_and_message()
{
#ifdef STLSOFT_CF_EXCEPTION_SUPPORT
    unixstl::unixstl_exception x(ENOENT);

    TEST_INT_EQ(ENOENT, x.status_code());
    TEST_PTR_NE(NULL, x.what());

    unixstl::unixstl_exception x2("reason", EACCES);
    TEST_INT_EQ(EACCES, x2.status_code());
    TEST_PTR_NE(NULL, x2.what());
#endif
}
""",
)

_reg(
    "exception/throw_policies",
    """
static void test_unix_exception_policy_throws()
{
#ifdef STLSOFT_CF_EXCEPTION_SUPPORT
    try
    {
        unixstl::unix_exception_policy()(ENOENT);
        TEST_FAIL("expected exception");
    }
    catch (unixstl::unixstl_exception const& x)
    {
        TEST_INT_EQ(ENOENT, x.status_code());
    }

    try
    {
        unixstl::unix_exception_policy()("reason", EACCES);
        TEST_FAIL("expected exception");
    }
    catch (unixstl::unixstl_exception const& x)
    {
        TEST_INT_EQ(EACCES, x.status_code());
    }
#endif
}
""",
)

_reg(
    "exception/access_exception",
    """
static void test_inherits_unixstl_exception()
{
#ifdef STLSOFT_CF_EXCEPTION_SUPPORT
    unixstl::access_exception x("access denied", EACCES);

    TEST_INT_EQ(EACCES, x.status_code());
    TEST_PTR_NE(NULL, x.what());
#endif
}
""",
)

_reg(
    "exception/entry_not_found_exception",
    """
static void test_carries_path()
{
#ifdef STLSOFT_CF_EXCEPTION_SUPPORT
    unixstl::entry_not_found_exception x("/missing/entry", ENOENT);

    TEST_INT_EQ(ENOENT, x.status_code());
    TEST_PTR_NE(NULL, x.what());
#endif
}
""",
)

_reg(
    "exception/filesystem_exception",
    """
static void test_filesystem_exception()
{
#ifdef STLSOFT_CF_EXCEPTION_SUPPORT
    unixstl::filesystem_exception x("/path", ENOENT);

    TEST_INT_EQ(ENOENT, x.status_code());
#endif
}
""",
)

_reg(
    "exception/file_not_found_exception",
    """
static void test_file_not_found()
{
#ifdef STLSOFT_CF_EXCEPTION_SUPPORT
    unixstl::file_not_found_exception x("/no/such/file", ENOENT);

    TEST_INT_EQ(ENOENT, x.status_code());
#endif
}
""",
)

_reg(
    "exception/invalid_entry_type_exception",
    """
static void test_invalid_entry_type()
{
#ifdef STLSOFT_CF_EXCEPTION_SUPPORT
    unixstl::invalid_entry_type_exception x("/entry", EINVAL);

    TEST_INT_EQ(EINVAL, x.status_code());
#endif
}
""",
)

_reg(
    "exception/invalid_file_type_exception",
    """
static void test_invalid_file_type()
{
#ifdef STLSOFT_CF_EXCEPTION_SUPPORT
    unixstl::invalid_file_type_exception x("/file", EINVAL);

    TEST_INT_EQ(EINVAL, x.status_code());
#endif
}
""",
)

_reg(
    "exception/operating_environment_exception",
    """
static void test_operating_environment()
{
#ifdef STLSOFT_CF_EXCEPTION_SUPPORT
    unixstl::operating_environment_exception x("env", ENOENT);

    TEST_INT_EQ(ENOENT, x.status_code());
#endif
}
""",
)

_reg(
    "exception/security_exception",
    """
static void test_security_exception()
{
#ifdef STLSOFT_CF_EXCEPTION_SUPPORT
    unixstl::security_exception x("/secure", EACCES);

    TEST_INT_EQ(EACCES, x.status_code());
#endif
}
""",
)

_reg(
    "filesystem/path_classify_functions",
    """
static void test_empty_path()
{
    unixstl_C_path_classification_results_m_t results = {};

    int const r = unixstl_C_path_classify_m("", 0, UNIXSTL_PATH_CLASSIFY_F_NONE, &results);

    TEST_INT_EQ(UNIXSTL_C_PathType_Empty, r);
}

static void test_relative_path()
{
    unixstl_C_path_classification_results_m_t results = {};

    char const path[] = "dir/file.txt";
    int const r = unixstl_C_path_classify_m(path, strlen(path), UNIXSTL_PATH_CLASSIFY_F_NONE, &results);

    TEST_INT_EQ(UNIXSTL_C_PathType_Relative, r);
    TEST_INT_GE(1u, results.numDirectoryParts);
}

static void test_slash_rooted()
{
    unixstl_C_path_classification_results_m_t results = {};

    char const path[] = "/usr/bin";
    int const r = unixstl_C_path_classify_m(path, strlen(path), UNIXSTL_PATH_CLASSIFY_F_NONE, &results);

    TEST_INT_EQ(UNIXSTL_C_PathType_SlashRooted, r);
}

static void test_home_rooted_with_flag()
{
    unixstl_C_path_classification_results_m_t results = {};

    char const path[] = "~/projects";
    int const r = unixstl_C_path_classify_m(path, strlen(path), UNIXSTL_PATH_CLASSIFY_F_RECOGNISETILDEHOME, &results);

    TEST_INT_EQ(UNIXSTL_C_PathType_HomeRooted, r);
}
""",
)

_reg(
    "filesystem/path_parse_functions",
    """
static void test_find_first_separator()
{
    char const path[] = "dir/sub/file";

    TEST_PTR_EQ(path + 3, unixstl_C_find_first_path_name_separator_m(path));
    TEST_PTR_EQ(path + 3, unixstl::find_first_path_name_separator(path));
}

static void test_find_last_separator()
{
    char const path[] = "dir/sub/file";

    TEST_PTR_EQ(path + 7, unixstl_C_find_last_path_name_separator_m(path));
    TEST_PTR_EQ(path + 7, unixstl::find_last_path_name_separator(path));
}

static void test_no_separator()
{
    char const path[] = "fileonly";

    TEST_PTR_EQ(NULL, unixstl_C_find_first_path_name_separator_m(path));
    TEST_PTR_EQ(NULL, unixstl_C_find_last_path_name_separator_m(path));
}

static void test_bounded_search()
{
    char const path[] = "a/b/c";
    size_t const len = 3; /* "a/b" */

    TEST_PTR_EQ(path + 1, unixstl_C_find_first_path_name_separator_len_m(path, len));
    TEST_PTR_EQ(path + 1, unixstl_C_find_last_path_name_separator_len_m(path, len));
}
""",
)

_reg(
    "filesystem/filesystem_traits",
    """
typedef unixstl::filesystem_traits<char> fs_traits_t;

static unixstl::path_classification_t classify_path(char const* path)
{
    unixstl::path_classification_results_m_t results = {};

    return static_cast<unixstl::path_classification_t>(
        fs_traits_t::path_classify(path, ::strlen(path), UNIXSTL_PATH_CLASSIFY_F_NONE, &results));
}

static void test_path_separators()
{
    TEST_CHAR_EQ('/', fs_traits_t::path_name_separator());
    TEST_CHAR_EQ(':', fs_traits_t::path_separator());
}

static void test_path_is_rooted()
{
    TEST_BOOLEAN_TRUE(fs_traits_t::path_is_rooted(classify_path("/")));
    TEST_BOOLEAN_TRUE(fs_traits_t::path_is_rooted(classify_path("/usr")));
    TEST_BOOLEAN_FALSE(fs_traits_t::path_is_rooted(classify_path("relative")));
}

static void test_starts_with_dots()
{
    TEST_BOOLEAN_TRUE(fs_traits_t::starts_with_dots("."));
    TEST_BOOLEAN_TRUE(fs_traits_t::starts_with_dots(".."));
    TEST_BOOLEAN_FALSE(fs_traits_t::starts_with_dots("file"));
}

static void test_ensure_and_remove_dir_end()
{
    char buf1[8] = "dir";
    fs_traits_t::ensure_dir_end(buf1);
    TEST_CHAR_EQ('/', buf1[3]);
    TEST_CHAR_EQ('\\0', buf1[4]);

    char buf2[] = "dir/";
    fs_traits_t::remove_dir_end(buf2);
    TEST_MS_EQ("dir", buf2);
}
""",
)
)

_reg(
    "filesystem/functionals",
    """
typedef unixstl::path_compare<char> path_compare_t;

static void test_path_compare_equal()
{
    path_compare_t cmp;

    TEST_BOOLEAN_TRUE(cmp("a/b", "a/b"));
    TEST_BOOLEAN_FALSE(cmp("a/b", "a/c"));
}

static void test_path_compare_rooted()
{
    path_compare_t cmp;

    TEST_BOOLEAN_TRUE(cmp("/usr/bin", "/usr/bin"));
    TEST_BOOLEAN_FALSE(cmp("/usr/bin", "/usr/lib"));
}
""",
)

_reg(
    "filesystem/path_buffer",
    """
static void test_default_constructed_empty()
{
    unixstl::path_buffer_a buf;

    TEST_INT_EQ(0, buf.size());
    TEST_MS_EQ("", buf.c_str());
}

static void test_assign_and_clear()
{
    unixstl::path_buffer_a buf;

    buf.assign("hello/world", ::strlen("hello/world"));
    TEST_MS_EQ("hello/world", buf.c_str());

    buf.assign("", 0);
    TEST_INT_EQ(0, buf.size());
}
""",
)

_reg(
    "filesystem/file_path_buffer",
    """
#include <string.h>

#include <stlsoft/internal/warnings/push/suppress_deprecation_.h>

static void test_file_path_buffer()
{
    unixstl::file_path_buffer_a buf;

    ::strcpy(buf.data(), "/tmp/example.txt");
    TEST_MS_EQ("/tmp/example.txt", buf.c_str());
    TEST_INT_GT(0, buf.size());
}
""",
)

_reg(
    "filesystem/path_functions",
    """
static void test_aggregate_includes_path_parse()
{
    char const path[] = "a/b";

    TEST_PTR_EQ(path + 1, unixstl::find_first_path_name_separator(path));
}

static void test_aggregate_includes_path_classify()
{
    unixstl_C_path_classification_results_m_t results = {};

    int const r = unixstl_C_path_classify_m("file.txt", 8, UNIXSTL_PATH_CLASSIFY_F_NONE, &results);

    TEST_INT_EQ(UNIXSTL_C_PathType_Relative, r);
}
""",
)

_reg(
    "filesystem/current_directory",
    """
static void test_get_current_directory()
{
    unixstl::current_directory_a cwd;

    TEST_INT_GT(0, cwd.length());
    TEST_PTR_NE(NULL, cwd.c_str());
    TEST_CHAR_EQ('\\0', cwd.c_str()[cwd.length()]);
}
""",
)

_reg(
    "filesystem/current_directory_scope",
    """
#include <unixstl/filesystem/path.hpp>
#include <xtests/util/temp_directory.hpp>
#include <unistd.h>
#include <string>

using xtests::cpp::util::temp_directory;

static void test_scope_restores_directory()
{
    char original[PATH_MAX];
    XTESTS_REQUIRE(TEST(NULL != getcwd(original, sizeof(original))));

    std::string const saved(original);

    {
        temp_directory td(temp_directory::EmptyOnOpen | temp_directory::RemoveOnClose);
        unixstl::current_directory_scope_a scope(td.c_str());

        char now[PATH_MAX];
        XTESTS_REQUIRE(TEST(NULL != getcwd(now, sizeof(now))));

        char resolved_td[PATH_MAX];
        char resolved_now[PATH_MAX];
        XTESTS_REQUIRE(TEST(NULL != realpath(td.c_str(), resolved_td)));
        XTESTS_REQUIRE(TEST(NULL != realpath(now, resolved_now)));
        TEST_MS_EQ(resolved_td, resolved_now);
    }

    char restored[PATH_MAX];
    XTESTS_REQUIRE(TEST(NULL != getcwd(restored, sizeof(restored))));
    TEST_MS_EQ(saved, restored);
}
""",
)
)

_reg(
    "filesystem/directory_functions",
    """
#include <xtests/util/temp_directory.hpp>
#include <sys/stat.h>

using xtests::cpp::util::temp_directory;

typedef unixstl::filesystem_traits<char> fs_traits_t;

static void test_create_directory_recurse()
{
    temp_directory td(temp_directory::EmptyOnOpen | temp_directory::RemoveOnClose);

    unixstl::path_a sub(td.c_str());
    sub /= "a/b/c";

    TEST_BOOLEAN_TRUE(unixstl::create_directory_recurse(sub.c_str()));

    struct stat st;
    TEST_INT_EQ(0, ::stat(sub.c_str(), &st));
    TEST_BOOLEAN_TRUE(S_ISDIR(st.st_mode));
}

static void test_remove_directory_recurse()
{
    temp_directory td(temp_directory::EmptyOnOpen | temp_directory::RemoveOnClose);

    unixstl::path_a sub(td.c_str());
    sub /= "remove-me";

    TEST_BOOLEAN_TRUE(fs_traits_t::create_directory(sub.c_str()));
    TEST_BOOLEAN_TRUE(unixstl::remove_directory_recurse(sub.c_str()));
    TEST_BOOLEAN_FALSE(fs_traits_t::file_exists(sub.c_str()));
}
""",
)

_reg(
    "filesystem/pipe",
    """
static void test_anonymous_pipe_read_write()
{
    unixstl::pipe pipe;

    char const msg[] = "pipe-data";
    ssize_t const written = ::write(pipe.write_handle(), msg, sizeof(msg));

    TEST_INT_EQ((ssize_t)sizeof(msg), written);

    char buf[32] = { 0 };
    ssize_t const readn = ::read(pipe.read_handle(), buf, sizeof(buf));

    TEST_INT_EQ((ssize_t)sizeof(msg), readn);
    TEST_MS_EQ(msg, buf);
}
""",
)

_reg(
    "filesystem/memory_map_functions",
    """
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <xtests/util/temp_directory.hpp>

using xtests::cpp::util::temp_directory;

static void test_unmap_view_of_file()
{
    temp_directory td(temp_directory::EmptyOnOpen | temp_directory::RemoveOnClose);

    unixstl::path_a file(td.c_str());
    file /= "maptest.bin";

    int fd = ::open(file.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0644);
    XTESTS_REQUIRE(TEST(-1 != fd));

    char const payload[] = "mmap-payload";
    XTESTS_REQUIRE(TEST((ssize_t)sizeof(payload) == ::write(fd, payload, sizeof(payload))));

    void* p = ::mmap(NULL, sizeof(payload), PROT_READ, MAP_SHARED, fd, 0);
    XTESTS_REQUIRE(TEST(MAP_FAILED != p));

    TEST_MS_EQ(payload, static_cast<char const*>(p));

    unixstl::unmap_view_of_file(p, sizeof(payload));
    ::close(fd);
}
""",
)

_reg(
    "filesystem/handles/memory_mapped_file_view_handle",
    """
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <xtests/util/temp_directory.hpp>
#include <stlsoft/synch/refcount_policies/refcount_policy_single_threaded.hpp>

using xtests::cpp::util::temp_directory;

typedef unixstl::memory_mapped_file_view_handle<stlsoft::refcount_policy_single_threaded> view_handle_t;

static void test_view_handle_create_and_destroy()
{
    temp_directory td(temp_directory::EmptyOnOpen | temp_directory::RemoveOnClose);

    unixstl::path_a file(td.c_str());
    file /= "view.bin";

    int fd = ::open(file.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0644);
    XTESTS_REQUIRE(TEST(-1 != fd));

    char const data[] = "view-handle";
    XTESTS_REQUIRE(TEST((ssize_t)sizeof(data) == ::write(fd, data, sizeof(data))));

    void* p = ::mmap(NULL, sizeof(data), PROT_READ, MAP_SHARED, fd, 0);
    XTESTS_REQUIRE(TEST(MAP_FAILED != p));

  {
        view_handle_t::Ref ref = view_handle_t::create(p, sizeof(data));

        TEST_PTR_EQ(p, ref->handle.memory);
        TEST_INT_EQ(sizeof(data), ref->handle.size);
    }

    ::close(fd);
}
""",
)

_reg(
    "shims/access/string/dirent",
    """
#include <dirent.h>
#include <string.h>

static void test_c_str_data_null()
{
    TEST_MS_EQ("", stlsoft::c_str_data_a(static_cast<struct dirent const*>(NULL)));
    TEST_MS_EQ("", stlsoft::c_str_data(static_cast<struct dirent const*>(NULL)));
}

static void test_c_str_ptr_with_name()
{
    struct dirent entry;
    strcpy(entry.d_name, "filename.ext");

    TEST_MS_EQ("filename.ext", stlsoft::c_str_ptr_a(&entry));
    TEST_INT_EQ(strlen("filename.ext"), stlsoft::c_str_len_a(&entry));
}
""",
)

_reg(
    "shims/conversion/to_uint64/stat",
    """
#include <sys/stat.h>

static void test_to_uint64_from_stat()
{
    struct stat st = {};
    st.st_size = 12345;

    stlsoft::ss_uint64_t const v = stlsoft::to_uint64(st);

    TEST_BOOLEAN_TRUE(stlsoft::ss_uint64_t(12345) == v);
}
""",
)
)

_reg(
    "synch/atomic_types",
    """
#include <stlsoft/meta/is_integral_type.hpp>

static void test_atomic_int_type_is_integral()
{
    static_assert(stlsoft::is_integral_type<unixstl::atomic_int_t>::value, "atomic_int_t must be integral");
    TEST_PASSED();
}
""",
)

_reg(
    "synch/atomic_functions",
    """
static void test_atomic_increment_decrement()
{
    unixstl::atomic_int_t n = 0;

    TEST_INT_EQ(1, unixstl::atomic_increment(&n));
    TEST_INT_EQ(1, n);

    TEST_INT_EQ(0, unixstl::atomic_decrement(&n));
    TEST_INT_EQ(0, n);
}

static void test_atomic_exchange()
{
    unixstl::atomic_int_t n = 5;

    TEST_INT_EQ(5, unixstl::atomic_exchange(&n, 9));
    TEST_INT_EQ(9, n);
}
""",
)

_reg(
    "synch/common",
    """
static void test_common_header_compiles()
{
#ifdef UNIXSTL_USING_PTHREADS
    TEST_BOOLEAN_TRUE(true);
#else
    TEST_PASSED();
#endif
}
""",
)

_reg(
    "synch/exceptions",
    """
static void test_synch_exception_carries_code()
{
#ifdef STLSOFT_CF_EXCEPTION_SUPPORT
    unixstl::synchronisation_exception x("lock failed", EINVAL);
    TEST_INT_EQ(EINVAL, x.status_code());
    TEST_PTR_NE(NULL, x.what());
#endif
}
""",
)

_reg(
    "synch/spin_mutex_policies",
    """
static void test_default_policy_type_exists()
{
    STLSOFT_SUPPRESS_UNUSED(typeid(unixstl::yield_on_N_spin_mutex_policy<1000>));
    TEST_PASSED();
}
""",
)

_reg(
    "synch/spin_mutex",
    """
#include <stlsoft/synch/lock_scope.hpp>

static void test_lock_unlock()
{
    unixstl::spin_mutex mx;

    mx.lock();
    TEST_PASSED();
    mx.unlock();
}

static void test_lock_scope()
{
    unixstl::spin_mutex mx;
    stlsoft::lock_scope<unixstl::spin_mutex> lock(mx);
    TEST_PASSED();
}
""",
)

_reg(
    "synch/thread_mutex",
    """
#include <stlsoft/synch/lock_scope.hpp>

static void test_thread_mutex_lock_unlock()
{
    unixstl::thread_mutex mx;

    mx.lock();
    TEST_PASSED();
    mx.unlock();
}

static void test_thread_mutex_try_lock()
{
    unixstl::thread_mutex mx;

    TEST_BOOLEAN_TRUE(mx.try_lock());
    mx.unlock();
}
""",
)

_reg(
    "synch/process_mutex",
    """
#include <stlsoft/synch/lock_scope.hpp>

static void test_process_mutex_lock_unlock()
{
    unixstl::process_mutex mx;

    mx.lock();
    TEST_PASSED();
    mx.unlock();
}
""",
)

_reg(
    "synch/semaphore",
    """
static void test_semaphore_wait_post()
{
    unixstl::semaphore sem(0);

    sem.unlock();

    sem.lock();
    TEST_PASSED();
}
""",
)

_reg(
    "synch/sleep_functions",
    """
#include <sys/time.h>

static void test_micro_sleep_returns()
{
    struct timeval start;
    struct timeval end;

    ::gettimeofday(&start, NULL);
    unixstl::micro_sleep(50000);
    ::gettimeofday(&end, NULL);

    long const elapsed_ms = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) / 1000;

    TEST_INT_GE(30, elapsed_ms);
}
""",
)

_reg(
    "synch/tss_index",
    """
static void test_tss_index_set_get()
{
    unixstl::tss_index idx;

    idx.set_value(reinterpret_cast<void*>(0x1234));
    TEST_PTR_EQ(reinterpret_cast<void*>(0x1234), idx.get_value());
}
""",
)

_reg(
    "system/system_traits",
    """
typedef unixstl::system_traits<char> sys_traits_t;

static void test_get_current_directory()
{
    char buf[PATH_MAX];

    size_t const n = sys_traits_t::get_current_directory(STLSOFT_NUM_ELEMENTS(buf), buf);

    TEST_INT_GT(0u, n);
    TEST_CHAR_EQ('\\0', buf[n]);
}

static void test_environment_variable_exists()
{
    char const* path = sys_traits_t::get_environment_variable("PATH");

    if (NULL != path)
    {
        TEST_INT_GT(0, ::strlen(path));
    }
}
""",
)

_reg(
    "system/directory_functions",
    """
static void test_get_home_directory()
{
    char buf[PATH_MAX];

    size_t const n = unixstl::get_home_directory(buf, STLSOFT_NUM_ELEMENTS(buf));

    TEST_INT_GT(0u, n);
    TEST_CHAR_EQ('/', buf[0]);
}
""",
)

_reg(
    "system/console_functions",
    """
static void test_get_console_width()
{
    int const w = unixstl::get_console_width();

    if (w >= 0)
    {
        TEST_INT_GT(0, w);
    }
    else
    {
        /* No controlling terminal in this environment. */
        TEST_PASSED();
    }
}
""",
)
)

_reg(
    "system/home_directory",
    """
static void test_home_directory_non_empty()
{
    unixstl::home_directory_a home;

    TEST_INT_GT(0, home.length());
    TEST_CHAR_EQ('/', home.c_str()[0]);
}
""",
)

_reg(
    "system/pid_sequence",
    """
static void test_pid_sequence_contains_self()
{
    unixstl::pid_sequence pids;

    TEST_BOOLEAN_FALSE(pids.empty());

    pid_t const self = ::getpid();
    bool found = false;

    for (unixstl::pid_sequence::const_iterator i = pids.begin(); i != pids.end(); ++i)
    {
        if (*i == self)
        {
            found = true;
            break;
        }
    }

    TEST_BOOLEAN_TRUE(found);
}
""",
)


PTHREAD_TESTS = {
    "test.component.unixstl.synch.thread_mutex",
    "test.component.unixstl.synch.process_mutex",
}

TSS_INDEX_TEST = "test.component.unixstl.synch.tss_index"


def write_test(area: str, kind: str, header: str, extra_cmake: str) -> None:
    name = test_name(area, kind)
    if name in EXISTING:
        return

    base = TEST_COMPONENT if kind == "component" else TEST_UNIT
    parts = area.split("/")
    leaf = base.joinpath(*parts[:-1], name)

    leaf.mkdir(parents=True, exist_ok=True)

    (leaf / "entry.cpp").write_text(test_body(area, kind, header, name))

    cmake = f"define_automated_test_program({name} entry.cpp)\n"
    if name in PTHREAD_TESTS:
        cmake += f"target_compile_options({name} PRIVATE -pthread)\n"
        cmake += f"target_compile_definitions({name} PRIVATE _REENTRANT)\n"
        cmake += f"target_link_options({name} PRIVATE -pthread)\n"
    elif name == TSS_INDEX_TEST:
        cmake += f"target_compile_options({name} PRIVATE -pthread -Wno-deprecated-copy)\n"
        cmake += f"target_compile_definitions({name} PRIVATE _REENTRANT)\n"
        cmake += f"target_link_options({name} PRIVATE -pthread)\n"
    (leaf / "CMakeLists.txt").write_text(cmake)


def write_cmake_parents() -> None:
    """Regenerate intermediate CMakeLists.txt add_subdirectory chains."""
    for base, kind_prefix in ((TEST_UNIT, "unit"), (TEST_COMPONENT, "component")):
        areas: dict[str, set[str]] = {}
        for area, kind, _, _ in TESTS:
            if kind != kind_prefix.replace("unit", "unit") and kind != ("component" if base == TEST_COMPONENT else "unit"):
                continue
            name = test_name(area, kind)
            if name in EXISTING:
                continue
            if kind != ("component" if base == TEST_COMPONENT else "unit"):
                continue
            top = area.split("/")[0]
            areas.setdefault(top, set()).add(area)

        # rebuild per top-level area
        for top, subareas in sorted(areas.items()):
            # collect all intermediate dirs
            dirs_needed: set[Path] = set()
            test_dirs: dict[Path, str] = {}
            for area in subareas:
                name = test_name(area, "component" if base == TEST_COMPONENT else "unit")
                rel = Path(*area.split("/"))
                test_dirs[base / rel.parent / name] = name
                for i in range(1, len(rel.parts)):
                    dirs_needed.add(base / Path(*rel.parts[:i]))

            for d in sorted(dirs_needed):
                d.mkdir(parents=True, exist_ok=True)

            # write leaf cmake parent dirs bottom-up
            by_parent: dict[Path, list[str]] = {}
            for path, name in test_dirs.items():
                by_parent.setdefault(path.parent, []).append(name)

            for parent, names in by_parent.items():
                lines = sorted(f"add_subdirectory({n})" for n in names)
                content = "# SIS:AUTO_GENERATED: Remove this line if you edit the file, otherwise it will be overwritten\n"
                content += "\n".join(lines) + "\n"
                (parent / "CMakeLists.txt").write_text(content)

            # intermediate dirs that only have subdirs
            for d in sorted(dirs_needed):
                subdirs = [p.name for p in d.iterdir() if p.is_dir() and (p / "CMakeLists.txt").exists() and p.name != f"test.{kind_prefix}"]
                # only write if not a test leaf parent already written
                if (d / "CMakeLists.txt").exists():
                    continue
                child_cmake = [p for p in d.iterdir() if p.is_dir() and (p / "CMakeLists.txt").exists()]
                if child_cmake:
                    lines = sorted(f"add_subdirectory({p.name})" for p in child_cmake)
                    content = "# SIS:AUTO_GENERATED: Remove this line if you edit the file, otherwise it will be overwritten\n"
                    content += "\n".join(lines) + "\n"
                    (d / "CMakeLists.txt").write_text(content)

        # top-level unixstl CMakeLists
        top_dirs = sorted(areas.keys())
        root_cmake = TEST_UNIT if base == TEST_UNIT else TEST_COMPONENT
        existing_lines = []
        if (root_cmake / "CMakeLists.txt").exists():
            existing_lines = (root_cmake / "CMakeLists.txt").read_text().splitlines()
        existing_subs = {l.split("(")[1].rstrip(")") for l in existing_lines if l.startswith("add_subdirectory(")}
        all_subs = existing_subs | set(top_dirs)
        content = "# SIS:AUTO_GENERATED: Remove this line if you edit the file, otherwise it will be overwritten\n"
        content += "\n".join(f"add_subdirectory({s})" for s in sorted(all_subs)) + "\n"
        (root_cmake / "CMakeLists.txt").write_text(content)


def main() -> None:
    for area, kind, header, extra in TESTS:
        write_test(area, kind, header, extra)

    # Fix dl/module cmake guard
    dl_cmake = TEST_COMPONENT / "dl" / "CMakeLists.txt"
    dl_cmake.parent.mkdir(parents=True, exist_ok=True)
    dl_content = """if(X_CMAKE_CXX_FULLSTANDARD GREATER_EQUAL 2011)

\tif(UNIX)

\t\tadd_subdirectory(test.component.unixstl.dl.dl_call)
\t\tadd_subdirectory(test.component.unixstl.dl.module)
\tendif(UNIX)
endif()
"""
    dl_cmake.write_text(dl_content)

    write_cmake_parents()

    # Manual fixes for nested shims structure
    shims_unit = TEST_UNIT / "shims"
    (shims_unit / "CMakeLists.txt").write_text(
        "# SIS:AUTO_GENERATED: Remove this line if you edit the file, otherwise it will be overwritten\n"
        "add_subdirectory(access)\n"
        "add_subdirectory(conversion)\n"
    )
    (shims_unit / "access" / "CMakeLists.txt").write_text(
        "# SIS:AUTO_GENERATED: Remove this line if you edit the file, otherwise it will be overwritten\n"
        "add_subdirectory(string)\n"
    )
    (shims_unit / "access" / "string" / "CMakeLists.txt").write_text(
        "# SIS:AUTO_GENERATED: Remove this line if you edit the file, otherwise it will be overwritten\n"
        "add_subdirectory(test.unit.unixstl.shims.access.string.timeval)\n"
        "add_subdirectory(test.unit.unixstl.shims.access.string.dirent)\n"
    )
    (shims_unit / "conversion" / "CMakeLists.txt").write_text(
        "# SIS:AUTO_GENERATED: Remove this line if you edit the file, otherwise it will be overwritten\n"
        "add_subdirectory(to_uint64)\n"
    )
    (shims_unit / "conversion" / "to_uint64" / "CMakeLists.txt").write_text(
        "# SIS:AUTO_GENERATED: Remove this line if you edit the file, otherwise it will be overwritten\n"
        "add_subdirectory(test.unit.unixstl.shims.conversion.to_uint64.stat)\n"
    )

    # filesystem handles nesting
    fs_handles = TEST_COMPONENT / "filesystem" / "handles"
    fs_handles.mkdir(parents=True, exist_ok=True)
    (fs_handles / "CMakeLists.txt").write_text(
        "# SIS:AUTO_GENERATED: Remove this line if you edit the file, otherwise it will be overwritten\n"
        "add_subdirectory(test.component.unixstl.filesystem.handles.memory_mapped_file_view_handle)\n"
    )

    # Preserve pre-existing filesystem component tests
    (TEST_COMPONENT / "filesystem" / "CMakeLists.txt").write_text(
        "# SIS:AUTO_GENERATED: Remove this line if you edit the file, otherwise it will be overwritten\n"
        "add_subdirectory(handles)\n"
        "add_subdirectory(test.component.unixstl.filesystem.current_directory)\n"
        "add_subdirectory(test.component.unixstl.filesystem.current_directory_scope)\n"
        "add_subdirectory(test.component.unixstl.filesystem.directory_functions)\n"
        "add_subdirectory(test.component.unixstl.filesystem.glob_sequence)\n"
        "add_subdirectory(test.component.unixstl.filesystem.memory_map_functions)\n"
        "add_subdirectory(test.component.unixstl.filesystem.memory_mapped_file)\n"
        "add_subdirectory(test.component.unixstl.filesystem.pipe)\n"
        "add_subdirectory(test.component.unixstl.filesystem.readdir_sequence)\n"
        "add_subdirectory(test.component.unixstl.filesystem.readonly_memory_mapped_file)\n"
    )

    # Preserve pre-existing unit filesystem tests
    (TEST_UNIT / "filesystem" / "CMakeLists.txt").write_text(
        "# SIS:AUTO_GENERATED: Remove this line if you edit the file, otherwise it will be overwritten\n"
        "add_subdirectory(test.unit.unixstl.filesystem.file_path_buffer)\n"
        "add_subdirectory(test.unit.unixstl.filesystem.filesystem_traits)\n"
        "add_subdirectory(test.unit.unixstl.filesystem.functionals)\n"
        "add_subdirectory(test.unit.unixstl.filesystem.path)\n"
        "add_subdirectory(test.unit.unixstl.filesystem.path_buffer)\n"
        "add_subdirectory(test.unit.unixstl.filesystem.path_classify_functions)\n"
        "add_subdirectory(test.unit.unixstl.filesystem.path_functions)\n"
        "add_subdirectory(test.unit.unixstl.filesystem.path_parse_functions)\n"
        "add_subdirectory(test.unit.unixstl.filesystem.squeeze_functions)\n"
    )

    # Preserve pre-existing system component tests
    (TEST_COMPONENT / "system" / "CMakeLists.txt").write_text(
        "# SIS:AUTO_GENERATED: Remove this line if you edit the file, otherwise it will be overwritten\n"
        "add_subdirectory(test.component.unixstl.system.console_functions)\n"
        "add_subdirectory(test.component.unixstl.system.directory_functions)\n"
        "add_subdirectory(test.component.unixstl.system.environment_variable)\n"
        "add_subdirectory(test.component.unixstl.system.home_directory)\n"
        "add_subdirectory(test.component.unixstl.system.pid_sequence)\n"
    )

    # Update unit/component root cmake
    unit_root = TEST_UNIT / "CMakeLists.txt"
    unit_subs = sorted(
        p.name
        for p in TEST_UNIT.iterdir()
        if p.is_dir() and p.name not in (".", "..")
    )
    (unit_root).write_text(
        "# SIS:AUTO_GENERATED: Remove this line if you edit the file, otherwise it will be overwritten\n"
        + "\n".join(f"add_subdirectory({s})" for s in unit_subs)
        + "\n"
    )

    comp_root = TEST_COMPONENT / "CMakeLists.txt"
    comp_subs = sorted(
        p.name
        for p in TEST_COMPONENT.iterdir()
        if p.is_dir() and p.name not in (".", "..")
    )
    (comp_root).write_text(
        "# SIS:AUTO_GENERATED: Remove this line if you edit the file, otherwise it will be overwritten\n"
        + "\n".join(f"add_subdirectory({s})" for s in comp_subs)
        + "\n"
    )

    print(f"Generated {len([t for t in TESTS if test_name(t[0], t[1]) not in EXISTING])} test programs")


if __name__ == "__main__":
    main()
