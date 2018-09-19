cmake_minimum_required(VERSION 3.10)
project(main)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

include_directories(../sdk)
include_directories(../sdk/common)
include_directories(../sdk/pogo)
include_directories(../common)


add_subdirectory(../sdk/pogo ../../build/pogo.out)
add_subdirectory(../sdk/tier0 ../../build/tier0.out)
add_subdirectory(../sdk/common ../../build/common.out)

add_executable(main main.cpp logsystem.cpp game.cpp module.cpp console_linux.cpp)


target_link_libraries(main ${CMAKE_DL_LIBS} pogo tier0 common)
