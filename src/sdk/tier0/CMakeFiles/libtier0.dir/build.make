# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/never/Downloads/clion-2018.2.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/never/Downloads/clion-2018.2.3/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/never/CLionProjects/pixelpai/src/sdk/tier0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/never/CLionProjects/pixelpai/src/sdk/tier0

# Include any dependencies generated for this target.
include CMakeFiles/libtier0.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/libtier0.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/libtier0.dir/flags.make

CMakeFiles/libtier0.dir/platform_linux.cpp.o: CMakeFiles/libtier0.dir/flags.make
CMakeFiles/libtier0.dir/platform_linux.cpp.o: platform_linux.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/never/CLionProjects/pixelpai/src/sdk/tier0/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/libtier0.dir/platform_linux.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libtier0.dir/platform_linux.cpp.o -c /home/never/CLionProjects/pixelpai/src/sdk/tier0/platform_linux.cpp

CMakeFiles/libtier0.dir/platform_linux.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libtier0.dir/platform_linux.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/never/CLionProjects/pixelpai/src/sdk/tier0/platform_linux.cpp > CMakeFiles/libtier0.dir/platform_linux.cpp.i

CMakeFiles/libtier0.dir/platform_linux.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libtier0.dir/platform_linux.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/never/CLionProjects/pixelpai/src/sdk/tier0/platform_linux.cpp -o CMakeFiles/libtier0.dir/platform_linux.cpp.s

CMakeFiles/libtier0.dir/dbg.cpp.o: CMakeFiles/libtier0.dir/flags.make
CMakeFiles/libtier0.dir/dbg.cpp.o: dbg.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/never/CLionProjects/pixelpai/src/sdk/tier0/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/libtier0.dir/dbg.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libtier0.dir/dbg.cpp.o -c /home/never/CLionProjects/pixelpai/src/sdk/tier0/dbg.cpp

CMakeFiles/libtier0.dir/dbg.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libtier0.dir/dbg.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/never/CLionProjects/pixelpai/src/sdk/tier0/dbg.cpp > CMakeFiles/libtier0.dir/dbg.cpp.i

CMakeFiles/libtier0.dir/dbg.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libtier0.dir/dbg.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/never/CLionProjects/pixelpai/src/sdk/tier0/dbg.cpp -o CMakeFiles/libtier0.dir/dbg.cpp.s

CMakeFiles/libtier0.dir/mem.cpp.o: CMakeFiles/libtier0.dir/flags.make
CMakeFiles/libtier0.dir/mem.cpp.o: mem.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/never/CLionProjects/pixelpai/src/sdk/tier0/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/libtier0.dir/mem.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libtier0.dir/mem.cpp.o -c /home/never/CLionProjects/pixelpai/src/sdk/tier0/mem.cpp

CMakeFiles/libtier0.dir/mem.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libtier0.dir/mem.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/never/CLionProjects/pixelpai/src/sdk/tier0/mem.cpp > CMakeFiles/libtier0.dir/mem.cpp.i

CMakeFiles/libtier0.dir/mem.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libtier0.dir/mem.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/never/CLionProjects/pixelpai/src/sdk/tier0/mem.cpp -o CMakeFiles/libtier0.dir/mem.cpp.s

CMakeFiles/libtier0.dir/memstd.cpp.o: CMakeFiles/libtier0.dir/flags.make
CMakeFiles/libtier0.dir/memstd.cpp.o: memstd.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/never/CLionProjects/pixelpai/src/sdk/tier0/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/libtier0.dir/memstd.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libtier0.dir/memstd.cpp.o -c /home/never/CLionProjects/pixelpai/src/sdk/tier0/memstd.cpp

CMakeFiles/libtier0.dir/memstd.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libtier0.dir/memstd.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/never/CLionProjects/pixelpai/src/sdk/tier0/memstd.cpp > CMakeFiles/libtier0.dir/memstd.cpp.i

CMakeFiles/libtier0.dir/memstd.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libtier0.dir/memstd.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/never/CLionProjects/pixelpai/src/sdk/tier0/memstd.cpp -o CMakeFiles/libtier0.dir/memstd.cpp.s

