/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.winstl.registry.reg_value_sequence/entry.cpp
 *
 * Purpose: Unit-tests for `winstl::reg_value_sequence`.
 *
 * Created: 22nd October 2024
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <winstl/registry/reg_value_sequence.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <winstl/registry/reg_key.hpp>

/* Standard C++ header files */
#include <string>
#include <vector>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_1_12();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * helper functions
 */

namespace {

    static winstl::reg_key* rootKey;
}

static int setup(void* /* arg */)
{
    try
    {
        rootKey = new winstl::reg_key(winstl::reg_key::create_key(HKEY_CURRENT_USER, "SOFTWARE\\Synesis Software\\freelibs\\STLSoft\\test\\test.unit.winstl.registry.reg_value_sequence"));

        return 0;
    }
    catch (winstl::registry_exception& x)
    {
        fprintf(stderr, "setup() failed to create registry key: %s: %lu\n", x.what(), static_cast<DWORD>(x.status_code()));

        return -1;
    }
    catch (std::exception& x)
    {
        fprintf(stderr, "setup() failed to create registry key: %s\n", x.what());

        return -1;
    }
}

static int teardown(void* /* arg */)
{
    winstl::reg_traits<char>::reg_delete_tree(rootKey->get(), "");

    delete rootKey;
    rootKey = NULL;

    return 0;
}


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char **argv)
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER_WITH_SETUP_FNS("test.component.winstl.registry.reg_value_sequence", verbosity, setup, teardown, NULL))
    {
        XTESTS_RUN_CASE(test_1_12);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

    using winstl::reg_value;
    using winstl::reg_value_sequence;

static void test_1_12()
{
    rootKey->set_value("value-name-1", "value-1");
    rootKey->set_value("value-name-2", "value-2");
    rootKey->set_value("value-name-3", "value-3");
    rootKey->set_value("value-name-4", "value-4");

    reg_value_sequence values(*rootKey);

    std::vector<std::string>    value_names;
    std::vector<std::string>    value_values;

    reg_value recorded_value;

    { for (reg_value_sequence::const_iterator i = values.begin(); values.end() != i; ++i)
    {
        reg_value const v(*i);

        TEST_ENUM_NE(REG_NONE, v.type());

        value_names.push_back(v.name().c_str());
        value_values.push_back(v.value_sz().c_str());

        {
            if (REG_NONE == recorded_value.type() &&
                "*" == v.name())
            {
                recorded_value = v;
            }
            else if ("Debug" == v.name())
            {
                recorded_value = v;
            }
        }
    }}
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

