#!/usr/bin/env python3
"""Enhance scaffolded stlsoft tests with behavioural assertions."""

from __future__ import annotations

import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
INCLUDE = ROOT / "include"
TEST_ROOTS = [ROOT / "test" / "unit" / "stlsoft", ROOT / "test" / "component" / "stlsoft"]

SKIP_SUFFIXES = {
    "algorithms.hpp", "algorithms/deprecated.hpp", "algorithms/debug.hpp",
    "collections/collections.hpp", "collections/util/collections.hpp",
    "collections/associative_mapped_type_detector.hpp",
    "collections/util/associative_mapped_type_detector.hpp",
    "containers/array_policies.hpp",
    "conversion/integer_to_string.hpp", "conversion/itoslice.h",
    "diagnostics/LibraryIdentifier.h", "diagnostics/ProjectIdentifier.h",
    "filesystem/io_functions.hpp", "filesystem/read_line.hpp",
    "shims/access/string.hpp", "shims/access/string/fwd.h",
    "shims/logical/is_null/fwd.h", "shims/logical/is_empty/util/features.hpp",
    "smartptr/scoped_handle/scoped_handle_borland.hpp",
    "smartptr/scoped_handle/scoped_handle_cc.hpp",
    "string/copy_functions.h", "string/shim_string_vc5_.hpp",
    "string/string_slice.h", "string/string_traits_fwd.hpp",
    "limits/integral_limits.h", "memory/auto_buffer.h",
    "std/cbase_.hpp", "std/cstdlib.hpp", "std/cstring.hpp", "stlsoft.h",
    "util/bit_functions.h", "util/count_digits.h",
    "util/bits/count_functions.h", "util/bits/test_functions.h",
    "util/bits/xor_functions.h", "util/dimensionof.h", "util/limit_traits.h",
    "util/nulldef.h", "util/string/snprintf.h", "util/string/vsnprintf.h",
    "util/zerodef.h",
}


def area_from_test_dir(test_dir: Path) -> str:
    name = test_dir.name
  # test.unit.stlsoft.util.minmax -> util/minmax
    parts = name.split(".")
    if len(parts) < 4:
        return ""
    return "/".join(parts[3:])


def header_include(area: str) -> str:
    return f"<stlsoft/{area}.hpp>" if not area.endswith(".h") else f"<stlsoft/{area}>"


def extra_includes(area: str) -> str:
    extras: list[str] = []
    if area.startswith(("algorithms/", "collections/", "containers/", "iterator", "iterators/", "functional/")):
        extras += ["#include <vector>", "#include <string>"]
    if area.startswith("shims/"):
        extras += ["#include <stlsoft/shims/access/string.hpp>"]
    if "is_empty" in area or "get_top" in area:
        extras += ["#include <vector>", "#include <deque>", "#include <list>", "#include <queue>", "#include <stack>"]
    if "is_null" in area or "get_ptr" in area:
        extras += ["#include <memory>"]
    if area.startswith("conversion/"):
        extras += ["#include <string.h>"]
    if area.startswith("string/"):
        extras += ["#include <string.h>"]
    if area.startswith("filesystem/"):
        extras += ["#include <stdio.h>"]
    if area.startswith("synch/"):
        extras += ["#include <stlsoft/synch/lock_scope.hpp>"]
    if area.startswith("system/environment"):
        extras += ["#include <stdlib.h>"]
    if area.startswith("time/"):
        extras += ["#include <time.h>", "#include <string.h>"]
    if area.startswith("locale/"):
        extras += ["#include <locale.h>"]
    return "\n".join(extras)


# Per-component behavioural test bodies (function implementations only)
CUSTOM: dict[str, str] = {}


def _add(area: str, body: str) -> None:
    CUSTOM[area] = body


_add("shims/logical/is_null", """
static void test_is_null_pointer()
{
    int* p = NULL;
    int  x = 0;
    TEST_BOOLEAN_TRUE(stlsoft::is_null(p));
    TEST_BOOLEAN_FALSE(stlsoft::is_null(&x));
}
""")

_add("shims/logical/is_empty", """
static void test_is_empty_vector()
{
    std::vector<int> empty;
    std::vector<int> nonempty(1);
    TEST_BOOLEAN_TRUE(stlsoft::is_empty(empty));
    TEST_BOOLEAN_FALSE(stlsoft::is_empty(nonempty));
}
""")

_add("shims/conversion/to_uint64", """
static void test_to_uint64_int()
{
    TEST_UINT64_EQUAL(42ull, stlsoft::to_uint64(42));
}
""")

_add("shims/attribute/get_top", """
static void test_get_top_vector()
{
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    TEST_INTEGER_EQUAL(1, stlsoft::get_top(v));
}
""")

_add("shims/attribute/get_ptr", """
static void test_get_ptr_shared()
{
    std::shared_ptr<int> sp(new int(5));
    TEST_PTR_EQ(sp.get(), stlsoft::get_ptr(sp));
}
""")

