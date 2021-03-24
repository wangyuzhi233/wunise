cmake_minimum_required(VERSION 3.16)
project(wunise)
set(CMAKE_CXX_STANDARD 17)
add_library(wunise STATIC
	src/rendersystem.cpp
)
target_include_directories(wunise PRIVATE ${CMAKE_SOURCE_DIR}/include)