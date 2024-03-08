#ifndef ITERATOR
#define ITERATOR

/**
 * @brief List Iterator Base Class
 *      Random_Access_Iterator
 * Base
 *      Bidirectional_Access_Iterator
 */
#include "iterator_traits.h"
#include <cstddef>
#include <iostream>
#include <assert.h>
#include "./list/node.h"



// iterator 模板
template <typename T>
struct iterator_base
{

public:
  typedef T value_type;
  typedef T *pointer;
  typedef T &reference;
  typedef ptrdiff_t difference_type;
  typedef tinystl::random_access_iterator_tag iterator_category;

  iterator_base() = default;
  explicit iterator_base(pointer __i, size_t size = 0) : _M_current(__i), m_start(__i), m_finish(__i + size) {}
  // explicit iterator_base(pointer __i) : _M_current(__i) {}
  pointer __get_current() const
  {
    return this->_M_current;
  }

protected:
  pointer _M_current, m_start, m_finish;

  // virtual operator* operator-> operator+ operator++ operator== operator !=
  virtual bool operator==(const iterator_base &) const = 0;
  virtual bool operator!=(const iterator_base &) const = 0;
};

template <typename T>
struct iterator_base<tinystl::list_node_base<T>>
{

public:
  typedef tinystl::list_node_base<T> value_type;
  typedef tinystl::list_node_base<T> *pointer;
  typedef tinystl::list_node_base<T> &reference;
  typedef ptrdiff_t difference_type;
  typedef tinystl::random_access_iterator_tag iterator_category;

  iterator_base() = default;
  explicit iterator_base(pointer __i, size_t size = 0) : _M_current(__i), m_start(__i), m_finish(__i + size) {}
  // explicit iterator_base(pointer __i) : _M_current(__i) {}
  pointer __get_current() const
  {
    return this->_M_current;
  }

protected:
  pointer _M_current, m_start, m_finish;

  virtual bool operator==(const iterator_base<tinystl::list_node_base<T>> &) const = 0;
  virtual bool operator!=(const iterator_base<tinystl::list_node_base<T>> &) const = 0;
};

template <typename T, typename Container>
class Output_Iterator : public iterator_base<T>
{

public:
  typedef Output_Iterator<T, Container> self;

  typedef iterator_base<T> self_base;
  typedef typename self_base::value_type value_type;
  typedef typename self_base::pointer pointer;
  typedef typename self_base::reference reference;
  typedef typename self_base::difference_type difference_type;

  Output_Iterator() : iterator_base<T>() {}

  explicit Output_Iterator(pointer __i, size_t size = 0) : iterator_base<T>(__i, size) {}

  self &operator++()
  {
    // if (this->_M_current >= this->m_finish)
    // {
    //   pointer tmp = new T();
    //   *tmp = T();
    //   return *tmp;
    // }
    ++this->_M_current;
    return *this;
  }

  self operator+(difference_type __n) { return self(this->_M_current + __n); }

  self operator++(int)
  {
    self temp = *this;
    ++this->_M_current;
    return temp;
  }

  bool operator==(const self_base &it) const override
  {
    return this->_M_current == it.__get_current();
  }
  bool operator!=(const self_base &it) const override
  {
    return it.__get_current() != this->_M_current;
  }

  // reference operator*() const
  // {
  //   if (this->_M_current >= this->m_finish)
  //   {
  //     pointer tmp = new T();
  //     *tmp = T();
  //     return *tmp;
  //   }
  //   return *this->_M_current;
  // }

  pointer operator->()
  {
    return this->_M_current;
    ;
  }

  self &operator=(const value_type &it) const
  {
    this->_M_current = &it;
    return *this;
  }

  pointer base() const { return this->_M_current; }
};

template <typename T, typename Container>
class Input_Iterator : public iterator_base<T>
{

public:
  typedef Input_Iterator<T, Container> self;

  typedef iterator_base<T> self_base;
  typedef typename self_base::value_type value_type;
  typedef typename self_base::pointer pointer;
  typedef typename self_base::reference reference;
  typedef typename self_base::difference_type difference_type;

  Input_Iterator() : iterator_base<T>() {}

  explicit Input_Iterator(pointer __i, size_t size = 0) : iterator_base<T>(__i, size) {}

  self &operator++()
  {
    if (this->_M_current >= this->m_finish)
    {

      T tmp = T();
      return tmp;
    }
    ++this->_M_current;
    return *this;
  }

  self &operator--()
  {
    if (this->_M_current == this->m_start)
    {
      throw std::out_of_range("Negative distance");
    }
    --this->_M_current;
    return *this;
  }

  self operator-(difference_type __n) { return self(this->_M_current - __n); }

  self operator+(difference_type __n) { return self(this->_M_current + __n); }

