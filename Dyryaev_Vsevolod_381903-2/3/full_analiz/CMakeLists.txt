cmake_minimum_required(VERSION 3.13.4)

project(full_analiz)

set(FULL full_analiz.cpp)


include_directories(include)

add_library(full_analiz STATIC ${FULL})


target_link_libraries(full_analiz leks)
target_link_libraries(full_analiz broadcast)
target_link_libraries(full_analiz synt)
