#ifndef TINYSTL_STACK_H
#define TINYSTL_STACK_H

#include "vector/vector.h"

namespace tinystl
{
    template <typename T, typename Container = tinystl::Vector<T>>
    class Stack
    {
    private:
        typedef Container container_type;

        // 使用底层容器的型别
        typedef typename Container::value_type value_type;
        typedef typename Container::size_type size_type;
        typedef typename Container::reference reference;
        typedef typename Container::const_reference const_reference;

        static_assert(std::is_same<T, value_type>::value,
                      "the value_type of Container should be same with T");
        container_type m_container;

    public:
        // 构造、复制、移动函数
        Stack() = default;

        explicit Stack(size_type n)
            : m_container(n)
        {
        }
        Stack(size_type n, const value_type &value)
            : m_container(n, value)
        {
        }

        template <class IIter>
        Stack(IIter first, IIter last)
            : m_container(first, last)
        {
        }

        Stack(std::initializer_list<T> ilist)
            : m_container(ilist.begin(), ilist.end())
        {
        }

        Stack(const Container &c)
            : m_container(c)
        {
        }
        Stack(Container &&c) noexcept(std::is_nothrow_move_constructible<Container>::value)
            : m_container(tinystl::move(c))
        {
        }

        Stack(const Stack &rhs)
            : m_container(rhs.m_container)
        {
        }
        Stack(Stack &&rhs) noexcept(std::is_nothrow_move_constructible<Container>::value)
            : m_container(tinystl::move(rhs.m_container))
        {
        }

        Stack &operator=(const Stack &rhs)
        {
            m_container = rhs.m_container;
            return *this;
        }
        Stack &operator=(Stack &&rhs) noexcept(std::is_nothrow_move_assignable<Container>::value)
        {
            m_container = tinystl::move(rhs.m_container);
            return *this;
        }

        Stack &operator=(std::initializer_list<T> ilist)
        {
            m_container = ilist;
            return *this;
        }

        ~Stack() = default;

        // 访问元素相关操作
        reference top() { return m_container.back(); }
        const_reference top() const { return m_container.back(); }

        // 容量相关操作
        bool empty() const noexcept { return m_container.empty(); }
        size_type size() const noexcept { return m_container.size(); }

        // 修改容器相关操作

        template <class... Args>
        void emplace(Args &&...args)
        {
            m_container.emplace_back(tinystl::forward<Args>(args)...);
        }

        void push(const value_type &value)
        {
            m_container.push_back(value);
        }
        void push(value_type &&value)
        {
            m_container.push_back(tinystl::move(value));
        }

        void pop()
        {
            m_container.pop_back();
        }

        void clear()
        {
            while (!empty())
                pop();
        }

        // void swap(Stack &rhs) noexcept(noexcept(tinystl::swap(m_container, rhs.m_container)))
        // {
        //     tinystl::swap(m_container, rhs.m_container);
        // }

    public:
        friend bool operator==(const Stack &lhs, const Stack &rhs) { return lhs.m_container == rhs.m_container; }
        friend bool operator<(const Stack &lhs, const Stack &rhs) { return lhs.m_container < rhs.m_container; }
    };
    
    // 重载比较操作符
    template <class T, class Container>
    bool operator==(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs)
    {
        return lhs == rhs;
    }

    template <class T, class Container>
    bool operator<(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs)
    {
        return lhs < rhs;
    }

    template <class T, class Container>
    bool operator!=(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs)
    {
        return !(lhs == rhs);
    }

    template <class T, class Container>
    bool operator>(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs)
    {
        return rhs < lhs;
    }

    template <class T, class Container>
    bool operator<=(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs)
    {
        return !(rhs < lhs);
    }

    template <class T, class Container>
    bool operator>=(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs)
    {
        return !(lhs < rhs);
    }

    // 重载 tinystl 的 swap
    template <class T, class Container>
    void swap(Stack<T, Container> &lhs, Stack<T, Container> &rhs) noexcept(noexcept(lhs.swap(rhs)))
    {
        lhs.swap(rhs);
    }
}

#endif