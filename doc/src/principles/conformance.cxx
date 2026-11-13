
/**
 * Created: 9th June 2006
 * Updated: 13th November 2026
 */


/** \defgroup group__principle__conformance Intersecting Conformance
 * \ingroup group__principles
 *
 * \brief &nbsp;&nbsp;&nbsp;&nbsp;Identifying Syntactic and Semantic Conformance between Conceptually Related Types while Avoiding Coupling.
 *
 * This page discusses the well-known principles of
 * \ref section__principle__conformance__NC "Named Conformance"
 * and
 * \ref section__principle__conformance__structural_conformance "Structural Conformance",
 * and
 * a refinement of
 * \ref section__principle__conformance__structural_conformance "Structural Conformance"
 * appropriate to the design of lightweight
 * \ref group__pattern__facade "facade"s:
 * \ref section__principle__conformance__intersecting_conformance "Intersecting Conformance".
 *
 * \section section__principle__conformance__NC Named Conformance
 *
 * Two types are <b>named conformant</b> if they share the same name. The
 * significance of this is that types related by inheritance share the same
 * name, that of their common base class. Consider the following class
 * hierarchy:
 *
\htmlonly
<pre>
 class A
 {
 public:
   <b>virtual</b> char const *<b>getName</b>() const { return "A"; }
 };

 class B
   : public A
 {
 public:
   <b>virtual</b> char const *<b>getName</b>() const { return "B"; }
   <b>virtual</b> size_t     <b>getId</b>() const    { return 1; }
 };

 class C
   : public A
 {
 public:
   <b>virtual</b> char const *<b>getName</b>() const { return "C"; }
           size_t     <b>getId</b>() const    { return 2; }
 };

 class D
   : public B
 {
 public:
   <b>virtual</b> char const *<b>getName</b>() const { return "D"; }
   <b>virtual</b> size_t     <b>getId</b>() const    { return 3; }
 };
</pre>
\endhtmlonly
 *
 * Now assume we want to write a function that will print out the class name
 * for instances of these classes:
\htmlonly
<pre>
  void printClassName(A const &ra)
  {
    ra.<b>getName</b>();
  }

  A   a;
  B   b;
  C   c;
  D   d;

  printClassName(a); // Prints "A"
  printClassName(b); // Prints "B"
  printClassName(c); // Prints "C"
  printClassName(d); // Prints "D"
</pre>
\endhtmlonly
 *
 * This is nothing surprising (or at least it shouldn't be to any C++ programmer).
 * It works because classes <code>B</code>, <code>C</code>, and <code>D</code>
 * are all (publicly) derived from <code>A</code>, and because <code>A::getName()</code>
 * is declared virtual. Thus, invocation of <code>getName()</code> on a given
 * object reference (or pointer) depends not on the type of the reference (or
 * pointer) but on the actual type of the object being referenced. This is
 * known as
 * <i><b>Virtual Function Polymorphism</b></i>,
 * or <i><b>Runtime Polymorphism</b></i>
 * or as just <i><b>Polymorphism</b></i>. (The latter, unqualified, name is no longer
 * popular, for reasons that will become clear later in this document.
 * <i><b>Runtime Polymorphism</b></i> is the recommended term, since it precisely
 * describes what is going on: that the type is determined at runtime.)
 *
 * We can say:
 * <i>Classes <code>B</code>, <code>C</code> and
 * <code>D</code> exhibit named conformance with <code>A</code></i>.
 *
 * So far so good.
 *
 * Now assume that we want to write a function that will elicit the Id
 * of instance of class <code>B</code> (or its derived classes):
\htmlonly
<pre>
  void printClassId(B const &rb)
  {
    std::cout &lt;&lt; rb.<b>getId</b>() &lt;&lt; std::endl;
  }

  B   b;
  D   d;

  printClassId(b); // Prints "1"
  printClassId(d); // Prints "3"

</pre>
\endhtmlonly
 *
 * Again, we rely on vtable polymorphism, and that:
 * <i>Class <code>D</code> exhibits named conformance with <code>B</code></i>.
 *
 * Obviously applying <code>printClassId()</code> to an instance of <code>A</code>
 * will be a compile error, since A does not have a member <code>getId()</code>:
\htmlonly
<pre>

  A   a;

  printClassId(a); // compile error: Cannot convert 'A' to 'B const &'
</pre>
\endhtmlonly
 *
 * What should also be understood is that we equally cannot apply
 * <code>printClassId()</code> to an instance of <code>C</code>. Even
 * though <code>C</code> has a <code>getId()</code> method, it is not
 * derived from <code>B</code>, and thus is not compatible: it has a
 * different <i>name</i>.
 *
 * Hence:
 * <i>Class <code>C</code>, is not named conformant with <code>B</code></i>.
 *
 * Put another way, the definition of <code>printClassId()</code> imposes the
 * constraint on any type to which we wish to apply it that it must be
 * <i><b>named-conformant</b></i> with <code>B</code>.
 *
 * To display the Id from C we'd have to overload the
 * <code>printClassId()</code> function:
\htmlonly
<pre>
  void printClassId(C const &rc)
  {
    std::cout &lt;&lt; rc.<b>getId</b>() &lt;&lt; std::endl;
  }

  C   c;

  printClassId(c); // Prints "2"
</pre>
\endhtmlonly
 *
 * Note the code duplication between the two overloads of
 * <code>printClassId()</code>. They're identical in syntax (and
 * semantics) and yet are quite distinct functions.
 *
 * \section section__principle__conformance__structural_conformance Structural Conformance
 *
 * Two types are <b>structurally conformant</b> if instances of them can be placed in
 * syntactically identical constructs and exhibit (appropriately) similar
 * semantics. In other words, they can both compile in the same code and
 * will operate in the same (or suitably similar) manner.
 *
 * Before we start, it's sensible to concede that, absent pre-processor
 * acrobatics, structural conformance is primarily relevant when using
 * templates.
 *
 * Let's recast <code>printClassId()</code> as a function template:
\htmlonly
<pre>
  template &lt;class T&gt;
  void printClassId(T const &rt)
  {
    std::cout &lt;&lt; rt.<b>getId</b>() &lt;&lt; std::endl;
  }
</pre>
\endhtmlonly
 *
 * The template parameter <code>T</code> is used in the function
 * signature, as (part of) the type of the object parameter.
 *
 * No part of the function template definition mentions the actual
 * type of the parameter. What is mentioned, however, is that a
 * (a non-mutating reference to) an instance of <code>T</code> has
 * a member <code>getId</code> which can be involved in a function
 * call expression and, further, that the result of that expression
 * can be used with <code>std::cout</code> and <code>std::endl</code> via the insertion
 * operator.
 *
 * (Note: what may seem relatively obvious syntax above can actually
 * be quite involved and surprising. For example, <code>getId()</code>
 * could be a static method, or could be a member variable of a type
 * that has a function call operator defined. Sometimes things can
 * be even more exotic, involving enumerations and properties. The
 * issue is discussed in greater depth in the chapter "Duck and Goose"
 * from the forthcoming book
 * <a href = "http://extendedstl.com">Extended STL</a>.)
 *
 * This version of <code>printClassId()</code> is compatible with
 * instances of <code>B</code> and <code>D</code>, and also with
 * <code>C</code>.
\htmlonly
<pre>
  B   b;
  C   c;
  D   d;

  printClassId(b); // Prints "1"
  printClassId(c); // Prints "2"
  printClassId(d); // Prints "3"
</pre>
\endhtmlonly
 *
 *
 * Thus we can state:
 * <i>Classes <code>B</code>, <code>C</code> and <code>D</code> are
 * <b>structurally conformant</b></i> with respect to <code>printClassId()</code>.
 *
 * Note the difference in emphasis in this statement. First, we
 * describe this in terms of a <i>mutual</i> conformance between
 * the conformant types, as opposed to a <i>relative</i> conformance
 * in the case of <i><b>named conformance</b></i>. Second, we define
 * their <i><b>structural conformance</b></i> in terms of the
 * requirements of a <i>constraining component</i>, in this case the
 * function template <code>printClassId()</code>. Further, it is
 * important to understand that the enforced constraints of the
 * <i>constraining component</i> are entirely syntactic. Naturally,
 * there is an expectation that syntatically conformant types will
 * also have the semantic conformance, but this is not something
 * that the C++ language can enforce for us. Rather, we need to
 * observe higher level conventions, such as member/method naming
 * conventions.
 *
 * \note There are mechanisms for explicit conformance, such as
 *   Shims, Concept Tagging and Member Type Tagging, but these are
 *   outside the scope of the current discussion. (See
 *   <a href = "http://extendedstl.com">Extended STL</a> for more
 *   details.)
 *
 * \section section__principle__conformance__intersecting_conformance Intersecting Conformance
 *
 * As discussed \ref section__principle__conformance__structural_conformance "above",
 * <i><b>structural conformance</b></i> is the correspondence between
 * syntax and semantics for unrelated types, for a given syntactic context (or set
 * of contexts).
 *
 * When designing \ref group__pattern__facade "facade"s one continually meets the challenge of abstracting
 * common functionality between disparate technologies/APIs. Operating systems
 * APIs are a very good example of this.
 *
 * Consider that we want to provide a \ref group__pattern__facade "facade"
 * over the Windows mutex kernel object. Like most Windows kernel objects,
 * the mutex may, optionally, be named to facilitate sharing between
 * processes, and/or carry security attributes. They may be created already
 * in the 'acquired' state. They are always recursive
 * (which is to say that a thread that owns a mutex may 'acquire' it again).
 *
 * The \ref group__project__winstl "WinSTL" project defines the facade
 * winstl::process_mutex, which has the following class interface
 * (<code>explicit</code> constructor qualifiers are not shown for clarity):
\htmlonly
<pre>
  class winstl::process_mutex
  {
  public: // types
    typedef HANDLE        handle_type;
    typedef process_mutex class_type;

  public: // construction
    process_mutex();
    process_mutex(char const *mutexName);
    process_mutex(wchar_t const *mutexName);
    process_mutex(char const *mutexName, bool bInitiallyAcquired);
    process_mutex(wchar_t const *mutexName, bool bInitiallyAcquired);
    process_mutex(char const *mutexName, bool bInitiallyAcquired, SECURITY_ATTRIBUTES *securityAttrs);
    process_mutex(wchar_t const *mutexName, bool bInitiallyAcquired, SECURITY_ATTRIBUTES *securityAttrs);
    ~process_mutex();

  public: // operations
    void lock();
    bool lock(DWORD waitMilliseconds);
    bool try_lock();
    void unlock();

  public: // accessors
    handle_type get();
  };
</pre>
\endhtmlonly
 *
 * Now we want to provide a corresponding \ref group__pattern__facade "facade"
 * for the PThreads mutex (<code>pthread_mutex_t</code>). Unlike the Windows
 * kernel object, PThreads' mutexes may not be named and do not support
 * (Windows-like) security information. They do allow sharing, but in a much
 * different (and largely) incompatible way to Windows: the mutex must be
 * created as shareable, and is shared between processes via shared memory,
 * rather than by accessing a kernel handle as in Windows.
 *
 * The \ref group__project__unixstl "UNIXSTL" project defines the facade
 * <code>unixstl::process_mutex</code>, which has the following class interface
 * (<code>explicit</code> constructor qualifiers are not shown for clarity):
\htmlonly
<pre>
  class unixstl::process_mutex
  {
  public: // types
    typedef pthread_mutex_t *handle_type;
    typedef process_mutex   class_type;

  public: // construction
    process_mutex();
    process_mutex(bool bRecursive);
    process_mutex(int pshared, bool bRecursive);
    ~process_mutex();

  public: // operations
    void lock();
    bool try_lock();
    void unlock();

  public: // accessors
    handle_type get();
  };
</pre>
\endhtmlonly
 *
 * Clearly, each class interface contains elements that the other misses.
 * There are two conventional approaches to this situation:
 *
 * \subsection subsection__conformance__emulate_missing_functionality Emulate Missing Functionality
 *
 * In this approach functionality present in one interface that is missing
 * in the other is emulated. For example, we <i>could</i> emulate the
 * <code>winstl::process_mutex::wait(DWORD)</code> method for
 * <code>unixstl::process_mutex</code> by using a retry loop and
 * a <code>unixstl::micro_sleep()</code> operation.
 *
 * However, such approaches can be ugly, or unsafe, or inefficient, and are often
 * all three. Furthermore, there are many cases where no meaningful analogue
 * functionality can be specified. For example, we cannot incline the
 * Windows mutex kernel object to reject recursive acquisition to be in line
 * with the PThreads version. Nor can we apply the equivalent of Windows
 * security information to a PThreads mutex. These things are, to all intents
 * and purposes, impossible.
 *
 * \subsection subsection__conformance__provide_only_common_functionality Provide Only Common Functionality
 *
 * Given an impossibility of
 * \ref subsection__conformance__emulate_missing_functionality "emulating missing functionality"
 * for a given facade,
 * one might think that the only reasonable approach is to provide only
 * what functionality is, or can be readily made to be, common to both. In
 * the case of the <code>process_mutex</code>, this would yield class interfaces
 * as follows:
\htmlonly
<pre>
  class winstl::process_mutex
  {
  public: // types
    typedef HANDLE        handle_type;
    typedef process_mutex class_type;

  public: // construction
    process_mutex();
    ~process_mutex();

  public: // operations
    void lock();
    bool try_lock();
    void unlock();

  public: // accessors
    handle_type get();
  };
</pre>
\endhtmlonly
 *
 * and:
\htmlonly
<pre>
  class unixstl::process_mutex
  {
  public: // types
    typedef pthread_mutex_t *handle_type;
    typedef process_mutex   class_type;

  public: // construction
    process_mutex();
    ~process_mutex();

  public: // operations
    void lock();
    bool try_lock();
    void unlock();

  public: // accessors
    handle_type get();
  };
</pre>
\endhtmlonly
 *
 * And, since they're now virtually identical, there'd be little point in
 * maintaining separate class definitions, and we would instead define a
 * single class <code>platformstl::process_mutex</code>:
\htmlonly
<pre>
  class platformstl::process_mutex
  {
  public: // types
<span class="preprocessor">#if defined(PLATFORMSTL_OS_IS_UNIX)</span>
    typedef pthread_mutex_t *handle_type;
<span class="preprocessor">#elif defined(PLATFORMSTL_OS_IS_WIN32)</span>
    typedef HANDLE          handle_type;
<span class="preprocessor">#else /* ? OS */</span>
<span class="preprocessor"># error Operating system not discriminated</span>
<span class="preprocessor">#endif /* OS */</span>
    typedef process_mutex   class_type;

  public: // construction
    process_mutex();
    ~process_mutex();

  public: // operations
    void lock();
    bool try_lock();
    void unlock();

  public: // accessors
    handle_type get();
  };
