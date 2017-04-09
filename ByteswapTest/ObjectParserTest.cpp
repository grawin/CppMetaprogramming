#include <string>
#include <boost/fusion/include/adapt_struct.hpp>
#include <gtest/gtest.h>
#include "ObjectParser.h"

// Test type definitions

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

// End test type definitions

// Start Test fixtures

class ByteswapTestFixture : public testing::Test
{
public:

  // Test object to persist between tests.
  A testObj;

  // Initializes test object.
  ByteswapTestFixture()
  {
    testObj = { 0x1000000, "test",{ 0x2000000, 0x3000000, "test2" } };
  }

  // Called before each test.
  void SetUp()
  {
    Parser::ObjectParser<A>::parse(testObj);
  }

  // Called after each test.
  void TearDown()
  {

  }

  ~ByteswapTestFixture()
  {

  }
};

// End test fixtures

// Start test cases

TEST_F(ByteswapTestFixture, EndToEndTest)
{
  ASSERT_EQ(testObj.i, 1);

  A::char10 expected = "test";
  ASSERT_EQ(0, std::memcmp(&testObj.arr[0], expected, sizeof(expected)));

  ASSERT_EQ(testObj.myB.x, 2);
  ASSERT_EQ(testObj.myB.y, 3);
  ASSERT_EQ(testObj.myB.str, "test2");
}

// End test cases

