cmake_minimum_required(VERSION 3.10)
project(orderset_pc3)

set(CMAKE_CXX_STANDARD 17)

# el ejecutable principal para el problema ORDERSET
add_executable(orderset src/main.cpp src/treap.cpp)
target_include_directories(orderset PRIVATE include)

# tests unitarios del treap
enable_testing()

add_executable(test_treap tests/test_treap.cpp src/treap.cpp)
target_include_directories(test_treap PRIVATE include)
add_test(NAME test_treap COMMAND test_treap)

# test de fuerza bruta (comparar treap vs vector ordenado)
add_executable(test_brute_force tests/test_brute_force.cpp src/treap.cpp)
target_include_directories(test_brute_force PRIVATE include)
add_test(NAME test_brute_force COMMAND test_brute_force)

# demo interactivo
add_executable(demo_orderset demos/demo_orderset.cpp src/treap.cpp)
target_include_directories(demo_orderset PRIVATE include)
