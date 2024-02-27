#ifndef COW_STRING_H
#define COW_STRING_H

/**
 * @brief CowString Class
 *
 */

#include <cstddef>
#include <cstring>
#include <iostream>
#include <string> // for string class

using namespace std;

namespace tinystl
{
    class CowString
    {
    public:
        // constructor
        // CowString()
        // {
        //     m_data = new char[5]() + 4;
        //     *(int *)(m_data - 4) = 1;
        //     _size = 0;
        //     m_data[0] = '\0';
        // }
        // CowString(const char *str)
        // {
        CowString(const char *str = nullptr)
        {
            if (str == nullptr)
            {
                m_data = new char[5]() + 4;
                *(int *)(m_data - 4) = 1;
                _size = 0;
                m_data[0] = '\0';
            }
            else
            {
                _size = strlen(str);
                m_data = new char[_size + 5]() + 4;
                *(int *)(m_data - 4) = 1;
                strcpy(m_data, str);
            }
        }
        // }
        // {

        //     _size = strlen(str);
        //     m_data = new char[_size + 5]() + 4;
        //     strcpy(m_data, str);
        //     *(int *)(m_data - 4) = 1;
        // }
        // copy ctor
        CowString(const CowString &str)
        {
            _size = str._size;
            m_data = str.m_data; // shallow copy
            *(int *)(m_data - 4) += 1;
            // m_data = new char[size + 1];
            // strcpy(m_data, str.m_data);
        }

        ~CowString()
        {
            std::cout << "~CowString" << std::endl;
            if (m_data && *(int *)(m_data - 4) == 1)
            {
                delete[] (m_data - 4);
                m_data = nullptr;
                _size = 0;
            }
        }

        bool operator!()
        {
            return _size == 0;
        }

        CowString &operator=(const char *s)
        {
            _size = std::strlen(s);
            if (1 == *(int *)(m_data - 4))
            {
                delete[] (m_data - 4);
            }

            // 两个指针指向同一个字符串,实现浅拷贝
            std::strcpy(m_data, s);
            // 对字符串引用计数+1
            *(int *)(m_data - 4) += 1;
            return *this;
        }

        class StringProxy
        {
        public:
            StringProxy(int index, CowString *self) : index(index), self(self) {}

            char &operator=(const char &str)
            {
                // cow
                if (index >= 0 && index < self->size())
                {
                    if (*(int *)(self->m_data - 4) > 1)
                    {
                        char *tmp = new char[self->_size + 5]() + 4;
                        *(int *)(self->m_data - 4) -= 1;
                        strcpy(tmp, self->m_data);
                        self->m_data = tmp;
                        *(int *)(self->m_data - 4) = 1;
                        // self->_size += strlen(&str);
                    }
                    self->m_data[index] = str;
                }
                return self->m_data[index];
            }

            // 类型转换
            operator char() { return self->m_data[index]; }

        private:
            int index;
            CowString *self;
        };

        StringProxy operator[](int i)
        {
            return StringProxy(i, this);
        }

        // read-write char access for non-const String
        // char & CowString::operator[](int i)
        // {
        //     return m_data[i];
        // }

        // read-only char access for const String
        const char &operator[](int i) const
        {
            return m_data[i];
        }

        CowString &operator=(const CowString &rhs)
        {
            //             String &
            // String::operator=(const String &st)
            /*
                    delete[] str;
                    len = st.len;
                    str = new char[len + 1];
                    std::strcpy(str, st.str);
                    return *this; */

            // 判断是否是自己赋值给自己
            if (this != &rhs)
            {
                // 如果被赋值的字符串引用计数为1，那么就释放(被赋值的)原始内存空间，
                // 防止脏数据（如被赋值的数据长度大于赋值过来的数据）
                if (m_data && 1 == *(int *)(m_data - 4))
                {
                    delete[] (m_data - 4);
                }
                // 两个指针指向同一个字符串,实现浅拷贝
                m_data = rhs.m_data;
                // 对字符串引用计数+1
                *(int *)(m_data - 4) += 1;
                _size = rhs._size;

                // _size = rhs._size;
                // // 两个指针指向同一个字符串,实现浅拷贝
                // m_data = new char[_size + 5] + 4;
                // std::strcpy(m_data,rhs.m_data);
                // // m_data = rhs.m_data;
                // // 对字符串引用计数+1
                // *(int *)(m_data - 4) += 1;
            }
            return *this;
        }

        size_t size() const { return _size; }

        // ostream的friend function
        friend ostream &operator<<(ostream &output, const CowString &str)
        {
            output << str.m_data;
            return output;
        }

        int refCount() const { return *(int *)(m_data - 4); }

        const char *strAddr() const { return m_data; }

        CowString operator+(const CowString &str)
        {
            CowString tmp;
            tmp._size = _size + str._size;
            tmp.m_data = new char[tmp._size + 5]() + 4;
            strcpy(tmp.m_data, m_data);
            strcat(tmp.m_data, str.m_data);
            return tmp;
        }

        CowString operator+(const char *str)
        {
            CowString tmp;
            tmp._size = _size + strlen(str);
            tmp.m_data = new char[tmp._size + 5]() + 4;
            strcpy(tmp.m_data, m_data);
            strcat(tmp.m_data, str);
            return tmp;
        }

        friend bool operator==(const CowString &c1, const char *str)
        {
            int size = strlen(str);
            if (size != c1._size)
            {
                return false;
            }

            for (int i = 0; i < size; i++)
            {
                if (str[i] != c1.m_data[i])
                {
                    return false;
                }
            }

            return true;
        }

        friend bool operator==(const CowString &c1, const CowString &str)
        {
            int size = str._size;
            if (size != c1._size)
            {
                return false;
            }

            for (int i = 0; i < size; i++)
            {
                if (str.m_data[i] != c1.m_data[i])
                {
                    return false;
                }
            }

            return true;
        }

        friend bool operator!=(const CowString &c1, const CowString &str)
        {
            int size = str._size;
            if (size != c1._size)
            {
                return true;
            }

            for (int i = 0; i < size; i++)
            {
                if (str.m_data[i] != c1.m_data[i])
                {
                    return true;
                }
            }

            return false;
        }

    private:
        char *m_data;
        int _size;
    };

    bool operator!(const CowString &s)
    {
        return s.size() == 0;
    }
}

#endif
