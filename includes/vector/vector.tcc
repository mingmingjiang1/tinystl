#ifndef TINYSTL_VECTOR_TCC
#define TINYSTL_VECTOR_TCC

namespace tinystl
{
    template <typename T, typename Alloc>
    Vector<T, Alloc>::Vector(Vector<T, Alloc>::size_type size)
    {
        _size = _capacity = size;
        m_data = data_allocator::allocate(_size);
        for (int i = 0; i < size; i++)
        {
            // m_data[i] = static_cast<T>(0);
            T *ptr = std::addressof(m_data[i]);
            new ((void *)ptr) T();
        }
    }
    template <typename T, typename Alloc>
    Vector<T, Alloc>::Vector(T *first, T *last)
    {
        _size = _capacity = last - first;
        m_data = data_allocator::allocate(_size);
        for (int i = 0; i < _size; i++)
        {
            T *ptr = std::addressof(m_data[i]);
            new ((void *)ptr) T(first[i]);
        }
    }
    template <typename T, typename Alloc>
    Vector<T, Alloc>::Vector(Vector<T, Alloc>::size_type size, const T &value) // value为临时对象的时候，value在当前行之后的生命周期结束了
    {
        _size = _capacity = size;
        m_data = data_allocator::allocate(_size);
        for (int i = 0; i < size; i++)
        {
            // m_data[i] = value;
            T *ptr = std::addressof(m_data[i]);
            new ((void *)ptr) T(value);
        }
    }
    // template <typename T>
    // Vector<T, Alloc>::Vector(typename Vector<T, Alloc>::size_type size, T &&value) // value为临时对象的时候，value在当前行之后的生命周期结束了
    // {
    //     _size = _capacity = size;
    //     m_data = data_allocator::allocate(_size);
    //     for (int i = 0; i < size; i++)
    //     {
    //         // m_data[i] = value;
    //         T *ptr = std::addressof(m_data[i]);
    //         new ((void *)ptr) T(value);
    //     }
    // }
    template <typename T, typename Alloc>
    Vector<T, Alloc>::Vector(std::initializer_list<T> arr)
    {
        _size = _capacity = arr.size();
        m_data = data_allocator::allocate(_size);
        int i = 0;
        for (auto it = arr.begin(); it != arr.end(); ++it)
        {
            // m_data[i++] = *it;
            T *ptr = std::addressof(m_data[i++]);
            new ((void *)ptr) T(*it);
        }
    }
    template <typename T, typename Alloc>
    Vector<T, Alloc>::Vector() : m_data(nullptr), _size(0), _capacity(0) {}

    template <typename T, typename Alloc>
    void Vector<T, Alloc>::clear()
    {
        _size = 0;
    }

    template <typename T, typename Alloc>
    void Vector<T, Alloc>::pop_back() { --_size; }

    template <typename T, typename Alloc>
    void Vector<T, Alloc>::erase(const iterator it)
    {
        if (it >= iterator(m_data + _size))
        {
            return;
        }
        int index = it - begin();
        for (int i = index; i < _size; i++)
        {
            m_data[i] = m_data[i + 1];
        }
        --_size;
    }

    template <typename T, typename Alloc>
    void Vector<T, Alloc>::destroy()
    {
        for (int i = 0; i < _size; i++)
        {
            constructor::destroy(m_data[i]);
        }
    }

    template <typename T, typename Alloc>
    typename Vector<T, Alloc>::reverse_iterator Vector<T, Alloc>::rbegin() _GLIBCXX_NOEXCEPT
    {
        return reverse_iterator(m_data + _size);
    }

    template <typename T, typename Alloc>
    const typename Vector<T, Alloc>::reverse_iterator Vector<T, Alloc>::rbegin() const _GLIBCXX_NOEXCEPT
    {
        return const_reverse_iterator(m_data + _size);
    }

    template <typename T, typename Alloc>
    typename Vector<T, Alloc>::reverse_iterator Vector<T, Alloc>::rend()
    {
        return reverse_iterator(m_data);
    }

    template <typename T, typename Alloc>
    const typename Vector<T, Alloc>::reverse_iterator Vector<T, Alloc>::rend() const _GLIBCXX_NOEXCEPT
    {
        return const_reverse_iterator(m_data);
    }

    template <typename T, typename Alloc>
    typename Vector<T, Alloc>::const_reverse_iterator Vector<T, Alloc>::crbegin() const _GLIBCXX_NOEXCEPT
    {
        return rbegin();
    }

    template <typename T, typename Alloc>
    typename Vector<T, Alloc>::const_reverse_iterator Vector<T, Alloc>::crend() const _GLIBCXX_NOEXCEPT
    {
        return rend();
    }

    template <typename T, typename Alloc>
    typename Vector<T, Alloc>::value_type Vector<T, Alloc>::front() { return m_data[0]; }

    template <typename T, typename Alloc>
    typename Vector<T, Alloc>::value_type Vector<T, Alloc>::back() { return m_data[_size - 1]; }

    template <typename T, typename Alloc>
    typename Vector<T, Alloc>::const_iterator Vector<T, Alloc>::begin() const _GLIBCXX_NOEXCEPT { return const_iterator(m_data); }

