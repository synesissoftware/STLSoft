/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/mfcstl/string/string_traits/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft::string_traits<CString>`.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <mfcstl/string/string_traits.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/meta/is_same_type.hpp>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_TYPE_TRAITS();
    static void TEST_empty_string();
    static void TEST_CONSTRUCT_AND_assign_inplace();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER(__FILE__, verbosity))
    {
        XTESTS_RUN_CASE(TEST_TYPE_TRAITS);
        XTESTS_RUN_CASE(TEST_empty_string);
        XTESTS_RUN_CASE(TEST_CONSTRUCT_AND_assign_inplace);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_TYPE_TRAITS()
{
    typedef stlsoft::string_traits<CString> traits_t;

    STLSOFT_STATIC_ASSERT((stlsoft::is_same_type<CString, traits_t::value_type>::value));
    STLSOFT_STATIC_ASSERT((stlsoft::is_same_type<TCHAR, traits_t::char_type>::value));
    STLSOFT_STATIC_ASSERT(traits_t::is_pointer == false);

    TEST_PASSED();
}

static void TEST_empty_string()
{
    typedef stlsoft::string_traits<CString> traits_t;

    CString const s = traits_t::empty_string();

    TEST_BOOLEAN_TRUE(s.IsEmpty());
}

static void TEST_CONSTRUCT_AND_assign_inplace()
{
    typedef stlsoft::string_traits<CString> traits_t;

    CString const src(_T("mfcstl"));
    CString       dest;

    CString const sub = traits_t::construct(src, 2, 3);

    /* construct() is 0-based: "mfcstl" at position 2, length 3, is "cst". */
    TEST_MS_EQ(_T("cst"), sub);

    LPCTSTR const begin = static_cast<LPCTSTR>(src);

    traits_t::assign_inplace(dest, begin, begin + src.GetLength());

    TEST_MS_EQ(_T("mfcstl"), dest);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
