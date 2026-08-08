/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.winstl.synch.spin_mutex/entry.cpp
 *
 * Purpose: Component test for `winstl::spin_mutex`.
 *
 * Created: sometime in 2015
 * Updated: 9th August 2026
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

    static void test_1_0();
    static void test_types_exist();
    static void test_types_have_expected_attributes();
    static void test_spin_mutex_can_be_locked_and_unlocked();
    static void test_spin_mutex_can_be_locked_and_unlocked_with_lock_scope();
    static void test_spin_mutex_can_be_locked_in_the_main_thread_and_unlocked_in_a_worker_thread();
    static void test_spin_mutex32_can_be_locked_and_unlocked();
    static void test_spin_mutex32_can_be_locked_and_unlocked_with_lock_scope();
    static void test_spin_mutex32_can_be_locked_in_the_main_thread_and_unlocked_in_a_worker_thread();
    static void test_with_specific_policy();
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
        XTESTS_RUN_CASE(test_1_0);
        XTESTS_RUN_CASE(test_types_exist);
        XTESTS_RUN_CASE(test_types_have_expected_attributes);
        XTESTS_RUN_CASE(test_spin_mutex_can_be_locked_and_unlocked);
        XTESTS_RUN_CASE(test_spin_mutex_can_be_locked_and_unlocked_with_lock_scope);
        XTESTS_RUN_CASE(test_spin_mutex_can_be_locked_in_the_main_thread_and_unlocked_in_a_worker_thread);
        XTESTS_RUN_CASE(test_spin_mutex32_can_be_locked_and_unlocked);
        XTESTS_RUN_CASE(test_spin_mutex32_can_be_locked_and_unlocked_with_lock_scope);
        XTESTS_RUN_CASE(test_spin_mutex32_can_be_locked_in_the_main_thread_and_unlocked_in_a_worker_thread);
        XTESTS_RUN_CASE(test_with_specific_policy);

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
    public: // Types
        typedef stlsoft::ss_sint32_t                            ss_sint32_t;
        typedef stlsoft::ss_truthy_t                            ss_truthy_t;
        typedef winstl::atomic_int_t                            atomic_int_type;

    public: // Operations
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

    static void test_1_0()
    {
    }

    static void test_types_exist()
    {
        STLSOFT_SUPPRESS_UNUSED(typeid(winstl::spin_mutex));
        STLSOFT_SUPPRESS_UNUSED(typeid(winstl::spin_mutex_no_yield));
        STLSOFT_SUPPRESS_UNUSED(typeid(winstl::spin_mutex32));

        TEST_PASSED();
    }

    static void test_types_have_expected_attributes()
    {
        static_assert(stlsoft::is_integral_type<winstl::spin_mutex::atomic_int_type>::value, "spin_mutex type must have integral atomic type");
        static_assert(stlsoft::is_integral_type<winstl::spin_mutex32::atomic_int_type>::value, "spin_mutex32 type must have integral atomic type");

        TEST_PASSED();
    }

    static void test_spin_mutex_can_be_locked_and_unlocked()
    {
        winstl::spin_mutex mx;

        mx.lock();

        TEST_PASSED();

        mx.unlock();

        TEST_PASSED();
    }

    static void test_spin_mutex_can_be_locked_and_unlocked_with_lock_scope()
    {
        winstl::spin_mutex mx;

        {
            stlsoft::lock_scope<winstl::spin_mutex> lock(mx);

            TEST_PASSED();
        }

        TEST_PASSED();
    }

    static void test_spin_mutex_can_be_locked_in_the_main_thread_and_unlocked_in_a_worker_thread()
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

    static void test_spin_mutex32_can_be_locked_and_unlocked()
    {
        winstl::spin_mutex32 mx;

        mx.lock();

        TEST_PASSED();

        mx.unlock();

        TEST_PASSED();
    }

    static void test_spin_mutex32_can_be_locked_and_unlocked_with_lock_scope()
    {
        winstl::spin_mutex32 mx;

        {
            stlsoft::lock_scope<winstl::spin_mutex32> lock(mx);

            TEST_PASSED();
        }

        TEST_PASSED();
    }

    static void test_spin_mutex32_can_be_locked_in_the_main_thread_and_unlocked_in_a_worker_thread()
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

    static void test_with_specific_policy()
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

