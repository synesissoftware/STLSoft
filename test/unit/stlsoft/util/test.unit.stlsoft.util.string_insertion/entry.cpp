/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.util.string_insertion/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft::string_insert`.
 *
 * Created: 14th November 2024
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/util/streams/string_insertion.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>
#include <stlsoft/conversion/integer_to_string/integer_to_decimal_string.hpp>
#include <stlsoft/conversion/integer_to_string/integer_to_hexadecimal_string.hpp>
#include <stlsoft/conversion/integer_to_string/integer_to_octal_string.hpp>

/* Standard C++ header files */
#include <iomanip>
#include <ios>
#include <sstream>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * types
 */

namespace stlsoft {

    inline
    int
    stream_flags_base(
        std::ios_base const& stm
    )
    {
        std::ios_base::fmtflags const flags = stm.flags();

        switch (flags & std::ios_base::basefield)
        {
        case std::ios_base::oct:

            return 8;
        case std::ios_base::hex:

            return 16;
        case std::ios_base::dec:

            return 10;
        default:

            return 0;
        }
    }

} // namespace stlsoft

namespace {

    using stlsoft::ss_uint32_t;

    struct CustomNumericType
    {
        ss_uint32_t v;
    };

    template <ss_typename_param_k T_stream>
    T_stream&
    operator <<(
        T_stream&                   stm
    ,   CustomNumericType const&    ct
    )
    {
        std::ios_base::fmtflags const   flags       =   stm.flags();
        int const                       base        =   stlsoft::stream_flags_base(stm);
        bool const                      show_base   =   0 != (std::ios_base::showbase & flags);
        bool const                      show_pos    =   0 != (std::ios_base::showpos & flags);
        bool const                      upper_case  =   0 != (std::ios_base::uppercase & flags);

        char        sz[24]; // 21 all numbers, 2 for base, 1 for +
        char const* s;
        size_t      n;

        switch (base)
        {
        default:

            s = &sz[0];
            n = 0;
            break;
        case 8:

            s = stlsoft::integer_to_octal_string(sz, STLSOFT_NUM_ELEMENTS(sz), ct.v, &n);

            if (show_base)
            {
                *const_cast<char*>(--s) = '0';
                ++n;
            }
            break;
        case 10:

            s = stlsoft::integer_to_decimal_string(sz, STLSOFT_NUM_ELEMENTS(sz), ct.v, &n);
            break;
        case 16:

            s = stlsoft::integer_to_hexadecimal_string(sz, STLSOFT_NUM_ELEMENTS(sz), ct.v, &n);

            if (show_base)
            {
                *const_cast<char*>(--s) = upper_case ? 'X' : 'x';
                ++n;

                *const_cast<char*>(--s) = '0';
                ++n;
            }
            break;
        }

        if (show_pos && ct.v >= 0)
        {
            *const_cast<char*>(--s) = '+';
            ++n;
        }

        STLSOFT_ASSERT(s >= &sz[0]);

        // stm << ct.v;

        stlsoft::util::string_insert(stm, s, n);

        return stm;
    }
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.util.string_insertion", verbosity))
    {
        XTESTS_RUN_CASE_WITH_NAME_AND_DESC("`CustomNumericType` (default)", "", [] {

            CustomNumericType ct = { 1234 };

            std::stringstream stm;

            stm
                << ct;

            TEST_MS_EQ("1234", stm.str());
        });

        XTESTS_RUN_CASE_WITH_NAME_AND_DESC("`CustomNumericType` (std::dec | std::showbase)", "", [] {

            CustomNumericType ct = { 1234 };

            std::stringstream stm;

            stm
                << std::dec
                << std::showbase
                << ct;

            TEST_MS_EQ("1234", stm.str());
        });

        XTESTS_RUN_CASE_WITH_NAME_AND_DESC("`CustomNumericType` (std::hex | std::showbase)", "", [] {

            CustomNumericType ct = { 1234 };

            std::stringstream stm;

            stm
                << std::hex
                << std::showbase
                << ct;

            TEST_MS_EQ("0x4d2", stm.str());
        });

        XTESTS_RUN_CASE_WITH_NAME_AND_DESC("`CustomNumericType` (std::hex | std::showbase | std::showpos)", "", [] {

            CustomNumericType ct = { 1234 };

            std::stringstream stm;

            stm
                << std::hex
                << std::showbase
                << std::showpos
                << ct;

            TEST_MS_EQ("+0x4d2", stm.str());
        });

        XTESTS_RUN_CASE_WITH_NAME_AND_DESC("`CustomNumericType` (std::oct | std::showbase | std::showpos)", "", [] {

            CustomNumericType ct = { 1234 };

            std::stringstream stm;

            stm
                << std::oct
                << std::showbase
                << std::showpos
                << ct;

            TEST_MS_EQ("+02322", stm.str());
        });


        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

