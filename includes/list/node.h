#ifndef TINYSTL_LIST_NODE_H
#define TINYSTL_LIST_NODE_H

namespace tinystl
{
    template <class T>
    struct list_node_base;

    template <class T>
    struct list_node;

    template <class T>
    struct node_traits
    {
        typedef list_node_base<T> *base_ptr;
        typedef list_node<T> *node_ptr;
    };

    // list 的节点结构

    template <class T>
    struct list_node_base
    {
        typedef typename node_traits<T>::base_ptr base_ptr;
        typedef typename node_traits<T>::node_ptr node_ptr;

        base_ptr prev; // 前一节点
        base_ptr next; // 下一节点

        list_node_base() = default;

        node_ptr as_node()
        {
            return static_cast<node_ptr>(self());
        }

        void unlink()
        {
            prev = next = self();
        }

        base_ptr self()
        {
            return static_cast<base_ptr>(&*this);
        }
    };

    template <class T>
    struct list_node : public list_node_base<T>
    {
        typedef typename node_traits<T>::base_ptr base_ptr;
        typedef typename node_traits<T>::node_ptr node_ptr;
        // typedef typename tinystl::NodeAlloc<list_node<T>> allocator;

        /*

            node_ptr node = node_allocator::allocate();
            T *ptr = std::addressof(node->m_data);
            new ((void *)ptr) T(data);
         */

        T m_data; // 数据域

        // T* _M_get_node()
        // {

        //   return allocator::allocate();
        // }

        list_node()
        {
            std::cout << "list_node" << std::endl;
        }

        ~list_node()
        {
            std::cout << "~~~~~~~~~~list_node" << std::endl;
        };

        list_node(const T &v)
            : m_data(v)
        {
        }
        list_node(T &&v)
            : m_data(std::move(v))
        {
        }

        base_ptr as_base()
        {
            return static_cast<base_ptr>(&*this);
        }
        node_ptr self()
        {
            return static_cast<node_ptr>(&*this);
        }
    };
}

#endif // TINYSTL_LIST_NODE_H