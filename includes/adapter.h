#include <stddef.h>
#include <stdlib.h>
#include "allocator/construct.h"
#include "iterator/iterator.h"
#ifndef ADAPTER_H
#define ADAPTER_H

namespace tinystl
{

    static const int ALIGN = 8;
    static const int MAX_BYTES = 128;
    static const int FREE_LIST_NUMS = MAX_BYTES / ALIGN; // 16

    class Alloc
    {
    public:
        static void *allocate(size_t n)
        {
            obj **my_free_list;
            obj *result;
            if (n > (size_t)MAX_BYTES)
            {
                return ::operator new(n);
            }
            my_free_list = free_list + FREE_LIST_INDEX(n);
            result = *my_free_list;
            if (result == nullptr)
            {
                void *r = refill(ROUND_UP(n));
                return r;
            }
            try
            {
                // std::cout << " Alloc::allocate(size_t n) " << *my_free_list << " "  << result << std::endl; // *my_free_list是给用户的
                *my_free_list = result->next;
            }
            catch (...)
            {
                // std::cout << " catch branch " << std::endl;
            }
            return result;
        }
        static void deallocate(void *p, size_t n)
        {
            obj *q = (obj *)p;
            obj **my_free_list;
            if (n > (size_t)MAX_BYTES)
            {
                return ::operator delete(p);
            }
            my_free_list = free_list + FREE_LIST_INDEX(n);
            q->next = *my_free_list;
            *my_free_list = q;
        }

    private:
        // 单向链表
        union obj
        {
            union obj *next;
        };

    private:
        // 内存池
        static char *start_free;
        static char *end_free;
        static size_t heap_size;

    private:
        static obj *free_list[FREE_LIST_NUMS];
        static void *refill(size_t n);
        static char *chunk_alloc(size_t n, int &blocks);

    private:
        // 从 1 起步
        static size_t FREE_LIST_INDEX(size_t bytes)
        {
            return ((bytes + ALIGN - 1) / (ALIGN - 1));
        }
        static size_t ROUND_UP(size_t bytes)
        {
            return ((bytes + ALIGN - 1) & ~(ALIGN - 1));
        }
    };

    Alloc::obj *Alloc::free_list[FREE_LIST_NUMS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    char *Alloc::start_free = nullptr;
    char *Alloc::end_free = nullptr;
    size_t Alloc::heap_size = 0;

    void *Alloc::refill(size_t n)
    {
        int blocks = 20;
        char *chunk = chunk_alloc(n, blocks);

        obj **my_free_list;
        obj *result;
        obj *next_obj, *current_obj;
        if (blocks == 1)
        {
            return chunk;
        }
        my_free_list = free_list + FREE_LIST_INDEX(n);
        result = (obj *)chunk;
        *my_free_list = next_obj = (obj *)(chunk + n);
        for (int i = 1;; ++i)
        {
            current_obj = next_obj;
            next_obj = (obj *)((char *)next_obj + n);
            if (blocks - 1 == i)
            {
                current_obj->next = nullptr;
                break;
            }
            else
            {
                current_obj->next = next_obj;
            }
        }
        return result;
    }

    char *Alloc::chunk_alloc(size_t n, int &blocks)
    {
        size_t bytes_left = end_free - start_free;
        size_t total_bytes = n * blocks;
        char *result;
        if (bytes_left >= total_bytes)
        {
            result = start_free;
            start_free += total_bytes;
            return result;
        }
        else if (bytes_left >= n)
        {
            blocks = bytes_left / n;
            total_bytes = n * blocks;
            result = start_free;
            start_free += total_bytes;
            return result;
        }
        else
        {
            size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4);
            if (bytes_left > 0)
            {
                obj **my_free_list = free_list + FREE_LIST_INDEX(bytes_left);
                ((obj *)start_free)->next = *my_free_list;
                *my_free_list = (obj *)start_free;
            }
            start_free = (char *)std::malloc(bytes_to_get);
            if (start_free == nullptr)
            {
                obj **my_free_list;
                obj *p;
                for (int i = n + ALIGN; i <= MAX_BYTES; i += ALIGN)
                {
                    my_free_list = free_list + FREE_LIST_INDEX(i);
                    p = *my_free_list;
                    if (p != nullptr)
                    {
                        *my_free_list = p->next;
                        start_free = (char *)p;
                        end_free = (char *)p + i;
                        return chunk_alloc(n, blocks);
                    }
                }
                end_free = nullptr;
                start_free = (char *)::operator new(bytes_to_get);
            }
            heap_size += bytes_to_get;
            end_free = start_free + bytes_to_get;
            return chunk_alloc(n, blocks);
        }
    }

