# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/astlok/Documents/IT/AaDS/zadacha_1_1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/astlok/Documents/IT/AaDS/zadacha_1_1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/AaDS.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/AaDS.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/AaDS.dir/flags.make

CMakeFiles/AaDS.dir/src/main.cpp.o: CMakeFiles/AaDS.dir/flags.make
CMakeFiles/AaDS.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/astlok/Documents/IT/AaDS/zadacha_1_1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/AaDS.dir/src/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AaDS.dir/src/main.cpp.o -c /Users/astlok/Documents/IT/AaDS/zadacha_1_1/src/main.cpp

CMakeFiles/AaDS.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AaDS.dir/src/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/astlok/Documents/IT/AaDS/zadacha_1_1/src/main.cpp > CMakeFiles/AaDS.dir/src/main.cpp.i

CMakeFiles/AaDS.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AaDS.dir/src/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/astlok/Documents/IT/AaDS/zadacha_1_1/src/main.cpp -o CMakeFiles/AaDS.dir/src/main.cpp.s

CMakeFiles/AaDS.dir/src/max_sum_index.cpp.o: CMakeFiles/AaDS.dir/flags.make
CMakeFiles/AaDS.dir/src/max_sum_index.cpp.o: ../src/max_sum_index.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/astlok/Documents/IT/AaDS/zadacha_1_1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/AaDS.dir/src/max_sum_index.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AaDS.dir/src/max_sum_index.cpp.o -c /Users/astlok/Documents/IT/AaDS/zadacha_1_1/src/max_sum_index.cpp

CMakeFiles/AaDS.dir/src/max_sum_index.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AaDS.dir/src/max_sum_index.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/astlok/Documents/IT/AaDS/zadacha_1_1/src/max_sum_index.cpp > CMakeFiles/AaDS.dir/src/max_sum_index.cpp.i

CMakeFiles/AaDS.dir/src/max_sum_index.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AaDS.dir/src/max_sum_index.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/astlok/Documents/IT/AaDS/zadacha_1_1/src/max_sum_index.cpp -o CMakeFiles/AaDS.dir/src/max_sum_index.cpp.s

# Object files for target AaDS
AaDS_OBJECTS = \
"CMakeFiles/AaDS.dir/src/main.cpp.o" \
"CMakeFiles/AaDS.dir/src/max_sum_index.cpp.o"

# External object files for target AaDS
AaDS_EXTERNAL_OBJECTS =

AaDS: CMakeFiles/AaDS.dir/src/main.cpp.o
AaDS: CMakeFiles/AaDS.dir/src/max_sum_index.cpp.o
AaDS: CMakeFiles/AaDS.dir/build.make
AaDS: CMakeFiles/AaDS.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/astlok/Documents/IT/AaDS/zadacha_1_1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable AaDS"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AaDS.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/AaDS.dir/build: AaDS

.PHONY : CMakeFiles/AaDS.dir/build

CMakeFiles/AaDS.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/AaDS.dir/cmake_clean.cmake
.PHONY : CMakeFiles/AaDS.dir/clean

CMakeFiles/AaDS.dir/depend:
	cd /Users/astlok/Documents/IT/AaDS/zadacha_1_1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/astlok/Documents/IT/AaDS/zadacha_1_1 /Users/astlok/Documents/IT/AaDS/zadacha_1_1 /Users/astlok/Documents/IT/AaDS/zadacha_1_1/cmake-build-debug /Users/astlok/Documents/IT/AaDS/zadacha_1_1/cmake-build-debug /Users/astlok/Documents/IT/AaDS/zadacha_1_1/cmake-build-debug/CMakeFiles/AaDS.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/AaDS.dir/depend

