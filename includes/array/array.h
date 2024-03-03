#ifndef ARRAY
#define ARRAY

#include "iterator/iterator.h"
#include "iterator/iterator_traits.h"
#include "adapter.h"
#include "allocator/allocator_copy.h"

namespace tinystl
{
    template <typename T, size_t N>
    class Array
    {
    private:
        T *m_data;
        size_t _size;
        /** allocator */
        typedef tinystl::allocator<T> data_allocator;

        /** constructor */
        typedef tinystl::Construct<T> constructor;

        /** typedefs */
        typedef typename data_allocator::value_type value_type;
        typedef typename data_allocator::pointer pointer;
        typedef typename data_allocator::const_pointer const_pointer;
        typedef typename data_allocator::reference reference;
        typedef typename data_allocator::const_reference const_reference;
        typedef typename data_allocator::size_type size_type;
        typedef typename data_allocator::difference_type difference_type;

    public:
        // typedef T value_type; // alias for T
        // typedef Random_Access_Iterator<T, Array> iterator;
        typedef pointer iterator;
        typedef Reverse_Iterator<pointer> reverse_iterator;
        Array(std::initializer_list<value_type> arr)
        {
            // m_data = new T[arr.size()];
            _size = arr.size();
            m_data = data_allocator::allocate(_size);
            int i = 0;
            for (auto it = arr.begin(); it != arr.end(); ++it)
            {
                // *(m_data + i++) = *it;
                value_type *ptr = std::addressof(m_data[i++]);
                new ((void *)ptr) value_type(*it);
            }
        }

        Array(iterator first, iterator last)
        {
            _size = last - first;
            // m_data = new T[_size];
            m_data = data_allocator::allocate(_size);
            for (int i = 0; i < _size; i++)
            {
                value_type *ptr = std::addressof(m_data[i]);
                new ((void *)ptr) value_type(first[i]);

                // T *ptr = std::addressof(m_data[i]);
                // new ((void *)ptr) T(first[i]);
                // m_data[i] = first[i];
            }
        }

        Array(size_type size)
        {
            // m_data = new T[size];
            m_data = data_allocator::allocate(size);
            _size = size;
            for (int i = 0; i < _size; i++)
            {
                // m_data[i] = T();
                value_type *ptr = std::addressof(m_data[i]);
                new ((void *)ptr) value_type(value_type());
            }
        }

        Array()
        {
            // m_data = new value_type[N];
            m_data = data_allocator::allocate(N);
            _size = N;
            for (int i = 0; i < _size; i++)
            {
                // m_data[i] = T();
                value_type *ptr = std::addressof(m_data[i]);
                new ((void *)ptr) value_type(value_type());
            }
            // memset(m_data, 0, sizeof(T) * N);
        }

        iterator begin() _GLIBCXX_NOEXCEPT { return iterator(m_data); }

        iterator end() _GLIBCXX_NOEXCEPT
        {
            return iterator(m_data + _size);
        }

        void destroy()
        {
            for (int i = 0; i < _size; i++)
            {
                constructor::destroy(m_data[i]);
                // pointer ptr = std::addressof(m_data[i]);
                // if (ptr)
                // {
                //     ptr->~value_type();
                // }
            }
        }

        ~Array()
        {
            destroy();
            if (m_data)
            {
                data_allocator::deallocate(m_data);
            }
            // delete[] m_data;
            m_data = nullptr;
            _size = 0;
            // }
        }

        Array(const_reference arr)
        {
            int i;
            _size = arr._size;
            // m_data = new T[arr._size];
            m_data = data_allocator::allocate(arr._size);
            memset(m_data, 0, sizeof(value_type) * arr._size);
            for (i = 0; i < arr._size; i++)
            {
                // *(m_data + i) = *(arr.m_data + i);
                pointer ptr = std::addressof(m_data[i]);
                new ((void *)ptr) value_type(arr.m_data[i]);
            }
        }

        reference operator[](size_type idx) const
        {
            return m_data[idx];
        }

        reference at(size_t idx) const
        {
            return m_data[idx];
        }

        pointer data()
        {
            return m_data;
        }

        reference front() const
        {
            return m_data[0];
        }

        reference back() const
        {
            return m_data[_size - 1];
        }

        pointer data() const
        {
            return m_data;
        }

        bool empty() const
        {
            return _size == 0;
        }

        size_type size() const
        {
            return _size;
        }

        size_type max_size() const
        {
            return _size;
        }

        void fill(const_reference value)
        {
            memset(m_data, value, sizeof(value_type) * _size);
        }

        void swap(Array &arr)
        {
            pointer tmp = m_data;
            m_data = arr.m_data;
            arr.m_data = tmp;
        }

        Array &operator=(const Array &arr)
        {
            if (this == &arr)
                return *this;
            int i;
            // if (m_data)
            // {
            //     delete[] m_data;
            // }
            if (m_data)
            {
                destroy();
                data_allocator::deallocate(m_data);
            }
            _size = arr._size;

            // m_data = new value_type[_size];
            m_data = data_allocator::allocate(_size);
            for (i = 0; i < _size; i++)
            {
                pointer ptr = std::addressof(m_data[i]);
                new ((void *)ptr) value_type(arr[i]);
            }
            return *this;
        }
    };
}

/*
线性的可以直接delete [] arr，非线性的需要遍历一个一个delete
赋值的时候记得被赋值的要滞空指针
 */

#endif

/*


using关键字
decltype
剩余参数
向上转型
 */