    template <typename T, typename Alloc>
    typename Vector<T, Alloc>::iterator Vector<T, Alloc>::begin() _GLIBCXX_NOEXCEPT { return iterator(m_data); }

    template <typename T, typename Alloc>
    typename Vector<T, Alloc>::const_iterator Vector<T, Alloc>::cbegin() const _GLIBCXX_NOEXCEPT
    {
        return begin();
    }

    template <typename T, typename Alloc>
    typename Vector<T, Alloc>::iterator Vector<T, Alloc>::end() _GLIBCXX_NOEXCEPT
    {

        return iterator(m_data + _size);
    }

    template <typename T, typename Alloc>
    typename Vector<T, Alloc>::const_iterator Vector<T, Alloc>::end() const _GLIBCXX_NOEXCEPT
    {

        return const_iterator(m_data + _size);
    }

    template <typename T, typename Alloc>
    typename Vector<T, Alloc>::const_iterator Vector<T, Alloc>::cend() const _GLIBCXX_NOEXCEPT
    {
        return end();
    }

    template <typename T, typename Alloc>
    typename Vector<T, Alloc>::size_type Vector<T, Alloc>::capacity() { return _capacity; }

    template <typename T, typename Alloc>
    bool Vector<T, Alloc>::empty() { return _size == 0; }

    template <typename T, typename Alloc>
    typename Vector<T, Alloc>::size_type Vector<T, Alloc>::size() const { return _size; }

    template <typename T, typename Alloc>
    typename Vector<T, Alloc>::value_type &Vector<T, Alloc>::operator[](int index)
    {
        return m_data[index];
    }

    template <typename T, typename Alloc>
    void Vector<T, Alloc>::push_back(const value_type &vec)
    {
        if (_capacity == 0)
        {
            _capacity = 1;
            m_data = data_allocator::allocate(_capacity);
        }
        else if (_size == _capacity)
        {
            T *new_data = data_allocator::allocate(_capacity * 2);
            for (int i = 0; i < _size; i++)
            {
                new_data[i] = m_data[i];
            }
            data_allocator::deallocate(m_data, _size);
            m_data = new_data;
            _capacity *= 2;
        }
        m_data[_size++] = vec;
    }

    /*
      初始化列表的初始化顺序并不是由构造函数后的变量顺序决定的，而是由类中成员变量的定义顺序决定的
     */

    template <typename T, typename Alloc>
    Vector<T, Alloc>::~Vector()
    {
        destroy();
        if (m_data)
        {
            data_allocator::deallocate(m_data, _size);
        }
        m_data = nullptr;
        _size = 0;
        _capacity = 0;
    }

    template <typename T, typename Alloc>
    bool Vector<T, Alloc>::operator==(value_type &vec)
    {
        if (_size != vec._size)
            return false;
        for (int i = 0; i < _size; ++i)
        {
            if (m_data[i] != vec._data[i])
                return false;
        }
        return true;
    }

    // deep copy
    template <typename T, typename Alloc>
    Vector<T, Alloc>::Vector(const Vector<T, Alloc> &vec)
    {
        _size = vec._size;
        _capacity = vec._capacity;
        m_data = data_allocator::allocate(_size);
        for (int i = 0; i < _size; i++)
        {
            T *ptr = std::addressof(m_data[i]);
            new ((void *)ptr) T(vec.m_data[i]);
            // m_data[i] = vec.m_data[i];
        }
    }

    template <typename T, typename Alloc>
    void Vector<T, Alloc>::insert(iterator it, value_type val)
    {
        // int index = it - m_data;
        const size_type index = it - begin();
        if (0 == _capacity)
        {
            _capacity = 1;
            m_data = data_allocator::allocate();
            m_data[0] = val;
        }
        else if (_size + 1 > _capacity)
        {
            _capacity *= 2;
            value_type *temp = data_allocator::allocate(_capacity);
            for (int i = 0; i < index; ++i)
            {
                temp[i] = m_data[i];
            }
            temp[index] = val;
            for (int i = index; i < _size; i++)
            {
                temp[i + 1] = m_data[i];
            }
            data_allocator::deallocate(m_data, _size);
            m_data = temp;
        }
        else
        {
            for (int i = _size - 1; i >= index; --i)
            {
                m_data[i + 1] = m_data[i];
            }
            m_data[index] = val;
        }
        ++_size;
    }

    template <typename T, typename Alloc>
    Vector<T, Alloc> &Vector<T, Alloc>::operator=(const Vector<T, Alloc> &vec)
    {
        if (&vec == this)
        {
            return *this;
        }
        if (_size)
        {
            destroy();
            data_allocator::deallocate(m_data, _size);
            m_data = nullptr;
        }
        _size = vec._size;
        _capacity = vec._capacity;
        m_data = data_allocator::allocate(_size);
        for (int i = 0; i < _size; i++)
        {
            // m_data[i] = vec.m_data[i];
            T *ptr = std::addressof(m_data[i]);
            new ((void *)ptr) T(vec.m_data[i]);
        }
        return *this;
    }
}

#endif