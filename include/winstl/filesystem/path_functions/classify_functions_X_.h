/* /////////////////////////////////////////////////////////////////////////
 * File:    winstl/filesystem/path_functions/classify_functions_X_.h
 *
 * Purpose: Path classification functions char-X implementation
 *          (R11 long-path "\\?\" / "\\?\UNC\"; R12 device "\\.\").
 *
 * Created: 28th November 2020
 * Updated: 20th October 2026
 *
 * Home:    http://stlsoft.org/
 *
 * Copyright (c) 2020-2026, Matthew Wilson and Synesis Information Systems
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * - Neither the name(s) of Matthew Wilson and Synesis Information Systems
 *   nor the names of any contributors may be used to endorse or promote
 *   products derived from this software without specific prior written
 *   permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ////////////////////////////////////////////////////////////////////// */


/* STLSOFT:FILE_EXCEPTED */

#ifndef WINSTL_INCL_WINSTL_FILESYSTEM_H_PATH_CLASSIFY_FUNCTIONS
# error This file must be included from winstl/filesystem/path_classify_functions.h
#endif

#ifndef WINSTL_C_PATH_CLASSIFY_IMPL_stlsoft_C_string_slice_X_t_
# error WINSTL_C_PATH_CLASSIFY_IMPL_stlsoft_C_string_slice_X_t_
#endif

#ifndef winstl_C_path_classification_results_X_t_
# error winstl_C_path_classification_results_X_t_
#endif

#ifndef WINSTL_C_PATH_CLASSIFY_IMPL_stlsoft_C_strnchr_X_
# error WINSTL_C_PATH_CLASSIFY_IMPL_stlsoft_C_strnchr_X_
#endif

#ifndef WINSTL_C_PATH_CLASSIFY_IMPL_stlsoft_C_strnpbrkn_X_
# error WINSTL_C_PATH_CLASSIFY_IMPL_stlsoft_C_strnpbrkn_X_
#endif

#ifndef WINSTL_C_PATH_CLASSIFY_IMPL_stlsoft_C_strnstrn_X_
# error WINSTL_C_PATH_CLASSIFY_IMPL_stlsoft_C_strnstrn_X_
#endif

#ifndef WINSTL_C_PATH_CLASSIFY_IMPL_char_t_
# error WINSTL_C_PATH_CLASSIFY_IMPL_char_t_ must be defined
#endif

#ifndef winstl_C_path_classify_alwaysInvalidChars_X_
# error winstl_C_path_classify_alwaysInvalidChars_X_ must be defined
#endif

#ifndef winstl_C_path_classify_find_UNC_server_and_share_X_
# error winstl_C_path_classify_find_UNC_server_and_share_X_ must be defined
#endif

#ifndef winstl_C_path_classify_root_X_
# error winstl_C_path_classify_root_X_ must be defined
#endif

#ifndef winstl_C_path_classify_impl_X_
# error winstl_C_path_classify_impl_X_ must be defined
#endif


/* /////////////////////////////////////////////////////////////////////////
 * implementation
 */

STLSOFT_INLINE
WINSTL_C_PATH_CLASSIFY_IMPL_stlsoft_C_string_slice_X_t_
winstl_C_path_classify_alwaysInvalidChars_X_()
{
    typedef WINSTL_C_PATH_CLASSIFY_IMPL_char_t_             char_t;

    static char_t s_invalidCards[] =
    {
        '<'
    ,   '>'
    ,   '|'
    ,   '?'
    ,   '*'
    ,   '"'
    ,   '\0'
    };

    WINSTL_C_PATH_CLASSIFY_IMPL_stlsoft_C_string_slice_X_t_  r = { STLSOFT_NUM_ELEMENTS(s_invalidCards), s_invalidCards };

    return r;
}

