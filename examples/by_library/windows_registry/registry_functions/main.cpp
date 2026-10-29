/* /////////////////////////////////////////////////////////////////////////
 * File:    examples/by_library/windows_registry/registry_functions/main.cpp
 *
 * Purpose: C++ example program demonstrating use of the Windows Registry
 *          library.
 *
 * Created: 22nd May 2006
 * Updated: 9th October 2024
 *
 * ////////////////////////////////////////////////////////////////////// */


/* WinSTL header files */
#include <winstl/registry/functions.hpp>
#include <winstl/error/error_desc.hpp>


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
    try
    {
        // 1. Pass NULL and 0 to elicit the required size.
        size_t  cchBuffer   =   0;
        LONG    res;

        res = winstl::reg_get_string_value(HKEY_CURRENT_USER, "Environment", static_cast<char*>(0), cchBuffer);

        // 2. Now create an instance of stlsoft::auto_buffer to
        // hold the value, based on the size elicited by the
        // previous call.
        stlsoft::auto_buffer<TCHAR>     buff(cchBuffer);

        // 3. Now call again, this time checking the return code
        cchBuffer   =   buff.size();
        res         =   winstl::reg_get_string_value(HKEY_CURRENT_USER, "Environment", &buff[0], cchBuffer);

        if (ERROR_SUCCESS == res)
        {
            // 3.a Print out the value, which will be nul-terminated
            cout << "The value is: " << buff.data() << endl;
        }
        else
        {
            // 3.b Display the error. (error_desc is a class that converts a
            // Win32 error code into the corresponding string, and for which
            // a stream insertion operator is defined, making it rather
            // convenient, as you can see.)
            cerr << "Failed to elicit value: " << winstl::error_desc(res) << endl;
        }

#if 0
        // / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /

        // NOTE: In a real system, the size of the value can change at any time,
        // including between the first call (which elicits the size) and the
        // second (which elicits the contents). (Yes, you may wonder at the sense
        // of a global information database that engenders race conditions!) Hence,
        // the return value of the second call should be checked for
        // ERROR_MORE_DATA, in which circumstance the buffer should be expanded
        // and the call repeated. The following #ifdef'd out code shows how this
        // could be implemented. It has a goto in it, which is why I've #ifdef'd
        // it out. (Too many people have a cow when they see a goto, which is a
        // fair enough response ...)

        // 3. Now call again, this time checking the return code
retry:
        cchBuffer   =   buff.size();
        res         =   winstl::reg_get_string_value(HKEY_CURRENT_USER, "Environment", &buff[0], cchBuffer);

        if (ERROR_SUCCESS == res)
        {
            // 3.a Print out the value, which will be nul-terminated
            cout << "The value is: " << buff.data() << endl;
        }
        else if (ERROR_MORE_DATA == res)
        {
            // 3.b Need to resize the buffer according to the latest (failed)
            // retrieval attempt.
            buff.resize(cchBuffer);
            goto retry;
        }
        else
        {
            // 3.c Display the error. (error_desc is a class that converts a
            // Win32 error code into the corresponding string, and for which
            // a stream insertion operator is defined, making it rather
            // convenient, as you can see.)
            cerr << "Failed to elicit value: " << winstl::error_desc(res) << endl;
        }

        // Of course, a for or a while loop would be best. As an exercise for
        // the reader, perhaps you might work out the minimum amount of code
        // that takes into account all the above behaviour, with only one call
        // site of reg_get_string_value(). ;-)

        // / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
#endif

        return EXIT_SUCCESS;
    }
    catch (std::exception& x)
    {
        fprintf(stderr, "Error: %s\n", x.what());

        return EXIT_FAILURE;
    }
    catch (...)
    {
        fprintf(stderr, "Unknown error\n");

        return EXIT_FAILURE;
    }
}


/* ///////////////////////////// end of file //////////////////////////// */

