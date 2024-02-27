#ifndef MYTINYSTL_ALLOC_H_
#define MYTINYSTL_ALLOC_H_

#include <new>

#include <cstddef>
#include <cstdio>
#include <stdlib.h>
#include <iostream>

namespace tinystl
{

    // 共用体: FreeList
    // 采用链表的方式管理内存碎片，分配与回收小内存（<=4K）区块
    union FreeList
    {
        union FreeList *next; // 指向下一个区块
        char data[1];         // 储存本块内存的首地址
    };

    // 不同内存范围的上调大小
    enum
    {
        EAlign128 = 8,
        EAlign256 = 16,
        EAlign512 = 32,
        EAlign1024 = 64,
        EAlign2048 = 128,
        EAlign4096 = 256
    };

    // 小对象的内存大小
    enum
    {
        ESmallObjectBytes = 4096
    };

    // free lists 个数
    enum
    {
        EFreeListsNumber = 56
    };

    // 空间配置类 alloc
    // 如果内存较大，超过 4096 bytes，直接调用 std::malloc, std::free
    // 当内存较小时，以内存池管理，每次配置一大块内存，并维护对应的自由链表
    template <typename T>
    class alloc
    {
    private:
        static char *start_free;   // 内存池起始位置
        static char *start_free_1; // 内存池起始位置
        static char *end_free;     // 内存池结束位置
        static size_t heap_size;   // 申请 heap 空间附加值大小

        static FreeList *free_list[EFreeListsNumber]; // 自由链表

    public:
        static T *allocate(size_t n);
        static void deallocate(T *p, size_t n);
        static void *reallocate(void *p, size_t old_size, size_t new_size);

        ~alloc();

    private:
        static size_t M_align(size_t bytes);
        static size_t M_round_up(size_t bytes);
        static size_t M_freelist_index(size_t bytes);
        static T *M_refill(size_t n, size_t size);
        static char *M_chunk_alloc(size_t size, size_t &nobj);
    };

    // 静态成员变量初始化

    template <typename T>
    char *alloc<T>::start_free = nullptr;

    template <typename T>
    char *alloc<T>::start_free_1 = nullptr;

    template <typename T>
    char *alloc<T>::end_free = nullptr;

    template <typename T>
    size_t alloc<T>::heap_size = 0;

    template <typename T>
    FreeList *alloc<T>::free_list[EFreeListsNumber] = {
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};

    template <typename T>
    alloc<T>::~alloc()
    {
        for (int i = 0; i < EFreeListsNumber; i++)
        {
            if (free_list[i] != nullptr)
            {
                FreeList *ptr = free_list[i];
                while (ptr != nullptr)
                {
                    std::cout << "~alloc";
                    auto nptr = ptr->next;
                    delete []ptr;
                    ptr = nptr;
                }
            }
            free_list[i] = nullptr;
        }
    }

    // 分配大小为 n 的空间， n > 0, n单位是n个元素
    template <typename T>
    inline T *alloc<T>::allocate(size_t n)
    {
        if (n == 0)
        {
            return nullptr;
        }

        FreeList *my_free_list;
        if (n > ESmallObjectBytes)
            return new T[n];
        size_t size = n * sizeof(T);
        my_free_list = free_list[M_freelist_index(size)];
        std::cout << "allocate: " << n << " " << sizeof(T) << " " << M_freelist_index(size) << " " << M_round_up(sizeof(T)) << std::endl; // (8+7)/8 - 1
        FreeList *result = my_free_list;
        if (result == nullptr)
        {
            T *r = M_refill(M_round_up(size), n);

            return (T *)r;
        }
        my_free_list = result->next;
        return (T *)result;
    }

    // 释放 p 指向的大小为 n 的空间, p 不能为 0
    template <typename T>
    inline void alloc<T>::deallocate(T *p, size_t n)
    {
        if (n > ESmallObjectBytes)
        {

            delete[] p;
            return;
        }
        FreeList *q = reinterpret_cast<FreeList *>(p);
        std::cout << "delete:" << p << std::endl;

        // while (n)
        // {
        //     delete p;
        //     n++;
        // }
        FreeList *my_free_list;
        size_t size = n * sizeof(T);
        my_free_list = free_list[M_freelist_index(size)];
        q->next = my_free_list; // 插入到头部
        my_free_list = q;
    }

    // 重新分配空间，接受三个参数，参数一为指向新空间的指针，参数二为原来空间的大小，参数三为申请空间的大小
    template <typename T>
    inline void *alloc<T>::reallocate(void *p, size_t old_size, size_t new_size)
    {
        deallocate(p, old_size);
        p = allocate(new_size);
        return p;
    }

    // bytes 对应上调大小
    template <typename T>
    inline size_t alloc<T>::M_align(size_t bytes)
    {
        if (bytes <= 512)
        {
            return bytes <= 256
                       ? bytes <= 128 ? EAlign128 : EAlign256
                       : EAlign512;
        }
        return bytes <= 2048
                   ? bytes <= 1024 ? EAlign1024 : EAlign2048
                   : EAlign4096;
    }

