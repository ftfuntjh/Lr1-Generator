cmake_minimum_required(VERSION 3.3)
set(CMAKE_CPP_STANDARD 11)
project(lr1)

add_executable(lr1 ./src/Production.cpp ./src/Item.cpp ./src/Lr1.cpp ./src/Context.cpp)
