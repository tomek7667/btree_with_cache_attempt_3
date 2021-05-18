cmake_minimum_required(VERSION 3.19)
project(btree_with_cache_attempt_3)

set(CMAKE_CXX_STANDARD 14)

add_executable(btree_with_cache_attempt_3 main.cpp BTree.cpp BTree.h Node.cpp Node.h)