/*
 * Parse a UNC path body (characters after the leading "\\\\", or after
 * "\\\\?\\UNC\\").
 *
 * \param s Points to the first character of the potential server name
 *
 * \retval 0 Host and share are both nonempty. *ppServer / *ppShare point at
 *   the first character of each. *ppDir0 points at the separator before any
 *   further path (trailing sep or directory), or is null when the input ends
 *   exactly at the share (complete root with no trailing separator).
 * \retval 1 Incomplete or malformed (empty host/share, bare ":", etc.)
 */
STLSOFT_INLINE
int
winstl_C_path_classify_find_UNC_server_and_share_X_(
    WINSTL_C_PATH_CLASSIFY_IMPL_char_t_ const*  s
,   size_t                                      cch
,   WINSTL_C_PATH_CLASSIFY_IMPL_char_t_ const** ppServer
,   WINSTL_C_PATH_CLASSIFY_IMPL_char_t_ const** ppShare
,   WINSTL_C_PATH_CLASSIFY_IMPL_char_t_ const** ppDir0
)
{
    typedef WINSTL_C_PATH_CLASSIFY_IMPL_char_t_             char_t;

    char_t const*   p;
    size_t          rem;

    WINSTL_ASSERT(ss_nullptr_k != ppServer);
    WINSTL_ASSERT(ss_nullptr_k != ppShare);
    WINSTL_ASSERT(ss_nullptr_k != ppDir0);

    *ppServer   =   ss_nullptr_k;
    *ppShare    =   ss_nullptr_k;
    *ppDir0     =   ss_nullptr_k;

    if (0 == cch ||
        '\\' == *s ||
        '/' == *s)
    {
        /* Empty server (e.g. "\\\\" body or "\\\\\\share"). */
        return 1;
    }

    *ppServer = s;
    p         = s;
    rem       = cch;

    /* Server name: ended only by '\\' (not '/'); ':' is not a UNC host char. */
    for (; 0 != rem; ++p, --rem)
    {
        char_t const ch = *p;

        if (':' == ch)
        {
            return 1;
        }
        else
        if ('\\' == ch)
        {
            break;
        }
    }

    if (0 == rem ||
        p == *ppServer)
    {
        /* No share separator, or empty server. */
        return 1;
    }

    /* p at '\\' after server; advance into share. */
    ++p;
    --rem;

    if (0 == rem ||
        '\\' == *p ||
        '/' == *p)
    {
        /* Empty share (e.g. "\\\\svr\\" or "\\\\svr\\"). */
        return 1;
    }

    *ppShare = p;

    /* Share name: '\\' or '/' begins the directory / trailing-sep. */
    for (; 0 != rem; ++p, --rem)
    {
        char_t const ch = *p;

        if (':' == ch)
        {
            return 1;
        }
        else
        if ('\\' == ch ||
            '/' == ch)
        {
            *ppDir0 = p;

            return 0;
        }
    }

    /* Input ends at share — complete UNC root without trailing separator. */
    return 0;
}

/*
 * R11: detect "\\?\UNC\" (or "\\?\unc\", etc.). The "UNC" token is matched
 * ASCII-case-insensitively; the surrounding backslashes and '?' are exact.
 *
 * \retval 0 Not a long-path UNC prefix
 * \retval 1 Prefix present (caller may parse host/share from s + 8)
 */
STLSOFT_INLINE
int
winstl_C_path_classify_is_long_UNC_prefix_X_(
    WINSTL_C_PATH_CLASSIFY_IMPL_char_t_ const*  s
,   size_t                                      cch
)
{
    typedef WINSTL_C_PATH_CLASSIFY_IMPL_char_t_             char_t;

    char_t  u;
    char_t  n;
    char_t  c;

    if (cch < 8 ||
        '\\' != s[0] ||
        '\\' != s[1] ||
        '?' != s[2] ||
        '\\' != s[3] ||
        '\\' != s[7])
    {
        return 0;
    }

    u = s[4];
    n = s[5];
    c = s[6];

    if (u >= 'a' && u <= 'z')
    {
        u = (char_t)('A' + (u - 'a'));
    }
    if (n >= 'a' && n <= 'z')
    {
        n = (char_t)('A' + (n - 'a'));
    }
    if (c >= 'a' && c <= 'z')
    {
        c = (char_t)('A' + (c - 'a'));
    }

    return ('U' == u && 'N' == n && 'C' == c) ? 1 : 0;
}

