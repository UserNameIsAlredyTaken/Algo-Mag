# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


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

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.2.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.2.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Projects\DateConverter_withTests-master\DateConverter_withTests-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Projects\DateConverter_withTests-master\DateConverter_withTests-master\cmake-build-debug

# Include any dependencies generated for this target.
include Doctest_tests\CMakeFiles\Doctest_tests_run.dir\depend.make

# Include the progress variables for this target.
include Doctest_tests\CMakeFiles\Doctest_tests_run.dir\progress.make

# Include the compile flags for this target's objects.
include Doctest_tests\CMakeFiles\Doctest_tests_run.dir\flags.make

Doctest_tests\CMakeFiles\Doctest_tests_run.dir\ConverterTests.cpp.obj: Doctest_tests\CMakeFiles\Doctest_tests_run.dir\flags.make
Doctest_tests\CMakeFiles\Doctest_tests_run.dir\ConverterTests.cpp.obj: ..\Doctest_tests\ConverterTests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Projects\DateConverter_withTests-master\DateConverter_withTests-master\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Doctest_tests/CMakeFiles/Doctest_tests_run.dir/ConverterTests.cpp.obj"
	cd C:\Projects\DateConverter_withTests-master\DateConverter_withTests-master\cmake-build-debug\Doctest_tests
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Doctest_tests_run.dir\ConverterTests.cpp.obj /FdCMakeFiles\Doctest_tests_run.dir\ /FS -c C:\Projects\DateConverter_withTests-master\DateConverter_withTests-master\Doctest_tests\ConverterTests.cpp
<<
	cd C:\Projects\DateConverter_withTests-master\DateConverter_withTests-master\cmake-build-debug

Doctest_tests\CMakeFiles\Doctest_tests_run.dir\ConverterTests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Doctest_tests_run.dir/ConverterTests.cpp.i"
	cd C:\Projects\DateConverter_withTests-master\DateConverter_withTests-master\cmake-build-debug\Doctest_tests
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe > CMakeFiles\Doctest_tests_run.dir\ConverterTests.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Projects\DateConverter_withTests-master\DateConverter_withTests-master\Doctest_tests\ConverterTests.cpp
<<
	cd C:\Projects\DateConverter_withTests-master\DateConverter_withTests-master\cmake-build-debug

Doctest_tests\CMakeFiles\Doctest_tests_run.dir\ConverterTests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Doctest_tests_run.dir/ConverterTests.cpp.s"
	cd C:\Projects\DateConverter_withTests-master\DateConverter_withTests-master\cmake-build-debug\Doctest_tests
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Doctest_tests_run.dir\ConverterTests.cpp.s /c C:\Projects\DateConverter_withTests-master\DateConverter_withTests-master\Doctest_tests\ConverterTests.cpp
<<
	cd C:\Projects\DateConverter_withTests-master\DateConverter_withTests-master\cmake-build-debug

Doctest_tests\CMakeFiles\Doctest_tests_run.dir\AbsoluteDateTest.cpp.obj: Doctest_tests\CMakeFiles\Doctest_tests_run.dir\flags.make
Doctest_tests\CMakeFiles\Doctest_tests_run.dir\AbsoluteDateTest.cpp.obj: ..\Doctest_tests\AbsoluteDateTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Projects\DateConverter_withTests-master\DateConverter_withTests-master\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object Doctest_tests/CMakeFiles/Doctest_tests_run.dir/AbsoluteDateTest.cpp.obj"
	cd C:\Projects\DateConverter_withTests-master\DateConverter_withTests-master\cmake-build-debug\Doctest_tests
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Doctest_tests_run.dir\AbsoluteDateTest.cpp.obj /FdCMakeFiles\Doctest_tests_run.dir\ /FS -c C:\Projects\DateConverter_withTests-master\DateConverter_withTests-master\Doctest_tests\AbsoluteDateTest.cpp
<<
	cd C:\Projects\DateConverter_withTests-master\DateConverter_withTests-master\cmake-build-debug

Doctest_tests\CMakeFiles\Doctest_tests_run.dir\AbsoluteDateTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Doctest_tests_run.dir/AbsoluteDateTest.cpp.i"
	cd C:\Projects\DateConverter_withTests-master\DateConverter_withTests-master\cmake-build-debug\Doctest_tests
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe > CMakeFiles\Doctest_tests_run.dir\AbsoluteDateTest.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Projects\DateConverter_withTests-master\DateConverter_withTests-master\Doctest_tests\AbsoluteDateTest.cpp
<<
	cd C:\Projects\DateConverter_withTests-master\DateConverter_withTests-master\cmake-build-debug

