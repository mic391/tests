#include <gtest/gtest.h>
#include "archie/ring.hpp"
#include <memory>
#include <array>
#include <vector>
#include <algorithm>
#include <iostream>

class test_ring: public testing::Test {
protected:
  enum {
    buff_size = 5
  };
  typedef archie::ring<int> ring_type;
  void SetUp() {
    buffptr.reset(new ring_type(buff_size));
  }
  std::unique_ptr<ring_type> buffptr;
  void assertElement(const ring_type& buffer, ring_type::difference_type idx,
      ring_type::value_type value) {
    EXPECT_EQ(value, buffer[idx]);
  }
  template<typename T, typename V>
  void assertEqualContent(const T& t, const V& v) {
    EXPECT_EQ(v.size(), t.size());
    for (typename T::size_type idx = 0; idx < t.size(); ++idx) {
      assertElement(t, idx, v[idx]);
    }
  }
  template<typename T>
  void pushBackMany(ring_type& buff, T t) {
    for (const typename T::value_type& value : t) {
      buff.push_back(value);
    }
  }
};


TEST_F(test_ring, canCreateRingBuffer) {
  archie::ring<int> buffer;
}

TEST_F(test_ring, canCreateRingBufferOfGivenSize) {
  archie::ring<int> buffer(5);
  EXPECT_EQ(buff_size, buffptr->capacity());
}

TEST_F(test_ring, canPushBackNSizeValues) {
  std::array<int, buff_size> array { 11, 22, 33, 44, 55 };
  pushBackMany(*buffptr, array);
  assertEqualContent(*buffptr, array);
}

TEST_F(test_ring, canPushBackMoreNSizeValues) {
  std::array<int, buff_size + 1> input { 11, 22, 33, 44, 55, 66 };
  std::array<int, buff_size> output { 22, 33, 44, 55, 66 };
  pushBackMany(*buffptr, input);
  assertEqualContent(*buffptr, output);
}

TEST_F(test_ring, canCopyFromContainer)
{
  std::array<int, buff_size> array { 22, 33, 44, 55, 66 };
  archie::ring<int> buffer(array.begin(), array.end());
  assertEqualContent(buffer, array);
}

TEST_F(test_ring, canCopyFromOtherRing)
{
  std::array<int, buff_size> array { 22, 33, 44, 55, 66 };
  pushBackMany(*buffptr, array);
  archie::ring<int> buffer(*buffptr);
  assertEqualContent(buffer, *buffptr);
}

TEST_F(test_ring, canTellPosition) {
  EXPECT_EQ(0, buffptr->tellp());
  buffptr->push_back(11);
  EXPECT_EQ(1, buffptr->tellp());
}

TEST_F(test_ring, canGetFrontElement) {
  buffptr->push_back(11);
  EXPECT_EQ(11, buffptr->front());
  std::array<int, buff_size-1> array { 22, 33, 44, 55 };
  pushBackMany(*buffptr, array);
  EXPECT_EQ(11, buffptr->front());
  buffptr->push_back(66);
  EXPECT_EQ(22, buffptr->front());
}

TEST_F(test_ring, canGetBackElement) {
  buffptr->push_back(11);
  EXPECT_EQ(11, buffptr->back());
  buffptr->push_back(22);
  EXPECT_EQ(22, buffptr->back());
  buffptr->push_back(33);
  EXPECT_EQ(33, buffptr->back());
  buffptr->push_back(44);
  EXPECT_EQ(44, buffptr->back());
  buffptr->push_back(55);
  EXPECT_EQ(55, buffptr->back());
  buffptr->push_back(66);
  EXPECT_EQ(66, buffptr->back());
}

TEST_F(test_ring, canCheckIfIsEmpty)
{
  EXPECT_TRUE(buffptr->empty());
  buffptr->push_back(11);
  EXPECT_FALSE(buffptr->empty());
}

TEST_F(test_ring, canGetBegin)
{
  buffptr->push_back(11);
  EXPECT_EQ(*(buffptr->begin()), 11);
}

TEST_F(test_ring, canGetEnd)
{
  buffptr->push_back(11);
  ring_type::iterator it = buffptr->begin();
  EXPECT_NE(it, buffptr->end());
  ++it;
  EXPECT_EQ(it, buffptr->end());
}


