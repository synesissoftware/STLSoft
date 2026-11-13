
/**
 * Created: 6th June 2006
 * Updated: 14th November 2026
 */

/** \defgroup group__library__error Error Library
 * \ingroup group__libraries
 *
 * \brief This library defines components that assist with error
 *  interpretation and handling.
 *
 * \section section__library__Error__Classes Error Classes
 *
 * The Error library currently includes the following classes:
 *
 * - atlstl::SupportErrorInfoImpl, atlstl::SupportErrorInfoImpl2, atlstl::SupportErrorInfoImpl3, atlstl::SupportErrorInfoImpl4, atlstl::SupportErrorInfoImpl5 - provide implementations of the standard COM interface <code>ISupportErrorInfo</code> to indicate support for specific interface(s)
 * - comstl::errorinfo_desc - represents the current value of the COM Error Object as a string
 * - stlsoft::errno_scope - \ref group__pattern__scoping_class "scoping class" for <code>errno</code>
 * - winstl::basic_error_desc - represents a Windows error code as its string form
 * - winstl::last_error_scope - \ref group__pattern__scoping_class "scoping class" for the Windows thread error
 *
 * \section section__library__Error__Functions Error Functions
 *
 * The Error library currently includes the function suites:
 *
 * - comstl::set_error_info - Sets/modifies the COM Error Object
 * - winstl::format_message - Translates a Windows system error to its equivalent string form
 *
 */


