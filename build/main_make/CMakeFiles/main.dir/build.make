# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/never/CLionProjects/pixelpai/src/main

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/never/CLionProjects/pixelpai/build/main_make

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/main.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/main.cpp.o: /home/never/CLionProjects/pixelpai/src/main/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/never/CLionProjects/pixelpai/build/main_make/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/main.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/main.cpp.o -c /home/never/CLionProjects/pixelpai/src/main/main.cpp

CMakeFiles/main.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/never/CLionProjects/pixelpai/src/main/main.cpp > CMakeFiles/main.dir/main.cpp.i

CMakeFiles/main.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/never/CLionProjects/pixelpai/src/main/main.cpp -o CMakeFiles/main.dir/main.cpp.s

CMakeFiles/main.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/main.dir/main.cpp.o.requires

CMakeFiles/main.dir/main.cpp.o.provides: CMakeFiles/main.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/main.dir/main.cpp.o.provides

CMakeFiles/main.dir/main.cpp.o.provides.build: CMakeFiles/main.dir/main.cpp.o


CMakeFiles/main.dir/logsystem.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/logsystem.cpp.o: /home/never/CLionProjects/pixelpai/src/main/logsystem.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/never/CLionProjects/pixelpai/build/main_make/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/main.dir/logsystem.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/logsystem.cpp.o -c /home/never/CLionProjects/pixelpai/src/main/logsystem.cpp

CMakeFiles/main.dir/logsystem.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/logsystem.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/never/CLionProjects/pixelpai/src/main/logsystem.cpp > CMakeFiles/main.dir/logsystem.cpp.i

CMakeFiles/main.dir/logsystem.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/logsystem.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/never/CLionProjects/pixelpai/src/main/logsystem.cpp -o CMakeFiles/main.dir/logsystem.cpp.s

CMakeFiles/main.dir/logsystem.cpp.o.requires:

.PHONY : CMakeFiles/main.dir/logsystem.cpp.o.requires

CMakeFiles/main.dir/logsystem.cpp.o.provides: CMakeFiles/main.dir/logsystem.cpp.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/logsystem.cpp.o.provides.build
.PHONY : CMakeFiles/main.dir/logsystem.cpp.o.provides

CMakeFiles/main.dir/logsystem.cpp.o.provides.build: CMakeFiles/main.dir/logsystem.cpp.o


CMakeFiles/main.dir/game.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/game.cpp.o: /home/never/CLionProjects/pixelpai/src/main/game.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/never/CLionProjects/pixelpai/build/main_make/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/main.dir/game.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/game.cpp.o -c /home/never/CLionProjects/pixelpai/src/main/game.cpp

CMakeFiles/main.dir/game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/game.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/never/CLionProjects/pixelpai/src/main/game.cpp > CMakeFiles/main.dir/game.cpp.i

CMakeFiles/main.dir/game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/game.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/never/CLionProjects/pixelpai/src/main/game.cpp -o CMakeFiles/main.dir/game.cpp.s

CMakeFiles/main.dir/game.cpp.o.requires:

.PHONY : CMakeFiles/main.dir/game.cpp.o.requires

CMakeFiles/main.dir/game.cpp.o.provides: CMakeFiles/main.dir/game.cpp.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/game.cpp.o.provides.build
.PHONY : CMakeFiles/main.dir/game.cpp.o.provides

CMakeFiles/main.dir/game.cpp.o.provides.build: CMakeFiles/main.dir/game.cpp.o


CMakeFiles/main.dir/module.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/module.cpp.o: /home/never/CLionProjects/pixelpai/src/main/module.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/never/CLionProjects/pixelpai/build/main_make/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/main.dir/module.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/module.cpp.o -c /home/never/CLionProjects/pixelpai/src/main/module.cpp

CMakeFiles/main.dir/module.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/module.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/never/CLionProjects/pixelpai/src/main/module.cpp > CMakeFiles/main.dir/module.cpp.i

CMakeFiles/main.dir/module.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/module.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/never/CLionProjects/pixelpai/src/main/module.cpp -o CMakeFiles/main.dir/module.cpp.s

