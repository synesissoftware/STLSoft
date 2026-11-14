/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/stlsoft/smartptr/shared_ptr/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft::shared_ptr`.
 *
 * Created: 7th October 2024
 * Updated: 14th November 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/smartptr/shared_ptr.hpp>


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* Standard C++ header files */
#include <string>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_TYPES_EXIST();

    static void TEST_CTOR_DEFAULT();
    static void TEST_CTOR_NULLPTR();
    static void TEST_CTOR_CONVERSION();
    static void TEST_CTOR_COPY();
#ifdef STLSOFT_CF_RVALUE_REFERENCES_SUPPORT

    static void TEST_CTOR_MOVE();
#endif
    static void TEST_SWAP();
    static void TEST_std_swap();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.smartptr.shared_ptr", verbosity))
    {
        XTESTS_RUN_CASE(TEST_TYPES_EXIST);

        XTESTS_RUN_CASE(TEST_CTOR_DEFAULT);
        XTESTS_RUN_CASE(TEST_CTOR_NULLPTR);
        XTESTS_RUN_CASE(TEST_CTOR_CONVERSION);
        XTESTS_RUN_CASE(TEST_CTOR_COPY);
#ifdef STLSOFT_CF_RVALUE_REFERENCES_SUPPORT

        XTESTS_RUN_CASE(TEST_CTOR_MOVE);
#endif
        XTESTS_RUN_CASE(TEST_SWAP);
        XTESTS_RUN_CASE(TEST_std_swap);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

    struct CountHolder
    {
    public: // construction
        CountHolder(int& i)
            : m_i(i)
        {
            ++m_i;
        }
        ~CountHolder() STLSOFT_NOEXCEPT
        {
            --m_i;
        }
    private:
        void operator =(CountHolder const&) STLSOFT_COPY_ASSIGNMENT_PROSCRIBED;

    public: // accessors
        int i() const STLSOFT_NOEXCEPT
        {
            return m_i;
        }

    public: // fields
        int& m_i;
    };
} // anonymous namespace

namespace {

static void TEST_TYPES_EXIST()
{
    STLSOFT_SUPPRESS_UNUSED(typeid(stlsoft::shared_ptr<char*>));
#if 0

    STLSOFT_SUPPRESS_UNUSED(typeid(stlsoft::shared_ptr<void>));
#endif

    TEST_PASSED();
}

static void TEST_CTOR_DEFAULT()
{
    {
        stlsoft::shared_ptr<int> ptr;

        TEST_INT_EQ(0, ptr.count());
        TEST_INT_EQ(0, ptr.use_count());
        TEST_PTR_NULL(ptr.get());
    }

    {
        stlsoft::shared_ptr<std::string> ptr;

        TEST_INT_EQ(0, ptr.count());
        TEST_INT_EQ(0, ptr.use_count());
        TEST_PTR_NULL(ptr.get());
    }

    {
        stlsoft::shared_ptr<CountHolder> ptr;

        TEST_INT_EQ(0, ptr.count());
        TEST_INT_EQ(0, ptr.use_count());
        TEST_PTR_NULL(ptr.get());
    }
}

static void TEST_CTOR_NULLPTR()
{
    {
        stlsoft::shared_ptr<int> ptr(ss_nullptr_k);

        TEST_INT_EQ(0, ptr.count());
        TEST_INT_EQ(0, ptr.use_count());
        TEST_PTR_NULL(ptr.get());
    }

    {
        stlsoft::shared_ptr<std::string> ptr(ss_nullptr_k);

        TEST_INT_EQ(0, ptr.count());
        TEST_INT_EQ(0, ptr.use_count());
        TEST_PTR_NULL(ptr.get());
    }

    {
        stlsoft::shared_ptr<CountHolder> ptr(ss_nullptr_k);

        TEST_INT_EQ(0, ptr.count());
        TEST_INT_EQ(0, ptr.use_count());
        TEST_PTR_NULL(ptr.get());
    }
}

static void TEST_CTOR_CONVERSION()
{
    {
        stlsoft::shared_ptr<int> ptr(new int(123));

        TEST_INT_EQ(1, ptr.count());
        TEST_INT_EQ(1, ptr.use_count());
        TEST_PTR_NOT_NULL(ptr.get());

        TEST_INT_EQ(123, *ptr);
    }

    {
        stlsoft::shared_ptr<std::string> ptr(new std::string("123"));

        TEST_INT_EQ(1, ptr.count());
        TEST_INT_EQ(1, ptr.use_count());
        TEST_PTR_NOT_NULL(ptr.get());

        TEST_MS_EQ("123", *ptr);
        TEST_INT_EQ(3u, ptr->size());
    }

    {
        int i = 123;

        {
            stlsoft::shared_ptr<CountHolder> ptr(new CountHolder(i));

            TEST_INT_EQ(1, ptr.count());
            TEST_INT_EQ(1, ptr.use_count());
            TEST_PTR_NOT_NULL(ptr.get());

            TEST_INT_EQ(124, ptr->i());
        }

        TEST_INT_EQ(123, i);
    }
}

static void TEST_CTOR_COPY()
{
    {
        stlsoft::shared_ptr<int> ptr(new int(123));

        TEST_INT_EQ(1, ptr.count());
        TEST_INT_EQ(1, ptr.use_count());
        TEST_PTR_NOT_NULL(ptr.get());

        TEST_INT_EQ(123, *ptr);

        stlsoft::shared_ptr<int> ptr2(ptr);

        TEST_INT_EQ(2, ptr.count());
        TEST_INT_EQ(2, ptr.use_count());
        TEST_PTR_NOT_NULL(ptr.get());

        TEST_INT_EQ(123, *ptr);

        TEST_INT_EQ(2, ptr2.count());
        TEST_INT_EQ(2, ptr2.use_count());
        TEST_PTR_NOT_NULL(ptr2.get());

        TEST_INT_EQ(123, *ptr2);
    }

    {
        stlsoft::shared_ptr<std::string> ptr(new std::string("123"));

        TEST_INT_EQ(1, ptr.count());
        TEST_INT_EQ(1, ptr.use_count());
        TEST_PTR_NOT_NULL(ptr.get());

        TEST_MS_EQ("123", *ptr);

        stlsoft::shared_ptr<std::string> ptr2(ptr);

        TEST_INT_EQ(2, ptr.count());
        TEST_INT_EQ(2, ptr.use_count());
        TEST_PTR_NOT_NULL(ptr.get());

        TEST_MS_EQ("123", *ptr);
        TEST_INT_EQ(3u, ptr->size());

        TEST_INT_EQ(2, ptr2.count());
        TEST_INT_EQ(2, ptr2.use_count());
        TEST_PTR_NOT_NULL(ptr2.get());

        TEST_MS_EQ("123", *ptr2);
        TEST_INT_EQ(3u, ptr2->size());
    }

    {
        int i = 123;

        {
            stlsoft::shared_ptr<CountHolder> ptr(new CountHolder(i));

            TEST_INT_EQ(1, ptr.count());
            TEST_INT_EQ(1, ptr.use_count());
            TEST_PTR_NOT_NULL(ptr.get());

            TEST_INT_EQ(124, ptr->i());

            {
                stlsoft::shared_ptr<CountHolder> ptr2(ptr);

                TEST_INT_EQ(2, ptr.count());
                TEST_INT_EQ(2, ptr.use_count());
                TEST_PTR_NOT_NULL(ptr.get());

                TEST_INT_EQ(124, ptr->i());

                TEST_INT_EQ(2, ptr2.count());
                TEST_INT_EQ(2, ptr2.use_count());
                TEST_PTR_NOT_NULL(ptr2.get());

                TEST_INT_EQ(124, ptr2->i());
            }

            TEST_INT_EQ(1, ptr.count());
            TEST_INT_EQ(1, ptr.use_count());
            TEST_PTR_NOT_NULL(ptr.get());

            TEST_INT_EQ(124, ptr->i());
        }

        TEST_INT_EQ(123, i);
    }
}

#ifdef STLSOFT_CF_RVALUE_REFERENCES_SUPPORT

static void TEST_CTOR_MOVE()
{
    {
        stlsoft::shared_ptr<int> ptr(new int(123));

        TEST_INT_EQ(1, ptr.count());
        TEST_INT_EQ(1, ptr.use_count());
        TEST_PTR_NOT_NULL(ptr.get());

        TEST_INT_EQ(123, *ptr);

        stlsoft::shared_ptr<int> ptr2(std::move(ptr));

        TEST_INT_EQ(0, ptr.count());
        TEST_INT_EQ(0, ptr.use_count());
        TEST_PTR_NULL(ptr.get());

        TEST_INT_EQ(1, ptr2.count());
        TEST_INT_EQ(1, ptr2.use_count());
        TEST_PTR_NOT_NULL(ptr2.get());

        TEST_INT_EQ(123, *ptr2);
    }

    {
        stlsoft::shared_ptr<std::string> ptr(new std::string("123"));

        TEST_INT_EQ(1, ptr.count());
        TEST_INT_EQ(1, ptr.use_count());
        TEST_PTR_NOT_NULL(ptr.get());

        TEST_MS_EQ("123", *ptr);

        stlsoft::shared_ptr<std::string> ptr2(std::move(ptr));

        TEST_INT_EQ(0, ptr.count());
        TEST_INT_EQ(0, ptr.use_count());
        TEST_PTR_NULL(ptr.get());

        TEST_INT_EQ(1, ptr2.count());
        TEST_INT_EQ(1, ptr2.use_count());
        TEST_PTR_NOT_NULL(ptr2.get());

        TEST_MS_EQ("123", *ptr2);
        TEST_INT_EQ(3u, ptr2->size());
    }

    {
        int i = 123;

        {
            stlsoft::shared_ptr<CountHolder> ptr(new CountHolder(i));

            TEST_INT_EQ(1, ptr.count());
            TEST_INT_EQ(1, ptr.use_count());
            TEST_PTR_NOT_NULL(ptr.get());

            TEST_INT_EQ(124, ptr->i());

            {
                stlsoft::shared_ptr<CountHolder> ptr2(std::move(ptr));

                TEST_INT_EQ(0, ptr.count());
                TEST_INT_EQ(0, ptr.use_count());
                TEST_PTR_NULL(ptr.get());

                TEST_INT_EQ(1, ptr2.count());
                TEST_INT_EQ(1, ptr2.use_count());
                TEST_PTR_NOT_NULL(ptr2.get());

                TEST_INT_EQ(124, ptr2->i());
            }

            TEST_INT_EQ(0, ptr.count());
            TEST_INT_EQ(0, ptr.use_count());
            TEST_PTR_NULL(ptr.get());
        }

        TEST_INT_EQ(123, i);
    }
}
#endif

static void TEST_SWAP()
{
    {
        stlsoft::shared_ptr<int> ptr(new int(123));

        TEST_INT_EQ(1, ptr.count());
        TEST_INT_EQ(1, ptr.use_count());
        TEST_PTR_NOT_NULL(ptr.get());

        TEST_INT_EQ(123, *ptr);

        stlsoft::shared_ptr<int> ptr2;

        ptr2.swap(ptr);

        TEST_INT_EQ(0, ptr.count());
        TEST_INT_EQ(0, ptr.use_count());
        TEST_PTR_NULL(ptr.get());

        TEST_INT_EQ(1, ptr2.count());
        TEST_INT_EQ(1, ptr2.use_count());
        TEST_PTR_NOT_NULL(ptr2.get());

        TEST_INT_EQ(123, *ptr2);
    }

    {
        stlsoft::shared_ptr<std::string> ptr(new std::string("123"));

        TEST_INT_EQ(1, ptr.count());
        TEST_INT_EQ(1, ptr.use_count());
        TEST_PTR_NOT_NULL(ptr.get());

        TEST_MS_EQ("123", *ptr);

        stlsoft::shared_ptr<std::string> ptr2;

        ptr2.swap(ptr);

        TEST_INT_EQ(0, ptr.count());
        TEST_INT_EQ(0, ptr.use_count());
        TEST_PTR_NULL(ptr.get());

        TEST_INT_EQ(1, ptr2.count());
        TEST_INT_EQ(1, ptr2.use_count());
        TEST_PTR_NOT_NULL(ptr2.get());

        TEST_MS_EQ("123", *ptr2);
        TEST_INT_EQ(3u, ptr2->size());
    }

    {
        int i = 123;

        {
            stlsoft::shared_ptr<CountHolder> ptr(new CountHolder(i));

            TEST_INT_EQ(1, ptr.count());
            TEST_INT_EQ(1, ptr.use_count());
            TEST_PTR_NOT_NULL(ptr.get());

            TEST_INT_EQ(124, ptr->i());

            {
                stlsoft::shared_ptr<CountHolder> ptr2;

                ptr2.swap(ptr);

                TEST_INT_EQ(0, ptr.count());
                TEST_INT_EQ(0, ptr.use_count());
                TEST_PTR_NULL(ptr.get());

                TEST_INT_EQ(1, ptr2.count());
                TEST_INT_EQ(1, ptr2.use_count());
                TEST_PTR_NOT_NULL(ptr2.get());

                TEST_INT_EQ(124, ptr2->i());
            }

            TEST_INT_EQ(0, ptr.count());
            TEST_INT_EQ(0, ptr.use_count());
            TEST_PTR_NULL(ptr.get());
        }

        TEST_INT_EQ(123, i);
    }
}

static void TEST_std_swap()
{
    {
        stlsoft::shared_ptr<int> ptr(new int(123));

        TEST_INT_EQ(1, ptr.count());
        TEST_INT_EQ(1, ptr.use_count());
        TEST_PTR_NOT_NULL(ptr.get());

        TEST_INT_EQ(123, *ptr);

        stlsoft::shared_ptr<int> ptr2;

        std::swap(ptr, ptr2);

        TEST_INT_EQ(0, ptr.count());
        TEST_INT_EQ(0, ptr.use_count());
        TEST_PTR_NULL(ptr.get());

        TEST_INT_EQ(1, ptr2.count());
        TEST_INT_EQ(1, ptr2.use_count());
        TEST_PTR_NOT_NULL(ptr2.get());

        TEST_INT_EQ(123, *ptr2);
    }

    {
        stlsoft::shared_ptr<std::string> ptr(new std::string("123"));

        TEST_INT_EQ(1, ptr.count());
        TEST_INT_EQ(1, ptr.use_count());
        TEST_PTR_NOT_NULL(ptr.get());

        TEST_MS_EQ("123", *ptr);

        stlsoft::shared_ptr<std::string> ptr2;

        std::swap(ptr, ptr2);

        TEST_INT_EQ(0, ptr.count());
        TEST_INT_EQ(0, ptr.use_count());
        TEST_PTR_NULL(ptr.get());

        TEST_INT_EQ(1, ptr2.count());
        TEST_INT_EQ(1, ptr2.use_count());
        TEST_PTR_NOT_NULL(ptr2.get());

        TEST_MS_EQ("123", *ptr2);
        TEST_INT_EQ(3u, ptr2->size());
    }
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

