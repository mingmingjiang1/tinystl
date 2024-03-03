
#ifndef ITERATOR_TRAITS
#define ITERATOR_TRAITS

/**
 * @brief Iterator_Traits
 *
 */

#include <cstddef>

namespace tinystl
{
  //    ITERATOR STUFF (from <iterator>)
  // ITERATOR TAGS (from <iterator>)
  struct input_iterator_tag
  { // identifying tag for input iterators
  };

  struct output_iterator_tag
  { // identifying tag for output iterators
  };

  struct forward_iterator_tag
      : input_iterator_tag,
        output_iterator_tag
  { // identifying tag for forward iterators  这些继承关系有有效的IS-A
  };

  struct bidirectional_iterator_tag
      : forward_iterator_tag
  { // identifying tag for bidirectional iterators
  };

  struct random_access_iterator_tag
      : bidirectional_iterator_tag
  { // identifying tag for random-access iterators
  };

  template <typename _Tp>
  struct Iterator_Traits
  {
    typedef typename _Tp::iterator_category iterator_category;
    typedef typename _Tp::value_type value_type;
    typedef typename _Tp::pointer pointer;
    typedef typename _Tp::reference reference;
    typedef typename _Tp::difference_type difference_type;
  };

  template <typename _Tp>
  struct Iterator_Traits<_Tp *>
  {
    typedef random_access_iterator_tag iterator_category;
    typedef _Tp value_type;
    typedef _Tp *pointer;
    typedef _Tp &reference;
    typedef ptrdiff_t difference_type;
  };

  template <typename _Tp>
  struct Iterator_Traits<const _Tp *>
  {
    typedef random_access_iterator_tag iterator_category;
    typedef _Tp value_type;
    typedef const _Tp *pointer;
    typedef const _Tp &reference;
    typedef ptrdiff_t difference_type;
  };

  // 萃取某个迭代器的 distance_type
  template <class Iterator>
  typename Iterator_Traits<Iterator>::difference_type *
  distance_type(const Iterator &)
  {
    return static_cast<typename Iterator_Traits<Iterator>::difference_type *>(0);
  }

  template <class Iterator>
  typename Iterator_Traits<Iterator>::iterator_category
  iterator_category(const Iterator &)
  {
    return typename Iterator_Traits<Iterator>::iterator_category();
  }
}

#endif
