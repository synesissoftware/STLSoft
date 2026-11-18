/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/stlsoft/string/string_tokeniser/entry.cpp
 *
 * Purpose: Unit tests for stlsoft::string_tokeniser.
 *
 * Created: 9th August 2026
 * Updated: 18th November 2026
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/string/simple_string.hpp>
#include <stlsoft/string/string_tokeniser.hpp>
#include <stlsoft/string/string_view.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>

#include <iterator>
#include <string>
#include <vector>

#include <stddef.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_char_preserve_blanks(void);
    static void TEST_char_skip_blanks(void);
    static void TEST_constructors(void);
    static void TEST_documented_examples(void);
    static void TEST_empty_input(void);
    static void TEST_ignore_blanks_alias(void);
    static void TEST_iterators(void);
    static void TEST_string_delimiter_preserve_blanks(void);
    static void TEST_string_delimiter_skip_blanks(void);
    static void TEST_value_type_string_view(void);
    static void TEST_wchar_t(void);
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
        XTESTS_RUN_CASE(TEST_char_preserve_blanks);
        XTESTS_RUN_CASE(TEST_char_skip_blanks);
        XTESTS_RUN_CASE(TEST_constructors);
        XTESTS_RUN_CASE(TEST_documented_examples);
        XTESTS_RUN_CASE(TEST_empty_input);
        XTESTS_RUN_CASE(TEST_ignore_blanks_alias);
        XTESTS_RUN_CASE(TEST_iterators);
        XTESTS_RUN_CASE(TEST_string_delimiter_preserve_blanks);
        XTESTS_RUN_CASE(TEST_string_delimiter_skip_blanks);
        XTESTS_RUN_CASE(TEST_value_type_string_view);
        XTESTS_RUN_CASE(TEST_wchar_t);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

typedef std::string                                             string_t;
typedef std::wstring                                            wstring_t;
typedef stlsoft::string_tokeniser<
    string_t
,   char
>                                                               skip_char_tokeniser_t;
typedef stlsoft::string_tokeniser<
    string_t
,   char
,   stlsoft::skip_blank_tokens<false>
>                                                               keep_char_tokeniser_t;
typedef stlsoft::string_tokeniser<
    string_t
,   string_t
>                                                               skip_string_tokeniser_t;
typedef stlsoft::string_tokeniser<
    string_t
,   string_t
,   stlsoft::skip_blank_tokens<false>
>                                                               keep_string_tokeniser_t;


/* A trailing delimiter does not yield a final empty token: N trailing
 * delimiters produce N - 1 empty tokens. That is the contract locked in
 * by these tests (and by the examples in string_tokeniser.hpp).
 *
 * A tail that is a proper prefix of a multi-character delimiter is not
 * exercised: the comparator compares delim.length() characters without
 * consulting the end iterator.
 */

#define EXPECT_CHAR_TOKENS_(tokens, ...) \
    \
    do \
    { \
        char const* const expected_[] = { __VA_ARGS__ }; \
        size_t const n_expected_ = sizeof(expected_) / sizeof(expected_[0]); \
        std::vector<string_t> actual_; \
        \
        actual_.assign((tokens).begin(), (tokens).end()); \
        \
        TEST_INT_EQ(static_cast<int>(n_expected_), static_cast<int>(actual_.size())); \
        \
        { for (size_t i_ = 0; i_ != n_expected_ && i_ != actual_.size(); ++i_) \
        { \
            TEST_MS_EQ(expected_[i_], actual_[i_].c_str()); \
        }} \
    } while (0)

#define EXPECT_WIDE_TOKENS_(tokens, ...) \
    \
    do \
    { \
        wchar_t const* const expected_[] = { __VA_ARGS__ }; \
        size_t const n_expected_ = sizeof(expected_) / sizeof(expected_[0]); \
        std::vector<wstring_t> actual_; \
        \
        actual_.assign((tokens).begin(), (tokens).end()); \
        \
        TEST_INT_EQ(static_cast<int>(n_expected_), static_cast<int>(actual_.size())); \
        \
        { for (size_t i_ = 0; i_ != n_expected_ && i_ != actual_.size(); ++i_) \
        { \
            TEST_WS_EQ(expected_[i_], actual_[i_].c_str()); \
        }} \
    } while (0)


