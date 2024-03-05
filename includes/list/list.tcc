#ifndef TINYSTL_LIST_TCC
#define TINYSTL_LIST_TCC

namespace tinystl
{
    template <typename T, typename Alloc>
    List<T, Alloc>::List()
    {
        head = base_allocator::allocate();
        tail = base_allocator::allocate();
        head->next = tail;
        tail->prev = head;
    }

    template <typename T, typename Alloc>
    List<T, Alloc>::List(List<T, Alloc>::size_type size)
    {
        head = base_allocator::allocate();
        tail = base_allocator::allocate();
        head->next = tail;
        tail->prev = head;
        for (int i = 0; i < size; i++)
        {
            push_back(T());
        }
    }

    template <typename T, typename Alloc>
    List<T, Alloc>::List(List<T, Alloc>::size_type size, const T &val)
    {
        head = base_allocator::allocate();
        tail = base_allocator::allocate();
        head->next = tail;
        tail->prev = head;
        for (int i = 0; i < size; i++)
        {
            push_back(val);
        }
    }

    template <typename T, typename Alloc>
    typename List<T, Alloc>::size_type List<T, Alloc>::size() const
    {
        auto node = head->next;
        size_t s = 0;
        while (node != tail)
        {
            node = node->next;
            ++s;
        }
        return s;
    }

    template <typename T, typename Alloc>
    bool List<T, Alloc>::empty()
    {
        return head->next == tail && tail->prev == head;
    }
    template <typename T, typename Alloc>
    void List<T, Alloc>::destroy_node(node_ptr p)
    {
        constructor::destroy(p->m_data);

        node_allocator::deallocate(p);
    }

    template <typename T, typename Alloc>
    void List<T, Alloc>::clear()
    {
        auto node = head->next;
        while (node != tail)
        {
            auto next = node->next;
            // delete node;

            destroy_node(node->as_node());
            node = next;
        }
        head->next = tail;
        tail->prev = head;
    }

    template <typename T, typename Alloc>
    List<T, Alloc>::~List()
    {
        clear();
        base_allocator::deallocate(head);
        base_allocator::deallocate(tail);

        /*
            因为我们的list头和尾巴也有数据，所有也要主动调用析构
        */

        // delete head;
        // delete tail;
        head = NULL;
        tail = NULL;
    }

    template <typename T, typename Alloc>
    void List<T, Alloc>::push_front(T data)
    {
        node_ptr node = node_allocator::allocate();
        T *ptr = std::addressof(node->m_data);
        new ((void *)ptr) T(data);
        // construct(std::addressof(node->m_data), arg)

        node->next = head->next;
        node->prev = head;

        head->next->prev = node;
        head->next = node;
    }

    template <typename T, typename Alloc>
    void List<T, Alloc>::push_back(const T &data)
    {
        node_ptr node = node_allocator::allocate();
        // T *ptr = std::addressof(node->m_data);
        // new ((void *)ptr) T(data);

        constructor::construct(node->m_data, data);

        node->prev = tail->prev;
        node->next = tail;
        tail->prev->next = node;
        tail->prev = node;
    }

    template <typename T, typename Alloc>
    void List<T, Alloc>::push_back(T &&data)
    {
        // node_ptr node = new node_type(data, tail->prev, tail);
        node_ptr node = node_allocator::allocate(); // 这里又调用一次String
        // auto node = create_node(data);

        // 构造
        T *ptr = std::addressof(node->m_data);
        new ((void *)ptr) T(data);

        node->prev = tail->prev;
        node->next = tail;
        tail->prev->next = node;
        tail->prev = node;
    }

    template <typename T, typename Alloc>
    List<T, Alloc>::List(const List &lt)
    {
        head = base_allocator::allocate();
        tail = base_allocator::allocate();
        head->next = tail;
        tail->prev = head;
        node_ptr node = static_cast<node_ptr>((lt.head)->next);
        while (node != lt.tail)
        {
            push_back(node->m_data);
            node = static_cast<node_ptr>(node->next);
        }
    }

