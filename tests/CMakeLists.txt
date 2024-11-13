project(HuffmanFileZipperTests)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

file(GLOB TEST_SRC *.cpp)
add_executable(HuffmanFileZipperTests ${TEST_SRC})
target_link_libraries(HuffmanFileZipperTests HuffmanFileZipper_lib)
target_link_libraries(HuffmanFileZipperTests gtest gtest_main)
