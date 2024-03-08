#ifndef FORWARDLIST_TEST_H
#define FORWARDLIST_TEST_H

#include <gtest/gtest.h>

#include "forward_list/forward_list.h"
#include "string/string.h"
#include <string>

template <typename T>
bool compare(tinystl::forward_list<T> &a, tinystl::forward_list<T> b)
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
class ForwardListTEST : public testing::Test
{
public:
    T *value_;

    ~ForwardListTEST() {
        delete[] value_;
    }

    void fillVal(unsigned int, int size)
    {
        value_ = new unsigned int[size];
        srand((unsigned)time(NULL));
        for (int i = 0; i < size; i++)
        {
            value_[i] = rand() % (100 + 1);
        }
    }

    void fillVal(double, int size)
    {
        value_ = new double[size];
        srand((unsigned)time(NULL));
        for (int i = 0; i < size; i++)
        {
            value_[i] = rand() % (100 + 1);
        }
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


TYPED_TEST_SUITE_P(ForwardListTEST);

// 测试所有的声明
template <typename T>
void testDeclareWithInit(T *a, int size)
{
    typename tinystl::forward_list<T>::iterator it_tmp; // 声明一个迭代器
    tinystl::forward_list<T> l1(a, a + size);
    ASSERT_EQ(l1.size(), size);
    int i = 0;
    for (it_tmp = l1.begin(); it_tmp != l1.end(); it_tmp++)
    {
        ASSERT_EQ(*it_tmp, a[i++]);
    }

    tinystl::forward_list<T> l3(a, a + 2);
    i = 0;
    ASSERT_EQ(l3.size(), 2);
    for (it_tmp = l3.begin(); it_tmp != l3.end(); it_tmp++)
    {
        ASSERT_EQ(*it_tmp, a[i++]);
    }

    // test for iterator
    tinystl::forward_list<T> l4(l1.begin(), l1.end());
    i = 0;
    ASSERT_EQ(l4.size(), size);
    for (it_tmp = l4.begin(); it_tmp != l4.end(); it_tmp++)
    {
        ASSERT_EQ(*it_tmp, a[i++]);
    }

    // test for l-value
    tinystl::forward_list<T> l6(std::move(l1));
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
    typename tinystl::forward_list<T>::iterator it_tmp; // 声明一个迭代器
    tinystl::forward_list<T> l1(size);
    ASSERT_EQ(l1.size(), size);
    for (it_tmp = l1.begin(); it_tmp != l1.end(); it_tmp++)
    {
        ASSERT_EQ(*it_tmp, static_cast<T>(0));
    }
}

template <typename T>
void testAssign(T *a, int size)
{
    typename tinystl::forward_list<T>::iterator it_tmp; // 声明一个迭代器
    tinystl::forward_list<T> l1(a, a + size);
    tinystl::forward_list<T> l2, l4, l5;
    l2 = l1;
    ASSERT_EQ(l2.size(), size);
    int i = 0;
    for (it_tmp = l2.begin(); it_tmp != l2.end(); it_tmp++)
    {
        ASSERT_EQ(*it_tmp, a[i++]);
    }

    tinystl::forward_list<T> l3(a, a + 2);
    l4 = l3;
    i = 0;
    ASSERT_EQ(l3.size(), 2);
    for (it_tmp = l4.begin(); it_tmp != l4.end(); it_tmp++)
    {
        ASSERT_EQ(*it_tmp, a[i++]);
    }

    // // test for iterator
    tinystl::forward_list<T> lt(l1.begin() + 1, l1.end());
    l5 = lt;
    i = 1;
    ASSERT_EQ(l5.size(), 4);
    for (it_tmp = l5.begin(); it_tmp != l5.end(); it_tmp++)
    {
        ASSERT_EQ(*it_tmp, a[i++]);
    }

    // test for l-value
    tinystl::forward_list<T> l6(std::move(l1));
    i = 0;
    ASSERT_EQ(l6.size(), size);
    for (it_tmp = l6.begin(); it_tmp != l6.end(); it_tmp++)
    {
        ASSERT_EQ(*it_tmp, a[i++]);
    }
}

TYPED_TEST_P(ForwardListTEST, Constructor)
{

    TypeParam n = 0;

    this->fillVal(n, 5);
    TypeParam *tmp = this->value_;
    testDeclareWithInit<TypeParam>(tmp, 5);
    testDeclareWithNoInit<TypeParam>(5);
    testAssign<TypeParam>(tmp, 5);

}


REGISTER_TYPED_TEST_SUITE_P(ForwardListTEST, Constructor);
using ForwardListEleTypes = ::testing::Types<int, unsigned int, char, const char*, double>;


INSTANTIATE_TYPED_TEST_SUITE_P(tinystl, ForwardListTEST, ForwardListEleTypes);

// 测试自定义string类型
TEST(ForwardListTEST, Test_ForwardList_String)
{
    tinystl::String a[] = {"aa", "bb", "cc", "dd", "ee"};
    tinystl::forward_list<tinystl::String>::iterator it_tmp; // 声明一个迭代器
    tinystl::forward_list<tinystl::String> l1(a, a + 5);

    const char *a2[5] = {"aa", "bb", "cc", "dd", "ee"};
    tinystl::forward_list<const char *> lun(a2, a2 + 5);

    // test for iterator
    tinystl::forward_list<const char *> lt(lun.begin(), lun.end());
    int i = 0;
    ASSERT_EQ(l1.size(), 5);
    for (it_tmp = l1.begin(); it_tmp != l1.end(); it_tmp++)
    {
        ASSERT_EQ(*it_tmp, a[i++]);
    }
}

// 测试嵌套类型
TEST(ForwardListTests, Test_ForwardList_Initialize_List)
{
    tinystl::forward_list<int> l1{1, 2, 3, 4, 5, 6, 7, 8, 9};
    tinystl::forward_list<int>::iterator it_tmp; // 声明一个迭代器
    int i = 0;
    for (it_tmp = l1.begin(); it_tmp != l1.end(); it_tmp++)
    {
        ASSERT_EQ(*it_tmp, i + 1);
        i++;
    }

    tinystl::forward_list<std::string> l2{"1", "2", "3"};
    tinystl::forward_list<std::string>::iterator it_tmp_2; // 声明一个迭代器
    i = 0;
    for (it_tmp_2 = l2.begin(); it_tmp_2 != l2.end(); it_tmp_2++)
    {
        ASSERT_EQ(*it_tmp_2, std::to_string(i + 1).c_str());
        i++;
    }

    tinystl::forward_list<std::string> l3;
    l3 = l2;
    i = 0;
    for (it_tmp_2 = l3.begin(); it_tmp_2 != l3.end(); it_tmp_2++)
    {
        ASSERT_EQ(*it_tmp_2, std::to_string(i + 1).c_str());
        i++;
    }

    tinystl::forward_list<tinystl::String> l4{"1", "2", "3"};
    tinystl::forward_list<tinystl::String>::iterator it_tmp_3; // 声明一个迭代器
    i = 0;
    for (it_tmp_3 = l4.begin(); it_tmp_3 != l4.end(); it_tmp_3++)
    {
        ASSERT_EQ(*it_tmp_3, std::to_string(i + 1).c_str());
        i++;
    }

    tinystl::forward_list<tinystl::String> l5;
    l5 = l4;
    i = 0;
    for (it_tmp_3 = l5.begin(); it_tmp_3 != l5.end(); it_tmp_3++)
    {
        ASSERT_EQ(*it_tmp_3, std::to_string(i + 1).c_str());
        i++;
    }
}

// TEST(ForwardListTests, Test_ForwardList_Member_Function)
// {
//     tinystl::forward_list<int> l1{1, 2, 3, 4, 5, 6, 7, 8, 9};
//     ASSERT_EQ(l1.size(), 9);
//     // push_back
//     l1.push_back(10);
//     // size
//     ASSERT_EQ(l1.size(), 10);
//     compare(l1, tinystl::forward_list<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});

//     // pop_back
//     l1.pop_back();
//     // size
//     ASSERT_EQ(l1.size(), 9);
//     compare(l1, tinystl::forward_list<int>{1, 2, 3, 4, 5, 6, 7, 8, 9});

//     ASSERT_EQ(l1.size(), 10);
//     compare(l1, tinystl::forward_list<int>{1, 10, 2, 3, 4, 5, 6, 7, 8, 9});

//     // erase
//     // l1.erase(l1.begin() + 1);
//     compare(l1, tinystl::forward_list<int>{1, 2, 3, 4, 5, 6, 7, 8, 9});
//     // size
//     ASSERT_EQ(l1.size(), 9);
//     // compare

//     // capacity

//     // clear
//     l1.clear();

//     // empty
//     ASSERT_EQ(l1.empty(), true);
// }

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#endif
