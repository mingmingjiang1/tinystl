#ifndef LIST_H
#define LIST_H

#include "iterator.h"
#include "adapter.h"
#include "allocator_copy.h"
#include <string>
#include <memory>
#include <iostream>

/**
 * @brief List Class
 *
 */

class NotElementException : public std::exception
{
public:
	NotElementException(const char *info = "没有元素") : errinfo(info) {}
	~NotElementException() throw() {}
	const char *what() throw()
	{
		return errinfo.c_str();
	}

private:
	std::string errinfo;
};

class InvalidIteratorException : public std::exception
{
public:
	InvalidIteratorException(const char *info = "无效迭代器指针") : errinfo(info) {}
	~InvalidIteratorException() throw() {}
	const char *what() throw()
	{
		return errinfo.c_str();
	}

private:
	std::string errinfo;
};

namespace tinystl
{
	template <typename T>
	class NodeAlloc
	{
	public:
		static T *allocate()
		{
			return static_cast<T *>(::operator new(sizeof(T)));
			;
		}

		static void deallocate(T *ptr)
		{
			if (ptr == nullptr)
				return;
			::operator delete(ptr); // 一定要用这个，用new T()，会调用构造函数，会自动初始化所有数据成员
		}
	};

	template <typename T>
	class List
	{

	public:
		typedef Bidirectional_Access_Iterator<T, List> iterator;
		// typedef tinystl::Allocator<node_type> allocator_type;
		// typedef tinystl::allocator<node_type> allocator_type;
		// typedef tinystl::NodeAlloc<node_type> allocator_type;
		// typedef tinystl::NodeAlloc<T> data_allocator;

		/** allocator */
		typedef tinystl::Allocator<list_node_base<T>> base_allocator;
		typedef tinystl::Allocator<list_node<T>> node_allocator;
		typedef tinystl::Allocator<T> data_allocator;

		typedef typename node_traits<T>::base_ptr base_ptr;
		typedef typename node_traits<T>::node_ptr node_ptr;

		/** constructor */
		typedef tinystl::Construct<T> constructor;

		List()
		{
			head = base_allocator::allocate();
			tail = base_allocator::allocate();
			head->next = tail;
			tail->prev = head;
		}

		List(size_t size)
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

		List(size_t size, const T& val)
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

		size_t size()
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
		bool empty()
		{
			return head->next == tail && tail->prev == head;
		}
		void destroy_node(node_ptr p)
		{
			// data_allocator::destroy(mystl::address_of(p->value));
			// T *ptr = std::addressof(p->m_data);

			// if (ptr)
			// {
			// 	ptr->~T();
			// }

			constructor::destroy(p->m_data);

			node_allocator::deallocate(p);
		}

		void clear()
		{
			auto node = head->next;
			while (node != tail)
			{
				auto next = node->next;
				// delete node;
				// data_allocator::destroy(mystl::address_of(p->value));

				// allocator_type::deallocate(node);
				destroy_node(node->as_node());
				node = next;
			}
			head->next = tail;
			tail->prev = head;
		}
		~List()
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

		void push_front(T data)
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

		void push_back(const T &data)
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
		void push_back(T &&data)
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

		List(const List &lt)
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

		// template<typename Args>
		// node_type* create_node(Args &&...args)
		// {
		// 	node_type p = allocator_type::allocate(1);
		// 	try
		// 	{
		// 		data_allocator::construct(std::address_of(p->value), std::forward<Args>(args)...);
		// 		p->prev = nullptr;
		// 		p->next = nullptr;
		// 	}
		// 	catch (...)
		// 	{
		// 		allocator_type::deallocate(p);
		// 		throw;
		// 	}
		// 	return p;
		// }

		List(T *from, T *to)
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

		List(iterator from, iterator to)
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

		List(std::initializer_list<T> lt)
		{
			head = base_allocator::allocate();
			tail = base_allocator::allocate();
			head->next = tail;
			tail->prev = head;

			base_ptr pre = head;
			for (auto &cur : lt)
			{
				// node_ptr node = new node_type(cur, pre, tail);
				node_ptr node = node_allocator::allocate();
				T *ptr = std::addressof(node->m_data);
				new ((void *)ptr) T(cur);

				node->prev = pre;
				node->next = tail;

				pre->next = node;
				tail->prev = node;
				pre = node;
			}
		}

		// l1 = l2;
		List &operator=(const List &lt)
		{
			if (this != &lt)
			{
				clear(); // 清空自己
				node_ptr node = static_cast<node_ptr>((lt.head)->next);
				while (node != lt.tail)
				{ // 遍历lt
					push_back(node->m_data);
					node = static_cast<node_ptr>(node->next);
				}
			}
			return *this;
		}

		// class iterator
		// {
		// public:
		// 	node_ptr node;

		// public:
		// 	iterator(node_ptr node) : node(node){};
		// 	iterator &operator++()
		// 	{
		// 		node = node->next;
		// 		return *this;
		// 	}
		// 	iterator operator++(int)
		// 	{
		// 		iterator it(*this);
		// 		node = node->next;
		// 		return it;
		// 	}
		// 	iterator &operator--()
		// 	{
		// 		node = node->prev;
		// 		return *this;
		// 	}
		// 	iterator operator--(int)
		// 	{
		// 		iterator it(*this);
		// 		node = node->prev;
		// 		return it;
		// 	}
		// 	bool operator==(const iterator &it) const
		// 	{
		// 		return node == it.node;
		// 	};
		// 	bool operator!=(const iterator &it) const
		// 	{
		// 		return node != it.node;
		// 	}
		// 	T &operator*(void)
		// 	{
		// 		return node->data;
		// 	}
		// };

		iterator begin()
		{
			return iterator(static_cast<node_ptr>(head->next));
		}
		iterator end()
		{
			return iterator(static_cast<node_ptr>(tail));
		}
		void pop_front()
		{
			if (empty())
			{
				throw NotElementException();
			}
			node_ptr node = static_cast<node_ptr>(head->next);
			head->next->next->prev = head;
			head->next = head->next->next;
			// delete node;
			node_allocator::deallocate(node);
		}
		void pop_back()
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
		// 删除it所指向的节点
		iterator erase(iterator &it)
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

	private:
		base_ptr head;
		base_ptr tail;
	};

}

#endif