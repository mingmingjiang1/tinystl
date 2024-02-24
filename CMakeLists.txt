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


include_directories(${PROJECT_SOURCE_DIR}/includes)

# build type
set(CMAKE_BUILD_TYPE release)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra -Wno-sign-compare -Wno-unused-but-set-variable -Wno-array-bounds")
	# set(EXTRA_CXX_FLAGS -Weffc++ -Wswitch-default -Wfloat-equal -Wconversion -Wsign-conversion)
	if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "8.0.0")
		message(FATAL_ERROR "required GCC 8.0 or later")
	else()
		# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	endif()
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra -Wno-sign-compare")
	# set(EXTRA_CXX_FLAGS -Weffc++ -Wswitch-default -Wfloat-equal -Wconversion -Wimplicit-fallthrough)
	if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "3.5.0")
		message(FATAL_ERROR "required Clang 3.5 or later")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	endif()
endif()

# add_library( hello libHelloSLAM.cpp)
# target_include_directories()

get_property(dirs DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
message(">>> include_dirs=${dirs}") #打印一下目录情况

message(">>> GCC=${CMAKE_CXX_COMPILER_VERSION}") #打印一下目录情况


include(CTest)
enable_testing()

# add_subdirectory(includes)
add_subdirectory(tests)

add_executable(${PROJECT_NAME} main.cpp)

# add_test(NAME ${PROJECT_NAME}
#         COMMAND ${PROJECT_NAME})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

