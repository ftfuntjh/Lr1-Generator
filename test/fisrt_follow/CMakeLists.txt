add_executable(first_follow main.cpp)
target_link_libraries(first_follow gmock gtest lr1)
add_test(NAME F_F COMMAND first_follow)
