
/**
 * Created: 13th November 2026
 * Updated: 13th November 2026
 */


/** \page page__exception_agnostic Exception Agnosticism
 *
 * Many STLSoft components can be built and used either with C++ exception
 * handling enabled, or in an exception-free configuration. Where a component
 * documents behaviour with respect to that choice, it refers to this page.
 *
 * When exception handling is <b>enabled</b>, failure of an operation that
 * cannot be reported via the return value typically results in a typed
 * exception derived from the appropriate project exception hierarchy.
 *
 * When exception handling is <b>not enabled</b>, the same failure conditions
 * are reported by return codes, null handles, or other non-throwing means
 * documented on the component, and no exception is thrown.
 */