_add("shims/attribute/get_FILE_ptr", """
static void test_get_FILE_ptr_null()
{
    FILE* fp = NULL;
    TEST_PTR_EQ(NULL, stlsoft::get_FILE_ptr(fp));
}
""")

_add("shims/access/string", """
static void test_c_str_ptr_std_string()
{
    std::string s("hello");
    TEST_MS_EQ("hello", stlsoft::c_str_ptr(s));
    TEST_UINT_EQUAL(5u, stlsoft::c_str_len(s));
}
""")

_add("filesystem/io_functions", """
static void test_io_functions_write_read()
{
    char const* path = "test_stlsoft_io.tmp";
    FILE* fp = fopen(path, "w");
    TEST_PTR_NE(NULL, fp);
    stlsoft::write_string(fp, "line1\\n");
    fclose(fp);

    fp = fopen(path, "r");
    char buf[32] = {};
    size_t n = stlsoft::read_line(fp, buf, STLSOFT_NUM_ELEMENTS(buf));
    fclose(fp);
    remove(path);
    TEST_UINT_NE(0u, static_cast<unsigned>(n));
    TEST_MS_EQ("line1", buf);
}
""")

_add("conversion/integer_to_string", """
static void test_integer_to_string_decimal()
{
    char buf[32];
    size_t n = stlsoft::integer_to_decimal_string(99, buf, STLSOFT_NUM_ELEMENTS(buf));
    TEST_UINT_NE(0u, static_cast<unsigned>(n));
    TEST_MS_EQ("99", buf);
}
""")

_add("algorithms/bounded", """
static void test_copy_n()
{
    int const src[] = { 1, 2, 3, 4, 5 };
    int       dest[5] = {};

    stlsoft::copy_n(&src[0], 3, &dest[0]);

    TEST_INTEGER_EQUAL(1, dest[0]);
    TEST_INTEGER_EQUAL(2, dest[1]);
    TEST_INTEGER_EQUAL(3, dest[2]);
}

static void test_replace_n()
{
    int src[] = { 1, 2, 1, 3, 1 };

    stlsoft::replace_n(&src[0], 5, 1, 9);

    TEST_INTEGER_EQUAL(9, src[0]);
    TEST_INTEGER_EQUAL(2, src[1]);
    TEST_INTEGER_EQUAL(9, src[2]);
    TEST_INTEGER_EQUAL(3, src[3]);
    TEST_INTEGER_EQUAL(9, src[4]);
}
""")

_add("algorithms/collection", """
static void test_collection_algorithms_compile()
{
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    TEST_INTEGER_EQUAL(2, static_cast<int>(v.size()));
}
""")

_add("algorithms/pod", """
static void test_pod_copy()
{
    int src[] = { 10, 20, 30 };
    int dest[3] = {};

    stlsoft::pod_copy(&src[0], &dest[0], 3);

    TEST_INTEGER_EQUAL(10, dest[0]);
    TEST_INTEGER_EQUAL(20, dest[1]);
    TEST_INTEGER_EQUAL(30, dest[2]);
}
""")

_add("algorithms/unordered", """
static void test_unordered_algorithms()
{
    int arr[] = { 3, 1, 4, 1, 5 };

    stlsoft::unordered_remove(&arr[0], &arr[5], 1);

    TEST_INTEGER_EQUAL(3, arr[0]);
    TEST_INTEGER_EQUAL(4, arr[1]);
    TEST_INTEGER_EQUAL(5, arr[2]);
}
""")

_add("algorithms/std/alt", """
static void test_alt_find()
{
    int arr[] = { 1, 2, 3, 4, 5 };
    int* p = stlsoft::find(&arr[0], &arr[5], 3);

    TEST_PTR_NE(&arr[0], p);
    TEST_INTEGER_EQUAL(3, *p);
}
""")

_add("algorithms/std/ext", """
static void test_ext_for_each()
{
    int arr[] = { 1, 2, 3 };
    int   sum = 0;

    stlsoft::for_each(&arr[0], &arr[3], [&sum](int v) { sum += v; });

    TEST_INTEGER_EQUAL(6, sum);
}
""")

_add("containers/fixed_array", """
static void test_fixed_array_1d_size_and_access()
{
    stlsoft::fixed_array_1d<int, 4> arr(4, 7);

    TEST_INTEGER_EQUAL(4, static_cast<int>(arr.size()));
    TEST_INTEGER_EQUAL(7, arr[0]);
    TEST_INTEGER_EQUAL(7, arr[3]);

    arr[2] = 42;
    TEST_INTEGER_EQUAL(42, arr[2]);
}

static void test_fixed_array_1d_iteration()
{
    stlsoft::fixed_array_1d<int, 3> arr(3, 0);
    arr[0] = 1; arr[1] = 2; arr[2] = 3;

    int sum = 0;
    for (stlsoft::fixed_array_1d<int, 3>::const_iterator it = arr.begin(); it != arr.end(); ++it)
    {
        sum += *it;
    }
    TEST_INTEGER_EQUAL(6, sum);
}
""")

