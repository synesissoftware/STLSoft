
/**
 * Created: 26th May 2006
 * Updated: 12th January 2017
 */

/** \defgroup group__library__Windows_Clipboard Windows Clipboard Library
 * \ingroup group__libraries
 *
 * \brief This library contains classes and functions for manipulation of
 *  the Windows Clipboard.
 *
 * The \ref group__library__Windows_Clipboard provides a suite of classes
 * that represent these entities and provide facilities for accessing,
 * enumerating and modifying them:
 * 
 * - The winstl::clipboard_format_sequence class provides an STL-like
 *   sequence for iterating the clipboard formats for the current process.
 * - The winstl::clipboard_scope class acquires access to the Win32
 *   clipboard, and acts as a facade over the clipboard API. .
 *
 */

/** \example by_library/windows_clipboard/clipboard_format_sequence/main.cpp
 * \brief [C++ only] Illustrates use of the
 *  \ref group__library__Windows_Clipboard "Windows Clipboard library"
 *   class \link winstl::clipboard_format_sequence clipboard_format_sequence\endlink.
 */

/** \example by_library/windows_clipboard/clipboard_scope/main.cpp
 * \brief [C++ only] Illustrates use of the
 *  \ref group__library__Windows_Clipboard "Windows Clipboard library"
 *   class \link winstl::clipboard_scope clipboard_scope\endlink.
 */
