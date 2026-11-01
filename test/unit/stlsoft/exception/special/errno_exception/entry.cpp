/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/stlsoft/exception/special/errno_exception/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft::errno_exception`.
 *
 * Created: 1st November 2026
 * Updated: 1st November 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/shims/access/string/std/basic_string.hpp>
#include <stlsoft/exception/special/errno_exception.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* Standard C++ header files */
#include <stdexcept>
#include <string>

/* Standard C header files */
#include <errno.h>
#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static std::string crt_message_(int e);

    static void TEST_ERRNO_0();
    static void TEST_EACCES();
    static void TEST_EEXIST();
    static void TEST_EINVAL();
    static void TEST_EIO();
    static void TEST_ENOENT();
    static void TEST_ENOMEM();
    static void TEST_EPERM();
    static void TEST_ERANGE();
    static void TEST_UNKNOWN_ERRNO();
    static void TEST_NEGATIVE_ERRNO();
    static void TEST_MESSAGE_CHAR();
    static void TEST_MESSAGE_STD_STRING();
    static void TEST_MESSAGE_EMPTY();
    static void TEST_MESSAGE_LONG();
    static void TEST_MESSAGE_DOES_NOT_REPLACE_ERRNO();
    static void TEST_COPY();
    static void TEST_CAUGHT_AS_ERRNO_EXCEPTION();
    static void TEST_CAUGHT_AS_RUNTIME_ERROR();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER(__FILE__, verbosity))
    {
        XTESTS_RUN_CASE(TEST_ERRNO_0);
        XTESTS_RUN_CASE(TEST_EACCES);
        XTESTS_RUN_CASE(TEST_EEXIST);
        XTESTS_RUN_CASE(TEST_EINVAL);
        XTESTS_RUN_CASE(TEST_EIO);
        XTESTS_RUN_CASE(TEST_ENOENT);
        XTESTS_RUN_CASE(TEST_ENOMEM);
        XTESTS_RUN_CASE(TEST_EPERM);
        XTESTS_RUN_CASE(TEST_ERANGE);
        XTESTS_RUN_CASE(TEST_UNKNOWN_ERRNO);
        XTESTS_RUN_CASE(TEST_NEGATIVE_ERRNO);
        XTESTS_RUN_CASE(TEST_MESSAGE_CHAR);
        XTESTS_RUN_CASE(TEST_MESSAGE_STD_STRING);
        XTESTS_RUN_CASE(TEST_MESSAGE_EMPTY);
        XTESTS_RUN_CASE(TEST_MESSAGE_LONG);
        XTESTS_RUN_CASE(TEST_MESSAGE_DOES_NOT_REPLACE_ERRNO);
        XTESTS_RUN_CASE(TEST_COPY);
        XTESTS_RUN_CASE(TEST_CAUGHT_AS_ERRNO_EXCEPTION);
        XTESTS_RUN_CASE(TEST_CAUGHT_AS_RUNTIME_ERROR);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * helper functions
 */

namespace {

    static std::string crt_message_(int e)
    {
#if defined(STLSOFT_USING_SAFE_STR_FUNCTIONS)

        char        buff[1001];
        int const   err =   ::strerror_s(buff, e);

        if (0 != err)
        {
            return std::string("unknown failure");
        }

        return std::string(buff);
#else /* ? STLSOFT_USING_SAFE_STR_FUNCTIONS */

        return std::string(::strerror(e));
#endif /* STLSOFT_USING_SAFE_STR_FUNCTIONS */
    }
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_ERRNO_0()
{
    stlsoft::errno_exception const  x(0);
    std::string const               crt(crt_message_(0));
    char const* const               expecteds[] =
    {
        "No error",
        "Success",
        "Undefined error: 0",
    };

    TEST_INT_EQ(0, x.ErrnoValue);
    TEST_PTR_NOT_NULL(x.what());
    TEST_MS_EQ(crt.c_str(), x.what());
    TEST_MS_EQ_ANY_OF(expecteds, STLSOFT_NUM_ELEMENTS(expecteds), x.what());
}

static void TEST_EACCES()
{
    stlsoft::errno_exception const  x(EACCES);
    std::string const               crt(crt_message_(EACCES));

    TEST_INT_EQ(EACCES, x.ErrnoValue);
    TEST_PTR_NOT_NULL(x.what());
    TEST_MS_EQ(crt.c_str(), x.what());
    TEST_MS_MATCHES("*ermission denied*", x.what());
}

static void TEST_EEXIST()
{
    stlsoft::errno_exception const  x(EEXIST);
    std::string const               crt(crt_message_(EEXIST));

    TEST_INT_EQ(EEXIST, x.ErrnoValue);
    TEST_PTR_NOT_NULL(x.what());
    TEST_MS_EQ(crt.c_str(), x.what());
    TEST_MS_MATCHES("*File exists*", x.what());
}

static void TEST_EINVAL()
{
    stlsoft::errno_exception const  x(EINVAL);
    std::string const               crt(crt_message_(EINVAL));

    TEST_INT_EQ(EINVAL, x.ErrnoValue);
    TEST_PTR_NOT_NULL(x.what());
    TEST_MS_EQ(crt.c_str(), x.what());
    TEST_MS_MATCHES("*nvalid argument*", x.what());
}

static void TEST_EIO()
{
    stlsoft::errno_exception const  x(EIO);
    std::string const               crt(crt_message_(EIO));

    TEST_INT_EQ(EIO, x.ErrnoValue);
    TEST_PTR_NOT_NULL(x.what());
    TEST_MS_EQ(crt.c_str(), x.what());
    TEST_MS_EQ_ANY_OF2("I/O error", "Input/output error", x.what());
}

static void TEST_ENOENT()
{
    stlsoft::errno_exception const  x(ENOENT);
    std::string const               crt(crt_message_(ENOENT));

    TEST_INT_EQ(ENOENT, x.ErrnoValue);
    TEST_PTR_NOT_NULL(x.what());
    TEST_MS_EQ(crt.c_str(), x.what());
    TEST_MS_MATCHES("*No such file*", x.what());
}

static void TEST_ENOMEM()
{
    stlsoft::errno_exception const  x(ENOMEM);
    char const* const               expecteds[] =
    {
        "Cannot allocate memory",
        "Not enough memory",
        "Not enough space",
    };

    TEST_INT_EQ(ENOMEM, x.ErrnoValue);
    TEST_PTR_NOT_NULL(x.what());
    TEST_MS_EQ_ANY_OF(expecteds, STLSOFT_NUM_ELEMENTS(expecteds), x.what());
}

static void TEST_EPERM()
{
    stlsoft::errno_exception const  x(EPERM);
    std::string const               crt(crt_message_(EPERM));

    TEST_INT_EQ(EPERM, x.ErrnoValue);
    TEST_PTR_NOT_NULL(x.what());
    TEST_MS_EQ(crt.c_str(), x.what());
    TEST_MS_EQ_ANY_OF2("Not owner", "Operation not permitted", x.what());
}

static void TEST_ERANGE()
{
    stlsoft::errno_exception const  x(ERANGE);
    std::string const               crt(crt_message_(ERANGE));

    TEST_INT_EQ(ERANGE, x.ErrnoValue);
    TEST_PTR_NOT_NULL(x.what());
    TEST_MS_EQ(crt.c_str(), x.what());
    TEST_MS_EQ_ANY_OF2("Numerical result out of range", "Result too large", x.what());
}

static void TEST_UNKNOWN_ERRNO()
{
    int const                       e = 99999;
    stlsoft::errno_exception const  x(e);
    std::string const               crt(crt_message_(e));

    TEST_INT_EQ(e, x.ErrnoValue);
    TEST_PTR_NOT_NULL(x.what());
    TEST_MS_EQ(crt.c_str(), x.what());
    TEST_MS_MATCHES("*rror*", x.what());
    TEST_MS_DOES_NOT_MATCH("Success", x.what());
}

static void TEST_NEGATIVE_ERRNO()
{
    stlsoft::errno_exception const  x(-1);
    std::string const               crt(crt_message_(-1));

    TEST_INT_EQ(-1, x.ErrnoValue);
    TEST_PTR_NOT_NULL(x.what());
    TEST_MS_EQ(crt.c_str(), x.what());
    TEST_MS_MATCHES("*rror*", x.what());
}

static void TEST_MESSAGE_CHAR()
{
    stlsoft::errno_exception const x(EIO, "disk failed");

    TEST_INT_EQ(EIO, x.ErrnoValue);
    TEST_MS_EQ("disk failed", x.what());
}

static void TEST_MESSAGE_STD_STRING()
{
    std::string const               message("from string");
    stlsoft::errno_exception const  x(EINVAL, message);

    TEST_INT_EQ(EINVAL, x.ErrnoValue);
    TEST_MS_EQ("from string", x.what());
}

static void TEST_MESSAGE_EMPTY()
{
    stlsoft::errno_exception const x(0, "");

    TEST_INT_EQ(0, x.ErrnoValue);
    TEST_MS_EQ("", x.what());
}

static void TEST_MESSAGE_LONG()
{
    std::string const               message(2000, 'm');
    stlsoft::errno_exception const  x(EINVAL, message);

    TEST_INT_EQ(EINVAL, x.ErrnoValue);
    TEST_MS_EQ(message.c_str(), x.what());
    TEST_INT_EQ(2000, ::strlen(x.what()));
}

static void TEST_MESSAGE_DOES_NOT_REPLACE_ERRNO()
{
    stlsoft::errno_exception const x(ENOENT, "supplied");

    TEST_INT_EQ(ENOENT, x.ErrnoValue);
    TEST_MS_EQ("supplied", x.what());
    TEST_MS_DOES_NOT_MATCH("*No such file*", x.what());
}

static void TEST_COPY()
{
    stlsoft::errno_exception const  original(ENOENT);
    stlsoft::errno_exception const  copy(original);

    TEST_INT_EQ(ENOENT, copy.ErrnoValue);
    TEST_MS_EQ(original.what(), copy.what());
    TEST_MS_MATCHES("*No such file*", copy.what());
}

static void TEST_CAUGHT_AS_ERRNO_EXCEPTION()
{
    try
    {
        throw stlsoft::errno_exception(ENOENT);
    }
    catch (stlsoft::errno_exception const& x)
    {
        TEST_INT_EQ(ENOENT, x.ErrnoValue);
        TEST_MS_MATCHES("*No such file*", x.what());

        return;
    }
    catch (...)
    {
    }

    TEST_FAIL("errno_exception was not caught");
}

static void TEST_CAUGHT_AS_RUNTIME_ERROR()
{
    try
    {
        throw stlsoft::errno_exception(EACCES);
    }
    catch (std::runtime_error const& x)
    {
        TEST_MS_MATCHES("*ermission denied*", x.what());

        return;
    }
    catch (...)
    {
    }

    TEST_FAIL("std::runtime_error was not caught");
}
} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */
