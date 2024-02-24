# tinystl
无聊的时候随便写的一个简易stl库，主要是因为个人比较喜欢cpp这个语言，语言这个东西长期不用就忘了，希望有一个长期项目来练手；所以干脆就写一个项目；
这个项目会一直维护，直到比较完善了或者从事了cpp相关的工作

目录结构：


包含：
1. 基本容器: Array, Vector, Tuple, List, String
2. 基本迭代器: random, sequential
3. 基本算法: for_each, count_if, sort, max(min), max(min)_element, bind2nd ...
4. 基本分配器: 自定义内存池
5. 辅助容器: tuple, pair

知识点：
1. 面向对象编程(orient object programming)
2. 泛型与模板(generic programming & template)
3. cow string(copy on write for string)
4. 内存池(memory pool)  
5. 自定义指针(custom pointer)
6. 断言(exception)
7. 右值引用(move semantics)
8. 单元测试(ctest & gtest)

约定：

| 前缀 | 意义               | 前缀 | 意义       |
| ---- | ------------------ | ---- | ---------- |
| g_   | 全局变量           | C_   | 常量/macro |
| m_   | 类成员变量(public) | s_   | 静态变量   |
|      |                    |      |            |




## 支持
操作系统
linux
windows
编译器
g++ 8.3 或以上
cmake 3.15 或以上

## 需要
使用 cmake 3.15以上 来构建项目（可选）

## 运行测试

gcc on linux
``` shell
克隆仓库
$ git clone git@github.com:mingmingjiang1/tinystl.git
$ cd tinystl
构建并运行
$ mkdir build && cd build
$ cmake ..
$ make
$ cd ../bin && ./stltest
```

mingw on window


https://wangjii.github.io/article/25e9/



