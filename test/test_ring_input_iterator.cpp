#include <gtest/gtest.h>
#include "archie/ring.hpp"

class test_ring_input_iterator: public testing::Test {
protected:
  typedef archie::detail::ring_input_iterator<int> iterator;
  typedef archie::ring<int> ring;
  void SetUp() {
  }
};
template <class Type>
class MultValue
{
private:
Type Factor;
public:
MultValue(const Type& _Val) : Factor(_Val) {}
void operator()(Type& elem) const
{ elem *= Factor; }
};


TEST_F(test_ring_input_iterator, canCreateIterator) {
  iterator it;
}

TEST_F(test_ring_input_iterator, canCreateIteratorOnRange) {
  ring buff(5);
  iterator it(&buff.front(), &buff.back() + 1);
}

TEST_F(test_ring_input_iterator, canDereferenceIterator) {
  ring buff(5);
  iterator it(&buff.front(), &buff.back() + 1);
  buff.push_back(33);
  EXPECT_EQ(33, *it);
}

TEST_F(test_ring_input_iterator, canIncrementIteratorMany) {
  ring buff(5);
  iterator it(&buff.front(), &buff.front() + buff.capacity());
  buff.push_back(33);
  buff.push_back(44);
  buff.push_back(55);
  buff.push_back(66);
  buff.push_back(77);
  EXPECT_EQ(33, *it);
  ++it;
  EXPECT_EQ(44, *it);
  ++it;
  EXPECT_EQ(55, *it);
  ++it;
  EXPECT_EQ(66, *it);
  ++it;
  EXPECT_EQ(77, *it);
  ++it;
  EXPECT_EQ(33, *it);
}

TEST_F(test_ring_input_iterator, canEqualityCompareIterators) {
  iterator it1, it2;
  EXPECT_EQ(it1, it2);
  ring buff(5);
  iterator it3(&buff.front(), &buff.front() + buff.capacity());
  iterator it4(&buff.front(), &buff.front() + buff.capacity());
  EXPECT_NE(it1, it3);
  EXPECT_EQ(it3, it4);
  ++it3;
  EXPECT_NE(it3, it4);
  ++it3;
  ++it3;
  ++it3;
  ++it3;
  EXPECT_NE(it3, it4);
}

TEST_F(test_ring_input_iterator, isCopyConstructable) {
  ring buff(5);
  buff.push_back(11);
  iterator it1(&buff.front(), &buff.front() + buff.capacity());
  iterator it2(it1);
  EXPECT_EQ(11, *it2);
}

TEST_F(test_ring_input_iterator, isAssignable) {
  ring buff(5);
  buff.push_back(11);
  iterator it1(&buff.front(), &buff.front() + buff.capacity());
  iterator it2;
  it2 = it1;
  EXPECT_EQ(11, *it2);
}

TEST_F(test_ring_input_iterator, canUseForEach) {
  ring buff(3);
  buff.push_back(11);
  buff.push_back(22);
  iterator it(&buff.front(), &buff.front() + buff.capacity());
  std::for_each(buff.begin(),buff.end(), [](int& i) { i*=2; });
  EXPECT_EQ(22, *it);
 // EXPECT_EQ(22, *(std::prev(it, 1)));    doesn't work - for next test
  ++it;
  EXPECT_EQ(44, *it);
}





