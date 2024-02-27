#ifndef VECTOR_TEST_H
#define VECTOR_TEST_H

#include <gtest/gtest.h>

#include "vector.h"
#include "String.h"
#include <string>

template <typename T>
bool compare(tinystl::Vector<T> &a, tinystl::Vector<T> b)
{
    if (a.size() != b.size())
    {
        return false;
    }
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] != b[i])
        {
            return false;
        }
    }

    return true;
}

template <typename T>
class VectorTest : public testing::Test
{
public:
    T *value_;

    ~VectorTest() {
        delete[] value_;
    }

    void fillVal(unsigned int val, int size)
    {
        value_ = new unsigned int[size];
        srand((unsigned)time(NULL));
        for (int i = 0; i < size; i++)
        {
            value_[i] = rand() % (100 + 1);
        }
    }

    void fillVal(double val, int size)
    {
        value_ = new double[size];
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


TYPED_TEST_SUITE_P(VectorTest);

// 测试所有的声明
template <typename T>
void testDeclareWithInit(T *a, int size)
{
    typename tinystl::Vector<T>::iterator it_tmp; // 声明一个迭代器
    tinystl::Vector<T> l1(a, a + size);
    std::cout << l1.size() << std::endl;
    ASSERT_EQ(l1.size(), size);
    int i = 0;
    for (it_tmp = l1.begin(); it_tmp != l1.end(); it_tmp++)
    {
        ASSERT_EQ(*it_tmp, a[i++]);
    }

    tinystl::Vector<T> l3(a, a + 2);
    i = 0;
    ASSERT_EQ(l3.size(), 2);
    for (it_tmp = l3.begin(); it_tmp != l3.end(); it_tmp++)
    {
        ASSERT_EQ(*it_tmp, a[i++]);
    }

    // test for iterator
    tinystl::Vector<T> l4(l1.begin(), l1.end());
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
    tinystl::Vector<T> l6(std::move(l1));
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
    typename tinystl::Vector<T>::iterator it_tmp; // 声明一个迭代器
    tinystl::Vector<T> l1(size);
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
    typename tinystl::Vector<T>::iterator it_tmp; // 声明一个迭代器
    tinystl::Vector<T> l1(a, a + size);
    tinystl::Vector<T> l2, l4, l5;
    l2 = l1;
    ASSERT_EQ(l2.size(), size);
    int i = 0;
    for (it_tmp = l2.begin(); it_tmp != l2.end(); it_tmp++)
    {
        ASSERT_EQ(*it_tmp, a[i++]);
    }

    tinystl::Vector<T> l3(a, a + 2);
    l4 = l3;
    i = 0;
    ASSERT_EQ(l3.size(), 2);
    for (it_tmp = l4.begin(); it_tmp != l4.end(); it_tmp++)
    {
        ASSERT_EQ(*it_tmp, a[i++]);
    }
    std::cout << "l4.size() = " << std::endl;
    for (auto i : l1)
    {
        std::cout << i << " " << std::endl;
    }

    // // test for iterator
    tinystl::Vector<T> lt(l1.begin() + 1, l1.end());
    l5 = lt;
    i = 1;
    ASSERT_EQ(l5.size(), 4);
    for (it_tmp = l5.begin(); it_tmp != l5.end(); it_tmp++)
    {
        ASSERT_EQ(*it_tmp, a[i++]);
    }

    // test for l-value
    tinystl::Vector<T> l6(std::move(l1));
    i = 0;
    ASSERT_EQ(l6.size(), size);
    for (it_tmp = l6.begin(); it_tmp != l6.end(); it_tmp++)
    {
        ASSERT_EQ(*it_tmp, a[i++]);
    }
}

TYPED_TEST_P(VectorTest, Constructor)
{

    TypeParam n = 0;

    this->fillVal(n, 5);
    TypeParam *tmp = this->value_;
    testDeclareWithInit<TypeParam>(tmp, 5);
    testDeclareWithNoInit<TypeParam>(5);
    testAssign<TypeParam>(tmp, 5);

}

// REGISTER_TYPED_TEST_CASE_P(VectorTest, Constructor);

REGISTER_TYPED_TEST_SUITE_P(VectorTest, Constructor);
using VectorTypes = ::testing::Types<int, unsigned int, char, const char*, double>;


INSTANTIATE_TYPED_TEST_SUITE_P(tinystl, VectorTest, VectorTypes);
// INSTANTIATE_TYPED_TEST_SUITE_P(tinystl2, VectorTest, char);

// 测试自定义string类型
TEST(VectorTests, Test_Vector_String)
{
    tinystl::String a[] = {"aa", "bb", "cc", "dd", "ee"};
    tinystl::Vector<tinystl::String>::iterator it_tmp; // 声明一个迭代器
    tinystl::Vector<tinystl::String> l1(a, a + 5);

    const char *a2[5] = {"aa", "bb", "cc", "dd", "ee"};
    tinystl::Vector<const char *> lun(a2, a2 + 5);

    unsigned int arr[5] = {1, 2, 3, 4, 5};

    testAssign<const char *>(a2, 5);

    // // test for iterator
    tinystl::Vector<const char *> lt(lun.begin() + 3, lun.end());
    int i = 0;
    ASSERT_EQ(l1.size(), 5);
    for (it_tmp = l1.begin(); it_tmp != l1.end(); it_tmp++)
    {
        ASSERT_EQ(*it_tmp, a[i++]);
    }
}

// 测试嵌套类型
TEST(VectorTests, Test_Vector_Initialize_List)
{
    tinystl::Vector<int> l1{1, 2, 3, 4, 5, 6, 7, 8, 9};
    tinystl::Vector<int>::iterator it_tmp; // 声明一个迭代器
    int i = 0;
    for (it_tmp = l1.begin(); it_tmp != l1.end(); it_tmp++)
    {
        ASSERT_EQ(*it_tmp, i + 1);
        i++;
    }

    tinystl::Vector<std::string> l2{"1", "2", "3"};
    tinystl::Vector<std::string>::iterator it_tmp_2; // 声明一个迭代器
    i = 0;
    for (it_tmp_2 = l2.begin(); it_tmp_2 != l2.end(); it_tmp_2++)
    {
        ASSERT_EQ(*it_tmp_2, std::to_string(i + 1).c_str());
        i++;
    }

    tinystl::Vector<std::string> l3;
    l3 = l2;
    i = 0;
    for (it_tmp_2 = l3.begin(); it_tmp_2 != l3.end(); it_tmp_2++)
    {
        ASSERT_EQ(*it_tmp_2, std::to_string(i + 1).c_str());
        i++;
    }

    tinystl::Vector<tinystl::String> l4{"1", "2", "3"};
    tinystl::Vector<tinystl::String>::iterator it_tmp_3; // 声明一个迭代器
    i = 0;
    for (it_tmp_3 = l4.begin(); it_tmp_3 != l4.end(); it_tmp_3++)
    {
        ASSERT_EQ(*it_tmp_3, std::to_string(i + 1).c_str());
        i++;
    }

    tinystl::Vector<tinystl::String> l5;
    l5 = l4;
    i = 0;
    for (it_tmp_3 = l5.begin(); it_tmp_3 != l5.end(); it_tmp_3++)
    {
        ASSERT_EQ(*it_tmp_3, std::to_string(i + 1).c_str());
        i++;
    }
}

TEST(VectorTests, Test_Vector_Member_Function)
{
    tinystl::Vector<int> l1{1, 2, 3, 4, 5, 6, 7, 8, 9};
    tinystl::Vector<int>::iterator it_tmp; // 声明一个迭代器
    int i = 0;
    int back = l1.back();
    // back
    ASSERT_EQ(9, back);
    // front
    int front = l1.front();
    ASSERT_EQ(1, front);
    // size
    ASSERT_EQ(l1.size(), 9);
    // push_back
    l1.push_back(10);
    // size
    ASSERT_EQ(l1.size(), 10);
    compare(l1, tinystl::Vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});

    // pop_back
    l1.pop_back();
    // size
    ASSERT_EQ(l1.size(), 9);
    compare(l1, tinystl::Vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9});

    // insert
    l1.insert(l1.begin() + 1, 10);
    // size
    ASSERT_EQ(l1.size(), 10);
    compare(l1, tinystl::Vector<int>{1, 10, 2, 3, 4, 5, 6, 7, 8, 9});

    // erase
    l1.erase(l1.begin() + 1);
    compare(l1, tinystl::Vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9});
    // size
    ASSERT_EQ(l1.size(), 9);
    // compare

    // capacity

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
