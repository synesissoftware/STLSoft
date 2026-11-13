
/**
 * Created: 11th June 2006
 * Updated: 12th January 2017
 */

/** \defgroup group__library__DL DL Library
 * \ingroup group__libraries
 *
 * \brief This library provides
 *  \ref section__library__dl__classes "classes"
 *  and 
 *  \ref section__library__dl__functions "functions"
 *  for manipulating
 *  dynamic libraries and executing the functions exported by them.
 *
 * \section section__library__dl__classes DL Classes
 *
 * The DL library currently includes the following classes:
 *
 * - unixstl::module - a facade over the UNIX <code>dlopen()</code> / <code>dlclose()</code> / <code>dlsym()</code> API
 * - winstl::module - a facade over the Windows <code>LoadLibrary()</code> / <code>FreeLibrary()</code> / <code>GetProcAddress()</code> API
 *
 * These two classes are structurally conformant, in having the same general structure
 *
\htmlonly
<pre>
  class <b>module</b>
  {
  public: // Member Types
    typedef ??? <b>proc_pointer_type</b>; // A generic function pointer type, as appropriate to the operating system

  public: // Construction
    <b>module</b>(char const *moduleName); // Loads the library contained in the named executable file
    <b>~module</b>(); // Unloads the library

  public: // Operations
    proc_pointer <b>get_symbol</b>(char const *symbolName); // Gets the given function as a generic function pointer
    template &lt;typename F>
    proc_pointer <b>get_symbol</b>(char const *symbolName, F &f); // Gets the given function into a typed function pointer variable
  };
</pre>
\endhtmlonly
 * 
 * These two classes are structurally conformant. Indeed, they exhibit
 * group__principle__intersecting_conformance "Intersecting Conformance".
 * Consequently, the <code>platformstl</code> namespace contains the
 * platformstl::module typedef, which may be used in platform-independent
 * code.
 *
 * \see \ref group__concept__Shim__module_attribute
 *
 * \section section__library__dl__functions DL Functions
 *
 * The DL library currently includes the function suites:
 *
 * - unixstl::dl_call() - implemented in terms of the UNIX <code>dlopen()</code> / <code>dlclose()</code> / <code>dlsym()</code> API
 * - winstl::dl_call() - implemented in terms of the Windows <code>LoadLibrary()</code> / <code>FreeLibrary()</code> / <code>GetProcAddress()</code> API
 *
 * <code>dl_call()</code> provides efficient, generic, <b>type-safe</b>,
 * single-statement invocation of dynamic library functions of between 0 and
 * 32 parameters. For example:
 *
 * <b>1</b>. Invoke the <code>GetSystemDirectoryA()</code> function, located in
 *    KERNEL32.DLL, to determine the Windows system directory for the
 *    current host.
 *
 * We can specify the name of the dynamic library, the name of the entry point,
 * and then all the parameters as if we were invoking the function as a statically
 * linked symbol:
 * 
\htmlonly
<pre>
  CHAR  dir[1 + _MAX_PATH];
  DWORD cch = winstl::<b>dl_call</b>&lt;DWORD>("KERNEL32.DLL", "S:GetSystemDirectoryA", &dir[0], STLSOFT_NUM_ELEMENTS(dir));
</pre>
\endhtmlonly
 *
 * or, if the library name is contained in a string object (or any type
 * for which the \ref group__concept__Shim__string_access "String Access Shims"
 * \link stlsoft::c_str_data c_str_data\endlink and 
 * \link stlsoft::c_str_len c_str_len\endlink
 * are defined):
 *
\htmlonly
<pre>
  std::string libraryName("KERNEL32.DLL");
  CHAR  dir[1 + _MAX_PATH];
  DWORD cch = winstl::<b>dl_call</b>&lt;DWORD>(libraryName, "S:GetSystemDirectoryA", &dir[0], STLSOFT_NUM_ELEMENTS(dir));
</pre>
\endhtmlonly
 *
 * or, if the library has already been loaded, and we don't want/need to
 * incur the cost of loading again:
 *
\htmlonly
<pre>
  HINSTANCE hinstKernel32 = ::LoadLibrary("KERNEL32.DLL");

  . . .

  CHAR  dir[1 + _MAX_PATH];
  DWORD cch = winstl::<b>dl_call</b>&lt;DWORD>(hinstKernel32, "S:GetSystemDirectoryA", &dir[0], STLSOFT_NUM_ELEMENTS(dir));
</pre>
\endhtmlonly
 *
 * \note The <b>S</b> in "<b>S</b>:GetSystemDirectoryA" denotes that the
 * entry point has the <b>stdcall</b> calling convention. The WinSTL version
 * of <b>dl_call()</b> understands the following common Windows calling
 * conventions:
 *
 * - <b>cdecl</b> - prefix with C or cdecl, or no prefix, e.g. <b>"C:func_c"</b>, <b>"cdecl::func_c"</b>, or <b>"func_c"</b>
 * - <b>fastcall</b> - prefix with F or fastcall, e.g. <b>"F:func_f"</b> or <b>"fastcall::func_f"</b>
 * - <b>stdcall</b> - prefix with S or stdcall, e.g. <b>"S:func_s"</b> or <b>"stdcall::func_s"</b>
 *
 * <b>2</b>. Invoke the <a href = "http://recls.org/">recls</a> function
 *    <code>Recls_Search()</code>, located in recls.so, to search for all
 *    C/C++ header files in the current directory or in any sub-directories.
 *
 * We can specify the name of the 
 *
\htmlonly
<pre>
  hrecls_t    hSrch;
  recls_rc_t  rc = unixstl::<b>dl_call</b>&lt;recls_rc_t>("recls.so", "Recls_Search", ".", "*.h|*.hpp|*.hxx", RECLS_F_RECURSIVE | RECLS_F_FILES, &hSrch);
</pre>
\endhtmlonly
 */

/** \defgroup group__library__dl__error DL Library Error
 *
 * \brief Exception classes used by the \ref group__library__DL.
 *
 * \ingroup group__library__DL
 */
