#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <iostream>
// #include "./pool.h"

template <typename T, size_t N = 0>
class StackAllocator
{
public:
    using value_type = T;
    using pointer = T *;
    using const_pointer = const T *;
    using reference = T &;
    using const_reference = const T &;
    using difference_type = ptrdiff_t;

    StackAllocator() noexcept {}
    template <class U>
    StackAllocator(const StackAllocator<U, N> &) noexcept {}
    ~StackAllocator() noexcept {}

    pointer allocate(size_t n)
    {
        cout << n << max_size() << std::endl;
        if (n > max_size())
        {
            throw std::bad_alloc();
        }
        if (_start + n > _end)
        {
            throw std::bad_alloc();
        }
        auto result = _start;
        _start += n;
        return result;
    }

    pointer allocate()
    {
        // return
        // _buf = ;
        // return static_cast<pointer>(::operator new(sizeof(T))); // 堆上分配
    }

    void deallocate()
    {
        // if (p == nullptr)
        //     return;
    }

    template <class U, class... Args>
    void construct(U *p, Args &&...args)
    {
        new (p) U(std::forward<Args>(args)...);
    }

    void destroy(pointer p) { p->~T(); }

    size_t max_size() const noexcept { return N; }

private:
    // alignas(alignof(T))
    char _buf[N * sizeof(T)];
    // MemPool<sizeof(T) * N, 1> mp;
    pointer _start = reinterpret_cast<pointer>(_buf);
    pointer _end = reinterpret_cast<pointer>(_buf + sizeof(_buf));
};

template <typename T, typename U, size_t N>
bool operator==(const StackAllocator<T, N> &, const StackAllocator<U, N> &)
{
    return true;
}

template <typename T, typename U, size_t N>
bool operator!=(const StackAllocator<T, N> &lhs, const StackAllocator<U, N> &rhs)
{
    return !(lhs == rhs);
}

#endif