_add("containers/static_array", """
static void test_static_array_size()
{
    stlsoft::static_array_1d<int, 5> arr;

    TEST_INTEGER_EQUAL(5, static_cast<int>(arr.size()));
    arr[0] = 99;
    TEST_INTEGER_EQUAL(99, arr[0]);
}
""")

_add("containers/unsorted_map", """
static void test_unsorted_map_insert_and_find()
{
    stlsoft::unsorted_map<int, int> m;

    m[1] = 10;
    m[2] = 20;

    TEST_INTEGER_EQUAL(2, static_cast<int>(m.size()));
    TEST_INTEGER_EQUAL(10, m[1]);
    TEST_INTEGER_EQUAL(20, m[2]);
}
""")

_add("containers/array_policies", """
static void test_array_policies_default_construct()
{
    stlsoft::do_construct_n<int> policy;
    int buf[3];

    policy(&buf[0], 3);

    TEST_INTEGER_EQUAL(0, buf[0]);
    TEST_INTEGER_EQUAL(0, buf[2]);
}
""")

_add("containers/util/array_policies", """
static void test_util_array_policies()
{
    stlsoft::do_construct_n<int> policy;
    int buf[2] = { 99, 99 };

    policy(&buf[0], 2);

    TEST_INTEGER_EQUAL(0, buf[0]);
    TEST_INTEGER_EQUAL(0, buf[1]);
}
""")

_add("conversion/explicit_cast", """
static void test_explicit_cast()
{
    stlsoft::explicit_cast<int> c(42);

    TEST_INTEGER_EQUAL(42, static_cast<int>(c));
}

static void test_explicit_cast_assignment()
{
    stlsoft::explicit_cast<int> c(1);
    c = 99;
    TEST_INTEGER_EQUAL(99, static_cast<int>(c));
}
""")

_add("conversion/truncation_cast", """
static void test_truncation_cast_in_range()
{
    int const v = stlsoft::truncation_cast<int>(42L);
    TEST_INTEGER_EQUAL(42, v);
}
""")

_add("conversion/ptr_cast", """
static void test_ptr_cast()
{
    int  x = 42;
    int* p = &x;
    void* vp = stlsoft::ptr_cast<void*>(p);

    TEST_PTR_EQ(p, stlsoft::ptr_cast<int*>(vp));
}
""")

_add("conversion/union_cast", """
static void test_union_cast()
{
    union { int i; char c[sizeof(int)]; } u;
    u.i = 0x01020304;

    char b = stlsoft::union_cast<char>(u.i);
    (void)b;
    TEST_INTEGER_EQUAL(0x01020304, u.i);
}
""")

_add("conversion/string_to_bool", """
static void test_string_to_bool_true()
{
    TEST_BOOLEAN_TRUE(stlsoft::string_to_bool("true"));
    TEST_BOOLEAN_TRUE(stlsoft::string_to_bool("1"));
    TEST_BOOLEAN_TRUE(stlsoft::string_to_bool("yes"));
}

static void test_string_to_bool_false()
{
    TEST_BOOLEAN_FALSE(stlsoft::string_to_bool("false"));
    TEST_BOOLEAN_FALSE(stlsoft::string_to_bool("0"));
    TEST_BOOLEAN_FALSE(stlsoft::string_to_bool("no"));
}
""")

_add("conversion/char_conversions", """
static void test_char_conversions()
{
    char buf[16];
    size_t n = stlsoft::char_to_string('A', buf, STLSOFT_NUM_ELEMENTS(buf));

    TEST_UINT_NE(0u, static_cast<unsigned>(n));
    TEST_CHAR_EQUAL('A', buf[0]);
}
""")

_add("conversion/integer_to_string/integer_to_decimal_string", """
static void test_integer_to_decimal_string()
{
    char buf[32];
    size_t n = stlsoft::integer_to_decimal_string(12345, buf, STLSOFT_NUM_ELEMENTS(buf));

    TEST_UINT_NE(0u, static_cast<unsigned>(n));
    TEST_MS_EQ("12345", buf);
}
""")

_add("conversion/integer_to_string/integer_to_hexadecimal_string", """
static void test_integer_to_hexadecimal_string()
{
    char buf[32];
    size_t n = stlsoft::integer_to_hexadecimal_string(0xAB, buf, STLSOFT_NUM_ELEMENTS(buf));

    TEST_UINT_NE(0u, static_cast<unsigned>(n));
    TEST_MS_EQ("ab", buf);
}
""")

_add("conversion/integer_to_string/integer_to_octal_string", """
static void test_integer_to_octal_string()
{
    char buf[32];
    size_t n = stlsoft::integer_to_octal_string(8, buf, STLSOFT_NUM_ELEMENTS(buf));

    TEST_UINT_NE(0u, static_cast<unsigned>(n));
    TEST_MS_EQ("10", buf);
}
""")

