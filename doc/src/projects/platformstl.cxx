
/**
 * Created: 21st May 2006
 * Updated: 13th March 2007
 */


/** \defgroup group__project__platformstl PlatformSTL
 * \ingroup group__projects
 *
 * \brief &nbsp;&nbsp;&nbsp;&nbsp;Template Software for general operating systems.
 *
 * <img src="platformstl32x32.jpg" width="32" height="32" align="left" />
 *
 * The philosophy of PlatformSTL (http://platformstl.org/) is essentially the same as that
 * of the STLSoft (http://stlsoft.org/) organisation: providing robust and
 * lightweight software to the UNIX development
 * community. PlatformSTL provides template-based software that builds on that
 * provided by UNIX and STLSoft in order to reduce programmer effort and increase
 * robustness in the use of the UNIX.
 *
 * <b>Namespaces</b>
 *
 * The PlatformSTL namespace <code><b>platformstl</b></code> is actually an alias for the
 * namespace <code><b>stlsoft::platformstl_project</b></code>, and as such all the
 * PlatformSTL project components actually reside within the
 * <code><b>stlsoft</b></code> namespace. However, there is never any need to
 * use the <code><b>stlsoft::platformstl_project</b></code> namespace in your code,
 * and you should always use the alias <code><b>platformstl</b></code>.
 *
 * <b>Dependencies</b>
 *
 * As with <b><i>all</i></b> parts of the STLSoft libraries, there are no
 * dependencies on PlatformSTL binary components and no need to compile PlatformSTL
 * implementation files; PlatformSTL is <b>100%</b> header-only!
 *
 * As with most of the STLSoft sub-projects, PlatformSTL depends only on:
 *
 * - Selected headers from the C standard library, such as  <code><b>wchar.h</b></code>
 * - Selected headers from the C++ standard library, such as <code><b>new</b></code>, <code><b>functional</b></code>
 * - Selected header files of the STLSoft main project
 * - The header files particular to the technology area, in this case the UNIX library headers, such as <code><b>dirent.h</b></code>
 * - The binary (static and dynamic libraries) components particular to the technology area, in this case the UNIX libraries that ship with the operating system and your compiler(s)
 */

