#ifndef TINYSTL_ALGORITHM_TEST_H
#define TINYSTL_ALGORITHM_TEST_H

#include <gtest/gtest.h>

#include "array/array.h"
#include "string/string.h"
#include "algorithm.h"
#include "vector/vector.h"
#include "iterator/iterator.h"
#include <string>

template <typename T>
class AlgorithmTest : public testing::Test
{
public:
    T *value_;
    void fillVal(unsigned int, int size)
    {
        value_ = new unsigned int[size];
        srand((unsigned)time(NULL));
        for (int i = 0; i < size; i++)
        {
            value_[i] = rand() % (100 + 1);
        }
    }

    ~AlgorithmTest()
    {
        delete[] value_;
    }

    void fillVal(int, int size)
    {
        value_ = new int[size];
        srand((unsigned)time(NULL));
        for (int i = 0; i < size; i++)
        {
            value_[i] = rand() % (100 + 1);
        }
    }

    void fillVal(char, int size)
    {
        // 随机生成string

        value_ = new char[size];
        srand((unsigned)time(NULL));
        for (int i = 0; i < size; i++)
        {
            value_[i] = rand() % (100 + 1);
        }
    }

    void fillVal(const char *, int size)
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

TYPED_TEST_CASE_P(AlgorithmTest);

// 测试所有的声明
template <typename T>
void testDeclareWithInit(T *a, int size)
{
    typename tinystl::Array<T, 5>::iterator it_tmp; // 声明一个迭代器
    tinystl::Array<T, 5> l1(a, a + size);
    std::cout << l1.size() << std::endl;
    ASSERT_EQ(l1.size(), size);
    int i = 0;
    for (it_tmp = l1.begin(); it_tmp != l1.end(); it_tmp++)
    {
        ASSERT_EQ(*it_tmp, a[i++]);
    }

    tinystl::Array<T, 2> l3(a, a + 2);
    i = 0;
    ASSERT_EQ(l3.size(), 2);
    for (it_tmp = l3.begin(); it_tmp != l3.end(); it_tmp++)
    {
        ASSERT_EQ(*it_tmp, a[i++]);
    }

    // test for iterator
    tinystl::Array<T, 5> l4(l1.begin(), l1.end());
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
    tinystl::Array<T, 5> l6(std::move(l1));
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
    typename tinystl::Array<T, 5>::iterator it_tmp; // 声明一个迭代器
    tinystl::Array<T, 5> l1(size);
    ASSERT_EQ(l1.size(), size);
    for (it_tmp = l1.begin(); it_tmp != l1.end(); it_tmp++)
    {
        ASSERT_EQ(*it_tmp, static_cast<T>(0));
    }
}

template <typename T>
void testAssign(T *a, int size)
{
    typename tinystl::Array<T, 5>::iterator it_tmp; // 声明一个迭代器
    tinystl::Array<T, 5> l1(a, a + size);
    tinystl::Array<T, 5> l2, l4, l5;
    l2 = l1;
    ASSERT_EQ(l2.size(), size);
    int i = 0;
    for (it_tmp = l2.begin(); it_tmp != l2.end(); it_tmp++)
    {
        ASSERT_EQ(*it_tmp, a[i++]);
    }

    tinystl::Array<T, 5> l3(a, a + 2);
    l4 = l3;
    i = 0;
    ASSERT_EQ(l3.size(), 2);
    for (it_tmp = l4.begin(); it_tmp != l4.end(); it_tmp++)
    {
        ASSERT_EQ(*it_tmp, a[i++]);
    }

    // test for iterator
    tinystl::Array<T, 5> lt(l1.begin() + 1, l1.end());
    l5 = lt;
    i = 1;
    ASSERT_EQ(l5.size(), 4);
    for (it_tmp = l5.begin(); it_tmp != l5.end(); it_tmp++)
    {
        ASSERT_EQ(*it_tmp, a[i++]);
    }

    // test for l-value
    tinystl::Array<T, 5> l6(std::move(l1));
    i = 0;
    ASSERT_EQ(l6.size(), size);
    for (it_tmp = l6.begin(); it_tmp != l6.end(); it_tmp++)
    {
        ASSERT_EQ(*it_tmp, a[i++]);
    }
}

TYPED_TEST_P(AlgorithmTest, Contructor)
{

    TypeParam n = 0;

    this->fillVal(n, 5);
    TypeParam *tmp = this->value_;
    testDeclareWithInit<TypeParam>(tmp, 5);
    testDeclareWithNoInit<TypeParam>(5);
    testAssign<TypeParam>(tmp, 5);
}

REGISTER_TYPED_TEST_CASE_P(AlgorithmTest, Contructor);

typedef testing::Types<char, int, unsigned int, const char *> AlgorithmTypes;

INSTANTIATE_TYPED_TEST_CASE_P(tinystl, AlgorithmTest, AlgorithmTypes);

// 测试自定义string类型
TEST(AlgorithmTests, Test_Algorithm_String)
{
    tinystl::String a[] = {"aa", "bb", "cc", "dd", "ee"};
    tinystl::Array<tinystl::String, 5> l1(a, a + 5);
    tinystl::Array<tinystl::String, 5>::iterator it_tmp1 = l1.begin();
    tinystl::advance(it_tmp1, 2);
    ASSERT_EQ("cc", *it_tmp1);

    tinystl::Vector<tinystl::String> l2(a, a + 5);
    tinystl::Vector<tinystl::String>::iterator it_tmp2 = l2.begin();
    tinystl::advance(it_tmp2, 2);
    tinystl::advance(it_tmp2, -1);
    ASSERT_EQ("bb", *it_tmp2);
    std::cout << *it_tmp2 << "#####" << std::endl;

    tinystl::advance(it_tmp2, 5);
    std::cout << *it_tmp2 << "#####======";

    tinystl::Vector<int> l3{1, 2, 3};
    tinystl::Vector<int>::iterator it_tmp4 = l3.begin();
    tinystl::advance(it_tmp4, 100);

    std::cout << *it_tmp4 << "#####======";

    // Output_Iterator<int, tinystl::Vector<int>> it1 = l3.begin();
    // Output_Iterator<int, tinystl::Vector<int>> x;
    // x = *it1;
}

// 测试嵌套类型
TEST(AlgorithmTests, Algorithm_Initialize_List)
{
    tinystl::Array<int, 9> l1{1, 2, 3, 4, 5, 6, 7, 8, 9};
    tinystl::Array<int, 9>::iterator it_tmp; // 声明一个迭代器
    int i = 0;
    for (it_tmp = l1.begin(); it_tmp != l1.end(); it_tmp++)
    {
        ASSERT_EQ(*it_tmp, i + 1);
        i++;
    }

    tinystl::Array<std::string, 3> l2{"1", "2", "3"};
    tinystl::Array<std::string, 3>::iterator it_tmp_2; // 声明一个迭代器
    i = 0;
    for (it_tmp_2 = l2.begin(); it_tmp_2 != l2.end(); it_tmp_2++)
    {
        ASSERT_EQ(*it_tmp_2, std::to_string(i + 1).c_str());
        i++;
    }

    tinystl::Array<std::string, 3> l3;
    l3 = l2;
    i = 0;
    for (it_tmp_2 = l3.begin(); it_tmp_2 != l3.end(); it_tmp_2++)
    {
        ASSERT_EQ(*it_tmp_2, std::to_string(i + 1).c_str());
        i++;
    }

    tinystl::Array<tinystl::String, 3> l4{"1", "2", "3"};
    tinystl::Array<tinystl::String, 3>::iterator it_tmp_3; // 声明一个迭代器
    i = 0;
    for (it_tmp_3 = l4.begin(); it_tmp_3 != l4.end(); it_tmp_3++)
    {
        ASSERT_EQ(*it_tmp_3, std::to_string(i + 1).c_str());
        i++;
    }

    tinystl::Array<tinystl::String, 3> l5;
    l5 = l4;
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