static void TEST_empty_input(void)
{
    {
        skip_char_tokeniser_t const tokens("", ':');

        TEST_BOOLEAN_EQ(true, tokens.empty());
        TEST_BOOLEAN_EQ(true, tokens.begin() == tokens.end());
    }

    {
        keep_char_tokeniser_t const tokens("", ':');

        TEST_BOOLEAN_EQ(true, tokens.empty());
        TEST_BOOLEAN_EQ(true, tokens.begin() == tokens.end());
    }

    {
        skip_string_tokeniser_t const tokens("", string_t("\r\n"));

        TEST_BOOLEAN_EQ(true, tokens.empty());
    }
}

static void TEST_char_skip_blanks(void)
{
    {
        skip_char_tokeniser_t const tokens("abc", ':');

        EXPECT_CHAR_TOKENS_(tokens, "abc");
        TEST_BOOLEAN_EQ(false, tokens.empty());
    }

    {
        skip_char_tokeniser_t const tokens("a:b:c", ':');

        EXPECT_CHAR_TOKENS_(tokens, "a", "b", "c");
    }

    {
        skip_char_tokeniser_t const tokens(":a::b:c::", ':');

        EXPECT_CHAR_TOKENS_(tokens, "a", "b", "c");
    }

    {
        skip_char_tokeniser_t const tokens("::::", ':');

        TEST_BOOLEAN_EQ(true, tokens.empty());
    }

    {
        skip_char_tokeniser_t const tokens("a:b:", ':');

        EXPECT_CHAR_TOKENS_(tokens, "a", "b");
    }
}

static void TEST_char_preserve_blanks(void)
{
    {
        keep_char_tokeniser_t const tokens("a,b", ',');

        EXPECT_CHAR_TOKENS_(tokens, "a", "b");
    }

    {
        keep_char_tokeniser_t const tokens("a,,b", ',');

        EXPECT_CHAR_TOKENS_(tokens, "a", "", "b");
    }

    {
        keep_char_tokeniser_t const tokens(",a", ',');

        EXPECT_CHAR_TOKENS_(tokens, "", "a");
    }

    {
        /* One trailing delimiter: the final empty token is absent. */
        keep_char_tokeniser_t const tokens("a,", ',');

        EXPECT_CHAR_TOKENS_(tokens, "a");
    }

    {
        /* Two trailing delimiters: one empty token, between them. */
        keep_char_tokeniser_t const tokens("a,,", ',');

        EXPECT_CHAR_TOKENS_(tokens, "a", "");
    }

    {
        keep_char_tokeniser_t const tokens(",", ',');

        EXPECT_CHAR_TOKENS_(tokens, "");
    }

    {
        keep_char_tokeniser_t const tokens(",,,", ',');

        EXPECT_CHAR_TOKENS_(tokens, "", "", "");
    }

    {
        keep_char_tokeniser_t const tokens("abc", ',');

        EXPECT_CHAR_TOKENS_(tokens, "abc");
    }
}

static void TEST_documented_examples(void)
{
    {
        skip_char_tokeniser_t const tokens(":abc::def:ghi:jkl::::::::::", ':');

        EXPECT_CHAR_TOKENS_(tokens, "abc", "def", "ghi", "jkl");
    }

    {
        /* Header sample. ostream would print ",abc,,def,ghi,jkl,,,,,,,,,,"
         * which is these 15 tokens, each followed by a comma.
         */
        keep_char_tokeniser_t const tokens(":abc::def:ghi:jkl::::::::::", ':');

        EXPECT_CHAR_TOKENS_(
            tokens
        ,   ""
        ,   "abc"
        ,   ""
        ,   "def"
        ,   "ghi"
        ,   "jkl"
        ,   ""
        ,   ""
        ,   ""
        ,   ""
        ,   ""
        ,   ""
        ,   ""
        ,   ""
        ,   ""
        );
    }

    {
        skip_string_tokeniser_t const tokens(
            "\r\nabc\r\n\r\ndef\r\nghi\r\njkl\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n"
        ,   string_t("\r\n")
        );

        EXPECT_CHAR_TOKENS_(tokens, "abc", "def", "ghi", "jkl");
    }
}

