#include <stddef.h>
#include <stdlib.h>
#include "allocator/construct.h"
#include "iterator/iterator.h"
#ifndef ADAPTER_H
#define ADAPTER_H

namespace tinystl
{
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