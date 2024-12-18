# CMakeLists.txt 예시

cmake_minimum_required(VERSION 3.10)

project(AvlTreeTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# GoogleTest 설정
include_directories(${CMAKE_SOURCE_DIR}/path_to_your_google_test/include)
link_directories(${CMAKE_SOURCE_DIR}/path_to_your_google_test/lib)

set(SOURCE_FILES
    test_runner.cc
    avl_tree.h
    avl_tree.h
    set.h
)

add_executable(AvlTreeTest ${SOURCE_FILES})

target_link_libraries(AvlTreeTest gtest gtest_main)

enable_testing()
add_test(NAME AvlTreeTest COMMAND AvlTreeTest)
