
/**
 * Created: 8th June 2006
 * Updated: 12th January 2017
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

/* \example by_library/windows_shell/enum_values/enum_values.cpp
 * \brief [C++ only] Illustrates use of the
 *  \ref group__library__Windows_Shell "Windows Shell library"
 *  component
 *  \link winstl::basic_reg_value_sequence reg_value_sequence\endlink
 *  (and the associated component
 *  \link winstl::basic_reg_value reg_value\endlink), by enumerating
 *  the environment variables defined for the current user.
 *
 * The name (obtained via
 * \link winstl::basic_reg_value::name() name()\endlink) of
 * each shell value is printed out, followed by its value, as follows:
 * - If the value is a path list (it contains two or more paths separated
 *   by semicolons), then the value (obtained via 
 *   \link winstl::basic_reg_value::value_sz value_sz()\endlink) is tokenised
 *   into individual paths that are printed in an indented list.
 * - If the value contains an environment variable (it contains the %
 *   character), then the value (obtained via 
 *   \link winstl::basic_reg_value::value_sz value_sz()\endlink) is printed,
 *   followed by the actual value (obtained via 
 *   \link winstl::basic_reg_value::value_expand_sz() value_expand_sz()\endlink),
 *   wherein all environment variable references are resolved.
 * - Otherwise the value (obtained via 
 *   \link winstl::basic_reg_value::value_sz value_sz()\endlink) is printed.
 *
 *
 * \remarks The test program also illustrates the use of the 
 *  stlsoft::string_tokeniser
 *  and
 *  stlsoft::ostream_iterator
 *  components.
 */

/** \example by_library/windows_shell/shell_functions/shell_functions.cpp
 * \brief [C++ only] Illustrates use of the
 *  \ref group__library__Windows_Shell "Windows Shell library"
 *   folder browsing and file operation functions.
 *  component.
 */

/** \example by_library/windows_shell/memory_functions/memory_functions.cpp
 * \brief [C++ only] Illustrates use of the
 *  \ref group__library__Windows_Shell "Windows Shell library"
 *   memory operations.
 *  component.
 */
