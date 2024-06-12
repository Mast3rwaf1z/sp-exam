cmake_minimum_required(VERSION 3.15)
project(sp-exam)
set(CMAKE_CXX_STANDARD 23)

# add libs
include_directories(include)

add_definitions(-DDEBUG=0)

add_executable(main src/main.cpp)

target_link_libraries(main
)