STLSOFT_INLINE
winstl_C_path_classification_t
winstl_C_path_classify_root_X_(
    WINSTL_C_PATH_CLASSIFY_IMPL_char_t_ const*  s0
,   size_t                                      cch0
,   int                                         parseFlags
,   winstl_C_path_classification_results_X_t_*  results
,   WINSTL_C_PATH_CLASSIFY_IMPL_char_t_ const** ppS1
,   size_t*                                     pCch1
,   size_t*                                     pCchPrefix
,   int*                                        pIsLongPathPrefixed
)
{
    typedef WINSTL_C_PATH_CLASSIFY_IMPL_char_t_             char_t;

    WINSTL_ASSERT(ss_nullptr_k != s0);
    WINSTL_ASSERT(0 != cch0);

    WINSTL_MESSAGE_ASSERT("unrecognised parsing flags", 0 == (~WINSTL_PATH_CLASSIFY_F_MASK_ & parseFlags));

    WINSTL_ASSERT(ss_nullptr_k != results);

    WINSTL_ASSERT(ss_nullptr_k != ppS1);
    WINSTL_ASSERT(ss_nullptr_k != pCch1);

    WINSTL_ASSERT(ss_nullptr_k != pCchPrefix);

    WINSTL_ASSERT(ss_nullptr_k != pIsLongPathPrefixed);


    STLSOFT_SUPPRESS_UNUSED(parseFlags);


    *ppS1       =   s0;
    *pCch1      =   cch0;

    *pCchPrefix             =   0;

    *pIsLongPathPrefixed    =   0;

    if ('/' == s0[0])
    {
        /* "/" */

        return winstl_C_PathType_SlashRooted;
    }

    if ('~' == s0[0])
    {
        if (0 != (WINSTL_PATH_CLASSIFY_F_RECOGNISETILDEHOME & parseFlags))
        {
            if (1 == cch0)
            {
                *ppS1       =   s0 + 1;
                *pCch1      =   cch0 - 1;

                return winstl_C_PathType_HomeRooted;
            }
            else
            switch (s0[1])
            {
            case '\\':
            case '/':

                *ppS1       =   s0 + 1;
                *pCch1      =   cch0 - 1;

                return winstl_C_PathType_HomeRooted;
            }
        }
    }

    if ('\\' == s0[0])
    {
        if (1 == cch0)
        {
            /* "\" */

            return winstl_C_PathType_SlashRooted;
        }
        else
        {
            if ('\\' == s0[1])
            {
                /* potentially a UNC or long-path or device
                 *
                 * shortest possibilities:
                 *
                 * - \\.\A:             (6)
                 * - \\?\/              (5)
                 * - \\v\h\             (6)
                 * - \\v\h              (5)
                 * - \\?\v\h\           (8)
                 * - \\?\v\h            (7)
                 * - \\?\UNC\v\h\       (12)
                 */

                if (cch0 >= 5)
                {
                    char_t const*   server  =   ss_nullptr_k;
                    char_t const*   share   =   ss_nullptr_k;
                    char_t const*   dir0    =   ss_nullptr_k;

                    if ('\\' == s0[3])
                    {
                        /*
                         * Long-path / device namespaces (order matters):
                         * 1. "\\?\UNC\" → extended UNC (R11);
                         * 2. "\\?\" → strip; drive only, else Invalid (R11);
                         * 3. "\\.\" → device namespace, unsupported → Invalid (R12);
                         * 4. else → regular UNC / invalid.
                         */
                        if (0 != winstl_C_path_classify_is_long_UNC_prefix_X_(s0, cch0))
                        {
                            *pIsLongPathPrefixed = 1;

                            if (0 != winstl_C_path_classify_find_UNC_server_and_share_X_(s0 + 8, cch0 - 8, &server, &share, &dir0))
                            {
                                return winstl_C_PathType_UncIncomplete;
                            }
                            else
                            {
                                *pCchPrefix = 8;
                            }
                        }
                        else
                        if ('?' == s0[2])
                        {
                            /* "\\?\" but not "\\?\UNC\" — drive or unsupported. */
                            *pIsLongPathPrefixed = 1;

                            s0      +=  4;
                            cch0    -=  4;

                            *pCchPrefix = 4;

                            goto try_detect_drive;
                        }
                        else
                        if ('.' == s0[2])
                        {
                            /* R12: "\\.\" device / pipe namespace — not classified. */
                            results->firstInvalid.len   =   1;
                            results->firstInvalid.ptr   =   s0 + 2;

                            return winstl_C_PathType_Invalid;
                        }
                        else
                        {
                            if (WINSTL_C_PATH_CLASSIFY_IMPL_stlsoft_C_isdriveletter_X_(s0[2]))
                            {
                                /* potentially a UNC server with 1-character name */

                                goto maybe_regular_UNC;
                            }
                            else
                            {
                                results->firstInvalid.len = 1;
                                results->firstInvalid.ptr = s0 + 2;

                                return winstl_C_PathType_Invalid;
                            }
                        }
                    }
                    else
                    {
maybe_regular_UNC:
                        if (0 != winstl_C_path_classify_find_UNC_server_and_share_X_(s0 + 2, cch0 - 2, &server, &share, &dir0))
                        {
                            return winstl_C_PathType_UncIncomplete;
                        }
                        else
                        {
                            *pCchPrefix = 2;
                        }
                    }

                    if (ss_nullptr_k != server &&
                        ss_nullptr_k != share)
                    {
                        /* Invalid characters in the UNC root (host + share). */
                        if (0 == (WINSTL_PATH_CLASSIFY_F_IGNOREINVALIDCHARS & parseFlags))
                        {
                            char_t const* const rootEnd =
                                (ss_nullptr_k != dir0)
                                    ?   dir0
                                    :   (s0 + cch0);
                            size_t const        rootCch =
                                (size_t)(rootEnd - server);
                            WINSTL_C_PATH_CLASSIFY_IMPL_stlsoft_C_string_slice_X_t_ const alwaysInvalidChars =
                                winstl_C_path_classify_alwaysInvalidChars_X_();
                            char_t const*       invalidChar;

                            if (ss_nullptr_k != (invalidChar = WINSTL_C_PATH_CLASSIFY_IMPL_stlsoft_C_strnpbrkn_X_(server, rootCch, alwaysInvalidChars.ptr, alwaysInvalidChars.len)))
                            {
                                results->firstInvalid.len   =   1;
                                results->firstInvalid.ptr   =   invalidChar;

                                return winstl_C_PathType_InvalidChars;
                            }
                        }

                        if (ss_nullptr_k != dir0)
                        {
                            *ppS1   =   dir0;
                            *pCch1  =   cch0 - (dir0 - s0);
                        }
                        else
                        {
                            /* "\\host\share" with no trailing separator. */
                            *ppS1   =   s0 + cch0;
                            *pCch1  =   0;
                        }

                        return winstl_C_PathType_UncRooted;
                    }
                }
                else
                {
                    return winstl_C_PathType_Invalid;
                }
            }
            else
            {
                return winstl_C_PathType_SlashRooted;
            }
        }
    }

try_detect_drive:
    if (cch0 > 1)
    {
        if (WINSTL_C_PATH_CLASSIFY_IMPL_stlsoft_C_isdriveletter_X_(s0[0]) &&
            ':' == s0[1])
        {
            if (2 == cch0)
            {
drive_letter_relative:
                *ppS1   =   s0 + 2;
                *pCch1  =   cch0 - 2;

                return winstl_C_PathType_DriveLetterRelative;
            }
            else
            {
                if ('/' == s0[2] ||
                    '\\' == s0[2])
                {
                    *ppS1   =   s0 + 2;
                    *pCch1  =   cch0 - 2;

                    return winstl_C_PathType_DriveLetterRooted;
                }
                else
                {
                    goto drive_letter_relative;
                }
            }
        }
        else
        if (0 != *pIsLongPathPrefixed)
        {
            /* "\\?\…" that is not "\\?\UNC\…" and not "\\?\X:…" */
            return winstl_C_PathType_Invalid;
        }
        else
        if (0 != *pCchPrefix)
        {
            *ppS1   =   s0;
            *pCch1  =   cch0;
        }
    }
    else
    if (0 != *pIsLongPathPrefixed)
    {
        return winstl_C_PathType_Invalid;
    }

    return winstl_C_PathType_Relative;
}

