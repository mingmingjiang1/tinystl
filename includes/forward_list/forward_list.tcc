#ifndef TINYSTL_FORWARD_LIST_TCC
#define TINYSTL_FORWARD_LIST_TCC

#include "algorithm.h"

namespace tinystl
{
    template <class T, class Allocator>
    forward_list<T, Allocator>::forward_list()
    {
        head = base_allocator::allocate();
        tail = base_allocator::allocate();
        head->next = tail;
        m_size = 0;
    }

    template <class T, class Allocator>
    forward_list<T, Allocator>::forward_list(size_type size, const T &val)
    {
        head = base_allocator::allocate();
        tail = base_allocator::allocate();
        head->next = tail;
        for (int i = 0; i < size; i++)
        {
            push_back(val);
        }
    }

    template <class T, class Allocator>
    void forward_list<T, Allocator>::insert(forward_list<T, Allocator>::iterator it, T val)
    {
        auto node = head;
        while (iterator(node->next) != it && node->next != tail)
        {
            node = node->next;
        }
        auto next = node->next;
        node_ptr cur = node_allocator::allocate();
        construct(std::addressof(cur->m_data), val);
        node->next = cur;
        cur->next = next;
    }

    template <class T, class Allocator>
    forward_list<T, Allocator>::forward_list(size_type size)
    {
        head = base_allocator::allocate();
        tail = base_allocator::allocate();
        head->next = tail;
        for (int i = 0; i < size; i++)
        {
            push_back(T());
        }
    }

    template <class T, class Allocator>
    forward_list<T, Allocator>::forward_list(const forward_list &other)
    {
        head = base_allocator::allocate();
        tail = base_allocator::allocate();
        head->next = tail;
        node_ptr node = static_cast<node_ptr>((other.head)->next);
        while (node != other.tail)
        {
            push_back(node->m_data);
            node = static_cast<node_ptr>(node->next);
        }
    }
    template <class T, class Allocator>
    forward_list<T, Allocator>::forward_list::forward_list(iterator first, iterator last)
    {
        head = base_allocator::allocate();
        tail = base_allocator::allocate();
        head->next = tail;

        base_ptr pre = head;
        while (first != last)
        {
            node_ptr node = node_allocator::allocate();
            T *ptr = std::addressof(node->m_data);
            new ((void *)ptr) T(*first);

            node->next = tail;

            pre->next = node;
            pre = node;
            ++first;
        }
    }

    template <class T, class Allocator>
    forward_list<T, Allocator>::forward_list::forward_list(T *first, T *last)
    {
        head = base_allocator::allocate();
        tail = base_allocator::allocate();
        head->next = tail;
        m_size = last - first;

        base_ptr pre = head;
        while (first != last)
        {
            node_ptr node = node_allocator::allocate();
            T *ptr = std::addressof(node->m_data);
            new ((void *)ptr) T(*first);

            node->next = tail;

            pre->next = node;
            pre = node;
            ++first;
        }
    }

    template <class T, class Allocator>
    void forward_list<T, Allocator>::clear()
    {
        node_ptr node = static_cast<node_ptr>(head->next);
        while (node != tail)
        {
            node_ptr next = static_cast<node_ptr>(node->next);

            constructor::destroy(node->m_data);

            node_allocator::deallocate(node);
            node = next;
        }
        head->next = tail;
        m_size = 0;
    }

    template <class T, class Allocator>
    forward_list<T, Allocator>::forward_list(forward_list &&other)
    {
        // m_size = other.size();
        head = base_allocator::allocate();
        tail = base_allocator::allocate();
        head->next = tail;
        m_size = other.size();
        node_ptr tmp = static_cast<node_ptr>((other.head)->next);

        base_ptr pre = head;
        while (tmp != other.tail)
        {
            node_ptr node = node_allocator::allocate();
            T *ptr = std::addressof(node->m_data);
            new ((void *)ptr) T(tmp->m_data);

            node->next = tail;

            pre->next = node;
            pre = node;

            tmp = static_cast<node_ptr>(tmp->next);
        }

        // while (node != other.tail)
        // {
        //     push_back(node->m_data);
        //     node = static_cast<node_ptr>(node->next);
        // }
    }
    template <class T, class Allocator>
    forward_list<T, Allocator>::forward_list(std::initializer_list<T> il)
    {
        head = base_allocator::allocate();
        tail = base_allocator::allocate();
        head->next = tail;

        m_size = il.size();

        base_ptr pre = head;
        for (auto it = il.begin(); it != il.end(); ++it)
        {
            node_ptr node = node_allocator::allocate();
            T *ptr = std::addressof(node->m_data);
            new ((void *)ptr) T(*it);

            node->next = tail;

            pre->next = node;
            pre = node;
        }
    }

