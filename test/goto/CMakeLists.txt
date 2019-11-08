add_executable(goto ./main.cpp)
target_link_libraries(goto gmock gtest lr1)
add_test(NAME goto COMMAND goto)