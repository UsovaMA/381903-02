cmake_minimum_required(VERSION 3.13.4)

project(leks)

set(LEKS leks.cpp)

include_directories(include)

add_library(leks STATIC ${LEKS})
