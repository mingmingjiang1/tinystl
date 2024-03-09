#ifndef VECTOR_H
#define VECTOR_H

#include "iterator/iterator.h"
#include "iterator/iterator_traits.h"
#include "adapter.h"
#include "allocator/allocator.h"
#include "allocator/alloc.h"

namespace tinystl
{
  template <typename T, typename Alloc = Allocator<T>>
  class Vector
  {
  public:
    typedef T *iterator;

    typedef Alloc data_allocator;

    typedef typename data_allocator::value_type value_type;
    typedef typename data_allocator::size_type size_type;

    typedef typename data_allocator::reference reference;
    typedef typename data_allocator::const_reference const_reference;

    /** constructor */
    typedef tinystl::Construct<T> constructor;

    /*
      另一种写法：
      typedef T* iterator;
      typedef Iterator_Traits<iterator, tinystl::random_access_iterator_tag> __traits_type; // buildin pointer
     */

    typedef const value_type *const_iterator;
    typedef tinystl::reverse_iterator<iterator> reverse_iterator;

    typedef tinystl::reverse_iterator<const_iterator> const_reverse_iterator;

    Vector(size_type size);

    Vector(T *first, T *last);

    Vector(size_type size, const T &value); // value为临时对象的时候，value在当前行之后的生命周期结束了

    Vector(std::initializer_list<T> arr);
    Vector();
    Vector(const Vector &vec);
    ~Vector();
    Vector<T, Alloc> &operator=(const Vector<T, Alloc> &vec);

    void push_back(const value_type &vec);

    void clear();

    void pop_back();
    void erase(const iterator it);

    void destroy();

    reverse_iterator rbegin() _GLIBCXX_NOEXCEPT;

    const reverse_iterator rbegin() const _GLIBCXX_NOEXCEPT;

    reverse_iterator rend();

    const reverse_iterator rend() const _GLIBCXX_NOEXCEPT;

    const_reverse_iterator crbegin() const _GLIBCXX_NOEXCEPT;
    const_reverse_iterator crend() const _GLIBCXX_NOEXCEPT;

    void insert(iterator it, value_type val);

    value_type front();

    value_type back();

    iterator begin() _GLIBCXX_NOEXCEPT;

    const_iterator begin() const _GLIBCXX_NOEXCEPT;

    const_iterator cbegin() const _GLIBCXX_NOEXCEPT;

    iterator end() _GLIBCXX_NOEXCEPT;

    const_iterator end() const _GLIBCXX_NOEXCEPT;

    const_iterator cend() const _GLIBCXX_NOEXCEPT;

    size_type capacity();

    bool empty();

    size_type size() const;

    value_type &operator[](int index);

    bool operator==(value_type &vec);

  private:
    T *m_data;
    size_type _size;
    size_type _capacity;
  };
}

#include "vector.tcc"

#endif