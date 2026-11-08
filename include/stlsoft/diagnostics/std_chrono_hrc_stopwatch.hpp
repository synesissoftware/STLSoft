/* /////////////////////////////////////////////////////////////////////////
 * File:    stlsoft/diagnostics/std_chrono_hrc_stopwatch.hpp
 *
 * Purpose: stopwatch class based on std::chrono::high_resolution_clock.
 *
 * Created: 17th March 2024
 * Updated: 15th October 2026
 *
 * Home:    http://stlsoft.org/
 *
 * Copyright (c) 2024, Matthew Wilson and Synesis Information Systems
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


/* STLSOFT:C++98:FILE_EXCEPTED */
/* STLSOFT:C++03:FILE_EXCEPTED */

/** \file stlsoft/diagnostics/std_chrono_hrc_stopwatch.hpp
 *
 * \brief [C++] Definition of the
 *  \link stlsoft::stopwatch stopwatch\endlink class
 *   (\ref group__library__Diagnostic "Diagnostic" Library).
 */

#ifndef STLSOFT_INCL_STLSOFT_DIAGNOSTICS_HPP_STD_CHRONO_HRC_STOPWATCH
#define STLSOFT_INCL_STLSOFT_DIAGNOSTICS_HPP_STD_CHRONO_HRC_STOPWATCH

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define STLSOFT_VER_STLSOFT_DIAGNOSTICS_HPP_STD_CHRONO_HRC_STOPWATCH_MAJOR     1
# define STLSOFT_VER_STLSOFT_DIAGNOSTICS_HPP_STD_CHRONO_HRC_STOPWATCH_MINOR     1
# define STLSOFT_VER_STLSOFT_DIAGNOSTICS_HPP_STD_CHRONO_HRC_STOPWATCH_REVISION  1
# define STLSOFT_VER_STLSOFT_DIAGNOSTICS_HPP_STD_CHRONO_HRC_STOPWATCH_EDIT      6
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

#ifndef STLSOFT_INCL_CHRONO
# define STLSOFT_INCL_CHRONO
# include <chrono>
#endif /* !STLSOFT_INCL_CHRONO */


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

/** A stopwatch using \c std::chrono::high_resolution_clock
 *
 * \ingroup group__library__Diagnostic
 *
 * This class provides performance monitoring functionality based around
 * \c std::chrono::high_resolution_clock.
 */
class std_chrono_hrc_stopwatch
{
private: // types
    typedef std::chrono::high_resolution_clock              clock_type_;
public:
    /// The epoch type
    ///
    /// The type of the epoch measurement
    typedef std::chrono::time_point<
        clock_type_
    >                                                       epoch_type;
    /// The interval type
    ///
    /// The type of the interval measurement, a 64-bit signed integer
    typedef ss_sint64_t                                     interval_type;
    /// The class type
    typedef std_chrono_hrc_stopwatch                        class_type;

public: // construction
#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
    std_chrono_hrc_stopwatch() // This is needed only to suppress compiler warnings about unused variables
    {}
#endif /* !STLSOFT_DOCUMENTATION_SKIP_SECTION */

public: // Operations
    /// Starts measurement
    ///
    /// Begins the measurement period
    void    start();
    /// Pauses the measurement
    ///
    void    pause();
    /// Unpauses the measurement
    ///
    void    unpause();
    /// Ends measurement
    ///
    /// Ends the measurement period
    void    stop();
    /// Ends the current measurement period and start the next
    ///
    /// \note This is equivalent to an atomic invocation of stop() and
    ///   start().
    void    restart();

public: // attributes
    /// The current epoch
    static epoch_type       get_epoch();

    /// The number of whole seconds in the given measurement period
    static interval_type    get_seconds(epoch_type start, epoch_type end);
    /// The number of whole milliseconds in the given measurement period
    static interval_type    get_milliseconds(epoch_type start, epoch_type end);
    /// The number of whole microseconds in the given measurement period
    static interval_type    get_microseconds(epoch_type start, epoch_type end);
    /// The number of whole nanoseconds in the given measurement period
    static interval_type    get_nanoseconds(epoch_type start, epoch_type end);

