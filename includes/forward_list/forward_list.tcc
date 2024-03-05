#ifndef TINYSTL_FORWARD_LIST_TCC
#define TINYSTL_FORWARD_LIST_TCC

// #include "forward_list.h"

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
    forward_list<T, Allocator>::forward_list(size_t size, const T &val)
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
        size_type size = last - first;
        head = base_allocator::allocate();
        tail = base_allocator::allocate();
        head->next = tail;
        for (int i = 0; i < size; i++)
        {
            push_back(*(first + i));
        }
    }

    template <class T, class Allocator>
    forward_list<T, Allocator>::forward_list::forward_list(const T *first, const T *last)
    {
        size_type size = last - first;
        head = base_allocator::allocate();
        tail = base_allocator::allocate();
        head->next = tail;
        for (int i = 0; i < size; i++)
        {
            push_back(*(first + i));
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
    }

    template <class T, class Allocator>
    forward_list<T, Allocator>::forward_list(forward_list &&other)
    {
        // m_size = other.size();
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
    forward_list<T, Allocator>::forward_list(const std::initializer_list<T> &il)
    {
        head = base_allocator::allocate();
        tail = base_allocator::allocate();
        head->next = tail;
        for (auto &i : il)
        {
            push_back(i);
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

    // template <class T, class Allocator>
    // typename forward_list<T, Allocator>::iterator forward_list<T, Allocator>::erase(typename forward_list<T, Allocator>::iterator it) {
    //     // if (it == head || it == tail)
    // 	// 	{
    // 	// 		return;
    // 	// 	}
    // 		node_ptr next = ;
    // 		it.node->prev->next = it.node->next;
    // 		it.node->next->prev = it.node->prev;
    // 		node_allocator::deallocate(it.node);
    // 		it.node = next;
    // 		return it;
    // }

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
        node_ptr tmp = static_cast<node_ptr>(head->next);
        while (tmp != tail)
        {
            // node_ptr tmp = tmp->next;
            destroy(std::addressof(tmp->m_data));
            tmp = static_cast<node_ptr>(tmp->next);
            node_allocator::deallocate(tmp);
        }
        base_allocator::deallocate(head);
        base_allocator::deallocate(tail);
    }
    template <class T, class Allocator>
    typename forward_list<T, Allocator>::iterator forward_list<T, Allocator>::begin()
    {
        return iterator(static_cast<node_ptr>(head->next));
    }

    template <class T, class Allocator>
    typename forward_list<T, Allocator>::iterator forward_list<T, Allocator>::end()
    {
        return iterator(static_cast<node_ptr>(tail));
    }

    template <class T, class Allocator>
    typename forward_list<T, Allocator>::size_type forward_list<T, Allocator>::size() const
    {
        return m_size;
    }

    template <class T, class Allocator>
    bool forward_list<T, Allocator>::empty() const
    {
        return m_size == 0;
    }
}

#endif // TINYSTL_FORWARD_LIST_TCC