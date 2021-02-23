cmake_minimum_required(VERSION 3.15)
project(wunise)
set(CMAKE_CXX_STANDARD 17)

add_library(wunise src/wunise.cpp)
target_include_directories(wunise PRIVATE ${PROJECT_SOURCE_DIR}/include)

add_subdirectory(examples)