cmake_minimum_required(VERSION 3.10)
project(orderset_pc3)

set(CMAKE_CXX_STANDARD 17)

# el ejecutable principal para el problema ORDERSET
add_executable(orderset src/main.cpp)
target_include_directories(orderset PRIVATE include)
