
/**
 * Created: 12th December 2006
 * Updated: 14th November 2026
 */

/** \defgroup group__library__Utility Utility Library
 * \ingroup group__libraries
 *
 * \brief This library defines classes and functions that are
 *   used by other libraries and/or have no other obvious grouping.
 *
 * The utility components provided by the STLSoft libraries are
 * subdivided into project/library-specific projects, which include:
 *
 * - \ref group__library__Utility__COM
 *
 *
 */

/** \defgroup group__library__Utility__Constraints Constraints Utility Library
 * \ingroup group__library__Utility
 *
 * \brief This library defines classes, functions and macros that act as
 *   constraints.
 *
 * The following constraints are defined by the STLSoft libraries:
 * - stlsoft::must_have_base - ensures that a given class is derived from, or is the same as, another.
 * - stlsoft::must_be_derived - ensures that a given class is derived from, and not the same as, another.
 * - stlsoft::must_be_same_size - ensures that two types are the same size.
 * - stlsoft::must_be_subscriptable - ensures that a type is subscriptable.
 * - stlsoft::must_subscript_as_decayable_pointer - ensures that a type is subscriptable as a decayable pointer, i.e. it is a pointer or an array.
 * - stlsoft::must_be_pod - ensures that a type is POD (plain old data).
 * - stlsoft::must_be_pod_or_void - ensures that a type is POD (plain old data), or is \c void.
 */

/** \defgroup group__library__Utility__COM COM Utility Library
 * \ingroup group__library__Utility
 * \ingroup group__project__comstl
 *
 * \brief This library defines classes and functions for COM that are
 *   used by other libraries and/or have no other obvious grouping.
 *
 * The components in the COM Utility library provide the following
 * services (all components are in the \ref comstl namespace):
 *
 * - <b>Facades</b>: \link comstl::bstr bstr\endlink, \link comstl::guid guid\endlink, \link comstl::variant variant\endlink
 * - <b>Library initialisation</b>: \link comstl::initialiser initialiser\endlink
 * - <b>Object creation</b>: \link comstl::co_create_instance co_create_instance()\endlink
 * - <b>Interface control</b>: <code>comstl::addref()</code>, <code>comstl::safe_addref()</code>, <code>comstl::release()</code>, <code>comstl::safe_release()</code>
 * - <b>Running Object Table</b>: <code>comstl::Rot_Register()</code>, <code>comstl::Rot_Revoke()</code>, <code>comstl::Rot_IsRunning()</code>, <code>comstl::Rot_GetObject()</code>, <code>comstl::Rot_NoteChangeTime()</code>, <code>comstl::Rot_GetTimeOfLastChange()</code>, <code>comstl::Rot_EnumRunning()</code>
 * - <b>Marshalling</b>: \link comstl::MarshalInterThreadInterfaceInStream MarshalInterThreadInterfaceInStream()\endlink, \link comstl::GetInterfaceAndReleaseStream GetInterfaceAndReleaseStream()\endlink
 *
 */

/** \defgroup group__library__Utility__Windows Windows Utility Library
 * \ingroup group__library__Utility
 * \ingroup group__project__winstl
 *
 */

/*
 * - <b>Sequences</b>: \link comstl::enumerator_sequence enumerator_sequence\endlink, \link comstl::collection_sequence collection_sequence\endlink, \link comstl::safearray_sequence safearray_sequence\endlink
 */

/** \example by_library/com_utility/rot_functions/main.cpp
 *
 * \brief C++ example program demonstrating use of various \ref comstl "COMSTL"
 *   components to manipulate the COM Running Object Table.
 */

/** \example by_library/com_utility/creation_functions/main.cpp
 *
 * \brief C++ example program demonstrating use of the \ref comstl "COMSTL"
 *   co_create_instance functions to create instances of the
 *   <code><a href = "http://pantheios.org/">Pantheios.COM</a>.LoggerManager</code> coclass.
 */
