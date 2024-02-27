#ifndef AGRITHOM_H
#define AGRITHOM_H

#include "./tuple.h"
#include "./array.h"
#pragma GCC diagnostic ignored "-Wdeprecated-declarations" // 静默 warning: warning: 'template<class _Operation> class tinystl::binder2nd' is deprecated [-Wdeprecated-declarations]...

template <size_t idx, typename Head, typename... Tail>
typename get_helper<idx, Tuple<Head, Tail...>>::value_type
get(Tuple<Head, Tail...> &tup)
{
  using next_type = typename get_helper<idx, Tuple<Head, Tail...>>::next_type;
  // cout << "addr: " << ((next_type *)(&tup)) << "  " << sizeof(tup) << "  " << &tup << ((next_type *)(&tup))->value_ << endl;
  return ((next_type *)(&tup))->get_value();
}

template <typename... Types>
Tuple<Types &...> tie(Types &...args) noexcept
{
  return Tuple<Types &...>(args...);
}

// Array<int, 2UL>
template <size_t id, size_t idx, typename Tp>
Tp get(tinystl::Array<Tp, idx> &arr)
{
  return arr[id];
}

template <typename T>
constexpr const T &max(const T &a, const T &b)
{
}

namespace tinystl
{

  template <typename Arg, typename Result>
  struct unary_function
  {
  public:
    using first_argument_type = Arg;
    using result_type = Result;

    // virtual void operator()() = 0;
  };
  template <typename T1, typename T2, typename Result>
  struct binary_function
  {
  public:
    using first_argument_type = T1;
    using second_argument_type = T2;
    using result_type = Result;

    // virtual void operator()() = 0;
  };

  template <typename T>
  struct greater : binary_function<T, T, bool>
  {
    constexpr bool operator()(const T &x, const T &y) const
    {
      return x < y;
    }
  };

  template <typename T>
  struct less : binary_function<T, T, bool>
  {
  public:
    constexpr bool operator()(const T &x, const T &y) const
    {
      return x < y;
    }
  };

  template <typename T>
  constexpr const T &max(const T &a, const T &b)
  {
    return a < b ? b : a;
  }

  template <typename T, typename Compare = greater<T>>
  constexpr const T &max(const T &a, const T &b, Compare comp)
  {
    return comp(a, b) ? b : a;
  }

  template <typename T>
  constexpr const T &min(const T &a, const T &b)
  {
    return a < b ? a : b;
  }

  template <typename T, typename Compare = less<T>>
  constexpr const T &min(const T &a, const T &b, Compare comp)
  {
    return comp(a, b) ? a : b;
  }

  template <typename T>
  constexpr T max(std::initializer_list<T> ilist)
  {
    T max_val = *ilist.begin();
    for (auto &i : ilist)
    {
      max_val = max(i, max_val);
    }
    return max_val;
  }

  template <typename T, typename Compare = greater<T>>
  constexpr T max(std::initializer_list<T> ilist, Compare comp)
  {
    T max_val = *ilist.begin();
    for (auto &i : ilist)
    {
      max_val = max(i, max_val, comp);
    }
    return max_val;
  }

  template <typename Iterator>
  Iterator max_element(Iterator begin, Iterator end)
  {
    Iterator max_iter = begin;
    for (Iterator it = begin; it != end; ++it)
    {
      if (*it > *max_iter)
      {
        max_iter = it;
      }
    }
    return max_iter;
    ;
  }

  template <typename Iterator>
  Iterator min_element(Iterator begin, Iterator end)
  {
    Iterator min_iter = begin;
    for (Iterator it = begin; it != end; ++it)
    {
      if (*it < *min_iter)
      {
        min_iter = it;
      }
    }
    return min_iter;
  }

  template <typename Iterator, typename Function>
  void for_each(Iterator start, Iterator end, Function f)
  {
    while (start != end)
      f(*start++);
  }

  template <typename Iterator, typename N>
  Iterator find(Iterator start, Iterator end, N target)
  {
    while (start != end)
      if (*start == target)
        return start;
      else
        ++start;
    return end;
  }

  template <typename Iterator, typename Compare>
  Iterator find_if(Iterator start, Iterator end, Compare comp)
  {
      std::cout << *start << "fvgggt";
    while (start != end)
    {
      if (comp(*start))
        return start;
      else
        ++start;
    }
    return end;
  }

  template <typename Iterator, typename Predicate>
  size_t count_if(Iterator start, Iterator end, Predicate pred)
  {
    size_t count = 0;
    while (start != end)
    {
      if (pred(*start))
      {
        ++count;
      }
      ++start;
    }
    return count;
  }

  // template <class InputIterator, class Predicate>
  // typename iterator_traits<InputIterator>::difference_type count_if(
  //     InputIterator _First,
  //     InputIterator _Last,
  //     Predicate _Pred);

  template <typename Iterator, typename Compare>
  Iterator sort(Iterator start, Iterator end, Compare comp)
  {
  }

  template <class Iterator, class T>
  T accumulate(Iterator first, Iterator last, T init)
  {
    for (; first != last; ++first)
      init = init + *first;
    return init;
  }

  template <class Iterator, class T, class BinaryOperation>
  T accumulate(Iterator first, Iterator last, T init,
               BinaryOperation op)
  {
    for (; first != last; ++first)
    {
      init = op(init, *first);
    }
    return init;
  }