CMakeFiles/libtier0.dir/security_linux.cpp.o: CMakeFiles/libtier0.dir/flags.make
CMakeFiles/libtier0.dir/security_linux.cpp.o: security_linux.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/never/CLionProjects/pixelpai/src/sdk/tier0/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/libtier0.dir/security_linux.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libtier0.dir/security_linux.cpp.o -c /home/never/CLionProjects/pixelpai/src/sdk/tier0/security_linux.cpp

CMakeFiles/libtier0.dir/security_linux.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libtier0.dir/security_linux.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/never/CLionProjects/pixelpai/src/sdk/tier0/security_linux.cpp > CMakeFiles/libtier0.dir/security_linux.cpp.i

CMakeFiles/libtier0.dir/security_linux.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libtier0.dir/security_linux.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/never/CLionProjects/pixelpai/src/sdk/tier0/security_linux.cpp -o CMakeFiles/libtier0.dir/security_linux.cpp.s

CMakeFiles/libtier0.dir/recording.cpp.o: CMakeFiles/libtier0.dir/flags.make
CMakeFiles/libtier0.dir/recording.cpp.o: recording.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/never/CLionProjects/pixelpai/src/sdk/tier0/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/libtier0.dir/recording.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libtier0.dir/recording.cpp.o -c /home/never/CLionProjects/pixelpai/src/sdk/tier0/recording.cpp

CMakeFiles/libtier0.dir/recording.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libtier0.dir/recording.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/never/CLionProjects/pixelpai/src/sdk/tier0/recording.cpp > CMakeFiles/libtier0.dir/recording.cpp.i

CMakeFiles/libtier0.dir/recording.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libtier0.dir/recording.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/never/CLionProjects/pixelpai/src/sdk/tier0/recording.cpp -o CMakeFiles/libtier0.dir/recording.cpp.s

# Object files for target libtier0
libtier0_OBJECTS = \
"CMakeFiles/libtier0.dir/platform_linux.cpp.o" \
"CMakeFiles/libtier0.dir/dbg.cpp.o" \
"CMakeFiles/libtier0.dir/mem.cpp.o" \
"CMakeFiles/libtier0.dir/memstd.cpp.o" \
"CMakeFiles/libtier0.dir/security_linux.cpp.o" \
"CMakeFiles/libtier0.dir/recording.cpp.o"

# External object files for target libtier0
libtier0_EXTERNAL_OBJECTS =

lib/liblibtier0.so: CMakeFiles/libtier0.dir/platform_linux.cpp.o
lib/liblibtier0.so: CMakeFiles/libtier0.dir/dbg.cpp.o
lib/liblibtier0.so: CMakeFiles/libtier0.dir/mem.cpp.o
lib/liblibtier0.so: CMakeFiles/libtier0.dir/memstd.cpp.o
lib/liblibtier0.so: CMakeFiles/libtier0.dir/security_linux.cpp.o
lib/liblibtier0.so: CMakeFiles/libtier0.dir/recording.cpp.o
lib/liblibtier0.so: CMakeFiles/libtier0.dir/build.make
lib/liblibtier0.so: CMakeFiles/libtier0.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/never/CLionProjects/pixelpai/src/sdk/tier0/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX shared library lib/liblibtier0.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/libtier0.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/libtier0.dir/build: lib/liblibtier0.so

.PHONY : CMakeFiles/libtier0.dir/build

CMakeFiles/libtier0.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/libtier0.dir/cmake_clean.cmake
.PHONY : CMakeFiles/libtier0.dir/clean

CMakeFiles/libtier0.dir/depend:
	cd /home/never/CLionProjects/pixelpai/src/sdk/tier0 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/never/CLionProjects/pixelpai/src/sdk/tier0 /home/never/CLionProjects/pixelpai/src/sdk/tier0 /home/never/CLionProjects/pixelpai/src/sdk/tier0 /home/never/CLionProjects/pixelpai/src/sdk/tier0 /home/never/CLionProjects/pixelpai/src/sdk/tier0/CMakeFiles/libtier0.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/libtier0.dir/depend
