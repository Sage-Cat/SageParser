# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.24

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Qt\Tools\CMake_64\bin\cmake.exe

# The command to remove a file.
RM = C:\Qt\Tools\CMake_64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\project\SageDocs

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\project\SageDocs\build

# Include any dependencies generated for this target.
include tests/CMakeFiles/TestSageDocsLib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/CMakeFiles/TestSageDocsLib.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/TestSageDocsLib.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/TestSageDocsLib.dir/flags.make

tests/CMakeFiles/TestSageDocsLib.dir/testSageDocsLib.cpp.obj: tests/CMakeFiles/TestSageDocsLib.dir/flags.make
tests/CMakeFiles/TestSageDocsLib.dir/testSageDocsLib.cpp.obj: tests/CMakeFiles/TestSageDocsLib.dir/includes_CXX.rsp
tests/CMakeFiles/TestSageDocsLib.dir/testSageDocsLib.cpp.obj: C:/project/SageDocs/tests/testSageDocsLib.cpp
tests/CMakeFiles/TestSageDocsLib.dir/testSageDocsLib.cpp.obj: tests/CMakeFiles/TestSageDocsLib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\project\SageDocs\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/TestSageDocsLib.dir/testSageDocsLib.cpp.obj"
	cd /d C:\project\SageDocs\build\tests && C:\Qt\Tools\mingw1120_64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/TestSageDocsLib.dir/testSageDocsLib.cpp.obj -MF CMakeFiles\TestSageDocsLib.dir\testSageDocsLib.cpp.obj.d -o CMakeFiles\TestSageDocsLib.dir\testSageDocsLib.cpp.obj -c C:\project\SageDocs\tests\testSageDocsLib.cpp

tests/CMakeFiles/TestSageDocsLib.dir/testSageDocsLib.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TestSageDocsLib.dir/testSageDocsLib.cpp.i"
	cd /d C:\project\SageDocs\build\tests && C:\Qt\Tools\mingw1120_64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\project\SageDocs\tests\testSageDocsLib.cpp > CMakeFiles\TestSageDocsLib.dir\testSageDocsLib.cpp.i

tests/CMakeFiles/TestSageDocsLib.dir/testSageDocsLib.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TestSageDocsLib.dir/testSageDocsLib.cpp.s"
	cd /d C:\project\SageDocs\build\tests && C:\Qt\Tools\mingw1120_64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\project\SageDocs\tests\testSageDocsLib.cpp -o CMakeFiles\TestSageDocsLib.dir\testSageDocsLib.cpp.s

# Object files for target TestSageDocsLib
TestSageDocsLib_OBJECTS = \
"CMakeFiles/TestSageDocsLib.dir/testSageDocsLib.cpp.obj"

# External object files for target TestSageDocsLib
TestSageDocsLib_EXTERNAL_OBJECTS =

bin/TestSageDocsLib.exe: tests/CMakeFiles/TestSageDocsLib.dir/testSageDocsLib.cpp.obj
bin/TestSageDocsLib.exe: tests/CMakeFiles/TestSageDocsLib.dir/build.make
bin/TestSageDocsLib.exe: lib/libSageDocsLib.dll.a
bin/TestSageDocsLib.exe: C:/Users/Ploda/.conan2/p/b/gtesta940192eb4507/p/lib/libgtest_main.dll.a
bin/TestSageDocsLib.exe: C:/Users/Ploda/.conan2/p/b/gtesta940192eb4507/p/lib/libgtest.dll.a
bin/TestSageDocsLib.exe: tests/CMakeFiles/TestSageDocsLib.dir/linklibs.rsp
bin/TestSageDocsLib.exe: tests/CMakeFiles/TestSageDocsLib.dir/objects1.rsp
bin/TestSageDocsLib.exe: tests/CMakeFiles/TestSageDocsLib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\project\SageDocs\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ..\bin\TestSageDocsLib.exe"
	cd /d C:\project\SageDocs\build\tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\TestSageDocsLib.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/TestSageDocsLib.dir/build: bin/TestSageDocsLib.exe
.PHONY : tests/CMakeFiles/TestSageDocsLib.dir/build

tests/CMakeFiles/TestSageDocsLib.dir/clean:
	cd /d C:\project\SageDocs\build\tests && $(CMAKE_COMMAND) -P CMakeFiles\TestSageDocsLib.dir\cmake_clean.cmake
.PHONY : tests/CMakeFiles/TestSageDocsLib.dir/clean

tests/CMakeFiles/TestSageDocsLib.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\project\SageDocs C:\project\SageDocs\tests C:\project\SageDocs\build C:\project\SageDocs\build\tests C:\project\SageDocs\build\tests\CMakeFiles\TestSageDocsLib.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/TestSageDocsLib.dir/depend
