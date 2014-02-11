#ifndef _ITERATOR_HPP_INCLUDED
#define _ITERATOR_HPP_INCLUDED

#include <cstddef>
#include <vector>
#include <iterator>

template<typename Tp>
class iterator
{

public:
  typedef Tp value_type;
  typedef std::size_t size_type;
  typedef value_type* pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  
  iterator() : iterator(nullptr, nullptr) {}

  template<typename ptr>
  iterator(ptr first, ptr last)
    : begin(first), end(last), p(end) {}

  reference operator *() {
    return *p;
  }
  
  const reference operator *() const {
    return *p;
  }

private:

   pointer p;
   pointer begin;
   pointer end;
  
};

#endif
