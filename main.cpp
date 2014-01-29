#include <iostream>
#include "ring.hpp"
#include <cassert>
#include <array>
#define assert_equal(expected, actual) assert(expected == actual);

/*template<typename Tp, typename Vp>
void assert_equal(const Tp& t, const Vp& v)
{
  assert(t == v);
}*/

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
#define assert_equal(expected, actual) assert(expected == actual);

void canUseAnotherPushBackFunc()
{
  std::array<int, 5> pool;
  ring<int> buff2(pool.begin(), pool.end());
  buff2.push_back(11);
  buff2.push_back(22);
  assert_equal(buff2[0], 11);
  assert_equal(buff2[1], 22);
}


void canOverloadPushBackFunc()
{
  std::array<int, 3> pool;
  ring<int> buff3(pool.begin(), pool.end());
  buff3.push_back(11);
  buff3.push_back(22);
  buff3.push_back(33);
  buff3.push_back(44);
  buff3.push_back(55);
  assert_equal(buff3[0], 33);
  assert_equal(buff3[1], 44);
  assert_equal(buff3[2], 55);
}

void canGetFrontFunc()
{
   std::array<int, 3> pool;
   ring<int> buff4(pool.begin(), pool.end());
   buff4.push_back(11);
   buff4.push_back(22);
   buff4.push_back(33);
   assert_equal(buff4.front(), 11);
}

void canOverloadFrontFunc()
{
  std::array<int, 3> pool;
  ring<int> buff3(pool.begin(), pool.end());
  buff3.push_back(11);
  assert_equal(buff3.front(), 11);
  buff3.push_back(22);
  assert_equal(buff3.front(), 11);
  buff3.push_back(33);
  assert_equal(buff3.front(), 11);
  buff3.push_back(44);
  assert_equal(buff3.front(), 22);
  buff3.push_back(55);
  assert_equal(buff3.front(), 33);
}

void canGetBackFunc()
{
   std::array<int, 3> pool;
   ring<int> buff4(pool.begin(), pool.end());
   buff4.push_back(11);
   buff4.push_back(22);
   assert_equal(buff4.back(), 22);
}

void canOverloadBackFunc()
{
   std::array<int, 3> pool;
  ring<int> buff3(pool.begin(), pool.end());
  buff3.push_back(11);
  assert_equal(buff3.back(), 11);
  buff3.push_back(22);
  assert_equal(buff3.back(), 22);
  buff3.push_back(33);
  assert_equal(buff3.back(), 33);
  buff3.push_back(44);
  assert_equal(buff3.back(), 44);
  buff3.push_back(55);
  assert_equal(buff3.back(), 55);
   
   
}


int main()
{
  canCreateRingBuffer();
  canCreateRingOnPool();
  canCreateAnotherRingOnPool();
  canUseOperator();
  canUsePushBackFunc();
  canUseAnotherPushBackFunc();
  canOverloadPushBackFunc();
  canGetFrontFunc();
  canOverloadFrontFunc();
  canGetBackFunc();
  canOverloadBackFunc();
  std::cout << "Test Passed" << std::endl;
  return 0;
}
