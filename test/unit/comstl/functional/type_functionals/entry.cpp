/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/comstl/functional/type_functionals/entry.cpp
 *
 * Purpose: Unit-tests for COM type functionals.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <comstl/functional/type_functionals.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST__BSTR__CLOSE();
    static void TEST_OLESTRING_CLOSE();
    static void TEST_TASK_MEMORY_CLOSE();
    static void TEST__VARIANT__CLOSE();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    OleInitialize(NULL);

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER(__FILE__, verbosity))
    {
        XTESTS_RUN_CASE(TEST__BSTR__CLOSE);
        XTESTS_RUN_CASE(TEST_OLESTRING_CLOSE);
        XTESTS_RUN_CASE(TEST_TASK_MEMORY_CLOSE);
        XTESTS_RUN_CASE(TEST__VARIANT__CLOSE);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST__BSTR__CLOSE()
{
    comstl::BSTR_close  closer;
    BSTR                s = ::SysAllocString(L"z");

    TEST_PTR_NE(NULL, s);
    closer(s);
}

static void TEST_OLESTRING_CLOSE()
{
    comstl::olestring_close  closer;
    LPOLESTR                 s = static_cast<LPOLESTR>(::CoTaskMemAlloc(4 * sizeof(OLECHAR)));

    TEST_PTR_NE(NULL, s);
    closer(s);
}

static void TEST_TASK_MEMORY_CLOSE()
{
    comstl::task_memory_close  closer;
    void*                      p = ::CoTaskMemAlloc(16);

    TEST_PTR_NE(NULL, p);
    closer(p);
}

static void TEST__VARIANT__CLOSE()
{
    comstl::VARIANT_close  closer;
    VARIANT                v;

    ::VariantInit(&v);
    v.vt = VT_I4;
    v.lVal = 1;

    closer(v);
    TEST_INT_EQ((int)VT_EMPTY, (int)v.vt);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
