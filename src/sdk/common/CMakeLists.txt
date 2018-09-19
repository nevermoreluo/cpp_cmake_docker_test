cmake_minimum_required(VERSION 3.10)
project(common)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)


add_library(common STATIC vstdlib/commandline.cpp vstdlib/strtools.cpp filesystem.cpp interface.cpp launcher.cpp utlsymbol.cpp)

target_link_libraries(common ${CMAKE_DL_LIBS})