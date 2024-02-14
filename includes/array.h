#ifndef ARRAY
#define ARRAY

#include <iostream>
#include "iterator.h"
#include "iterator_traits.h"

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
    typedef Random_Access_Iterator<T, Array> random_access_iterator;
    typedef Reverse_Iterator<T *> reverse_iterator;
    Array(initializer_list<T> arr)
    {
        m_data = new T[N];
        _size = N;
        initializer_list<int>::iterator it;
        int i = 0;
        for (it = arr.begin(); it != arr.end(); ++it)
        {
            *(m_data + i++) = *it;
        }
        // memset(this->m_data, 0, sizeof(T) * N);
    }

    Array()
    {
        m_data = new T[N];
        _size = N;
        memset(m_data, 0, sizeof(T) * N);
    }


    random_access_iterator begin() _GLIBCXX_NOEXCEPT { return random_access_iterator(m_data); }

    random_access_iterator end() _GLIBCXX_NOEXCEPT
    {
        cout << m_data << m_data + _size  << "gggggggg" << endl;
        return random_access_iterator(m_data + _size);
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

    T operator[](size_t idx) const
    {
        return m_data[idx];
    }

    T &at(size_t idx) const
    {
        return m_data[idx];
    }

    T* data() {
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

    void print() const
    {
        for (int i = 0; i < _size; i++)
        {
            std::cout << m_data[i] << " ";
        }
        std::cout << std::endl;
    }
};

#endif

/*


using关键字
decltype
剩余参数
向上转型
 */