
/**
 * Created: 1st June 2006
 * Updated: 14th January 2007
 */


/** \defgroup group__pattern__special_string_instance Special String Instance Pattern
 * \ingroup group__patterns
 *
 * \brief &nbsp;&nbsp;&nbsp;&nbsp;Objects Acting as Well-known String Values.
 *
 * A <b>Special String Instance</b> is a type, or an instance of such a
 * type, that acts as a string with a special value.
 *
 * For example, the 
 *
 * - winstl::absolute_path (and winstl::absolute_path_a and winstl::absolute_path_w)
 * - unixstl::current_directory (and unixstl::current_directory_a)
 * - winstl::current_directory (and winstl::current_directory_a and  winstl::current_directory_w)
 * - winstl::module_directory (and winstl::module_directory_a and  winstl::module_directory_w)
 * - winstl::module_filename (and winstl::module_filename_a and  winstl::module_filename_w)
 * - winstl::system_directory (and winstl::system_directory_a and  winstl::system_directory_w)
 * - winstl::windows_directory (and winstl::windows_directory_a and  winstl::windows_directory_w)
 *
 * The basic semantics of a special string instance can be achieved with conversion
 * functions, as in the following:
 *
\htmlonly
<pre>
std::string get_cwd()
{
  stlsoft::auto_buffer&lt;char>  buff(1 + unixstl::filesystem_traits&lt;char>::path_max());

  ::getcwd(&buff, buff.size());

  return std::string(buff.data(), buff.size());
}
</pre>
\endhtmlonly
 *
 * However, it's harder to achieve the features that are available with a class-based
 * approach:
 *
 * - Static (per-class) state, for values that do not change, such as the Windows
 *   directory.
 * - Simple, succinct policies for specifying each <b>Special String Instance</b>
 *   type's behaviour.
 * - Simple customisation of the allocator policy used.
 * - Straightforward use of \link stlsoft::auto_buffer auto_buffer\endlink for
 *   optimised memory allocation.
 *
 * Using stlsoft::special_string_instance_0 / stlsoft::special_string_instance_1, all
 * that is required is a simple policy for each type. The following listing is
 * the full definition of the winstl::cwd_policy, which is combined with 
 * stlsoft::special_string_instance_0 to define the
 * winstl::current_directory_a, winstl::current_directory_w and
 * winstl::current_directory types:
 *
\htmlonly
<pre>
template &lt;typename C>
struct cwd_policy
{
  typedef C                           char_type;
  typedef processheap_allocator&lt;C>    allocator_type;
  typedef size_t                      size_type;
  typedef size_type                   (*pfn_type)(char_type *, size_type);

  enum { internalBufferSize       =   128 };
  enum { allowImplicitConversion  =   1   };
  enum { sharedState              =   0   };

  static pfn_type     get_fn()
  {
    return winstl::filesystem_traits&lt;char_type>::<b>get_current_directory</b>;
  }
};
</pre>
\endhtmlonly
 *
 *
 * The following listing is
 * the full definition of the winstl::sysdir_policy, which is combined with 
 * stlsoft::special_string_instance_0 to define the
 * winstl::system_directory_a, winstl::system_directory_w and
 * winstl::system_directory types. Note that the enumerator
 * <code>sharedState</code> is 1, which means that the evaluated value of
 * the Windows <b>system</b> directory will be shared between all instances
 * of the class, since it is immutable for the lifetime of the process (and
 * indeed of an installation).
 *
\htmlonly
<pre>
template &lt;typename C>
struct sysdir_policy
{
  typedef C                           char_type;
  typedef processheap_allocator&lt;C>    allocator_type;
  typedef size_t                      size_type;
  typedef size_type                   (*pfn_type)(char_type *, size_type);

  enum { internalBufferSize       =   32  };
  enum { allowImplicitConversion  =   1   };
  enum { <b>sharedState              =   1</b>   };

  static pfn_type     get_fn()
  {
    return winstl::filesystem_traits&lt;char_type>::<b>get_system_directory</b>;
  }
};
</pre>
\endhtmlonly
 *
 */

