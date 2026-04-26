cmake_minimum_required(VERSION 3.10)
project(liblinal_testing LANGUAGES C)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS_DEBUG "-O0 -g")

add_executable(liblinal_testing src/main.c src/vectors/la_vectors.c tests/vectors/vector_tests.c)
target_include_directories(liblinal_testing PRIVATE include/liblinal)
target_compile_features(liblinal_testing PRIVATE c_std_17)
target_compile_options(liblinal_testing PRIVATE -Wall -Wextra)

