cmake_minimum_required(VERSION 3.16)

project(RateLimiter)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_library(rate_limiter src/RateLimiter.cpp)

add_executable(main src/main.cpp)
target_link_libraries(main rate_limiter)

add_executable(rate_limiter_tests tests/RateLimiterTest.cpp)
target_link_libraries(rate_limiter_tests rate_limiter)