    template <typename T>
    class Allocator
    {
    public:
        typedef T value_type;
        typedef T *pointer;
        typedef const T *const_pointer;
        typedef T &reference;
        typedef const T &const_reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;

        static T *allocate(size_t n)
        {
            return (n == 0) ? 0 : (T *)Alloc::allocate(n * sizeof(T));
        }
        static T *allocate()
        {
            return (T *)Alloc::allocate(sizeof(T));
        }
        static void deallocate(T *p, size_t n)
        {
            if (n != 0)
            {
                Alloc::deallocate(p, n * sizeof(T));
            }
        }
        static void deallocate(T *p)
        {
            // p->~T();
            Alloc::deallocate(p, sizeof(T));
        }

        static void construct(T *ptr)
        {
            tinystl::construct(ptr);
        }

        static void construct(T *ptr, const T &value)
        {
            tinystl::construct(ptr, value);
        }

        static void construct(T *ptr, T &&value)
        {
            tinystl::construct(ptr, tinystl::move(value));
        }

        template <class... Args>
        static void construct(T *ptr, Args &&...args)
        {
            tinystl::construct(ptr, tinystl::forward<Args>(args)...);
        }
    };

    /** 迭代器适配器 */
    template <typename T, typename charT = char>
    class ostream_iterator
    {
        std::basic_ostream<charT> *out_stream;
        const charT *delim;

    public:
        typedef charT char_type;
        typedef std::basic_ostream<charT> ostream_type;
        ostream_iterator(ostream_type &s) : out_stream(&s), delim(0) {}
        ostream_iterator(ostream_type &s, const charT *delimiter) : out_stream(&s), delim(delimiter) {}
        ~ostream_iterator() {}
        ostream_iterator<T, charT> &operator=(const T &value)
        {
            *out_stream << value;
            if (delim != 0)
                *out_stream << delim;
            return *this;
        }
        ostream_iterator<T, charT> &operator*() { return *this; }
        ostream_iterator<T, charT> &operator++() { return *this; }
        ostream_iterator<T, charT> &operator++(int) { return *this; }
    };

    /** 迭代器适配器 */
    template <typename Iterator>
    class reverse_iterator
    {
        typedef reverse_iterator<Iterator> Self;

        typedef typename tinystl::Iterator_Traits<Iterator>::iterator_category iterator_category;
        typedef typename tinystl::Iterator_Traits<Iterator>::value_type value_type;
        typedef typename tinystl::Iterator_Traits<Iterator>::difference_type difference_type;
        typedef typename tinystl::Iterator_Traits<Iterator>::pointer pointer;
        typedef typename tinystl::Iterator_Traits<Iterator>::reference reference;

    public:
        reverse_iterator(Iterator it)
            : _it(it)
        {
        }

        reference operator*()
        {
            Iterator tmp = _it;
            return *(--tmp); // 与正向迭代器对称的设计，解引用访问前一个位置
        }

        pointer operator->()
        {
            return &(operator*());
        }

        Self &operator++()
        {
            --_it;
            return *this;
        }

        Self &operator--()
        {
            ++_it;
            return *this;
        }

        bool operator!=(const Self &s) const
        {
            return _it != s._it;
        }

    private:
        Iterator _it;
    };

    // 仿函数适配器
    class bind
    {
    };
}

/*


    auxiliary 0


*/

#endif