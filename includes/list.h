#ifndef LIST_H
#define LIST_H

#include "iterator.h"
#include <iostream>

/**
 * @brief List Class
 *
 */

namespace tinystl
{
  template <typename T>
  class List
  {
  public:
    typedef T value_type;
    typedef T &refernce;
    typedef T *pointer;
    typedef const T &const_reference;
    typedef const T *const_pointer;
    typedef node<T> _node;
    typedef Sequence_Access_Iterator<T, _node> iterator;

    /**
     * default ctor
     */
    List() : _size(0) { head = tail = new _node(); };

    /**
     * ctor like List(5, 0)
     */
    List(size_t size, T init_val) : _size(size)
    {
      _node *p = new _node();
      head = tail = p;
      for (size_t i = 0; i < size; ++i)
      {
        p->next = new _node();
        p->next->prev = p;
        p->next->m_data = init_val;
        p = p->next;
        tail = p;
      };
    };

    /**
     * ctor like List(5)
     */
    List(size_t size) : _size(size)
    {
      _node *p = new _node();
      head = tail = p;
      for (size_t i = 0; i < size; ++i)
      {
        p->next = new _node();
        p->next->prev = p;
        p->next->m_data = static_cast<T>(0); // 赋值 nullptr可能会有问题
        p = p->next;
        tail = p;
      };
      tail->next = nullptr;
    };

    /**
     * ctor like List(a, a + 1)
     */
    List(T *first, T *last)
    {
      if (first == last)
      {
        head = tail = new _node();
        return;
      }
      _size = 0;
      _node *p = new _node();
      head = tail = p;
      for (T *it = first; it != last; ++it)
      {
        p->next = new _node();
        p->next->prev = p;
        p->next->m_data = *it; // 赋值 nullptr可能会有问题
        p = p->next;
        tail = p;
        _size += 1;
      };
    }

    /**
     * ctor like List(list.begin(), list.end())
     */
    List(iterator first, iterator last)
    {
      if (first == last)
      {
        head = tail = new _node();
        return;
      }
      _size = 0;
      _node *p = new _node();
      head = tail = p;
      for (iterator it = first; it != last; ++it)
      {
        p->next = new _node();
        p->next->prev = p;
        p->next->m_data = *it; // 赋值 nullptr可能会有问题
        p = p->next;
        tail = p;
        _size += 1;
      }
    }

    /**
     * ctor like List = {}
     */
    List(std::initializer_list<T> args)
    {
      if (args.size() == 0 && head == nullptr)
      {
        head = tail = new _node();
        return;
      }
      _node *p = new _node();
      head = tail = p;
      for (auto it = args.begin(); it != args.end(); ++it)
      {
        p->next = new _node();
        p->next->prev = p;
        p->next->m_data = *it;
        p = p->next;
        tail = p;
        _size += 1;
      };
      _size = args.size();
    }

    /**
     * copy ctor like List(5, 0)
     */
    List(const List<T> &list)
    {
      head = tail = new _node();
      _node *p = list.head->next;
      while (p != nullptr)
      {
        push_back(p->m_data);
        p = p->next;
      }
      _size = list._size;
    }

    ~List()
    {
      _node *p = head;
      while (p != nullptr)
      {
        _node *tmp = p;
        p = p->next;
        delete tmp;
      }
    }

    iterator begin() { return iterator(head->next); }

    iterator end() { return iterator(tail->next); }

    value_type& front() { return head->next->m_data; }

    value_type& back() { return tail->m_data; }

    void push_front(const_reference val);

    void push_back(const_reference val);

    void pop_front();

    void pop_back();

    bool empty() { return _size == 0; }

    size_t size();

    List<T> &operator=(const List<T> &list);

  private:
    _node *head;
    _node *tail;
    size_t _size;
  };

  // --------------------------------------------------------------------------- split ---------------------------------------------------------------------------

  /**
   * @brief size of list
   *
   * @tparam T
   * @return size_t
   */
  template <typename T>
  size_t List<T>::size() { return _size; }

  /**
   * @brief push element `val` ahead of list
   *
   * @param val
   */

  template <typename T>
  void List<T>::push_front(const_reference val)
  {
    _node *cur = new _node(); // T* cur = new node; // 泛型会报错
    cur->next = head->next;
    cur->prev = head;
    cur->m_data = val;
    if (nullptr == head->next)
      tail = cur;
    else
      // cur->next->prev = cur;
      head->next->prev = cur;
    head->next = cur;
    ++_size;
  }

  /**
   * @brief push element `val` back of list
   *
   * @param val
   */
  template <typename T>
  void List<T>::push_back(const_reference val)
  {
    _node *cur = new _node();
    cur->next = nullptr;
    cur->m_data = val;
    if (nullptr == head->next)
    {
      head->next = tail->next = cur;
    }
    else
    {
      tail->next = cur;
    }
    cur->prev = tail;
    tail = cur;
    // tail->next = nullptr;
    ++_size;
  }

  /**
   * @brief pop element ahead of list
   *
   * @tparam T
   */
  template <typename T>
  void List<T>::pop_front()
  {
    if (empty())
      return;
    _node *tmp = head->next;
    head->next = tmp->next;
    // only one element
    if (nullptr == tmp->next)
      tail = head;
    else
      tmp->next->prev = head;
    delete tmp;
    --_size;
  }

  /**
   * @brief pop element back of list
   *
   * @tparam T
   */
  template <typename T>
  void List<T>::pop_back()
  {
    if (empty())
      return;
    _node *tmp = tail->prev;
    delete tail;
    tail = tmp;
    tail->next = nullptr;
    --_size;
  }

  /**
   * @brief operator= for list, like: l = list;
   *
   * @tparam T
   * @param list
   * @return List<T>&
   */
  template <typename T>
  List<T> &List<T>::operator=(const List<T> &list)
  {
    if (&list == this)
      return *this;

    _node *p = head->next;
    while (p != nullptr)
    {
      _node *tmp = p;
      p = p->next;
      delete tmp;
    }

    _node *cur = list.head->next;
    while (cur != nullptr)
    {
      push_back(cur->m_data);
      cur = cur->next;
    }

    _size = list._size;
    return *this;
  }
}

#endif