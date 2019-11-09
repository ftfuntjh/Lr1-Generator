add_executable(lua ./main.cpp)
target_link_libraries(lua gmock gtest lr1)
add_test(NAME lua COMMAND lua)