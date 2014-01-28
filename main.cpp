#include <iostream>
#include "ring.hpp"
#include <cassert>
#include <array>

template<typename Tp, typename Vp>
void assert_equal(const Tp& t, const Vp& v)
{
  assert(t == v);
} 

void canCreateRingBuffer()
{
  ring<int> buff;
  (void)buff;
}

void canCreateRingOnPool()
{
  std::array<int, 20> pool;
  ring<int> buff(pool.begin(), pool.end());
  (void)buff;
  assert_equal(buff.size(), pool.size());
}

void canCreateAnotherRingOnPool()
{
  std::array<int, 5> pool;
  ring<int> buff(pool.begin(), pool.end());
  (void)buff;
  assert_equal(buff.size(), pool.size());
}

void canUseOperator()
{
  std::array<int, 5> pool{11, 22, 33, 44, 55};
  ring<int> buff(pool.begin(), pool.end());
  assert_equal(pool[0], buff[0]);
  assert_equal(pool[1], buff[1]);
}

void canUsePushBackFunc()
{
  std::array<int, 5> pool;
  ring<int> buff(pool.begin(), pool.end());
  buff.push_back(11);
  assert_equal(buff[0], 11);

}


void canUseAnotherPushBackFunc()
{
  std::array<int, 5> pool;
  ring<int> buff2(pool.begin(), pool.end());
  buff2.push_back(11);
  buff2.push_back(22);
  assert_equal(buff2[0], 11);
  assert_equal(buff2[1], 22);
}

int main()
{
  canCreateRingBuffer();
  canCreateRingOnPool();
  canCreateAnotherRingOnPool();
  canUseOperator();
  canUsePushBackFunc();
  canUseAnotherPushBackFunc();
  std::cout << "Test Passed" << std::endl;
  return 0;
}