    // 将 bytes 上调至对应区间大小
    template <typename T>
    inline size_t alloc<T>::M_round_up(size_t bytes)
    {
        return ((bytes + M_align(bytes) - 1) & ~(M_align(bytes) - 1));
    }

    // 根据区块大小，选择第 n 个 free lists
    template <typename T>
    inline size_t alloc<T>::M_freelist_index(size_t bytes)
    {
        if (bytes <= 512)
        {
            return bytes <= 256
                       ? bytes <= 128
                             ? ((bytes + EAlign128 - 1) / EAlign128 - 1)    // (n + 7 / 7) - 1 = n/7 = (1 ~ 128) / 7 = [0, 15]
                             : (15 + (bytes + EAlign256 - 129) / EAlign256) // 15 + (n - 113) / 16 = n/16 - 113 / 16 + 15 = n/16 + 8 = (129 ~ 256) / 16 + 8 = [16, 23]
                       : (23 + (bytes + EAlign512 - 257) / EAlign512);      // [24, 31] //
        }
        return bytes <= 2048
                   ? bytes <= 1024
                         ? (31 + (bytes + EAlign1024 - 513) / EAlign1024)  // [32, 39]
                         : (39 + (bytes + EAlign2048 - 1025) / EAlign2048) // [40. 47]
                   : (47 + (bytes + EAlign4096 - 2049) / EAlign4096);      // [48, 55]
    }

    // 重新填充 free list
    template <typename T>
    T *alloc<T>::M_refill(size_t n, size_t)
    {
        size_t nblock = 10;
        char *c = M_chunk_alloc(n, nblock);

        FreeList *my_free_list;
        FreeList *result, *cur, *next;
        // 如果只有一个区块，就把这个区块返回给调用者，free list 没有增加新节点
        if (nblock == 1)
            return (T *)c;
        // 否则把一个区块给调用者，剩下的纳入 free list 作为新节点
        my_free_list = free_list[M_freelist_index(n)];
        result = (FreeList *)c; // 起点

        std::cout << "refill: " << n << (void *)result << " " << M_freelist_index(n) << std::endl; // delete: 0x204d1c0, 160个字节, 0x204d0f0, end: 0x204d190 190 - 0f0 = 100 = 9*16 = 144
        my_free_list = next = (FreeList *)(c + n);                                                 // 起点+8,为什么是8，因为这是节点号
        for (size_t i = 1;; ++i)
        {
            cur = next;
            std::cout << "next: " << next << std::endl;
            next = (FreeList *)((char *)next + n); // 共9个节点，每个节点？个字节
            if (nblock - 1 == i)                   // 9 == 1
            {
                cur->next = nullptr;
                break;
            }
            else
            {
                cur->next = next;
            }
        }
        return (T *)result;
    }

    // 从内存池中取空间给 free list 使用，条件不允许时，会调整 nblock
    template <typename T>
    char *alloc<T>::M_chunk_alloc(size_t size, size_t &nblock)
    {
        char *result;
        size_t need_bytes = size * nblock; // 80
        size_t pool_bytes = end_free - start_free;

        // 如果内存池剩余大小完全满足需求量，返回它
        if (pool_bytes >= need_bytes)
        {
            result = (char *)start_free;
            std::cout << "pool_bytes" << (void *)result << (void *)start_free << pool_bytes << std::endl;
            // return start_free;
            start_free += need_bytes;
            return result;
        }

        // 如果内存池剩余大小不能完全满足需求量，但至少可以分配一个或一个以上的区块，就返回它
        else if (pool_bytes >= size)
        {
            nblock = pool_bytes / size;
            need_bytes = size * nblock;
            result = start_free;
            start_free += need_bytes;
            return result;
        }

        // 如果内存池剩余大小连一个区块都无法满足
        else
        {
            if (pool_bytes > 0)
            { // 如果内存池还有剩余，把剩余的空间加入到 free list 中
                FreeList *my_free_list = free_list[M_freelist_index(pool_bytes)];
                ((FreeList *)start_free)->next = my_free_list;
                my_free_list = (FreeList *)start_free;
            }
            // 申请 heap 空间
            size_t bytes_to_get = (need_bytes << 1) + M_round_up(heap_size >> 4);
            std::cout << "apply" << bytes_to_get << std::endl;
            start_free = new char[bytes_to_get];
            if (!start_free)
            { // heap 空间也不够
                FreeList *my_free_list, *p;
                // 试着查找有无未用区块，且区块足够大的 free list
                for (size_t i = size; i <= ESmallObjectBytes; i += M_align(i))
                {
                    my_free_list = free_list[M_freelist_index(i)];
                    p = my_free_list;
                    if (p)
                    {
                        my_free_list = p->next;
                        start_free = (char *)p;
                        end_free = start_free + i;
                        return M_chunk_alloc(size, nblock);
                    }
                }
                std::printf("out of memory");
                end_free = nullptr;
                throw std::bad_alloc();
            }
            end_free = start_free + bytes_to_get;
            std::cout << "yes" << (int *)start_free << (int *)end_free << std::endl;
            heap_size += bytes_to_get;
            return M_chunk_alloc(size, nblock);
        }
    }

} // namespace tinystl
#endif // !MYTINYSTL_ALLOC_H_