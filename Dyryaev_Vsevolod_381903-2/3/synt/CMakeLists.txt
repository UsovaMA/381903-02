cmake_minimum_required(VERSION 3.13.4)

project(synt)


set(SYNT synt.cpp)

include_directories(include)


add_library(synt STATIC ${SYNT})