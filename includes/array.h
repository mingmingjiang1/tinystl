#ifndef ARRAY
#define ARRAY

#include <iostream>
#include "iterator.h"
#include "iterator_traits.h"
#include <cstring>

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

    public:
        typedef T value_type; // alias for T
        // typedef Random_Access_Iterator<T, Array> iterator;
        typedef T *iterator;
        typedef Reverse_Iterator<T *> reverse_iterator;
        Array(std::initializer_list<T> arr)
        {
            m_data = new T[arr.size()];
            _size = arr.size();
            typename std::initializer_list<T>::iterator it;
            int i = 0;
            for (it = arr.begin(); it != arr.end(); ++it)
            {
                *(m_data + i++) = *it;
            }
            // memset(this->m_data, 0, sizeof(T) * N);
        }

        Array(iterator first, iterator last)
        {
            _size = last - first;
            m_data = new T[_size];
            for (int i = 0; i < _size; i++)
            {
                m_data[i] = first[i];
            }
        }

        Array(size_t size)
        {
            m_data = new T[size];
            _size = size;
            memset(m_data, 0, sizeof(T) * size);
        }

        Array()
        {
            m_data = new T[N];
            _size = N;
            memset(m_data, 0, sizeof(T) * N);
        }

        iterator begin() _GLIBCXX_NOEXCEPT { return iterator(m_data); }

        iterator end() _GLIBCXX_NOEXCEPT
        {
            return iterator(m_data + _size);
        }

        ~Array()
        {
            if (this->m_data != NULL)
            {
                delete[] m_data;
                m_data = NULL;
            }
        }

        Array(const Array &arr)
        {
            int i;
            _size = arr._size;
            m_data = new T[arr._size];
            memset(m_data, 0, sizeof(T) * arr._size);
            for (i = 0; i < arr._size; i++)
            {
                *(m_data + i) = *(arr.m_data + i);
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
            if (m_data != NULL)
            {
                delete[] m_data;
            }
            _size = arr._size;
            m_data = new T[arr._size];

            // memset(m_data, 0, sizeof(T) * arr._size);
            m_data = new value_type[_size];
            for (i = 0; i < _size; i++)
            {
                m_data[i] = arr.m_data[i];
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