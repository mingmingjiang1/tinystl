#ifndef ITERATOR
#define ITERATOR

/**
 * @brief List Iterator Base Class
 *      Random_Access_Iterator
 * Base
 *      Sequence_Access_Iterator
 */
#include "iterator_traits.h"
#include <cstddef>
#include <iostream>

template <typename _Tp, typename _Tag>
class Iterator
{
  typedef _Tp value_type;
  typedef ptrdiff_t difference_type;
  typedef _Tp *pointer;
  typedef _Tp &reference;
  typedef _Tag iterator_category;
};

int count = 0;

template <typename T, typename Container>
class Random_Access_Iterator
{
public:
  // typedef T value_type;
  // typedef T *pointer;
  // typedef random_access_iterator_tag iterator_category;
  typedef Iterator_Traits<T, tinystl::random_access_iterator_tag> __traits_type;

  typedef T *iterator_type;

  // iterator必须包含的五种typedef
  typedef typename __traits_type::iterator_category iterator_category;
  typedef typename __traits_type::value_type value_type;
  typedef typename __traits_type::difference_type difference_type;
  typedef typename __traits_type::reference reference;
  typedef typename __traits_type::pointer pointer;

  typedef Random_Access_Iterator<T, Container> self;

  // Random_Access_Iterator(pointer M_current) : _M_current(M_current) {}
  explicit Random_Access_Iterator(T *__i) : _M_current(__i) {}

  self &operator++()
  {
    std::cout << _M_current << "   heeee-----" << std::endl;
    ++_M_current;
    std::cout << _M_current << "   heeee++++" << std::endl;
    return *this;
  }

  self &operator--()
  {
    --_M_current;
    return *this;
  }

  self operator-(difference_type __n) { return self(_M_current - __n); }

  self operator+(difference_type __n) { return self(_M_current + __n); }

  self operator++(int)
  {
    self temp = *this;
    ++_M_current;
    return temp;
  }
  self operator--(int)
  {
    self temp(_M_current);
    --_M_current;
    return temp;
  }
  bool operator==(const Random_Access_Iterator &it) const
  {
    return _M_current == it._M_current;
  }
  bool operator!=(const Random_Access_Iterator &it) const
  {
    // it.current是end
    std::cout << it._M_current << "   jjjjjjjjj   " << _M_current << std::endl;
    return it._M_current != _M_current;
  }

  reference operator[](difference_type __n) const _GLIBCXX_NOEXCEPT
  {
    return _M_current[__n];
  }

  // +=操作符 跳跃n个difference_type
  Random_Access_Iterator &operator+=(difference_type __n) _GLIBCXX_NOEXCEPT
  {
    _M_current += __n;
    return *this;
  }

  // -=操作符 后退n个difference_type
  Random_Access_Iterator &operator-=(difference_type __n) _GLIBCXX_NOEXCEPT
  {
    _M_current -= __n;
    return *this;
  }

  reference operator*() { return *_M_current; }

  /*
    T &operator*() { return _cur->m_data; }

    T *operator->() { return &_cur->m_data; }
 */

  pointer operator->()
  {
    return _M_current;
    ;
  }

  iterator_type base() const { return _M_current; }

private:
  pointer _M_current;
};

template <typename T>
struct node
{
  T m_data;
  node *prev;
  node *next;
  node() : prev(nullptr), next(nullptr) {}
};

template <typename _Iterator, typename _Container>
typename Random_Access_Iterator<_Iterator, _Container>::difference_type
operator-(const Random_Access_Iterator<_Iterator, _Container> &__lhs,
          const Random_Access_Iterator<_Iterator, _Container> &__rhs) noexcept
{
  return __lhs.base() - __rhs.base();
}

template <typename _Iterator, typename _IteratorR, typename _Container>
typename Random_Access_Iterator<_Iterator, _Container>::difference_type
operator+(const Random_Access_Iterator<_Iterator, _Container> &__lhs,
          const Random_Access_Iterator<_Iterator, _Container> &__rhs) noexcept
{
  return __lhs.base() + __rhs.base();
}

template <typename _Iterator, typename _IteratorR, typename _Container>
bool operator!=(const Random_Access_Iterator<_Iterator, _Container> &__lhs,
                const Random_Access_Iterator<_Iterator, _Container> &__rhs)
{
  return !(__lhs == __rhs);
}

