/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.versions/entry.cpp
 *
 * Purpose: Unit-tests for versions
 *
 * Created: 23rd August 2025
<<<<<<< HEAD
 * Updated: 9th August 2026
=======
 * Updated: 7th August 2026
>>>>>>> dev
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/stlsoft.h>
#include <platformstl/platformstl.h>
#if 0
#elif defined(PLATFORMSTL_OS_IS_UNIX)

# include <unixstl/unixstl.h>
#elif defined(PLATFORMSTL_OS_IS_WINDOWS)

# include <comstl/comstl.h>
# include <winstl/winstl.h>
#endif
#ifdef STLSOFT_HAS_ACE
# include <acestl/acestl.hpp>
#endif
#ifdef STLSOFT_HAS_ATL
# include <atlstl/atlstl.hpp>
#endif
#ifdef STLSOFT_HAS_MFC
# include <mfcstl/mfcstl.hpp>
#endif

/* /////////////////////////////////////
 * general includes
 */


/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* Standard C++ header files */

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST__STLSOFT_VER();
#ifdef STLSOFT_HAS_ACE
    static void TEST__ACESTL_VER();
#endif
#ifdef STLSOFT_HAS_ATL
    static void TEST__ATLSTL_VER();
#endif
    static void TEST__PLATFORMSTL_VER();
#if 0
#elif defined(PLATFORMSTL_OS_IS_UNIX)

    static void TEST__UNIXSTL_VER();
#elif defined(PLATFORMSTL_OS_IS_WINDOWS)

    static void TEST__COMSTL_VER();
    static void TEST__WINSTL_VER();
#endif
#ifdef STLSOFT_HAS_MFC
    static void TEST__MFCSTL_VER();
#endif
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main
 */

int main(int argc, char **argv)
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.versions", verbosity))
    {
        XTESTS_RUN_CASE(TEST__STLSOFT_VER);
#ifdef STLSOFT_HAS_ACE
        XTESTS_RUN_CASE(TEST__ACESTL_VER);
#endif
#ifdef STLSOFT_HAS_ATL
        XTESTS_RUN_CASE(TEST__ATLSTL_VER);
#endif
        XTESTS_RUN_CASE(TEST__PLATFORMSTL_VER);
#if 0
#elif defined(PLATFORMSTL_OS_IS_UNIX)

        XTESTS_RUN_CASE(TEST__UNIXSTL_VER);
#elif defined(PLATFORMSTL_OS_IS_WINDOWS)

        XTESTS_RUN_CASE(TEST__COMSTL_VER);
        XTESTS_RUN_CASE(TEST__WINSTL_VER);
#endif
#ifdef STLSOFT_HAS_MFC
        XTESTS_RUN_CASE(TEST__MFCSTL_VER);
#endif

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST__STLSOFT_VER()
{
	TEST_INT_EQ(_STLSOFT_VER_1_11_1_RC6, _STLSOFT_VER);
}
#ifdef STLSOFT_HAS_ACE

static void TEST__ACESTL_VER()
{
    TEST_INT_EQ(_ACESTL_VER_1_2_1, _ACESTL_VER);
}
#endif
#ifdef STLSOFT_HAS_ATL

static void TEST__ATLSTL_VER()
{
    TEST_INT_EQ(_ATLSTL_VER_1_7_1, _ATLSTL_VER);
}
#endif

static void TEST__PLATFORMSTL_VER()
{
	TEST_INT_EQ(_PLATFORMSTL_VER_1_10_0_B01, _PLATFORMSTL_VER);
}

#if 0
#elif defined(PLATFORMSTL_OS_IS_UNIX)

static void TEST__UNIXSTL_VER()
{
	TEST_INT_EQ(_UNIXSTL_VER_1_8_6_B06, _UNIXSTL_VER);
}
#elif defined(PLATFORMSTL_OS_IS_WINDOWS)

static void TEST__COMSTL_VER()
{
	TEST_INT_EQ(_COMSTL_VER_1_10_3, _COMSTL_VER);
}

static void TEST__WINSTL_VER()
{
	TEST_INT_EQ(_WINSTL_VER_1_13_0_B02, _WINSTL_VER);
}
#endif
#ifdef STLSOFT_HAS_MFC

static void TEST__MFCSTL_VER()
{
    TEST_INT_EQ(_MFCSTL_VER_1_6_1, _MFCSTL_VER);
}
#endif

} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

