SET(LLVM_SRC /usr/bin/llvm-config)
SET(CMAKE_C_COMPILER /usr/bin/gcc)
SET(CMAKE_CXX_COMPILER /usr/bin/clang++)
# add_compile_options(-g -O3 ${LLVM_SRC})
# find_package(LLVM_SRC)
cmake_minimum_required(VERSION 3.0.0)
project(tinystl VERSION 0.1.0 LANGUAGES C CXX)


include_directories()


include(CTest)
enable_testing()

add_executable(main main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

