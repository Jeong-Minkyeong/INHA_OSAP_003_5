#[[ 
MIT License

Copyright (c) 2024 오픈소스응용프로그래밍 3분반 5팀

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Written by : 오픈소스응용프로그래밍 3분반 5팀
Date : 2024-11-26
]]

cmake_minimum_required(VERSION 3.10)

project(AvlTreeTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# GoogleTest 탐색
find_package(GTest REQUIRED)

# 소스 파일 설정
set(SOURCE_FILES
    node.h
    set.h
    avl_tree.h
    avl_tree_tests.cc
)

# 실행 파일 생성
add_executable(AvlTreeTest ${SOURCE_FILES})

# GoogleTest 라이브러리 링크
target_link_libraries(AvlTreeTest ${GTEST_LIBRARIES} pthread)

# 테스트 설정
enable_testing()
add_test(NAME AvlTreeTest COMMAND AvlTreeTest)