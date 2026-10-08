
#include <stlsoft/stlsoft.h>

#include <cstdint>
#include <iomanip>
#include <iostream>
#include <limits>


#define DUMP_INTEGER_(t)                                    dump_integer<t>(#t, std::numeric_limits<t>::min(), std::numeric_limits<t>::max())



struct overloader
{
    static char const* real_type(signed short)              { return "signed short"; }
    static char const* real_type(unsigned short)            { return "unsigned short"; }
    static char const* real_type(signed int)                { return "signed int"; }
    static char const* real_type(unsigned int)              { return "unsigned int"; }
    static char const* real_type(signed long)               { return "signed long"; }
    static char const* real_type(unsigned long)             { return "unsigned long"; }
    static char const* real_type(signed long long)          { return "signed long long"; }
    static char const* real_type(unsigned long long)        { return "unsigned long long"; }
};

template <typename T>
void
dump_integer(
    char const* type_name
,   T const     min_value
,   T const     max_value
)
{
    ((void)&type_name);
    ((void)&min_value);
    ((void)&max_value);

    std::cout
        << std::setw(32)
        << type_name
        << " ("
        << std::setw(20)
        << overloader::real_type(T(0))
        << ") "
        << std::setw(2)
        << sizeof(T) * 8
        << " bits"
        << ": "
        << std::setw(21)
        << min_value
        << ", "
        << std::setw(21)
        << max_value
        << std::endl
        ;
    ;
}


int main(int /*argc*/, char* /*argv*/[])
{
    // built-ins
    {
        std::cout << "built-ins:" << std::endl;

        DUMP_INTEGER_(signed char);
        DUMP_INTEGER_(unsigned char);

        DUMP_INTEGER_(short);
        DUMP_INTEGER_(signed short);
        DUMP_INTEGER_(unsigned short);

        DUMP_INTEGER_(int);
        DUMP_INTEGER_(signed int);
        DUMP_INTEGER_(unsigned int);

        DUMP_INTEGER_(long);
        DUMP_INTEGER_(signed long);
        DUMP_INTEGER_(unsigned long);

        DUMP_INTEGER_(long long);
        DUMP_INTEGER_(signed long long);
        DUMP_INTEGER_(unsigned long long);
    }

    // std sized
    {
        std::cout << "std sized:" << std::endl;

        DUMP_INTEGER_(std::int8_t);
        DUMP_INTEGER_(std::uint8_t);

        DUMP_INTEGER_(std::int16_t);
        DUMP_INTEGER_(std::uint16_t);

        DUMP_INTEGER_(std::int32_t);
        DUMP_INTEGER_(std::uint32_t);

        DUMP_INTEGER_(std::int64_t);
        DUMP_INTEGER_(std::uint64_t);
    }

    // STLSoft sized
    {
        std::cout << "STLSoft sized:" << std::endl;

        DUMP_INTEGER_(stlsoft::sint8_t);
        DUMP_INTEGER_(stlsoft::uint8_t);

        DUMP_INTEGER_(stlsoft::sint16_t);
        DUMP_INTEGER_(stlsoft::uint16_t);

        DUMP_INTEGER_(stlsoft::sint32_t);
        DUMP_INTEGER_(stlsoft::uint32_t);

        DUMP_INTEGER_(stlsoft::sint64_t);
        DUMP_INTEGER_(stlsoft::uint64_t);
    }


    return 0;
}

