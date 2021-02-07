cmake_minimum_required(VERSION 3.16)
project(Temp)

set(CMAKE_CXX_STANDARD 14)

include_directories(adns_src)

file(GLOB_RECURSE src "adns_src/*.c")

add_executable(temp Temp.cpp ${src})