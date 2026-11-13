
/**
 * Created: 10th June 2006
 * Updated: 12th January 2017
 */

/** \defgroup group__library__Conversion Conversion Library
 * \ingroup group__libraries
 *
 * \brief This library defines a number of components that provide
 *  conversion functionality.
 *
 * The components provided by the <b>Conversion Library</b> include:
 *
 * - The stlsoft::any_caster cast class template
 * - The stlsoft::explicit_cast cast class template
 * - The stlsoft::literal_cast cast class template
 * - The stlsoft::sap_cast cast function template
 * - The stlsoft::ptr_cast cast class template
 * - The stlsoft::union_cast cast function template
 * - The comstl::interface_cast cast function template
 *
 * - The stlsoft::integer_to_string() suite of highly efficient
 *   conversion functions
 *
 * - The winstl::ansi2Unicode and winstl::unicode2Ansi char encoding
 *   converter classes
 *
 */

/** \example by_library/conversion/interface_cast/main.cpp
 *
 * \brief Illustrates use of the \link comstl::interface_cast interface_cast\endlink
 *   custom cast function template, which permits casts between
 *   (non-<code>void*</code>) pointers of the same <i>cv</i>-qualification.
 */

/** \example by_library/conversion/sap_cast/main.cpp
 *
 * \brief Illustrates use of the \link stlsoft::sap_cast sap_cast\endlink
 *   custom cast function template, which permits casts between
 *   (non-<code>void*</code>) pointers of the same <i>cv</i>-qualification.
 */

/** \example by_library/conversion/union_cast/main.cpp
 *
 * \brief Illustrates use of the \link stlsoft::union_cast union_cast\endlink
 *   custom cast function template, which permits casts between
 *   arbitrary types as long as they have the same size.
 */