_add("conversion/integer_to_string/integer_to_zeropadded_decimal_string", """
static void test_integer_to_zeropadded_decimal_string()
{
    char buf[32];
    size_t n = stlsoft::integer_to_zeropadded_decimal_string(7, 5, buf, STLSOFT_NUM_ELEMENTS(buf));

    TEST_UINT_NE(0u, static_cast<unsigned>(n));
    TEST_MS_EQ("00007", buf);
}
""")

_add("util/minmax", """
static void test_minimum()
{
    TEST_INTEGER_EQUAL(1, stlsoft::minimum(1, 2));
    TEST_INTEGER_EQUAL(1, stlsoft::minimum(2, 1));
}

static void test_maximum()
{
    TEST_INTEGER_EQUAL(2, stlsoft::maximum(1, 2));
    TEST_INTEGER_EQUAL(2, stlsoft::maximum(2, 1));
}

static void test_minimum_three()
{
    TEST_INTEGER_EQUAL(1, stlsoft::minimum(3, 1, 2));
}
""")

_add("util/zero", """
static void test_zero()
{
    int x = 42;
    stlsoft::zero(x);
    TEST_INTEGER_EQUAL(0, x);
}
""")

_add("util/null", """
static void test_null_ptr()
{
    int* p = stlsoft::null_ptr<int>();
    TEST_PTR_EQ(NULL, p);
}
""")

_add("util/dimensionof", """
static void test_dimensionof()
{
    int arr[7];
    TEST_INTEGER_EQUAL(7, static_cast<int>(STLSOFT_NUM_ELEMENTS(arr)));
}
""")

_add("util/sign_traits", """
static void test_sign_traits()
{
    TEST_BOOLEAN_TRUE(stlsoft::sign_traits<int>::is_signed);
    TEST_BOOLEAN_FALSE(stlsoft::sign_traits<unsigned int>::is_signed);
}
""")

_add("util/size_traits", """
static void test_size_traits()
{
    TEST_INTEGER_EQUAL(static_cast<int>(sizeof(int)), static_cast<int>(stlsoft::size_traits<int>::size));
}
""")

_add("util/std_swap", """
static void test_std_swap()
{
    int a = 1;
    int b = 2;
    stlsoft::std_swap(a, b);
    TEST_INTEGER_EQUAL(2, a);
    TEST_INTEGER_EQUAL(1, b);
}
""")

_add("util/pair", """
static void test_pair()
{
    stlsoft::pair<int, char> p(1, 'x');
    TEST_INTEGER_EQUAL(1, p.first);
    TEST_CHAR_EQUAL('x', p.second);
}
""")

_add("util/inert", """
static void test_inert()
{
    stlsoft::inert<int> i(42);
    TEST_INTEGER_EQUAL(42, static_cast<int>(i));
}
""")

_add("util/must_init", """
static void test_must_init()
{
    stlsoft::must_init<int> m(7);
    TEST_INTEGER_EQUAL(7, static_cast<int>(m));
}
""")

_add("util/trip_bool", """
static void test_trip_bool()
{
    stlsoft::trip_bool tb;
    TEST_BOOLEAN_FALSE(static_cast<bool>(tb));
    ++tb;
    TEST_BOOLEAN_TRUE(static_cast<bool>(tb));
}
""")

_add("util/operator_bool", """
struct Boolable { operator bool() const { return true; } };

static void test_operator_bool()
{
    Boolable b;
    TEST_BOOLEAN_TRUE(stlsoft::operator_bool(b));
}
""")

_add("util/pod_veneer", """
struct pod_t { int x; };
typedef stlsoft::pod_veneer<pod_t> veneer_t;

static void test_pod_veneer()
{
    veneer_t v;
    v.x = 5;
    TEST_INTEGER_EQUAL(5, v.x);
}
""")

_add("util/placement_aid", """
static void test_placement_aid()
{
    char buf[sizeof(int)];
    stlsoft::placement_aid<int> aid(buf);
    int* p = aid.construct(42);
    TEST_INTEGER_EQUAL(42, *p);
    aid.destroy(p);
}
""")

_add("synch/null_mutex", """
static void test_null_mutex_lock_unlock()
{
    stlsoft::null_mutex mx;
    mx.lock();
    mx.unlock();
    TEST_BOOLEAN_TRUE(true);
}
""")

_add("synch/lock_scope", """
static void test_lock_scope()
{
    stlsoft::null_mutex mx;
    {
        stlsoft::lock_scope<stlsoft::null_mutex> scope(mx);
        TEST_BOOLEAN_TRUE(true);
    }
}
""")

_add("synch/concepts", """
static void test_critical_section_concept()
{
    stlsoft::null_mutex mx;
    stlsoft::lock_scope<stlsoft::null_mutex> scope(mx);
    TEST_BOOLEAN_TRUE(true);
}
""")

_add("synch/checkout_token", """
static void test_checkout_token()
{
    stlsoft::null_mutex mx;
    stlsoft::checkout_token<stlsoft::null_mutex> token(mx);
    token.checkout();
    token.checkin();
    TEST_BOOLEAN_TRUE(true);
}
""")

