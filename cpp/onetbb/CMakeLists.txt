cmake_minimum_required(VERSION 3.10)

project(tbb-test CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(TBB REQUIRED)

if (NOT TBB_FOUND)
    message(FATAL_ERROR "TBB Required")
endif()

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

add_executable(main multi_function.cc)
#add_executable(main sub_graph.cc)

target_link_libraries(main TBB::tbb)

