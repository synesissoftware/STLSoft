/* /////////////////////////////////////////////////////////////////////////
 * File:    test.performance.platformstl.file_lines/boot_probe.c
 *
 * Purpose: TEMPORARY. Pure-C breadcrumbs before C++ static init, written
 *          with write(2) and a cwd file so a silent MinGW death still
 *          leaves evidence for the harness to cat.
 *
 * Created: 30th September 2026
 * Updated: 30th September 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#if defined(_WIN32)
# include <io.h>
#else /* ? _WIN32 */
# include <unistd.h>
#endif /* _WIN32 */


#define BOOT_TRACE_FILE_ "file_lines.perf.trace.txt"


static void
boot_crumb_(
    char const* msg
)
{
    int const len = (int)strlen(msg);
#if defined(_WIN32)
    int const fd = _open(
        BOOT_TRACE_FILE_
    ,   _O_WRONLY | _O_CREAT | _O_APPEND
    ,   0644
    );
#else /* ? _WIN32 */
    int const fd = open(
        BOOT_TRACE_FILE_
    ,   O_WRONLY | O_CREAT | O_APPEND
    ,   0644
    );
#endif /* _WIN32 */

    if (fd >= 0)
    {
#if defined(_WIN32)
        _write(fd, msg, (unsigned)len);
        _write(fd, "\n", 1u);
        _close(fd);
#else /* ? _WIN32 */
        write(fd, msg, (size_t)len);
        write(fd, "\n", 1u);
        close(fd);
#endif /* _WIN32 */
    }

#if defined(_WIN32)
    _write(2, msg, (unsigned)len);
    _write(2, "\n", 1u);
#else /* ? _WIN32 */
    write(2, msg, (size_t)len);
    write(2, "\n", 1u);
#endif /* _WIN32 */

    /* Also poke stdio in case the harness only captures FILE* streams. */
    fputs(msg, stderr);
    fputc('\n', stderr);
    fflush(stderr);
    fputs(msg, stdout);
    fputc('\n', stdout);
    fflush(stdout);
}


#if defined(__GNUC__)

__attribute__((constructor(101)))
static void
boot_ctor_early_(void)
{
    boot_crumb_("[file_lines.perf] boot constructor early");
}

__attribute__((constructor(65535)))
static void
boot_ctor_late_(void)
{
    boot_crumb_("[file_lines.perf] boot constructor late");
}

#endif /* __GNUC__ */


/* ///////////////////////////// end of file //////////////////////////// */
