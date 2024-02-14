#ifndef STRING
#define STRING

/**
 * @brief String Class
 *
 */

#include <cstddef>
#include <cstring>
#include <iostream>
using namespace std;

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
      std::cout << "构造函数" << strlen(str) << std::endl;
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

  String &operator=(const String &str)
  {
    // if (&str == this) {
    //   return *this;
    // }
    // delete[] m_data;
    // size = str.size;
    // m_data = new char[size + 1];
    // strcpy(m_data, str.m_data);
    // return *this;
    if (&str != this)
    {
      if (*(int *)(m_data - 4) == 1)
      {
        // delete[] (m_data - 4);
        // m_data = new char[str._size + 5];
        // strcpy(m_data, str.m_data);
      }
      m_data = str.m_data;
      *(int *)(m_data - 4) += 1;
      // _size = str._size;
    }
    return *this;
  }

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
    output << str.m_data << endl;
    return output;
  }

  int refCount() const { return *(int *)(m_data - 4); }

  const char *strAddr() const { return m_data; }

private:
  char *m_data;
  int _size;
};

// int main(int argc, char **argv) {
//   String s1("hello");
//   cout << "s1 = " << s1 << endl;
//   cout << "s1.refcount = " << s1.refCount() << endl;
//   printf("s1.addr = %p\n", s1.strAddr());

//   cout << endl;
//   cout << "拷贝操作String s2 = s1" << endl;
//   String s2 = s1;
//   cout << "s1 = " << s1 << endl;
//   cout << "s2 = " << s2 << endl;
//   cout << "s1.refcount = " << s1.refCount() << endl;
//   printf("s1.addr = %p\n", s1.strAddr());
//   cout << "s2.refcount = " << s2.refCount() << endl;
//   printf("s2.addr = %p\n", s2.strAddr());
//   s2.strAddr();

//   cout << endl;
//   cout << "赋值操作s3 = s2" << endl;
//   String s3;
//   s3 = s2;
//   cout << "s2.refcount = " << s2.refCount() << endl;
//   printf("s2.addr = %p\n", s2.strAddr());
//   cout << "s3.refcount = " << s3.refCount() << endl;
//   printf("s3.addr = %p\n", s3.strAddr());

//   cout << endl;
//   cout << "读下标操作" << endl;
//   cout << "s2[0] = " << s2[0] << ", s1 = " << s1 << endl;
//   cout << "s1.refcount = " << s1.refCount() << endl;
//   printf("s1.addr = %p\n", s1.strAddr());
//   cout << "s2.refcount = " << s2.refCount() << endl;
//   printf("s2.addr = %p\n", s2.strAddr());

//   cout << endl;
//   cout << "对数据写操作,将会触发写时复制技术！" << endl;
//   s2[0] = '0';
//   cout << "s2[0] = " << s2[0] << ", s2 = " << s2 << endl;
//   cout << "s1.refcount = " << s1.refCount() << endl;
//   printf("s1.addr = %p\n", s1.strAddr());
//   cout << "s2.refcount = " << s2.refCount() << endl;
//   printf("s2.addr = %p\n", s2.strAddr());
//   cout << "s3.refcount = " << s3.refCount() << endl;
//   printf("s3.addr = %p\n", s3.strAddr());

//   return 0;
// }

#endif