STLSOFT_INLINE
winstl_C_path_classification_t
winstl_C_path_classify_impl_X_(
    WINSTL_C_PATH_CLASSIFY_IMPL_char_t_ const*  s0
,   size_t                                      cch0
,   int                                         parseFlags
,   winstl_C_path_classification_results_X_t_*  results
)
{
    typedef WINSTL_C_PATH_CLASSIFY_IMPL_char_t_             char_t;

    char_t const*                               s1;
    size_t                                      cch1;
    size_t                                      cchPrefix;
    int                                         isLongPathPrefixed;
    char_t const*                               invalidChar;
    winstl_C_path_classification_t              rcRoot;
#if 0
#elif defined(STLSOFT_CF_gcc_pragma_diagnostic_pop)

# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wmissing-braces"
# pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif
    winstl_C_path_classification_results_X_t_   blank = { 0 };
#if 0
#elif defined(STLSOFT_CF_gcc_pragma_diagnostic_pop)

# pragma GCC diagnostic pop
#endif

    WINSTL_ASSERT(0 == cch0 || ss_nullptr_k != s0);

    WINSTL_MESSAGE_ASSERT("unrecognised parsing flags", 0 == (~WINSTL_PATH_CLASSIFY_F_MASK_ & parseFlags));

    WINSTL_ASSERT(ss_nullptr_k != results);

    *results = blank;

    results->input.ptr  =   s0;
    results->input.len  =   cch0;

    if (0 == cch0)
    {
        return winstl_C_PathType_Empty;
    }

    rcRoot = winstl_C_path_classify_root_X_(
        s0, cch0
    ,   parseFlags
    ,   results
    ,   &s1, &cch1
    ,   &cchPrefix
    ,   &isLongPathPrefixed
    );

    WINSTL_ASSERT(s0 + cch0 == s1 + cch1);

    switch (rcRoot)
    {
    case    winstl_C_PathType_Relative:
    case    winstl_C_PathType_SlashRooted:
    case    winstl_C_PathType_DriveLetterRelative:
    case    winstl_C_PathType_DriveLetterRooted:
    case    winstl_C_PathType_UncRooted:
    case    winstl_C_PathType_HomeRooted:

        break;
    default:

        return rcRoot;
    }

    if (0 == (WINSTL_PATH_CLASSIFY_F_IGNOREINVALIDCHARS & parseFlags))
    {
        WINSTL_C_PATH_CLASSIFY_IMPL_stlsoft_C_string_slice_X_t_ const alwaysInvalidChars = winstl_C_path_classify_alwaysInvalidChars_X_();

        if (ss_nullptr_k != (invalidChar = WINSTL_C_PATH_CLASSIFY_IMPL_stlsoft_C_strnpbrkn_X_(s1, cch1, alwaysInvalidChars.ptr, alwaysInvalidChars.len)))
        {
            results->firstInvalid.len   =   1;
            results->firstInvalid.ptr   =   invalidChar;

            return winstl_C_PathType_InvalidChars;
        }

        if (ss_nullptr_k != (invalidChar = WINSTL_C_PATH_CLASSIFY_IMPL_stlsoft_C_strnchr_X_(s1, cch1, ':')))
        {
            results->firstInvalid.len   =   1;
            results->firstInvalid.ptr   =   invalidChar;

            return winstl_C_PathType_InvalidChars;
        }
    }

    {
        char_t const* const last    =   s1 + cch1;

        char_t const*       p0;
        size_t              i;

        char_t const*       lastBSlash  =   ss_nullptr_k;
        char_t const*       lastFSlash  =   ss_nullptr_k;
        char_t const*       lastSlash   =   ss_nullptr_k;

        char_t const*       lastDot     =   ss_nullptr_k;
        char_t const*       prev        =   ss_nullptr_k;

#if 0 || \
    defined(STLSOFT_COMPILER_IS_CLANG) || \
    defined(STLSOFT_COMPILER_IS_GCC) || \
    0

        STLSOFT_SUPPRESS_UNUSED(prev);
#endif

        int const           checkRuns   =   0 == (WINSTL_PATH_CLASSIFY_F_IGNORESLASHRUNS & parseFlags);
        int                 runLength   =   0;

        size_t              numParts        =   0;
        size_t              numDotsParts    =   0;
        char_t const*       partStart       =   s1;

        for (i = 0, p0 = s1; i != cch1; ++i, ++p0)
        {
            switch (*p0)
            {
            case '.':

                if (0 != runLength)
                {
                    partStart = p0;
                }

                lastDot = p0;

                runLength = 0;
                break;
            case '/':

                if (isLongPathPrefixed &&
                    0 == (WINSTL_PATH_CLASSIFY_F_IGNOREINVALIDCHARSINLONGPATH & parseFlags))
                {
                    results->firstInvalid.len   =   1;
                    results->firstInvalid.ptr   =   p0;

                    return winstl_C_PathType_InvalidChars;
                }

                /* fall through */
                STLSOFT_FALLTHROUGH();
            case '\\':

                *((*p0 == '\\') ? &lastBSlash : &lastFSlash) = p0;

                lastDot = ss_nullptr_k;

                if (0 == runLength)
                {
                    /* Completed a directory part (entry is not counted).
                     * Count only exact "." / ".." components.
                     */
                    size_t const partLen = (size_t)(p0 - partStart);

                    if (1 == partLen &&
                        '.' == partStart[0])
                    {
                        ++numDotsParts;
                    }
                    else
                    if (2 == partLen &&
                        '.' == partStart[0] &&
                        '.' == partStart[1])
                    {
                        ++numDotsParts;
                    }

                    ++numParts;
                }
                else
                {
                    if (checkRuns)
                    {
                        results->firstInvalid.len    =   1;
                        results->firstInvalid.ptr    =   p0;

                        return winstl_C_PathType_InvalidSlashRuns;
                    }
                }

                ++runLength;
                break;
            default:

                if (0 != runLength)
                {
                    partStart = p0;
                }

                runLength = 0;
                break;
            }

            prev = p0;
        }

        if (ss_nullptr_k != lastBSlash)
        {
            if (ss_nullptr_k != lastFSlash)
            {
                if (lastBSlash < lastFSlash)
                {
                    lastSlash = lastFSlash;
                }
                else
                {
                    lastSlash = lastBSlash;
                }
            }
            else
            {
                lastSlash = lastBSlash;
            }
        }
        else
        {
            if (ss_nullptr_k != lastFSlash)
            {
                lastSlash = lastFSlash;
            }
            else
            {
                ; /* nothing to do */
            }
        }

        if (ss_nullptr_k != lastSlash)
        {
            if (lastSlash < s1 + (cch1 - 1))
            {
                results->entry.len  =   last - (lastSlash + 1);
                results->entry.ptr  =   lastSlash + 1;
            }
        }
        else
        {
            if (0 != cch1)
            {
                results->entry.len  =   cch1;
                results->entry.ptr  =   s1;
            }
        }

        results->stem   =   results->entry;

        if (ss_nullptr_k != lastDot)
        {
            /* Now we need to examine for special names
             *
             * - "."
             * - ".."
             *
             */

            if (1 == results->entry.len)
            {
                WINSTL_ASSERT(lastDot == results->entry.ptr);

                /* The current directory "." */

                ;
            }
            else
            if (2 == results->entry.len &&
                '.' == results->entry.ptr[0] &&
                '.' == results->entry.ptr[1])
            {
                /* The parent directory ".." */

                ;
            }
            else
            {
                results->extension.len  =   last - lastDot;
                results->extension.ptr  =   lastDot;

                results->stem.len       -=  results->extension.len;
            }
        }

        results->numDirectoryParts      =   numParts;
        results->numDotsDirectoryParts  =   numDotsParts;
    }

    results->prefix.len =   cchPrefix;
    results->prefix.ptr =   s0;

    results->root.len   =   cch0 - cch1;
    results->root.ptr   =   s0;

    results->location   =   results->input;
    results->directory  =   results->input;

    if (0 != results->entry.len)
    {
        results->location.len   -=  results->entry.len;
        results->directory.len  -=  results->entry.len;
    }

    if (0 != results->root.len)
    {
        results->directory.len  -=  results->root.len;
        results->directory.ptr  +=  results->root.len;
    }

    return rcRoot;
}

