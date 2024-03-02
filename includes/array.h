#ifndef ARRAY
#define ARRAY

#include <iostream>
#include <cstring>

#include "iterator.h"
#include "iterator_traits.h"
#include "adapter.h"
#include "allocator_copy.h"

namespace tinystl
{
    // template <size_t idx, typename T>
    // class Array;
    template <typename T, size_t N>
    class Array
    {
    private:
        T *m_data;
        size_t _size;
        /** allocator */
        typedef tinystl::allocator<T> data_allocator;

    public:
        typedef T value_type; // alias for T
        // typedef Random_Access_Iterator<T, Array> iterator;
        typedef T *iterator;
        typedef Reverse_Iterator<T *> reverse_iterator;
        Array(std::initializer_list<T> arr)
        {
            /*

                  _size = _capacity = arr.size();
                  m_data = data_allocator::allocate(_size);
                  int i = 0;
                  for (auto it = arr.begin(); it != arr.end(); ++it)
                  {
                    // m_data[i++] = *it;
                    T *ptr = std::addressof(m_data[i++]);
                    new ((void *)ptr) T(*it);
                  }
             */
            std::cout << "size: ===> " << arr.size() << std::endl;
            // m_data = new T[arr.size()];
            _size = arr.size();
            m_data = data_allocator::allocate(_size);
            int i = 0;
            for (auto it = arr.begin(); it != arr.end(); ++it)
            {
                // *(m_data + i++) = *it;
                T *ptr = std::addressof(m_data[i++]);
                new ((void *)ptr) T(*it);
            }
        }

        Array(iterator first, iterator last)
        {
            _size = last - first;
            // m_data = new T[_size];
            m_data = data_allocator::allocate(_size);
            for (int i = 0; i < _size; i++)
            {
                T *ptr = std::addressof(m_data[i]);
                new ((void *)ptr) T(first[i]);

                // T *ptr = std::addressof(m_data[i]);
                // new ((void *)ptr) T(first[i]);
                // m_data[i] = first[i];
            }
        }

        Array(size_t size)
        {
            // m_data = new T[size];
            m_data = data_allocator::allocate(size);
            _size = size;
            for (int i = 0; i < _size; i++)
            {
                // m_data[i] = T();
                T *ptr = std::addressof(m_data[i]);
                new ((void *)ptr) T(T());
            }
        }

        Array()
        {
            // m_data = new value_type[N];
            m_data = data_allocator::allocate(N);
            std::cout << "jnfrjnjn" << sizeof(T) << N << m_data;
            _size = N;
            for (int i = 0; i < _size; i++)
            {
                // m_data[i] = T();
                T *ptr = std::addressof(m_data[i]);
                new ((void *)ptr) T(T());
            }
            // memset(m_data, 0, sizeof(T) * N);
        }

        iterator begin() _GLIBCXX_NOEXCEPT { return iterator(m_data); }

        iterator end() _GLIBCXX_NOEXCEPT
        {
            return iterator(m_data + _size);
        }

        void destroy_one()
        {
            for (int i = 0; i < _size; i++)
            {

                T *ptr = std::addressof(m_data[i]);
                if (ptr)
                {
                    ptr->~T();
                }
            }
        }

        ~Array()
        {
            std::cout << "调用析构函数" << m_data;
            destroy_one();
            if (m_data)
            {
                data_allocator::deallocate(m_data);
            }
            // delete[] m_data;
            m_data = nullptr;
            _size = 0;
            // }
        }

        Array(const Array &arr)
        {
            int i;
            _size = arr._size;
            // m_data = new T[arr._size];
            m_data = data_allocator::allocate(arr._size);
            memset(m_data, 0, sizeof(T) * arr._size);
            for (i = 0; i < arr._size; i++)
            {
                // *(m_data + i) = *(arr.m_data + i);
                T *ptr = std::addressof(m_data[i]);
                new ((void *)ptr) T(arr.m_data[i]);
            }
        }

        T &operator[](size_t idx) const
        {
            return m_data[idx];
        }

        T &at(size_t idx) const
        {
            return m_data[idx];
        }

        T *data()
        {
            return m_data;
        }

        T &front() const
        {
            return m_data[0];
        }

        T &back() const
        {
            return m_data[_size - 1];
        }

        T *data() const
        {
            return m_data;
        }

        bool empty() const
        {
            return _size == 0;
        }

        size_t size() const
        {
            return _size;
        }

        size_t max_size() const
        {
            return _size;
        }

        void fill(const T &value)
        {
            memset(m_data, value, sizeof(T) * _size);
        }

        void swap(Array &arr)
        {
            T *tmp = m_data;
            m_data = arr.m_data;
            arr.m_data = tmp;
        }

        Array<T, N> &operator=(const Array<T, N> &arr)
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
                destroy_one();
                data_allocator::deallocate(m_data);
            }
            _size = arr._size;

            // memset(m_data, 0, sizeof(T) * arr._size);
            // m_data = new value_type[_size];
            m_data = data_allocator::allocate(_size);
            for (i = 0; i < _size; i++)
            {
                // m_data[i] = arr.m_data[i];
                T *ptr = std::addressof(m_data[i]);
                new ((void *)ptr) T(arr[i]);
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