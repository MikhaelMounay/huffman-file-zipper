cmake_minimum_required(VERSION 3.14)
project(HuffmanFileZipperTests)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/d144031940543e15423a25ae5a8a74141044862f.zip
        DOWNLOAD_EXTRACT_TIMESTAMP 1
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


file(GLOB TEST_SRC *.cpp)
add_executable(HuffmanFileZipperTests ${TEST_SRC})
target_link_libraries(HuffmanFileZipperTests HuffmanFileZipper_lib)
target_link_libraries(HuffmanFileZipperTests gtest gtest_main)
