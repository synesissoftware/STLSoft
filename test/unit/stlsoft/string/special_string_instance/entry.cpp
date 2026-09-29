/* /////////////////////////////////////////////////////////////////////////
 * File:    special_string_instance/entry.cpp
 *
 * Purpose: Unit-tests for special_string_instance::equal.
 *
 * Created: 29th September 2026
 * Updated: 29th September 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* simple_string's c_str_data / c_str_len must be declared before
 * special_string_instance.hpp parses equal(), which calls them by
 * qualified name.
 */
#include <stlsoft/string/simple_string.hpp>

/* counted_chars reports a length that may include a NUL.
 * simple_string's (pointer, count) constructor stops at NUL.
 */
struct counted_chars
{
    char const*         p;
    stlsoft::ss_size_t  n;
};

namespace stlsoft
{
inline char const* c_str_data(counted_chars const& s)
{
    return s.p;
}
inline ss_size_t c_str_len(counted_chars const& s)
{
    return s.n;
}
} /* namespace stlsoft */

#include <stlsoft/string/special_string_instance.hpp>


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <xtests/terse-api.h>
#include <xtests/xtests.h>

#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace
{

    static void TEST_equal_CASE_SENSITIVE();
    static void TEST_equal_CASE_INSENSITIVE_ASCII();
    static void TEST_equal_LENGTH_MISMATCH();
    static void TEST_equal_EMBEDDED_NUL();
    static void TEST_equal_WCHAR();

} /* anonymous namespace */


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.string.special_string_instance", verbosity))
    {
        XTESTS_RUN_CASE(TEST_equal_CASE_SENSITIVE);
        XTESTS_RUN_CASE(TEST_equal_CASE_INSENSITIVE_ASCII);
        XTESTS_RUN_CASE(TEST_equal_LENGTH_MISMATCH);
        XTESTS_RUN_CASE(TEST_equal_EMBEDDED_NUL);
        XTESTS_RUN_CASE(TEST_equal_WCHAR);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace
{

struct content_abc {};
struct content_empty {};
struct content_embedded {};

template <
    ss_typename_param_k C
,   int                 V_caseSensitive
,   ss_typename_param_k T_content
>
struct fixed_ssi_policy
{
    typedef C                                               char_type;
    typedef stlsoft::ss_size_t                              size_type;
    typedef size_type                                     (*pfn_type)(char_type*, size_type);
    typedef ss_typename_type_k stlsoft::allocator_selector<
        char_type
    >::allocator_type                                       allocator_type;

    enum { internalBufferSize       =   32  };
    enum { allowImplicitConversion  =   0   };
    enum { caseSensitive            =   V_caseSensitive };
    enum { sharedState              =   0   };

    static size_type get_value(char_type* buffer, size_type cch)
    {
        char_type const* const  src =   content_chars(static_cast<T_content*>(0), static_cast<char_type const*>(0));
        size_type const         n   =   content_length(static_cast<T_content*>(0));

        if (cch <= n)
        {
            return n;
        }

        { size_type i; for (i = 0; i != n; ++i)
        {
            buffer[i] = src[i];
        }}

        return n;
    }

    static pfn_type get_fn()
    {
        return &get_value;
    }
};

inline char const* content_chars(content_abc const*, char const*)
{
    return "abc";
}
inline wchar_t const* content_chars(content_abc const*, wchar_t const*)
{
    return L"abc";
}
inline stlsoft::ss_size_t content_length(content_abc const*)
{
    return 3;
}

inline char const* content_chars(content_empty const*, char const*)
{
    return "";
}
inline stlsoft::ss_size_t content_length(content_empty const*)
{
    return 0;
}

inline char const* content_chars(content_embedded const*, char const*)
{
    static char const s[] = { 'a', '\0', 'x' };

    return s;
}
inline stlsoft::ss_size_t content_length(content_embedded const*)
{
    return 3;
}

typedef stlsoft::special_string_instance_0<
    fixed_ssi_policy<char, 1, content_abc>
>                                                           abc_t;
typedef stlsoft::special_string_instance_0<
    fixed_ssi_policy<char, 0, content_abc>
>                                                           abc_nocase_t;
typedef stlsoft::special_string_instance_0<
    fixed_ssi_policy<char, 1, content_empty>
>                                                           empty_t;
typedef stlsoft::special_string_instance_0<
    fixed_ssi_policy<char, 1, content_embedded>
>                                                           embedded_t;
typedef stlsoft::special_string_instance_0<
    fixed_ssi_policy<wchar_t, 1, content_abc>
>                                                           wabc_t;
typedef stlsoft::special_string_instance_0<
    fixed_ssi_policy<wchar_t, 0, content_abc>
>                                                           wabc_nocase_t;

static void TEST_equal_CASE_SENSITIVE()
{
    abc_t const     abc;
    empty_t const   empty;
    stlsoft::simple_string const same("abc");

    TEST_BOOLEAN_TRUE(abc.equal("abc"));
    TEST_BOOLEAN_TRUE(abc.equal(same));
    TEST_BOOLEAN_FALSE(abc.equal("abC"));
    TEST_BOOLEAN_FALSE(abc.equal("xyz"));
    TEST_BOOLEAN_TRUE(empty.equal(""));
}

static void TEST_equal_CASE_INSENSITIVE_ASCII()
{
    abc_nocase_t const  abc;
    wabc_nocase_t const wabc;

    TEST_BOOLEAN_TRUE(abc.equal("abc"));
    TEST_BOOLEAN_TRUE(abc.equal("ABC"));
    TEST_BOOLEAN_TRUE(abc.equal("AbC"));
    TEST_BOOLEAN_FALSE(abc.equal("ABD"));
    TEST_BOOLEAN_FALSE(abc.equal("AB"));

    TEST_BOOLEAN_TRUE(wabc.equal(L"abc"));
    TEST_BOOLEAN_TRUE(wabc.equal(L"ABC"));
    TEST_BOOLEAN_FALSE(wabc.equal(L"ABD"));
}

static void TEST_equal_LENGTH_MISMATCH()
{
    abc_t const     abc;
    empty_t const   empty;

    TEST_BOOLEAN_FALSE(abc.equal("ab"));
    TEST_BOOLEAN_FALSE(abc.equal("abcd"));
    TEST_BOOLEAN_FALSE(abc.equal(""));
    TEST_BOOLEAN_FALSE(empty.equal("a"));
}

static void TEST_equal_EMBEDDED_NUL()
{
    embedded_t const embedded;
    char const same[] = { 'a', '\0', 'x' };
    char const diff[] = { 'a', '\0', 'y' };
    char const other[] = { 'b', '\0', 'x' };
    counted_chars const s_same = { same, 3 };
    counted_chars const s_diff = { diff, 3 };
    counted_chars const s_other = { other, 3 };

    TEST_INT_EQ(3u, embedded.size());
    TEST_BOOLEAN_TRUE(embedded.equal(s_same));
    TEST_BOOLEAN_TRUE(embedded.equal(s_diff));
    TEST_BOOLEAN_FALSE(embedded.equal(s_other));
    TEST_BOOLEAN_FALSE(embedded.equal("a"));
}

static void TEST_equal_WCHAR()
{
    wabc_t const wabc;
    stlsoft::simple_wstring const same(L"abc");

    TEST_BOOLEAN_TRUE(wabc.equal(L"abc"));
    TEST_BOOLEAN_TRUE(wabc.equal(same));
    TEST_BOOLEAN_FALSE(wabc.equal(L"abC"));
    TEST_BOOLEAN_FALSE(wabc.equal(L"ab"));
    TEST_BOOLEAN_FALSE(wabc.equal(L"abcd"));
}

} /* anonymous namespace */


/* ///////////////////////////// end of file //////////////////////////// */

