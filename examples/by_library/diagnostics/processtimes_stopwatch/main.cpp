/* /////////////////////////////////////////////////////////////////////////
 * File:    examples/by_library/diagnostics/processtimes_stopwatch/main.cpp
 *
 * Purpose: C++ example program demonstrating use of the Diagnostics
 *          library's processtimes_stopwatch component.
 *
 * Created: 9th June 2006
 * Updated: 29th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* PlatformSTL header files */
#include <platformstl/diagnostics/stopwatch.hpp>
#include <platformstl/diagnostics/processtimes_stopwatch.hpp>
#include <platformstl/synch/sleep_functions.h>

/* Standard C++ header files */
#include <exception>
#include <iostream>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;

/* Standard C header files */
#include <stdio.h>
#include <stdlib.h> // for EXIT_FAILURE, EXIT_SUCCESS


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main()
{
    using platformstl::micro_sleep;
    using platformstl::processtimes_stopwatch;
    using platformstl::stopwatch;
    using stlsoft::ss_sint64_t;


    // simple interval
    {
        cout << "simple interval:" << endl;

        // 1.a. Create an instance of the platformstl::processtimes_stopwatch. (On
        // UNIX this will resolve to unixstl::processtimes_stopwatch; on Win32 it
        // will resolve to winstl::processtimes_stopwatch.)
        processtimes_stopwatch usageCounter;
        // 1.b. Create an instance of the platformstl::stopwatch that
        // will be used to measure the elapsed times.
        stopwatch              sw;

        // 2. Begin the measurement
        usageCounter.start();
        sw.start();

        // 3.a. A loop that will consume some user time.
        { for (volatile size_t i = 0; i != 0x1fffffff; )
        {
            size_t j = i;

            i = ++j;
        }}
        // 3.b. A loop that will consume some kernel time.
        { for (volatile size_t i = 0; i != 0x1ffff; )
        {
            size_t j = i;
            i = ++j;

            fprintf(stdout, " \b");
        }}
        // 3.c. A sleep, for five seconds, to separate elapsed and usage times.
        micro_sleep(5 * 1000 * 1000);

        // 4. End the measurement
        usageCounter.stop();
        sw.stop();

        // 5.a. Display the number of whole seconds of elapsed time
        cout << '\t' << "elapsed interval (s):  " << sw.get_seconds() << endl;
        // 6.a. Display the number of whole milliseconds of user time.
        cout << '\t' << "elapsed interval (ms): " << sw.get_milliseconds() << endl;
        // 7.a. Display the number of whole microseconds of user time.
        cout << '\t' << "elapsed interval (us): " << sw.get_microseconds() << endl;
        // 8.a. Display the number of whole nanoseconds of user time.
        cout << '\t' << "elapsed interval (ns): " << sw.get_nanoseconds() << endl;

        // 5.b. Display the number of whole seconds of user time.
        cout << '\t' << "user interval (s):     " << usageCounter.get_user_seconds() << endl;
        // 6.b. Display the number of whole milliseconds of user time.
        cout << '\t' << "user interval (ms):    " << usageCounter.get_user_milliseconds() << endl;
        // 7.b. Display the number of whole microseconds of user time.
        cout << '\t' << "user interval (us):    " << usageCounter.get_user_microseconds() << endl;
        // 8.b. Display the number of whole nanoseconds of user time.
        cout << '\t' << "user interval (ns):    " << usageCounter.get_user_nanoseconds() << endl;

        // 5.c. Display the number of whole seconds of kernel time.
        cout << '\t' << "kernel interval (s):   " << usageCounter.get_kernel_seconds() << endl;
        // 6.c. Display the number of whole milliseconds of kernel time.
        cout << '\t' << "kernel interval (ms):  " << usageCounter.get_kernel_milliseconds() << endl;
        // 7.c. Display the number of whole microseconds of kernel time.
        cout << '\t' << "kernel interval (us):  " << usageCounter.get_kernel_microseconds() << endl;
        // 8.c. Display the number of whole nanoseconds of kernel time.
        cout << '\t' << "kernel interval (ns):  " << usageCounter.get_kernel_nanoseconds() << endl;
    }

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */

