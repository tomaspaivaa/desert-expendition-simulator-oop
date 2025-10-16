cmake_minimum_required(VERSION 3.27)
project(TrabalhoPratico_POO)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES "./*.cpp")

file(GLOB_RECURSE EXCLUDE_SOURCES "./cmake-build-debug/*.cpp")

list(REMOVE_ITEM SOURCES ${EXCLUDE_SOURCES})

add_executable(TrabalhoPratico_POO ${SOURCES})