    /// The elapsed count in the measurement period
    ///
    /// This represents the extent, in arbitrary units, of the measurement period
    interval_type   get_period_count() const;
    /// The number of whole seconds in the measurement period
    ///
    /// This represents the extent, in whole seconds, of the measurement period
    interval_type   get_seconds() const;
    /// The number of whole milliseconds in the measurement period
    ///
    /// This represents the extent, in whole milliseconds, of the measurement period
    interval_type   get_milliseconds() const;
    /// The number of whole microseconds in the measurement period
    ///
    /// This represents the extent, in whole microseconds, of the measurement period
    interval_type   get_microseconds() const;
    /// The number of whole nanoseconds in the measurement period
    ///
    /// This represents the extent, in whole nanoseconds, of the measurement period
    interval_type   get_nanoseconds() const;

    /// Stops the current period, starts the next, and returns the
    ///  period count for the prior period.
    interval_type   stop_get_period_count_and_restart();

    /// Stops the current period, starts the next, and returns the
    ///  interval, in seconds, for the prior period.
    interval_type   stop_get_seconds_and_restart();

    /// Stops the current period, starts the next, and returns the
    ///  interval, in milliseconds, for the prior period.
    interval_type   stop_get_milliseconds_and_restart();

    /// Stops the current period, starts the next, and returns the
    ///  interval, in microseconds, for the prior period.
    interval_type   stop_get_microseconds_and_restart();

    /// Stops the current period, starts the next, and returns the
    ///  interval, in nanoseconds, for the prior period.
    interval_type   stop_get_nanoseconds_and_restart();

private: // implementation

private: // fields
    /// Stores the start epoch
    epoch_type      m_start;
    /// Stores the end epoch
    epoch_type      m_end;
    /// Stores the pause epoch
    epoch_type      m_pause;
    /// Stores the (cumulate) pause time (in nanoseconds)
    interval_type   m_paused_ns;
/// @}
};

/* /////////////////////////////////////////////////////////////////////////
 * implementation
 */

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION

inline
void
std_chrono_hrc_stopwatch::start()
{
    m_start = clock_type_::now();

    m_end = m_start;
    m_paused_ns = 0;
}

inline
void
std_chrono_hrc_stopwatch::pause()
{
    m_pause = clock_type_::now();
}

inline
void
std_chrono_hrc_stopwatch::unpause()
{
    epoch_type now = clock_type_::now();

    m_paused_ns += std::chrono::duration_cast<std::chrono::nanoseconds>(now - m_pause).count();
}

inline
void
std_chrono_hrc_stopwatch::stop()
{
    m_end = clock_type_::now();
}

inline
void
std_chrono_hrc_stopwatch::restart()
{
    start();
}

inline
/* static */
std_chrono_hrc_stopwatch::epoch_type
std_chrono_hrc_stopwatch::get_epoch()
{
    return clock_type_::now();
}

inline
/* static */
std_chrono_hrc_stopwatch::interval_type
std_chrono_hrc_stopwatch::get_seconds(
    std_chrono_hrc_stopwatch::epoch_type   start
,   std_chrono_hrc_stopwatch::epoch_type   end
)
{
    STLSOFT_MESSAGE_ASSERT("end before start: stop() must be called after start()", start <= end);

    return std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
}

