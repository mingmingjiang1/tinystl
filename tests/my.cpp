#include <string>
#include "../includes/test2.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    // auto ptr = new std::string("Hello, World!");
    // delete ptr;
    const int n = 40;
    // int p[n];

    int *p = tinystl::Allocator<int>::allocate(40);
    for (int i = 0; i < n; i++)
    {
        p[i] = i;
    }

    for (int i = 0; i < n; i++)
    {
        cout << ": " << p[i] << endl;
        // tinystl::Allocator<int>::deallocate(p[i]);
    }
    tinystl::Allocator<int>::deallocate(p);
    cout << endl;

    // m_data = new value_type[_size];
    vector<int> arr{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34};
    std::vector<int>::iterator it = arr.begin();
    int *m_data = tinystl::Allocator<int>::allocate(40);
    // m_data = static_cast<T *>(allocator_type_new::allocate(_size));
    int i = 0;

    for (; i < 40; i++)
    {
        m_data[i] = *(it+i);
    }

    for (int i = 0; i < 40; i++)
    {
        cout << ": " << m_data[i] << endl;
        // tinystl::Allocator<int>::deallocate(p[i]);
    }

    tinystl::Allocator<int>::deallocate(m_data);
    // Test Container
    vector<int, tinystl::Allocator<int>> vec;
    vec.push_back(3);
    vec.push_back(5);
    return 0;
}

/*
error:
Valgrind Fatal error at startup: a function redirection
sudo apt-get update
 sudo apt-get install libc6-dbg
 */