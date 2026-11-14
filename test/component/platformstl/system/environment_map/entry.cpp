#include <platformstl/system/environment_map.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {

    static void TEST_ENUMERATION();
    static void TEST_LOOKUP_PATH();
}

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER(__FILE__, verbosity))
    {
        XTESTS_RUN_CASE(TEST_ENUMERATION);
        XTESTS_RUN_CASE(TEST_LOOKUP_PATH);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

namespace {

static void TEST_ENUMERATION()
{
#ifdef PLATFORMSTL_ENVVAR_HAS_ENVIRON
    platformstl::environment_map em;
    TEST_BOOLEAN_TRUE(em.begin() != em.end());
#endif
}

static void TEST_LOOKUP_PATH()
{
#ifdef PLATFORMSTL_ENVVAR_HAS_ENVIRON
#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable : 4996)
#endif
    char const* const path = ::getenv("PATH");
#if defined(_MSC_VER)
# pragma warning(pop)
#endif
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
