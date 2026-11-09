/* /////////////////////////////////////////////////////////////////////////
 * File:    stlsoft/diagnostics/doomgram.hpp
 *
 * Purpose: Definition of the doomgram class.
 *
 * Created: 13th May 2013
 * Updated: 9th November 2026
 *
 * Home:    http://stlsoft.org/
 *
 * Copyright (c) 2019-2026, Matthew Wilson and Synesis Information Systems
 * Copyright (c) 2013-2019, Matthew Wilson and Synesis Software
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * - Neither the name(s) of Matthew Wilson and Synesis Information Systems
 *   nor the names of any contributors may be used to endorse or promote
 *   products derived from this software without specific prior written
 *   permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ////////////////////////////////////////////////////////////////////// */


/** \file stlsoft/diagnostics/doomgram.hpp
 *
 * \brief [C++] Definition of the doomgram class
 *   (\ref group__library__Diagnostic "Diagnostic" Library).
 */

#ifndef STLSOFT_INCL_STLSOFT_DIAGNOSTICS_HPP_DOOMGRAM
#define STLSOFT_INCL_STLSOFT_DIAGNOSTICS_HPP_DOOMGRAM

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define STLSOFT_VER_STLSOFT_DIAGNOSTICS_HPP_DOOMGRAM_MAJOR     2
# define STLSOFT_VER_STLSOFT_DIAGNOSTICS_HPP_DOOMGRAM_MINOR     0
# define STLSOFT_VER_STLSOFT_DIAGNOSTICS_HPP_DOOMGRAM_REVISION  2
# define STLSOFT_VER_STLSOFT_DIAGNOSTICS_HPP_DOOMGRAM_EDIT      36
#endif /* !STLSOFT_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#ifndef STLSOFT_INCL_STLSOFT_H_STLSOFT
# include <stlsoft/stlsoft.h>
#endif /* !STLSOFT_INCL_STLSOFT_H_STLSOFT */
#ifdef STLSOFT_TRACE_INCLUDE
# pragma message(__FILE__)
#endif /* STLSOFT_TRACE_INCLUDE */

#ifndef STLSOFT_INCL_STLSOFT_LIMITS_HPP_INTEGRAL_LIMITS
# include <stlsoft/limits/integral_limits.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_LIMITS_HPP_INTEGRAL_LIMITS */

#ifndef STLSOFT_INCL_STLSOFT_API_external_h_memfns
# include <stlsoft/api/external/memfns.h>
#endif /* !STLSOFT_INCL_STLSOFT_API_external_h_memfns */


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#ifndef STLSOFT_NO_NAMESPACE
namespace stlsoft
{
#endif /* STLSOFT_NO_NAMESPACE */


/* /////////////////////////////////////////////////////////////////////////
 * classes
 */

/** Decimal Order-Of-Magnitude frequency histoGRAM
 *
 * \ingroup group__library__Diagnostic
 *
 * This class is a specific frequency histogram operating over twelve
 * decimal orders of magnitude representing the timeslots of nanoseconds
 * (units, 10s, 100s), microseconds (units, 10s, 100s), milliseconds
 * (units, 10s, 100s), and seconds (units, 10s, 100s+).
 */
class doomgram
{
public: // types
    /// This type
    typedef doomgram                                        class_type;
    /// The integer type
    typedef ss_uint64_t                                     integer_type;
private:
    typedef integral_limits<integer_type>                   integral_limits_type;


public: // construction
    /// Constructs an instance
    doomgram() STLSOFT_NOEXCEPT;


public: // operations
    /// Pushes an event with the given number of nanoseconds
    bool push_event_time_ns(integer_type time_in_ns);
    /// Pushes an event with the given number of microseconds
    bool push_event_time_us(integer_type time_in_ms);
    /// Pushes an event with the given number of milliseconds
    bool push_event_time_ms(integer_type time_in_ms);
    /// Pushes an event with the given number of seconds
    bool push_event_time_s(integer_type time_in_ms);


public: // accessors
    /// Number of events counted
    integer_type event_count() const STLSOFT_NOEXCEPT;
    /// Attempts to obtain the total event time (in nanoseconds)
    ///
    /// \param value Pointer to variable to receive the value. May be
    ///  \c nullptr
    ///
    /// \retval true No overflow has occurred
    /// \retval false Overflow has occurred
    bool try_get_total_event_time_ns(integer_type* value) const STLSOFT_NOEXCEPT;
    /// Obtains the total event time (in nanoseconds), regardless of whether
    ///
    integer_type total_event_time_ns_raw() const STLSOFT_NOEXCEPT;
    /// Attempts to obtain the minimum event time (in nanoseconds)
    ///
    /// \param value Pointer to variable to receive the value. May not be
    ///  \c nullptr
    bool try_get_min_event_time_ns(integer_type* value) const STLSOFT_NOEXCEPT;
    /// Attempts to obtain the maximum event time (in nanoseconds)
    ///
    /// \param value Pointer to variable to receive the value. May not be
    ///  \c nullptr
    bool try_get_max_event_time_ns(integer_type* value) const STLSOFT_NOEXCEPT;
    /// Number of events counted in the interval [1ns, 10ns)
    integer_type num_events_in_1ns() const STLSOFT_NOEXCEPT;
    /// Number of events counted in the interval [10ns, 100ns)
    integer_type num_events_in_10ns() const STLSOFT_NOEXCEPT;
    /// Number of events counted in the interval [100ns, 1µs)
    integer_type num_events_in_100ns() const STLSOFT_NOEXCEPT;
    /// Number of events counted in the interval [1µs, 10µs)
    integer_type num_events_in_1us() const STLSOFT_NOEXCEPT;
    /// Number of events counted in the interval [10µs, 100µs)
    integer_type num_events_in_10us() const STLSOFT_NOEXCEPT;
    /// Number of events counted in the interval [100µs, 1ms)
    integer_type num_events_in_100us() const STLSOFT_NOEXCEPT;
    /// Number of events counted in the interval [1ms, 10ms)
    integer_type num_events_in_1ms() const STLSOFT_NOEXCEPT;
    /// Number of events counted in the interval [10ms, 100ms)
    integer_type num_events_in_10ms() const STLSOFT_NOEXCEPT;
    /// Number of events counted in the interval [100ms, 1s)
    integer_type num_events_in_100ms() const STLSOFT_NOEXCEPT;
    /// Number of events counted in the interval [1s, 10s)
    integer_type num_events_in_1s() const STLSOFT_NOEXCEPT;
    /// Number of events counted in the interval [10s, 100s)
    integer_type num_events_in_10s() const STLSOFT_NOEXCEPT;
    /// Number of events counted in the interval [100s, ∞)
    integer_type num_events_ge_100s() const STLSOFT_NOEXCEPT;

