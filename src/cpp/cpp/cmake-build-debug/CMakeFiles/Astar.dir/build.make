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
CMAKE_COMMAND = /opt/clion/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/fux/projects/pycharm/maze-solver/src/cpp/cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/fux/projects/pycharm/maze-solver/src/cpp/cpp/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Astar.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Astar.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Astar.dir/flags.make

CMakeFiles/Astar.dir/AStar.cpp.o: CMakeFiles/Astar.dir/flags.make
CMakeFiles/Astar.dir/AStar.cpp.o: ../AStar.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fux/projects/pycharm/maze-solver/src/cpp/cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Astar.dir/AStar.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Astar.dir/AStar.cpp.o -c /home/fux/projects/pycharm/maze-solver/src/cpp/cpp/AStar.cpp

CMakeFiles/Astar.dir/AStar.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Astar.dir/AStar.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/fux/projects/pycharm/maze-solver/src/cpp/cpp/AStar.cpp > CMakeFiles/Astar.dir/AStar.cpp.i

CMakeFiles/Astar.dir/AStar.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Astar.dir/AStar.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/fux/projects/pycharm/maze-solver/src/cpp/cpp/AStar.cpp -o CMakeFiles/Astar.dir/AStar.cpp.s

# Object files for target Astar
Astar_OBJECTS = \
"CMakeFiles/Astar.dir/AStar.cpp.o"

# External object files for target Astar
Astar_EXTERNAL_OBJECTS =

libAstar.a: CMakeFiles/Astar.dir/AStar.cpp.o
libAstar.a: CMakeFiles/Astar.dir/build.make
libAstar.a: CMakeFiles/Astar.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/fux/projects/pycharm/maze-solver/src/cpp/cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libAstar.a"
	$(CMAKE_COMMAND) -P CMakeFiles/Astar.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Astar.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Astar.dir/build: libAstar.a

.PHONY : CMakeFiles/Astar.dir/build

CMakeFiles/Astar.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Astar.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Astar.dir/clean

CMakeFiles/Astar.dir/depend:
	cd /home/fux/projects/pycharm/maze-solver/src/cpp/cpp/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fux/projects/pycharm/maze-solver/src/cpp/cpp /home/fux/projects/pycharm/maze-solver/src/cpp/cpp /home/fux/projects/pycharm/maze-solver/src/cpp/cpp/cmake-build-debug /home/fux/projects/pycharm/maze-solver/src/cpp/cpp/cmake-build-debug /home/fux/projects/pycharm/maze-solver/src/cpp/cpp/cmake-build-debug/CMakeFiles/Astar.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Astar.dir/depend

