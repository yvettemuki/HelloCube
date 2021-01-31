# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/yvettemuki/Documents/code/OpenGL/cube_shader

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/yvettemuki/Documents/code/OpenGL/cube_shader/build

# Include any dependencies generated for this target.
include CMakeFiles/cube_shader.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cube_shader.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cube_shader.dir/flags.make

CMakeFiles/cube_shader.dir/src/glad.c.o: CMakeFiles/cube_shader.dir/flags.make
CMakeFiles/cube_shader.dir/src/glad.c.o: ../src/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/yvettemuki/Documents/code/OpenGL/cube_shader/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/cube_shader.dir/src/glad.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cube_shader.dir/src/glad.c.o -c /Users/yvettemuki/Documents/code/OpenGL/cube_shader/src/glad.c

CMakeFiles/cube_shader.dir/src/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cube_shader.dir/src/glad.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/yvettemuki/Documents/code/OpenGL/cube_shader/src/glad.c > CMakeFiles/cube_shader.dir/src/glad.c.i

CMakeFiles/cube_shader.dir/src/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cube_shader.dir/src/glad.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/yvettemuki/Documents/code/OpenGL/cube_shader/src/glad.c -o CMakeFiles/cube_shader.dir/src/glad.c.s

CMakeFiles/cube_shader.dir/main.cpp.o: CMakeFiles/cube_shader.dir/flags.make
CMakeFiles/cube_shader.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/yvettemuki/Documents/code/OpenGL/cube_shader/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/cube_shader.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cube_shader.dir/main.cpp.o -c /Users/yvettemuki/Documents/code/OpenGL/cube_shader/main.cpp

CMakeFiles/cube_shader.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cube_shader.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/yvettemuki/Documents/code/OpenGL/cube_shader/main.cpp > CMakeFiles/cube_shader.dir/main.cpp.i

CMakeFiles/cube_shader.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cube_shader.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/yvettemuki/Documents/code/OpenGL/cube_shader/main.cpp -o CMakeFiles/cube_shader.dir/main.cpp.s

# Object files for target cube_shader
cube_shader_OBJECTS = \
"CMakeFiles/cube_shader.dir/src/glad.c.o" \
"CMakeFiles/cube_shader.dir/main.cpp.o"

# External object files for target cube_shader
cube_shader_EXTERNAL_OBJECTS =

cube_shader: CMakeFiles/cube_shader.dir/src/glad.c.o
cube_shader: CMakeFiles/cube_shader.dir/main.cpp.o
cube_shader: CMakeFiles/cube_shader.dir/build.make
cube_shader: /usr/local/Cellar/glew/2.2.0/lib/libGLEW.2.2.dylib
cube_shader: /usr/local/Cellar/glfw/3.3.2/lib/libglfw.3.dylib
cube_shader: CMakeFiles/cube_shader.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/yvettemuki/Documents/code/OpenGL/cube_shader/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable cube_shader"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cube_shader.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cube_shader.dir/build: cube_shader

.PHONY : CMakeFiles/cube_shader.dir/build

CMakeFiles/cube_shader.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cube_shader.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cube_shader.dir/clean

CMakeFiles/cube_shader.dir/depend:
	cd /Users/yvettemuki/Documents/code/OpenGL/cube_shader/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/yvettemuki/Documents/code/OpenGL/cube_shader /Users/yvettemuki/Documents/code/OpenGL/cube_shader /Users/yvettemuki/Documents/code/OpenGL/cube_shader/build /Users/yvettemuki/Documents/code/OpenGL/cube_shader/build /Users/yvettemuki/Documents/code/OpenGL/cube_shader/build/CMakeFiles/cube_shader.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cube_shader.dir/depend

