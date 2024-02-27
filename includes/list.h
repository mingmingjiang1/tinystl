#ifndef LIST_H
#define LIST_H

#include "iterator.h"
#include "adapter.h"
#include "allocator_copy.h"
#include <string>
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
			T *p = new T();
			return p;
		}

		static void deallocate(T *p)
		{
			delete p;
		}
	};

	template <typename T>
	class List
	{

	public:
		typedef Bidirectional_Access_Iterator<T, List> iterator;
		typedef Node<T> node_type;
		typedef tinystl::Allocator<node_type> allocator_type;
		// typedef tinystl::allocator<node_type> allocator_type;
		// typedef tinystl::NodeAlloc<node_type> allocator_type;

		List()
		{
			head = allocator_type::allocate();
			tail = allocator_type::allocate();
			head->next = tail;
			tail->prev = head;
		}
		size_t size()
		{
			node_type *node = head->next;
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
		void clear()
		{
			node_type *node = head->next;
			while (node != tail)
			{
				node_type *next = node->next;
				// delete node;
				allocator_type::deallocate(node);
				node = next;
			}
			head->next = tail;
			tail->prev = head;
		}
		~List()
		{
			clear();
			allocator_type::deallocate(head);
			allocator_type::deallocate(tail);
			// delete head;
			// delete tail;
			head = NULL;
			tail = NULL;
		}
		void push_front(T data)
		{
			node_type *node = new node_type(data, head, head->next);
			head->next->prev = node;
			head->next = node;
		}
		void push_back(T data)
		{
			node_type *node = new node_type(data, tail->prev, tail);
			tail->prev->next = node;
			tail->prev = node;
		}
		List(const List &lt)
		{
			head = allocator_type::allocate();
			tail = allocator_type::allocate();
			head->next = tail;
			tail->prev = head;
			node_type *node = (lt.head)->next;
			while (node != lt.tail)
			{
				push_back(node->data);
				node = node->next;
			}
		}

		List(std::initializer_list<T> lt)
		{
			head = allocator_type::allocate();
			tail = allocator_type::allocate();
			head->next = tail;
			tail->prev = head;

			node_type *pre = head;
			for (auto &cur : lt)
			{
				node_type *node = new node_type(cur, pre, tail);
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
				node_type *node = (lt.head)->next;
				while (node != lt.tail)
				{ // 遍历lt
					push_back(node->data);
					node = node->next;
				}
			}
			return *this;
		}

		// class iterator
		// {
		// public:
		// 	node_type *node;

		// public:
		// 	iterator(node_type *node) : node(node){};
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
			return iterator(head->next);
		}
		iterator end()
		{
			return iterator(tail);
		}
		void pop_front()
		{
			if (empty())
			{
				throw NotElementException();
			}
			node_type *node = head->next;
			head->next->next->prev = head;
			head->next = head->next->next;
			// delete node;
			allocator_type::deallocate(node);
		}
		void pop_back()
		{
			if (empty())
			{
				throw NotElementException();
			}
			node_type *node = tail->prev;
			tail->prev->prev->next = tail;
			tail->prev = tail->prev->prev;
			// delete node;
			allocator_type::deallocate(node);
		}
		// 删除it所指向的节点
		iterator erase(iterator &it)
		{
			if (it == head || it == tail)
			{
				throw InvalidIteratorException();
			}
			node_type *next = it.node->next;
			it.node->prev->next = it.node->next;
			it.node->next->prev = it.node->prev;
			// delete it.node;
			allocator_type::deallocate(it.node);
			it.node = next;
			return it;
		}
		// it之前插入
		iterator insert(iterator &it, T data)
		{
			if (it.node == head)
			{
				throw InvalidIteratorException();
			}
			node_type *node = new node_type(data, it.node->prev, it.node);
			it.node->prev->next = node;
			it.node->prev = node;
			it.node = node;
			return it;
		}

	private:
		node_type *head;
		node_type *tail;
	};

}

#endif