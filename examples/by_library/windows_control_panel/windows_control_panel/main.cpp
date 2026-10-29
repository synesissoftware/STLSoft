/* /////////////////////////////////////////////////////////////////////////
 * File:    examples/by_library/windows_control_panel/windows_control_panel/main.cpp
 *
 * Purpose: C++ example program demonstrating use of the Windows Control
 *          Panel library.
 *
 * Created: 27th May 2006
 * Updated: 13th October 2024
 *
 * ////////////////////////////////////////////////////////////////////// */


/* WinSTL header files */
#include <winstl/filesystem/findfile_sequence.hpp>
#include <winstl/system/system_directory.hpp>
#include <winstl/control_panel/applet_module.hpp>

/* Standard C++ header files */
#include <iostream>


int main()
{
    using namespace winstl;

    try
    {
        system_directory    sysDir;
        findfile_sequence   files(sysDir, "*.cpl", findfile_sequence::files);

        { for (findfile_sequence::const_iterator b = files.begin(); b != files.end(); ++b)
        {
            try
            {
                applet_module am(*b, applet_module::dontExpectNonZeroInit);

                applet_module::const_iterator   b2 = am.begin();
                applet_module::const_iterator   e2 = am.end();

                std::cout << "path:          " << am.get_path() << std::endl;
                for (; b2 != e2; ++b2)
                {
                    applet const& applet = *b2;

                    std::cout << " applet index: " << applet.get_index() << std::endl;

                    std::cout << "  name:        " << applet.get_name() << std::endl;
                    std::cout << "  description: " << applet.get_description() << std::endl;
                }
                std::cout << std::endl;
            }
            catch (control_panel_exception& x)
            {
                //std::cout << "path:          " << am.get_path() << std::endl;
                std::cerr << "Exception: " << x.what() << std::endl;
            }

            std::cout << std::endl;
        }}
    }
    catch (std::exception& x)
    {
        std::cerr << "Exception: " << x.what() << std::endl;
    }

    return 0;
}


/* ///////////////////////////// end of file //////////////////////////// */

