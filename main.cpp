#include "list.h"
#include "String.h"
#include "vector.h"
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
#include "tuple.h"
#include "pair.h"
#include "array.h"
#include "algorithm.h"
#include "global.h"
#include <stdlib.h>
#include <time.h>

using namespace ::std;

void fun1(int i)
{
  cout << i << " ";
}

void fun(int i, const char *str)
{
  cout << str << i << " ";
}

struct Play
{
  void operator()(int i)
  {
    cout << i << " ";
  }
};

struct Play1
{
  const char *str;
  Play1(const char *s) : str(s) {}
  void operator()(int i)
  {
    cout << str << i << endl;
  }
};

bool abs_greater(int elem1, int elem2)
{
  if (elem1 < 0)
    elem1 = -elem1;
  if (elem2 < 0)
    elem2 = -elem2;
  return elem1 < elem2;
};

bool greater10(int value)
{
  return value > 10;
}

tinystl::String dash_fold(tinystl::String &a, tinystl::String &b)
{
  return tinystl::String(a + "-" + b);
};

int main()
{

  /* 测试String */
  cout << "********************** Test String **********************" << endl;

  tinystl::String s1 = "hello";
  tinystl::String s2 = "hello";
  // bool r1 = s1 == s2;
  // bool r2 = s1 != s2;
  // cout << "boolean测试：" << r1 << endl;
  // cout << "boolean测试：" << r2 << endl;
  tinystl::String s3 = s1 + s2;
  cout << s3 << endl;
  cout << s3.size() << endl;
  s2 = s1;
  cout << s2 << endl;

  cout << "s1 = " << s1 << endl;
  cout << "s1.refcount = " << s1.refCount() << endl;
  printf("s1.addr = %p\n", s1.strAddr());

  cout << endl;
  cout << "拷贝操作String s_2 = s1" << endl;
  tinystl::String s_2 = s1;
  cout << "s1 = " << s1 << endl;
  cout << "s_2 = " << s_2 << endl;
  cout << "s1.refcount = " << s1.refCount() << endl;
  printf("s1.addr = %p\n", s1.strAddr());
  cout << "s_2.refcount = " << s_2.refCount() << endl;
  printf("s_2.addr = %p\n", s_2.strAddr());
  s2.strAddr();

  cout << endl;
  cout << "赋值操作s3 = s2" << endl;
  s3 = s2;
  cout << "s2.refcount = " << s2.refCount() << endl;
  printf("s2.addr = %p\n", s2.strAddr());
  cout << "s3.refcount = " << s3.refCount() << endl;
  printf("s3.addr = %p\n", s3.strAddr());

  cout << endl;
  cout << "读下标操作" << endl;
  cout << "s_2[0] = " << s_2[0] << ", s1 = " << s1 << endl;
  cout << "s1.refcount = " << s1.refCount() << endl;
  printf("s1.addr = %p\n", s1.strAddr());
  cout << "s_2.refcount = " << s_2.refCount() << endl;
  printf("s_2.addr = %p\n", s_2.strAddr());
  cout << "s.size = " << s_2.size() << endl;

  cout << endl;
  cout << "对数据写操作,将会触发写时复制技术！" << endl;
  s2[0] = '0';
  cout << "s2[0] = " << s2[0] << ", s2 = " << s2 << endl;
  cout << "s1.refcount = " << s1.refCount() << endl;
  printf("s1.addr = %p\n", s1.strAddr());
  cout << "s2.refcount = " << s2.refCount() << endl;
  printf("s2.addr = %p\n", s2.strAddr());
  cout << "s3.refcount = " << s3.refCount() << endl;
  printf("s3.addr = %p\n", s3.strAddr());
  cout << "s3.size = " << s2.size() << endl;
  tinystl::Vector<std::string> vs(1, "aaa5566");

  // tinystl::String ss = tinystl::accumulate(vs.begin(), vs.end(), tinystl::String("receive"), dash_fold);

  // std::cout << "dash-separated string : " << ss << std::endl;

  cout << "********************** Test String **********************" << endl;

  cout << "********************** Test Array **********************" << endl;

  tinystl::Array<int, 10> arr;
  for (int i = 0; i < 10; i++)
  {
    arr[i] = i;
  }

  for (int i = 0; i < 10; i++)
  {
    cout << arr[i] << " ";
  }

  for (auto a : arr)
  {
    cout << a << " ";
  }

  cout << endl;

  cout << "********************** Test Array **********************" << endl;

  cout << "********************** Test List **********************" << endl;
  int a22[] = {11, 22, 33, 44, 55};
  // tinystl::List<int>::iterator it_tmp; // 声明一个迭代器
  // tinystl::List<int> lint{1, 2, 3, 4, 5, 6, 7, 8, 9};
  // tinystl::List<int> l2(5);
  // cout << "l2: >>>>>" << endl;
  // for (it_tmp = l2.begin(); it_tmp != l2.end(); it_tmp++)
  // {
  //   cout << *it_tmp << endl;
  // }
  // cout << "l3: >>>>>" << endl;
  // tinystl::List<int> l3(5, 1);
  // for (it_tmp = l3.begin(); it_tmp != l3.end(); it_tmp++)
  // {
  //   cout << *it_tmp << endl;
  // }
  // cout << "l4: >>>>>" << endl;
  // tinystl::List<int> l4(a22, a22 + 5);
  // for (it_tmp = l4.begin(); it_tmp != l4.end(); it_tmp++)
  // {
  //   cout << *it_tmp << endl;
  // }

  // cout << "l4-2: >>>>>" << endl;
  // tinystl::List<int> l42(a22 + 1, a22 + 5);
  // cout << l42.size() << endl;
  // for (it_tmp = l42.begin(); it_tmp != l42.end(); it_tmp++)
  // {
  //   cout << *it_tmp << endl;
  // }
  cout << "l5: >>>>>" << endl;
  // tinystl::List<int> l5(l2);
  // for (it_tmp = l5.begin(); it_tmp != l5.end(); it_tmp++)
  // {
  //   cout << *it_tmp << endl;
  // }
  // cout << "l6: >>>>>" << endl;
  // tinystl::List<int> l6(std::move(l4));
  // for (it_tmp = l6.begin(); it_tmp != l6.end(); it_tmp++)
  // {
  //   cout << *it_tmp << endl;
  // }
  // cout << "l7: >>>>>" << endl;
  // tinystl::List<int> l7{1, 2, 3, 4, 5, 6, 7, 8, 9};
  // for (it_tmp = l7.begin(); it_tmp != l7.end(); it_tmp++)
  // {
  //   cout << *it_tmp << endl;
  // }
  // cout << "l8: >>>>>" << endl;
  // tinystl::List<int> l8;
  // for (it_tmp = l8.begin(); it_tmp != l8.end(); it_tmp++)
  // {
  //   cout << *it_tmp << endl;
  // }
  // l8 = l3;
  // cout << "l8: >>>>>" << endl;
  // for (it_tmp = l8.begin(); it_tmp != l8.end(); it_tmp++)
  // {
  //   cout << *it_tmp << endl;
  // }
  // tinystl::List<int> l9;
  // l9 = std::move(l3);
  // cout << "l9: >>>>>" << endl;
  // for (it_tmp = l9.begin(); it_tmp != l9.end(); it_tmp++)
  // {
  //   cout << *it_tmp << endl;
  // }
  // tinystl::List<int> l10;
  // l10 = {1, 2, 2, 3, 5, 6, 7, 8, 9};
  // cout << "l10: >>>>>" << endl;
  // for (it_tmp = l10.begin(); it_tmp != l10.end(); it_tmp++)
  // {
  //   cout << *it_tmp << endl;
  // }

  tinystl::List<int> l1;
  l1.push_back(1);
  l1.push_back(2);
  l1.push_back(3);
  l1.push_back(4);
  l1.push_back(5);
  l1.push_back(6);
  l1.push_back(7);

  // tinystl::List<int>::iterator it; // 声明一个迭代器

  // for (it = l1.begin(); it != l1.end(); it++)
  // {
  //   cout << *it << endl;
  // }

  cout << "first ele: " << *(l1.begin()) << endl;
  // cout << "last ele" << *(l1.end()) << endl;

  l1.push_front(10); // 10 1 2 3 4 5 6 7

  cout << "size: " << l1.size() << endl;

  l1.pop_back(); // 10 1 2 3 4 5 6

  cout << "size after pop back: " << l1.size() << endl;

  cout << "all eles after pop back: " << endl;

  // for (it = l1.begin(); it != l1.end(); it++)
  // {
  //   cout << *it << endl;
  // }

  l1.pop_front(); // 1 2 3 4 5 6
  cout << "size after pop front: " << l1.size() << endl;

  cout << "all eles after pop front: " << endl;

  // for (it = l1.begin(); it != l1.end(); it++)
  // {
  //   cout << *it << endl;
  // }

  cout << "********************** Test List **********************" << endl;

  cout << "********************** Test Vector **********************" << endl;

  tinystl::Vector<int>::iterator it_tmp_vec; // 声明一个迭代器
  tinystl::Vector<int> v2(5);
    cout << "v5: >>>>>" << endl;
  tinystl::Vector<int> v5(v2);
  cout << "v2: >>>>>" << endl;
  for (it_tmp_vec = v2.begin(); it_tmp_vec != v2.end(); it_tmp_vec++)
  {
    cout << *it_tmp_vec << endl;
  }
  cout << "v3: >>>>>" << endl;
  tinystl::Vector<int> v3(5, 1);
  for (it_tmp_vec = v3.begin(); it_tmp_vec != v3.end(); it_tmp_vec++)
  {
    cout << *it_tmp_vec << endl;
  }
  cout << "v4: >>>>>" << endl;
  tinystl::Vector<int> v4(a22, a22 + 5);
  for (it_tmp_vec = v4.begin(); it_tmp_vec != v4.end(); it_tmp_vec++)
  {
    cout << *it_tmp_vec << endl;
  }
    cout << "v2: >>>>>"  << endl;

  // for (it_tmp_vec = v5.begin(); it_tmp_vec != v5.end(); it_tmp_vec++)
  // {
  //   cout << *it_tmp_vec << endl;
  // }
  // cout << "v6: >>>>>" << endl;
  // tinystl::Vector<int> v6(std::move(v4));
  // for (it_tmp_vec = v6.begin(); it_tmp_vec != v6.end(); it_tmp_vec++)
  // {
  //   cout << *it_tmp_vec << endl;
  // }
  // cout << "v7: >>>>>" << endl;
  // tinystl::Vector<int> v7{1, 2, 3, 4, 5, 6, 7, 8, 9};
  // for (it_tmp_vec = v7.begin(); it_tmp_vec != v7.end(); it_tmp_vec++)
  // {
  //   cout << *it_tmp_vec << endl;
  // }
  // cout << "v8: >>>>>" << endl;
  // tinystl::Vector<int> v8;
  // for (it_tmp_vec = v8.begin(); it_tmp_vec != v8.end(); it_tmp_vec++)
  // {
  //   cout << *it_tmp_vec << endl;
  // }
  // v8 = v3;
  // cout << "v8: >>>>>" << endl;
  // for (it_tmp_vec = v8.begin(); it_tmp_vec != v8.end(); it_tmp_vec++)
  // {
  //   cout << *it_tmp_vec << endl;
  // }
  // tinystl::Vector<int> v9;
  // v9 = std::move(v3);
  // cout << "v9: >>>>>" << endl;
  // for (it_tmp_vec = v9.begin(); it_tmp_vec != v9.end(); it_tmp_vec++)
  // {
  //   cout << *it_tmp_vec << endl;
  // }
  // tinystl::Vector<int> v10;
  // v10 = {1, 2, 2, 3, 5, 6, 7, 8, 9};
  // cout << "v10: >>>>>" << endl;
  // for (it_tmp_vec = v10.begin(); it_tmp_vec != v10.end(); it_tmp_vec++)
  // {
  //   cout << *it_tmp_vec << endl;
  // }

  // cout << "********************** Test Vector **********************" << endl;

  // cout << "********************** Test Tuple **********************" << endl;

  // Tuple<int, double, std::string> t{1, 2.3, "haha"};
  // cout << get<0>(t) << endl;
  // cout << get<1>(t) << endl;
  // cout << get<2>(t) << endl;
  // cout << get<0>(t) << endl;

  // std::string name("jmm");
  // double score(1.2);
  // int rank(10);
  // Tuple<int, double, std::string> tt(1, 2.3, "haha");

  // tt = tie(rank, score, name); // 10, 2.3, haha

  // cout << rank << endl;  // 10
  // cout << name << endl;  // haha
  // cout << score << endl; // 2.3
  // cout << get<0>(tt) << endl;
  // cout << get<1>(tt) << endl;
  // cout << get<2>(tt) << endl;

  // // Tuple<int, double, std::string> mm;

  // // Pair<int, std::string> a1(101, "lanzhihui"); // 参数类型必须与定义类型一样
  // // cout << a1.first << " " << a1.second << endl;

  // // Tuple<int, std::string> t2;
  // // t2 = a1;

  // // cout << get<0>(t2) << " hhhhh" << get<1>(t2) << "eee" << endl;
  // // 这么看来copy构造是返回一个新的地址；
  // // string name1;
  // // Tuple<string&, int> tpRef(name1,30);
  // // // 对tpRef第一个元素赋值，同时name也被赋值 - 引用
  // // get<0>(tpRef) = "Sven";

  // // // name输出也是Sven
  // // cout << "name: " << name1 << '\n';

  // cout << "********************** Test Tuple **********************" << endl;

  // cout << "********************** Test Pair **********************" << endl;

  // cout << "********************** Test Pair **********************" << endl;

  // cout << "********************** Test find **********************" << endl;

  // cout << "********************** Test find **********************" << endl;

  // cout << "********************** Test find_if **********************" << endl;

  // cout << "********************** Test find_if **********************" << endl;

  // cout << "********************** Test max **********************" << endl;

  // int a = 6, b = -7;
  // int c = -10, d = 8;
  // // 返回绝对值较大的整数
  // const int &result1 = tinystl::max(a, b, abs_greater);
  // // 返回较大的整数
  // const int &result2 = tinystl::max(a, b);
  // const int &result3 = tinystl::max({a, b, c, d});
  // const int &result4 = tinystl::max({a, b, c, d}, abs_greater);
  // cout << result2 << " " << result1 << " " << result3 << " " << result4 << endl;

  // cout << "********************** Test max **********************" << endl;

  // cout << "********************** Test max_element **********************" << endl;

  // cout << "********************** Test max_element **********************" << endl;

  // cout << "********************** Test for_each **********************" << endl;

  // cout << "********************** Test for_each **********************" << endl;
  // cout << "********************** Test count_if **********************" << endl;

  // cout << "********************** Test count_if **********************" << endl;
  // cout << "********************** Test accumulate **********************" << endl;

  // srand((unsigned)time(NULL));
  // tinystl::Vector<unsigned int> v(10, 0);
  // for (int i = 0; i < v.size(); i++)
  // {
  //   v[i] = (rand() % (100 + 1));
  //   cout << v[i] << " ";
  // }
  // cout << endl;
  // cout << "answer: " << *tinystl::max_element(v.begin(), v.end()) << endl;

  // int sum = tinystl::accumulate(v.begin(), v.end(), 0);

  // cout << "sum: " << sum << std::endl;

  // cout << "********************** Test accumulate **********************" << endl;
  // cout << "********************** Test String **********************" << endl;

  // cout << "********************** Test fill **********************" << endl;
  // cout << "********************** Test fill **********************" << endl;

  // cout << "********************** Test Array get **********************" << endl;

  // tinystl::Array<int, 3> arr1{1, 2, 3};

  // for (auto ele : arr1)
  // {
  //   cout << ele << " ";
  // }

  // cout << get<0>(arr1) << endl;

  // cout << "********************** Test Array get **********************" << endl;

  // cout << "********************** Test advance **********************" << endl;
  // cout << "********************** Test advance **********************" << endl;

  // cout << "********************** Test binder2nd **********************" << endl;
  // cout << "********************** Test binder2nd **********************" << endl;

  // cout << "********************** Test ptr_func **********************" << endl;
  // tinystl::List<int>::iterator it1 = l1.begin(); // 声明一个迭代器

  // // for (it = l1.begin(); it != l1.end(); it++)
  // // {
  // //   cout << *it << endl;
  // // }
  // tinystl::advance(it1, 2);

  // std::cout << "The xxx element in mylist is: " << *it1 << '\n';

  // // 1 2 3 4 5 6

  // // it1 = tinystl::find_if(l1.begin(), l1.end(), tinystl::bind2nd(tinystl::less<int>(), 5));

  // std::cout << "find ele less than 5: " << *it1 << '\n';

  // cout << tinystl::count_if(l1.begin(), l1.end(), tinystl::bind2nd(tinystl::less<int>(), 6)) << endl; // < 6 === > 5
  // cout << tinystl::count_if(l1.begin(), l1.end(), greater10) << endl;                                 // > 10 ====> 0

  // tinystl::for_each(l1.begin(), l1.end(), fun1);
  // tinystl::for_each(l1.begin(), l1.end(), tinystl::bind2nd(tinystl::ptr_fun(fun), "Element:"));
  // tinystl::for_each(l1.begin(), l1.end(), Play());
  // tinystl::for_each(l1.begin(), l1.end(), Play1("Element:"));

  // tinystl::Vector<int> v1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  //  tinystl::Vector<int> vhh(v1.begin() + 1, v1.end());
  // for (int i = 0; i < 10; i++)
  //   v1.push_back(i * 10);
  // tinystl::Vector<int>::iterator it_vector = v1.begin();
  // tinystl::advance(it_vector, 5);
  // std::cout << "The sixth element in mylist is: " << *it_vector << '\n';

  // it_vector = tinystl::find_if(v1.begin(), v1.end(), tinystl::bind2nd(tinystl::less<int>(), 5));

  // std::cout << "find ele less than 5: " << *it_vector << '\n';

  // cout << tinystl::count_if(v1.begin(), v1.end(), tinystl::bind2nd(tinystl::less<int>(), 6)) << endl;
  // cout << tinystl::count_if(v1.begin(), v1.end(), greater10) << endl;

  // tinystl::for_each(v1.begin() + 1, v1.end(), fun1);
  // tinystl::for_each(v1.begin(), v1.end(), tinystl::bind2nd(tinystl::ptr_fun(fun), "Element:"));
  // tinystl::for_each(v1.begin(), v1.end(), Play());
  // tinystl::for_each(v1.begin(), v1.end(), Play1("Element:"));

  cout << "********************** Test ptr_func **********************" << endl;

  return 0;
}