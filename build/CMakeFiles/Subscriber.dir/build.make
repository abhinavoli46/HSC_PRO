# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/linos/Client-Server-Model

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/linos/Client-Server-Model/build

# Include any dependencies generated for this target.
include CMakeFiles/Subscriber.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Subscriber.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Subscriber.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Subscriber.dir/flags.make

CMakeFiles/Subscriber.dir/src/subscriber.cpp.o: CMakeFiles/Subscriber.dir/flags.make
CMakeFiles/Subscriber.dir/src/subscriber.cpp.o: ../src/subscriber.cpp
CMakeFiles/Subscriber.dir/src/subscriber.cpp.o: CMakeFiles/Subscriber.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/linos/Client-Server-Model/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Subscriber.dir/src/subscriber.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Subscriber.dir/src/subscriber.cpp.o -MF CMakeFiles/Subscriber.dir/src/subscriber.cpp.o.d -o CMakeFiles/Subscriber.dir/src/subscriber.cpp.o -c /home/linos/Client-Server-Model/src/subscriber.cpp

CMakeFiles/Subscriber.dir/src/subscriber.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Subscriber.dir/src/subscriber.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/linos/Client-Server-Model/src/subscriber.cpp > CMakeFiles/Subscriber.dir/src/subscriber.cpp.i

CMakeFiles/Subscriber.dir/src/subscriber.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Subscriber.dir/src/subscriber.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/linos/Client-Server-Model/src/subscriber.cpp -o CMakeFiles/Subscriber.dir/src/subscriber.cpp.s

CMakeFiles/Subscriber.dir/src/framepack.cpp.o: CMakeFiles/Subscriber.dir/flags.make
CMakeFiles/Subscriber.dir/src/framepack.cpp.o: ../src/framepack.cpp
CMakeFiles/Subscriber.dir/src/framepack.cpp.o: CMakeFiles/Subscriber.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/linos/Client-Server-Model/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Subscriber.dir/src/framepack.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Subscriber.dir/src/framepack.cpp.o -MF CMakeFiles/Subscriber.dir/src/framepack.cpp.o.d -o CMakeFiles/Subscriber.dir/src/framepack.cpp.o -c /home/linos/Client-Server-Model/src/framepack.cpp

CMakeFiles/Subscriber.dir/src/framepack.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Subscriber.dir/src/framepack.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/linos/Client-Server-Model/src/framepack.cpp > CMakeFiles/Subscriber.dir/src/framepack.cpp.i

CMakeFiles/Subscriber.dir/src/framepack.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Subscriber.dir/src/framepack.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/linos/Client-Server-Model/src/framepack.cpp -o CMakeFiles/Subscriber.dir/src/framepack.cpp.s

# Object files for target Subscriber
Subscriber_OBJECTS = \
"CMakeFiles/Subscriber.dir/src/subscriber.cpp.o" \
"CMakeFiles/Subscriber.dir/src/framepack.cpp.o"

# External object files for target Subscriber
Subscriber_EXTERNAL_OBJECTS =

Subscriber: CMakeFiles/Subscriber.dir/src/subscriber.cpp.o
Subscriber: CMakeFiles/Subscriber.dir/src/framepack.cpp.o
Subscriber: CMakeFiles/Subscriber.dir/build.make
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_img_hash.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: /usr/local/lib/libzmq.so
Subscriber: /usr/local/lib/libopencv_world.so.4.8.0
Subscriber: CMakeFiles/Subscriber.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/linos/Client-Server-Model/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Subscriber"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Subscriber.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Subscriber.dir/build: Subscriber
.PHONY : CMakeFiles/Subscriber.dir/build

CMakeFiles/Subscriber.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Subscriber.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Subscriber.dir/clean

CMakeFiles/Subscriber.dir/depend:
	cd /home/linos/Client-Server-Model/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/linos/Client-Server-Model /home/linos/Client-Server-Model /home/linos/Client-Server-Model/build /home/linos/Client-Server-Model/build /home/linos/Client-Server-Model/build/CMakeFiles/Subscriber.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Subscriber.dir/depend
