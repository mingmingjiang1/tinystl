#ifndef TINYSTL_LIST_NODE_H
#define TINYSTL_LIST_NODE_H

/*   template<typename _Tp, typename _Alloc>
    class _List_base
    {
    protected:
      typedef typename __gnu_cxx::__alloc_traits<_Alloc>::template
	rebind<_Tp>::other				_Tp_alloc_type;

      typedef __gnu_cxx::__alloc_traits<_Tp_alloc_type>	_Tp_alloc_traits;

      typedef typename _Tp_alloc_traits::template
	rebind<_List_node<_Tp> >::other _Node_alloc_type;

      typedef __gnu_cxx::__alloc_traits<_Node_alloc_type> _Node_alloc_traits;

#if !_GLIBCXX_INLINE_VERSION
      static size_t
      _S_distance(const __detail::_List_node_base* __first,
		  const __detail::_List_node_base* __last)
      {
	size_t __n = 0;
	while (__first != __last)
	  {
	    __first = __first->_M_next;
	    ++__n;
	  }
	return __n;
      }

#if __cplusplus >= 201103L
	_List_impl(_List_impl&&) = default;

	_List_impl(_Node_alloc_type&& __a, _List_impl&& __x)
	: _Node_alloc_type(std::move(__a)), _M_node(std::move(__x._M_node))
	{ }

	_List_impl(_Node_alloc_type&& __a) noexcept
	: _Node_alloc_type(std::move(__a))
	{ }
#endif
      };

      _List_impl _M_impl;

#if _GLIBCXX_USE_CXX11_ABI
      size_t _M_get_size() const { return _M_impl._M_node._M_size; }

      void _M_set_size(size_t __n) { _M_impl._M_node._M_size = __n; }

      void _M_inc_size(size_t __n) { _M_impl._M_node._M_size += __n; }

      void _M_dec_size(size_t __n) { _M_impl._M_node._M_size -= __n; }
#endif

      typename _Node_alloc_traits::pointer
      _M_get_node()
      { return _Node_alloc_traits::allocate(_M_impl, 1); }

      void
      _M_put_node(typename _Node_alloc_traits::pointer __p) _GLIBCXX_NOEXCEPT
      { _Node_alloc_traits::deallocate(_M_impl, __p, 1); }

  public:
      typedef _Alloc allocator_type;

      _Node_alloc_type&
      _M_get_Node_allocator() _GLIBCXX_NOEXCEPT
      { return _M_impl; }

      const _Node_alloc_type&
      _M_get_Node_allocator() const _GLIBCXX_NOEXCEPT
      { return _M_impl; }

#if __cplusplus >= 201103L
      _List_base() = default;
#else
      _List_base() { }
#endif

      _List_base(const _Node_alloc_type& __a) _GLIBCXX_NOEXCEPT
      : _M_impl(__a)
      { }

#if __cplusplus >= 201103L
      _List_base(_List_base&&) = default;

# if !_GLIBCXX_INLINE_VERSION
      _List_base(_List_base&& __x, _Node_alloc_type&& __a)
      : _M_impl(std::move(__a))
      {
	if (__x._M_get_Node_allocator() == _M_get_Node_allocator())
	  _M_move_nodes(std::move(__x));
	// else caller must move individual elements.
      }
# endif

      // Used when allocator is_always_equal.
      _List_base(_Node_alloc_type&& __a, _List_base&& __x)
      : _M_impl(std::move(__a), std::move(__x._M_impl))
      { }

      // Used when allocator !is_always_equal.
      _List_base(_Node_alloc_type&& __a)
      : _M_impl(std::move(__a))
      { }

      void
      _M_move_nodes(_List_base&& __x)
      { _M_impl._M_node._M_move_nodes(std::move(__x._M_impl._M_node)); }
#endif

      // This is what actually destroys the list.
      ~_List_base() _GLIBCXX_NOEXCEPT
      { _M_clear(); }

      void
      _M_clear() _GLIBCXX_NOEXCEPT;

      void
      _M_init() _GLIBCXX_NOEXCEPT
      { this->_M_impl._M_node._M_init(); }
    }; 
    */

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