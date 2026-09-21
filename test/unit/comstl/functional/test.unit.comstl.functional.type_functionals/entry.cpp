/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.comstl.functional.type_functionals/entry.cpp
 *
 * Purpose: Unit-tests for COM type functionals.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
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

    static void test_BSTR_close(void);
    static void test_olestring_close(void);
    static void test_task_memory_close(void);
    static void test_VARIANT_close(void);
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

    if (XTESTS_START_RUNNER("test.unit.comstl.functional.type_functionals", verbosity))
    {
        XTESTS_RUN_CASE(test_BSTR_close);
        XTESTS_RUN_CASE(test_olestring_close);
        XTESTS_RUN_CASE(test_task_memory_close);
        XTESTS_RUN_CASE(test_VARIANT_close);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_BSTR_close(void)
{
    comstl::BSTR_close  closer;
    BSTR                s = ::SysAllocString(L"z");

    TEST_PTR_NE(NULL, s);
    closer(s);
}

static void test_olestring_close(void)
{
    comstl::olestring_close  closer;
    LPOLESTR                 s = static_cast<LPOLESTR>(::CoTaskMemAlloc(4 * sizeof(OLECHAR)));

    TEST_PTR_NE(NULL, s);
    closer(s);
}

static void test_task_memory_close(void)
{
    comstl::task_memory_close  closer;
    void*                      p = ::CoTaskMemAlloc(16);

    TEST_PTR_NE(NULL, p);
    closer(p);
}

static void test_VARIANT_close(void)
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
