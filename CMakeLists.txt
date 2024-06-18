cmake_minimum_required(VERSION 3.15)
project(sp-exam)
set(CMAKE_CXX_STANDARD 23)

# add libs
include_directories(include)

add_subdirectory(lib/matplotplusplus)

add_executable(main src/main.cpp)
add_executable(benchmark src/benchmark.cpp)
add_executable(example src/example.cpp)
add_executable(hospitalized src/hospitalized.cpp)
add_executable(hospitalized_v2 src/hospitalized_v2.cpp)
add_executable(observer src/observer.cpp)
add_executable(test_utils src/tests/test_utils.cpp)
add_executable(test_reactant src/tests/test_reactant.cpp)
add_executable(test_reaction src/tests/test_reaction.cpp)
add_executable(test_vessel src/tests/test_vessel.cpp)

enable_testing()

target_link_libraries(test_utils
    matplot
)

target_link_libraries(hospitalized
    matplot
)

target_link_libraries(hospitalized_v2
    matplot
)
target_link_libraries(main
    matplot
)
target_link_libraries(benchmark
    matplot
)
target_link_libraries(example
    matplot
)
target_link_libraries(test_reactant
    matplot
)
target_link_libraries(test_reaction
    matplot
)
target_link_libraries(test_vessel
    matplot
)
target_link_libraries(observer
    matplot
)

add_test(NAME test_utils COMMAND test_utils)
add_test(NAME test_reactant COMMAND test_reactant)
add_test(NAME test_reaction COMMAND test_reaction)
add_test(NAME test_vessel COMMAND test_vessel)