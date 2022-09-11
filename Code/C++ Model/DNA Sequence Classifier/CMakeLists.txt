cmake_minimum_required(VERSION 3.0.0)
project(DNA_Sequence_Classifier VERSION 1.0.0)



set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin)
set(BINARY ${CMAKE_PROJECT_NAME})


# add_subdirectory(lib/Eigen)

include_directories(
    lib/
)
add_executable(${BINARY}_run main.cpp)