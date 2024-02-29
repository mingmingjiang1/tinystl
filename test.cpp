
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "./includes/adapter.h"
#include "./includes/String.h"
#include "./includes/list.h"
#include <vector>
#include <list>

template<typename T>
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

template<typename T>
char *Pool<T>::start_free = nullptr;

struct FreeList
{
    FreeList *next;
    FreeList *prev;
    void *data;
    FreeList() : next(nullptr), prev(nullptr), data(nullptr) {}
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
    int *p = Pool<int>::allocate();
    *p = 2;
    std::cout << "pointer: " << p << " value = " << *p << std::endl;
    // arr[0] = new FreeList();

    // Test Container
    std::list<tinystl::String, tinystl::Allocator<tinystl::String>> vec;
    // tinystl::List<tinystl::String> vec;
    tinystl::String s("nvfjnvfjn");
    // vec.push_back();
    vec.push_back(s);
    // std::cout << vec.back() << "frfggt";

    // tinystl::String a[] = {"aa", "bb", "cc", "dd", "ee"};
    // tinystl::List<tinystl::String>::iterator it_tmp; // 声明一个迭代器
    // tinystl::List<tinystl::String> l1(a, a + 5);
    return 0;
}