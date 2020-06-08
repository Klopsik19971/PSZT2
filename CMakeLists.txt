cmake_minimum_required(VERSION 3.0)

set(CMAKE_MODULE_PATH  ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

project(PSZT2)
set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

include_directories(inc)
add_executable(PSZT2 src/main.cc src/data_read.cc inc/data_read.hpp src/sort_col.cc inc/sort_col.hpp inc/common.hpp src/tree_ptr.cc inc/tree_ptr.hpp src/calculate_gini.cc inc/calculate_gini.hpp src/decision_tree.cc inc/decision_tree.hpp)
