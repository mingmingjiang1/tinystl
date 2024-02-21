# SET(LLVM_SRC /usr/bin/llvm-config)
SET(CMAKE_C_COMPILER /usr/bin/gcc)
SET(CMAKE_CXX_COMPILER /usr/bin/g++)
cmake_minimum_required(VERSION 3.0.0)
project(tinystl)

# version
set(MyTinySTL_VERSION_MAJOR 1)
set(MyTinySTL_VERSION_MINOR 0)
set(MyTinySTL_VERSION_PATCH 0)
set(MyTinySTL_VERSION "${MyTinySTL_VERSION_MAJOR}.${MyTinySTL_VERSION_MINOR}.${MyTinySTL_VERSION_PATCH}")
message(STATUS "The version of this project is: ${MyTinySTL_VERSION}")


# include_directories(includes)

get_property(dirs DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
message(">>> include_dirs=${dirs}") #打印一下目录情况


include(CTest)
enable_testing()

# add_subdirectory(includes)
add_subdirectory(test)

add_executable(${PROJECT_NAME} main.cpp)

# add_test(NAME ${PROJECT_NAME}
#         COMMAND ${PROJECT_NAME})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

