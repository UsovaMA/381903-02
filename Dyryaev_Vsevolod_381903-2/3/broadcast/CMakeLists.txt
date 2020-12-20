cmake_minimum_required(VERSION 3.13.4)

project(broadcast)

set(BROAD broadcast.cpp)


include_directories(include)

add_library(broadcast STATIC ${BROAD}) 
