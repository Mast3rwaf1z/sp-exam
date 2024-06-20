cmake_minimum_required(VERSION 3.15)
project(sp-exam)
set(CMAKE_CXX_STANDARD 23)

# add libs
include_directories(include)

add_subdirectory(lib/matplotplusplus)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

foreach(executable main benchmark example hospitalized hospitalized_v2 observer)
    add_executable(${executable} src/${executable}.cpp)
    target_link_libraries(${executable} matplot)
endforeach()

enable_testing()

foreach(test test_utils test_reactant test_reaction test_vessel)
    add_executable(${test} src/tests/${test}.cpp)
    target_link_libraries(${test} matplot)
    add_test(NAME ${test} COMMAND ${test})
endforeach()