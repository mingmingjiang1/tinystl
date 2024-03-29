#ifndef TINYSTL_LIST_H
#define TINYSTL_LIST_H

#include "../iterator/iterator.h"
#include "../adapter.h"
#include "../allocator/alloc.h"
#include "../allocator/allocator.h"
#include <string>
#include <memory>
#include <iostream>

/**
 * @brief List Class
 *
 */


namespace tinystl
{
	template <typename T, typename Alloc = Allocator<T>>
	class List
	{

	public:
		typedef Bidirectional_Access_Iterator<T, List> iterator;

		/** allocator */
		typedef tinystl::allocator<list_node_base<T>> base_allocator;
		typedef tinystl::allocator<list_node<T>> node_allocator;
		typedef Alloc data_allocator;

		typedef typename node_traits<T>::base_ptr base_ptr;
		typedef typename node_traits<T>::node_ptr node_ptr;

		typedef typename data_allocator::size_type size_type;
		typedef typename data_allocator::value_type value_type;

		typedef typename data_allocator::reference reference;
		typedef typename data_allocator::const_reference const_reference;

		/** constructor */
		typedef tinystl::Construct<T> constructor;

		List();
		List(size_type size);
		List(size_type size, const T &val);
		size_type size() const;
		bool empty();
		void destroy_node(node_ptr p);
		void clear();
		~List();
		void push_front(T data);
		void push_back(const T &data);
		void push_back(T &&data);
		List(const List &lt);
		List(T *from, T *to);
		List(iterator from, iterator to);
		List(std::initializer_list<T> lt);
		List &operator=(const List &lt);
		iterator begin() const;
		iterator end() const;
		void pop_front();
		void pop_back();
		// 删除it所指向的节点
		void erase(iterator it);
		// it之前插入
		void insert(iterator it, T data);
		value_type& operator[](size_type index);

	private:
		base_ptr head;
		base_ptr tail;
	};
}

#include "list.tcc"

#endif