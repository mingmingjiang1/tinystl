#ifndef TINYSTL_LIST_TEST_H
#define TINYSTL_LIST_TEST_H

#include <gtest/gtest.h>

#include "list/list.h"
#include "string/string.h"
#include <string>
#include <list>
#pragma GCC diagnostic ignored "-Wunused-parameter" // disable warning: unused variable 'i' [-Wunused-variable]

template <typename T>
bool compare(const tinystl::List<T> &a, const tinystl::List<T> b)
{
    // 一旦限定是const成员了，成员函数必须是const，不然不保证成员函数会不会修改成员变量
    if (a.size() != b.size())
    {
        return false;
    }

    while (a.begin() != a.end()) {
        if (a.begin() != b.begin()) {
            return false;
        }
    }

    return true;
}

template <typename T>
class ListTest : public testing::Test
{
public:
    T *value_;
    void fillVal(unsigned int val, int size)
    {
        value_ = new unsigned int[size];
        srand((unsigned)time(NULL));
        for (int i = 0; i < size; i++)
        {
            value_[i] = rand() % (100 + 1);
        }
    }

    ~ListTest()
    {
        delete[] value_;
    }

    void fillVal(int val, int size)
    {
        value_ = new int[size];
        srand((unsigned)time(NULL));
        for (int i = 0; i < size; i++)
        {
            value_[i] = rand() % (100 + 1);
        }
    }

    void fillVal(char val, int size)
    {
        // 随机生成string

        value_ = new char[size];
        srand((unsigned)time(NULL));
        for (int i = 0; i < size; i++)
        {
            value_[i] = rand() % (100 + 1);
        }
    }

    void fillVal(const char *val, int size)
    {
        // 随机生成string
        value_ = new const char *[size];
        srand((unsigned)time(NULL));
        for (int i = 0; i < size; i++)
        {
            value_[i] = std::to_string(rand() % (100 + 1)).c_str();
        }
    }
};


TYPED_TEST_SUITE_P(ListTest);

// 测试所有的声明
template <typename T>
void testDeclareWithInit(T *a, int size)
{
    typename tinystl::List<T>::iterator it_tmp; // 声明一个迭代器
    tinystl::List<T> l1(a, a + size);
    ASSERT_EQ(l1.size(), size);
    int i = 0;
    it_tmp = l1.begin();
    // it_tmp++;
    std::cout << *it_tmp << "fkmmmmgtgm========";
    for (it_tmp = l1.begin(); it_tmp != l1.end(); it_tmp++)
    {
        ASSERT_EQ(*it_tmp, a[i++]);
    }

    tinystl::List<T> l3(a, a + 2);
    i = 0;
    ASSERT_EQ(l3.size(), 2);
    for (it_tmp = l3.begin(); it_tmp != l3.end(); it_tmp++)
    {
        ASSERT_EQ(*it_tmp, a[i++]);
    }

    // test for iterator
    tinystl::List<T> l4(l1.begin(), l1.end());

    i = 0;
    ASSERT_EQ(l4.size(), size);
    for (it_tmp = l4.begin(); it_tmp != l4.end(); it_tmp++)
    {
        ASSERT_EQ(*it_tmp, a[i++]);
    }

    tinystl::List<tinystl::String> vec;
    vec.push_back(tinystl::String("Hello"));
    vec.push_back(tinystl::String("World!"));

    // test for l-value
    tinystl::List<T> l6(std::move(l1));
    i = 0;
    ASSERT_EQ(l6.size(), size);
    for (it_tmp = l6.begin(); it_tmp != l6.end(); it_tmp++)
    {
        ASSERT_EQ(*it_tmp, a[i++]);
    }
}

template <typename T>
void testDeclareWithNoInit(int size)
{
    typename tinystl::List<T>::iterator it_tmp; // 声明一个迭代器
    tinystl::List<T> l1(size);
    ASSERT_EQ(l1.size(), size);
    for (it_tmp = l1.begin(); it_tmp != l1.end(); it_tmp++)
    {
        ASSERT_EQ(*it_tmp, static_cast<T>(0));
    }
}

template <typename T>
void testAssign(T *a, int size)
{
    typename tinystl::List<T>::iterator it_tmp; // 声明一个迭代器
    tinystl::List<T> l1(a, a + size);
    tinystl::List<T> l2, l4, l5;
    l2 = l1;
    ASSERT_EQ(l2.size(), size);
    int i = 0;
    for (it_tmp = l2.begin(); it_tmp != l2.end(); it_tmp++)
    {
        ASSERT_EQ(*it_tmp, a[i++]);
    }

    tinystl::List<T> l3(a, a + 2);
    l4 = l3;
    i = 0;
    ASSERT_EQ(l3.size(), 2);
    for (it_tmp = l4.begin(); it_tmp != l4.end(); it_tmp++)
    {
        ASSERT_EQ(*it_tmp, a[i++]);
    }

    // test for iterator
    tinystl::List<T> lt(l1.begin() + 1, l1.end());
    l5 = lt;
    i = 1;
    ASSERT_EQ(l5.size(), 4);
    for (it_tmp = l5.begin(); it_tmp != l5.end(); it_tmp++)
    {
        ASSERT_EQ(*it_tmp, a[i++]);
    }

    // test for l-value
    tinystl::List<T> l6(std::move(l1));
    i = 0;
    ASSERT_EQ(l6.size(), size);
    for (it_tmp = l6.begin(); it_tmp != l6.end(); it_tmp++)
    {
        ASSERT_EQ(*it_tmp, a[i++]);
    }
}

