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
include CMakeFiles/ADT_queue.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ADT_queue.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ADT_queue.dir/flags.make

CMakeFiles/ADT_queue.dir/ADT_queue.c.obj: CMakeFiles/ADT_queue.dir/flags.make
CMakeFiles/ADT_queue.dir/ADT_queue.c.obj: ../ADT_queue.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\A\CLionProjects\untitled\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ADT_queue.dir/ADT_queue.c.obj"
	C:\TDM-GCC-64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\ADT_queue.dir\ADT_queue.c.obj   -c C:\Users\A\CLionProjects\untitled\ADT_queue.c

CMakeFiles/ADT_queue.dir/ADT_queue.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ADT_queue.dir/ADT_queue.c.i"
	C:\TDM-GCC-64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\A\CLionProjects\untitled\ADT_queue.c > CMakeFiles\ADT_queue.dir\ADT_queue.c.i

CMakeFiles/ADT_queue.dir/ADT_queue.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ADT_queue.dir/ADT_queue.c.s"
	C:\TDM-GCC-64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\A\CLionProjects\untitled\ADT_queue.c -o CMakeFiles\ADT_queue.dir\ADT_queue.c.s

# Object files for target ADT_queue
ADT_queue_OBJECTS = \
"CMakeFiles/ADT_queue.dir/ADT_queue.c.obj"

# External object files for target ADT_queue
ADT_queue_EXTERNAL_OBJECTS =

ADT_queue.exe: CMakeFiles/ADT_queue.dir/ADT_queue.c.obj
ADT_queue.exe: CMakeFiles/ADT_queue.dir/build.make
ADT_queue.exe: CMakeFiles/ADT_queue.dir/linklibs.rsp
ADT_queue.exe: CMakeFiles/ADT_queue.dir/objects1.rsp
ADT_queue.exe: CMakeFiles/ADT_queue.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\A\CLionProjects\untitled\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ADT_queue.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\ADT_queue.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ADT_queue.dir/build: ADT_queue.exe

.PHONY : CMakeFiles/ADT_queue.dir/build

CMakeFiles/ADT_queue.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\ADT_queue.dir\cmake_clean.cmake
.PHONY : CMakeFiles/ADT_queue.dir/clean

CMakeFiles/ADT_queue.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\A\CLionProjects\untitled C:\Users\A\CLionProjects\untitled C:\Users\A\CLionProjects\untitled\cmake-build-debug C:\Users\A\CLionProjects\untitled\cmake-build-debug C:\Users\A\CLionProjects\untitled\cmake-build-debug\CMakeFiles\ADT_queue.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ADT_queue.dir/depend

