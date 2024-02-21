#ifndef LIST_TEST_H
#define LIST_TEST_H

#include <gtest/gtest.h>

#include "../includes/list.h"
#include "../includes/string.h"
#include <string>
#include <list>

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

unsigned int *fillVal(unsigned int val, int size)
{
    unsigned int *a = new unsigned int[size];
    srand((unsigned)time(NULL));
    for (int i = 0; i < size; i++)
    {
        a[i] = rand() % (100 + 1);
    }
    return a;
}

int *fillVal(int val, int size)
{
    int *a = new int[size];
    srand((unsigned)time(NULL));
    for (int i = 0; i < size; i++)
    {
        a[i] = rand() % (100 + 1);
    }

    return a;
}

char *fillVal(char val, int size)
{
    // 随机生成string

    char *a = new char[size];
    srand((unsigned)time(NULL));
    for (int i = 0; i < size; i++)
    {
        a[i] = rand() % (100 + 1);
    }

    return a;
}

const char **fillVal(const char *val, int size)
{
    // 随机生成string
    const char **a = new const char *[size];
    srand((unsigned)time(NULL));
    for (int i = 0; i < size; i++)
    {
        a[i] = std::to_string(rand() % (100 + 1)).c_str();
    }

    return a;
}

TYPED_TEST_CASE_P(ListTest);

// 测试所有的声明
template <typename T>
void testDeclareWithInit(T *a, int size)
{
    typename tinystl::List<T>::iterator it_tmp; // 声明一个迭代器
    tinystl::List<T> l1(a, a + size);
    ASSERT_EQ(l1.size(), size);
    int i = 0;
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

    // test for initialist
    // stl::initializer_list<T> l5(size);
    // for (int i = 0;i < size;i++) {
    //     // l5.push_back(a[i]);
    //     l5[i] = a[i];
    // }
    // i = 0;
    // ASSERT_EQ(l5.size(), 5);
    // for (it_tmp = l5.begin(); it_tmp != l5.end(); it_tmp++)
    // {
    //     ASSERT_EQ(*it_tmp, a[i++]);
    // }

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
    int i = 0;
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

TYPED_TEST_P(ListTest, CONSTRUCTOR)
{

    TypeParam n = 0;

    this->fillVal(n, 5);
    TypeParam *tmp = this->value_;
    testDeclareWithInit<TypeParam>(tmp, 5);
    testDeclareWithNoInit<TypeParam>(5);
    testAssign<TypeParam>(tmp, 5);
    delete[] tmp;
}

REGISTER_TYPED_TEST_CASE_P(ListTest, CONSTRUCTOR);

typedef testing::Types<char, int, unsigned int, const char *> ListTypes;

INSTANTIATE_TYPED_TEST_CASE_P(tinystl, ListTest, ListTypes);

// 测试自定义string类型
TEST(ListTests, TestLIST_MYSTRING)
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
TEST(ListTests, TestLIST_INILIALIZE_LIST)
{
    tinystl::List<int> l1{1, 2, 3, 4, 5, 6, 7, 8, 9};
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
    l3 = l2;
    i = 0;
    for (it_tmp_3 = l5.begin(); it_tmp_3 != l5.end(); it_tmp_3++)
    {
        ASSERT_EQ(*it_tmp_3, std::to_string(i + 1).c_str());
        i++;
    }
}

// 明天给list测试一些常见方法

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#endif