Doctest_tests\CMakeFiles\Doctest_tests_run.dir\AbsoluteDateTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Doctest_tests_run.dir/AbsoluteDateTest.cpp.s"
	cd C:\Projects\DateConverter_withTests-master\DateConverter_withTests-master\cmake-build-debug\Doctest_tests
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Doctest_tests_run.dir\AbsoluteDateTest.cpp.s /c C:\Projects\DateConverter_withTests-master\DateConverter_withTests-master\Doctest_tests\AbsoluteDateTest.cpp
<<
	cd C:\Projects\DateConverter_withTests-master\DateConverter_withTests-master\cmake-build-debug

# Object files for target Doctest_tests_run
Doctest_tests_run_OBJECTS = \
"CMakeFiles\Doctest_tests_run.dir\ConverterTests.cpp.obj" \
"CMakeFiles\Doctest_tests_run.dir\AbsoluteDateTest.cpp.obj"

# External object files for target Doctest_tests_run
Doctest_tests_run_EXTERNAL_OBJECTS =

Doctest_tests\Doctest_tests_run.exe: Doctest_tests\CMakeFiles\Doctest_tests_run.dir\ConverterTests.cpp.obj
Doctest_tests\Doctest_tests_run.exe: Doctest_tests\CMakeFiles\Doctest_tests_run.dir\AbsoluteDateTest.cpp.obj
Doctest_tests\Doctest_tests_run.exe: Doctest_tests\CMakeFiles\Doctest_tests_run.dir\build.make
Doctest_tests\Doctest_tests_run.exe: DateConverter_lib\DateConverter_lib.lib
Doctest_tests\Doctest_tests_run.exe: Doctest_tests\CMakeFiles\Doctest_tests_run.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Projects\DateConverter_withTests-master\DateConverter_withTests-master\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Doctest_tests_run.exe"
	cd C:\Projects\DateConverter_withTests-master\DateConverter_withTests-master\cmake-build-debug\Doctest_tests
	"C:\Program Files\JetBrains\CLion 2020.2.3\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\Doctest_tests_run.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100177~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100177~1.0\x86\mt.exe --manifests  -- C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\Doctest_tests_run.dir\objects1.rsp @<<
 /out:Doctest_tests_run.exe /implib:Doctest_tests_run.lib /pdb:C:\Projects\DateConverter_withTests-master\DateConverter_withTests-master\cmake-build-debug\Doctest_tests\Doctest_tests_run.pdb /version:0.0  /machine:X86 /debug /INCREMENTAL /subsystem:console  ..\DateConverter_lib\DateConverter_lib.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<
	cd C:\Projects\DateConverter_withTests-master\DateConverter_withTests-master\cmake-build-debug

# Rule to build all files generated by this target.
Doctest_tests\CMakeFiles\Doctest_tests_run.dir\build: Doctest_tests\Doctest_tests_run.exe

.PHONY : Doctest_tests\CMakeFiles\Doctest_tests_run.dir\build

Doctest_tests\CMakeFiles\Doctest_tests_run.dir\clean:
	cd C:\Projects\DateConverter_withTests-master\DateConverter_withTests-master\cmake-build-debug\Doctest_tests
	$(CMAKE_COMMAND) -P CMakeFiles\Doctest_tests_run.dir\cmake_clean.cmake
	cd C:\Projects\DateConverter_withTests-master\DateConverter_withTests-master\cmake-build-debug
.PHONY : Doctest_tests\CMakeFiles\Doctest_tests_run.dir\clean

Doctest_tests\CMakeFiles\Doctest_tests_run.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Projects\DateConverter_withTests-master\DateConverter_withTests-master C:\Projects\DateConverter_withTests-master\DateConverter_withTests-master\Doctest_tests C:\Projects\DateConverter_withTests-master\DateConverter_withTests-master\cmake-build-debug C:\Projects\DateConverter_withTests-master\DateConverter_withTests-master\cmake-build-debug\Doctest_tests C:\Projects\DateConverter_withTests-master\DateConverter_withTests-master\cmake-build-debug\Doctest_tests\CMakeFiles\Doctest_tests_run.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : Doctest_tests\CMakeFiles\Doctest_tests_run.dir\depend