</pre>
\endhtmlonly
 *
 * This is useful, to be sure, but Windows users may find themselves needing
 * to be able to use a named mutex, or apply security information. Worse,
 * the issue of choice regarding recursive nature in UNIX is taken away from
 * the user. If the platformstl::process_mutex now mandates recursion the
 * UNIX user may pay unncessary performance costs; if the class mandates
 * non-recursive nature then the class has significantly different behaviour
 * depending on operating system, something that is very wrong and guaranteed
 * to result in <code>platformstl::process_mutex</code> being avoided like
 * the plague.
 *
 * \subsection subsection__conformance__embrace_variety Stipulate Intersecting Functionality but Embrace Variety
 *
 * Rather than attempt either of these absolutist approaches, the principle of
 * <i><b>Intersecting Conformance</b></i>
 * dictates that \ref group__pattern__facade "facade"s for disparate
 * technologies should employ
 * \ref section__principle__conformance__structural_conformance "structural conformance"
 * only to the degree of the intersection of (meaningfully) identical functionality,
 * rather than employing significant additional functionality to achieve total
 * structural conformance. In other words, where functionality is identical, or
 * very similar,
 * \ref section__principle__conformance__structural_conformance "structural conformance"
 * is employed to ensure exact syntactic correspondence. Where the functionality is
 * different, such that conformant semantics is not possible, or realisable in an
 * efficient and robust manner, conformance should be explicitly eschewed.
 *
 * Thus, the intersection of the functionality of winstl::process_mutex
 * and unixstl::process_mutex, as shown in the definition of process_mutex given in the
 * \ref subsection__conformance__provide_only_common_functionality "previous section",
 * will be as follows:
