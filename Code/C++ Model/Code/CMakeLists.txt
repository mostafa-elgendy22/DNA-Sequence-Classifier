cmake_minimum_required(VERSION 3.0.0)
project(DNA_Sequence_Classifier VERSION 1.0.0)


set(BINARY ${CMAKE_PROJECT_NAME})
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-O3")


include_directories(
    lib/
)
add_executable(${BINARY}_run main.cpp)