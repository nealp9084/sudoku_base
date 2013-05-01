project(sudoku)
cmake_minimum_required(VERSION 2.6)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(sudoku_SRCS main.cpp sudoku.cpp validator.cpp grid.cpp)
add_executable(sudoku ${sudoku_SRCS})

install(TARGETS sudoku RUNTIME DESTINATION bin)
set(CMAKE_CXX_FLAGS "--std=c++11 -O2")