  self operator++(int)
  {
    self temp = *this;
    ++this->_M_current;
    return temp;
  }
  self_base &operator--(int)
  {
    self temp(this->_M_current);
    --this->_M_current;
    return temp;
  }
  bool operator==(const self_base &it) const override
  {
    return this->_M_current == it.__get_current();
  }
  bool operator!=(const self_base &it) const override
  {
    return it.__get_current() != this->_M_current;
  }

  self &operator=(const self &it) const
  { // const 不允许修改
    this->_M_current = it.__get_current();
    return *this;
  }

  reference operator[](difference_type __n) const _GLIBCXX_NOEXCEPT
  {
    return this->m_start[__n];
  }

  // +=操作符 跳跃n个difference_type
  self &operator+=(difference_type __n) _GLIBCXX_NOEXCEPT
  {
    this->_M_current += __n;
    return *this;
  }

  // -=操作符 后退n个difference_type
  self &operator-=(difference_type __n) _GLIBCXX_NOEXCEPT
  {
    this->_M_current -= __n;
    return *this;
  }

  reference operator*()
  {
    if (this->_M_current >= this->m_finish)
    {
      T tmp = T();
      return tmp;
    }
    return *this->_M_current;
  }

  pointer operator->()
  {
    return this->_M_current;
    ;
  }

  pointer base() const { return this->_M_current; }
};

// T是迭代器
template <typename T, typename Container>
class Random_Access_Iterator : public Output_Iterator<T, Container>
{

public:
  typedef Random_Access_Iterator<T, Container> self;

  typedef iterator_base<T> self_base;
  typedef typename self_base::value_type value_type;
  typedef typename self_base::pointer pointer;
  typedef typename self_base::reference reference;
  typedef typename self_base::difference_type difference_type;

  typedef tinystl::Iterator_Traits<self> __traits_type;

  Random_Access_Iterator() : Output_Iterator<T, Container>() {}

  explicit Random_Access_Iterator(pointer __i, size_t size = 0) : Output_Iterator<T, Container>(__i, size) {}

  self &operator=(const self &it)
  {
    this->_M_current = it._M_current;
    this->m_finish = it.m_finish;
    this->m_start = it.m_start;
    return *this;
  }

  self &operator++()
  {
    // if (this->_M_current >= this->m_finish)
    // {
    //   self* tmp = new self();
    //   *tmp = self();
    //   return *tmp;
    // }
    ++this->_M_current;
    return *this;
  }

  self &operator--()
  {
    if (this->_M_current == this->m_start)
    {
      throw std::out_of_range("Negative distance");
    }
    --this->_M_current;
    return *this;
  }

  self operator-(difference_type __n) { return self(this->_M_current - __n); }

  self operator+(difference_type __n) { return self(this->_M_current + __n); }

  self &operator++(int)
  {
    ++this->_M_current;
    return *this;
  }
  self operator--(int)
  {
    self temp = *this;
    --this->_M_current;
    return temp;
  }
  bool operator==(const self_base &it) const override
  {
    return this->_M_current == it.__get_current();
  }
  bool operator!=(const self_base &it) const override
  {
    // it.current是end
    // std::cout << "end:>>>>> " << it._M_current << "   begin:>>>>>>   " << _M_current << std::endl;
    return it.__get_current() != this->_M_current;
  }

  reference operator[](difference_type __n) const _GLIBCXX_NOEXCEPT
  {
    return this->m_start[__n];
  }

  // +=操作符 跳跃n个difference_type
  self &operator+=(difference_type __n) _GLIBCXX_NOEXCEPT
  {
    this->_M_current += __n;
    return *this;
  }

  // -=操作符 后退n个difference_type
  self &operator-=(difference_type __n) _GLIBCXX_NOEXCEPT
  {
    this->_M_current -= __n;
    return *this;
  }

  reference operator*()
  {
    if (this->_M_current >= this->m_finish)
    {

      T tmp = T();
      return tmp;
    }
    return *this->_M_current;
  }

  pointer operator->()
  {
    return this->_M_current;
    ;
  }

  pointer base() const { return this->_M_current; }

private:
  // pointer _M_current, m_start, m_finish;
};

template <typename _Iterator, typename _Container>
typename Random_Access_Iterator<_Iterator, _Container>::difference_type
operator>=(const Random_Access_Iterator<_Iterator, _Container> &__lhs,
           const Random_Access_Iterator<_Iterator, _Container> &__rhs) noexcept
{
  return __lhs.base() - __rhs.base() >= 0;
}

template <typename _Iterator, typename _Container>
typename Random_Access_Iterator<_Iterator, _Container>::difference_type
operator>(const Random_Access_Iterator<_Iterator, _Container> &__lhs,
          const Random_Access_Iterator<_Iterator, _Container> &__rhs) noexcept
{
  return __lhs.base() - __rhs.base() > 0;
}

