
/**
 * Created: 20th May 2006
 * Updated: 12th January 2017
 */

/** \defgroup group__library__Windows_Registry Windows Registry Library
 * \ingroup group__libraries
 *
 * \brief This library contains classes and functions for manipulation of
 *  the Windows Registry.
 *
 * The Windows registry is a hierarchical database wherein nodes
 * contain values and sub-nodes. A node is known as a <b>key</b>, and
 * the values are known as, er, <b>values</b>. The 
 * \ref group__library__Windows_Registry provides a suite of classes
 * that represent these entities and provide facilities for accessing,
 * enumerating and modifying them:
 * 
 * - The winstl::basic_reg_key class template represents a registry key. It
 *    provides methods for creating, opening, deleting keys, and accessing
 *    and modifying values.
 * - The winstl::basic_reg_value class template represents a registry value.
 *    It provides methods for retrieving the value's value (!) in a variety
 *    of types and forms.
 * - The winstl::basic_reg_key_sequence class template provides an STL
 *    collection for accessing the sub-keys of a given key. Its value type
 *    is (a specialisation of) winstl::basic_reg_key.
 * - The winstl::basic_reg_value_sequence class template provides an STL
 *    collection for accessing the values of a given key. Its value type
 *    is (a specialisation of) winstl::basic_reg_value.
 *
 * \section section__library__Windows_Registry__enumerating_subkeys Enumerating Sub-Keys
 *
 * \section section__library__Windows_Registry__enumerating_values Enumerating Values
 *
 */

/** \example by_library/windows_registry/enum_values/enum_values.cpp
 * \brief [C++ only] Illustrates use of the
 *  \ref group__library__Windows_Registry "Windows Registry library"
 *  component
 *  \link winstl::basic_reg_value_sequence reg_value_sequence\endlink
 *  (and the associated component
 *  \link winstl::basic_reg_value reg_value\endlink), by enumerating
 *  the environment variables defined for the current user.
 *
 * The name (obtained via
 * \link winstl::basic_reg_value::name() name()\endlink) of
 * each registry value is printed out, followed by its value, as follows:
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

/** \example by_library/windows_registry/registry_functions/registry_functions.cpp
 * \brief [C++ only] Illustrates use of the
 *  \ref group__library__Windows_Registry "Windows Registry library"
 *   function reg_get_string_value()
 *  component.
 */