    template <typename T, typename Alloc>
    List<T, Alloc>::List(T *from, T *to)
    {
        head = base_allocator::allocate();
        tail = base_allocator::allocate();
        head->next = tail;
        tail->prev = head;

        base_ptr pre = head;
        while (from != to)
        {
            node_ptr node = node_allocator::allocate();
            T *ptr = std::addressof(node->m_data);
            new ((void *)ptr) T(*from);

            node->prev = pre;
            node->next = tail;

            pre->next = node;
            tail->prev = node;
            pre = node;
            ++from;
        }
    }

    template <typename T, typename Alloc>
    List<T, Alloc>::List(iterator from, iterator to)
    {
        head = base_allocator::allocate();
        tail = base_allocator::allocate();
        head->next = tail;
        tail->prev = head;

        base_ptr pre = head;
        while (from != to)
        {
            node_ptr node = node_allocator::allocate();
            T *ptr = std::addressof(node->m_data);
            new ((void *)ptr) T(*from);

            // node->m_data = *from; // ****直接赋值有问题：

            node->prev = pre;
            node->next = tail;

            pre->next = node;
            tail->prev = node;
            pre = node;
            ++from;
        }
    }

    template <typename T, typename Alloc>
    List<T, Alloc>::List(std::initializer_list<T> lt)
    {
        head = base_allocator::allocate();
        tail = base_allocator::allocate();
        head->next = tail;
        tail->prev = head;

        base_ptr pre = head;
        for (auto &cur : lt)
        {
            // node_ptr node = new node_type(cur, pre, tail);
            typename List<T, Alloc>::node_ptr node = node_allocator::allocate();
            T *ptr = std::addressof(node->m_data);
            new ((void *)ptr) T(cur);

            node->prev = pre;
            node->next = tail;

            pre->next = node;
            tail->prev = node;
            pre = node;
        }
    }

    template <typename T, typename Alloc>
    List<T, Alloc> &List<T, Alloc>::operator=(const List &lt)
    {
        if (this != &lt)
        {
            clear(); // 清空自己
            typename List<T, Alloc>::node_ptr node = static_cast<typename List<T, Alloc>::node_ptr>((lt.head)->next);
            while (node != lt.tail)
            { // 遍历lt
                push_back(node->m_data);
                node = static_cast<typename List<T, Alloc>::node_ptr>(node->next);
            }
        }
        return *this;
    }

    template <typename T, typename Alloc>
    typename List<T, Alloc>::iterator List<T, Alloc>::begin()
    {
        return iterator(static_cast<typename List<T, Alloc>::node_ptr>(head->next));
    }

    template <typename T, typename Alloc>
    typename List<T, Alloc>::iterator List<T, Alloc>::end()
    {
        return iterator(static_cast<node_ptr>(tail));
    }

    template <typename T, typename Alloc>
    void List<T, Alloc>::pop_front()
    {
        if (empty())
        {
            throw NotElementException();
        }
        List<T, Alloc>::node_ptr node = static_cast<List<T, Alloc>::node_ptr>(head->next);
        head->next->next->prev = head;
        head->next = head->next->next;
        // delete node;
        node_allocator::deallocate(node);
    }

    template <typename T, typename Alloc>
    void List<T, Alloc>::pop_back()
    {
        if (empty())
        {
            throw NotElementException();
        }
        node_ptr node = static_cast<node_ptr>(tail->prev);
        tail->prev->prev->next = tail;
        tail->prev = tail->prev->prev;
        // delete node;
        node_allocator::deallocate(node);
    }

    template <typename T, typename Alloc>
    typename List<T, Alloc>::iterator List<T, Alloc>::erase(iterator &it)
    {
        if (it == head || it == tail)
        {
            throw InvalidIteratorException();
        }
        node_ptr next = it.node->next;
        it.node->prev->next = it.node->next;
        it.node->next->prev = it.node->prev;
        // delete it.node;
        node_allocator::deallocate(it.node);
        it.node = next;
        return it;
    }
    // it之前插入
    // iterator insert(iterator &it, T data)
    // {
    // 	if (it.node == head)
    // 	{
    // 		throw InvalidIteratorException();
    // 	}
    // 	node_ptr node = new node_type(data, it.node->prev, it.node);
    // 	it.node->prev->next = node;
    // 	it.node->prev = node;
    // 	it.node = node;
    // 	return it;
    // }
}

#endif