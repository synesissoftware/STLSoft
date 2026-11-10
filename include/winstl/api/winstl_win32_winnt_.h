
/* WARNING: this file contains undocumented internal features that are
 * subject to change at any time, so if you use them it is at your own risk.
 */


#ifndef WINSTL_INCL_WINSTL_API_H_winstl_win32_winnt_
#define WINSTL_INCL_WINSTL_API_H_winstl_win32_winnt_


/* /////////////////////////////////////////////////////////////////////////
 * Windows version compatibility check(s)
 */

#ifdef WINSTL_WIN32_WINNT
# undef WINSTL_WIN32_WINNT
#endif /* WINSTL_WIN32_WINNT */

#ifndef _WIN32_WINNT
# define WINSTL_WIN32_WINNT                                 (0)
#else
# define WINSTL_WIN32_WINNT                                 (_WIN32_WINNT)
#endif

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION

# define WINSTL_WIN32_WINNT_NT4                             (0x0400)
# define WINSTL_WIN32_WINNT_WIN2K                           (0x0500)
# define WINSTL_WIN32_WINNT_WINXP                           (0x0501)
# define WINSTL_WIN32_WINNT_WS03                            (0x0502)
# define WINSTL_WIN32_WINNT_WIN6                            (0x0600)
# define WINSTL_WIN32_WINNT_VISTA                           (0x0600)
# define WINSTL_WIN32_WINNT_WS08                            (0x0600)
# define WINSTL_WIN32_WINNT_LONGHORN                        (0x0600)
# define WINSTL_WIN32_WINNT_WIN7                            (0x0601)
# define WINSTL_WIN32_WINNT_WIN8                            (0x0602)
# define WINSTL_WIN32_WINNT_WINBLUE                         (0x0603)
# define WINSTL_WIN32_WINNT_WINTHRESHOLD                    (0x0A00)
# define WINSTL_WIN32_WINNT_WIN10                           (0x0A00)
#endif /* !STLSOFT_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_PPF_pragma_message_SUPPORT
# pragma once
#endif /* STLSOFT_PPF_pragma_message_SUPPORT */

#endif /* !WINSTL_INCL_WINSTL_API_H_winstl_win32_winnt_ */

/* ///////////////////////////// end of file //////////////////////////// */

