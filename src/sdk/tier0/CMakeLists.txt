cmake_minimum_required(VERSION 3.12)
project(libtier0)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--export-all-symbols")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


add_library(libtier0 SHARED platform_linux.cpp dbg.cpp mem.cpp memstd.cpp security_linux.cpp recording.cpp)