TYPED_TEST_P(ListTest, Constructor)
{

    TypeParam n = 0;

    this->fillVal(n, 5);
    TypeParam *tmp = this->value_;
    testDeclareWithInit<TypeParam>(tmp, 5);
    testDeclareWithNoInit<TypeParam>(5);
    testAssign<TypeParam>(tmp, 5);
}

REGISTER_TYPED_TEST_SUITE_P(ListTest, Constructor);
using ListTypes = ::testing::Types<int, unsigned int, const char *>;

INSTANTIATE_TYPED_TEST_SUITE_P(tinystl, ListTest, ListTypes);

// 测试自定义string类型
TEST(ListTests, Test_List_String)
{
    tinystl::String a[] = {"aa", "bb", "cc", "dd", "ee"};
    tinystl::List<tinystl::String>::iterator it_tmp; // 声明一个迭代器
    tinystl::List<tinystl::String> l1(a, a + 5);
    int i = 0;
    ASSERT_EQ(l1.size(), 5);
    for (it_tmp = l1.begin(); it_tmp != l1.end(); it_tmp++)
    {
        ASSERT_EQ(*it_tmp, a[i++]);
    }
}

// 测试嵌套类型
TEST(ListTests, Test_Lits_Inilialize_List)
{
    tinystl::List<int> l1{1, 2, 3, 4, 5, 6, 7, 8, 9};
    tinystl::List<int>::iterator it = l1.begin();
    tinystl::List<int>::iterator it_tmp; // 声明一个迭代器
    int i = 0;
    for (it_tmp = l1.begin(); it_tmp != l1.end(); it_tmp++)
    {
        ASSERT_EQ(*it_tmp, i + 1);
        i++;
    }

    tinystl::List<std::string> l2{"1", "2", "3"};
    tinystl::List<std::string>::iterator it_tmp_2; // 声明一个迭代器
    i = 0;
    for (it_tmp_2 = l2.begin(); it_tmp_2 != l2.end(); it_tmp_2++)
    {
        ASSERT_EQ(*it_tmp_2, std::to_string(i + 1).c_str());
        i++;
    }

    tinystl::List<std::string> l3;
    l3 = l2;
    i = 0;
    for (it_tmp_2 = l3.begin(); it_tmp_2 != l3.end(); it_tmp_2++)
    {
        ASSERT_EQ(*it_tmp_2, std::to_string(i + 1).c_str());
        i++;
    }

    tinystl::List<tinystl::String> l4{"1", "2", "3"};
    tinystl::List<tinystl::String>::iterator it_tmp_3; // 声明一个迭代器
    i = 0;
    for (it_tmp_3 = l4.begin(); it_tmp_3 != l4.end(); it_tmp_3++)
    {
        ASSERT_EQ(*it_tmp_3, std::to_string(i + 1).c_str());
        i++;
    }

    tinystl::List<tinystl::String> l5;
    l5 = l4;
    i = 0;
    for (it_tmp_3 = l5.begin(); it_tmp_3 != l5.end(); it_tmp_3++)
    {
        ASSERT_EQ(*it_tmp_3, std::to_string(i + 1).c_str());
        i++;
    }
}

TEST(ForwardListTests, Test_ForwardList_Member_Function)
{
    tinystl::List<int> l1{1, 2, 3, 4, 5, 6, 7, 8, 9};
    ASSERT_EQ(l1.size(), 9);
    // push_back
    l1.push_back(10);
    // size
    ASSERT_EQ(l1.size(), 10);
    compare(l1, tinystl::List<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});

    // pop_back
    l1.pop_back();
    // size
    ASSERT_EQ(l1.size(), 9);
    compare(l1, tinystl::List<int>{1, 2, 3, 4, 5, 6, 7, 8, 9});

    // insert
    l1.insert(l1.begin(), 1000);

    compare(l1, tinystl::List<int>{1000, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    ASSERT_EQ(l1.size(), 10);

    // erase
    l1.erase(l1.begin() + 1);

    compare(l1, tinystl::List<int>{1000, 2, 3, 4, 5, 6, 7, 8, 9});
    // size
    ASSERT_EQ(l1.size(), 9);

    // clear
    l1.clear();

    // empty
    ASSERT_EQ(l1.empty(), true);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#endif
