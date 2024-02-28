#ifndef VECTOR_H
#define VECTOR_H

#include "iterator.h"
#include "iterator_traits.h"
#include <iostream>
#include "adapter.h"

namespace tinystl
{
  template <typename T>
  class Vector
  {
  public:
    typedef T value_type; // alias for T
    // typedef T* iterator;

    typedef Random_Access_Iterator<T, Vector> iterator;

    /*
      另一种写法：
      typedef T* iterator;
      typedef Iterator_Traits<iterator, tinystl::random_access_iterator_tag> __traits_type; // buildin pointer
     */


    typedef Reverse_Iterator<T *> reverse_iterator;
    Vector(size_t size)
    {
      _size = _capacity = size;
      m_data = new value_type[size];
      // m_data = tinystl::Allocator<T>::allocate(_size);
      for (int i = 0; i < size; i++)
      {
        m_data[i] = static_cast<T>(0);
      }
    }
    Vector(T *first, T *last)
    {
      _size = _capacity = last - first;
      m_data = new value_type[_size];
      // m_data = tinystl::Allocator<T>::allocate(_size);
      for (int i = 0; i < _size; i++)
      {
        m_data[i] = first[i];
      }
    }

    Vector(iterator first, iterator last)
    {
      _size = _capacity = last - first;
      m_data = new value_type[_size];
      // m_data = tinystl::Allocator<T>::allocate(_size);
      for (int i = 0; i < _size; i++)
      {
        m_data[i] = first[i];
      }
    }

    Vector(size_t size, const T &value) // value为临时对象的时候，value在当前行之后的生命周期结束了
    {
      _size = _capacity = size;
      m_data = new value_type[size];
      // m_data = tinystl::Allocator<T>::allocate(_size);
      for (int i = 0; i < size; i++)
      {
        m_data[i] = value;
      }
    }

    Vector(std::initializer_list<T> arr)
    {
      _size = _capacity = arr.size();
      m_data = new T[_size];
      // m_data = tinystl::Allocator<T>::allocate(_size);
      // typename initializer_list<T>::iterator it;
      int i = 0;
      for (auto it = arr.begin(); it != arr.end(); ++it)
      {
        m_data[i++] = *it;
      }
    }
    Vector() : m_data(nullptr), _size(0), _capacity(0) {}
    Vector(const Vector &vec);
    ~Vector();
    Vector<T> &operator=(const Vector<T> &vec);

    // 移动赋值，为了拿到右值的控制权
    // Vector &operator=(const value_type &&vec)
    // {
    //   if (&vec == this)
    //   {
    //     return *this;
    //   }
    //   // delete[] m_data;
    //   // _size = vec.size;
    //   // _capacity = vec.capacity;
    //   m_data = vec.m_data;
    //   _capacity = vec._capacity;
    //   _size = vec._size;
    // }

    void push_back(const value_type &vec);

    void clear()
    {
      _size = 0;
    }

    void pop_back() { --_size; }
    void erase(const iterator it)
    {
      if (it >= iterator(m_data + _size, _size))
      {
        return;
      }
      int index = it - begin();
      for (int i = index; i < _size; i++)
      {
        m_data[i] = m_data[i + 1];
      }
      --_size;
    }

    void rinser(reverse_iterator it, value_type val)
    {
      const size_t index = it - rbegin();
    }

    reverse_iterator rbegin()
    {
      return reverse_iterator(m_data + _size);
    }

    void insert(iterator it, value_type val);

    value_type front() { return m_data[0]; }

    value_type back() { return m_data[_size - 1]; }

    iterator begin() _GLIBCXX_NOEXCEPT { return iterator(m_data, _size); }

    iterator end() _GLIBCXX_NOEXCEPT
    {

      return iterator(m_data + _size, _size);
    }

    size_t capacity() { return _capacity; }

    bool empty() { return _size == 0; }

    size_t size() { return _size; }

    value_type &operator[](int index)
    {
      return m_data[index];
    }

    bool operator==(value_type &vec);

