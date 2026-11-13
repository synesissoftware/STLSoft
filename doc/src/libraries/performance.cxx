
/**
 * Created: 22nd May 2006
 * Updated: 12th January 2017
 */

/** \defgroup group__library__Performance Performance Library
 * \ingroup group__libraries
 *
 * \brief This library contains classes that assist in the measurement
 *  of program performance.
 *
 * The library consists primarily of different performance counter
 * classes that are all structurally conformant about a single simple
 * interface. These including the following:
 *
 * - The unixstl::performance_counter class implements timing in terms
 *   of the UNIX ::<code>gettimeofday()</code> API function.
 * - The unixstl::processtimes_counter class implements timing in terms
 *   of the UNIX API function ::<code>getrusage()</code>, which
 *   provides timing information for a given process, rather than as
 *   elapsed time.
 * - The winstl::highperformance_counter class implements timing in terms
 *   of the Windows High Performance Counter function
 *   ::<code>QueryPerformanceCounter()</code>, which provides the highest
 *   possible accuracy of all timer functions provided by the Win32 API,
 *   but which is not guaranteed to be available on all Windows platforms.
 * - The winstl::multimedia_counter class implements timing in terms
 *   of the Windows Multimedia API function ::<code>timeGetTime()</code>.
 * - The winstl::processtimes_counter class implements timing in terms
 *   of the Windows API function ::<code>GetProcessTimes()</code>, which
 *   provides timing information for a given process, rather than as
 *   elapsed time.
 * - The winstl::threadtimes_counter class implements timing in terms
 *   of the Windows API function ::<code>GetThreadTimes()</code>, which
 *   provides timing information for a given thread, rather than as
 *   elapsed time.
 * - The winstl::tick_counter class implements timing in terms of the
 *   ::<code>GetTickCount()</code> function, which is guaranteed to be
 *   available on all Windows platforms and has a very low call cost, but
 *   has low resolution.
 * - The winstl::performance_counter class implements timing by
 *   attempting to use ::<code>QueryPerformanceCounter()</code> if
 *   available, otherwise defaulting to using ::<code>GetTickCount()</code>.
 *
 * \remarks A detailed discussion of the costs and benefits of the
 *  various Windows timing functions, and of the implementation of the
 *  \ref group__project__winstl "WinSTL" classes in the Performance library
 *  is given in the article: 
 *  <a href="http://www.windevnet.com/documents/win0305a/">Win32 Performance Measurement Options</a>,
 *  Matthew Wilson,
 *  <a href = "http://www.windevnet.com/">Windows Developer Network</a>,
 *  Volume 2 Number 5, May 2003.
 */

/** \example by_library/performance/performance/performance.cpp
 * \brief [C++ only] Illustrates use of the
 *  \ref group__library__Performance "Performance library"
 *  <code>performance_counter</code> component
 *  (unixstl::performance_counter for UNIX;
 *  winstl::performance_counter for Windows).
 *
 * This example demonstrates timing an interval and displaying the
 * interval elapsed times in seconds, milliseconds and microseconds.
 */

/** \example by_library/performance/processtimes_counter/processtimes_counter.cpp
 * \brief [C++ only] Illustrates use of the
 *  \ref group__library__Performance "Performance library"
 *  <code>processtimes_counter</code> component
 *  (unixstl::processtimes_counter for UNIX;
 *  winstl::processtimes_counter for Windows).
 *
 * This example demonstrates timing an interval comprising kernel and user
 * activity and displaying the interval elapsed times for both kernel and
 * user in seconds, milliseconds and microseconds.
 */



