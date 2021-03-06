cmake_minimum_required(VERSION 3.16)
project(wunise)
set(CMAKE_CXX_STANDARD 17)
add_definitions(-DUNICODE)
add_executable(wunise WIN32 
	src/wunise.cpp 
	src/dxapp.cpp 
	src/d3dobject.cpp
	src/shader.cpp
)
target_include_directories(wunise PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(wunise PRIVATE d3d11 d3d12 dxgi d3dcompiler)