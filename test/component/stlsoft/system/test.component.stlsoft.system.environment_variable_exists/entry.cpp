/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.stlsoft.system.environment_variable_exists/entry.cpp
 *
 * Purpose: Component-tests for `stlsoft::environment_variable_exists()`.
 *
 * Created: 28th September 2026
 * Updated: 28th September 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

/* String-access shims must be visible before functions.hpp so the template
 * overload can bind c_str_ptr() for these types.
 */
#include <stlsoft/shims/access/string/std/basic_string.hpp>
#include <stlsoft/string/simple_string.hpp>
#include <stlsoft/system/environment/functions.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <platformstl/system/environment_variable_scope.hpp>
#include <stlsoft/stlsoft.h>

/* Standard C++ header files */
#include <string>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_environment_variable_exists_WHEN_ABSENT();
    static void TEST_environment_variable_exists_WHEN_PRESENT();
    static void TEST_environment_variable_exists_WHEN_ERASED();
    static void TEST_environment_variable_exists_WHEN_VALUE_REPLACED();
    static void TEST_environment_variable_exists_EXACT_NAME();
    static void TEST_environment_variable_exists_WITH_std_string();
    static void TEST_environment_variable_exists_WITH_simple_string();
#ifndef _WIN32
    static void TEST_environment_variable_exists_WHEN_EMPTY();
