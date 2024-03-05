#ifndef TINYSTL_ARRAY_TCC
#define TINYSTL_ARRAY_TCC

#include <cstring>

namespace tinystl
{
    template <typename T, size_t N, typename Alloc>
    Array<T, N, Alloc>::Array(std::initializer_list<value_type> arr)
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

    template <typename T, size_t N, typename Alloc>
    Array<T, N, Alloc>::Array(iterator first, iterator last)
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

    template <typename T, size_t N, typename Alloc>
    Array<T, N, Alloc>::Array(size_type size)
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

    template <typename T, size_t N, typename Alloc>
    Array<T, N, Alloc>::Array()
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

    template <typename T, size_t N, typename Alloc>
    typename Array<T, N, Alloc>::iterator Array<T, N, Alloc>::begin() _GLIBCXX_NOEXCEPT { return iterator(m_data); }

    template <typename T, size_t N, typename Alloc>
    typename Array<T, N, Alloc>::iterator Array<T, N, Alloc>::end() _GLIBCXX_NOEXCEPT
    {
        return iterator(m_data + _size);
    }

    template <typename T, size_t N, typename Alloc>
    void Array<T, N, Alloc>::destroy()
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

    template <typename T, size_t N, typename Alloc>
    Array<T, N, Alloc>::~Array()
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

    template <typename T, size_t N, typename Alloc>
    Array<T, N, Alloc>::Array(const_reference arr)
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

    template <typename T, size_t N, typename Alloc>
    typename Array<T, N, Alloc>::reference Array<T, N, Alloc>::operator[](size_type idx) const
    {
        return m_data[idx];
    }

    template <typename T, size_t N, typename Alloc>
    typename Array<T, N, Alloc>::reference Array<T, N, Alloc>::at(size_t idx) const
    {
        return m_data[idx];
    }

    template <typename T, size_t N, typename Alloc>
    typename Array<T, N, Alloc>::pointer Array<T, N, Alloc>::data()
    {
        return m_data;
    }

    template <typename T, size_t N, typename Alloc>
    typename Array<T, N, Alloc>::reference Array<T, N, Alloc>::front() const
    {
        return m_data[0];
    }

    template <typename T, size_t N, typename Alloc>
    typename Array<T, N, Alloc>::reference Array<T, N, Alloc>::back() const
    {
        return m_data[_size - 1];
    }

    template <typename T, size_t N, typename Alloc>
    typename Array<T, N, Alloc>::pointer Array<T, N, Alloc>::data() const
    {
        return m_data;
    }

    template <typename T, size_t N, typename Alloc>
    bool Array<T, N, Alloc>::empty() const
    {
        return _size == 0;
    }

    template <typename T, size_t N, typename Alloc>
    typename Array<T, N, Alloc>::size_type Array<T, N, Alloc>::size() const
    {
        return _size;
    }

    template <typename T, size_t N, typename Alloc>
    typename Array<T, N, Alloc>::size_type Array<T, N, Alloc>::max_size() const
    {
        return _size;
    }

    template <typename T, size_t N, typename Alloc>
    void Array<T, N, Alloc>::fill(const_reference value)
    {
        memset(m_data, value, sizeof(value_type) * _size);
    }

    template <typename T, size_t N, typename Alloc>
    void Array<T, N, Alloc>::swap(Array &arr)
    {
        pointer tmp = m_data;
        m_data = arr.m_data;
        arr.m_data = tmp;
    }

    template <typename T, size_t N, typename Alloc>
    Array<T, N, Alloc> &Array<T, N, Alloc>::operator=(const Array<T, N, Alloc> &arr)
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
}

#endif