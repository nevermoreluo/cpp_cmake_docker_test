cmake_minimum_required(VERSION 3.10)
project(pogo)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)

include_directories(../)
include_directories(../common)
include_directories(../value/public)
add_library(pogo STATIC Exception.cpp IdGenerator.cpp PogoUtils.cpp PropsUtils.cpp Properties.cpp TenProps.cpp Version.cpp ../common/interface.cpp)

target_link_libraries(pogo ${CMAKE_DL_LIBS})
