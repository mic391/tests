#ifndef _ARCHIE_RING_HPP_
#define _ARCHIE_RING_HPP_

#include <memory>
#include <iterator>
#include <algorithm>
#include <boost/range/iterator_range.hpp>

namespace archie {
namespace detail {

template<typename Tp, typename ValueType = Tp,
  typename Pointer = Tp*, typename ConstPointer = const Tp*,
  typename Reference = Tp&,
  typename ConstReference = const Tp&,
  typename SizeType = std::size_t,
  typename DifferenceType = std::size_t>
class ring_input_iterator {
public:
  enum cycle_type {
    primal, repeated
  };
  typedef ValueType value_type;
  typedef Pointer pointer;
  typedef ConstPointer const_pointer;
  typedef Reference reference;
  typedef ConstReference const_reference;
  typedef SizeType size_type;
  typedef DifferenceType difference_type;

  ring_input_iterator()
    : ring_input_iterator(nullptr, nullptr) {
  }

  template<typename Iterator>
  ring_input_iterator(const Iterator begin,
    const Iterator end, difference_type off, cycle_type c)
    : range(begin, end), offset(off), cycle(c) {
  }

  template<typename Iterator>
  ring_input_iterator(const Iterator begin,
    const Iterator end)
    : ring_input_iterator(begin, end, 0, cycle_type::primal) {
  }

  const_pointer operator->() const {
    return position();
  }

  const_reference operator*() const {
    return *position();
  }

  ring_input_iterator& operator ++() {
    if (is_out_of_range(++offset)) reset();
    return *this;
  }

  bool operator ==(const ring_input_iterator& rhs) const {
    return is_same_as(rhs);
  }

  bool operator !=(const ring_input_iterator& rhs) const {
    return not is_same_as(rhs);
  }

private:
  typedef boost::iterator_range<pointer> range_type;

  void repeate() {
    cycle = cycle_type::repeated;
  }

  void reset() {
    offset = 0;
    repeate();
  }

  bool is_out_of_range(difference_type dist) const {
    return dist < 0 || dist >= range.size();
  }

  bool has_same_position(
    const ring_input_iterator& rhs) const {
    return offset == rhs.offset;
  }

  bool has_same_range(
    const ring_input_iterator& rhs) const {
    return range == rhs.range;
  }

  bool has_same_cycle(
    const ring_input_iterator& rhs) const {
    return cycle == rhs.cycle;
  }

  bool is_same_as(const ring_input_iterator& rhs) const {
    return has_same_position(rhs) && has_same_range(rhs)
      && has_same_cycle(rhs);
  }

  pointer position() const {
    pointer ptr = range.begin();
    std::advance(ptr, offset);
    return ptr;
  }

  range_type range;
  difference_type offset;
  cycle_type cycle;
};

}
template<typename Tp, class Alloc = std::allocator<Tp> >
class ring: private Alloc {
public:
  typedef Alloc allocator_type;
  typedef typename allocator_type::value_type value_type;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::size_type size_type;
  typedef typename allocator_type::difference_type difference_type;
  typedef boost::iterator_range<pointer> range_type;
  typedef detail::ring_input_iterator<value_type,
    value_type, pointer, const_pointer, reference,
    const_reference, size_type, difference_type> iterator;
  typedef typename iterator::cycle_type cycle_type;
private:

  class range_adapter {
  public:
    range_adapter(pointer p, size_type s)
      : ptr(p), size(s) {
    }
    range_type get_range() const {
      return range_type(ptr, ptr + size);
    }
  private:
    pointer ptr;
    size_type size;
  };

public:
  ring()
    : ring(0) {
  }

  ring(const ring& other)
    : ring(other.size()) {
    std::copy(other.range.begin(), other.range.end(),
      range.begin());
    cycle = cycle_type::repeated;
  }

  explicit ring(size_type size)
    : range(
      range_adapter(allocator_type::allocate(size), size).get_range()), offset(
      0), cycle(cycle_type::primal) {
  }

  template<typename Iterator>
  ring(Iterator first, Iterator last)
    : ring(last - first) {
    std::copy(first, last, range.begin());
    cycle = cycle_type::repeated;
  }

  ~ring() {
    allocator_type::deallocate(range.begin(), range.size());
  }

  void push_back(const_reference value) {
    *position() = value;
    if (is_out_of_range(++offset)) {
      offset = 0;
      cycle = cycle_type::repeated;
    }
  }

  const_reference operator[](difference_type idx) const {
    return at(idx);
  }

  size_type capacity() const {
    return range.size();
  }

  bool empty() const {
    return size() == 0;
  }

  size_type size() const {
    return is_primal() ? tellp() : capacity();
  }

  difference_type tellp() const {
    return std::distance(range.begin(), position());
  }

  difference_type tellg() const {
    return is_primal() ? 0 : tellp();
  }

  const_reference front() const {
    return at(0);
  }

  reference front() {
    return at(0);
  }

  const_reference back() const {
    return at(size() - 1);
  }

  reference back() {
    return at(size() - 1);
  }

  iterator begin() const {
    return iterator(range.begin(), range.end(), tellg(),
      cycle_type::primal);
  }

  iterator end() const {
    return iterator(range.begin(), range.end(), tellp(),
      cycle_type::primal);
  }

private:
  const_reference at(difference_type idx) const {
    return range[normalize(idx)];
  }

  reference at(difference_type idx) {
    return range[normalize(idx)];
  }

  bool is_primal() const {
    return cycle == cycle_type::primal;
  }

  bool is_out_of_range(difference_type diff) const {
    return diff < 0 || diff >= range.size();
  }

  difference_type normalize(difference_type idx) const {
    if (is_primal()) return idx % capacity();
    else return (tellp() + idx) % capacity();
  }

  pointer position() const {
    pointer ptr = range.begin();
    std::advance(ptr, offset);
    return ptr;
  }

  const range_type range;
  difference_type offset;
  cycle_type cycle;
};

}

#endif /* _ARCHIE_RING_HPP_ */