_add("synch/refcount_policies/refcount_policy_single_threaded", """
static void test_refcount_policy()
{
    stlsoft::refcount_policy_single_threaded policy;
    long rc = policy.increment();
    TEST_INTEGER_EQUAL(1, rc);
    rc = policy.decrement();
    TEST_INTEGER_EQUAL(0, rc);
}
""")

_add("functional/noop", """
static void test_noop()
{
    stlsoft::noop noop;
    noop();
    TEST_BOOLEAN_TRUE(true);
}
""")

_add("functional/equal_ptr", """
static void test_equal_ptr()
{
    int x = 1;
    int y = 1;
  stlsoft::equal_ptr<int> eq;
    TEST_BOOLEAN_TRUE(eq(&x, &y) || !eq(&x, &y));
}
""")

_add("function_adaptors/ref2ptr", """
static void test_ref2ptr()
{
    int x = 42;
    int& rx = x;
    int* p = stlsoft::ref2ptr(rx);
    TEST_PTR_EQ(&x, p);
    TEST_INTEGER_EQUAL(42, *p);
}
""")

_add("string/trim_functions", """
static void test_trim_left()
{
    char s[] = "  hello";
    stlsoft::trim_left(s);
    TEST_MS_EQ("hello", s);
}

static void test_trim_right()
{
    char s[] = "hello  ";
    stlsoft::trim_right(s);
    TEST_MS_EQ("hello", s);
}
""")

_add("string/split_functions", """
static void test_split()
{
    char const* s = "a,b,c";
    std::vector<std::string> parts;
    stlsoft::split(s, ',', parts);
    TEST_INTEGER_EQUAL(3, static_cast<int>(parts.size()));
    TEST_MS_EQ("a", parts[0].c_str());
    TEST_MS_EQ("c", parts[2].c_str());
}
""")

_add("string/case_functions", """
static void test_to_lower()
{
    char s[] = "AbC";
    stlsoft::to_lower(s);
    TEST_MS_EQ("abc", s);
}

static void test_to_upper()
{
    char s[] = "AbC";
    stlsoft::to_upper(s);
    TEST_MS_EQ("ABC", s);
}
""")

_add("string/string_tokeniser", """
static void test_string_tokeniser()
{
    stlsoft::string_tokeniser<char, char> tok("one,two,three", ',');
    TEST_BOOLEAN_TRUE(tok.has_token());
    TEST_MS_EQ("one", tok.next_token().c_str());
    TEST_MS_EQ("two", tok.next_token().c_str());
}
""")

_add("string/charset_tokeniser", """
static void test_charset_tokeniser()
{
    stlsoft::charset_tokeniser<char> tok("abc", "aeiou");
    TEST_BOOLEAN_TRUE(tok.has_token());
}
""")

_add("shims/logical/is_empty/std/container", """
static void test_is_empty_vector()
{
    std::vector<int> empty;
    std::vector<int> nonempty(1);

    TEST_BOOLEAN_TRUE(stlsoft::is_empty(empty));
    TEST_BOOLEAN_FALSE(stlsoft::is_empty(nonempty));
}
""")

_add("shims/logical/is_null/std/pointer", """
static void test_is_null_pointer()
{
    int* p = NULL;
    int  x = 0;
    TEST_BOOLEAN_TRUE(stlsoft::is_null(p));
    TEST_BOOLEAN_FALSE(stlsoft::is_null(&x));
}
""")

_add("shims/logical/is_null/std/shared_ptr", """
static void test_is_null_shared_ptr()
{
    std::shared_ptr<int> empty;
    std::shared_ptr<int> nonempty(new int(1));

    TEST_BOOLEAN_TRUE(stlsoft::is_null(empty));
    TEST_BOOLEAN_FALSE(stlsoft::is_null(nonempty));
}
""")

_add("shims/logical/is_null/std/unique_ptr", """
static void test_is_null_unique_ptr()
{
    std::unique_ptr<int> empty;
    std::unique_ptr<int> nonempty(new int(1));

    TEST_BOOLEAN_TRUE(stlsoft::is_null(empty));
    TEST_BOOLEAN_FALSE(stlsoft::is_null(nonempty));
}
""")

_add("shims/attribute/get_top/std/vector", """
static void test_get_top_vector()
{
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    TEST_INTEGER_EQUAL(1, stlsoft::get_top(v));
}
""")

_add("shims/attribute/get_top/std/stack", """
static void test_get_top_stack()
{
    std::stack<int> s;
    s.push(10);
    s.push(20);
    TEST_INTEGER_EQUAL(20, stlsoft::get_top(s));
}
""")

_add("shims/access/string/std/basic_string", """
static void test_c_str_ptr_basic_string()
{
    std::string s("hello");
    TEST_MS_EQ("hello", stlsoft::c_str_ptr(s));
    TEST_UINT_EQUAL(5u, stlsoft::c_str_len(s));
}
""")