    template <class T, class Allocator>
    forward_list<T, Allocator> &forward_list<T, Allocator>::operator=(const forward_list &other)
    {
        if (this == &other)
        {
            return *this;
        }
        m_size = other.size();
        node_ptr node = static_cast<node_ptr>((other.head)->next);
        while (node != other.tail)
        {
            push_back(node->m_data);
            node = static_cast<node_ptr>(node->next);
        }
        return *this;
    }

    template <class T, class Allocator>
    void forward_list<T, Allocator>::erase(typename forward_list<T, Allocator>::iterator it)
    {
        if (head->next == tail)
        {
            return;
        }

        auto node = head;

        while (iterator(node->next) != it && node->next != tail)
        {
            node = node->next;
        }
        auto next = node->next->next;
        constructor::destroy(static_cast<node_ptr>(node->next)->m_data);

        node_allocator::deallocate(static_cast<node_ptr>(node->next));
        node->next = next;
    }

    template <class T, class Allocator>
    void forward_list<T, Allocator>::remove(const T &val)
    {

        base_ptr node = head;
        while (node->next != tail) // origin:  while (node != tail)
        {
            node_ptr cur = static_cast<node_ptr>(node->next);
            if (cur->m_data == val)
            {
                node->next = cur->next;
                constructor::destroy(cur->m_data);
                node_allocator::deallocate(cur);
                m_size--;
            }
            node = static_cast<node_ptr>(node->next);
        }
    }

    template <class T, class Allocator>
    forward_list<T, Allocator> &forward_list<T, Allocator>::operator=(forward_list &&other)
    {
        if (this == &other)
        {
            return *this;
        }
        m_size = other.size();
        node_ptr node = static_cast<node_ptr>((other.head)->next);
        while (node != other.tail)
        {
            push_back(node->m_data);
            node = static_cast<node_ptr>(node->next);
        }
        return *this;
    }

    template <class T, class Allocator>
    void forward_list<T, Allocator>::push_back(const T &val)
    {
        node_ptr node = node_allocator::allocate();

        construct(std::addressof(node->m_data), val);

        base_ptr tmp = head;
        while (tmp->next != tail)
        {
            tmp = tmp->next;
        }
        node->next = tmp->next;
        tmp->next = node;
        m_size++;
    }

    template <class T, class Allocator>
    void forward_list<T, Allocator>::push_back(T &&val)
    {
        node_ptr node = node_allocator::allocate();

        construct(std::addressof(node->m_data), val);

        base_ptr tmp = head;
        while (tmp->next != tail)
        {
            tmp = tmp->next;
        }
        node->next = tmp->next;
        tmp->next = node;
        m_size++;
    }

    template <class T, class Allocator>
    void forward_list<T, Allocator>::push_front(const T &val)
    {
        node_ptr node = node_allocator::allocate();

        construct(std::addressof(node->m_data), val);
        node->next = head->next;
        head->next = node;
        m_size++;
    }

    template <class T, class Allocator>
    void forward_list<T, Allocator>::pop_back()
    {
        // static_assert(m_size > 0);
        if (head->next == tail)
        {
            return;
        }

        m_size--;
        auto tmp = head;

        while (tmp->next->next != tail)
        {
            tmp = tmp->next;
        }

        node_ptr pop_ = static_cast<node_ptr>(tmp->next);
        tmp->next = tail;

        constructor::destroy(pop_->m_data);

        node_allocator::deallocate(pop_);
    }

    template <class T, class Allocator>
    void forward_list<T, Allocator>::pop_front()
    {
        m_size--;
        node_ptr tmp = static_cast<node_ptr>(head->next);
        head->next = tmp->next;
        constructor::destroy(tmp->m_data);

        node_allocator::deallocate(tmp);
    }

    template <class T, class Allocator>
    forward_list<T, Allocator>::~forward_list()
    {
        clear();
        base_allocator::deallocate(head);
        base_allocator::deallocate(tail);
        head = NULL;
        tail = NULL;
    }
    template <class T, class Allocator>
    typename forward_list<T, Allocator>::iterator forward_list<T, Allocator>::begin() const
    {
        return iterator(static_cast<node_ptr>(head->next));
    }

    template <class T, class Allocator>
    typename forward_list<T, Allocator>::iterator forward_list<T, Allocator>::end() const
    {
        return iterator(static_cast<node_ptr>(tail));
    }

    template <class T, class Allocator>
    typename forward_list<T, Allocator>::size_type forward_list<T, Allocator>::size() const
    {
        auto node = head->next;
        size_type s = 0;
        while (node != tail)
        {
            node = node->next;
            ++s;
        }
        return s;
    }

    template <class T, class Allocator>
    bool forward_list<T, Allocator>::empty() const
    {
        return m_size == 0;
    }
}

#endif // TINYSTL_FORWARD_LIST_TCC