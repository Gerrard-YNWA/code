cmake_minimum_required(VERSION 3.14)

project(ntp_client)

find_package(Boost REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

add_executable(ntp_client_main main.cc client.cc)
target_compile_features(ntp_client_main PRIVATE cxx_std_11)
