#ifndef _RING_HPP_INCLUDED
#define _RING_HPP_INCLUDED

#include <cstddef>

template<typename Tp>
class ring
{
public:
  typedef std::size_t size_type;
  ring(){}
  template<typename Iterator>
  ring(Iterator first, Iterator last) {}
  size_type size() const {
    return 20;
  }
};

#endif
