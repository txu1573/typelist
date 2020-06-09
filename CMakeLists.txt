cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-std=c++03")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -w -g -ggdb")

project(untitled)

file(GLOB_RECURSE HEADERS "*.h")
add_custom_target(headers SOURCES ${HEADERS})

add_executable(${PROJECT_NAME} "main.cpp")
