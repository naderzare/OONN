cmake_minimum_required(VERSION 2.6)

PROJECT (OONN)
SET( PRODUCT_NAME  oonn)

set (MAJOR 1)
set (MINOR 0)
set (PATCH 0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -g -std=c++1y")
    
add_subdirectory(src)
