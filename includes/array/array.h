#ifndef TINYSTL_ARRAY_H
#define TINYSTL_ARRAY_H

#include "iterator/iterator.h"
#include "iterator/iterator_traits.h"
#include "adapter.h"
#include "allocator/alloc.h"
#include "allocator/allocator.h"

namespace tinystl
{
    template <typename T, size_t N, typename Alloc = Allocator<T>>
    class Array
    {
    private:
        T *m_data;
        size_t _size;

    public:
        // typedef Random_Access_Iterator<T, Array> iterator;

        /** constructor */
        typedef tinystl::Construct<T> constructor;

        /** typedefs */
        typedef Alloc data_allocator;
        typedef typename data_allocator::value_type value_type;
        typedef typename data_allocator::pointer pointer;
        typedef typename data_allocator::const_pointer const_pointer;
        typedef typename data_allocator::reference reference;
        typedef typename data_allocator::const_reference const_reference;
        typedef typename data_allocator::size_type size_type;
        typedef typename data_allocator::difference_type difference_type;

        typedef pointer iterator;
        typedef Reverse_Iterator<pointer> reverse_iterator;

        Array(std::initializer_list<value_type> arr);
        Array(iterator first, iterator last);
        Array(size_type size);
        Array();
        iterator begin() _GLIBCXX_NOEXCEPT;
        iterator end() _GLIBCXX_NOEXCEPT;
        void destroy();
        ~Array();
        Array(const Array<T, N, Alloc>&);
        reference operator[](size_type idx) const;
        reference at(size_t idx) const;
        pointer data();
        reference front() const;
        reference back() const;
        pointer data() const;
        bool empty() const;
        size_type size() const;
        size_type max_size() const;
        void fill(const_reference value);
        void swap(Array &arr);
        Array &operator=(const Array &arr);
    };

}

#include "array.tcc"

/*
线性的可以直接delete [] arr，非线性的需要遍历一个一个delete
赋值的时候记得被赋值的要滞空指针
 */

#endif

/*


using关键字
decltype
剩余参数
 */