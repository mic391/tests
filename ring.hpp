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
  

  ring() : begin(nullptr), end(nullptr), last_el(begin) {} 
  template<typename Iterator>
  ring(Iterator first, Iterator last) : begin(first), end(last), last_el(begin){}
	
  size_type size() const {
    return (end - begin);
  }
  reference operator[](size_type at) {
	  if (pushbackcycle==false)
    {return *(begin + at);}
    else {return *(last_el + at);}
  }
  const_reference operator[](size_type at) const {
    if (pushbackcycle==false)
    {return *(begin + at);}
    else {return *(last_el + at);}
  }
  void push_back(const_reference t) {
    *last_el = t;
    if (++last_el >= end) {pushbackcycle=true;}
    else {pushbackcycle=false;}
  }
  
  reference front() {
    
    if (pushbackcycle==false)
    {return *(begin);}
    else {return *(last_el);} 
  }


private:
  pointer begin;
  pointer end;
  pointer last_el;
  bool pushbackcycle;
};

#endif
