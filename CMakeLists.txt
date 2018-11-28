cmake_minimum_required(VERSION 3.12)
add_subdirectory(googletest-master)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} )
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR} )


add_executable(main alg101.cpp)
add_executable(test alg10.cpp)
target_link_libraries(main gtest_main gmock gmock_main pthread)
target_link_libraries(test gtest_main gmock gmock_main pthread)