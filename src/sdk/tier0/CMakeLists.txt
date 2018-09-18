cmake_minimum_required(VERSION 3.10)
project(libtier0)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)

include_directories(../)
include_directories(../common)
add_library(libtier0 SHARED platform_linux.cpp dbg.cpp mem.cpp memstd.cpp security_linux.cpp recording.cpp)

