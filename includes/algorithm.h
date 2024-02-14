#ifndef AGRITHOM
#define AGRITHOM

#include "./tuple.h"
#include "./array.h"

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
Tp get1(Array<Tp, idx> &arr)
{
    return arr[id];
}

#endif