cmake_minimum_required(VERSION 2.6)
 
project(test)

include_directories(include)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests test_main.cpp)

target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
target_link_libraries(runTests leks)
target_link_libraries(runTests synt)
target_link_libraries(runTests broadcast)
target_link_libraries(runTests full_analiz)
#target_link_directories(test_main leks)
