project(sudoku)
cmake_minimum_required(VERSION 2.6)
find_package(Qt5Core REQUIRED)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${Qt5Core_INCLUDE_DIRS})
add_definitions(${Qt5Core_DEFINITIONS})


set(sudoku_SRCS main.cpp sudoku.cpp validator.cpp)
add_executable(sudoku ${sudoku_SRCS})

install(TARGETS sudoku RUNTIME DESTINATION bin)
set(CMAKE_CXX_FLAGS "--std=c++11 -O2 ${Qt5Core_EXECUTABLE_COMPILE_FLAGS}")

target_link_libraries(sudoku ${Qt5Core_LIBRARIES})
