#ifndef TINYSTL_FORWARD_LIST_H
#define TINYSTL_FORWARD_LIST_H

#include "adapter.h"
#include "allocator/allocator_copy.h"
#include "iterator/iterator.h"

namespace tinystl
{
    template <typename T, typename Alloc = allocator<T>>
    class forward_list
    {
    public:
        typedef typename node_traits<T>::base_ptr base_ptr;
        typedef typename node_traits<T>::node_ptr node_ptr;

		typedef Allocator<list_node_base<T>> base_allocator;
		typedef Allocator<list_node<T>> node_allocator;
		typedef Alloc data_allocator;

        /** constructor */
		typedef tinystl::Construct<T> constructor;

        typedef typename data_allocator::value_type value_type;
        typedef typename data_allocator::size_type size_type;

        typedef Forward_Access_Iterator<T, forward_list> iterator;

    public:
        forward_list();
        forward_list(size_type size, const T& val);
        forward_list(size_type size);
        forward_list(const forward_list& other);
        forward_list(forward_list&& other);
        forward_list(iterator first, iterator last);
        forward_list(T* first, T* last);
        forward_list(std::initializer_list<T> il);
        forward_list& operator=(const forward_list& other);
        forward_list& operator=(forward_list&& other);
        size_type size() const;
        void push_front(const T& data);
        void push_back(const T& data);
        void push_back(T &&val);
        void pop_front();
        void pop_back();
        void clear();
        bool empty() const;
        // iterator erase(iterator pos); // todo
        void remove(const T& val); // todo
        void swap(forward_list& other); // todo
        iterator begin();
        iterator end();
        iterator cbegin() const; // todo
        iterator cend() const; // todo
        ~forward_list();

    private:
		base_ptr head;
		base_ptr tail;
        size_type m_size;
    };
}

#include "forward_list.tcc"

#endif // TINYSTL_