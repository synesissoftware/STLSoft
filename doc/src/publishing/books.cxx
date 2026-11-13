
/**
 * Created: 13th March 2007
 * Updated: 13th November 2026
 */


/** \defgroup group__publishing__books Books
 * \ingroup group__publishing
 *
 * \brief Books that pertain to the STLSoft libraries
 *
 * Matthew Wilson has published two books that pertain to the STLSoft libraries:
 *
\htmlonly
<!--
<ul>
 <li>
  <a href="#section__publishing__books__imperfectcplusplus">
   Imperfect C++
   <img src="http://synesis.com.au/pics/impcpp.jpg" width="40" height="50"/>
  </a>
 </li>
 <li>
  <a href="#section__publishing__books__xstlv1">
   Extended STL, volume 1
   <img src="http://synesis.com.au/publishing/xstl/xstlv1-small.jpg" width="40" height="50"/>
  </a>
 </li>
</ul>
-->
\endhtmlonly

 * - \ref section__publishing__books__imperfectcplusplus "Imperfect C++" 
 * - \ref section__publishing__books__xstlv1 "Extended STL, volume 1"
 *
 * There are also two more books in preparation:
 *
 * - <a href="http://breakingupthemonolith.com/" target="_blank">Breaking Up The Monolith</a>
 * - <a href="http://extendedstl.com/" target="_blank">Extended STL, volume 2</a>
 *
 *
 *
 * \section section__publishing__books__imperfectcplusplus Imperfect C++
 *
\htmlonly
<br/>
<img src="http://synesis.com.au/pics/impcpp.jpg" width="142" height="186" align="right" />
\endhtmlonly
 *
 * <a href="http://imperfectcplusplus.com/" target="_blank">Imperfect C++</a> was
 * published by Addison-Wesley in October 2004. It has attracted many
 * favourable (and two unfavourable)
 * <a href="http://imperfectcplusplus.com/reviews.html" target="_blank">reviews</a>.
 *
 * You can order a copy on Amazon.com
 * <a href="http://www.amazon.com/Imperfect-C%2B%2B-Practical-Solutions-Programming/dp/0321228774/" target="_blank">here</a>.
 *
 * The book's website is <a href="http://imperfectcplusplus.com/" target="_blank">http://imperfectcplusplus.com/</a>
 *
 * The material pertaining to STLSoft is as follows:
 *
 * <b>Part 1 - Fundamentals</b>:
 * - <b>Chapter 1 - Enforcing Design: \ref group__library__utility__constraints "Constraints", Contracts and Assertions</b>
 * - <b>Chapter 5 - Object Access Models</b>: stlsoft::lock_traits, stlsoft::lock_scope, winstl::thread_mutex
 *
 * <b>Part 2 - Surviving the Real World</b>:
 * - <b>Chapter 10 - Threading</b>: atomic integer operations, spin_mutex
 * - <b>Chapter 11 - Statics</b>: high_performance_counter
 *
 * <b>Part 1 - Language Concerns</b>:
 * - <b>Chapter 13 - Fundamental Types</b>: STLSOFT_NUM_ELEMENTS(), stlsoft::array_proxy
 * - <b>Chapter 14 - Arrays and Pointers</b>: \c NULL
 * - <b>Chapter 16 - Keywords</b>: stlsoft::explicit_cast
 * - <b>Chapter 18 - Typedefs</b>: stlsoft::true_typedef
 *
 * <b>Part 1 - Cognizant Conversions</b>:
 * - <b>Chapter 19 - Casts</b>: comstl::interface_cast
 * - <b>Chapter 20 - \ref group__concept__Shim "Shims"</b>
 *
 * <b>Part 1 - Operators</b>:
 * - <b>chapter 24 - operator bool()</b>: stlsoft::operator_bool_generator
 * - <b>Chapter 25 - Fast, Non-intrusive String Concatenation</b>: stlsoft::fast_string_concatenator
 * - Chapter 28 - : stlsoft::unused_return_value_monitor
 * - Chapter 29 - : stlsoft::sinteger64
 *
 * <b>Part 1 - Extending C++</b>:
 * - Chapter 31 - : stlsoft::integer_to_string(),
 * - <b>Chapter 32 - Memory</b>: stlsoft::auto_buffer, stlsoft::pod_vector
 * - <b>Chapter 33 - Multidimensional Arrays</b>: stlsoft::fixed_array_1d, stlsoft::fixed_array_2d, stlsoft::fixed_array_3d, stlsoft::fixed_array_4d
 * - <b>Chapter 34 - Ranges</b>: \ref group__project__rangelib "Ranges"
 * - <b>Chapter 35 - Properties</b>: \ref group__library__Properties "Properties"
 *
 *
 *
 * \section section__publishing__books__xstlv1 Extended STL, volume 1: Collections and Iterators
 *
\htmlonly
<br/>
<img src="http://synesis.com.au/publishing/xstl/xstlv1-small.jpg" width="133" height="167" align="right" />
\endhtmlonly
 *
 * <a href="http://extendedstl.com/" target="_blank">Extended STL, volume 1</a> will be
 * published by Addison-Wesley in June 2007.
 *
 * You can pre-order a copy on Amazon.com
 * <a href="http://www.amazon.com/Extended-STL-1-Matthew-Wilson/dp/0321305507/" target="_blank">here</a>.
 *
 * The book's website is <a href="http://extendedstl.com/" target="_blank">http://extendedstl.com/</a>
 *
 * The material pertaining to STLSoft is as follows:
 *
 * <b>Part 1 - Foundations</b>:
 * - <b>Chapter 12 - Template Tools</b>: stlsoft::allocator_selector, stlsoft::true_typedef, stlsoft::
 * - <b>Chapter 16 - Essential Components</b>: stlsoft::auto_buffer, unixstl::filesystem_traits and winstl::filesystem_traits, stlsoft::scoped_handle, dl_call
 *
 * <b>Part 2 - Collections</b>:
 * - <b>Chapter 17 - Adapting The glob API</b>: unixstl::glob_sequence
 * - <b>Chapter 19 - Adapting the opendir/readdir API</b>: unixstl::readdir_sequence
 * - <b>Chapter 20 - Adapting the FindFirstFile/FindNextFile API</b>: winstl::basic_findfile_sequence
 * - <b>Chapter 21 - Intermezzo: When the Efficiency/Usability Balance is Tipped: Enumerating FTP Server Directories</b>: inetstl::basic_findfile_sequence and inetstl::basic_ftpdir_sequence
 * - <b>Chapter 22 - Enumerating Processes and Modules</b>: winstl::pid_sequence and winstl::process_module_sequence
 * - <b>Chapter 24 - Adapting MFC's CArray Container Family</b>: mfcstl::carray_cadaptor and mfcstl::carray_iadaptor
 * - <b>Chapter 25 - A Map Of The Environment</b>: platformstl::environment_map
 * - <b>Chapter 26 - Travelling Back and Forth on the Z-Plane</b>: winstl::child_window_sequence and winstl::peer_window_sequence
 * - <b>Chapter 27 - String Tokenisation</b>: the venerable, but inordinately efficient, stlsoft::string_tokeniser
 * - <b>Chapter 28 - Adapting COM Enumerators</b>: comstl::enumerator_sequence
 * - <b>Chapter 30 - Adapting COM Collections</b>: comstl::collection_sequence
 * - <b>Chapter 31 - Gathering Scattered I/O</b>: acestl::message_queue_sequence
 *
 * <b>Part 3 - Iterators</b>:
 * - <b>Chapter 34 - An Enhanced ostream_iterator</b>: stlsoft::ostream_iterator
 * - <b>Chapter 36 - Transform Iterator</b>: stlsoft::transform_iterator
 * - <b>Chapter 38 - Member Selector Iterator</b>: stlsoft::member_selector_iterator
 * - <b>Chapter 39 - C-style String Concatenation</b>: stlsoft::cstring_concatenator_iterator
 * - <b>Chapter 40 - String Object Concatenation</b>: stlsoft::string_concatenator_iterator
 * - <b>Chapter 41 - Adapted Iterator Traits</b>: stlsoft::adapted_iterator_traits
 * - <b>Chapter 42 - Filtered Iteration</b>: stlsoft::filter_iterator
 */

