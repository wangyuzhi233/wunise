cmake_minimum_required(VERSION 3.16)
project(wunise)
set(CMAKE_CXX_STANDARD 17)
add_definitions(-DUNICODE -D_UNICODE)
add_executable(wunise WIN32 
	src/wunise.cpp
	src/window.cpp
	src/game.cpp
	src/graphics.cpp
)
target_include_directories(wunise PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(wunise PRIVATE d3d11 dxgi d3dcompiler)