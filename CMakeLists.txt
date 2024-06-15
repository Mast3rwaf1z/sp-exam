cmake_minimum_required(VERSION 3.15)
project(sp-exam)
set(CMAKE_CXX_STANDARD 23)

# add libs
include_directories(include)

add_definitions(-DDEBUG=0)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/lib/matplotlib-cpp)


add_executable(main src/main.cpp)
add_executable(benchmark src/benchmark.cpp)
add_executable(example src/example.cpp)

find_package(PythonLibs 3.12)
target_include_directories(main PRIVATE ${PYTHON_INCLUDE_DIRS})
target_link_libraries(main ${PYTHON_LIBRARIES})
target_include_directories(benchmark PRIVATE ${PYTHON_INCLUDE_DIRS})
target_link_libraries(benchmark ${PYTHON_LIBRARIES})
target_include_directories(example PRIVATE ${PYTHON_INCLUDE_DIRS})
target_link_libraries(example ${PYTHON_LIBRARIES})

target_link_libraries(main
    MatplotlibC++
)
target_link_libraries(benchmark
    MatplotlibC++
)
target_link_libraries(example
    MatplotlibC++
)