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
include CMakeFiles/DS_hashtable.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/DS_hashtable.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DS_hashtable.dir/flags.make

CMakeFiles/DS_hashtable.dir/DS_hashtable.c.obj: CMakeFiles/DS_hashtable.dir/flags.make
CMakeFiles/DS_hashtable.dir/DS_hashtable.c.obj: ../DS_hashtable.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\A\CLionProjects\untitled\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/DS_hashtable.dir/DS_hashtable.c.obj"
	C:\TDM-GCC-64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\DS_hashtable.dir\DS_hashtable.c.obj   -c C:\Users\A\CLionProjects\untitled\DS_hashtable.c

CMakeFiles/DS_hashtable.dir/DS_hashtable.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/DS_hashtable.dir/DS_hashtable.c.i"
	C:\TDM-GCC-64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\A\CLionProjects\untitled\DS_hashtable.c > CMakeFiles\DS_hashtable.dir\DS_hashtable.c.i

CMakeFiles/DS_hashtable.dir/DS_hashtable.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/DS_hashtable.dir/DS_hashtable.c.s"
	C:\TDM-GCC-64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\A\CLionProjects\untitled\DS_hashtable.c -o CMakeFiles\DS_hashtable.dir\DS_hashtable.c.s

# Object files for target DS_hashtable
DS_hashtable_OBJECTS = \
"CMakeFiles/DS_hashtable.dir/DS_hashtable.c.obj"

# External object files for target DS_hashtable
DS_hashtable_EXTERNAL_OBJECTS =

DS_hashtable.exe: CMakeFiles/DS_hashtable.dir/DS_hashtable.c.obj
DS_hashtable.exe: CMakeFiles/DS_hashtable.dir/build.make
DS_hashtable.exe: CMakeFiles/DS_hashtable.dir/linklibs.rsp
DS_hashtable.exe: CMakeFiles/DS_hashtable.dir/objects1.rsp
DS_hashtable.exe: CMakeFiles/DS_hashtable.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\A\CLionProjects\untitled\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable DS_hashtable.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\DS_hashtable.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DS_hashtable.dir/build: DS_hashtable.exe

.PHONY : CMakeFiles/DS_hashtable.dir/build

CMakeFiles/DS_hashtable.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\DS_hashtable.dir\cmake_clean.cmake
.PHONY : CMakeFiles/DS_hashtable.dir/clean

CMakeFiles/DS_hashtable.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\A\CLionProjects\untitled C:\Users\A\CLionProjects\untitled C:\Users\A\CLionProjects\untitled\cmake-build-debug C:\Users\A\CLionProjects\untitled\cmake-build-debug C:\Users\A\CLionProjects\untitled\cmake-build-debug\CMakeFiles\DS_hashtable.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/DS_hashtable.dir/depend
