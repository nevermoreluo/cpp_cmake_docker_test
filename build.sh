#!/bin/bash

cmake_build_path=/opt/output/cmake-build

mkdir -p $cmake_build_path

cd $cmake_build_path && cmake -DCMAKE_BUILD_TYPE=Release -G "CodeBlocks - Unix Makefiles" .. && cmake --build $cmake_build_path --target cpp_test -- -j 4 && make && echo -e "\n--------Run cpp_test--------" && $cmake_build_path/bin/cpp_test

