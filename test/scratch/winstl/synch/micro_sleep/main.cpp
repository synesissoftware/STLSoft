

#include <winstl/synch/sleep_functions.h>

#include <winstl/conversion/number/grouping_functions.hpp>
#include <winstl/diagnostics/stopwatch.hpp>

#include <cstdlib>
#include <iomanip>
#include <iostream>


template <ss_typename_param_k T_integer>
std::string
as_thousands(
    T_integer const& v
)
{
    char            dest[101];
    size_t const    n   =   winstl::format_thousands(&dest[0], STLSOFT_NUM_ELEMENTS(dest), v);

    return std::string(dest, n);
}

std::string
percent(
    double const d
)
{
    char        dest[101];
    int const   n = std::snprintf(dest, sizeof(dest), "%.2f%%", d * 100.0);

    return std::string(dest, n);
}


int main(int /*argc*/, char* /*argv*/[])
{
    const unsigned DELAYS[] =
    {
        0
    ,   1
    ,   2
    ,   4
    ,   8
    ,   16
    ,   32
    ,   64
    ,   128
    ,   256
    ,   384
    ,   512
    ,   640
    ,   768
    ,   896
    ,   928
    ,   960
    ,   992
    ,   1000
    ,   1024
    ,   1056
    ,   1088
    ,   1216
    ,   1344
    ,   1472
    ,   1600
    ,   1800
    ,   2000
    ,   2250
    ,   2500
    ,   2750
    ,   3000
    ,   3250
    ,   3500
    ,   3750
    ,   4000
    ,   4500
    ,   5000
    ,   6000
    ,   7000
    ,   8000
    ,   9000
    ,   10000
    ,   11000
    ,   12000
    ,   13000
    ,   14000
    ,   15000
    ,   16000
    ,   17000
    ,   18000
    ,   19000
    ,   20000
    ,   22500
    ,   25000
    ,   27500
    ,   30000
    ,   35000
    ,   40000
    ,   55000
    ,   50000
    ,   55000
    ,   60000
    ,   65000
    ,   70000
    ,   75000
    ,   80000
    ,   85000
    ,   90000
    ,   95000
    ,   100000
    ,   110000
    ,   120000
    ,   130000
    ,   140000
    ,   150000
    ,   175000
    ,   200000
    ,   225000
    ,   250000
    ,   275000
    ,   300000
    ,   350000
    ,   400000
    ,   500000
    ,   600000
    ,   700000
    ,   800000
    ,   900000
    };

    winstl::stopwatch sw;

    for (int W = 2; 0 != W; --W)
    {
        for (unsigned i = 0; STLSOFT_NUM_ELEMENTS(DELAYS) != i; ++i)
        {
            unsigned const delay_us = DELAYS[i];

            if (1 == W)
            {
                std::cout
                    << as_thousands(delay_us)
                    << ':'
                    << std::endl;
            }

            for (unsigned j = 0; 5 != j; ++j)
            {
                sw.start();

                winstl::micro_sleep(delay_us);

                sw.stop();

                winstl::stopwatch::interval_type const duration_us = sw.get_microseconds();

                if (1 == W)
                {
                    winstl::stopwatch::interval_type const delta_us = duration_us - delay_us;

                    double const ratio = double(delta_us) / double(delay_us);

                    std::cout
                        << '\t'
                        << std::setw(12) << std::right << as_thousands(duration_us)
                        << '\t'
                        << std::setw(12) << std::right << std::showpos << as_thousands(delta_us)
                        << '\t'
                        << std::setw(8) << percent(ratio)
                        << std::endl;
                }
            }
        }
    }


    return EXIT_SUCCESS;
}

