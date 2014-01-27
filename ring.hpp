#ifndef _RING_HPP_INCLUDED
#define _RING_HPP_INCLUDED

#include <cstddef>

template<typename Tp>
class ring
{
Tp *end,*begin;
int *Tab;
public:
   typedef std::size_t size_type;
  ring(){}
  template<typename Iterator>
  ring(Iterator first, Iterator last) : begin(first), end(last){}
  size_type size() const {
    return (end - begin);
  }
  Tp & operator[](size_t el) {return Tab[el];};
  const Tp & operator[](size_t el) const {return Tab[el];};
};

#endif
