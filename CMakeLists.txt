cmake_minimum_required(VERSION 3.29)
project(part4)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(part4
    LinkedList.h
    main.cpp)