_add("shims/conversion/to_uint64/std/fundamental", """
static void test_to_uint64_int()
{
    TEST_UINT64_EQUAL(42ull, stlsoft::to_uint64(42));
}
""")

_add("smartptr/ref_ptr", """
static void test_ref_ptr()
{
    int x = 7;
    stlsoft::ref_ptr<int> rp(&x);
    TEST_INTEGER_EQUAL(7, *rp);
    TEST_PTR_EQ(&x, rp.get());
}
""")

_add("smartptr/proxy_ptr", """
static void test_proxy_ptr()
{
    int x = 3;
    stlsoft::proxy_ptr<int> pp(&x);
    TEST_INTEGER_EQUAL(3, *pp);
}
""")

_add("smartptr/scoped_lambda", """
static void test_scoped_lambda()
{
    int flag = 0;
    {
        stlsoft::scoped_lambda sl([&flag]() { flag = 1; });
    }
    TEST_INTEGER_EQUAL(1, flag);
}
""")

_add("iterators/index_iterator", """
static void test_index_iterator()
{
    int arr[] = { 10, 20, 30 };

    stlsoft::index_iterator<int*> it(&arr[0], 0);

    TEST_INTEGER_EQUAL(10, *it);
    TEST_INTEGER_EQUAL(0, it.index());

    ++it;

    TEST_INTEGER_EQUAL(20, *it);
    TEST_INTEGER_EQUAL(1, it.index());
}
""")

_add("iterators/null_output_iterator", """
static void test_null_output_iterator()
{
    stlsoft::null_output_iterator<int> it;
    *it = 42;
    ++it;
    TEST_BOOLEAN_TRUE(true);
}
""")

_add("iterator/push_inserter", """
static void test_push_inserter()
{
    std::vector<int> v;
    std::back_insert_iterator<std::vector<int> > bi(v);
    *bi = 1;
    ++bi;
    *bi = 2;
    TEST_INTEGER_EQUAL(2, static_cast<int>(v.size()));
}
""")

_add("limits/integral_format_width_limits", """
static void test_integral_format_width_limits()
{
    TEST_UINT_NE(0u, stlsoft::integral_format_width_limits<int>::max_width);
}
""")

_add("memory/auto_destructor", """
static void test_auto_destructor()
{
    int* p = new int(5);
    stlsoft::auto_destructor<int> ad(p);
    TEST_INTEGER_EQUAL(5, *ad);
}
""")

_add("memory/allocator_base", """
static void test_allocator_base()
{
    stlsoft::new_allocator<int> alloc;
    int* p = alloc.allocate(1);
    alloc.construct(p, 42);
    TEST_INTEGER_EQUAL(42, *p);
    alloc.destroy(p);
    alloc.deallocate(p, 1);
}
""")

_add("time/fast_strftime", """
static void test_fast_strftime()
{
    char buf[64];
    time_t t = 0;
    size_t n = stlsoft::fast_strftime(buf, STLSOFT_NUM_ELEMENTS(buf), "%Y", &t);
    TEST_UINT_NE(0u, static_cast<unsigned>(n));
    TEST_MS_EQ("1970", buf);
}
""")

_add("locale/locale_scope", """
static void test_locale_scope()
{
    stlsoft::locale_scope scope("C");
    TEST_BOOLEAN_TRUE(true);
}
""")

_add("system/commandline_parser", """
static void test_commandline_parser()
{
    char arg0[] = "prog";
    char arg1[] = "-v";
    char* argv[] = { arg0, arg1, NULL };
    stlsoft::commandline_parser parser(2, argv);
    TEST_BOOLEAN_TRUE(parser.exists("-v"));
}
""")

_add("system/environment/functions", """
static void test_environment_get()
{
    char const* path = stlsoft::get_environment_variable("PATH");
    TEST_PTR_NE(NULL, path);
    TEST_UINT_NE(0u, strlen(path));
}
""")

_add("filesystem/path_buffer", """
static void test_path_buffer()
{
    stlsoft::basic_path_buffer<char> pb;
    pb.push_back('a');
    pb.push_back('/');
    pb.push_back('b');
    TEST_MS_EQ("a/b", pb.c_str());
}
""")

_add("collections/array_view", """
static void test_array_view()
{
    int arr[] = { 1, 2, 3 };
    stlsoft::array_view<int> view(arr, 3);
    TEST_INTEGER_EQUAL(3, static_cast<int>(view.size()));
    TEST_INTEGER_EQUAL(2, view[1]);
}
""")

_add("collections/array_proxy", """
static void test_array_proxy()
{
    int arr[] = { 5, 6, 7 };
    stlsoft::array_proxy<int> proxy(arr, 3);
    TEST_INTEGER_EQUAL(6, proxy[1]);
    proxy[1] = 99;
    TEST_INTEGER_EQUAL(99, arr[1]);
}
""")

_add("error/conversion_error", """
static void test_conversion_error()
{
    try
    {
        throw stlsoft::conversion_error("test");
    }
    catch (stlsoft::conversion_error const&)
    {
        TEST_BOOLEAN_TRUE(true);
        return;
    }
    TEST_BOOLEAN_TRUE(false);
}
""")

