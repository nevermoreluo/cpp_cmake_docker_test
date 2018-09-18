cmake_minimum_required(VERSION 3.10)
project(launcher)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)

include_directories(../sdk)
include_directories(../sdk/value/public)
include_directories(../sdk/common)
include_directories(../sdk/pogo)
include_directories(../common)
add_library(launcher SHARED logsystem.cpp game.cpp module.cpp console_linux.cpp)
