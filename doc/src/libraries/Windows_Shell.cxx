
/*
 * Created: 8th June 2006
 * Updated: 14th November 2026
 */

/** \defgroup group__library__Windows_Shell Windows Shell Library
 * \ingroup group__libraries
 *
 * \brief This library contains classes and functions for manipulation of
 *  the Windows Shell.
 *
 * The library includes the following classes and functions:
 * 
 * - The winstl::basic_drophandle_sequence class template provides an
 *   STL-collection interface over the Windows Shell API drop handle
 *   functions.
 * - The winstl::browse_for_folder() function templates provide type-safe
 *   and easy to use wrappers for the ::<code>SHBrowseForFolder</code> API function.
 * - The winstl::shell_delete() function templates provide type-safe and
 *   easy to use wrappers for the ::<code>SHFileOperation</code> API
 *   function, which delete file(s) and, optionally, place them in the
 *   recycle bin. (The kernel function ::<code>DeleteFile</code> does not do
 *   this; it permanently deletes your file(s).)
 *
 */

/* NOTE: former example by_library/windows_shell/enum_values/enum_values.cpp — not present in current examples/ tree */

/** \example by_library/windows_shell/shell_functions/main.cpp
 * \brief [C++ only] Illustrates use of the
 *  \ref group__library__Windows_Shell "Windows Shell library"
 *   folder browsing and file operation functions.
 *  component.
 */

/** \example by_library/windows_shell/memory_functions/main.cpp
 * \brief [C++ only] Illustrates use of the
 *  \ref group__library__Windows_Shell "Windows Shell library"
 *   memory operations.
 *  component.
 */