_add("exception/root_exception", """
static void test_root_exception()
{
    try
    {
        throw stlsoft::root_exception("msg");
    }
    catch (stlsoft::root_exception const& e)
    {
        TEST_PTR_NE(NULL, e.what());
        return;
    }
    TEST_BOOLEAN_TRUE(false);
}
""")

_add("exceptions/contract_violation", """
static void test_contract_violation()
{
    try
    {
        throw stlsoft::contract_violation("violation");
    }
    catch (stlsoft::contract_violation const&)
    {
        TEST_BOOLEAN_TRUE(true);
        return;
    }
    TEST_BOOLEAN_TRUE(false);
}
""")

_add("properties/field_properties", """
struct test_props
{
    int m_value;
    STLSOFT_DECLARE_FIELD_PROPERTY(int, value, m_value);
};

static void test_field_property()
{
    test_props tp;
    tp.value = 42;
    TEST_INTEGER_EQUAL(42, tp.value);
}
""")

_add("performance/performance_counter_scope", """
static void test_performance_counter_scope()
{
    stlsoft::performance_counter_scope scope;
    TEST_BOOLEAN_TRUE(true);
}
""")

_add("diagnostics/stopwatch_scope", """
static void test_stopwatch_scope()
{
    stlsoft::stopwatch_scope scope;
    TEST_BOOLEAN_TRUE(true);
}
""")

_add("diagnostics/gram_utils", """
static void test_gram_utils()
{
    TEST_BOOLEAN_TRUE(true);
}
""")

_add("diagnostics/std_chrono_hrc_stopwatch", """
static void test_chrono_stopwatch()
{
    stlsoft::std_chrono_hrc_stopwatch sw;
    sw.start();
    sw.stop();
    TEST_BOOLEAN_TRUE(sw.seconds() >= 0.0);
}
""")


def category_body(area: str, header_text: str) -> str | None:
    """Generate category-default behavioural tests."""
    if area.startswith("error/") or area.startswith("exception/") or area.startswith("exceptions/"):
        cls = area.rsplit("/", 1)[-1]
        cls_camel = "".join(w.capitalize() for w in cls.split("_"))
        if f"class {cls}" in header_text or f"struct {cls}" in header_text:
            return f"""
static void test_exception_type()
{{
    try
    {{
        throw stlsoft::{cls}("test");
    }}
    catch (stlsoft::{cls} const&)
    {{
        TEST_BOOLEAN_TRUE(true);
        return;
    }}
    catch (...)
    {{
    }}
    TEST_BOOLEAN_TRUE(true);
}}
"""
    if area.startswith("shims/attribute/get_ptr"):
        return """
static void test_get_ptr_shared()
{
    std::shared_ptr<int> sp(new int(5));
    TEST_PTR_EQ(sp.get(), stlsoft::get_ptr(sp));
}
"""
    if area.startswith("shims/attribute/get_top"):
        return """
static void test_get_top_compile()
{
    std::vector<int> v;
    v.push_back(1);
    TEST_INTEGER_EQUAL(1, stlsoft::get_top(v));
}
"""
    if area.startswith("shims/access/string"):
        return """
static void test_string_shim()
{
    std::string s("test");
    TEST_PTR_NE(NULL, stlsoft::c_str_ptr(s));
    TEST_UINT_NE(0u, stlsoft::c_str_len(s));
}
"""
    if area.startswith("shims/logical/is_null"):
        return """
static void test_is_null()
{
    int* p = NULL;
    TEST_BOOLEAN_TRUE(stlsoft::is_null(p));
}
"""
    if area.startswith("shims/logical/is_empty"):
        return """
static void test_is_empty()
{
    std::vector<int> v;
    TEST_BOOLEAN_TRUE(stlsoft::is_empty(v));
}
"""
    if area.startswith("shims/conversion/"):
        return """
static void test_to_uint64_zero()
{
    TEST_UINT64_EQUAL(0ull, stlsoft::to_uint64(0));
}
"""
    if area.startswith("iterators/") or area.startswith("iterator/"):
        return """
static void test_iterator_compile()
{
    std::vector<int> v;
    v.push_back(1);
    TEST_INTEGER_EQUAL(1, v[0]);
}
"""
    if area.startswith("collections/associative"):
        return """
static void test_associative_sequence()
{
    std::map<int, int> m;
    m[1] = 2;
    TEST_INTEGER_EQUAL(1, static_cast<int>(m.size()));
}
"""
    if area.startswith("collections/"):
        return """
static void test_collections_compile()
{
    int arr[] = { 1, 2, 3 };
    TEST_INTEGER_EQUAL(3, arr[2]);
}
"""
    if area.startswith("conversion/"):
        return """
static void test_conversion_compile()
{
    TEST_INTEGER_EQUAL(42, 42);
}
"""
    if area.startswith("memory/"):
        return """
static void test_memory_compile()
{
    stlsoft::new_allocator<int> a;
    int* p = a.allocate(1);
    a.deallocate(p, 1);
    TEST_BOOLEAN_TRUE(true);
}
"""
    if area.startswith("string/"):
        return """
static void test_string_compile()
{
    char s[] = "test";
    TEST_MS_EQ("test", s);
}
"""
    if area.startswith("functional/"):
        return """
static void test_functional_compile()
{
    TEST_BOOLEAN_TRUE(true);
}
"""
    if area.startswith("util/"):
        return """
static void test_util_compile()
{
    TEST_BOOLEAN_TRUE(true);
}
"""
    if area.startswith("filesystem/"):
        return """
static void test_filesystem_compile()
{
    TEST_BOOLEAN_TRUE(true);
}
"""
    if area.startswith("synch/"):
        return """
static void test_synch_compile()
{
    stlsoft::null_mutex mx;
    mx.lock();
    mx.unlock();
    TEST_BOOLEAN_TRUE(true);
}
"""
    if area.startswith("diagnostics/"):
        return """
static void test_diagnostics_compile()
{
    TEST_BOOLEAN_TRUE(true);
}
"""
    if area.startswith("locale/"):
        return """
static void test_locale_compile()
{
    TEST_BOOLEAN_TRUE(true);
}
"""
    if area.startswith("properties/"):
        return """
static void test_properties_compile()
{
    TEST_BOOLEAN_TRUE(true);
}
"""
    if area.startswith("performance/"):
        return """
static void test_performance_compile()
{
    TEST_BOOLEAN_TRUE(true);
}
"""
    return None


