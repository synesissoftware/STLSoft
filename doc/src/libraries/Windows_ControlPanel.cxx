
/**
 * Created: 26th May 2006
 * Updated: 12th January 2017
 */

/** \defgroup group__library__Windows_ControlPanel Windows Control Panel Library
 * \ingroup group__libraries
 *
 * \brief This library contains classes and functions for manipulation of
 *  the Windows Control Panel.
 *
 * The Windows Control Panel is XXX XXX XXX. The 
 * \ref group__library__Windows_ControlPanel provides a suite of classes
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
 */

/** \example by_library/windows_control_panel/windows_control_panel/main.cpp
 * \brief [C++ only] Illustrates use of the
 *  \ref group__library__Windows_ControlPanel "Windows Control Panel library"
 *   class XXX XXX XXX.
 */
