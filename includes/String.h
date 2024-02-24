#ifndef STRING
#define STRING

/**
 * @brief String Class
 *
 */

#include <cstddef>
#include <cstring>
#include <iostream>
#include <string> // for string class
using namespace std;

namespace tinystl
{

  class String
  {
  public:
    // constructor
    String(const char *str = nullptr)
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
    // copy ctor
    String(const String &str)
    {
      _size = str._size;
      m_data = str.m_data; // shallow copy
      *(int *)(m_data - 4) += 1;
      // m_data = new char[size + 1];
      // strcpy(m_data, str.m_data);
    }

    ~String()
    {
      if (m_data && *(int *)(m_data - 4) == 1)
      {
        delete[] (m_data - 4);
        m_data = nullptr;
      }
    }

    class StringProxy
    {
    public:
      StringProxy(int index, String *self) : index(index), self(self) {}

      // char &operator=(String &str) {
      //   // cow
      //   if (index >= 0 && index < self->size()) {
      //     if (*(int *)(self->m_data - 4) > 1) {
      //       char *tmp = new char[str._size + 1 + 4];
      //       strcpy(tmp, str.m_data);
      //       *(int *)(self->m_data - 4) = 1;
      //       self->_size = str._size;
      //       self->m_data = tmp;

      //     } else {
      //       self->m_data = str.m_data;
      //       self->_size = str._size;
      //     }
      //   }
      //   return self->m_data[index];
      // }

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
      String *self;
    };

    StringProxy operator[](int index) { return StringProxy(index, this); }

    // String &operator=(const String &str)
    // {
    //   cout << "Copy Constructor" << str.m_data << &m_data << endl;
    //   // _size = str._size;
    //   // m_data = str.m_data; // shallow copy
    //   // *(int *)(m_data - 4) += 1;
    //   if (&str != this)
    //   {
    //     if (*(int *)(m_data - 4) > 1)
    //     {
    //       *(int *)(m_data - 4) -= 1; // origin - 1
    //       m_data = str.m_data;
    //       *(int *)(m_data - 4) += 1;
    //     } else {
    //       m_data = str.m_data;
    //     }
    //     _size = str._size;
    //   }
    //   cout << "Copy Constructoring" << m_data << endl;
    //   return *this;
    // }

    String operator=(const String &rhs)
    {
      // 判断是否是自己赋值给自己
      if (this != &rhs)
      {
        // 如果被赋值的字符串引用计数为1，那么就释放(被赋值的)原始内存空间，
        // 防止脏数据（如被赋值的数据长度大于赋值过来的数据）
        if (1 == *(int *)(m_data - 4))
        {
          delete[] (m_data - 4);
        }

        // 两个指针指向同一个字符串,实现浅拷贝
        m_data = rhs.m_data;
        // 对字符串引用计数+1
        *(int *)(m_data - 4) += 1;
        _size = rhs._size;
      }
      return *this;
    }

    // String operator=(const char *rhs)
    // {
    //   // 如果被赋值的字符串引用计数为1，那么就释放(被赋值的)原始内存空间，
    //   // 防止脏数据（如被赋值的数据长度大于赋值过来的数据）
    //   if (1 == *(int *)(m_data - 4))
    //   {
    //     delete[] (m_data - 4);
    //   }
    //   m_data = new char[_size + 5]() + 4;
    //   strcpy(m_data, rhs);
    //   *(int *)(m_data - 4) += 1;
    //   _size = strlen(rhs);
    //   return *this;
    // }

    // String &operator=(String &&str) {
    //   cout << "Move = Constructor" << endl;
    //   if (&str == this) {
    //     return *this;
    //   }
    //   str.m_data = nullptr;
    //   delete[] m_data;
    //   _size = str._size;
    //   m_data = str.m_data;
    //   return *this;
    // }

    // String(const String &&str) : m_data(str.m_data) {
    //   cout << "Move Constructor" << endl;
    // }

    size_t size() const { return _size; }

    // ostream的friend function
    friend ostream &operator<<(ostream &output, const String &str)
    {
      output << str.m_data;
      return output;
    }

    int refCount() const { return *(int *)(m_data - 4); }

    const char *strAddr() const { return m_data; }

    String operator+(const String &str)
    {
      String tmp;
      tmp._size = _size + str._size;
      tmp.m_data = new char[tmp._size + 5]() + 4;
      strcpy(tmp.m_data, m_data);
      strcat(tmp.m_data, str.m_data);
      return tmp;
    }

    String operator+(const char *str)
    {
      String tmp;
      tmp._size = _size + strlen(str);
      tmp.m_data = new char[tmp._size + 5]() + 4;
      strcpy(tmp.m_data, m_data);
      strcat(tmp.m_data, str);
      return tmp;
    }

    friend bool operator==(const String &c1, const char *str)
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

    friend bool operator==(const String &c1, const String &str)
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

    friend bool operator!=(const String &c1, const String &str)
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
}

#endif