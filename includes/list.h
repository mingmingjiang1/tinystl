#ifndef LIST_H
#define LIST_H

#include "iterator.h"
#include "adapter.h"
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
	class List
	{
	private:
		class Node
		{
		public:
			T data;
			Node *prev;
			Node *next;

		public:
			Node() : prev(NULL), next(NULL) {}
			Node(T data, Node *prev = NULL, Node *next = NULL) : data(data), prev(prev), next(next) {}
		};
		Node *head;
		Node *tail;

	public:
		List()
		{
			head = tinystl::Allocator<Node>::allocate(1);
			tail = tinystl::Allocator<Node>::allocate(1);
			head->next = tail;
			tail->prev = head;
		}
		size_t size()
		{
			Node *node = head->next;
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
			Node *node = head->next;
			while (node != tail)
			{
				Node *next = node->next;
				// delete node;
				tinystl::Allocator<Node>::deallocate(node);
				node = next;
			}
			head->next = tail;
			tail->prev = head;
		}
		~List()
		{
			clear();
			tinystl::Allocator<Node>::deallocate(head);
			tinystl::Allocator<Node>::deallocate(tail);
			// delete head;
			// delete tail;
			head = NULL;
			tail = NULL;
		}
		void push_front(T data)
		{
			Node *node = new Node(data, head, head->next);
			head->next->prev = node;
			head->next = node;
		}
		void push_back(T data)
		{
			Node *node = new Node(data, tail->prev, tail);
			tail->prev->next = node;
			tail->prev = node;
		}
		List(const List &lt)
		{
			head = tinystl::Allocator<Node>::allocate(1);
			tail = tinystl::Allocator<Node>::allocate(1);
			head->next = tail;
			tail->prev = head;
			Node *node = (lt.head)->next;
			while (node != lt.tail)
			{
				push_back(node->data);
				node = node->next;
			}
		}

		List(std::initializer_list<T> lt)
		{
			head = tinystl::Allocator<Node>::allocate(1);
			tail = tinystl::Allocator<Node>::allocate(1);
			head->next = tail;
			tail->prev = head;

			Node *pre = head;
			for (auto &cur : lt)
			{
				Node *node = new Node(cur, pre, tail);
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
				Node *node = (lt.head)->next;
				while (node != lt.tail)
				{ // 遍历lt
					push_back(node->data);
					node = node->next;
				}
			}
			return *this;
		}

		class iterator
		{
		public:
			Node *node;

		public:
			iterator(Node *node) : node(node){};
			iterator &operator++()
			{
				node = node->next;
				return *this;
			}
			iterator operator++(int)
			{
				iterator it(*this);
				node = node->next;
				return it;
			}
			iterator &operator--()
			{
				node = node->prev;
				return *this;
			}
			iterator operator--(int)
			{
				iterator it(*this);
				node = node->prev;
				return it;
			}
			bool operator==(const iterator &it) const
			{
				return node == it.node;
			};
			bool operator!=(const iterator &it) const
			{
				return node != it.node;
			}
			T &operator*(void)
			{
				return node->data;
			}
		};

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
			Node *node = head->next;
			head->next->next->prev = head;
			head->next = head->next->next;
			// delete node;
			tinystl::Allocator<Node>::deallocate(node);
		}
		void pop_back()
		{
			if (empty())
			{
				throw NotElementException();
			}
			Node *node = tail->prev;
			tail->prev->prev->next = tail;
			tail->prev = tail->prev->prev;
			// delete node;
			tinystl::Allocator<Node>::deallocate(node);
		}
		// 删除it所指向的节点
		iterator erase(iterator &it)
		{
			if (it == head || it == tail)
			{
				throw InvalidIteratorException();
			}
			Node *next = it.node->next;
			it.node->prev->next = it.node->next;
			it.node->next->prev = it.node->prev;
			// delete it.node;
			tinystl::Allocator<Node>::deallocate(it.node);
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
			Node *node = new Node(data, it.node->prev, it.node);
			it.node->prev->next = node;
			it.node->prev = node;
			it.node = node;
			return it;
		}
	};

	// int main()
	// {
	// 	List<int> l1;
	// 	l1.push_back(1);
	// 	l1.push_back(3);
	// 	l1.push_back(5);
	// 	l1.push_back(7);
	// 	l1.push_back(9);
	// 	l1.push_front(2);
	// 	l1.push_front(4);
	// 	l1.push_front(6);
	// 	l1.push_front(8);
	// 	l1.push_front(10);
	// 	l1.push_front(0);
	// 	List<int>::iterator it = l1.begin();
	// 	for (; it != l1.end(); ++it)
	// 	{
	// 		cout << *it << " ";
	// 	}
	// 	l1.pop_front();
	// 	l1.pop_back();
	// 	print(l1.begin(), l1.end());
	// 	it = l1.begin();
	// 	++it;
	// 	++it;
	// 	++it;
	// 	l1.insert(it, 100);
	// 	print(l1.begin(), l1.end());
	// 	return 0;
	// }

}

#endif