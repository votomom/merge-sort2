cmake_minimum_required(VERSION 3.10.0)
add_executable(merge-sort-test merge-sort.cpp test.cpp)
target_link_libraries(merge-sort-test PUBLIC doctest default)
add_test(NAME merge-sort-test COMMAND merge-sort-test --force-colors -d)
add_custom_target(cloud-test COMMAND merge-sort-test --force-colors -d)

add_executable(merge-sort merge-sort.cpp main.cpp)
target_link_libraries(merge-sort PUBLIC default)