static void TEST_string_delimiter_skip_blanks(void)
{
    string_t const delim("XY");

    {
        skip_string_tokeniser_t const tokens("XYabcXYdefXY", delim);

        EXPECT_CHAR_TOKENS_(tokens, "abc", "def");
    }

    {
        skip_string_tokeniser_t const tokens("abc", delim);

        EXPECT_CHAR_TOKENS_(tokens, "abc");
    }

    {
        /* Full delimiter at the end, so the compare stays in range. */
        skip_string_tokeniser_t const tokens("abcXY", delim);

        EXPECT_CHAR_TOKENS_(tokens, "abc");
    }

    {
        /* Second delimiter character mismatches, still in range. */
        skip_string_tokeniser_t const tokens("abXZc", delim);

        EXPECT_CHAR_TOKENS_(tokens, "abXZc");
    }

    {
        skip_string_tokeniser_t const tokens("XYXY", delim);

        TEST_BOOLEAN_EQ(true, tokens.empty());
    }

    {
        /* Delimiter longer than the string; first character differs. */
        skip_string_tokeniser_t const tokens("hello", string_t("\r\n"));

        EXPECT_CHAR_TOKENS_(tokens, "hello");
    }
}

static void TEST_string_delimiter_preserve_blanks(void)
{
    string_t const delim("::");

    {
        keep_string_tokeniser_t const tokens("::abc", delim);

        EXPECT_CHAR_TOKENS_(tokens, "", "abc");
    }

    {
        keep_string_tokeniser_t const tokens("abc::def", delim);

        EXPECT_CHAR_TOKENS_(tokens, "abc", "def");
    }

    {
        keep_string_tokeniser_t const tokens("abc::::def", delim);

        EXPECT_CHAR_TOKENS_(tokens, "abc", "", "def");
    }

    {
        keep_string_tokeniser_t const tokens("a::", delim);

        EXPECT_CHAR_TOKENS_(tokens, "a");
    }

    {
        keep_string_tokeniser_t const tokens("a::::", delim);

        EXPECT_CHAR_TOKENS_(tokens, "a", "");
    }

    {
        keep_string_tokeniser_t const tokens("::", delim);

        EXPECT_CHAR_TOKENS_(tokens, "");
    }

    {
        keep_string_tokeniser_t const tokens("xxAxx", string_t("xx"));

        EXPECT_CHAR_TOKENS_(tokens, "", "A");
    }

    {
        keep_string_tokeniser_t const tokens("aaaa", string_t("aa"));

        EXPECT_CHAR_TOKENS_(tokens, "", "");
    }
}

static void TEST_constructors(void)
{
    {
        string_t        source("a:b:c");
        skip_char_tokeniser_t const tokens(source, ':');

        source = "mutated";

        EXPECT_CHAR_TOKENS_(tokens, "a", "b", "c");
    }

    {
        char const data[] = { 'a', '\0', 'b', ':', 'c' };
        skip_char_tokeniser_t const tokens(data, 5u, ':');
        std::vector<string_t> actual;

        actual.assign(tokens.begin(), tokens.end());

        TEST_INT_EQ(2, static_cast<int>(actual.size()));

        if (2 == actual.size())
        {
            TEST_INT_EQ(3, static_cast<int>(actual[0].size()));
            TEST_CHAR_EQ('a', actual[0][0]);
            TEST_CHAR_EQ('\0', actual[0][1]);
            TEST_CHAR_EQ('b', actual[0][2]);
            TEST_MS_EQ("c", actual[1].c_str());
        }
    }

    {
        char const source[] = "x:yy:z";
        skip_char_tokeniser_t const tokens(source + 0, source + 6, ':');

        EXPECT_CHAR_TOKENS_(tokens, "x", "yy", "z");
    }

    {
        stlsoft::basic_simple_string<char> const shimmed("p:q");
        skip_char_tokeniser_t const tokens(shimmed, ':');

        EXPECT_CHAR_TOKENS_(tokens, "p", "q");
    }

    {
        skip_char_tokeniser_t const original("a:b", ':');
        skip_char_tokeniser_t const copy(original);

        EXPECT_CHAR_TOKENS_(copy, "a", "b");
        EXPECT_CHAR_TOKENS_(original, "a", "b");
    }
}