  template <class Iterator, class T>
  void fill(Iterator first, Iterator last, T value)
  {
    for (; first != last; ++first)
      *first = value;
  }

  // 比如 双向迭代器的函数 。重载doAdvance，实现不同的迭代器类型的具体操作。
  // 可以看到迭代器类型仅仅是个重载的作用,使得重载机制得以运行，都不需要变量名。
  /**
   * @brief random / bidirection
   *
   * @tparam Iterator
   * @tparam DistT
   * @param iter
   * @param d
   */
  template <typename Iterator, typename DistT>
  void doAdvance(Iterator &iter, DistT d, tinystl::random_access_iterator_tag)
  {
    if (d < 0)
    {
      while (d++)
      {
        --iter;
      }
    }
    else
    {
      while (d--)
      {
        ++iter;
      }
    }
  }

  template <typename Iterator, typename DistT>
  void doAdvance(Iterator &iter, DistT d, tinystl::bidirectional_iterator_tag)
  {
    if (d < 0)
    {
      while (d++)
      {
        --iter;
      }
    }
    else
    {
      while (d--)
      {
        ++iter;
      }
    }
  }

  /**
   * @brief forward
   *
   * @tparam Iterator
   * @tparam DistT
   * @param iter
   * @param d
   */
  template <typename Iterator, typename DistT>
  void doAdvance(Iterator &iter, DistT d, tinystl::forward_iterator_tag)
  {
    if (d < 0)
    {
      throw std::out_of_range("Negative distance");
    }
    while (d--)
    {
      ++iter;
    }
  }

  // advance编译器确定使用哪种迭代器类型版本
  template <typename Iterator, typename DistT>
  void advance(Iterator &iter, DistT d)
  {
    doAdvance(iter, d, typename Iterator_Traits<Iterator>::iterator_category());
  }

  template <typename _Operation>
  class binder2nd
  {
  protected:
    _Operation op;
    typename _Operation::second_argument_type value;

  public:
    binder2nd(const _Operation &__x,
              const typename _Operation::second_argument_type &__y)
        : op(__x), value(__y) {}

    typename _Operation::result_type
    operator()(const typename _Operation::first_argument_type &__x) const
    {
      return op(__x, value);
    }

    // _GLIBCXX_RESOLVE_LIB_DEFECTS
    // 109.  Missing binders for non-const sequence elements
    typename _Operation::result_type
    operator()(typename _Operation::first_argument_type &__x) const
    {
      return op(__x, value);
    }
  } _GLIBCXX_DEPRECATED;

  template <typename _Operation, typename _Tp>
  inline binder2nd<_Operation>
  bind2nd(const _Operation &__fn, const _Tp &__x)
  {
    typedef typename _Operation::second_argument_type _Arg2_type;
    return binder2nd<_Operation>(__fn, _Arg2_type(__x));
  }

  template <typename _first_arg, typename _second_arg>
  using testF = void(_first_arg arg1, _second_arg arg2);

  // ptr_fun: func 2 object func
  /*   template <typename _first_arg, typename _second_arg>
    Operation<int, const char *, void> ptr_fun(testF<_first_arg, _second_arg> func)
    {
      struct Test : Operation<_first_arg, _second_arg, void>
      {
      public:
        // constexpr void operator()(const _first_arg first, const _second_arg second) const
        // {
        //   return func(first, second);
        // }
        constexpr void operator()(const int &x, const char *&y) const
        {
          // return x < y;
        }
      };

      return Test();
    }; */

  template <class Arg, class Result>
  class pointer_to_unary_function : unary_function<Arg, Result>
  {
  protected:
    // ptr是函数指针，相当于int (*ptr)(int),ptr指向的是函数LESS。前面那个int是返回值类型，后面那个是形参
    Result (*ptr)(Arg);

  public:
    pointer_to_unary_function() {}
    explicit pointer_to_unary_function(Result (*x)(Arg)) : ptr(x) {} // 构造函数，把传进来的函数指针赋值给ptr
    // ptr(x)，这就是通过函数指针执行函数的方式,x是形参类型Arg的一个对象
    Result operator()(Arg x) const { return ptr(x); } // 一定要理解ptr(x)
  };
  // Arg代表形参类型
  // Result是返回值类型
  // x是一个函数指针
  template <class Arg, class Result>
  inline pointer_to_unary_function<Arg, Result> ptr_fun(Result (*x)(Arg))
  {
    return pointer_to_unary_function<Arg, Result>(x);
  }

  template <class Arg1, class Arg2, class Result>
  class pointer_to_binary_function : public binary_function<Arg1, Arg2, Result>
  {
  protected:
    Result (*ptr)(Arg1, Arg2);

  public:
    pointer_to_binary_function() {}
    explicit pointer_to_binary_function(Result (*x)(Arg1, Arg2)) : ptr(x) {}
    Result operator()(Arg1 x, Arg2 y) const { return ptr(x, y); }
  };

  template <class Arg1, class Arg2, class Result>
  inline pointer_to_binary_function<Arg1, Arg2, Result>
  ptr_fun(Result (*x)(Arg1, Arg2))
  {
    return pointer_to_binary_function<Arg1, Arg2, Result>(x);
  }
}

#endif