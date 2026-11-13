
/**
 * Created: 23rd May 2006
 * Updated: 13th November 2026
 */


/** \defgroup group__concept__Shim Shims
 * \ingroup group__concepts
 *
 * \brief &nbsp;&nbsp;&nbsp;&nbsp;Generalised Type Manipulation without Coupling.
 */


////////////////////////////////////////////////////////////
// Categories:


/** \defgroup group__concept__Shim__Attribute Attribute Shims
 *
 * \ingroup group__concept__Shim
 *
 * \brief These \ref group__concept__Shim "shims" elicit attributes
 *   of the types for which they are defined.
 */

/** \defgroup group__concept__Shim__Conversion Conversion Shims
 *
 * \ingroup group__concept__Shim
 *
 * \brief These \ref group__concept__Shim "shims" convert instances
 *   of the types for which they are defined into a common type.
 */

/** \defgroup group__concept__Shim__Logical Logical Shims
 *
 * \ingroup group__concept__Shim
 *
 * \brief These \ref group__concept__Shim "shims" elicit a Boolean
 *   attribute of the types for which they are defined.
 */

/** \defgroup group__concept__dl Dynamic Library Concepts
 *
 * \ingroup group__concepts
 *
 * \brief Concepts pertaining to dynamic libraries / modules.
 */

////////////////////////////////////////////////////////////
// Subjects:

/** \defgroup group__subject__Shim__collection Collection Shims
 *
 * \ingroup group__concept__Shim
 *
 * \brief These \ref group__concept__Shim "shims" pertain to
 *   collections.
 */

/** \defgroup group__subject__Shim__pointer Pointer Shims
 *
 * \ingroup group__concept__Shim
 *
 * \brief These \ref group__concept__Shim "shims" pertain to
 *   pointers and "smart pointers".
 */

////////////////////////////////////////////////////////////
// Shims:

/** \defgroup group__concept__Shim__Logical__is_empty stlsoft::is_empty Logical Shim
 *
 * \ingroup group__subject__Shim__collection
 * \ingroup group__concept__Shim__Logical
 *
 * \brief These \ref group__concept__Shim "shims" indicate whether a given
 *    collection instance is empty.
 *
 * <h2>Shim Definition:</h2>
 *
 * - <b>Name</b>: <code>stlsoft::is_empty</code>
 * - <b>Intent</b>: Indicates whether or not a given collection instance
 *       is empty, i.e. does not currently contain any elements.
 * - <b>Category</b>: Logical
 * - <b>Ostensible Return Type</b>: <code>ss_truthy_k</code> (meaningful
 *       return values are 0 (<code>false</code>) and
 *       non-0 (<code>true</code>))
 *
 * - <b>Degenerate Case(s)</b>: &lt;<i>not applicable</i>&gt;
 * - <b>General Adapted Case(s)</b>: assumes <code>empty()</code> method
 *       callable on reference-to-non-mutating (<code>const</code>) instance,
 *       returning <code>bool</code>.
 */


/** \defgroup group__concept__Shim__Logical__is_null stlsoft::is_null Logical Shim
 *
 * \ingroup group__subject__Shim__pointer
 * \ingroup group__concept__Shim__Logical
 *
 * \brief These \ref group__concept__Shim "shims" indicate whether a given
 *    pointer instance is empty.
 *
 * <h2>Shim Definition:</h2>
 *
 * - <b>Name</b>: <code>stlsoft::is_null</code>
 * - <b>Intent</b>: Indicates whether or not a given pointer instance
 *       is null, i.e. does not currently point to anything.
 * - <b>Category</b>: Logical
 * - <b>Ostensible Return Type</b>: <code>ss_truthy_k</code> (meaningful
 *       return values are 0 (<code>false</code>) and
 *       non-0 (<code>true</code>))
 *
 * - <b>Degenerate Case(s)</b>: &lt;<i>not applicable</i>&gt;
 * - <b>General Adapted Case(s)</b>: assumes pointer is \c null.
 */


/** \defgroup group__concept__Shim__Attribute__get_ptr stlsoft::get_ptr Pointer Attribute Shim
 *
 * \ingroup group__subject__Shim__pointer
 * \ingroup group__concept__Shim__Attribute
 *
 * \brief These \ref group__concept__Shim "shims" elicit a pointer from
 *   the types for which they are defined.
 *
 * <h2>Shim Definition:</h2>
 *
 * - <b>Name</b>: <code>stlsoft::get_ptr</code>
 * - <b>Intent</b>: Elicits a raw pointer from the instance to which it is
 *                    applied.
 * - <b>Category</b>: Attribute
 * - <b>Ostensible Return Type</b>: <code>T*</code> or <code>T const*</code>,
 *                    where <code>T</code> is source type-specific.
 *
 * - <b>Degenerate Case(s)</b>: Two function templates for <code>T*</code>
 *                    and <code>T const*</code>.
 * - <b>General Adapted Case(s)</b>: &lt;<i>not applicable</i>&gt;
 * - <b>Common Adapted Type(s)</b>: stlsoft::ref_ptr, std::auto_ptr, stlsoft::shared_ptr, etc.
 */


