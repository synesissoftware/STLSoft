
/**
 * Created: 3rd June 2006
 * Updated: 14th January 2007
 */


/** \defgroup group__pattern__dereference_proxy Dereference Proxy Pattern
 * \ingroup group__patterns
 *
 * \brief &nbsp;&nbsp;&nbsp;&nbsp;Proscribing Fatuous Output Iterator Syntax.
 *
 * Many common implementations of output iterator classes provide an
 * assignable dereference (i.e. the result of *o is an lvalue) by
 * having <code>operator *()</code> return a reference to the
 * iterator type, and defining an <code>operator =()</code> that
 * takes the value type. The following code illustrates this:
\htmlonly
<pre>
  template &lt;typename T, . . . >
  class acme_output_iterator
  {
  public: // types
    typedef T                                 value_type;
    typedef acme_output_iterator&lt;T, . . . >   class_type;

  public: // Construction, etc.
    . . .

  public: // Output Iterator methods
    class_type &operator ++();
    class_type &operator ++(int);
    <b>class_type &operator *()
    {
      return *this;
    }
    class_type &operator =(value_type const &value)
    {
      . . . // Do the 'output' operation here
    }</b>

  private: // Members, Implementation, etc.
    . . .
  };
</pre>
\endhtmlonly
 *
 * Although this technique is simple, succinct and efficient, it facilitates
 * semantically bogus expressions. Consider the following sample code, using
 * a specialisation of the putative iterator type shown above:
\htmlonly
<pre>
  typedef acme_output_iterator&lt;int, . . .>  iterator_t;
  typedef std::vector&lt;int>                  ints_t;

  ints_t         ints(. . . );

  iterator_t     o(std::cout, "\n");

  std::copy(ints.begin(), ints.end(), o); // This is fine. It outputs all the elements in 'ints' to std::cout

  *o++ = 10; // This is fine. It outputs the integer '10' to std::cout

  o = 11; // This is bogus, but works. It outputs the integer '11' to std::cout!
</pre>
\endhtmlonly
 *
 * Think it queer if you will, but I don't like that kind of thing. Thus
 * was born the \ref group__pattern__dereference_proxy "Dereference Proxy"
 * pattern. An output iterator using this pattern defines a member class
 * template <code>deref_proxy</code>, whose job is to supply the
 * assignment operator. Rewriting the above iterator to use the
 * \ref group__pattern__dereference_proxy "Dereference Proxy"
 * pattern would be as follows:
\htmlonly
<pre>
  template &lt;typename T, . . . >
  class acme_output_iterator
  {
  public: // types
    typedef T                                 value_type;
    typedef acme_output_iterator&lt;T, . . . >   class_type;
  <b>private:
    class deref_proxy;
    friend class deref_proxy;</b>

  public: // Construction, etc.
    . . .

  public: // Output Iterator methods
    class_type &operator ++();
    class_type &operator ++(int);
    <b>deref_proxy operator *()
    {
      return deref_proxy(this);
    }
    // NOTE: No more assignment operator</b>

  private: // Dereference Proxy pattern implementation
    <b>class deref_proxy
    {
    public:
      deref_proxy(concatenator_iterator_type *it)
        : m_it(it)
      {}

    public:
      void operator =(value_type const &value_type)
      {
        m_it->invoke_(value_type);
      }

    private:
      concatenator_iterator_type  *const m_it;

    // Not to be implemented
    private:
      void operator =(deref_proxy const &);
    };

    void invoke_(value_type const &value_type)
    {
      . . . // Do the 'output' operation here
    }</b>

  private: // Members, Implementation, etc.
    . . .
  };
</pre>
\endhtmlonly
 *
 * To be sure, there's quite a bit more code, but expressions of the pattern
 * all take the same, well tested form, the correctness (or lack) of the
 * implementation can be verified easily and definitively, and once written
 * it is not changed.
 *
 * Now we receive the (hopefully!) looked-for compile error in the previous
 * example code:
\htmlonly
<pre>
  typedef acme_output_iterator&lt;int, . . .>  iterator_t;
  . . .

  iterator_t     o(std::cout, "\n");

  o = 11; // Compiler error. Good!
</pre>
\endhtmlonly
 *
 * Components in the STLSoft libraries that use the
 * \ref group__pattern__dereference_proxy "Dereference Proxy"
 * pattern include:
 *
 * - stlsoft::cstring_concatenator_iterator
 * - stlsoft::null_output_iterator
 * - stlsoft::ostream_iterator
 * - stlsoft::string_concatenator_iterator
 *
 * \note There's nothing about the pattern that restricts it to output
 *  iterators. It may be applicable to any type that supports the
 *  dereference operator (<code>operator *()</code>).
 *
 * \remarks The \ref group__pattern__dereference_proxy "Dereference Proxy"
 *  pattern is discussed in part 3 of the forthcoming book
 *  <a href = "http://extendedstl.com">Extended STL</a>, along with a
 *  great many other techniques utilisied throughout the STLSoft libraries.
 */


