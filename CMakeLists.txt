cmake_minimum_required(VERSION 3.15)
project(sp-exam)
set(CMAKE_CXX_STANDARD 23)

# add libs
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/lib/argparse)
include_directories(include)

add_executable(main src/main.cpp)

target_link_libraries(main
    argparse
)