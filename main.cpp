#include "./includes/list.h"
#include "./includes/string.h"
#include "./includes/vector.h"
#include <bits/c++config.h>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
#include "./includes/tuple.h"
#include "./includes/pair.h"
#include "./includes/array.h"
#include "./includes/algorithm.h"

using namespace ::std;


int main()
{
  Vector<String> vecs(4);
  // string s;
  // for (int i = 0; i < 10; i++) {
  //   std::string str(1, char('a' + i));
  //   vecs.push_back(str);
  // }

  // for (int i = 0; i < vecs.size(); i++) {
  //   cout << vecs[i] << " ";
  // }

  // vecs.pop_back();

  cout << vecs.size() << " ";

  for (int i = 0; i < vecs.size(); i++)
  {
    cout << vecs[i] << vecs.size() << " ";
  }



  String s("hfhhgfgf");
  vecs[0] = s;
  vecs[2] = s;
  vecs[1] = s;

  // for (int i = 0; i < 5; i++) {
  //   vecs.insert(vecs.begin() , s);
  // }
  // vecs.rinser(vecs.rbegin() - 2, String("jjjj"));
  vecs.insert(vecs.begin() + 1, String("jjjj"));

  for (int i = 0; i < vecs.size(); i++)
  {
    cout << ">>>>>>" << vecs.size() << vecs[i];
  }

  for (auto n : vecs)
  {
    cout << "===<"<< n << "=========> ";
  }
  cout << endl;

  List<string> list;
  list.push_front("happy");
  list.push_front("jmm");
  list.push_back("new");
  list.push_back("year");

  // list.pop_back();
  // list.pop_back();
  // list.pop_front();
  auto _begin = list.begin();
  for (auto n : list)
  {
    cout << n << " ";
  }
  cout << endl;
  String s1("hello");
  cout << "s1 = " << s1 << endl;
  cout << "s1.refcount = " << s1.refCount() << endl;
  printf("s1.addr = %p\n", s1.strAddr());

  cout << endl;
  cout << "拷贝操作String s2 = s1" << endl;
  String s2 = s1;
  cout << "s1 = " << s1 << endl;
  cout << "s2 = " << s2 << endl;
  cout << "s1.refcount = " << s1.refCount() << endl;
  printf("s1.addr = %p\n", s1.strAddr());
  cout << "s2.refcount = " << s2.refCount() << endl;
  printf("s2.addr = %p\n", s2.strAddr());
  s2.strAddr();

  cout << endl;
  cout << "赋值操作s3 = s2" << endl;
  String s3;
  s3 = s2;
  cout << "s2.refcount = " << s2.refCount() << endl;
  printf("s2.addr = %p\n", s2.strAddr());
  cout << "s3.refcount = " << s3.refCount() << endl;
  printf("s3.addr = %p\n", s3.strAddr());

  cout << endl;
  cout << "读下标操作" << endl;
  cout << "s2[0] = " << s2[0] << ", s1 = " << s1 << endl;
  cout << "s1.refcount = " << s1.refCount() << endl;
  printf("s1.addr = %p\n", s1.strAddr());
  cout << "s2.refcount = " << s2.refCount() << endl;
  printf("s2.addr = %p\n", s2.strAddr());
  cout << "s.size = " << s2.size() << endl;

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

  Tuple<int, double, std::string> t{1, 2.3, "haha"};
  cout << get<0>(t) << endl;
  cout << get<1>(t) << endl;
  cout << get<2>(t) << endl;
  cout << get<0>(t) << endl;

  std::string name("jmm");
  double score(1.2);
  int rank(10);
  Tuple<int, double, std::string> tt(1, 2.3, "haha");

  tt = tie(rank, score, name); // 10, 2.3, haha

  cout << rank << "eee" << endl;  // 10
  cout << name << "eee" << endl;  // haha
  cout << score << "eee" << endl; // 2.3
  cout << get<0>(tt) << "downin" << endl;
  cout << get<1>(tt) << "downin" << endl;
  cout << get<2>(tt) << "downin" << endl;

  Array<int, 3> arr1{1, 2, 3};

  for (auto ele : arr1)
  {
    cout << ele << " ";
  }

  cout << get<0>(arr1) << endl;
  ;

  //   Tuple<int, double, std::string> mm;

  //   Pair<int, std::string> a1(101, "lanzhihui"); // 参数类型必须与定义类型一样
  //   cout << a1.first << " " << a1.second << endl;

  //   Tuple<int, std::string> t2;
  //   t2 = a1;

  //   cout << get<0>(t2) << " hhhhh" << get<1>(t2) << "eee" << endl;
  //   // 这么看来copy构造是返回一个新的地址；
  // string name1;
  // Tuple<string&, int> tpRef(name1,30);
  // // 对tpRef第一个元素赋值，同时name也被赋值 - 引用
  // get<0>(tpRef) = "Sven";

  // // name输出也是Sven
  // cout << "name: " << name1 << '\n';
}