#endif /* !_WIN32 */
    static void TEST_environment_variable_exists_CASE_SENSITIVITY();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.stlsoft.system.environment_variable_exists", verbosity))
    {
        XTESTS_RUN_CASE(TEST_environment_variable_exists_WHEN_ABSENT);
        XTESTS_RUN_CASE(TEST_environment_variable_exists_WHEN_PRESENT);
        XTESTS_RUN_CASE(TEST_environment_variable_exists_WHEN_ERASED);
        XTESTS_RUN_CASE(TEST_environment_variable_exists_WHEN_VALUE_REPLACED);
        XTESTS_RUN_CASE(TEST_environment_variable_exists_EXACT_NAME);
        XTESTS_RUN_CASE(TEST_environment_variable_exists_WITH_std_string);
        XTESTS_RUN_CASE(TEST_environment_variable_exists_WITH_simple_string);
#ifndef _WIN32
        XTESTS_RUN_CASE(TEST_environment_variable_exists_WHEN_EMPTY);
#endif /* !_WIN32 */
        XTESTS_RUN_CASE(TEST_environment_variable_exists_CASE_SENSITIVITY);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * constants
 */

namespace {

    using platformstl::environment_variable_scope;

    char const VAR_NAME[]         = "STLSOFT_CT_ENV_VAR_EXISTS";
    char const VAR_NAME_EXTRA[]   = "STLSOFT_CT_ENV_VAR_EXISTS_EXTRA";
    char const VAR_NAME_PREFIX[]  = "STLSOFT_CT_ENV_VAR";
    char const VAR_NAME_UPPER[]   = "STLSOFT_CT_ENV_VAR_EXISTS_CASE";
    char const VAR_NAME_LOWER[]   = "stlsoft_ct_env_var_exists_case";
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_environment_variable_exists_WHEN_ABSENT()
{
    environment_variable_scope const absent(VAR_NAME, ss_nullptr_k);

    char const* const name = VAR_NAME;

    TEST_BOOLEAN_FALSE(stlsoft::environment_variable_exists(name));
    TEST_BOOLEAN_FALSE(stlsoft::stlsoft_C_environment_variable_exists_a(name));
    TEST_BOOLEAN_FALSE(stlsoft::environment_variable_exists("STLSOFT_CT_ENV_VAR_EXISTS_NO_SUCH"));
}

static void TEST_environment_variable_exists_WHEN_PRESENT()
{
    environment_variable_scope const present(VAR_NAME, "present");

    char const* const name = VAR_NAME;

    TEST_BOOLEAN_TRUE(stlsoft::environment_variable_exists(name));
    TEST_BOOLEAN_TRUE(stlsoft::stlsoft_C_environment_variable_exists_a(name));
}

static void TEST_environment_variable_exists_WHEN_ERASED()
{
    environment_variable_scope const present(VAR_NAME, "present");

    TEST_BOOLEAN_TRUE(stlsoft::environment_variable_exists(VAR_NAME));

    environment_variable_scope const erased(VAR_NAME, ss_nullptr_k);

    char const* const name = VAR_NAME;

    TEST_BOOLEAN_FALSE(stlsoft::environment_variable_exists(name));
}

static void TEST_environment_variable_exists_WHEN_VALUE_REPLACED()
{
    environment_variable_scope const first(VAR_NAME, "one");

    char const* const name = VAR_NAME;

    TEST_BOOLEAN_TRUE(stlsoft::environment_variable_exists(name));

    environment_variable_scope const second(VAR_NAME, "two");

    TEST_BOOLEAN_TRUE(stlsoft::environment_variable_exists(name));
}

static void TEST_environment_variable_exists_EXACT_NAME()
{
    environment_variable_scope const extra_absent(VAR_NAME_EXTRA, ss_nullptr_k);
    environment_variable_scope const prefix_absent(VAR_NAME_PREFIX, ss_nullptr_k);
    environment_variable_scope const present(VAR_NAME, "value");

    TEST_BOOLEAN_TRUE(stlsoft::environment_variable_exists(VAR_NAME));
    TEST_BOOLEAN_FALSE(stlsoft::environment_variable_exists(VAR_NAME_EXTRA));
    TEST_BOOLEAN_FALSE(stlsoft::environment_variable_exists(VAR_NAME_PREFIX));

    environment_variable_scope const erased(VAR_NAME, ss_nullptr_k);
    environment_variable_scope const extra(VAR_NAME_EXTRA, "extra");

    TEST_BOOLEAN_FALSE(stlsoft::environment_variable_exists(VAR_NAME));
    TEST_BOOLEAN_TRUE(stlsoft::environment_variable_exists(VAR_NAME_EXTRA));
}

static void TEST_environment_variable_exists_WITH_std_string()
{
    {
        environment_variable_scope const absent(VAR_NAME, ss_nullptr_k);

        std::string const name(VAR_NAME);

        TEST_BOOLEAN_FALSE(stlsoft::environment_variable_exists(name));
    }

    environment_variable_scope const present(VAR_NAME, "present");

    std::string const name(VAR_NAME);

    TEST_BOOLEAN_TRUE(stlsoft::environment_variable_exists(name));
}

static void TEST_environment_variable_exists_WITH_simple_string()
{
    {
        environment_variable_scope const absent(VAR_NAME, ss_nullptr_k);

        stlsoft::simple_string const name(VAR_NAME);

        TEST_BOOLEAN_FALSE(stlsoft::environment_variable_exists(name));
    }

    environment_variable_scope const present(VAR_NAME, "present");

    stlsoft::simple_string const name(VAR_NAME);

    TEST_BOOLEAN_TRUE(stlsoft::environment_variable_exists(name));
}
#ifndef _WIN32

/* An empty value is a defined variable on UNIX. The Windows CRT treats an
 * empty assignment as erasure, so this case is UNIX-only.
 */
static void TEST_environment_variable_exists_WHEN_EMPTY()
{
    environment_variable_scope const empty(VAR_NAME, "");

    char const* const value = ::getenv(VAR_NAME);

    XTESTS_REQUIRE(TEST_PTR_NE(NULL, value));
    TEST_MS_EQ("", value);

    char const* const name = VAR_NAME;

    TEST_BOOLEAN_TRUE(stlsoft::environment_variable_exists(name));
}
#endif /* !_WIN32 */

/* UNIX names are case-sensitive; the Windows CRT folds case.
 */
static void TEST_environment_variable_exists_CASE_SENSITIVITY()
{
    environment_variable_scope const lower(VAR_NAME_LOWER, ss_nullptr_k);
    environment_variable_scope const upper(VAR_NAME_UPPER, "1");

    TEST_BOOLEAN_TRUE(stlsoft::environment_variable_exists(VAR_NAME_UPPER));
#ifdef _WIN32

    TEST_BOOLEAN_TRUE(stlsoft::environment_variable_exists(VAR_NAME_LOWER));
#else

    TEST_BOOLEAN_FALSE(stlsoft::environment_variable_exists(VAR_NAME_LOWER));
#endif
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