    /// Indicates whether overflow has occurred
    bool has_overflowed() const STLSOFT_NOEXCEPT;


private: // implementation
    // Returns false if overflowed
    bool try_add_ns_to_total_and_update_minmax_and_count_(integer_type time_in_ns);


private: // fields
    integer_type    m_event_count;
    integer_type    m_total_event_time_ns;
    integer_type    m_min_event_time_ns;
    integer_type    m_max_event_time_ns;
#if 0

    integer_type    m_num_event_times[12]];
#else

    integer_type    m_num_events_in_1ns;
    integer_type    m_num_events_in_10ns;
    integer_type    m_num_events_in_100ns;
    integer_type    m_num_events_in_1us;
    integer_type    m_num_events_in_10us;
    integer_type    m_num_events_in_100us;
    integer_type    m_num_events_in_1ms;
    integer_type    m_num_events_in_10ms;
    integer_type    m_num_events_in_100ms;
    integer_type    m_num_events_in_1s;
    integer_type    m_num_events_in_10s;
    integer_type    m_num_events_ge_100s;
#endif
    bool            m_has_overflowed;
};


/* /////////////////////////////////////////////////////////////////////////
 * implementation
 */

// implementation

inline
bool
doomgram::try_add_ns_to_total_and_update_minmax_and_count_(
    integer_type time_in_ns
)
{
    integer_type const new_total_event_time_ns = time_in_ns + m_total_event_time_ns;

    if (new_total_event_time_ns < m_total_event_time_ns)
    {
        m_has_overflowed = true;

        return false;
    }
    else
    {
        m_total_event_time_ns = new_total_event_time_ns;

        ++m_event_count;

        if (time_in_ns < m_min_event_time_ns)
        {
            m_min_event_time_ns = time_in_ns;
        }

        if (time_in_ns > m_max_event_time_ns)
        {
            m_max_event_time_ns = time_in_ns;
        }

        return true;
    }
}


// construction

inline
doomgram::doomgram() STLSOFT_NOEXCEPT
    // : // no MILs because using `memset()` (see ctor body)
{
    // TODO: replace with `STLSOFT_API_EXTERNAL_memfns_memset()` when available
    STLSOFT_API_EXTERNAL_memfns_memset(this, 0, sizeof(*this));

    m_min_event_time_ns = integral_limits_type::maximum();
    m_max_event_time_ns = integral_limits_type::minimum();
}


// operations

