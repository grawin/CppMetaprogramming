#include "ObjectParser.h"
#include <boost/fusion/include/adapt_struct.hpp>
#include <iostream>

// Test data

struct B
{
  int x;
  int y;
  std::string str;
};

BOOST_FUSION_ADAPT_STRUCT
(
  B,
  (int, x)
  (int, y)
  (std::string, str)
)

struct A
{
  int i;
  typedef char char10[10];
  char10 arr;
  B myB;
};

BOOST_FUSION_ADAPT_STRUCT
(
  A,
  (int, i)
  (A::char10, arr)
  (B, myB)
)

// End test data

// Test driver
int main(int argc, char * argv[])
{
  A testObj = { 0x1000000, "test", { 0x2000000, 0x3000000, "test2" } };

  Parser::ObjectParser<A>::parse(testObj);

  std::cout << testObj.i << "\n";
  for (int i = 0; i < 4; ++i)
  {
    std::cout << testObj.arr[i];
  }
  std::cout << "\n";
  std::cout << testObj.myB.x << "\n";
  std::cout << testObj.myB.y << "\n";
  std::cout << testObj.myB.str << "\n";

  std::cout << "Press enter to continue...\n";
  std::cin.get();
  return 0;
}

