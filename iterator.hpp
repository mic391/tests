#ifndef _RING_HPP_INCLUDED
#define _RING_HPP_INCLUDED

#include <cstddef>
#include <vector>
#include <iterator>

template<typename Tp>
class iterator
{
  enum cycle_type {
    first, repeated
  };

public:
  typedef Tp value_type;
  typedef std::size_t size_type;
  typedef value_type* pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  

}

  reference operator[](size_type at) {
    return *(begin + normalize(at));
  }

  const_reference operator[](size_type at) const {
    return *(begin + normalize(at));
  }


  

private:

  bool is_first_cycle() const {
    return cycle == cycle_type::first;
  }

  bool is_out_of_range(pointer ptr) const {
    return ptr < begin || ptr >= end;
  }

  size_type normalize(size_type at) const {
    return (tellp() + at) % size();
  }

  pointer begin;
  pointer end;
  pointer youngest;
  cycle_type cycle;
};

#endif
