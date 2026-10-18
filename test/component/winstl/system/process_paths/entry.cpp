/* /////////////////////////////////////////////////////////////////////////
 * File:    test/component/winstl/system/process_paths/entry.cpp
 *
 * Purpose: Component-tests for
 *          `winstl::system_traits::get_current_process_path()` (multibyte
 *          and wide-character), including resizeable-buffer overloads.
 *
 * Created: 15th October 2026
 * Updated: 18th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <winstl/system/system_traits.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/memory/auto_buffer.hpp>
#include <winstl/filesystem/filesystem_traits.hpp>

/* Standard C++ header files */
#include <string>
#include <vector>

/* Standard C / Windows header files */
#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_size_QUERY_m();
    static void TEST_size_QUERY_w();
    static void TEST_size_THEN_SUFFICIENT_m();
    static void TEST_size_THEN_SUFFICIENT_w();
    static void TEST_EXCESS_SPACE_m();
    static void TEST_EXCESS_SPACE_w();
    static void TEST_INSUFFICIENT_SPACE_m();
    static void TEST_INSUFFICIENT_SPACE_w();
    static void TEST_ppFile_NULL_ON_SUCCESS_m();
    static void TEST_ppFile_NULL_ON_SUCCESS_w();
    static void TEST_ppFile_separator_ON_SUCCESS_m();
    static void TEST_ppFile_separator_ON_SUCCESS_w();
    static void TEST_ppFile_NULL_WHEN_INSUFFICIENT_m();
    static void TEST_ppFile_NULL_WHEN_INSUFFICIENT_w();
    static void TEST_RESIZEABLE_auto_buffer_SUCCESS_m();
    static void TEST_RESIZEABLE_auto_buffer_SUCCESS_w();
    static void TEST_RESIZEABLE_vector_SUCCESS_m();
    static void TEST_RESIZEABLE_vector_SUCCESS_w();
    static void TEST_RESIZEABLE_ppFile_NULL_m();
    static void TEST_RESIZEABLE_ppFile_NULL_w();
    static void TEST_RESIZEABLE_ppFile_separator_m();
    static void TEST_RESIZEABLE_ppFile_separator_w();
    static void TEST_RESIZEABLE_resize_FAILURE_leaves_rb_untouched_m();
    static void TEST_RESIZEABLE_resize_FAILURE_leaves_rb_untouched_w();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.winstl.system.process_paths", verbosity))
    {
        XTESTS_RUN_CASE(TEST_size_QUERY_m);
        XTESTS_RUN_CASE(TEST_size_QUERY_w);
        XTESTS_RUN_CASE(TEST_size_THEN_SUFFICIENT_m);
        XTESTS_RUN_CASE(TEST_size_THEN_SUFFICIENT_w);
        XTESTS_RUN_CASE(TEST_EXCESS_SPACE_m);
        XTESTS_RUN_CASE(TEST_EXCESS_SPACE_w);
        XTESTS_RUN_CASE(TEST_INSUFFICIENT_SPACE_m);
        XTESTS_RUN_CASE(TEST_INSUFFICIENT_SPACE_w);
        XTESTS_RUN_CASE(TEST_ppFile_NULL_ON_SUCCESS_m);
        XTESTS_RUN_CASE(TEST_ppFile_NULL_ON_SUCCESS_w);
        XTESTS_RUN_CASE(TEST_ppFile_separator_ON_SUCCESS_m);
        XTESTS_RUN_CASE(TEST_ppFile_separator_ON_SUCCESS_w);
        XTESTS_RUN_CASE(TEST_ppFile_NULL_WHEN_INSUFFICIENT_m);
        XTESTS_RUN_CASE(TEST_ppFile_NULL_WHEN_INSUFFICIENT_w);
        XTESTS_RUN_CASE(TEST_RESIZEABLE_auto_buffer_SUCCESS_m);
        XTESTS_RUN_CASE(TEST_RESIZEABLE_auto_buffer_SUCCESS_w);
        XTESTS_RUN_CASE(TEST_RESIZEABLE_vector_SUCCESS_m);
        XTESTS_RUN_CASE(TEST_RESIZEABLE_vector_SUCCESS_w);
        XTESTS_RUN_CASE(TEST_RESIZEABLE_ppFile_NULL_m);
        XTESTS_RUN_CASE(TEST_RESIZEABLE_ppFile_NULL_w);
        XTESTS_RUN_CASE(TEST_RESIZEABLE_ppFile_separator_m);
        XTESTS_RUN_CASE(TEST_RESIZEABLE_ppFile_separator_w);
        XTESTS_RUN_CASE(TEST_RESIZEABLE_resize_FAILURE_leaves_rb_untouched_m);
        XTESTS_RUN_CASE(TEST_RESIZEABLE_resize_FAILURE_leaves_rb_untouched_w);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * helpers
 */

namespace {

typedef winstl::filesystem_traits<char>                     fs_traits_m_t;
typedef winstl::filesystem_traits<wchar_t>                  fs_traits_w_t;
typedef winstl::system_traits<char>                         traits_m_t;
typedef winstl::system_traits<wchar_t>                      traits_w_t;


/** Obtains the current process image path via GetModuleFileNameA. */
static
std::string
obtain_raw_current_process_path_m()
{
    stlsoft::auto_buffer<char>  buff(MAX_PATH);

    for (;;)
    {
        DWORD const n = ::GetModuleFileNameA(NULL, &buff[0], static_cast<DWORD>(buff.size()));

        if (0 == n)
        {
            return std::string();
        }

        if (n < buff.size())
        {
            return std::string(&buff[0], static_cast<size_t>(n));
        }

        if (!buff.resize(buff.size() * 2))
        {
            return std::string();
        }
    }
}

/** Obtains the current process image path via GetModuleFileNameW. */
static
std::wstring
obtain_raw_current_process_path_w()
{
    stlsoft::auto_buffer<wchar_t>   buff(MAX_PATH);

    for (;;)
    {
        DWORD const n = ::GetModuleFileNameW(NULL, &buff[0], static_cast<DWORD>(buff.size()));

        if (0 == n)
        {
            return std::wstring();
        }

        if (n < buff.size())
        {
            return std::wstring(&buff[0], static_cast<size_t>(n));
        }

        if (!buff.resize(buff.size() * 2))
        {
            return std::wstring();
        }
    }
}

template <typename C>
static
C*
invalid_file_pointer()
{
    return reinterpret_cast<C*>(static_cast<size_t>(-1));
}

/** Minimal resizeable buffer whose #resize() always fails. */
template <typename C>
struct fail_on_resize_buffer
{
    typedef C                                               value_type;

    std::vector<C>                                          storage;

    size_t size() const
    {
        return storage.size();
    }

    C& operator [](size_t i)
    {
        return storage[i];
    }

    C const& operator [](size_t i) const
    {
        return storage[i];
    }

    bool resize(size_t /* newSize */)
    {
        return false;
    }
};
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_size_QUERY_m()
{
    std::string const   expected = obtain_raw_current_process_path_m();

    XTESTS_REQUIRE(TEST_BOOLEAN_TRUE(!expected.empty()));

    char*               pFile   =   invalid_file_pointer<char>();
    size_t const        cch     =   traits_m_t::get_current_process_path(0, NULL, &pFile);

    /* Demand may exceed len+1 (WinSTL GetModuleFileName size protocol). */
    TEST_INT_GE(expected.size() + 1, cch);
    TEST_PTR_EQ(NULL, pFile);
}

static void TEST_size_QUERY_w()
{
    std::wstring const  expected = obtain_raw_current_process_path_w();

    XTESTS_REQUIRE(TEST_BOOLEAN_TRUE(!expected.empty()));

    wchar_t*            pFile   =   invalid_file_pointer<wchar_t>();
    size_t const        cch     =   traits_w_t::get_current_process_path(0, NULL, &pFile);

    TEST_INT_GE(expected.size() + 1, cch);
    TEST_PTR_EQ(NULL, pFile);
}

static void TEST_size_THEN_SUFFICIENT_m()
{
    std::string const   expected = obtain_raw_current_process_path_m();

    XTESTS_REQUIRE(TEST_BOOLEAN_TRUE(!expected.empty()));

    size_t const                len     =   expected.size();
    size_t const                need    =   traits_m_t::get_current_process_path(0, NULL, NULL);

    XTESTS_REQUIRE(TEST_INT_GE(len + 1, need));

    stlsoft::auto_buffer<char>  buff(need);
    char*                       pFile   =   invalid_file_pointer<char>();
    size_t const                cch     =   traits_m_t::get_current_process_path(buff.size(), &buff[0], &pFile);

    TEST_INT_EQ(len, cch);
    TEST_MS_EQ(expected.c_str(), &buff[0]);
    TEST_CHAR_EQ('\0', buff[len]);
}

static void TEST_size_THEN_SUFFICIENT_w()
{
    std::wstring const  expected = obtain_raw_current_process_path_w();

    XTESTS_REQUIRE(TEST_BOOLEAN_TRUE(!expected.empty()));

    size_t const                    len     =   expected.size();
    size_t const                    need    =   traits_w_t::get_current_process_path(0, NULL, NULL);

    XTESTS_REQUIRE(TEST_INT_GE(len + 1, need));

    stlsoft::auto_buffer<wchar_t>   buff(need);
    wchar_t*                        pFile   =   invalid_file_pointer<wchar_t>();
    size_t const                    cch     =   traits_w_t::get_current_process_path(buff.size(), &buff[0], &pFile);

    TEST_INT_EQ(len, cch);
    TEST_WS_EQ(expected.c_str(), &buff[0]);
    TEST_CHAR_EQ(L'\0', buff[len]);
}

static void TEST_EXCESS_SPACE_m()
{
    std::string const   expected = obtain_raw_current_process_path_m();

    XTESTS_REQUIRE(TEST_BOOLEAN_TRUE(!expected.empty()));

    size_t const                len = expected.size();
    stlsoft::auto_buffer<char>  buff(len + 64);

    ::memset(&buff[0], '~', buff.size());

    char*                       pFile   =   invalid_file_pointer<char>();
    size_t const                cch     =   traits_m_t::get_current_process_path(buff.size(), &buff[0], &pFile);

    TEST_INT_EQ(len, cch);
    TEST_MS_EQ(expected.c_str(), &buff[0]);
    TEST_CHAR_EQ('\0', buff[len]);
}

static void TEST_EXCESS_SPACE_w()
{
    std::wstring const  expected = obtain_raw_current_process_path_w();

    XTESTS_REQUIRE(TEST_BOOLEAN_TRUE(!expected.empty()));

    size_t const                    len = expected.size();
    stlsoft::auto_buffer<wchar_t>   buff(len + 64);

    for (size_t i = 0; i != buff.size(); ++i)
    {
        buff[i] = L'~';
    }

    wchar_t*                        pFile   =   invalid_file_pointer<wchar_t>();
    size_t const                    cch     =   traits_w_t::get_current_process_path(buff.size(), &buff[0], &pFile);

    TEST_INT_EQ(len, cch);
    TEST_WS_EQ(expected.c_str(), &buff[0]);
    TEST_CHAR_EQ(L'\0', buff[len]);
}

static void TEST_INSUFFICIENT_SPACE_m()
{
    std::string const   expected = obtain_raw_current_process_path_m();

    XTESTS_REQUIRE(TEST_BOOLEAN_TRUE(!expected.empty()));

    size_t const len = expected.size();

    {
        size_t const                cchBuff = len;
        stlsoft::auto_buffer<char>  buff(cchBuff);

        ::memset(&buff[0], '~', buff.size());

        char*                       pFile   =   invalid_file_pointer<char>();
        size_t const                cch     =   traits_m_t::get_current_process_path(buff.size(), &buff[0], &pFile);

        TEST_INT_GE(len + 1, cch);
        TEST_PTR_EQ(NULL, pFile);
        TEST_CHAR_EQ('\0', buff[cchBuff - 1]);
        TEST_MS_EQ_N(expected.c_str(), &buff[0], cchBuff - 1);
    }

    {
        char            buff[1] =   { '~' };
        char*           pFile   =   invalid_file_pointer<char>();
        size_t const    cch     =   traits_m_t::get_current_process_path(STLSOFT_NUM_ELEMENTS(buff), buff, &pFile);

        TEST_INT_GE(len + 1, cch);
        TEST_PTR_EQ(NULL, pFile);
        TEST_CHAR_EQ('\0', buff[0]);
    }
}

static void TEST_INSUFFICIENT_SPACE_w()
{
    std::wstring const  expected = obtain_raw_current_process_path_w();

    XTESTS_REQUIRE(TEST_BOOLEAN_TRUE(!expected.empty()));

    size_t const len = expected.size();

    {
        size_t const                    cchBuff = len;
        stlsoft::auto_buffer<wchar_t>   buff(cchBuff);

        for (size_t i = 0; i != buff.size(); ++i)
        {
            buff[i] = L'~';
        }

        wchar_t*                        pFile   =   invalid_file_pointer<wchar_t>();
        size_t const                    cch     =   traits_w_t::get_current_process_path(buff.size(), &buff[0], &pFile);

        TEST_INT_GE(len + 1, cch);
        TEST_PTR_EQ(NULL, pFile);
        TEST_CHAR_EQ(L'\0', buff[cchBuff - 1]);
        TEST_WS_EQ_N(expected.c_str(), &buff[0], cchBuff - 1);
    }

    {
        wchar_t         buff[1] =   { L'~' };
        wchar_t*        pFile   =   invalid_file_pointer<wchar_t>();
        size_t const    cch     =   traits_w_t::get_current_process_path(STLSOFT_NUM_ELEMENTS(buff), buff, &pFile);

        TEST_INT_GE(len + 1, cch);
        TEST_PTR_EQ(NULL, pFile);
        TEST_CHAR_EQ(L'\0', buff[0]);
    }
}

static void TEST_ppFile_NULL_ON_SUCCESS_m()
{
    std::string const   expected = obtain_raw_current_process_path_m();

    XTESTS_REQUIRE(TEST_BOOLEAN_TRUE(!expected.empty()));

    size_t const                need = traits_m_t::get_current_process_path(0, NULL, NULL);

    XTESTS_REQUIRE(TEST_INT_GE(expected.size() + 1, need));

    stlsoft::auto_buffer<char>  buff(need);
    size_t const                cch = traits_m_t::get_current_process_path(buff.size(), &buff[0], NULL);

    TEST_INT_EQ(expected.size(), cch);
    TEST_MS_EQ(expected.c_str(), &buff[0]);
}

static void TEST_ppFile_NULL_ON_SUCCESS_w()
{
    std::wstring const  expected = obtain_raw_current_process_path_w();

    XTESTS_REQUIRE(TEST_BOOLEAN_TRUE(!expected.empty()));

    size_t const                    need = traits_w_t::get_current_process_path(0, NULL, NULL);

    XTESTS_REQUIRE(TEST_INT_GE(expected.size() + 1, need));

    stlsoft::auto_buffer<wchar_t>   buff(need);
    size_t const                    cch = traits_w_t::get_current_process_path(buff.size(), &buff[0], NULL);

    TEST_INT_EQ(expected.size(), cch);
    TEST_WS_EQ(expected.c_str(), &buff[0]);
}

static void TEST_ppFile_separator_ON_SUCCESS_m()
{
    std::string const   expected = obtain_raw_current_process_path_m();

    XTESTS_REQUIRE(TEST_BOOLEAN_TRUE(!expected.empty()));

    size_t const                need = traits_m_t::get_current_process_path(0, NULL, NULL);

    XTESTS_REQUIRE(TEST_INT_GE(expected.size() + 1, need));

    stlsoft::auto_buffer<char>  buff(need);
    char*                       pFile   =   invalid_file_pointer<char>();
    size_t const                cch     =   traits_m_t::get_current_process_path(buff.size(), &buff[0], &pFile);

    TEST_INT_EQ(expected.size(), cch);
    TEST_MS_EQ(expected.c_str(), &buff[0]);

    char const* const expectedSep = fs_traits_m_t::find_last_path_name_separator(&buff[0]);

    TEST_PTR_EQ(expectedSep, pFile);

    if (NULL != pFile)
    {
        TEST_MS_EQ(expectedSep + 1, pFile + 1);
    }
}

static void TEST_ppFile_separator_ON_SUCCESS_w()
{
    std::wstring const  expected = obtain_raw_current_process_path_w();

    XTESTS_REQUIRE(TEST_BOOLEAN_TRUE(!expected.empty()));

    size_t const                    need = traits_w_t::get_current_process_path(0, NULL, NULL);

    XTESTS_REQUIRE(TEST_INT_GE(expected.size() + 1, need));

    stlsoft::auto_buffer<wchar_t>   buff(need);
    wchar_t*                        pFile   =   invalid_file_pointer<wchar_t>();
    size_t const                    cch     =   traits_w_t::get_current_process_path(buff.size(), &buff[0], &pFile);

    TEST_INT_EQ(expected.size(), cch);
    TEST_WS_EQ(expected.c_str(), &buff[0]);

    wchar_t const* const expectedSep = fs_traits_w_t::find_last_path_name_separator(&buff[0]);

    TEST_PTR_EQ(expectedSep, pFile);

    if (NULL != pFile)
    {
        TEST_WS_EQ(expectedSep + 1, pFile + 1);
    }
}

static void TEST_ppFile_NULL_WHEN_INSUFFICIENT_m()
{
    std::string const   expected = obtain_raw_current_process_path_m();

    XTESTS_REQUIRE(TEST_BOOLEAN_TRUE(!expected.empty()));

    size_t const                len = expected.size();
    stlsoft::auto_buffer<char>  buff(len);
    char*                       pFile   =   invalid_file_pointer<char>();
    size_t const                cch     =   traits_m_t::get_current_process_path(buff.size(), &buff[0], &pFile);

    TEST_INT_GE(len + 1, cch);
    TEST_PTR_EQ(NULL, pFile);
}

static void TEST_ppFile_NULL_WHEN_INSUFFICIENT_w()
{
    std::wstring const  expected = obtain_raw_current_process_path_w();

    XTESTS_REQUIRE(TEST_BOOLEAN_TRUE(!expected.empty()));

    size_t const                    len = expected.size();
    stlsoft::auto_buffer<wchar_t>   buff(len);
    wchar_t*                        pFile   =   invalid_file_pointer<wchar_t>();
    size_t const                    cch     =   traits_w_t::get_current_process_path(buff.size(), &buff[0], &pFile);

    TEST_INT_GE(len + 1, cch);
    TEST_PTR_EQ(NULL, pFile);
}

static void TEST_RESIZEABLE_auto_buffer_SUCCESS_m()
{
    std::string const   expected = obtain_raw_current_process_path_m();

    XTESTS_REQUIRE(TEST_BOOLEAN_TRUE(!expected.empty()));

    stlsoft::auto_buffer<char>  rb(0);
    size_t const                cch = traits_m_t::get_current_process_path(rb);

    TEST_INT_EQ(expected.size(), cch);
    TEST_INT_GE(expected.size() + 1, rb.size());
    TEST_MS_EQ(expected.c_str(), &rb[0]);
}

static void TEST_RESIZEABLE_auto_buffer_SUCCESS_w()
{
    std::wstring const  expected = obtain_raw_current_process_path_w();

    XTESTS_REQUIRE(TEST_BOOLEAN_TRUE(!expected.empty()));

    stlsoft::auto_buffer<wchar_t>   rb(0);
    size_t const                    cch = traits_w_t::get_current_process_path(rb);

    TEST_INT_EQ(expected.size(), cch);
    TEST_INT_GE(expected.size() + 1, rb.size());
    TEST_WS_EQ(expected.c_str(), &rb[0]);
}

static void TEST_RESIZEABLE_vector_SUCCESS_m()
{
    std::string const   expected = obtain_raw_current_process_path_m();

    XTESTS_REQUIRE(TEST_BOOLEAN_TRUE(!expected.empty()));

    std::vector<char>   rb;
    size_t const        cch = traits_m_t::get_current_process_path(rb);

    TEST_INT_EQ(expected.size(), cch);
    TEST_INT_GE(expected.size() + 1, rb.size());
    TEST_MS_EQ(expected.c_str(), &rb[0]);
}

static void TEST_RESIZEABLE_vector_SUCCESS_w()
{
    std::wstring const  expected = obtain_raw_current_process_path_w();

    XTESTS_REQUIRE(TEST_BOOLEAN_TRUE(!expected.empty()));

    std::vector<wchar_t>    rb;
    size_t const            cch = traits_w_t::get_current_process_path(rb);

    TEST_INT_EQ(expected.size(), cch);
    TEST_INT_GE(expected.size() + 1, rb.size());
    TEST_WS_EQ(expected.c_str(), &rb[0]);
}

static void TEST_RESIZEABLE_ppFile_NULL_m()
{
    std::string const   expected = obtain_raw_current_process_path_m();

    XTESTS_REQUIRE(TEST_BOOLEAN_TRUE(!expected.empty()));

    stlsoft::auto_buffer<char>  rb(0);
    size_t const                cch = traits_m_t::get_current_process_path(rb, NULL);

    TEST_INT_EQ(expected.size(), cch);
    TEST_MS_EQ(expected.c_str(), &rb[0]);
}

static void TEST_RESIZEABLE_ppFile_NULL_w()
{
    std::wstring const  expected = obtain_raw_current_process_path_w();

    XTESTS_REQUIRE(TEST_BOOLEAN_TRUE(!expected.empty()));

    stlsoft::auto_buffer<wchar_t>   rb(0);
    size_t const                    cch = traits_w_t::get_current_process_path(rb, NULL);

    TEST_INT_EQ(expected.size(), cch);
    TEST_WS_EQ(expected.c_str(), &rb[0]);
}

static void TEST_RESIZEABLE_ppFile_separator_m()
{
    std::string const   expected = obtain_raw_current_process_path_m();

    XTESTS_REQUIRE(TEST_BOOLEAN_TRUE(!expected.empty()));

    stlsoft::auto_buffer<char>  rb(0);
    char*                       pFile   =   invalid_file_pointer<char>();
    size_t const                cch     =   traits_m_t::get_current_process_path(rb, &pFile);

    TEST_INT_EQ(expected.size(), cch);
    TEST_MS_EQ(expected.c_str(), &rb[0]);

    char const* const expectedSep = fs_traits_m_t::find_last_path_name_separator(&rb[0]);

    TEST_PTR_EQ(expectedSep, pFile);

    if (NULL != pFile)
    {
        TEST_MS_EQ(expectedSep + 1, pFile + 1);
    }
}

static void TEST_RESIZEABLE_ppFile_separator_w()
{
    std::wstring const  expected = obtain_raw_current_process_path_w();

    XTESTS_REQUIRE(TEST_BOOLEAN_TRUE(!expected.empty()));

    stlsoft::auto_buffer<wchar_t>   rb(0);
    wchar_t*                        pFile   =   invalid_file_pointer<wchar_t>();
    size_t const                    cch     =   traits_w_t::get_current_process_path(rb, &pFile);

    TEST_INT_EQ(expected.size(), cch);
    TEST_WS_EQ(expected.c_str(), &rb[0]);

    wchar_t const* const expectedSep = fs_traits_w_t::find_last_path_name_separator(&rb[0]);

    TEST_PTR_EQ(expectedSep, pFile);

    if (NULL != pFile)
    {
        TEST_WS_EQ(expectedSep + 1, pFile + 1);
    }
}

static void TEST_RESIZEABLE_resize_FAILURE_leaves_rb_untouched_m()
{
    fail_on_resize_buffer<char> rb;

    rb.storage.assign(4, 'X');

    size_t const    priorSize   =   rb.size();
    DWORD const     priorError  =   ::GetLastError();

    ::SetLastError(ERROR_SUCCESS);

    size_t const    cch = traits_m_t::get_current_process_path(rb);

    TEST_INT_EQ(0, cch);
    TEST_INT_EQ(ERROR_OUTOFMEMORY, ::GetLastError());
    TEST_INT_EQ(priorSize, rb.size());
    TEST_CHAR_EQ('X', rb.storage[0]);
    TEST_CHAR_EQ('X', rb.storage[3]);

    ::SetLastError(priorError);
}

static void TEST_RESIZEABLE_resize_FAILURE_leaves_rb_untouched_w()
{
    fail_on_resize_buffer<wchar_t>  rb;

    rb.storage.assign(4, L'X');

    size_t const    priorSize   =   rb.size();
    DWORD const     priorError  =   ::GetLastError();

    ::SetLastError(ERROR_SUCCESS);

    size_t const    cch = traits_w_t::get_current_process_path(rb);

    TEST_INT_EQ(0, cch);
    TEST_INT_EQ(ERROR_OUTOFMEMORY, ::GetLastError());
    TEST_INT_EQ(priorSize, rb.size());
    TEST_BOOLEAN_TRUE(L'X' == rb.storage[0]);
    TEST_BOOLEAN_TRUE(L'X' == rb.storage[3]);

    ::SetLastError(priorError);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

