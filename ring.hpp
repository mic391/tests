#ifndef _RING_HPP_INCLUDED
#define _RING_HPP_INCLUDED

#include <cstddef>
#include <vector>
#include <iterator>

template<typename Tp>
class ring
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
  

  ring() : ring(nullptr, nullptr) {} 

  template<typename Iterator>
  ring(Iterator first, Iterator last)
    : begin(first), end(last), youngest(begin), cycle(cycle_type::first) {}

  size_type size() const {
    return (end - begin);
  }

  reference operator[](size_type at) {
    return *(begin + normalize(at));
  }

  const_reference operator[](size_type at) const {
    return *(begin + normalize(at));
  }

  void push_back(const_reference t) {
    *youngest = t;
    if (is_out_of_range(++youngest)) {
      cycle = cycle_type::repeated;
      youngest = begin;
    }
  }

  size_type tellp() const {
    return std::distance(begin, youngest);
  }

  const_reference front() const {
    if (is_first_cycle()) return *begin;
    else return *youngest;
  }
  
  reference back() {return *(--youngest);}
  

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
