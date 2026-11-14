/* /////////////////////////////////////////////////////////////////////////
 * File:    test/component/winstl/synch/spin_mutex/entry.cpp
 *
 * Purpose: Component test for `winstl::spin_mutex`.
 *
 * Created: sometime in 2015
 * Updated: 14th November 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* ///////////////////////////////////////////////
 * test component header file include(s)
 */

#include <winstl/synch/spin_mutex.hpp>

/* ///////////////////////////////////////////////
 * compatibility
 */

#if 1 &&\
    !defined(_INC_WINDOWS) &&\
    !defined(_WINDOWS_H) &&\
    1
# error <windows.h> is not included
#endif

/* ///////////////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <winstl/synch/event.hpp>
#include <stlsoft/meta/is_integral_type.hpp>
#include <stlsoft/smartptr/scoped_lambda.hpp>
#include <stlsoft/synch/lock_scope.hpp>

/* Standard C++ header files */
#include <thread>

/* Standard C header files */
#include <stdint.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_1_0();
    static void TEST_TYPES_EXIST();
    static void TEST_TYPES_HAVE_EXPECTED_ATTRIBUTES();
    static void TEST_SPIN_MUTEX_CAN_BE_LOCKED_AND_UNLOCKED();
    static void TEST_SPIN_MUTEX_CAN_BE_LOCKED_AND_UNLOCKED_WITH_LOCK_SCOPE();
    static void TEST_SPIN_MUTEX_CAN_BE_LOCKED_IN_THE_MAIN_THREAD_AND_UNLOCKED_IN_A_WORKER_THREAD();
    static void TEST_SPIN_MUTEX32_CAN_BE_LOCKED_AND_UNLOCKED();
    static void TEST_SPIN_MUTEX32_CAN_BE_LOCKED_AND_UNLOCKED_WITH_LOCK_SCOPE();
    static void TEST_SPIN_MUTEX32_CAN_BE_LOCKED_IN_THE_MAIN_THREAD_AND_UNLOCKED_IN_A_WORKER_THREAD();
    static void TEST_WITH_SPECIFIC_POLICY();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.winstl.synch.spin_mutex", verbosity))
    {
        XTESTS_RUN_CASE(TEST_1_0);
        XTESTS_RUN_CASE(TEST_TYPES_EXIST);
        XTESTS_RUN_CASE(TEST_TYPES_HAVE_EXPECTED_ATTRIBUTES);
        XTESTS_RUN_CASE(TEST_SPIN_MUTEX_CAN_BE_LOCKED_AND_UNLOCKED);
        XTESTS_RUN_CASE(TEST_SPIN_MUTEX_CAN_BE_LOCKED_AND_UNLOCKED_WITH_LOCK_SCOPE);
        XTESTS_RUN_CASE(TEST_SPIN_MUTEX_CAN_BE_LOCKED_IN_THE_MAIN_THREAD_AND_UNLOCKED_IN_A_WORKER_THREAD);
        XTESTS_RUN_CASE(TEST_SPIN_MUTEX32_CAN_BE_LOCKED_AND_UNLOCKED);
        XTESTS_RUN_CASE(TEST_SPIN_MUTEX32_CAN_BE_LOCKED_AND_UNLOCKED_WITH_LOCK_SCOPE);
        XTESTS_RUN_CASE(TEST_SPIN_MUTEX32_CAN_BE_LOCKED_IN_THE_MAIN_THREAD_AND_UNLOCKED_IN_A_WORKER_THREAD);
        XTESTS_RUN_CASE(TEST_WITH_SPECIFIC_POLICY);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * types
 */

namespace {

    struct specific_policy
    {
    public: // types
        typedef stlsoft::ss_sint32_t                            ss_sint32_t;
        typedef stlsoft::ss_truthy_t                            ss_truthy_t;
        typedef winstl::atomic_int_t                            atomic_int_type;

    public: // operations
        static
        ss_truthy_t
        try_acquire_lock(
            void*                        /* yieldContext */
        ,   atomic_int_type volatile*       spinCount
        ,   ss_sint32_t                  /* spunCount */
        )
        {
            return 0 == winstl::atomic_write(spinCount, 1);
        }
        static
        void
        on_spin(
            void*                           yieldContext
        ,   ss_sint32_t                     spunCount
        )
        {
            if (1000 == spunCount)
            {
                static_cast<winstl::event*>(yieldContext)->set();
            }
        }
        static
        void
        on_acquire(
            void*                        /* yieldCount */
        ,   ss_sint32_t                  /* spunCount */
        ,   ss_sint32_t                     cLocks
        )
        {
#ifdef WINSTL_SPINMUTEX_COUNT_LOCKS
            WINSTL_ASSERT(0 < cLocks);
#else
            STLSOFT_SUPPRESS_UNUSED(cLocks);
#endif
        }
        static
        void
        release_lock(
            void*                        /* yieldContext */
        ,   atomic_int_type volatile*       spinCount
        ,   ss_sint32_t                  /* spunCount */
        ,   ss_sint32_t                     cLocks
        )
        {
#ifdef WINSTL_SPINMUTEX_COUNT_LOCKS
            WINSTL_ASSERT(0 < cLocks);
#else
            STLSOFT_SUPPRESS_UNUSED(cLocks);
#endif

            winstl::atomic_write(spinCount, 0);
        }
        static
        void
        on_destroy(
            void*                        /* yieldCount */
        ,   ss_sint32_t                  /* spunCount */
        ,   ss_sint32_t                     cLocks
        )
        {
#ifdef WINSTL_SPINMUTEX_COUNT_LOCKS
            WINSTL_ASSERT(0 == cLocks);
#else
            STLSOFT_SUPPRESS_UNUSED(cLocks);
#endif
        }
    };
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * helpers
 */

namespace {

} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

    static void TEST_1_0()
    {
    }

    static void TEST_TYPES_EXIST()
    {
        STLSOFT_SUPPRESS_UNUSED(typeid(winstl::spin_mutex));
        STLSOFT_SUPPRESS_UNUSED(typeid(winstl::spin_mutex_no_yield));
        STLSOFT_SUPPRESS_UNUSED(typeid(winstl::spin_mutex32));

        TEST_PASSED();
    }

    static void TEST_TYPES_HAVE_EXPECTED_ATTRIBUTES()
    {
        static_assert(stlsoft::is_integral_type<winstl::spin_mutex::atomic_int_type>::value, "spin_mutex type must have integral atomic type");
        static_assert(stlsoft::is_integral_type<winstl::spin_mutex32::atomic_int_type>::value, "spin_mutex32 type must have integral atomic type");

        TEST_PASSED();
    }

    static void TEST_SPIN_MUTEX_CAN_BE_LOCKED_AND_UNLOCKED()
    {
        winstl::spin_mutex mx;

        mx.lock();

        TEST_PASSED();

        mx.unlock();

        TEST_PASSED();
    }

    static void TEST_SPIN_MUTEX_CAN_BE_LOCKED_AND_UNLOCKED_WITH_LOCK_SCOPE()
    {
        winstl::spin_mutex mx;

        {
            stlsoft::lock_scope<winstl::spin_mutex> lock(mx);

            TEST_PASSED();
        }

        TEST_PASSED();
    }

    static void TEST_SPIN_MUTEX_CAN_BE_LOCKED_IN_THE_MAIN_THREAD_AND_UNLOCKED_IN_A_WORKER_THREAD()
    {
        winstl::spin_mutex mx;

        mx.lock();

        TEST_PASSED();

        bool locked = true;

        std::thread thread([&locked, &mx] { mx.unlock(); locked = false; });

        TEST_PASSED();

        thread.join();

        TEST_BOOLEAN_FALSE(locked);
    }

    static void TEST_SPIN_MUTEX32_CAN_BE_LOCKED_AND_UNLOCKED()
    {
        winstl::spin_mutex32 mx;

        mx.lock();

        TEST_PASSED();

        mx.unlock();

        TEST_PASSED();
    }

    static void TEST_SPIN_MUTEX32_CAN_BE_LOCKED_AND_UNLOCKED_WITH_LOCK_SCOPE()
    {
        winstl::spin_mutex32 mx;

        {
            stlsoft::lock_scope<winstl::spin_mutex32> lock(mx);

            TEST_PASSED();
        }

        TEST_PASSED();
    }

    static void TEST_SPIN_MUTEX32_CAN_BE_LOCKED_IN_THE_MAIN_THREAD_AND_UNLOCKED_IN_A_WORKER_THREAD()
    {
        winstl::spin_mutex32 mx;

        mx.lock();

        TEST_PASSED();

        bool locked = true;

        std::thread thread([&locked, &mx] { mx.unlock(); locked = false; });

        TEST_PASSED();

        thread.join();

        TEST_BOOLEAN_FALSE(locked);
    }

    static void TEST_WITH_SPECIFIC_POLICY()
    {
        winstl::event ev_start(true, false);
        winstl::event ev_stop(true, false);

        stlsoft::spin_mutex_base<specific_policy> mx(NULL, &ev_stop);

        std::thread thread([&] {

            // lock the mutex, then set the start event and wait on the stop event

            mx.lock();

            stlsoft::scoped_lambda scope([&] {

                mx.unlock();

                TEST_PASSED();
            });

            ev_start.set();

            ::WaitForSingleObject(winstl::get_synch_handle(ev_stop), INFINITE);
        });

        ::WaitForSingleObject(winstl::get_synch_handle(ev_start), INFINITE);

        mx.lock();

        TEST_PASSED();

        TEST_INT_GE(1000, mx.spun_count());

        mx.unlock();

        TEST_PASSED();

        thread.join();

        TEST_PASSED();
    }
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