static void TEST_iterators(void)
{
    skip_char_tokeniser_t const tokens("a:b:c", ':');
    skip_char_tokeniser_t::const_iterator const begin = tokens.begin();
    skip_char_tokeniser_t::const_iterator const end = tokens.end();
    skip_char_tokeniser_t::const_iterator it = begin;
    skip_char_tokeniser_t::const_iterator copy(begin);

    TEST_BOOLEAN_EQ(false, begin == end);
    TEST_BOOLEAN_EQ(true, begin != end);
    TEST_MS_EQ("a", (*it).c_str());

    copy = it;
    ++it;

    TEST_MS_EQ("b", (*it).c_str());
    TEST_MS_EQ("a", (*copy).c_str());
    TEST_BOOLEAN_EQ(false, it == copy);

    {
        skip_char_tokeniser_t::const_iterator post = it++;

        TEST_MS_EQ("b", (*post).c_str());
        TEST_MS_EQ("c", (*it).c_str());
    }

    ++it;

    TEST_BOOLEAN_EQ(true, it == end);

    {
        std::vector<string_t> first;
        std::vector<string_t> second;

        first.assign(tokens.begin(), tokens.end());
        second.assign(tokens.begin(), tokens.end());

        TEST_INT_EQ(static_cast<int>(first.size()), static_cast<int>(second.size()));

        { for (size_t i = 0; i != first.size() && i != second.size(); ++i)
        {
            TEST_MS_EQ(first[i].c_str(), second[i].c_str());
        }}

        TEST_INT_EQ(3, static_cast<int>(std::distance(tokens.begin(), tokens.end())));
    }
}

static void TEST_ignore_blanks_alias(void)
{
    typedef stlsoft::string_tokeniser<
        string_t
    ,   char
    ,   stlsoft::string_tokeniser_ignore_blanks<true>
    >                                                       skip_t;
    typedef stlsoft::string_tokeniser<
        string_t
    ,   char
    ,   stlsoft::string_tokeniser_ignore_blanks<false>
    >                                                       keep_t;

    {
        skip_t const tokens(":a::b:", ':');

        EXPECT_CHAR_TOKENS_(tokens, "a", "b");
    }

    {
        keep_t const tokens("a,,", ',');

        EXPECT_CHAR_TOKENS_(tokens, "a", "");
    }
}

static void TEST_value_type_string_view(void)
{
    typedef stlsoft::basic_simple_string<char>              string_t;
    typedef stlsoft::basic_string_view<char>                view_t;
    typedef stlsoft::string_tokeniser<
        string_t
    ,   char
    ,   stlsoft::skip_blank_tokens<true>
    ,   view_t
    >                                                       tokeniser_t;

    string_t const source("a:bb:c");
    tokeniser_t const tokens(source, ':');
    tokeniser_t::const_iterator it = tokens.begin();
    view_t const first = *it;

    TEST_INT_EQ(1, static_cast<int>(first.size()));
    TEST_CHAR_EQ('a', first[0]);

    ++it;

    {
        view_t const second = *it;

        TEST_INT_EQ(2, static_cast<int>(second.size()));
        TEST_CHAR_EQ('b', second[0]);
        TEST_CHAR_EQ('b', second[1]);
    }

    ++it;

    {
        view_t const third = *it;

        TEST_INT_EQ(1, static_cast<int>(third.size()));
        TEST_CHAR_EQ('c', third[0]);
    }

    ++it;

    TEST_BOOLEAN_EQ(true, it == tokens.end());

    /* The first view still refers into the tokeniser's copy. */
    TEST_INT_EQ(1, static_cast<int>(first.size()));
    TEST_CHAR_EQ('a', first[0]);
}

static void TEST_wchar_t(void)
{
    typedef stlsoft::string_tokeniser<
        wstring_t
    ,   wchar_t
    >                                                       skip_t;
    typedef stlsoft::string_tokeniser<
        wstring_t
    ,   wchar_t
    ,   stlsoft::skip_blank_tokens<false>
    >                                                       keep_t;

    {
        skip_t const tokens(L"|abc||def|ghi|jkl||||||||||", L'|');

        EXPECT_WIDE_TOKENS_(tokens, L"abc", L"def", L"ghi", L"jkl");
    }

    {
        keep_t const tokens(L"a|", L'|');

        EXPECT_WIDE_TOKENS_(tokens, L"a");
    }

    {
        keep_t const tokens(L"|a||b", L'|');

        EXPECT_WIDE_TOKENS_(tokens, L"", L"a", L"", L"b");
    }
}
} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */

