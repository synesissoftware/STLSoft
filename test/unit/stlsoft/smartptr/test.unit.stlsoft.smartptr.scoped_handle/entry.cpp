/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.smartptr.scoped_handle/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft::scoped_handle`.
 *
 * Created: 16th October 2008
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/smartptr/scoped_handle.hpp>


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/conversion/union_cast.hpp>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_types_exist();

    static void test_1_0();
#if !defined(STLSOFT_COMPILER_IS_GCC) || \
     __GNUC__ > 4 || \
     (   __GNUC__ == 3 && \
         __GNUC_MINOR__ > 4)
    static void test_1_1();
    static void test_1_2();
    static void test_1_3();
    static void test_1_4();
    static void test_1_5();
    static void test_1_6();
    static void test_1_7();
    static void test_1_8();
    static void test_1_9();
    static void test_1_10();
    static void test_1_11();
    static void test_1_12();
    static void test_1_13();
    static void test_1_14();
    static void test_1_15();
    static void test_1_16();
    static void test_1_17();
    static void test_1_18();
    static void test_1_19();
#endif /* compiler */
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.smartptr.scoped_handle", verbosity))
    {
        XTESTS_RUN_CASE(test_types_exist);

        XTESTS_RUN_CASE(test_1_0);
#if !defined(STLSOFT_COMPILER_IS_GCC) || \
     __GNUC__ > 4 || \
     (   __GNUC__ == 3 && \
         __GNUC_MINOR__ > 4)
        XTESTS_RUN_CASE(test_1_1);
        XTESTS_RUN_CASE(test_1_2);
        XTESTS_RUN_CASE(test_1_3);
        XTESTS_RUN_CASE(test_1_4);
        XTESTS_RUN_CASE(test_1_5);
        XTESTS_RUN_CASE(test_1_6);
        XTESTS_RUN_CASE(test_1_7);
        XTESTS_RUN_CASE(test_1_8);
        XTESTS_RUN_CASE(test_1_9);
        XTESTS_RUN_CASE(test_1_10);
        XTESTS_RUN_CASE(test_1_11);
        XTESTS_RUN_CASE(test_1_12);
        XTESTS_RUN_CASE(test_1_13);
        XTESTS_RUN_CASE(test_1_14);
        XTESTS_RUN_CASE(test_1_15);
        XTESTS_RUN_CASE(test_1_16);
        XTESTS_RUN_CASE(test_1_17);
        XTESTS_RUN_CASE(test_1_18);
        XTESTS_RUN_CASE(test_1_19);
#endif /* compiler */

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

#if defined(PLATFORMSTL_OS_IS_WINDOWS) && \
    defined(WINSTL_ARCH_IS_X86)

# define    FNDECL_1
# define    FNDECL_2    STLSOFT_CDECL
# define    FNDECL_3    STLSOFT_FASTCALL
# define    FNDECL_4    STLSOFT_STDCALL
#else

# define    FNDECL_1
# define    FNDECL_2
# define    FNDECL_3
# define    FNDECL_4
#endif


    int     s_intCount;
    int     s_voidstarCount;
    int     s_personCount;
    int     s_doubleCount;
    int     s_voidCount;

    int     alloc_int(bool succeeds);   // Returns -1 on failure
    int     FNDECL_1 free_int(int r);
    void    FNDECL_2 free_int_v(int r);
    int     FNDECL_1 free_int_p(int* r);
    void    FNDECL_2 free_int_v_p(int* r);

    void*   alloc_voidstar(bool succeeds);
    void*   FNDECL_3 free_voidstar(void* r);
    void    FNDECL_4 free_voidstar_v(void* r);

    class Person
    {};

    Person* alloc_Personstar(bool succeeds);
    Person* FNDECL_1 free_Personstar(Person* r);
    void    FNDECL_2 free_Personstar_v(Person* r);

    double  alloc_double(bool succeeds);
    double  FNDECL_3 free_double(double r);
    void    FNDECL_4 free_double_v(double r);

    void    alloc_void();
    void    FNDECL_1 free_void_1();
    void    FNDECL_2 free_void_2();
    void    FNDECL_3 free_void_3();
    void    FNDECL_4 free_void_4();
} // anonymous namespace

namespace {

static void test_types_exist()
{
    STLSOFT_SUPPRESS_UNUSED(typeid(stlsoft::scoped_handle<char*>));
    STLSOFT_SUPPRESS_UNUSED(typeid(stlsoft::scoped_handle<void>));

    TEST_PASSED();
}

static void test_1_0()
{
    TEST_INT_EQ(0, s_intCount);

    {
        stlsoft::scoped_handle<int> scoper(alloc_int(true), free_int_v, -1);

        TEST_INT_EQ(1, s_intCount);
    }

    TEST_INT_EQ(0, s_intCount);

    {
        stlsoft::scoped_handle<int> scoper(alloc_int(true), free_int, -1);

        TEST_INT_EQ(1, s_intCount);
    }

    TEST_INT_EQ(0, s_intCount);

    {
        stlsoft::scoped_handle<int> scoper(alloc_int(false), free_int_v, -1);

        TEST_INT_EQ(0, s_intCount);
    }

    TEST_INT_EQ(0, s_intCount);

    {
        stlsoft::scoped_handle<int> scoper(alloc_int(false), free_int, -1);

        TEST_INT_EQ(0, s_intCount);
    }

    TEST_INT_EQ(0, s_intCount);

    {
        stlsoft::scoped_handle<int> scoper(alloc_int(true), free_int_v, -1);

        TEST_INT_EQ(1, s_intCount);

        {
            stlsoft::scoped_handle<int> scoper_2(alloc_int(true), free_int, -1);

            TEST_INT_EQ(2, s_intCount);
        }

        TEST_INT_EQ(1, s_intCount);
    }

    TEST_INT_EQ(0, s_intCount);
}

#if !defined(STLSOFT_COMPILER_IS_GCC) || \
     __GNUC__ > 4 || \
     (   __GNUC__ == 3 && \
         __GNUC_MINOR__ > 4)

static void test_1_1()
{
    TEST_INT_EQ(0, s_doubleCount);

    {
        stlsoft::scoped_handle<double>  scoper(alloc_double(true), free_double_v);

        TEST_INT_EQ(1, s_doubleCount);
    }

    TEST_INT_EQ(0, s_doubleCount);

    {
        stlsoft::scoped_handle<double>  scoper(alloc_double(true), free_double);

        TEST_INT_EQ(1, s_doubleCount);
    }

    TEST_INT_EQ(0, s_doubleCount);

    {
        stlsoft::scoped_handle<double>  scoper(alloc_double(false), free_double_v);

        TEST_INT_EQ(0, s_doubleCount);
    }

    TEST_INT_EQ(0, s_doubleCount);

    {
        stlsoft::scoped_handle<double>  scoper(alloc_double(false), free_double);

        TEST_INT_EQ(0, s_doubleCount);
    }

    TEST_INT_EQ(0, s_doubleCount);

    {
        stlsoft::scoped_handle<double>  scoper(alloc_double(true), free_double_v);

        TEST_INT_EQ(1, s_doubleCount);

        {
            stlsoft::scoped_handle<double>  scoper_2(alloc_double(true), free_double);

            TEST_INT_EQ(2, s_doubleCount);
        }

        TEST_INT_EQ(1, s_doubleCount);
    }

    TEST_INT_EQ(0, s_doubleCount);
}

static void test_1_2()
{
    TEST_INT_EQ(0, s_voidstarCount);

    {
        stlsoft::scoped_handle<void*>   scoper(alloc_voidstar(true), free_voidstar_v);

        TEST_INT_EQ(1, s_voidstarCount);
    }

    TEST_INT_EQ(0, s_voidstarCount);

    {
        stlsoft::scoped_handle<void*>   scoper(alloc_voidstar(true), free_voidstar);

        TEST_INT_EQ(1, s_voidstarCount);
    }

    TEST_INT_EQ(0, s_voidstarCount);

    {
        stlsoft::scoped_handle<void*>   scoper(alloc_voidstar(false), free_voidstar_v);

        TEST_INT_EQ(0, s_voidstarCount);
    }

    TEST_INT_EQ(0, s_voidstarCount);

    {
        stlsoft::scoped_handle<void*>   scoper(alloc_voidstar(false), free_voidstar);

        TEST_INT_EQ(0, s_voidstarCount);
    }

    TEST_INT_EQ(0, s_voidstarCount);

    {
        stlsoft::scoped_handle<void*>   scoper(alloc_voidstar(true), free_voidstar_v);

        TEST_INT_EQ(1, s_voidstarCount);

        {
            stlsoft::scoped_handle<void*>   scoper_2(alloc_voidstar(true), free_voidstar);

            TEST_INT_EQ(2, s_voidstarCount);
        }

        TEST_INT_EQ(1, s_voidstarCount);
    }

    TEST_INT_EQ(0, s_voidstarCount);
}

static void test_1_3()
{
    TEST_INT_EQ(0, s_personCount);

    {
        stlsoft::scoped_handle<Person*> scoper(alloc_Personstar(true), free_Personstar_v);

        TEST_INT_EQ(1, s_personCount);
    }

    TEST_INT_EQ(0, s_personCount);

    {
        stlsoft::scoped_handle<Person*> scoper(alloc_Personstar(true), free_Personstar);

        TEST_INT_EQ(1, s_personCount);
    }

    TEST_INT_EQ(0, s_personCount);

    {
        stlsoft::scoped_handle<Person*> scoper(alloc_Personstar(false), free_Personstar_v);

        TEST_INT_EQ(0, s_personCount);
    }

    TEST_INT_EQ(0, s_personCount);

    {
        stlsoft::scoped_handle<Person*> scoper(alloc_Personstar(false), free_Personstar);

        TEST_INT_EQ(0, s_personCount);
    }

    TEST_INT_EQ(0, s_personCount);

    {
        stlsoft::scoped_handle<Person*> scoper(alloc_Personstar(true), free_Personstar_v);

        TEST_INT_EQ(1, s_personCount);

        {
            stlsoft::scoped_handle<Person*> scoper_2(alloc_Personstar(true), free_Personstar);

            TEST_INT_EQ(2, s_personCount);
        }

        TEST_INT_EQ(1, s_personCount);
    }

    TEST_INT_EQ(0, s_personCount);
}

static void test_1_4()
{
    TEST_INT_EQ(0, s_intCount);

    {
        stlsoft::scoped_handle<int> scoper(alloc_int(true), free_int_v, -1);

        TEST_INT_EQ(1, s_intCount);
    }

    TEST_INT_EQ(0, s_intCount);

    {
        stlsoft::scoped_handle<int> scoper(alloc_int(true), free_int, -1);

        TEST_INT_EQ(1, s_intCount);
    }

    TEST_INT_EQ(0, s_intCount);

    {
        stlsoft::scoped_handle<int> scoper(alloc_int(false), free_int_v, -1);

        TEST_INT_EQ(0, s_intCount);
    }

    TEST_INT_EQ(0, s_intCount);

    {
        stlsoft::scoped_handle<int> scoper(alloc_int(false), free_int, -1);

        TEST_INT_EQ(0, s_intCount);
    }

    TEST_INT_EQ(0, s_intCount);

    {
        stlsoft::scoped_handle<int> scoper(alloc_int(true), free_int_v, -1);

        TEST_INT_EQ(1, s_intCount);

        {
            stlsoft::scoped_handle<int> scoper_2(alloc_int(true), free_int, -1);

            TEST_INT_EQ(2, s_intCount);
        }

        TEST_INT_EQ(1, s_intCount);
    }

    TEST_INT_EQ(0, s_intCount);
}

static void test_1_5()
{
}

static void test_1_6()
{
    TEST_INT_EQ(0, s_voidCount);

    {
        alloc_void();

        stlsoft::scoped_handle<void>    scoper(free_void_1);

        TEST_BOOLEAN_FALSE(scoper.empty());

        TEST_INT_EQ(1, s_voidCount);
    }

    TEST_INT_EQ(0, s_voidCount);

    {
        alloc_void();

        stlsoft::scoped_handle<void>    scoper(free_void_2);

        TEST_BOOLEAN_FALSE(scoper.empty());

        TEST_INT_EQ(1, s_voidCount);
    }

    TEST_INT_EQ(0, s_voidCount);

    {
        alloc_void();

        stlsoft::scoped_handle<void>    scoper(free_void_3);

        TEST_BOOLEAN_FALSE(scoper.empty());

        TEST_INT_EQ(1, s_voidCount);
    }

    TEST_INT_EQ(0, s_voidCount);

    {
        alloc_void();

        stlsoft::scoped_handle<void>    scoper(free_void_4);

        TEST_BOOLEAN_FALSE(scoper.empty());

        TEST_INT_EQ(1, s_voidCount);
    }

    TEST_INT_EQ(0, s_voidCount);

    {
        alloc_void();

        stlsoft::scoped_handle<void>    scoper(free_void_1);

        TEST_BOOLEAN_FALSE(scoper.empty());

        TEST_INT_EQ(1, s_voidCount);

        {
            alloc_void();

            stlsoft::scoped_handle<void> scoper_2(free_void_2);

            TEST_BOOLEAN_FALSE(scoper_2.empty());

            TEST_INT_EQ(2, s_voidCount);
        }

        TEST_INT_EQ(1, s_voidCount);
    }

    TEST_INT_EQ(0, s_voidCount);
}

static void test_1_7()
{
}

static void test_1_8()
{
}

static void test_1_9()
{
}

static void test_1_10()
{
    TEST_INT_EQ(0, s_intCount);

#if 0
    int i;

    {
        i = alloc_int(true);
        stlsoft::scoped_handle<int> scoper(&i, free_int_v_p, -1);

        TEST_INT_NE(0, i);
        TEST_INT_EQ(1, s_intCount);
    }

    TEST_INT_EQ(0, s_intCount);
    TEST_INT_EQ(0, i);
#endif

    {
        stlsoft::scoped_handle<int> scoper(alloc_int(true), free_int, -1);

        TEST_INT_EQ(1, s_intCount);
    }

    TEST_INT_EQ(0, s_intCount);

    {
        stlsoft::scoped_handle<int> scoper(alloc_int(false), free_int_v, -1);

        TEST_INT_EQ(0, s_intCount);
    }

    TEST_INT_EQ(0, s_intCount);

    {
        stlsoft::scoped_handle<int> scoper(alloc_int(false), free_int, -1);

        TEST_INT_EQ(0, s_intCount);
    }

    TEST_INT_EQ(0, s_intCount);

    {
        stlsoft::scoped_handle<int> scoper(alloc_int(true), free_int_v, -1);

        TEST_INT_EQ(1, s_intCount);

        {
            stlsoft::scoped_handle<int> scoper_2(alloc_int(true), free_int, -1);

            TEST_INT_EQ(2, s_intCount);
        }

        TEST_INT_EQ(1, s_intCount);
    }

    TEST_INT_EQ(0, s_intCount);
}

static void test_1_11()
{
}

static void test_1_12()
{
}

static void test_1_13()
{
}

static void test_1_14()
{
}

static void test_1_15()
{
}

static void test_1_16()
{
}

static void test_1_17()
{
}

static void test_1_18()
{
}

static void test_1_19()
{
}
#endif /* compiler */
} // anonymous namespace


/* ////////////////////////////////////////////////////////////////////// */

namespace {

    int alloc_int(bool succeeds)    // Returns -1 on failure
    {
        if (!succeeds)
        {
            return -1;
        }
        else
        {
            ++s_intCount;

            return 0;
        }
    }
    int FNDECL_1 free_int(int r)
    {
        if (-1 != r)
        {
            --s_intCount;
        }
        return s_intCount;
    }
    void FNDECL_2 free_int_v(int r)
    {
        free_int(r);
    }
    int FNDECL_1 free_int_p(int* r)
    {
        int r2 = free_int(*r);

        *r = 0;

        return r2;
    }
    void FNDECL_2 free_int_v_p(int* r)
    {
        free_int_v(*r);
        *r = 0;
    }

#if !defined(STLSOFT_COMPILER_IS_GCC) || \
     __GNUC__ > 4 || \
     (   __GNUC__ == 3 && \
         __GNUC_MINOR__ > 4)

    void* alloc_voidstar(bool succeeds  )
    {
        if (!succeeds)
        {
            return NULL;
        }
        else
        {
            ++s_voidstarCount;

            return &s_voidstarCount;
        }
    }
    void* FNDECL_3 free_voidstar(void* r)
    {
        if (NULL != r)
        {
            --s_voidstarCount;
        }

        return &s_voidstarCount;
    }
    void FNDECL_4 free_voidstar_v(void* r)
    {
        free_voidstar(r);
    }


    Person* alloc_Personstar(bool succeeds)
    {
        if (!succeeds)
        {
            return NULL;
        }
        else
        {
            ++s_personCount;

            return stlsoft::union_cast<Person*>(&s_personCount);
        }
    }
    Person* FNDECL_1 free_Personstar(Person* r)
    {
        if (NULL != r)
        {
            --s_personCount;
        }
        return NULL;
    }
    void FNDECL_2 free_Personstar_v(Person* r)
    {
        free_Personstar(r);
    }


    double alloc_double(bool succeeds)
    {
        if (!succeeds)
        {
            return 0.0;
        }
        else
        {
            ++s_doubleCount;

            return 1.0;
        }
    }
    double FNDECL_3 free_double(double r)
    {
        if (0.0 != r)
        {
            --s_doubleCount;
        }
        return s_doubleCount;
    }
    void FNDECL_4 free_double_v(double r)
    {
        free_double(r);
    }


    void alloc_void()
    {
        ++s_voidCount;
    }

    void FNDECL_1 free_void_1()
    {
        --s_voidCount;
    }

    void FNDECL_2 free_void_2()
    {
        --s_voidCount;
    }

    void FNDECL_3 free_void_3()
    {
        --s_voidCount;
    }

    void FNDECL_4 free_void_4()
    {
        --s_voidCount;
    }
#endif /* compiler */
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */


