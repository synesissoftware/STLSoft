/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.mfcstl.collections.CList_traits/entry.cpp
 *
 * Purpose: Unit-tests for `mfcstl::CList_traits`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <mfcstl/collections/CList_traits.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/meta/is_same_type.hpp>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_CPtrList_traits(void);
    static void TEST_CStringList_traits(void);
    static void TEST_CList_specific_traits(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.mfcstl.collections.CList_traits", verbosity))
    {
        XTESTS_RUN_CASE(TEST_CPtrList_traits);
        XTESTS_RUN_CASE(TEST_CStringList_traits);
        XTESTS_RUN_CASE(TEST_CList_specific_traits);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_CPtrList_traits()
{
    typedef mfcstl::CList_traits<CPtrList> traits_t;

    STLSOFT_STATIC_ASSERT((stlsoft::is_same_type<void*, traits_t::value_type>::value));
    STLSOFT_STATIC_ASSERT((stlsoft::is_same_type<void*, traits_t::arg_type>::value));
    STLSOFT_STATIC_ASSERT((stlsoft::is_same_type<CPtrList, traits_t::list_type>::value));

    TEST_PASSED();
}

static void TEST_CStringList_traits()
{
    typedef mfcstl::CList_traits<CStringList> traits_t;

    STLSOFT_STATIC_ASSERT((stlsoft::is_same_type<CString, traits_t::value_type>::value));
    STLSOFT_STATIC_ASSERT((stlsoft::is_same_type<LPCTSTR, traits_t::arg_type>::value));
    STLSOFT_STATIC_ASSERT((stlsoft::is_same_type<CStringList, traits_t::list_type>::value));

    TEST_PASSED();
}

static void TEST_CList_specific_traits()
{
    typedef mfcstl::CList_specific_traits<CString, LPCTSTR, CStringList> traits_t;

    STLSOFT_STATIC_ASSERT((stlsoft::is_same_type<CString, traits_t::value_type>::value));
    STLSOFT_STATIC_ASSERT((stlsoft::is_same_type<LPCTSTR, traits_t::arg_type>::value));
    STLSOFT_STATIC_ASSERT((stlsoft::is_same_type<CStringList, traits_t::list_type>::value));

    TEST_PASSED();
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
