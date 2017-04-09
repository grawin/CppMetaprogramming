#include <iostream>
#include <gtest/gtest.h>

// Test driver
int main(int argc, char * argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  int status = RUN_ALL_TESTS();

  std::cout << "Press enter to continue...\n";
  std::cin.get();

  return status;
}

