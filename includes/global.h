#ifndef GLOBAL_H
#define GLOBAL_H

#include <iostream>
#include <cstddef>
#include <cstring>

#if __cplusplus >= 201103L

#define _GLIBCXX_NOEXCEPT noexcept

#else

#define _GLIBCXX_NOEXCEPT

#endif

#endif