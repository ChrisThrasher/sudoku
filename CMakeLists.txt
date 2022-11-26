cmake_minimum_required(VERSION 3.22)
project(sudoku-solver CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "(GNU|Clang)")
    add_compile_options(-ffast-math -Werror -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Wold-style-cast)
elseif(MSVC)
    add_compile_options(/WX /W4 /permissive-)
endif()

add_executable(sudoku-solver src/sudoku-solver.cpp)
target_compile_features(sudoku-solver PRIVATE cxx_std_17)

add_custom_target(format
    COMMAND clang-format -i `git ls-files *.hpp *.cpp`
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
add_custom_target(tidy
    COMMAND run-clang-tidy -p ${CMAKE_BINARY_DIR} `git ls-files *.cpp`
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
add_custom_target(run
    COMMAND sudoku-solver
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
