cmake_minimum_required(VERSION 3.10)
project(tier0)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)

include_directories(../)
include_directories(../common)
add_library(tier0 STATIC extendedtrace.cpp memdbg.cpp memoverride.cpp memvalidate.cpp platform_linux.cpp platform_linux.cpp dbg.cpp mem.cpp memstd.cpp security_linux.cpp recording.cpp)

target_link_libraries(tier0 ${CMAKE_DL_LIBS})