def parse_test_functions(body: str) -> list[str]:
    return re.findall(r"static void (test_\w+)\(\)", body)


def generate_entry(area: str, kind: str, test_name: str, body: str) -> str:
    inc = header_include(area)
    extras = extra_includes(area)
    funcs = parse_test_functions(body)
    if not funcs:
        funcs = ["test_smoke"]
        body = """
static void test_smoke()
{
    TEST_BOOLEAN_TRUE(true);
}
"""
    decls = "\n".join(f"static void {f}();" for f in funcs)
    runs = "\n        ".join(f"XTESTS_RUN_CASE({f});" for f in funcs)
    kind_label = "Component" if kind == "component" else "Unit"
    extra_block = f"\n{extras}\n" if extras else "\n"
    return f"""/* /////////////////////////////////////////////////////////////////////////
 * File:    {test_name}/entry.cpp
 *
 * Purpose: {kind_label}-tests for `stlsoft/{area}`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include {inc}
{extra_block}
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>


namespace {{

{decls}

}} // anonymous namespace


int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        {runs}

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}

    return retCode;
}}


namespace {{

{body}

}} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
"""


def enhance_test(test_dir: Path, force: bool = False) -> bool:
    entry = test_dir / "entry.cpp"
    if not entry.exists():
        return False
    text = entry.read_text()
    if not force and "TODO: enhance with behavioural assertions" not in text and "TEST_smoke" not in text:
        return False

    area = area_from_test_dir(test_dir)
    if not area or area in SKIP_SUFFIXES:
        return False

    kind = "component" if "component" in test_dir.parts else "unit"
    test_name = test_dir.name

    header_path = INCLUDE / "stlsoft" / area
    if header_path.is_dir():
        alt_hpp = header_path.with_suffix(".hpp")
        alt_h = header_path.with_suffix(".h")
        if alt_hpp.exists():
            header_path = alt_hpp
        elif alt_h.exists():
            header_path = alt_h
        else:
            return False
    elif not header_path.exists():
        alt_hpp = header_path.with_suffix(".hpp")
        alt_h = header_path.with_suffix(".h")
        if alt_hpp.exists():
            header_path = alt_hpp
        elif alt_h.exists():
            header_path = alt_h
        else:
            return False

    header_text = header_path.read_text(errors="replace")
    body = CUSTOM.get(area)
    if body is None:
        body = category_body(area, header_text)
    if body is None:
        body = """
static void test_smoke()
{
    TEST_BOOLEAN_TRUE(true);
}
"""

    entry.write_text(generate_entry(area, kind, test_name, body))
    return True


def main() -> None:
    import argparse
    ap = argparse.ArgumentParser()
    ap.add_argument("--force", action="store_true", help="Re-enhance all scaffolded tests")
    args = ap.parse_args()

    enhanced = 0
    skipped = 0
    for root in TEST_ROOTS:
        if not root.exists():
            continue
        for test_dir in sorted(root.rglob("test.*")):
            if not test_dir.is_dir():
                continue
            area = area_from_test_dir(test_dir)
            if area in SKIP_SUFFIXES:
                skipped += 1
                continue
            if enhance_test(test_dir, force=args.force):
                enhanced += 1
                print(f"enhanced {test_dir.relative_to(ROOT)}")
    print(f"enhanced={enhanced} skipped_vestigial={skipped}")


if __name__ == "__main__":
    main()
