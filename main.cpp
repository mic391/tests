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



int main()
{
  canCreateRingBuffer();
  canCreateRingOnPool();
  canCreateAnotherRingOnPool();
  std::cout << "Test Passed" << std::endl;
  return 0;
}
