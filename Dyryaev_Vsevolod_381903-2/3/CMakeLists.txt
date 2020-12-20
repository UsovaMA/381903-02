cmake_minimum_required(VERSION 3.13.4)

project(lab3)

set(SOURSE_NAME main.cpp)

include_directories(include)


add_subdirectory(leks)
add_subdirectory(synt)
add_subdirectory(broadcast)
add_subdirectory(full_analiz)
add_subdirectory(test)


add_executable(main ${SOURSE_NAME})

target_link_libraries(main leks)
target_link_libraries(main broadcast)
target_link_libraries(main synt)
target_link_libraries(main full_analiz)