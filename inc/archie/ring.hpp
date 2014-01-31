#ifndef _ARCHIE_RING_HPP_
#define _ARCHIE_RING_HPP_

#include <memory>
#include <iterator>
#include <algorithm>
#include <boost/range/iterator_range.hpp>

namespace archie {
namespace detail {

template<typename ValueType, typename Pointer = ValueType*,
  typename ConstPointer = const ValueType*,
  typename Reference = ValueType&,
  typename ConstReference = const ValueType&,
  typename SizeType = std::size_t,
  typename DifferenceType = std::size_t>
class circular {
public:
  typedef ValueType value_type;
  typedef Pointer pointer;
  typedef ConstPointer const_pointer;
  typedef Reference reference;
  typedef ConstReference const_reference;
  typedef SizeType size_type;
  typedef DifferenceType difference_type;

  enum cycle_type {
    primal, repeated
  };

  template<typename Iterator>
  circular(const Iterator b, const Iterator e,
    difference_type o)
    : range(b, e), offset(o), cycle(primal) {
  }

  template<typename Iterator>
  circular(const Iterator b, const Iterator e)
    : circular(b, e, 0) {
  }

  template<typename Iterator>
  circular(const Iterator b, size_type s)
    : circular(b, b + s, 0) {
  }

  circular()
    : circular(nullptr, nullptr) {
  }

  size_type capacity() const {
    return range.size();
  }

  bool is_out_of_range(difference_type at) const {
    return at < 0 || at >= capacity();
  }

  bool has_same_position(const circular& rhs) const {
    return offset == rhs.offset;
  }

  bool has_same_range(const circular& rhs) const {
    return range == rhs.range;
  }

  bool has_same_cycle(const circular& rhs) const {
    return cycle == rhs.cycle;
  }

  bool is_same_as(const circular& rhs) const {
    return has_same_position(rhs) && has_same_range(rhs)
      && has_same_cycle(rhs);
  }

  bool is_primal() const {
    return cycle == cycle_type::primal;
  }

  void repeate() {
    cycle = cycle_type::repeated;
  }

  void reset() {
    offset = 0;
    repeate();
  }

  void increment() {
    if (is_out_of_range(++offset)) reset();
  }

  pointer position() const {
    pointer ptr = range.begin();
    std::advance(ptr, offset);
    return ptr;
  }

  difference_type tellp() const {
    return std::distance(range.begin(), position());
  }

  difference_type tellg() const {
    return is_primal() ? 0 : tellp();
  }

  const_reference at(difference_type idx) const {
    return range[normalize(idx)];
  }

  reference at(difference_type idx) {
    return range[normalize(idx)];
  }

  difference_type normalize(difference_type idx) const {
    if (is_primal()) return idx % capacity();
    else return (tellp() + idx) % capacity();
  }

  pointer begin() const {
    return range.begin();
  }

  pointer end() const {
    return range.end();
  }

private:
  typedef boost::iterator_range<pointer> range_type;
  range_type range;
  difference_type offset;
  cycle_type cycle;
};

template<typename ValueType, typename Pointer = ValueType*,
  typename ConstPointer = const ValueType*,
  typename Reference = ValueType&,
  typename ConstReference = const ValueType&,
  typename SizeType = std::size_t,
  typename DifferenceType = std::size_t>
class ring_input_iterator: private circular<ValueType,
  Pointer, ConstPointer, Reference, ConstReference,
  SizeType, DifferenceType> {
public:
  typedef circular<ValueType, Pointer, ConstPointer,
    Reference, ConstReference, SizeType, DifferenceType> base;
  typedef typename base::value_type value_type;
  typedef typename base::pointer pointer;
  typedef typename base::const_pointer const_pointer;
  typedef typename base::reference reference;
  typedef typename base::const_reference const_reference;
  typedef typename base::size_type size_type;
  typedef typename base::difference_type difference_type;
  typedef typename base::cycle_type cycle_type;

  ring_input_iterator()
    : base() {
  }

  template<typename Iterator>
  ring_input_iterator(const Iterator begin,
    const Iterator end, difference_type offset)
    : base(begin, end, offset) {
  }

  template<typename Iterator>
  ring_input_iterator(const Iterator begin,
    const Iterator end)
    : base(begin, end) {
  }

  const_pointer operator->() const {
    return base::position();
  }

  const_reference operator*() const {
    return *base::position();
  }

  ring_input_iterator& operator ++() {
    base::increment();
    return *this;
  }

  bool operator ==(const ring_input_iterator& rhs) const {
    return base::is_same_as(rhs);
  }

  bool operator !=(const ring_input_iterator& rhs) const {
    return not base::is_same_as(rhs);
  }
};

}

template<typename Tp, class Alloc = std::allocator<Tp> >
class ring: private detail::circular<
  typename Alloc::value_type, typename Alloc::pointer,
  typename Alloc::const_pointer, typename Alloc::reference,
  typename Alloc::const_reference,
  typename Alloc::size_type, typename Alloc::difference_type>,
  private Alloc {
public:
  typedef Alloc allocator_type;

  typedef detail::circular<
    typename allocator_type::value_type,
    typename allocator_type::pointer,
    typename allocator_type::const_pointer,
    typename allocator_type::reference,
    typename allocator_type::const_reference,
    typename allocator_type::size_type,
    typename allocator_type::difference_type> base;

  typedef typename base::value_type value_type;
  typedef typename base::pointer pointer;
  typedef typename base::const_pointer const_pointer;
  typedef typename base::reference reference;
  typedef typename base::const_reference const_reference;
  typedef typename base::size_type size_type;
  typedef typename base::difference_type difference_type;
  typedef detail::ring_input_iterator<value_type, pointer,
    const_pointer, reference, const_reference, size_type,
    difference_type> iterator;

public:
  ring()
    : base() {
  }

  ring(const ring& other)
    : ring(other.size()) {
    std::copy(other.base::begin(), other.base::end(),
      base::begin());
    base::repeate();
  }

  explicit ring(size_type size)
    : base(allocator_type::allocate(size), size) {
  }

  template<typename Iterator>
  ring(Iterator first, Iterator last)
    : ring(last - first) {
    std::copy(first, last, base::begin());
    base::repeate();
  }

  ~ring() {
    allocator_type::deallocate(base::begin(),
      base::capacity());
  }

  void push_back(const_reference value) {
    *base::position() = value;
    base::increment();
  }

  const_reference operator[](difference_type idx) const {
    return base::at(idx);
  }

  using base::capacity;
  using base::tellp;
  using base::tellg;

  size_type size() const {
    return
      base::is_primal() ? base::tellp() : base::capacity();
  }

  bool empty() const {
    return size() == 0;
  }

  const_reference front() const {
    return base::at(0);
  }

  reference front() {
    return base::at(0);
  }

  const_reference back() const {
    return base::at(size() - 1);
  }

  reference back() {
    return base::at(size() - 1);
  }

  iterator begin() const {
    return iterator(base::begin(), base::end(),
      base::tellg());
  }

  iterator end() const {
    return iterator(base::begin(), base::end(),
      base::tellp());
  }
};

}

#endif /* _ARCHIE_RING_HPP_ */
