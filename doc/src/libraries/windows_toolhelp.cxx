
/**
 * Created: 20th May 2006
 * Updated: 12th January 2017
 */

/** \defgroup group__library__Windows_Toolhelp Windows ToolHelp Library
 * \ingroup group__libraries
 *
 * \brief This library provides facilities for accessing system
 *  information via the Windows TOOLHELP API.
 *
 * The library provides facilities for enumerating process, thread,
 * module and heap information from the system:
 *
 * - The winstl::heap_sequence class is used to enumerate the heaps
 *    in a process.
 * - The winstl::module_sequence class is used to enumerate the modules
 *    in a process.
 * - The winstl::heap_sequence class is used to enumerate the processes
 *    in the system.
 * - The winstl::thread_sequence class is used to enumerate the processes
 *    in a process.
 *
 * \note The Windows ToolHelp library was written and kindly contributed by
 *  STLSoft-power user
 *  <a href = "http://www.geocities.com/pablo_aguilarg/">Pablo Aguilar</a>.
 */

/** \example by_library/windows_toolhelp/process_sequence/process_sequence.cpp
 * \brief [C++ only] Illustrates use of the
 *  \ref group__library__Windows_Toolhelp "Windows ToolHelp library"
 *  \link winstl::process_sequence process_sequence\endlink
 *  component.
 *
 * This function enumerates all the currently executing process on the
 * host system, and displays the process Id and the file name.
 */

/** \example by_library/windows_toolhelp/module_sequence/module_sequence.cpp
 * \brief [C++ only] Illustrates use of the
 *  \ref group__library__Windows_Toolhelp "Windows ToolHelp library"
 *  \link winstl::module_sequence module_sequence\endlink
 *  component.
 *
 * This function enumerates all the currently loaded modules in the
 * executing process, and displays the module handle and the file name.
 */

