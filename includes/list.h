#ifndef LIST
#define LIST

#include "iterator.h"
#include <iostream>

/**
 * @brief List Class
 * List<string> list()
 */
template <typename T>
class List
{
public:
  typedef T data_type;
  typedef T &refernce;
  typedef T *pointer;
  typedef const T &const_reference;
  typedef const T *const_pointer;
  typedef node<T> _node;
  typedef Sequence_Access_Iterator<T, _node> iterator;

  List() : _size(0) { head = tail = new _node(); };

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
  };

  List(T *first, T *last)
  {
    if (first == last)
    {
      head = tail = new _node();
      return;
    }
    _node *p = new _node();
    head = tail = p;
    for (T *it = first; it != last; ++it)
    {
      p->next = new _node();
      p->next->prev = p;
      p->next->m_data = *it; // 赋值 nullptr可能会有问题
      p = p->next;
      tail = p;
    };
  }

  List(iterator first, iterator last)
  {
    if (first == last)
    {
      head = tail = new _node();
      return;
    }
    _node *p = new _node();
    head = tail = p;
    for (iterator it = first; it != last; ++it)
    {
      p->next = new _node();
      p->next->prev = p;
      p->next->m_data = *it; // 赋值 nullptr可能会有问题
      p = p->next;
      tail = p;
    }
  }

  List(std::initializer_list<T> args)
  {
    if (args.size() == 0 && head != nullptr)
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
    };
    _size = args.size();
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

  void push_front(const_reference val)
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

  void push_back(const_reference val)
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

  void pop_front()
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

  void pop_back()
  {
    if (empty())
      return;
    _node *tmp = tail->prev;
    delete tail;
    tail = tmp;
    tail->next = nullptr;
    --_size;
  }

  bool empty() { return _size == 0; }

  size_t size() { return _size; }

  // List<T> operator=(const List<T> &list)
  // {
  //   if (&list == this)
  //     return *this;
  //   _node *p = head;
  //   while (p != nullptr)
  //   {
  //     _node *tmp = p;
  //     p = p->next;
  //     delete tmp;
  //   }
  //   _node *cur = list.head;
  //   while (cur != nullptr)
  //   {
  //     push_back(cur->m_data);
  //     cur = cur->next;
  //   }
  //   return *this;
  // }


  List<T> &operator=(const List<T> &list)
  {
    if (&list == this)
      return *this;
    _node *p = head;
    while (p != nullptr)
    {
      _node *tmp = p;
      p = p->next;
      delete tmp;
    }
    _node *cur = list.head;
    while (cur != nullptr)
    {
      push_back(cur->m_data);
      cur = cur->next;
    }
    return *this;
    // if (args.size() == 0 && head != nullptr)
    // {
    //   head = tail = new _node();
    //   return *this;
    // }
    // _node *p = new _node();
    // head = tail = p;
    // for (auto it = args.begin(); it != args.end(); ++it)
    // {
    //   p->next = new _node();
    //   p->next->prev = p;
    //   p->next->m_data = *it;
    //   cout << *it << "hfhghhg" << endl;
    //   p = p->next;
    //   tail = p;
    // };
    // _size = args.size();
  }

private:
  _node *head;
  _node *tail;
  size_t _size;
};

int multiply(int a, int b);

float multiply(float a, float b);

double multiply(double a, double b);

#endif