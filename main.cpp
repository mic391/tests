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

void canpuseoperator()
{
  std::array<int, 5> pool;
  ring<int> buff(pool.begin(), pool.end());
  (void)buff;
  pool[0]=2;
  pool[0]=buff[0];
  pool[1]=5;
  pool[1]=buff[1];
  assert_equal(pool[0], buff[0]);
}


int main()
{
  canCreateRingBuffer();
  canCreateRingOnPool();
  canCreateAnotherRingOnPool();
  canpuseoperator();
  std::cout << "Test Passed" << std::endl;
  return 0;
}
