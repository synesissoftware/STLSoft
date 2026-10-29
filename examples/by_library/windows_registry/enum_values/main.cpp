/* /////////////////////////////////////////////////////////////////////////
 * File:    examples/by_library/windows_registry/enum_values/main.cpp
 *
 * Purpose: C++ example program demonstrating use of the Windows Registry
 *          library.
 *
 * Created: 22nd May 2006
 * Updated: 29th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* WinSTL header files */
#include <winstl/registry/reg_value_sequence.hpp>

#include <stlsoft/iterators/ostream_iterator.hpp>
#include <stlsoft/string/string_tokeniser.hpp>

/* Standard C++ header files */
#include <algorithm>
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
        cout    << "This program demonstrates use of the basic_reg_value_sequence" << endl
                << " class template by enumerating all the values of the environment" << endl
                << " for the current user." << endl;

        // 1. Construct an instance of reg_value_sequence (=== basic_reg_value_sequence<TCHAR>),
        // passing the hive root key (HKEY_CURRENT_USER) and the name of the key whose values
        // will be enumerated.
        winstl::reg_value_sequence  values(HKEY_CURRENT_USER, "Environment");

        // 2. Declare (and instantiate) iterators, since we're going to be using a
        // manual loop for manipulation of the sequence.
        winstl::reg_value_sequence::const_iterator  b   =   values.begin();
        winstl::reg_value_sequence::const_iterator  e   =   values.end();
        size_t                                      n;

        // 3. Enumerate through each element in turn.
        for (n = 0; b != e; ++b, ++n)
        {
            // 3.a. Print the name. Can use the value as a temporary (*b), ...
            cout << "\t" << (*b).name();

            // ... or create an instance of reg_value (=== basic_reg_value<TCHAR>)
            winstl::reg_value       val(*b);
            winstl::reg_string_t    value   =   val.value_sz();

            // 3.b. Test if it's a ; delimited path list.

            if (value.end() == std::find(value.begin(), value.end(), ';'))
            {
                // 3.b.1 It is not, so we just print it out as is. However,
                // it may contain an environment variable (e.g. "%USERPROFILE%\\Temp)
                // in which case we want to also print its actual value, using
                // the value_expand_sz() method.

                if (value.end() == std::find(value.begin(), value.end(), '%'))
                {
                    cout << "=" << value << endl;
                }
                else
                {
                    cout << "=" << value << " => " << val.value_expand_sz() << endl;
                }
            }
            else
            {
                // 3.b.2 It is a path list, so we now tokenise the value using
                // stlsoft::string_tokeniser ...
                stlsoft::string_tokeniser<winstl::reg_string_t, TCHAR>  tokens(value, ';');

                // ... and then print out all the tokens, in an indented list.
                cout << endl;
                std::copy(tokens.begin(), tokens.end()
                        , stlsoft::ostream_iterator<winstl::reg_string_t>(cout, "\t\t", "\n"));
            }

        }

        cout << "  " << n << " value(s)" << endl;

        return EXIT_SUCCESS;
    }
    catch (std::exception& x)
    {
        cerr << "Error: " << x.what() << endl;

        return EXIT_FAILURE;
    }
    catch (...)
    {
        cerr << "Unknown error" << endl;

        return EXIT_FAILURE;
    }
}


/* ///////////////////////////// end of file //////////////////////////// */