inline
bool
doomgram::push_event_time_ns(
    integer_type time_in_ns
)
{
    STLSOFT_MESSAGE_ASSERT("timing stack has overflowed and no further events may be pushed", !m_has_overflowed);

    if (!try_add_ns_to_total_and_update_minmax_and_count_(time_in_ns))
    {
        return false;
    }
    else
    {
        // Algorithm:
        //
        // We assume that most events will be down in the sub-1ms range, so
        // branch accordingly.

        if (0 != (time_in_ns & ~0x3FFFFFFF))
        {
            goto gt_1073741823;
        }

        if (time_in_ns >= 1000000)
        {


            // >= 1ms

            if (time_in_ns >= 1000000000)
            {
gt_1073741823:

                // >= 1s

                if (time_in_ns >= 100000000000)
                {
                    m_num_events_ge_100s += 1;
                }
                else if (time_in_ns >= 10000000000)
                {
                    m_num_events_in_10s += 1;
                }
                else
                {
                    m_num_events_in_1s += 1;
                }
            }
            else
            {
                // < 1s

                if (time_in_ns >= 100000000)
                {
                    m_num_events_in_100ms += 1;
                }
                else if (time_in_ns >= 10000000)
                {
                    m_num_events_in_10ms += 1;
                }
                else
                {
                    m_num_events_in_1ms += 1;
                }
            }
        }
        else
        {
            // < 1ms

            if (time_in_ns >= 1000)
            {
                // >= 1µs

                if (time_in_ns >= 100000)
                {
                    m_num_events_in_100us += 1;
                }
                else if (time_in_ns >= 10000)
                {
                    m_num_events_in_10us += 1;
                }
                else
                {
                    m_num_events_in_1us += 1;
                }
            }
            else
            {

                // < 1µs

                if (time_in_ns >= 100)
                {
                    m_num_events_in_100ns += 1;
                }
                else if (time_in_ns >= 10)
                {
                    m_num_events_in_10ns += 1;
                }
                else if (time_in_ns >= 1)
                {
                    m_num_events_in_1ns += 1;
                }
            }
        }

        return true;
    }
}

inline
bool
doomgram::push_event_time_us(
    integer_type time_in_us
)
{
    // TODO: implement separately, since already know µs

    integer_type const time_in_ns = time_in_us * 1000;

    if (!try_add_ns_to_total_and_update_minmax_and_count_(time_in_ns))
    {
        return false;
    }
    else
    {
        // possible slots:
        //
        // - 1µs
        // - 10µs
        // - 100µs
        // - 1ms
        // - 10ms
        // - 100ms
        // - 1s
        // - 10s
        // - 100s

        if (0 != (time_in_us & ~0xfffff))
        {
            goto ge_fffff;
        }

        if (time_in_us < 1000000)
        {
            if (time_in_us < 1000)
            {
                if (time_in_us >= 100)
                {
                    m_num_events_in_100us += 1;
                }
                else if (time_in_us >= 10)
                {
                    m_num_events_in_10us += 1;
                }
                else if (time_in_us >= 1)
                {
                    m_num_events_in_1us += 1;
                }
            }
            else
            {
                // 1s+

                if (time_in_us >= 100000)
                {
                    m_num_events_in_100ms += 1;
                }
                else if (time_in_us >= 10000)
                {
                    m_num_events_in_10ms += 1;
                }
                else
                {
                    m_num_events_in_1ms += 1;
                }
            }
        }
        else
        {
ge_fffff:

            if (time_in_us >= 100000000)
            {
                m_num_events_ge_100s += 1;
            }
            else if (time_in_us >= 10000000)
            {
                m_num_events_in_10s += 1;
            }
            else // if (time_in_us != 0)
            {
                m_num_events_in_1s += 1;
            }
        }

        return true;
    }
}

inline
bool
doomgram::push_event_time_ms(
    integer_type time_in_ms
)
{
    integer_type const time_in_ns = time_in_ms * 1000000;

    if (!try_add_ns_to_total_and_update_minmax_and_count_(time_in_ns))
    {
        return false;
    }
    else
    {
        // possible slots:
        //
        // - 1ms
        // - 10ms
        // - 100ms
        // - 1s
        // - 10s
        // - 100s

        if (0 != (time_in_ms & ~0x1ffff))
        {
            goto ge_1ffff;
        }

        if (time_in_ms < 1000)
        {
            if (time_in_ms >= 100)
            {
                m_num_events_in_100ms += 1;
            }
            else if (time_in_ms >= 10)
            {
                m_num_events_in_10ms += 1;
            }
            else if (time_in_ms >= 1)
            {
                m_num_events_in_1ms += 1;
            }
        }
        else
        {
            // 1s+

            if (time_in_ms >= 100000)
            {
ge_1ffff:

                m_num_events_ge_100s += 1;
            }
            else if (time_in_ms >= 10000)
            {
                m_num_events_in_10s += 1;
            }
            else
            {
                m_num_events_in_1s += 1;
            }
        }

        return true;
    }
}

