/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.util.count_hexadecimal_digits.C/entry.c
 *
 * Purpose: C validation for `util/count_digits/count_hexadecimal_digits` (compiles header in a C translation unit).
 *
 * Created: 9th August 2026
 * Updated: 12th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/util/count_digits/count_hexadecimal_digits.h>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

static void TEST_compile_and_link(void);


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.util.count_hexadecimal_digits.C", verbosity))
    {
        XTESTS_RUN_CASE(TEST_compile_and_link);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

static void TEST_compile_and_link(void)
{
    TEST_PASSED();
}


/* ///////////////////////////// end of file //////////////////////////// */
