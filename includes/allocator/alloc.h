#ifndef ALLOCATOR_H
#define ALLOCATOR_H


#include "construct.h"
#include "util.h"

namespace tinystl
{
    template <class T>
    class allocator
    {
    public:
        typedef T value_type;
        typedef T *pointer;
        typedef const T *const_pointer;
        typedef T &reference;
        typedef const T &const_reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;

    public:
        static T *allocate();
        static T *allocate(size_type n);

        static void deallocate(T *ptr);
        static void deallocate(T *ptr, size_type n);

        static void construct(T *ptr);
        static void construct(T *ptr, const T &value);
        static void construct(T *ptr, T &&value);

        template <class... Args>
        static void construct(T *ptr, Args &&...args);

        static void destroy(T *ptr);
        static void destroy(T *first, T *last);
    };

    /**
     * @brief allocate 1 unit mem of type T => T* ptr = new T[1]
     * 
     * @tparam T 
     * @return T* 
     */
    template <class T>
    T *allocator<T>::allocate()
    {
        // return new T();
        return static_cast<T*>(::operator new(sizeof(T)));
    }

    /**
     * @brief allocate n unit mem of type T => T* ptr = new T[n]
     * 
     * @tparam T 
     * @param n 
     * @return T* 
     */
    template <class T>
    T *allocator<T>::allocate(size_type n)
    {
        if (n == 0)
            return nullptr;
        // return new T[n];
        return static_cast<T*>(::operator new(sizeof(T) * n));
    }

    /**
     * @brief deallocate 1 unit => delete ptr
     * 
     * @tparam T 
     * @param ptr 
     */
    template <class T>
    void allocator<T>::deallocate(T *ptr)
    {
        if (ptr == nullptr)
            return;
        // delete(ptr);
        ::operator delete(ptr);
    }

    /**
     * @brief deallocate n unit => delete []ptr
     * 
     * @tparam T 
     */
    template <class T>
    void allocator<T>::deallocate(T *ptr, size_type /*size*/)
    {
        if (ptr == nullptr)
            return;
        // delete []ptr;
        ::operator delete(ptr);
    }

    
    template <class T>
    void allocator<T>::construct(T *ptr)
    {
        tinystl::construct(ptr);
    }

    template <class T>
    void allocator<T>::construct(T *ptr, const T &value)
    {
        tinystl::construct(ptr, value);
    }

    template <class T>
    void allocator<T>::construct(T *ptr, T &&value)
    {
        tinystl::construct(ptr, tinystl::move(value));
    }

    template <class T>
    template <class... Args>
    void allocator<T>::construct(T *ptr, Args &&...args)
    {
        tinystl::construct(ptr, tinystl::forward<Args>(args)...);
    }

    template <class T>
    void allocator<T>::destroy(T *ptr)
    {
        tinystl::destroy(ptr);
    }

    template <class T>
    void allocator<T>::destroy(T *first, T *last)
    {
        tinystl::destroy(first, last);
    }

}
#endif