template <typename _Iterator, typename _Container>
typename Random_Access_Iterator<_Iterator, _Container>::difference_type
operator<=(const Random_Access_Iterator<_Iterator, _Container> &__lhs,
           const Random_Access_Iterator<_Iterator, _Container> &__rhs) noexcept
{
  return __lhs.base() - __rhs.base() <= 0;
}

template <typename _Iterator, typename _Container>
typename Random_Access_Iterator<_Iterator, _Container>::difference_type
operator<(const Random_Access_Iterator<_Iterator, _Container> &__lhs,
          const Random_Access_Iterator<_Iterator, _Container> &__rhs) noexcept
{
  return __lhs.base() - __rhs.base() < 0;
}

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

// template <typename _Iterator, typename _IteratorR, typename _Container>
// bool operator!=(const Random_Access_Iterator<_Iterator, _Container> &__lhs,
//                 const Random_Access_Iterator<_Iterator, _Container> &__rhs)
// {
//   return !(__lhs.base() == __rhs.base());
// }

// template <typename _Iterator, typename _IteratorR, typename _Container>
// bool operator==(const Random_Access_Iterator<_Iterator, _Container> &__lhs,
//                 const Random_Access_Iterator<_Iterator, _Container> &__rhs)
// {
//   return (__lhs.base() == __rhs.base());
// }

template <typename T, typename Container>
class Forward_Access_Iterator : public iterator_base<tinystl::list_node_base<T>>
{
public:
  typedef iterator_base<tinystl::list_node_base<T>> self_base;
  typedef typename self_base::value_type value_type;
  typedef typename self_base::pointer pointer;
  typedef typename self_base::reference reference;
  typedef typename self_base::difference_type difference_type;
  typedef Forward_Access_Iterator<T, Container> self;

  Forward_Access_Iterator() : iterator_base<tinystl::list_node_base<T>>() {}

  pointer base() const { return this->_M_current; }

  Forward_Access_Iterator(tinystl::list_node_base<T> *cur) : iterator_base<tinystl::list_node_base<T>>(cur){};

  self &operator++()
  {
    this->_M_current = this->_M_current->next;
    return *this;
  }

  self operator+(difference_type __n)
  {
    while (-__n)
    {
      this->_M_current = this->_M_current->next;
      --__n;
    }
    self tmp(this->_M_current);
    return tmp;
  }

  self operator++(int)
  {
    self temp(this->_M_current);
    this->_M_current = this->_M_current->next;
    return temp;
  }

  bool operator==(const self_base &it) const override
  {
    return this->_M_current == it.__get_current();
  }
  bool operator!=(const self_base &it) const override
  {
    return this->_M_current != it.__get_current();
  }

  T &operator*()
  {
    return this->_M_current->as_node()->m_data;
  }

  T *operator->() { return &this->_M_current->m_data; }
};

template <typename T, typename Container>
class Bidirectional_Access_Iterator : public iterator_base<tinystl::list_node_base<T>>
{
public:
  typedef iterator_base<tinystl::list_node_base<T>> self_base;
  typedef typename self_base::value_type value_type;
  typedef typename self_base::pointer pointer;
  typedef typename self_base::reference reference;
  typedef typename self_base::difference_type difference_type;
  typedef Bidirectional_Access_Iterator<T, Container> self;

  // Bidirectional_Access_Iterator() = default;
  Bidirectional_Access_Iterator() : iterator_base<tinystl::list_node_base<T>>() {}

  pointer base() const { return this->_M_current; }

  Bidirectional_Access_Iterator(tinystl::list_node_base<T> *cur) : iterator_base<tinystl::list_node_base<T>>(cur){};

  self &operator++()
  {
    this->_M_current = this->_M_current->next;
    return *this;
  }

  self operator-(difference_type __n)
  {
    while (-__n)
    {
      this->_M_current = this->_M_current->prev;
      --__n;
    }
    self tmp(this->_M_current);
    return tmp;
  }

  self operator+(difference_type __n)
  {
    while (-__n)
    {
      this->_M_current = this->_M_current->next;
      --__n;
    }
    self tmp(this->_M_current);
    return tmp;
  }

  self &operator--()
  {
    this->_M_current = this->_M_current->prev;
    return *this;
  }

  self operator++(int)
  {
    self temp(this->_M_current);
    // this->_M_current = this->_M_current->next;
    ++*this;
    return temp;
  }
  self operator--(int)
  {
    self temp(this->_M_current);
    // this->_M_current = this->_M_current->prev;
    --*this;
        // self tmp = *this;
    // ++*this;
    return temp;
  }
  bool operator==(const self_base &it) const override
  {
    return this->_M_current == it.__get_current();
  }
  bool operator!=(const self_base &it) const override
  {
    return this->_M_current != it.__get_current();
  }