CMakeFiles/main.dir/module.cpp.o.requires:

.PHONY : CMakeFiles/main.dir/module.cpp.o.requires

CMakeFiles/main.dir/module.cpp.o.provides: CMakeFiles/main.dir/module.cpp.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/module.cpp.o.provides.build
.PHONY : CMakeFiles/main.dir/module.cpp.o.provides

CMakeFiles/main.dir/module.cpp.o.provides.build: CMakeFiles/main.dir/module.cpp.o


CMakeFiles/main.dir/console_linux.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/console_linux.cpp.o: /home/never/CLionProjects/pixelpai/src/main/console_linux.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/never/CLionProjects/pixelpai/build/main_make/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/main.dir/console_linux.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/console_linux.cpp.o -c /home/never/CLionProjects/pixelpai/src/main/console_linux.cpp

CMakeFiles/main.dir/console_linux.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/console_linux.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/never/CLionProjects/pixelpai/src/main/console_linux.cpp > CMakeFiles/main.dir/console_linux.cpp.i

CMakeFiles/main.dir/console_linux.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/console_linux.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/never/CLionProjects/pixelpai/src/main/console_linux.cpp -o CMakeFiles/main.dir/console_linux.cpp.s

CMakeFiles/main.dir/console_linux.cpp.o.requires:

.PHONY : CMakeFiles/main.dir/console_linux.cpp.o.requires

CMakeFiles/main.dir/console_linux.cpp.o.provides: CMakeFiles/main.dir/console_linux.cpp.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/console_linux.cpp.o.provides.build
.PHONY : CMakeFiles/main.dir/console_linux.cpp.o.provides

CMakeFiles/main.dir/console_linux.cpp.o.provides.build: CMakeFiles/main.dir/console_linux.cpp.o


# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/main.cpp.o" \
"CMakeFiles/main.dir/logsystem.cpp.o" \
"CMakeFiles/main.dir/game.cpp.o" \
"CMakeFiles/main.dir/module.cpp.o" \
"CMakeFiles/main.dir/console_linux.cpp.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

/home/never/CLionProjects/pixelpai/build/bin/main: CMakeFiles/main.dir/main.cpp.o
/home/never/CLionProjects/pixelpai/build/bin/main: CMakeFiles/main.dir/logsystem.cpp.o
/home/never/CLionProjects/pixelpai/build/bin/main: CMakeFiles/main.dir/game.cpp.o
/home/never/CLionProjects/pixelpai/build/bin/main: CMakeFiles/main.dir/module.cpp.o
/home/never/CLionProjects/pixelpai/build/bin/main: CMakeFiles/main.dir/console_linux.cpp.o
/home/never/CLionProjects/pixelpai/build/bin/main: CMakeFiles/main.dir/build.make
/home/never/CLionProjects/pixelpai/build/bin/main: /home/never/CLionProjects/pixelpai/build/lib/libpogo.a
/home/never/CLionProjects/pixelpai/build/bin/main: /home/never/CLionProjects/pixelpai/build/lib/libtier0.a
/home/never/CLionProjects/pixelpai/build/bin/main: /home/never/CLionProjects/pixelpai/build/lib/libcommon.a
/home/never/CLionProjects/pixelpai/build/bin/main: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/never/CLionProjects/pixelpai/build/main_make/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable /home/never/CLionProjects/pixelpai/build/bin/main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: /home/never/CLionProjects/pixelpai/build/bin/main

.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/requires: CMakeFiles/main.dir/main.cpp.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/logsystem.cpp.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/game.cpp.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/module.cpp.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/console_linux.cpp.o.requires

.PHONY : CMakeFiles/main.dir/requires

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	cd /home/never/CLionProjects/pixelpai/build/main_make && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/never/CLionProjects/pixelpai/src/main /home/never/CLionProjects/pixelpai/src/main /home/never/CLionProjects/pixelpai/build/main_make /home/never/CLionProjects/pixelpai/build/main_make /home/never/CLionProjects/pixelpai/build/main_make/CMakeFiles/main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main.dir/depend

