#include <platformstl/system/environment_map.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_enumeration(void); static void test_lookup_path(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.platformstl.system.environment_map", verbosity))
    {
        XTESTS_RUN_CASE(test_enumeration);
        XTESTS_RUN_CASE(test_lookup_path);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

namespace {

static void test_enumeration(void)
{
#ifdef PLATFORMSTL_ENVVAR_HAS_ENVIRON
    platformstl::environment_map em;
    TEST_BOOLEAN_TRUE(em.begin() != em.end());
#endif
}

static void test_lookup_path(void)
{
#ifdef PLATFORMSTL_ENVVAR_HAS_ENVIRON
    char const* const path = ::getenv("PATH");
    if (NULL != path)
    {
        platformstl::environment_map em;
        bool found = false;
        for (platformstl::environment_map::const_iterator i = em.begin(); em.end() != i; ++i)
        {
            if ((*i).first == "PATH")
            {
                TEST_MS_EQ(path, (*i).second);
                found = true;
                break;
            }
        }
        TEST_BOOLEAN_TRUE(found);
    }
#endif
}
} // anonymous namespace