inline
/* static */
std_chrono_hrc_stopwatch::interval_type
std_chrono_hrc_stopwatch::get_milliseconds(
    std_chrono_hrc_stopwatch::epoch_type   start
,   std_chrono_hrc_stopwatch::epoch_type   end
)
{
    STLSOFT_MESSAGE_ASSERT("end before start: stop() must be called after start()", start <= end);

    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

inline
/* static */
std_chrono_hrc_stopwatch::interval_type
std_chrono_hrc_stopwatch::get_microseconds(
    std_chrono_hrc_stopwatch::epoch_type   start
,   std_chrono_hrc_stopwatch::epoch_type   end
)
{
    STLSOFT_MESSAGE_ASSERT("end before start: stop() must be called after start()", start <= end);

    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

inline
/* static */
std_chrono_hrc_stopwatch::interval_type
std_chrono_hrc_stopwatch::get_nanoseconds(
    std_chrono_hrc_stopwatch::epoch_type   start
,   std_chrono_hrc_stopwatch::epoch_type   end
)
{
    STLSOFT_MESSAGE_ASSERT("end before start: stop() must be called after start()", start <= end);

    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

inline
std_chrono_hrc_stopwatch::interval_type
std_chrono_hrc_stopwatch::get_period_count() const
{
    return get_nanoseconds();
}

inline
std_chrono_hrc_stopwatch::interval_type
std_chrono_hrc_stopwatch::get_seconds() const
{
    STLSOFT_MESSAGE_ASSERT("end before start: stop() must be called after start()", m_start <= m_end);

    interval_type r = std::chrono::duration_cast<std::chrono::seconds>(m_end - m_start).count();

    r -= m_paused_ns / (1000 * 1000 * 1000);

    return r;
}

inline
std_chrono_hrc_stopwatch::interval_type
std_chrono_hrc_stopwatch::get_milliseconds() const
{
    STLSOFT_MESSAGE_ASSERT("end before start: stop() must be called after start()", m_start <= m_end);

    interval_type r = std::chrono::duration_cast<std::chrono::milliseconds>(m_end - m_start).count();

    r -= m_paused_ns / (1000 * 1000);

    return r;
}

inline
std_chrono_hrc_stopwatch::interval_type
std_chrono_hrc_stopwatch::get_microseconds() const
{
    STLSOFT_MESSAGE_ASSERT("end before start: stop() must be called after start()", m_start <= m_end);

    interval_type r = std::chrono::duration_cast<std::chrono::microseconds>(m_end - m_start).count();

    r -= m_paused_ns / 1000;

    return r;
}

inline
std_chrono_hrc_stopwatch::interval_type
std_chrono_hrc_stopwatch::get_nanoseconds() const
{
    STLSOFT_MESSAGE_ASSERT("end before start: stop() must be called after start()", m_start <= m_end);

    interval_type r = std::chrono::duration_cast<std::chrono::nanoseconds>(m_end - m_start).count();

    r -= m_paused_ns;

    return r;
}

inline
std_chrono_hrc_stopwatch::interval_type
std_chrono_hrc_stopwatch::stop_get_period_count_and_restart()
{
    stop();

    interval_type interval = get_period_count();

    m_start = m_end;

    return interval;
}

inline
std_chrono_hrc_stopwatch::interval_type
std_chrono_hrc_stopwatch::stop_get_seconds_and_restart()
{
    stop();

    interval_type interval = get_seconds();

    m_start = m_end;

    return interval;
}

inline
std_chrono_hrc_stopwatch::interval_type
std_chrono_hrc_stopwatch::stop_get_milliseconds_and_restart()
{
    stop();

    interval_type interval = get_milliseconds();

    m_start = m_end;

    return interval;
}

inline
std_chrono_hrc_stopwatch::interval_type
std_chrono_hrc_stopwatch::stop_get_microseconds_and_restart()
{
    stop();

    interval_type interval = get_microseconds();

    m_start = m_end;

    return interval;
}

inline
std_chrono_hrc_stopwatch::interval_type
std_chrono_hrc_stopwatch::stop_get_nanoseconds_and_restart()
{
    stop();

    interval_type interval = get_nanoseconds();

    m_start = m_end;

    return interval;
}
#endif /* !STLSOFT_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#ifndef STLSOFT_NO_NAMESPACE
} // namespace stlsoft
#endif /* STLSOFT_NO_NAMESPACE */


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_CF_PRAGMA_ONCE_SUPPORT
# pragma once
#endif /* STLSOFT_CF_PRAGMA_ONCE_SUPPORT */

#endif /* !STLSOFT_INCL_STLSOFT_DIAGNOSTICS_HPP_STD_CHRONO_HRC_STOPWATCH */

/* ///////////////////////////// end of file //////////////////////////// */

