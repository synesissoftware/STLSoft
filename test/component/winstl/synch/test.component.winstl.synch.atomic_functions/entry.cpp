/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.winstl.synch.atomic_functions/entry.cpp
 *
 * Purpose: Component test for WinSTL atomic_functions.
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

#include <winstl/synch/atomic_functions.h>

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

/* Standard C++ header files */
#include <thread>
#include <vector>

/* Standard C header files */
#include <stdint.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    namespace atomic_decrement {

        static void test_check_semantics();
        static void test_a_large_number();
    } // namespace atomic_decrement

    namespace atomic_increment {

        static void test_check_semantics();
        static void test_a_large_number();
    } // namespace atomic_increment

    namespace atomic_postadd {

        static void test_check_semantics();
        static void test_a_large_number();
    } // namespace atomic_postadd

    namespace atomic_postdecrement {

        static void test_check_semantics();
        static void test_a_large_number();
    } // namespace atomic_postdecrement

    namespace atomic_postincrement {

        static void test_check_semantics();
        static void test_a_large_number();
    } // namespace atomic_postincrement

    namespace atomic_preadd {

        static void test_check_semantics();
        static void test_a_large_number();
    } // namespace atomic_preadd

    namespace atomic_predecrement {

        static void test_check_semantics();
        static void test_a_large_number();
    } // namespace atomic_predecrement

    namespace atomic_preincrement {

        static void test_check_semantics();
        static void test_a_large_number();
    } // namespace atomic_preincrement


    namespace atomic_decrement32 {

        static void test_check_semantics();
        static void test_a_large_number();
    } // namespace atomic_decrement32

    namespace atomic_increment32 {

        static void test_check_semantics();
        static void test_a_large_number();
    } // namespace atomic_increment32

    namespace atomic_postadd32 {

        static void test_check_semantics();
        static void test_a_large_number();
    } // namespace atomic_postadd32

    namespace atomic_postdecrement32 {

        static void test_check_semantics();
        static void test_a_large_number();
    } // namespace atomic_postdecrement32

    namespace atomic_postincrement32 {

        static void test_check_semantics();
        static void test_a_large_number();
    } // namespace atomic_postincrement32

    namespace atomic_preadd32 {

        static void test_check_semantics();
        static void test_a_large_number();
    } // namespace atomic_preadd32

    namespace atomic_predecrement32 {

        static void test_check_semantics();
        static void test_a_large_number();
    } // namespace atomic_predecrement32

    namespace atomic_preincrement32 {

        static void test_check_semantics();
        static void test_a_large_number();
    } // namespace atomic_preincrement32
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.winstl.synch.atomic_functions", verbosity))
    {
        XTESTS_RUN_CASE(atomic_decrement::test_check_semantics);
        XTESTS_RUN_CASE(atomic_decrement::test_a_large_number);

        XTESTS_RUN_CASE(atomic_increment::test_check_semantics);
        XTESTS_RUN_CASE(atomic_increment::test_a_large_number);

        XTESTS_RUN_CASE(atomic_postadd::test_check_semantics);
        XTESTS_RUN_CASE(atomic_postadd::test_a_large_number);

        XTESTS_RUN_CASE(atomic_postdecrement::test_check_semantics);
        XTESTS_RUN_CASE(atomic_postdecrement::test_a_large_number);

        XTESTS_RUN_CASE(atomic_postincrement::test_check_semantics);
        XTESTS_RUN_CASE(atomic_postincrement::test_a_large_number);

        XTESTS_RUN_CASE(atomic_preadd::test_check_semantics);
        XTESTS_RUN_CASE(atomic_preadd::test_a_large_number);

        XTESTS_RUN_CASE(atomic_predecrement::test_check_semantics);
        XTESTS_RUN_CASE(atomic_predecrement::test_a_large_number);

        XTESTS_RUN_CASE(atomic_preincrement::test_check_semantics);
        XTESTS_RUN_CASE(atomic_preincrement::test_a_large_number);


        XTESTS_RUN_CASE(atomic_decrement32::test_check_semantics);
        XTESTS_RUN_CASE(atomic_decrement32::test_a_large_number);

        XTESTS_RUN_CASE(atomic_increment32::test_check_semantics);
        XTESTS_RUN_CASE(atomic_increment32::test_a_large_number);

        XTESTS_RUN_CASE(atomic_postadd32::test_check_semantics);
        XTESTS_RUN_CASE(atomic_postadd32::test_a_large_number);

        XTESTS_RUN_CASE(atomic_postdecrement32::test_check_semantics);
        XTESTS_RUN_CASE(atomic_postdecrement32::test_a_large_number);

        XTESTS_RUN_CASE(atomic_postincrement32::test_check_semantics);
        XTESTS_RUN_CASE(atomic_postincrement32::test_a_large_number);

        XTESTS_RUN_CASE(atomic_preadd32::test_check_semantics);
        XTESTS_RUN_CASE(atomic_preadd32::test_a_large_number);

        XTESTS_RUN_CASE(atomic_predecrement32::test_check_semantics);
        XTESTS_RUN_CASE(atomic_predecrement32::test_a_large_number);

        XTESTS_RUN_CASE(atomic_preincrement32::test_check_semantics);
        XTESTS_RUN_CASE(atomic_preincrement32::test_a_large_number);


        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * types
 */

namespace {

    using winstl::atomic_int_t;
    using winstl::atomic_int32_t;
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

    namespace atomic_decrement {

        static void test_check_semantics()
        {
            atomic_int_t    v = 0;

            winstl::atomic_decrement(&v);

            TEST_INT_EQ(-1, v);
        }

        static void test_a_large_number()
        {
            const int   InitialValue    =   10000000;
            const int   NumThreads      =   10;

            static_assert(0 == (InitialValue % NumThreads), "must be exact");

            atomic_int_t    v = static_cast<atomic_int_t>(InitialValue);

            std::vector<std::thread>    threads;

            for (unsigned i = 0; i != NumThreads; ++i)
            {
                threads.push_back(std::thread([&] {

                    for (int i = 0; i != InitialValue / NumThreads; ++i)
                    {
                        winstl::atomic_decrement(&v);

                        ::SwitchToThread();
                    }
                }));
            }

            for (auto i = threads.begin(); threads.end() != i; ++i)
            {
                (*i).join();
            }

            TEST_INT_EQ(0, v);
        }
    } // namespace atomic_decrement

    namespace atomic_increment {

        static void test_check_semantics()
        {
            atomic_int_t    v = 0;

            winstl::atomic_increment(&v);

            TEST_INT_EQ(+1, v);
        }

        static void test_a_large_number()
        {
            const int   FinalValue  =   10000000;
            const int   NumThreads  =   10;

            static_assert(0 == (FinalValue % NumThreads), "must be exact");

            atomic_int_t    v = 0;

            std::vector<std::thread>    threads;

            for (unsigned i = 0; i != NumThreads; ++i)
            {
                threads.push_back(std::thread([&] {

                    for (int i = 0; i != FinalValue / NumThreads; ++i)
                    {
                        winstl::atomic_increment(&v);

                        ::SwitchToThread();
                    }
                }));
            }

            for (auto i = threads.begin(); threads.end() != i; ++i)
            {
                (*i).join();
            }

            TEST_INT_EQ(FinalValue, v);
        }
    } // namespace atomic_increment

    namespace atomic_postadd {

        static void test_check_semantics()
        {
            atomic_int_t    v = 0;
            atomic_int_t    r = winstl::atomic_postadd(&v, 7);

            TEST_INT_EQ(7, v);
            TEST_INT_EQ(0, r);
        }

        static void test_a_large_number()
        {
            const int           FinalValue  =   10000000;
            const int           NumThreads  =   10;
            const atomic_int_t  Increment   =   3;

            static_assert(0 == (FinalValue % NumThreads), "must be exact");

            atomic_int_t    v = 0;


            std::vector<std::thread>    threads;

            for (unsigned i = 0; i != NumThreads; ++i)
            {
                threads.push_back(std::thread([&] {

                    for (int i = 0; i != FinalValue / NumThreads; ++i)
                    {
                        winstl::atomic_postadd(&v, Increment);

                        ::SwitchToThread();
                    }
                }));
            }

            for (auto i = threads.begin(); threads.end() != i; ++i)
            {
                (*i).join();
            }

            TEST_INT_EQ((FinalValue * Increment), v);
        }
    } // namespace atomic_postadd

    namespace atomic_postdecrement {

        static void test_check_semantics()
        {
            atomic_int_t    v = 0;
            atomic_int_t    r = winstl::atomic_postdecrement(&v);

            TEST_INT_EQ(-1, v);
            TEST_INT_EQ(0, r);
        }

        static void test_a_large_number()
        {
            const int   InitialValue    =   10000000;
            const int   NumThreads      =   10;

            static_assert(0 == (InitialValue % NumThreads), "must be exact");

            atomic_int_t    v = static_cast<atomic_int_t>(InitialValue);

            std::vector<std::thread>    threads;

            for (unsigned i = 0; i != NumThreads; ++i)
            {
                threads.push_back(std::thread([&] {

                    for (int i = 0; i != InitialValue / NumThreads; ++i)
                    {
                        winstl::atomic_postdecrement(&v);

                        ::SwitchToThread();
                    }
                }));
            }

            for (auto i = threads.begin(); threads.end() != i; ++i)
            {
                (*i).join();
            }

            TEST_INT_EQ(0, v);
        }
    } // namespace atomic_postdecrement

    namespace atomic_postincrement {

        static void test_check_semantics()
        {
            atomic_int_t    v = 0;
            atomic_int_t    r = winstl::atomic_postincrement(&v);

            TEST_INT_EQ(+1, v);
            TEST_INT_EQ(0, r);
        }

        static void test_a_large_number()
        {
            const int   FinalValue  =   10000000;
            const int   NumThreads  =   10;

            static_assert(0 == (FinalValue % NumThreads), "must be exact");

            atomic_int_t    v = 0;

            std::vector<std::thread>    threads;

            for (unsigned i = 0; i != NumThreads; ++i)
            {
                threads.push_back(std::thread([&] {

                    for (int i = 0; i != FinalValue / NumThreads; ++i)
                    {
                        winstl::atomic_postincrement(&v);

                        ::SwitchToThread();
                    }
                }));
            }

            for (auto i = threads.begin(); threads.end() != i; ++i)
            {
                (*i).join();
            }

            TEST_INT_EQ(FinalValue, v);
        }
    } // namespace atomic_postincrement

    namespace atomic_preadd {

        static void test_check_semantics()
        {
            atomic_int_t    v = 0;
            atomic_int_t    r = winstl::atomic_preadd(&v, 7);

            TEST_INT_EQ(7, v);
            TEST_INT_EQ(7, r);
        }

        static void test_a_large_number()
        {
            const int           FinalValue  =   10000000;
            const int           NumThreads  =   10;
            const atomic_int_t  Increment   =   3;

            static_assert(0 == (FinalValue % NumThreads), "must be exact");

            atomic_int_t    v = 0;

            std::vector<std::thread>    threads;

            for (unsigned i = 0; i != NumThreads; ++i)
            {
                threads.push_back(std::thread([&] {

                    for (int i = 0; i != FinalValue / NumThreads; ++i)
                    {
                        winstl::atomic_preadd(&v, Increment);

                        ::SwitchToThread();
                    }
                }));
            }

            for (auto i = threads.begin(); threads.end() != i; ++i)
            {
                (*i).join();
            }

            TEST_INT_EQ((FinalValue * Increment), v);
        }
    } // namespace atomic_preadd

    namespace atomic_predecrement {

        static void test_check_semantics()
        {
            atomic_int_t    v = 0;
            atomic_int_t    r = winstl::atomic_predecrement(&v);

            TEST_INT_EQ(-1, v);
            TEST_INT_EQ(-1, r);
        }

        static void test_a_large_number()
        {
            const int   InitialValue    =   10000000;
            const int   NumThreads      =   10;

            static_assert(0 == (InitialValue % NumThreads), "must be exact");

            atomic_int_t    v = static_cast<atomic_int_t>(InitialValue);

            std::vector<std::thread>    threads;

            for (unsigned i = 0; i != NumThreads; ++i)
            {
                threads.push_back(std::thread([&] {

                    for (int i = 0; i != InitialValue / NumThreads; ++i)
                    {
                        winstl::atomic_predecrement(&v);

                        ::SwitchToThread();
                    }
                }));
            }

            for (auto i = threads.begin(); threads.end() != i; ++i)
            {
                (*i).join();
            }

            TEST_INT_EQ(0, v);
        }
    } // namespace atomic_predecrement

    namespace atomic_preincrement {

        static void test_check_semantics()
        {
            atomic_int_t    v = 0;
            atomic_int_t    r = winstl::atomic_preincrement(&v);

            TEST_INT_EQ(+1, v);
            TEST_INT_EQ(+1, r);
        }

        static void test_a_large_number()
        {
            const int   FinalValue  =   10000000;
            const int   NumThreads  =   10;

            static_assert(0 == (FinalValue % NumThreads), "must be exact");

            atomic_int_t    v = 0;

            std::vector<std::thread>    threads;

            for (unsigned i = 0; i != NumThreads; ++i)
            {
                threads.push_back(std::thread([&] {

                    for (int i = 0; i != FinalValue / NumThreads; ++i)
                    {
                        winstl::atomic_preincrement(&v);

                        ::SwitchToThread();
                    }
                }));
            }

            for (auto i = threads.begin(); threads.end() != i; ++i)
            {
                (*i).join();
            }

            TEST_INT_EQ(FinalValue, v);
        }
    } // namespace atomic_preincrement



    namespace atomic_decrement32 {

        static void test_check_semantics()
        {
            atomic_int32_t  v = 0;

            winstl::atomic_decrement32(&v);

            TEST_INT_EQ(-1, v);
        }

        static void test_a_large_number()
        {
            const int   InitialValue    =   10000000;
            const int   NumThreads      =   10;

            static_assert(0 == (InitialValue % NumThreads), "must be exact");

            atomic_int32_t    v = static_cast<atomic_int32_t>(InitialValue);

            std::vector<std::thread>    threads;

            for (unsigned i = 0; i != NumThreads; ++i)
            {
                threads.push_back(std::thread([&] {

                    for (int i = 0; i != InitialValue / NumThreads; ++i)
                    {
                        winstl::atomic_decrement32(&v);

                        ::SwitchToThread();
                    }
                }));
            }

            for (auto i = threads.begin(); threads.end() != i; ++i)
            {
                (*i).join();
            }

            TEST_INT_EQ(0, v);
        }
    } // namespace atomic_decrement32

    namespace atomic_increment32 {

        static void test_check_semantics()
        {
            atomic_int32_t    v = 0;

            winstl::atomic_increment32(&v);

            TEST_INT_EQ(+1, v);
        }

        static void test_a_large_number()
        {
            const int   FinalValue  =   10000000;
            const int   NumThreads  =   10;

            static_assert(0 == (FinalValue % NumThreads), "must be exact");

            atomic_int32_t    v = 0;

            std::vector<std::thread>    threads;

            for (unsigned i = 0; i != NumThreads; ++i)
            {
                threads.push_back(std::thread([&] {

                    for (int i = 0; i != FinalValue / NumThreads; ++i)
                    {
                        winstl::atomic_increment32(&v);

                        ::SwitchToThread();
                    }
                }));
            }

            for (auto i = threads.begin(); threads.end() != i; ++i)
            {
                (*i).join();
            }

            TEST_INT_EQ(FinalValue, v);
        }
    } // namespace atomic_increment32

    namespace atomic_postadd32 {

        static void test_check_semantics()
        {
            atomic_int32_t  v = 0;
            atomic_int32_t  r = winstl::atomic_postadd32(&v, 7);

            TEST_INT_EQ(7, v);
            TEST_INT_EQ(0, r);
        }

        static void test_a_large_number()
        {
            const int               FinalValue  =   10000000;
            const int               NumThreads  =   10;
            const atomic_int32_t    Increment   =   3;

            static_assert(0 == (FinalValue % NumThreads), "must be exact");

            atomic_int32_t          v = 0;

            std::vector<std::thread>    threads;

            for (unsigned i = 0; i != NumThreads; ++i)
            {
                threads.push_back(std::thread([&] {

                    for (int i = 0; i != FinalValue / NumThreads; ++i)
                    {
                        winstl::atomic_postadd32(&v, Increment);

                        ::SwitchToThread();
                    }
                }));
            }

            for (auto i = threads.begin(); threads.end() != i; ++i)
            {
                (*i).join();
            }

            TEST_INT_EQ((FinalValue * Increment), v);
        }
    } // namespace atomic_postadd32

    namespace atomic_postdecrement32 {

        static void test_check_semantics()
        {
            atomic_int32_t  v = 0;
            atomic_int32_t  r = winstl::atomic_postdecrement32(&v);

            TEST_INT_EQ(-1, v);
            TEST_INT_EQ(0, r);
        }

        static void test_a_large_number()
        {
            const int   InitialValue    =   10000000;
            const int   NumThreads      =   10;

            static_assert(0 == (InitialValue % NumThreads), "must be exact");

            atomic_int32_t    v = static_cast<atomic_int32_t>(InitialValue);

            std::vector<std::thread>    threads;

            for (unsigned i = 0; i != NumThreads; ++i)
            {
                threads.push_back(std::thread([&] {

                    for (int i = 0; i != InitialValue / NumThreads; ++i)
                    {
                        winstl::atomic_postdecrement32(&v);

                        ::SwitchToThread();
                    }
                }));
            }

            for (auto i = threads.begin(); threads.end() != i; ++i)
            {
                (*i).join();
            }

            TEST_INT_EQ(0, v);
        }
    } // namespace atomic_postdecrement32

    namespace atomic_postincrement32 {

        static void test_check_semantics()
        {
            atomic_int32_t  v = 0;
            atomic_int32_t  r = winstl::atomic_postincrement32(&v);

            TEST_INT_EQ(+1, v);
            TEST_INT_EQ(0, r);
        }

        static void test_a_large_number()
        {
            const int   FinalValue  =   10000000;
            const int   NumThreads  =   10;

            static_assert(0 == (FinalValue % NumThreads), "must be exact");

            atomic_int32_t    v = 0;

            std::vector<std::thread>    threads;

            for (unsigned i = 0; i != NumThreads; ++i)
            {
                threads.push_back(std::thread([&] {

                    for (int i = 0; i != FinalValue / NumThreads; ++i)
                    {
                        winstl::atomic_postincrement32(&v);

                        ::SwitchToThread();
                    }
                }));
            }

            for (auto i = threads.begin(); threads.end() != i; ++i)
            {
                (*i).join();
            }

            TEST_INT_EQ(FinalValue, v);
        }
    } // namespace atomic_postincrement32

    namespace atomic_preadd32 {

        static void test_check_semantics()
        {
            atomic_int32_t  v = 0;
            atomic_int32_t  r = winstl::atomic_preadd32(&v, 7);

            TEST_INT_EQ(7, v);
            TEST_INT_EQ(7, r);
        }

        static void test_a_large_number()
        {
            const int           FinalValue  =   10000000;
            const int           NumThreads  =   10;
            const atomic_int32_t  Increment   =   3;

            static_assert(0 == (FinalValue % NumThreads), "must be exact");

            atomic_int32_t    v = 0;

            std::vector<std::thread>    threads;

            for (unsigned i = 0; i != NumThreads; ++i)
            {
                threads.push_back(std::thread([&] {

                    for (int i = 0; i != FinalValue / NumThreads; ++i)
                    {
                        winstl::atomic_preadd32(&v, Increment);

                        ::SwitchToThread();
                    }
                }));
            }

            for (auto i = threads.begin(); threads.end() != i; ++i)
            {
                (*i).join();
            }

            TEST_INT_EQ((FinalValue * Increment), v);
        }
    } // namespace atomic_preadd32

    namespace atomic_predecrement32 {

        static void test_check_semantics()
        {
            atomic_int32_t  v = 0;
            atomic_int32_t  r = winstl::atomic_predecrement32(&v);

            TEST_INT_EQ(-1, v);
            TEST_INT_EQ(-1, r);
        }

        static void test_a_large_number()
        {
            const int   InitialValue    =   10000000;
            const int   NumThreads      =   10;

            static_assert(0 == (InitialValue % NumThreads), "must be exact");

            atomic_int32_t    v = static_cast<atomic_int32_t>(InitialValue);

            std::vector<std::thread>    threads;

            for (unsigned i = 0; i != NumThreads; ++i)
            {
                threads.push_back(std::thread([&] {

                    for (int i = 0; i != InitialValue / NumThreads; ++i)
                    {
                        winstl::atomic_predecrement32(&v);

                        ::SwitchToThread();
                    }
                }));
            }

            for (auto i = threads.begin(); threads.end() != i; ++i)
            {
                (*i).join();
            }

            TEST_INT_EQ(0, v);
        }
    } // namespace atomic_predecrement32

    namespace atomic_preincrement32 {

        static void test_check_semantics()
        {
            atomic_int32_t  v = 0;
            atomic_int32_t  r = winstl::atomic_preincrement32(&v);

            TEST_INT_EQ(+1, v);
            TEST_INT_EQ(+1, r);
        }

        static void test_a_large_number()
        {
            const int   FinalValue  =   10000000;
            const int   NumThreads  =   10;

            static_assert(0 == (FinalValue % NumThreads), "must be exact");

            atomic_int32_t    v = 0;

            std::vector<std::thread>    threads;

            for (unsigned i = 0; i != NumThreads; ++i)
            {
                threads.push_back(std::thread([&] {

                    for (int i = 0; i != FinalValue / NumThreads; ++i)
                    {
                        winstl::atomic_preincrement32(&v);

                        ::SwitchToThread();
                    }
                }));
            }

            for (auto i = threads.begin(); threads.end() != i; ++i)
            {
                (*i).join();
            }

            TEST_INT_EQ(FinalValue, v);
        }
    } // namespace atomic_preincrement32
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

