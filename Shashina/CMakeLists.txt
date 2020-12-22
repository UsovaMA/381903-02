cmake_minimum_required(VERSION 2.8)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)

include_directories(sample gtest)

# BUILD
add_subdirectory(sample)
add_subdirectory(sample_test)
add_subdirectory(gtest)
