/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.winstl.system.directory_functions/entry.cpp
 *
 * Purpose: Component test for WinSTL atomic_functions.
 *
 * Created: sometime in 2015
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* ///////////////////////////////////////////////
 * test component header file include(s)
 */

#include <winstl/system/directory_functions.h>

/* ///////////////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <platformstl/system/environment_variable_scope.hpp>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    void TEST_get_home_directory_EXCESS_SPACE();
    void TEST_get_home_directory_SUFFICIENT_SPACE();
    void TEST_get_home_directory_INSUFFICIENT_SPACE();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.winstl.system.directory_functions", verbosity))
    {
        XTESTS_RUN_CASE(TEST_get_home_directory_EXCESS_SPACE);
        XTESTS_RUN_CASE(TEST_get_home_directory_SUFFICIENT_SPACE);
        XTESTS_RUN_CASE(TEST_get_home_directory_INSUFFICIENT_SPACE);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

void TEST_get_home_directory_EXCESS_SPACE()
{
    platformstl::environment_variable_scope scoper_HOMEDRIVE("HOMEDRIVE", "X:");
    platformstl::environment_variable_scope scoper_HOMEPATH("HOMEPATH", "\\Users\\me");
    platformstl::environment_variable_scope scoper_USERPROFILE("USERPROFILE", "X:\\Users\\me");

    {
        char            buff[1001];
        size_t const    cch =   winstl::get_home_directory(buff, STLSOFT_NUM_ELEMENTS(buff));

        TEST_INT_EQ(11, cch);
        TEST_MS_EQ("X:\\Users\\me", buff);
    }
#ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT

    {
        char            buff[1001];
        size_t const    cch =   winstl::get_home_directory(buff);

        TEST_INT_EQ(11, cch);
        TEST_MS_EQ("X:\\Users\\me", buff);
    }
#endif /* STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT */
}

