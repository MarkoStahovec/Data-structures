# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Users\A\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\202.7319.72\bin\cmake\win\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\A\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\202.7319.72\bin\cmake\win\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\A\CLionProjects\untitled

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\A\CLionProjects\untitled\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ADT_stack.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ADT_stack.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ADT_stack.dir/flags.make

CMakeFiles/ADT_stack.dir/ADT_stack.c.obj: CMakeFiles/ADT_stack.dir/flags.make
CMakeFiles/ADT_stack.dir/ADT_stack.c.obj: ../ADT_stack.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\A\CLionProjects\untitled\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ADT_stack.dir/ADT_stack.c.obj"
	C:\TDM-GCC-64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\ADT_stack.dir\ADT_stack.c.obj   -c C:\Users\A\CLionProjects\untitled\ADT_stack.c

CMakeFiles/ADT_stack.dir/ADT_stack.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ADT_stack.dir/ADT_stack.c.i"
	C:\TDM-GCC-64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\A\CLionProjects\untitled\ADT_stack.c > CMakeFiles\ADT_stack.dir\ADT_stack.c.i

CMakeFiles/ADT_stack.dir/ADT_stack.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ADT_stack.dir/ADT_stack.c.s"
	C:\TDM-GCC-64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\A\CLionProjects\untitled\ADT_stack.c -o CMakeFiles\ADT_stack.dir\ADT_stack.c.s

# Object files for target ADT_stack
ADT_stack_OBJECTS = \
"CMakeFiles/ADT_stack.dir/ADT_stack.c.obj"

# External object files for target ADT_stack
ADT_stack_EXTERNAL_OBJECTS =

ADT_stack.exe: CMakeFiles/ADT_stack.dir/ADT_stack.c.obj
ADT_stack.exe: CMakeFiles/ADT_stack.dir/build.make
ADT_stack.exe: CMakeFiles/ADT_stack.dir/linklibs.rsp
ADT_stack.exe: CMakeFiles/ADT_stack.dir/objects1.rsp
ADT_stack.exe: CMakeFiles/ADT_stack.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\A\CLionProjects\untitled\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ADT_stack.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\ADT_stack.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ADT_stack.dir/build: ADT_stack.exe

.PHONY : CMakeFiles/ADT_stack.dir/build

CMakeFiles/ADT_stack.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\ADT_stack.dir\cmake_clean.cmake
.PHONY : CMakeFiles/ADT_stack.dir/clean

CMakeFiles/ADT_stack.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\A\CLionProjects\untitled C:\Users\A\CLionProjects\untitled C:\Users\A\CLionProjects\untitled\cmake-build-debug C:\Users\A\CLionProjects\untitled\cmake-build-debug C:\Users\A\CLionProjects\untitled\cmake-build-debug\CMakeFiles\ADT_stack.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ADT_stack.dir/depend

