cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-std=c++03")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -w -g -ggdb")

project(untitled)
add_executable(${PROJECT_NAME} "main.cpp")