void TEST_get_home_directory_SUFFICIENT_SPACE()
{
    platformstl::environment_variable_scope scoper_HOMEDRIVE("HOMEDRIVE", "X:");
    platformstl::environment_variable_scope scoper_HOMEPATH("HOMEPATH", "\\Users\\me");
    platformstl::environment_variable_scope scoper_USERPROFILE("USERPROFILE", "Y:\\Users\\me");

    {
        {
            char            buff[12];
            size_t const    cch =   winstl::get_home_directory(buff, STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(11, cch);
            TEST_MS_EQ("Y:\\Users\\me", buff);
        }

        {
            wchar_t         buff[12];
            size_t const    cch =   winstl::get_home_directory(buff, STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(11, cch);
            TEST_WS_EQ(L"Y:\\Users\\me", buff);
        }
#ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT

        {
            char            buff[12];
            size_t const    cch =   winstl::get_home_directory(buff);

            TEST_INT_EQ(11, cch);
            TEST_MS_EQ("Y:\\Users\\me", buff);
        }

        {
            wchar_t         buff[12];
            size_t const    cch =   winstl::get_home_directory(buff);

            TEST_INT_EQ(11, cch);
            TEST_WS_EQ(L"Y:\\Users\\me", buff);
        }
#endif /* STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT */
    }

    {
        {
            platformstl::environment_variable_scope scoper_HOMEDRIVE_1("HOMEDRIVE", NULL);
            platformstl::environment_variable_scope scoper_HOMEPATH_1("HOMEPATH", NULL);

            {
                char            buff[12];
                size_t const    cch =   winstl::get_home_directory(buff, STLSOFT_NUM_ELEMENTS(buff));

                TEST_INT_EQ(11, cch);
                TEST_MS_EQ("Y:\\Users\\me", buff);
            }
        }
#ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT

        {
            platformstl::environment_variable_scope scoper_HOMEDRIVE_1("HOMEDRIVE", NULL);
            platformstl::environment_variable_scope scoper_HOMEPATH_1("HOMEPATH", NULL);

            {
                char            buff[12];
                size_t const    cch =   winstl::get_home_directory(buff);

                TEST_INT_EQ(11, cch);
                TEST_MS_EQ("Y:\\Users\\me", buff);
            }
        }
#endif /* STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT */
    }

    {
        {
            platformstl::environment_variable_scope scoper_HOMEDRIVE_2("HOMEDRIVE", NULL);

            {
                char            buff[12];
                size_t const    cch =   winstl::get_home_directory(buff, STLSOFT_NUM_ELEMENTS(buff));

                TEST_INT_EQ(11, cch);
                TEST_MS_EQ("Y:\\Users\\me", buff);
            }
        }
#ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT

        {
            platformstl::environment_variable_scope scoper_HOMEDRIVE_2("HOMEDRIVE", NULL);

            {
                char            buff[12];
                size_t const    cch =   winstl::get_home_directory(buff);

                TEST_INT_EQ(11, cch);
                TEST_MS_EQ("Y:\\Users\\me", buff);
            }
        }
#endif /* STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT */
    }

    {
        {
            platformstl::environment_variable_scope scoper_HOMEPATH_3("HOMEPATH", NULL);

            {
                char            buff[12];
                size_t const    cch =   winstl::get_home_directory(buff, STLSOFT_NUM_ELEMENTS(buff));

                TEST_INT_EQ(11, cch);
                TEST_MS_EQ("Y:\\Users\\me", buff);
            }
        }
#ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT

        {
            platformstl::environment_variable_scope scoper_HOMEPATH_3("HOMEPATH", NULL);

            {
                char            buff[12];
                size_t const    cch =   winstl::get_home_directory(buff);

                TEST_INT_EQ(11, cch);
                TEST_MS_EQ("Y:\\Users\\me", buff);
            }
        }
#endif /* STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT */
    }

    {
        {
            platformstl::environment_variable_scope scoper_USERPROFILE_4("USERPROFILE", NULL);

            {
                char            buff[12];
                size_t const    cch =   winstl::get_home_directory(buff, STLSOFT_NUM_ELEMENTS(buff));

                TEST_INT_EQ(11, cch);
                TEST_MS_EQ("X:\\Users\\me", buff);
            }
        }
#ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT

        {
            platformstl::environment_variable_scope scoper_USERPROFILE_4("USERPROFILE", NULL);

            {
                char            buff[12];
                size_t const    cch =   winstl::get_home_directory(buff);

                TEST_INT_EQ(11, cch);
                TEST_MS_EQ("X:\\Users\\me", buff);
            }
        }
#endif /* STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT */
    }
}

void TEST_get_home_directory_INSUFFICIENT_SPACE()
{
    platformstl::environment_variable_scope scoper_HOMEDRIVE("HOMEDRIVE", "X:");
    platformstl::environment_variable_scope scoper_HOMEPATH("HOMEPATH", "\\Users\\me");
    platformstl::environment_variable_scope scoper_USERPROFILE("USERPROFILE", "X:\\Users\\me");

    {
        {
            char            buff[1] = { '~' };
            size_t const    cch =   winstl::get_home_directory(buff, STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(12, cch);
            TEST_CHAR_EQ('\0', buff[0]);
        }
#ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT

        {
            char            buff[1] = { '~' };
            size_t const    cch =   winstl::get_home_directory(buff);

            TEST_INT_EQ(12, cch);
            TEST_CHAR_EQ('\0', buff[0]);
        }
#endif /* STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT */
    }

    {
        {
            char            buff[10] = { '~' };
            size_t const    cch =   winstl::get_home_directory(buff, STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(12, cch);
            TEST_CHAR_EQ('\0', buff[0]);
        }
#ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT

        {
            char            buff[10] = { '~' };
            size_t const    cch =   winstl::get_home_directory(buff);

            TEST_INT_EQ(12, cch);
            TEST_CHAR_EQ('\0', buff[0]);
        }
#endif /* STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT */
    }
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

