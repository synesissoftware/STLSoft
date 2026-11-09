
/* WARNING: this file contains undocumented internal features that are
 * subject to change at any time, so if you use them it is at your own risk.
 */


#ifndef WINSTL_INCL_WINSTL_API_H_winstl_ntddi_
#define WINSTL_INCL_WINSTL_API_H_winstl_ntddi_


/* /////////////////////////////////////////////////////////////////////////
 * Windows version compatibility check(s)
 */

#ifdef WINSTL_NTDDI_VERSION
# undef WINSTL_NTDDI_VERSION
#endif /* WINSTL_NTDDI_VERSION */

#ifndef NTDDI_VERSION
# define WINSTL_NTDDI_VERSION                               (0)
#else
# define WINSTL_NTDDI_VERSION                               (NTDDI_VERSION)
#endif

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION

//
// NTDDI version constants
//
#define WINSTL_NTDDI_WIN4                                   (0x04000000)

#define WINSTL_NTDDI_WIN2K                                  (0x05000000)
#define WINSTL_NTDDI_WIN2KSP1                               (0x05000100)
#define WINSTL_NTDDI_WIN2KSP2                               (0x05000200)
#define WINSTL_NTDDI_WIN2KSP3                               (0x05000300)
#define WINSTL_NTDDI_WIN2KSP4                               (0x05000400)

#define WINSTL_NTDDI_WINXP                                  (0x05010000)
#define WINSTL_NTDDI_WINXPSP1                               (0x05010100)
#define WINSTL_NTDDI_WINXPSP2                               (0x05010200)
#define WINSTL_NTDDI_WINXPSP3                               (0x05010300)
#define WINSTL_NTDDI_WINXPSP4                               (0x05010400)

#define WINSTL_NTDDI_WS03                                   (0x05020000)
#define WINSTL_NTDDI_WS03SP1                                (0x05020100)
#define WINSTL_NTDDI_WS03SP2                                (0x05020200)
#define WINSTL_NTDDI_WS03SP3                                (0x05020300)
#define WINSTL_NTDDI_WS03SP4                                (0x05020400)

#define WINSTL_NTDDI_WIN6                                   (0x06000000)
#define WINSTL_NTDDI_WIN6SP1                                (0x06000100)
#define WINSTL_NTDDI_WIN6SP2                                (0x06000200)
#define WINSTL_NTDDI_WIN6SP3                                (0x06000300)
#define WINSTL_NTDDI_WIN6SP4                                (0x06000400)

#define WINSTL_NTDDI_VISTA                                  (0x06000000)
#define WINSTL_NTDDI_VISTASP1                               (0x06000100)
#define WINSTL_NTDDI_VISTASP2                               (0x06000200)
#define WINSTL_NTDDI_VISTASP3                               (0x06000300)
#define WINSTL_NTDDI_VISTASP4                               (0x06000400)

#define WINSTL_NTDDI_LONGHORN                               (0x06000000)

#define WINSTL_NTDDI_WS08                                   (0x06000100)
#define WINSTL_NTDDI_WS08SP2                                (0x06000200)
#define WINSTL_NTDDI_WS08SP3                                (0x06000300)
#define WINSTL_NTDDI_WS08SP4                                (0x06000400)

#define WINSTL_NTDDI_WIN7                                   (0x06010000)
#define WINSTL_NTDDI_WIN8                                   (0x06020000)
#define WINSTL_NTDDI_WINBLUE                                (0x06030000)
#define WINSTL_NTDDI_WINTHRESHOLD                           (0x0A000000)
#define WINSTL_NTDDI_WIN10                                  (0x0A000000)
#define WINSTL_NTDDI_WIN10_TH2                              (0x0A000001)
#define WINSTL_NTDDI_WIN10_RS1                              (0x0A000002)
#define WINSTL_NTDDI_WIN10_RS2                              (0x0A000003)
#define WINSTL_NTDDI_WIN10_RS3                              (0x0A000004)
#define WINSTL_NTDDI_WIN10_RS4                              (0x0A000005)
#define WINSTL_NTDDI_WIN10_RS5                              (0x0A000006)
#define WINSTL_NTDDI_WIN10_19H1                             (0x0A000007)
#define WINSTL_NTDDI_WIN10_VB                               (0x0A000008)
#define WINSTL_NTDDI_WIN10_MN                               (0x0A000009)
#define WINSTL_NTDDI_WIN10_FE                               (0x0A00000A)
#define WINSTL_NTDDI_WIN10_CO                               (0x0A00000B)
#define WINSTL_NTDDI_WIN10_NI                               (0x0A00000C)
#define WINSTL_NTDDI_WIN10_CU                               (0x0A00000D)
#define WINSTL_NTDDI_WIN11_ZN                               (0x0A00000E)
#define WINSTL_NTDDI_WIN11_GA                               (0x0A00000F)
#define WINSTL_NTDDI_WIN11_GE                               (0x0A000010)
#endif /* !STLSOFT_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_PPF_pragma_message_SUPPORT
# pragma once
#endif /* STLSOFT_PPF_pragma_message_SUPPORT */

#endif /* !WINSTL_INCL_WINSTL_API_H_winstl_ntddi_ */

/* ///////////////////////////// end of file //////////////////////////// */

