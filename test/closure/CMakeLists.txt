add_executable(closure ./main.cpp)
target_link_libraries(closure gmock gtest lr1)
add_test(NAME closure COMMAND closure)