/**
 * @brief List Node Class
 *
 */
template <typename T>
class Sequence_Access_Iterator
{
public:
  typedef node<T> self;

  Sequence_Access_Iterator(self *cur) : _cur(cur){};

  Sequence_Access_Iterator operator++()
  {
    _cur = _cur->next;
    return *this;
  }

  Sequence_Access_Iterator operator--()
  {
    _cur = _cur->prev;
    return *this;
  }

  Sequence_Access_Iterator operator++(int)
  {
    Sequence_Access_Iterator temp(_cur);
    _cur = _cur->next;
    return temp;
  }
  Sequence_Access_Iterator operator--(int)
  {
    Sequence_Access_Iterator temp(_cur);
    _cur = _cur->prev;
    return temp;
  }
  bool operator==(const Sequence_Access_Iterator &it) const
  {
    return _cur == it._cur;
  }
  bool operator!=(const Sequence_Access_Iterator &it) const
  {
    return _cur != it._cur;
  }

  T &operator*() { return _cur->m_data; }

  T *operator->() { return &_cur->m_data; }

private:
  self *_cur;
};

// iterator 模板
template <class Category, class T, class Distance = ptrdiff_t,
          class Pointer = T *, class Reference = T &>
struct iterator
{
  typedef Category iterator_category;
  typedef T value_type;
  typedef Pointer pointer;
  typedef Reference reference;
  typedef Distance difference_type;
};

// iterator traits

template <class T>
struct has_iterator_cat
{
private:
  struct two
  {
    char a;
    char b;
  };
  template <class U>
  static two test(...);
  template <class U>
  static char test(typename U::iterator_category * = 0);

public:
  static const bool value = sizeof(test<T>(0)) == sizeof(char);
};

template <class Iterator, bool>
struct iterator_traits_impl
{
};

template <class Iterator>
struct iterator_traits_impl<Iterator, true>
{
  typedef typename Iterator::iterator_category iterator_category;
  typedef typename Iterator::value_type value_type;
  typedef typename Iterator::pointer pointer;
  typedef typename Iterator::reference reference;
  typedef typename Iterator::difference_type difference_type;
};

template <class Iterator>
class Reverse_Iterator
{
private:
  Iterator current; // 记录对应的正向迭代器

public:
  typedef Iterator_Traits<Iterator, tinystl::random_access_iterator_tag> __traits_type;
  // 反向迭代器的五种相应型别
  typedef typename __traits_type::value_type value_type;
  typedef typename __traits_type::difference_type difference_type;
  typedef typename __traits_type::reference reference;
  typedef typename __traits_type::pointer pointer;

  typedef Iterator iterator_type;
  typedef Reverse_Iterator<Iterator> self;

public:
  // 构造函数
  Reverse_Iterator() {}
  explicit Reverse_Iterator(iterator_type i) : current(i) {}
  Reverse_Iterator(const self &rhs) : current(rhs.current) {}

public:
  // 取出对应的正向迭代器
  iterator_type base() const { return current; }

  // 重载操作符
  reference operator*() const
  { // 实际对应正向迭代器的前一个位置
    auto tmp = current;
    return *--tmp;
  }
  pointer operator->() const { return &(operator*()); }

  // 前进(++)变为后退(--)
  self &operator++()
  {
    --current;
    return *this;
  }
  self operator++(int)
  {
    self tmp = *this;
    --current;
    return tmp;
  }
  // 后退(--)变为前进(++)
  self &operator--()
  {
    ++current;
    return *this;
  }
  self operator--(int)
  {
    self tmp = *this;
    ++current;
    return tmp;
  }

  self &operator+=(difference_type n)
  {
    current -= n;
    return *this;
  }
  self operator+(difference_type n) const { return self(current - n); }
  self &operator-=(difference_type n)
  {
    current += n;
    return *this;
  }
  self operator-(difference_type n) const { return self(current + n); }
  // size_t operator-(self n) const { return 9; }

  reference operator[](difference_type n) const { return *(*this + n); }
};

// 重载 operator-
template <class Iterator>
typename Reverse_Iterator<Iterator>::difference_type
operator-(const Reverse_Iterator<Iterator> &lhs,
          const Reverse_Iterator<Iterator> &rhs)
{
  return rhs.base() - lhs.base();
}

#endif
