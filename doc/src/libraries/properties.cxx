
/**
 * Created: 10th June 2006
 * Updated: 12th January 2017
 */

/** \defgroup group__library__Properties Properties Library
 * \ingroup group__libraries
 *
 * \brief This library defines file template components for the
 *   definition of efficient C++ classes exhibiting properties.
 *
 * C++ properties, like those in other languages (such as C#, D), have the
 * syntactic appearance of fields (member variables) but define precise read
 * and/or write access, and may in fact invoke methods on the callee, rather
 * than manipulating member variables. For example, consider the following
 * class that defines a read-only field property <b>Name</b> and a
 * read-write method property 

 *
 * The components provided by the
 * \ref group__library__Properties "Properties" library include:
 *
 * - Internal field properties may be defined using the 
 *   stlsoft::field_property_get and stlsoft::field_property_set
 *   class templates.
 * - External field properties may be defined using the 
 *   stlsoft::field_property_get_external and
 *   stlsoft::field_property_set_external class templates.
 * - Internal method properties may be defined using the 
 *   stlsoft::method_property_get, stlsoft::method_property_set and
 *   stlsoft::method_property_getset class templates.
 * - External method properties may be defined using the 
 *   stlsoft::method_property_get_external,
 *   stlsoft::method_property_set_external and
 *   stlsoft::method_property_getset_external class templates.
 * - Static method properties may be defined using the 
 *   stlsoft::static_method_property_get,
 *   stlsoft::static_method_property_set and
 *   stlsoft::static_method_property_getset class templates.
 * - Static external method properties may be defined using the
 *   stlsoft::static_method_property_get_external,
 *   stlsoft::static_method_property_set_external and
 *   stlsoft::static_method_property_getset_external class templates.
 *
 *
 */

/** \example by_library/properties/properties/properties.cpp
 * \brief [C++ only] Illustrates use of the
 *  \ref group__library__Properties "Properties library"
 *   \link stlsoft::field_property_get field_property_get\endlink
 *   and
 *   \link stlsoft::method_property_getset_external method_property_getset_external\endlink
 *   components.
 *
 * This example demonstrates the definition of a read-only field property
 * in conjunction with a (validating) read/write external method property.
 */


/** \example by_library/properties/field_property_get/field_property_get.cpp
 * \brief [C++ only] Illustrates use of the
 *  \ref group__library__Properties "Properties library"
 *   \link stlsoft::field_property_get field_property_get\endlink component.
 *
 * This example demonstrates the definition of a write-only field property.
 */

/** \example by_library/properties/field_property_set/field_property_set.cpp
 * \brief [C++ only] Illustrates use of the
 *  \ref group__library__Properties "Properties library"
 *   \link stlsoft::field_property_set field_property_set\endlink component.
 *
 * This example demonstrates the definition of a read-only field property.
 */
