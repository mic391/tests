#ifndef _RING_HPP_INCLUDED
#define _RING_HPP_INCLUDED

#include <cstddef>
#include <vector>

template<typename Tp>
class ring
{
public:
  typedef Tp value_type;
  typedef std::size_t size_type;
  typedef value_type* pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  

  ring() : begin(nullptr), end(nullptr), index(begin) {} 
  template<typename Iterator>
  ring(Iterator first, Iterator last) : begin(first), end(last), index(begin){}
	
  size_type size() const {
    return (end - begin);
  }
  reference operator[](size_type at) {
    return *(begin + at);
  }
  const_reference operator[](size_type at) const {
    return *(begin + at);
  }
  void push_back(const_reference t) {
		*begin=t;
		*index++;
  }



  
  
private:
  pointer begin;
  pointer end;
  pointer index;
};

#endif