inline
bool
doomgram::push_event_time_s(
    integer_type time_in_s
)
{
    integer_type const time_in_ns = time_in_s * 1000000000;

    if (!try_add_ns_to_total_and_update_minmax_and_count_(time_in_ns))
    {
        return false;
    }
    else
    {
        if (time_in_s >= 100)
        {
            m_num_events_ge_100s += 1;
        }
        else if (time_in_s >= 10)
        {
            m_num_events_in_10s += 1;
        }
        else if (time_in_s >= 1)
        {
            m_num_events_in_1s += 1;
        }

        return true;
    }
}


// accessors

inline
doomgram::integer_type
doomgram::event_count() const STLSOFT_NOEXCEPT
{
	return m_event_count;
}

inline
bool
doomgram::try_get_total_event_time_ns(
    integer_type* value
) const STLSOFT_NOEXCEPT
{
    if (ss_nullptr_k != value)
    {
        *value = m_total_event_time_ns;
    }

    return !m_has_overflowed;
}

inline
doomgram::integer_type
doomgram::total_event_time_ns_raw() const STLSOFT_NOEXCEPT
{
	return m_total_event_time_ns;
}

inline
bool
doomgram::try_get_min_event_time_ns(
    integer_type* value
) const STLSOFT_NOEXCEPT
{
    STLSOFT_ASSERT(ss_nullptr_k != value);

    if (0 != m_event_count)
    {
        *value = m_min_event_time_ns;

        return true;
    }
    else
    {
        *value = 0;

        return false;
    }
}

inline
bool
doomgram::try_get_max_event_time_ns(
    integer_type* value
) const STLSOFT_NOEXCEPT
{
    STLSOFT_ASSERT(ss_nullptr_k != value);

    if (0 != m_event_count)
    {
        *value = m_max_event_time_ns;

        return true;
    }
    else
    {
        *value = 0;

        return false;
    }
}

inline
doomgram::integer_type
doomgram::num_events_in_1ns() const STLSOFT_NOEXCEPT
{
	return m_num_events_in_1ns;
}

inline
doomgram::integer_type
doomgram::num_events_in_10ns() const STLSOFT_NOEXCEPT
{
	return m_num_events_in_10ns;
}

inline
doomgram::integer_type
doomgram::num_events_in_100ns() const STLSOFT_NOEXCEPT
{
	return m_num_events_in_100ns;
}

inline
doomgram::integer_type
doomgram::num_events_in_1us() const STLSOFT_NOEXCEPT
{
	return m_num_events_in_1us;
}

inline
doomgram::integer_type
doomgram::num_events_in_10us() const STLSOFT_NOEXCEPT
{
	return m_num_events_in_10us;
}

inline
doomgram::integer_type
doomgram::num_events_in_100us() const STLSOFT_NOEXCEPT
{
	return m_num_events_in_100us;
}

inline
doomgram::integer_type
doomgram::num_events_in_1ms() const STLSOFT_NOEXCEPT
{
	return m_num_events_in_1ms;
}

inline
doomgram::integer_type
doomgram::num_events_in_10ms() const STLSOFT_NOEXCEPT
{
	return m_num_events_in_10ms;
}

inline
doomgram::integer_type
doomgram::num_events_in_100ms() const STLSOFT_NOEXCEPT
{
	return m_num_events_in_100ms;
}

inline
doomgram::integer_type
doomgram::num_events_in_1s() const STLSOFT_NOEXCEPT
{
	return m_num_events_in_1s;
}

inline
doomgram::integer_type
doomgram::num_events_in_10s() const STLSOFT_NOEXCEPT
{
	return m_num_events_in_10s;
}

inline
doomgram::integer_type
doomgram::num_events_ge_100s() const STLSOFT_NOEXCEPT
{
	return m_num_events_ge_100s;
}

inline
bool
doomgram::has_overflowed() const STLSOFT_NOEXCEPT
{
    return m_has_overflowed;
}


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#ifndef STLSOFT_NO_NAMESPACE
} // namespace stlsoft
#endif /* STLSOFT_NO_NAMESPACE */


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_PPF_pragma_message_SUPPORT
# pragma once
#endif /* STLSOFT_PPF_pragma_message_SUPPORT */

#endif /* !STLSOFT_INCL_STLSOFT_DIAGNOSTICS_HPP_DOOMGRAM */

/* ///////////////////////////// end of file //////////////////////////// */

