
/* 
 * Created: 21st May 2006
 * Updated: 13th March 2007
 */


/** \defgroup group__project__comstl COMSTL
 * \ingroup group__projects
 *
 * \brief &nbsp;&nbsp;&nbsp;&nbsp;The Standard Template Library meets the Component Object Model (COM).
 *
 * <img src="comstl32x32.jpg" width="32" height="32" align="left" />
 *
 * The philosophy of COMSTL (http://comstl.org/) is essentially the same as that
 * of the STLSoft (http://stlsoft.org/) organisation: providing robust and
 * lightweight software to the Component Object Model (COM) development
 * community. COMSTL provides template-based software that builds on that
 * provided by COM and STLSoft in order to reduce programmer effort and increase
 * robustness in the use of the COM.
 *
 * All components in the <b>COMSTL</b> project reside in the ::comstl namespace
 *
 * As with <b><i>all</i></b> parts of the STLSoft libraries, there are no
 * dependencies on COMSTL binary components and no need to compile COMSTL
 * implementation files; COMSTL is <b>100%</b> header-only!
 *
 * The only other dependencies are on the COM headers and binary components.
 *
 * In addition, some parts of the libraries exhibit different behaviour when
 * translated in different contexts, such as with <code><b>_WIN32_DCOM</b></code>
 * defined, or with <code><b>iaccess.h</b></code> include. In <b><i>all</i></b>
 * cases the libraries function correctly in whatever context they are compiled.
 */


/** \defgroup group__project__comstl__language_agnostic_macros Language Agnostic Macros
 * \ingroup group__project__comstl
 *
 * \brief These macros are used enable writing COM client code that works
 *    regardless of whether it is compiled in C or C++.
 */


/** \defgroup group__project__comstl__assertion_macros Assert Macros
 * \ingroup group__project__comstl
 *
 * \brief These assert macros are used to enforcement contracts and
 *   intermediate assumptions about program state.
 */

/** \defgroup group__project__comstl__code_modification_macros Code Modification Macros
 * \ingroup group__project__comstl
 *
 * \brief These macros are used to 
 */




/** \example by_project/comstl/comstl.cpp
 *
 * \brief C++ example program demonstrating use of most components within
 *   the \ref comstl "COMSTL" project.
 */

