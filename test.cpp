
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

class Pool
{
public:
    static char *start_free;

    static void allocate()
    {
        start_free = (char *)std::malloc(20);
    }
};

char *Pool::start_free = nullptr;

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
    // Pool::allocate();
    // arr[0] = new FreeList();

        // Test Container
    // std::list<tinystl::String, tinystl::Allocator<tinystl::String>> vec;
    tinystl::List<tinystl::String> vec;
    // vec.push_back(tinystl::String("Hello"));
    // vec.push_back(tinystl::String("World!"));
    // std::cout << vec.back() << "frfggt";
    return 0;
}