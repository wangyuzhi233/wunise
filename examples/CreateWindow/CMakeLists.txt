add_executable(window WIN32 window.cpp)
target_include_directories(window PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(window PUBLIC wunise)