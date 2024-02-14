/*
target:
2. 实现另外几个容器：deque(optional)， array(明天) **
3. 算法和allocator(后天) ****
4. 解决单元测试(达后天开始) ***
5. 左右值优化（明天）**
6. 优化代码（明天）**

 */

/*
类模板有全特化和偏特化
而函数模板只有全特化
https://harttle.land/2015/10/03/cpp-template.html

类型转换
左右值
初始化template< class... Types >
std::tuple<Types&...> tie( Types&... args ) noexcept; //C++11起, C++14前
lambda函数
default: 我们知道有时候当我们仅创建了有参构造函数后，如果你想调用无参构造函数编译是会报错的。因为一旦你自己定义了构造函数，系统的默认构造函数是被屏蔽的，也就是说此时是没有无参构造函数的，所以我们需要自己定义一个无参构造函数。
但是现在在C++11中，如果我们仅定义了有参构造函数，可以通过default关键字让默认构造函数恢复
delete: https://zhuanlan.zhihu.com/p/430916670
noexcept
const-expr
explicit: 禁止隐式类型转换，如果的构造函数只有一个参数时, 那么在编译的时候就会有一个缺省的转换操作:将该构造函数对应数据类型的数据转换为该类对象. 也就是说 "CxString string2 = 10;" 这段代码, 
编译器自动将整型转换为CxString类对象
override
final
volatile
constexpr
std::forward; （转发）
关于默认拷贝构造函数（）
运算符全局重载
using 关键字和typedef区别


内存模型和内存pool
初始化
复杂指针
文件的链接性
static和auto

模板实例化原理

依赖名(dependent name)是指依赖于模板参数的名称，而非依赖名(non-dependent
name)则相反，指不依赖于模板参数的名称：

template <class T>
class MyClass {
     int i;
     vector<int> vi;
     vector<int>::iterator vitr;

     T t;
     vector<T> vt;
      vector<T>::iterator viter;
}

 因为int是内置类型，前三个定义的类型在声明这个模板类时就已知,叫做非依赖名。然而对于接下来的三行定义，只有在模板实例化时才能知道它们的类型，
 因为它们都依赖于模板参数T。则T,
vector<T>, vector<T>::iterator称为依赖名。

template <class T>
 void function()
 {
        T::iterator *iter;
        .....
 }
    看到上面这个例子时，我们脑子里可能会有两种想法：第一：T::iterator
*iter;实现乘法，iterator是类T的一个成员；第二：定义一个指针，指针指向的类型为T::iterator；

    这样的话就会产生异议，由上面的介绍可以知道iterator是类T的静态数据成员，静态成员函数或者是嵌套类型；如果没有修饰关键词typename编译器
    可能认为我们是想实现乘法运算；若我们的本意是想定义一个指针时，这是就需要typename来修饰，即在T::iterator前面加上关键字typename




  限定名(qualified name)
  做非限定名(unqualified
name)

class Date; // 前置声明
class Time
{
    friend class Date;
    // 声明日期类为时间类的友元类，则在日期类中就直接访问Time类中的私有成员变量
public:
    Time(int hour, int minute, int second): _hour(hour), _minute(minute),
_second(second)
    {}

private:
    int _hour;
    int _minute;
    int _second;
};

class Date
{
public:
    Date(int year = 1900, int month = 1, int day = 1): _year(year),
    _month(month),_day(day)
    {}
    void SetTimeOfDate(int hour, int minute, int second)
    {
        // 直接访问时间类私有的成员变量
        _t._hour = hour;
        _t._minute = minute;
        _t.second = second;
    }
private:
    int _year;
    int _month;
    int _day;
    Time _t;
};
 */