/* /////////////////////////////////////////////////////////////////////////
 * File:    examples/by_library/diagnostics/stopwatch/main.cpp
 *
 * Purpose: C++ example program demonstrating use of the stopwatch type
 *          `platformstl::stopwatch` from the Performance library.
 *
 * Created: 22nd May 2006
 * Updated: 29th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* PlatformSTL header files */
#include <platformstl/diagnostics/stopwatch.hpp>
#include <platformstl/synch/sleep_functions.h>

/* Standard C++ header files */
#include <exception>
#include <iostream>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;

/* Standard C header files */
#include <stdlib.h> // for EXIT_FAILURE, EXIT_SUCCESS


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main()
{
    using platformstl::micro_sleep;
    using platformstl::stopwatch;
    using stlsoft::ss_sint64_t;

    const size_t            NUM_ITERATIONS      =   0x7fffffff;
    const stlsoft::uint_t   REPEATED_SLEEP_us   =   4;


    // simple interval
    {
        cout << "simple interval:" << endl;

        // 1. Create an instance of the platformstl::stopwatch. (On
        // UNIX this will resolve to unixstl::stopwatch; on Win32 it
        // will resolve to winstl::stopwatch.)
        stopwatch sw;

        // 2. Begin the measurement
        sw.start();

        // 3. A loop that will consume some time.
        { for (volatile size_t i = 0; i != NUM_ITERATIONS; )
        {
            size_t j = i;

            if (0 == (j % 1000))
            {
                micro_sleep(REPEATED_SLEEP_us);
            }

            i = ++j;
        }}

        // 4. End the measurement
        sw.stop();

        // 5. Display the number of whole seconds that have elapsed.
        cout << '\t' << "interval (s):  " << sw.get_seconds() << endl;
        // 6. Display the number of whole milliseconds that have elapsed.
        cout << '\t' << "interval (ms): " << sw.get_milliseconds() << endl;
        // 7. Display the number of whole microseconds that have elapsed.
        cout << '\t' << "interval (us): " << sw.get_microseconds() << endl;
        // 8. Display the number of whole nanoseconds that have elapsed.
        cout << '\t' << "interval (ns): " << sw.get_nanoseconds() << endl;
    }


    // manual sampling
    {
        cout << "manual sampling:" << endl;

        stopwatch::epoch_type   e1;
        stopwatch::epoch_type   e2;

        e1 = stopwatch::get_epoch();

        micro_sleep(12345);

        e2 = stopwatch::get_epoch();

        cout << '\t' << "interval (s):  " << stopwatch::get_seconds(e1, e2) << endl;
        cout << '\t' << "interval (ms): " << stopwatch::get_milliseconds(e1, e2) << endl;
        cout << '\t' << "interval (us): " << stopwatch::get_microseconds(e1, e2) << endl;
        cout << '\t' << "interval (ns): " << stopwatch::get_nanoseconds(e1, e2) << endl;
    }


    // interspersed sampling
    {
        cout << "interspersed sampling:" << endl;

        stopwatch sw;

        // 2. Begin the measurement
        sw.start();

        // 3. A loop that will consume some time.
        { for (volatile size_t i = 0; i != NUM_ITERATIONS; )
        {
            size_t j = i;

            if (0 == (j % 1000))
            {
                sw.pause();

                micro_sleep(REPEATED_SLEEP_us);

                sw.unpause();
            }

            i = ++j;
        }}

        // 4. End the measurement
        sw.stop();

        // 5. Display the number of whole seconds that have elapsed.
        cout << '\t' << "interval (s):  " << sw.get_seconds() << endl;
        // 6. Display the number of whole milliseconds that have elapsed.
        cout << '\t' << "interval (ms): " << sw.get_milliseconds() << endl;
        // 7. Display the number of whole microseconds that have elapsed.
        cout << '\t' << "interval (us): " << sw.get_microseconds() << endl;
        // 8. Display the number of whole nanoseconds that have elapsed.
        cout << '\t' << "interval (ns): " << sw.get_nanoseconds() << endl;
    }

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */

