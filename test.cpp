
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
// #include "./includes/adapter.h"
// #include "./includes/string/string.h"
// #include "./includes/list/list.h"
#include <list>

template <typename T>
class Pool
{
public:
    static char *start_free;

    static void *allocate_()
    {
        start_free = (char *)std::malloc(20);
        return (void *)start_free;
    }

    static T *allocate()
    {
        return (T *)Pool::allocate_();
    }
};

template <typename T>
char *Pool<T>::start_free = nullptr;

template <class T>
class ObjectPool
{
public:
    // 对象池默认构造函数
    ObjectPool()
        : _memory(nullptr), _remain(0), _freeList(nullptr)
    {
    }
    // 申请一块T类型的对象空间
    T *New()
    {
        T *obj = nullptr;
        // 1、先看自由链表中是否有可用的对象空间，有的话直接从哪里拿
        // 2、没有的话从对象池中申请一块
        if (_freeList)
        {
            void *next = *(void **)_freeList;
            obj = (T *)_freeList;
            _freeList = next;
        }
        else
        {
            // 剩余空间不够一个对象的大小时要增容
            if (_remain < sizeof(T))
            {
                // delete[] _memory; // 错误操作
                size_t getSize = 100 * 1024;
                _memory = (char *)malloc(getSize);
                if (_memory == nullptr)
                {
                    throw std::bad_alloc();
                }
                _remain = getSize;
            }
            // 确保容量足够分配出一块对象大小的内存空间
            obj = (T *)_memory;
            size_t blockSize = sizeof(T) < sizeof(void *) ? sizeof(void *) : sizeof(T);
            _memory += blockSize;
            _remain -= blockSize;
        }
        new (obj) T; // 定位new显示调用T类型的默认构造函数初始化内存空间
        return obj;
    }
    // 伪释放一块T类型的对象空间
    void Delete(T *obj)
    {
        // 1、显示调用对象类型的构造函数，完成对象空间的内容清理
        obj->~T();
        // 2、把传入的这块对象空间头插到自由链表中
        *(void **)obj = _freeList;
        _freeList = obj;
    }

private:
    char *_memory;   // 对象池：指向一块连续待申请的空间
    size_t _remain;  // 记录对象池中剩余可用空间的大小，单位是字节
    void *_freeList; // 自由链表：指向第一块不用对象空间
};

struct FreeList
{
    FreeList *next;
    FreeList *prev;
    void *data;
    FreeList() : next(nullptr), prev(nullptr), data(nullptr) {}
};

struct TreeNode
{
    int _val;
    TreeNode *_left;
    TreeNode *_right;
    TreeNode() : _val(0), _left(nullptr), _right(nullptr) {}
};

int main()
{
    // const int n = 40;
    // int *p[n];

    // for (int i = 0; i < n; i++)
    // {
    //     p[i] = tinystl::Allocator<int>::allocate();
    //     *p[i] = i;
    // }

    // for (int i = 0; i < n; i++)
    // {
    //     std::cout << p[i] << ": " << *p[i] << std::endl;
    //     tinystl::Allocator<int>::deallocate(p[i]);
    // }

    // int* int1 = new int[1];
    // delete [] int1;

    // char *start_free = nullptr;
    // FreeList *arr[2] = {nullptr, nullptr};
    TreeNode *p = Pool<TreeNode>::allocate();
    p = new TreeNode();
    // std::cout << "pointer: " << p << " value = " << *p << std::endl;

    // size_t N = 20;
    // std::vector<TreeNode *> vet;
    // vet.resize(N);
    // for (size_t i = 0; i < vet.size(); i++)
    // {
    //     vet[i] = new TreeNode;
    // }

    // ObjectPool<TreeNode> pool;

    // for (size_t i = 0; i < vet.size(); i++)
    // {
    //     vet[i] = pool.New();
    // }

    // for (size_t i = 0; i < vet.size(); i++)
    // {
    //     pool.Delete(vet[i]);
    // }

    // arr[0] = new FreeList();

    // Test Container
    // std::list<tinystl::String, tinystl::Allocator<tinystl::String>> vec;
    // tinystl::List<tinystl::String> vec;
    // tinystl::String s("nvfjnvfjn");
    // vec.push_back();
    // vec.push_back(s);
    // std::cout << vec.back() << "frfggt";

    // tinystl::String a[] = {"aa", "bb", "cc", "dd", "ee"};
    // tinystl::List<tinystl::String>::iterator it_tmp; // 声明一个迭代器
    // tinystl::List<tinystl::String> l1(a, a + 5);
    return 0;
}