STLSOFT_INLINE
winstl_C_path_classification_t
winstl_C_path_classify_root_impl_X_(
    WINSTL_C_PATH_CLASSIFY_IMPL_char_t_ const*                  s0
,   size_t                                                      cch0
,   int                                                         parseFlags
,   WINSTL_C_PATH_CLASSIFY_IMPL_stlsoft_C_string_slice_X_t_*    root
)
{
    typedef WINSTL_C_PATH_CLASSIFY_IMPL_char_t_             char_t;

    char_t const*                               s1;
    size_t                                      cch1;
    size_t                                      cchPrefix;
    int                                         isLongPathPrefixed;
    winstl_C_path_classification_t              rcRoot;
    winstl_C_path_classification_results_X_t_   results;

    WINSTL_ASSERT(0 == cch0 || ss_nullptr_k != s0);

    WINSTL_MESSAGE_ASSERT("unrecognised parsing flags", 0 == (~WINSTL_PATH_CLASSIFY_F_MASK_ & parseFlags));

    WINSTL_ASSERT(ss_nullptr_k != root);

    root->len   =   0;
    root->ptr   =   NULL;

    if (0 == cch0)
    {
        return winstl_C_PathType_Empty;
    }

    rcRoot = winstl_C_path_classify_root_X_(
        s0, cch0
    ,   parseFlags
    ,   &results
    ,   &s1, &cch1
    ,   &cchPrefix
    ,   &isLongPathPrefixed
    );

    WINSTL_ASSERT(cch1 <= cch0);

    root->len   =   cch0 - cch1;

    switch (rcRoot)
    {
    case    winstl_C_PathType_SlashRooted:
    case    winstl_C_PathType_DriveLetterRooted:
    case    winstl_C_PathType_UncRooted:
    case    winstl_C_PathType_HomeRooted:

        root->ptr   =   s0;
        break;
    case    winstl_C_PathType_DriveLetterRelative:

        root->ptr   =   s0;
        break;
    case    winstl_C_PathType_UncIncomplete:

        root->len   =   cch0;
        root->ptr   =   s0;
        break;
    default:

        break;
    }

    return rcRoot;
}


/* ///////////////////////////// end of file //////////////////////////// */