  private:
    size_t _size;
    size_t _capacity;
    T *m_data;
  };

  template <typename T>
  void Vector<T>::push_back(const value_type &vec)
  {
    if (_capacity == 0)
    {
      _capacity = 1;
      m_data = new value_type[_capacity];
      // m_data = tinystl::Allocator<T>::allocate(_capacity);
    }
    else if (_size == _capacity)
    {
      T *new_data = new value_type[_capacity * 2];
      // T *new_data = tinystl::Allocator<T>::allocate(_capacity * 2);
      for (int i = 0; i < _size; i++)
      {
        new_data[i] = m_data[i];
      }
      delete[] m_data;
      // tinystl::Allocator<T>::deallocate(m_data);
      m_data = new_data;
      _capacity *= 2;
    }
    m_data[_size++] = vec;
  }

  /*
    初始化列表的初始化顺序并不是由构造函数后的变量顺序决定的，而是由类中成员变量的定义顺序决定的
   */

  template <typename T>
  Vector<T>::~Vector()
  {
    // for (int i = 0; i < _size; i++) {
    //   m_data[i].~T();
    // }
    if (m_data)
    {
      // tinystl::Allocator<T>::deallocate(m_data, _size);
      delete[] m_data;
    }
    m_data = nullptr;
    _size = 0;
    _capacity = 0;
  }

  template <typename T>
  void Vector<T>::insert(iterator it, value_type val)
  {
    // int index = it - m_data;
    const size_t index = it - begin();
    if (0 == _capacity)
    {
      _capacity = 1;
      // m_data = new value_type[1];
      m_data = tinystl::Allocator<T>::allocate(1);
      m_data[0] = val;
    }
    else if (_size + 1 > _capacity)
    {
      _capacity *= 2;
      // value_type *temp = new value_type[_capacity];
      value_type *temp = tinystl::Allocator<T>::allocate(_capacity);
      for (int i = 0; i < index; ++i)
      {
        temp[i] = m_data[i];
      }
      temp[index] = val;
      for (int i = index; i < _size; i++)
      {
        temp[i + 1] = m_data[i];
      }
      // delete[] m_data;
      tinystl::Allocator<T>::deallocate(m_data);
      m_data = temp;
    }
    else
    {
      for (int i = _size - 1; i >= index; --i)
      {
        m_data[i + 1] = m_data[i];
      }
      m_data[index] = val;
    }
    ++_size;
  }

  template <typename T>
  bool Vector<T>::operator==(value_type &vec)
  {
    if (_size != vec._size)
      return false;
    for (int i = 0; i < _size; ++i)
    {
      if (m_data[i] != vec._data[i])
        return false;
    }
    return true;
  }

  // deep copy
  template <typename T>
  Vector<T>::Vector(const Vector<T> &vec)
  {
    _size = vec._size;
    _capacity = vec._capacity;
    m_data = new Vector<T>::value_type[_size];
    // m_data = tinystl::Allocator<T>::allocate(_size);
    for (int i = 0; i < _size; i++)
    {
      m_data[i] = vec.m_data[i];
    }
  }

  /*
  赋值运算符重载函数时将传入参数的所有信息拷贝一份。
  针对vector而言，赋值运算符重载函数具体实现的是vec1 =
  ve2;，按函数调用来理解就是vec1.operator=(vec2)
   */

  template <typename T>
  Vector<T> &Vector<T>::operator=(const Vector<T> &vec)
  {
    if (&vec == this)
    {
      return *this;
    }
    if (m_data != nullptr)
    {
      delete[] m_data;
      // tinystl::Allocator<T>::deallocate(m_data);
      m_data = nullptr;
    }
    _size = vec._size;
    _capacity = vec._capacity;
    m_data = new Vector::value_type[_size];
    // m_data = tinystl::Allocator<T>::allocate(_size);
    for (int i = 0; i < _size; i++)
    {
      m_data[i] = vec.m_data[i];
    }
    return *this;
  }
}

#endif