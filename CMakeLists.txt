cmake_minimum_required(VERSION 3.25)
project(ProjectSafe)

set(CMAKE_CXX_STANDARD 20)

find_package(cryptopp CONFIG REQUIRED)

add_executable(ProjectSafe src/main.cpp)

target_link_libraries(ProjectSafe PRIVATE cryptopp::cryptopp)