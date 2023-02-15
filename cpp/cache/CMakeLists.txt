cmake_minimum_required(VERSION 3.14)

project(test_cache)

add_executable(test_cache test_cache.cc cache.cc lru_cache.cc)

target_compile_features(test_cache PRIVATE cxx_std_14)
