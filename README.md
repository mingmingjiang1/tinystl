
target:
1. 实现另外几个容器：deque(optional) **
2. 优化代码（明天）**
3. 算法和allocator(后天) ****
4. 解决单元测试(达后天开始) ***
5. 左右值优化（明天）**

检查list


 包含：
 1. 基本容器: array, vector, tuple, list, string
 2. 基本迭代器: random, sequential
 3. 基本算法: for_each
 4. 基本分配器: 自定义内存池(mempool, 初六)

知识点：
1. 面向对象编程
2. 泛型与模板
3. cow
4. 内存分配器
5. 自定义指针
6. 异常
7. 右值引用
8. 单元测试

下面补充一下函数指针的的概念
 

函数指针指向某种特定类型，函数的类型由其参数及返回类型共同决定，与函数名无关。举例如下：int add(int nLeft,int nRight);//函数定义  

 该函数类型为int(int,int),要想声明一个指向该类函数的指针，只需用指针替换函数名即可：

int(*p)(int, int);//未初始化
  则p可指向int(int,int)类型的函数。p前面有*，说明p是指针，右侧是形参列表，表示pf指向的是函数，左侧为int，说明pf指向的函数返回值为int。则pf可指向int(int,int)类型的函数。而LESS类型为int(int,int),则p可指向LESS函数。

p = LESS;//通过赋值使得函数指针指向某具体函数
