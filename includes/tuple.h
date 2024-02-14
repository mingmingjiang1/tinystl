#ifndef TUPLE
#define TUPLE

#include "pair.h"
#include <iostream>

template <typename... Arg>
class Tuple;
template <>
class Tuple<>
{
};
template <typename Head, typename... Tail>
class Tuple<Head, Tail...> : Tuple<Tail...>
{
private:
  Head value_;
  template <typename...>
  friend class Tuple;
  using Next = Tuple<Tail...>;

public:
  Tuple() = default;
  Tuple(const Head value, const Tail... tail) : value_(value), Tuple<Tail...>(tail...)
  {
    cout << "addring: " << this << value << endl;
  }

  Head get_value() const
  {
    return value_;
  }

  // Tuple(const Tuple<Head, Tail...> &tup) = delete; // 1 ======> implicit copy ctor

  // Tuple(const Tuple<Head, Tail...> &tup) {
  //   // if (tup.value_ != NULL) this->value_ = tup.value_;

  // }

  // protected:
  // Next &next() { return *this; }
  template <class U1, class U2>
  Tuple<Head, Tail...> &operator=(const Pair<U1, U2> &p)
  {
    value_ = p.first;
    Tuple<Tail...> tmp = Tuple<Tail...>(*this); // will call implicit copy ctor
    Tuple<Tail...> *parent = &tmp;
    Tuple<Tail...> *pa = (Tuple<Tail...> *)(this); // 指针类型转换

    cout << "addr1: " << pa << " " << &tmp << endl;

    pa->value_ = p.second;
    return *this;
  }

  template <typename Now, typename... Args>
  Tuple<Head, Tail...> &operator=(const Tuple<Now, Args...> &t)
  {
    value_ = t.value_;
    Tuple<Tail...> tmp1 = Tuple<Tail...>(*this);
    Tuple<Tail...> tmp2 = Tuple<Tail...>(*this);
    cout << "hello world" << &tmp1 << &tmp2 << endl;
    Tuple<Tail &...> *pa = (Tuple<Tail &...> *)(this);
    Tuple<Args...> tmp = Tuple<Args...>(t);
    pa = &tmp; // trick: 向上转型，类型转换 // will call implicit copy ctor

    return *this;
  }
};

template <size_t idx, typename... Arg>
class get_helper;
template <size_t idx, typename Head, typename... Tail>
struct get_helper<idx, Tuple<Head, Tail...>>
{
  using value_type = typename get_helper<idx - 1, Tuple<Tail...>>::value_type;
  using next_type = typename get_helper<idx - 1, Tuple<Tail...>>::next_type;
};
template <typename Head, typename... Tail>
struct get_helper<0, Tuple<Head, Tail...>>
{
  using value_type = Head;
  using next_type = Tuple<Head, Tail...>;
};
template <>
struct get_helper<0, Tuple<>>
{
  using value_type = void;
  using next_type = Tuple<>;
};


#endif
// https://juejin.cn/post/7146233769190490148#heading-2
// other version tuple implementtion: https://coliru.stacked-crooked.com/a/ac1e7947152acd6a
// https://www.cnblogs.com/fulina/p/7058288.html
// https://imcbc.cn/202207/cpp-stl-tuple/

// https://www.cnblogs.com/DswCnblog/p/6513310.html（constexpr）
// 编译时优化：常量会在编译时确定，inline，模板，constexpr
// 寄存器优化
// 内存优化：一般是浅copy，cow
// 并行优化