  T &operator*()
  {
    // this->_M_current->m_data
    // tinystl::list_node<T>* p = static_cast<tinystl::list_node<T>*>(this->_M_current);
    return this->_M_current->as_node()->m_data;
  }

  T *operator->() { return &(operator*()); }

  // private:
  //   node *_M_current;
};


template <typename _Iterator, typename _Container>
typename Forward_Access_Iterator<_Iterator, _Container>::difference_type
operator>=(const Forward_Access_Iterator<_Iterator, _Container> &__lhs,
           const Forward_Access_Iterator<_Iterator, _Container> &__rhs) noexcept
{
  return __lhs.base() >= __rhs.base();
}

template <typename _Iterator, typename _IteratorR, typename _Container>
typename Forward_Access_Iterator<_Iterator, _Container>::difference_type
operator>(const Forward_Access_Iterator<_Iterator, _Container> &__lhs,
          const Forward_Access_Iterator<_Iterator, _Container> &__rhs) noexcept
{
  return __lhs.base() > __rhs.base();
}

template <typename _Iterator, typename _IteratorR, typename _Container>
typename Forward_Access_Iterator<_Iterator, _Container>::difference_type
operator<=(const Forward_Access_Iterator<_Iterator, _Container> &__lhs,
           const Forward_Access_Iterator<_Iterator, _Container> &__rhs) noexcept
{
  return __lhs.base() <= __rhs.base();
}

template <typename _Iterator, typename _IteratorR, typename _Container>
typename Forward_Access_Iterator<_Iterator, _Container>::difference_type
operator<(const Forward_Access_Iterator<_Iterator, _Container> &__lhs,
          const Forward_Access_Iterator<_Iterator, _Container> &__rhs) noexcept
{
  return __lhs.base() < __rhs.base();
}

template <typename _Iterator, typename _IteratorR, typename _Container>
typename Forward_Access_Iterator<_Iterator, _Container>::difference_type
operator==(const Forward_Access_Iterator<_Iterator, _Container> &__lhs,
           const Forward_Access_Iterator<_Iterator, _Container> &__rhs) noexcept
{
  return __lhs.base() == __rhs.base();
}

template <typename _Iterator, typename _Container>
typename Bidirectional_Access_Iterator<_Iterator, _Container>::difference_type
operator>=(const Bidirectional_Access_Iterator<_Iterator, _Container> &__lhs,
           const Bidirectional_Access_Iterator<_Iterator, _Container> &__rhs) noexcept
{
  return __lhs.base() >= __rhs.base();
}

template <typename _Iterator, typename _IteratorR, typename _Container>
typename Bidirectional_Access_Iterator<_Iterator, _Container>::difference_type
operator>(const Bidirectional_Access_Iterator<_Iterator, _Container> &__lhs,
          const Bidirectional_Access_Iterator<_Iterator, _Container> &__rhs) noexcept
{
  return __lhs.base() > __rhs.base();
}

template <typename _Iterator, typename _IteratorR, typename _Container>
typename Bidirectional_Access_Iterator<_Iterator, _Container>::difference_type
operator<=(const Bidirectional_Access_Iterator<_Iterator, _Container> &__lhs,
           const Bidirectional_Access_Iterator<_Iterator, _Container> &__rhs) noexcept
{
  return __lhs.base() <= __rhs.base();
}

template <typename _Iterator, typename _IteratorR, typename _Container>
typename Bidirectional_Access_Iterator<_Iterator, _Container>::difference_type
operator<(const Bidirectional_Access_Iterator<_Iterator, _Container> &__lhs,
          const Bidirectional_Access_Iterator<_Iterator, _Container> &__rhs) noexcept
{
  return __lhs.base() < __rhs.base();
}

template <typename _Iterator, typename _IteratorR, typename _Container>
typename Bidirectional_Access_Iterator<_Iterator, _Container>::difference_type
operator==(const Bidirectional_Access_Iterator<_Iterator, _Container> &__lhs,
           const Bidirectional_Access_Iterator<_Iterator, _Container> &__rhs) noexcept
{
  return __lhs.base() == __rhs.base();
}

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
  typedef tinystl::Iterator_Traits<Iterator> __traits_type;
  typedef tinystl::bidirectional_iterator_tag iterator_category;
  typedef Iterator value_type;
  typedef Iterator *pointer;
  typedef Iterator &reference;
  typedef Iterator difference_type;

  // 反向迭代器的五种相应型别
  // typedef typename __traits_type::value_type value_type;
  // typedef typename __traits_type::difference_type difference_type;
  // typedef typename __traits_type::reference reference;
  // typedef typename __traits_type::pointer pointer;

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
