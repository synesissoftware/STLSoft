
/*
 * Created: 21st May 2006
 * Updated: 14th November 2026
 */


/** \defgroup group__project__stlsoft STLSoft
 * \ingroup group__projects
 *
 * \brief &nbsp;&nbsp;&nbsp;&nbsp;Robust, Lightweight, Cross-platform, Template Software.
 *
 * <img src="stlsoft32x32.jpg" width="32" height="32" align="left" />
 *
 * The philosophy of STLSoft is very simple: providing robust and lightweight software to the development community. The main STLSoft project, STLSoft itself (located at the site you are viewing now) provides cross-platform, technology/API-neutral classes and functions that stand on their own and are useful as independent libraries. They also support the other sub-projects (COMSTL, UNIXSTL, WinSTL, etc.) which are targeted at specific operating systems, technologies and APIs.
 *
 * The philosophy of <a href = "http://comstl.org/">COMSTL</a> is essentially
 * the same as that of the <a href = "http://stlsoft.org/">STLSoft</a>
 * organisation: providing robust and lightweight software to the Component
 * Object Model (COM) development community.
 * <a href = "http://comstl.org/">COMSTL</a> provides template-based software
 * that builds on that provided by COM and
 * <a href = "http://stlsoft.org/">STLSoft</a> in order to reduce programmer
 * effort and increase robustness in the use of the COM.
 *
 * <b>Namespaces</b>
 *
 * The <a href = "http://comstl.org/">COMSTL</a> namespace <code><b>comstl</b></code>
 * is actually an alias for the namespace <code><b>stlsoft::comstl_project</b></code>,
 * and as such all the COMSTL project components actually reside within the
 * <code><b>stlsoft</b></code> namespace
 *
 * <b>Dependencies</b>
 *
 * As with <b><i>all</i></b> parts of the STLSoft libraries, there are no
 * dependencies on <a href = "http://comstl.org/">COMSTL</a> binary components
 * and no need to compile <a href = "http://comstl.org/">COMSTL</a> implementation
 * files; <a href = "http://comstl.org/">COMSTL</a> is <b>100%</b> header-only!
 *
 * As with most of the <a href = "http://stlsoft.org/">STLSoft</a> sub-projects,
 * <a href = "http://comstl.org/">COMSTL</a> depends only on
 *
 * - Selected headers from the C standard library, such as  <code><b>wchar.h</b></code>
 * - Selected headers from the C++ standard library, such as <code><b>new</b></code>, <code><b>functional</b></code>
 * - Selected header files of the <a href = "http://stlsoft.org/">STLSoft</a> main project
 * - The header files particular to the technology area, in this case the COM library headers, such as <code><b>objbase.h</b></code>
 * - The binary (static and dynamic libraries) components particular to the technology area, in this case the COM libraries that ship with the operating system and your compiler(s)
 *
 * In addition, some parts of the libraries exhibit different behaviour when
 * translated in different contexts, such as with <code><b>_WIN32_DCOM</b></code>
 * defined, or with <code><b>iaccess.h</b></code> include. In <b><i>all</i></b>
 * cases the libraries function correctly in whatever context they are compiled.
 */

