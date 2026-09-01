/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.mfcstl.collections.CArray_traits/entry.cpp
 *
 * Purpose: Unit-tests for `mfcstl::CArray_traits`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <mfcstl/collections/CArray_traits.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/meta/is_same_type.hpp>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_CUIntArray_traits(void);
    static void TEST_CStringArray_traits(void);
    static void TEST_CPtrArray_traits(void);
    static void TEST_CArray_specific_traits(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.mfcstl.collections.CArray_traits", verbosity))
    {
        XTESTS_RUN_CASE(TEST_CUIntArray_traits);
        XTESTS_RUN_CASE(TEST_CStringArray_traits);
        XTESTS_RUN_CASE(TEST_CPtrArray_traits);
        XTESTS_RUN_CASE(TEST_CArray_specific_traits);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_CUIntArray_traits()
{
    typedef mfcstl::CArray_traits<CUIntArray> traits_t;

    STLSOFT_STATIC_ASSERT((stlsoft::is_same_type<UINT, traits_t::value_type>::value));
    STLSOFT_STATIC_ASSERT((stlsoft::is_same_type<UINT, traits_t::arg_type>::value));
    STLSOFT_STATIC_ASSERT((stlsoft::is_same_type<CUIntArray, traits_t::array_type>::value));

    TEST_PASSED();
}

static void TEST_CStringArray_traits()
{
    typedef mfcstl::CArray_traits<CStringArray> traits_t;

    STLSOFT_STATIC_ASSERT((stlsoft::is_same_type<CString, traits_t::value_type>::value));
    STLSOFT_STATIC_ASSERT((stlsoft::is_same_type<LPCTSTR, traits_t::arg_type>::value));
    STLSOFT_STATIC_ASSERT((stlsoft::is_same_type<CStringArray, traits_t::array_type>::value));

    TEST_PASSED();
}

static void TEST_CPtrArray_traits()
{
    typedef mfcstl::CArray_traits<CPtrArray> traits_t;

    STLSOFT_STATIC_ASSERT((stlsoft::is_same_type<void*, traits_t::value_type>::value));
    STLSOFT_STATIC_ASSERT((stlsoft::is_same_type<void*, traits_t::arg_type>::value));
    STLSOFT_STATIC_ASSERT((stlsoft::is_same_type<CPtrArray, traits_t::array_type>::value));

    TEST_PASSED();
}

static void TEST_CArray_specific_traits()
{
    typedef mfcstl::CArray_specific_traits<DWORD, DWORD, CDWordArray> traits_t;

    STLSOFT_STATIC_ASSERT((stlsoft::is_same_type<DWORD, traits_t::value_type>::value));
    STLSOFT_STATIC_ASSERT((stlsoft::is_same_type<DWORD, traits_t::arg_type>::value));
    STLSOFT_STATIC_ASSERT((stlsoft::is_same_type<CDWordArray, traits_t::array_type>::value));

    TEST_PASSED();
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