\htmlonly
<pre>
  class ????::process_mutex
  {
  public: // types
    typedef ????            handle_type;
    typedef process_mutex   class_type;

  public: // construction
    process_mutex();
    ~process_mutex();

  public: // operations
    void lock();
    bool try_lock();
    void unlock();

  public: // accessors
    handle_type get();
  };
</pre>
\endhtmlonly
 *
\htmlonly
<pre>
 *
</pre>
\endhtmlonly
 *
 * Consequently unixstl::process_mutex and winstl::process_mutex provide a meaningful subset of
 * common functionality (highlighted below) but each retain their important particular
 * features:
\htmlonly
<pre>
  class winstl::process_mutex
  {
  public: // types
    typedef HANDLE        handle_type;
<pre class="highlight">    typedef process_mutex class_type;</pre>
  public: // construction
<pre class="highlight">    process_mutex();</pre>    process_mutex(char const *mutexName);
    process_mutex(wchar_t const *mutexName);
    process_mutex(char const *mutexName, bool bInitiallyAcquired);
    process_mutex(wchar_t const *mutexName, bool bInitiallyAcquired);
    process_mutex(char const *mutexName, bool bInitiallyAcquired, SECURITY_ATTRIBUTES *securityAttrs);
    process_mutex(wchar_t const *mutexName, bool bInitiallyAcquired, SECURITY_ATTRIBUTES *securityAttrs);
<pre class="highlight">    ~process_mutex();</pre>
  public: // operations
<pre class="highlight">    void lock();</pre>    bool lock(DWORD waitMilliseconds);
<pre class="highlight">    bool try_lock();
    void unlock();</pre>
  public: // accessors
<pre class="highlight">    handle_type get();</pre>  };
</pre>
\endhtmlonly
 *
 * and:
\htmlonly
<pre>
  class unixstl::process_mutex
  {
  public: // types
    typedef pthread_mutex_t *handle_type;
<pre class="highlight">    typedef process_mutex   class_type;</pre>
  public: // construction
<pre class="highlight">    process_mutex();</pre>    process_mutex(bool bRecursive);
    process_mutex(int pshared, bool bRecursive);
<pre class="highlight">    ~process_mutex();</pre>
  public: // operations
<pre class="highlight">    void lock();
    bool try_lock();
    void unlock();</pre>
  public: // accessors
<pre class="highlight">    handle_type get();</pre>  };
</pre>
\endhtmlonly
 *
 * In this way, rich but thin \ref group__pattern__facade "facade"s may be
 * provided for a given operating system/technology area, while still
 * supporting the construction of higher level components that rely on a
 * common abstracted view of the services provided.
 */

