cmake_minimum_required(VERSION 3.10)
set(CMAKE_CPP_STANDARD 11)
project(lr1)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.10.x
)

FetchContent_GetProperties(googletest)
if (NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif ()

add_library(lr1 ./src/Production.cpp ./src/Item.cpp ./src/Context.cpp)

add_subdirectory(test)
add_subdirectory(example)
