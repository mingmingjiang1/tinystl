#ifndef LIST_TEST_H
#define LIST_TEST_H


#include <list>
#include <gtest/gtest.h>

#include "./includes/list.h"


TEST(MultiplyTests, TestIntegerOne_One)
{
    const auto expected = 1;
    const auto actual = multiply(1, 1);
    ASSERT_EQ(expected, actual);
}

TEST(MultiplyTests, TestIntegerZero_Zero)
{
    const auto expected = 0;
    const auto actual = multiply(0, 0);
    ASSERT_EQ(expected, actual);
}

TEST(MultiplyTests, TestIntegerZero_One)
{
    const auto expected = 0;
    const auto actual = multiply(0, 1);
    ASSERT_EQ(actual, expected);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


// namespace list_test
// {
//   bool is_odd(int x) { return x & 1; }

//   void list_test()
//   {
//     std::cout << "[===============================================================]" << std::endl;
//     std::cout << "[------------------ Run container test : list ------------------]" << std::endl;
//     std::cout << "[-------------------------- API test ---------------------------]" << std::endl;
//     int a[] = { 1,2,3,4,5 };
//     List<int> l1;
//     // List<int> l2(5);
//     // List<int> l3(5, 1);
//     // List<int> l4(a, a + 5);
//     List<int> l5(l2);
//     List<int> l6(std::move(l2));
//     // List<int> l7 { 1,2,3,4,5,6,7,8,9 };
//     List<int> l8;
//     l8 = l3;
//     List<int> l9;
//     l9 = std::move(l3);
//     List<int> l10;
//     // l10 = { 1, 2, 2, 3, 5, 6, 7, 8, 9 };
//   }

// }
#endif // !MYTINYSTL_LIST_TEST_H_