/** \defgroup group__concept__Shim__Attribute__get_FILE_ptr stlsoft::get_FILE_ptr Pointer Attribute Shim
 *
 * \ingroup group__subject__Shim__pointer
 * \ingroup group__concept__Shim__Attribute
 *
 */

/** \defgroup group__concept__Shim__Attribute__get_top stlsoft::get_top Top Attribute Shim
 *
 * \ingroup group__concept__Shim__Attribute
 *
 * \brief These \ref group__concept__Shim "shims" elicit the top element
 *   of stack-like / sequence types for which they are defined.
 */


/** \defgroup group__concept__Shim__module_attribute Module Attribute Shims
 *
 * \ingroup group__concept__Shim
 *
 * \ingroup group__concept__dl
 *
 * \brief These \ref group__concept__Shim "shims" access the module handle
 *   attribute of types that may represent operating system executable modules.
 */


/** \defgroup group__concept__Shim__stream_insertion Stream Insertion Shims
 *
 * \ingroup group__concept__Shim
 *
 * \brief These \ref group__concept__Shim "shims" make types compatible for
 *   stream insertion via the <code>overloaded &lt;&lt;</code> operator.
 */


/** \defgroup group__concept__Shim__string_access String Access Shims
 *
 * \ingroup group__concept__Shim
 *
 * \brief These \ref group__concept__Shim "shims" access the length and
 *   contents of types that may be represented as character strings.
 *
 * \section group__concept__Shim__string_access__c_str_data c_str_data String Access Shim
 *
 * \section group__concept__Shim__string_access__c_str_len c_str_len String Access Shim
 *
 * \section group__concept__Shim__string_access__c_str_ptr c_str_ptr String Access Shim
 *
 * \section group__concept__Shim__string_access__c_str_ptr_null c_str_ptr_null String Access Shim
 *
 * \section group__concept__Shim__string_access__c_str_size c_str_size String Access Shim
 */


/** \defgroup group__concept__Shim__synchronisation_control Synchronisation Control Shims
 *
 * \ingroup group__library__Synch
 * \ingroup group__concept__Shim
 *
 * \brief These \ref group__concept__Shim "shims" control the behaviour of
 *   synchronisation objects.
 */


/** \defgroup group__concept__Shim__Conversion__to_uint64 winstl::to_uint64 Time Conversion Shim
 *
 * \ingroup group__concept__Shim__Conversion
 *
 */


/** \defgroup group__concept__Shim__Conversion__to_DATE winstl::to_DATE Date Conversion Shim
 *
 * \ingroup group__concept__Shim__Conversion
 *
 */


/** \defgroup group__concept__Shim__Conversion__to_FILETIME winstl::to_FILETIME Time Conversion Shim
 *
 * \ingroup group__concept__Shim__Conversion
 *
 * \brief These \ref group__concept__Shim "shims" convert a given instance
 *   to an instance of the Windows type <code>FILETIME</code>.
 *
 * <h2>Shim Definition:</h2>
 *
 * - <b>Name</b>: <code>winstl::to_FILETIME</code>
 * - <b>Intent</b>: Converts a given instance to an instance
 *        of the Windows type <code>FILETIME</code>.
 * - <b>Category</b>: Conversion
 * - <b>Ostensible Return Type</b>: <code>const FILETIME</code>
 *
 * - <b>Degenerate Case(s)</b>: <code>FILETIME const &to_FILETIME(FILETIME const &rhs)</code>
 */


/** \defgroup group__concept__Shim__Conversion__to_SYSTEMTIME winstl::to_SYSTEMTIME Time Conversion Shim
 *
 * \ingroup group__concept__Shim__Conversion
 *
 * \brief These \ref group__concept__Shim "shims" convert a given instance
 *   to an instance of the Windows type <code>SYSTEMTIME</code>.
 *
 * <h2>Shim Definition:</h2>
 *
 * - <b>Name</b>: <code>winstl::to_SYSTEMTIME</code>
 * - <b>Intent</b>: Converts a given instance to an instance
 *        of the Windows type <code>SYSTEMTIME</code>.
 * - <b>Category</b>: Conversion
 * - <b>Ostensible Return Type</b>: <code>const SYSTEMTIME</code>
 *
 * - <b>Degenerate Case(s)</b>: <code>SYSTEMTIME const &to_SYSTEMTIME(SYSTEMTIME const &rhs)</code>
 */
