﻿# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.31

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

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

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\bno055\bbm\build\_deps\picotool-src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\bno055\bbm\build\_deps\picotool-build

# Include any dependencies generated for this target.
include lib\mbedtls\library\CMakeFiles\mbedtls.dir\depend.make
# Include any dependencies generated by the compiler for this target.
include lib\mbedtls\library\CMakeFiles\mbedtls.dir\compiler_depend.make

# Include the compile flags for this target's objects.
include lib\mbedtls\library\CMakeFiles\mbedtls.dir\flags.make

lib\mbedtls\library\CMakeFiles\mbedtls.dir\codegen:
.PHONY : lib\mbedtls\library\CMakeFiles\mbedtls.dir\codegen

lib\mbedtls\library\CMakeFiles\mbedtls.dir\debug.c.obj: lib\mbedtls\library\CMakeFiles\mbedtls.dir\flags.make
lib\mbedtls\library\CMakeFiles\mbedtls.dir\debug.c.obj: C:\Pico\pico-sdk\lib\mbedtls\library\debug.c
lib\mbedtls\library\CMakeFiles\mbedtls.dir\debug.c.obj: lib\mbedtls\library\CMakeFiles\mbedtls.dir\compiler_depend.ts
	cd C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library
	$(CMAKE_COMMAND) -E cmake_cl_compile_depends --dep-file=CMakeFiles\mbedtls.dir\debug.c.obj.d --working-dir=C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library --filter-prefix="Note: including file: " -- C:\PROGRA~2\MICROS~2\2022\BUILDT~1\VC\Tools\MSVC\1442~1.344\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /showIncludes /FoCMakeFiles\mbedtls.dir\debug.c.obj /FdCMakeFiles\mbedtls.dir\mbedtls.pdb /FS -c C:\Pico\pico-sdk\lib\mbedtls\library\debug.c
<<
	cd C:\bno055\bbm\build\_deps\picotool-build

lib\mbedtls\library\CMakeFiles\mbedtls.dir\debug.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/mbedtls.dir/debug.c.i"
	cd C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library
	C:\PROGRA~2\MICROS~2\2022\BUILDT~1\VC\Tools\MSVC\1442~1.344\bin\Hostx86\x86\cl.exe > CMakeFiles\mbedtls.dir\debug.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Pico\pico-sdk\lib\mbedtls\library\debug.c
<<
	cd C:\bno055\bbm\build\_deps\picotool-build

lib\mbedtls\library\CMakeFiles\mbedtls.dir\debug.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/mbedtls.dir/debug.c.s"
	cd C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library
	C:\PROGRA~2\MICROS~2\2022\BUILDT~1\VC\Tools\MSVC\1442~1.344\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\mbedtls.dir\debug.c.s /c C:\Pico\pico-sdk\lib\mbedtls\library\debug.c
<<
	cd C:\bno055\bbm\build\_deps\picotool-build

lib\mbedtls\library\CMakeFiles\mbedtls.dir\net_sockets.c.obj: lib\mbedtls\library\CMakeFiles\mbedtls.dir\flags.make
lib\mbedtls\library\CMakeFiles\mbedtls.dir\net_sockets.c.obj: C:\Pico\pico-sdk\lib\mbedtls\library\net_sockets.c
lib\mbedtls\library\CMakeFiles\mbedtls.dir\net_sockets.c.obj: lib\mbedtls\library\CMakeFiles\mbedtls.dir\compiler_depend.ts
	cd C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library
	$(CMAKE_COMMAND) -E cmake_cl_compile_depends --dep-file=CMakeFiles\mbedtls.dir\net_sockets.c.obj.d --working-dir=C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library --filter-prefix="Note: including file: " -- C:\PROGRA~2\MICROS~2\2022\BUILDT~1\VC\Tools\MSVC\1442~1.344\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /showIncludes /FoCMakeFiles\mbedtls.dir\net_sockets.c.obj /FdCMakeFiles\mbedtls.dir\mbedtls.pdb /FS -c C:\Pico\pico-sdk\lib\mbedtls\library\net_sockets.c
<<
	cd C:\bno055\bbm\build\_deps\picotool-build

lib\mbedtls\library\CMakeFiles\mbedtls.dir\net_sockets.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/mbedtls.dir/net_sockets.c.i"
	cd C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library
	C:\PROGRA~2\MICROS~2\2022\BUILDT~1\VC\Tools\MSVC\1442~1.344\bin\Hostx86\x86\cl.exe > CMakeFiles\mbedtls.dir\net_sockets.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Pico\pico-sdk\lib\mbedtls\library\net_sockets.c
<<
	cd C:\bno055\bbm\build\_deps\picotool-build

lib\mbedtls\library\CMakeFiles\mbedtls.dir\net_sockets.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/mbedtls.dir/net_sockets.c.s"
	cd C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library
	C:\PROGRA~2\MICROS~2\2022\BUILDT~1\VC\Tools\MSVC\1442~1.344\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\mbedtls.dir\net_sockets.c.s /c C:\Pico\pico-sdk\lib\mbedtls\library\net_sockets.c
<<
	cd C:\bno055\bbm\build\_deps\picotool-build

lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_cache.c.obj: lib\mbedtls\library\CMakeFiles\mbedtls.dir\flags.make
lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_cache.c.obj: C:\Pico\pico-sdk\lib\mbedtls\library\ssl_cache.c
lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_cache.c.obj: lib\mbedtls\library\CMakeFiles\mbedtls.dir\compiler_depend.ts
	cd C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library
	$(CMAKE_COMMAND) -E cmake_cl_compile_depends --dep-file=CMakeFiles\mbedtls.dir\ssl_cache.c.obj.d --working-dir=C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library --filter-prefix="Note: including file: " -- C:\PROGRA~2\MICROS~2\2022\BUILDT~1\VC\Tools\MSVC\1442~1.344\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /showIncludes /FoCMakeFiles\mbedtls.dir\ssl_cache.c.obj /FdCMakeFiles\mbedtls.dir\mbedtls.pdb /FS -c C:\Pico\pico-sdk\lib\mbedtls\library\ssl_cache.c
<<
	cd C:\bno055\bbm\build\_deps\picotool-build

lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_cache.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/mbedtls.dir/ssl_cache.c.i"
	cd C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library
	C:\PROGRA~2\MICROS~2\2022\BUILDT~1\VC\Tools\MSVC\1442~1.344\bin\Hostx86\x86\cl.exe > CMakeFiles\mbedtls.dir\ssl_cache.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Pico\pico-sdk\lib\mbedtls\library\ssl_cache.c
<<
	cd C:\bno055\bbm\build\_deps\picotool-build

lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_cache.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/mbedtls.dir/ssl_cache.c.s"
	cd C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library
	C:\PROGRA~2\MICROS~2\2022\BUILDT~1\VC\Tools\MSVC\1442~1.344\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\mbedtls.dir\ssl_cache.c.s /c C:\Pico\pico-sdk\lib\mbedtls\library\ssl_cache.c
<<
	cd C:\bno055\bbm\build\_deps\picotool-build

lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_ciphersuites.c.obj: lib\mbedtls\library\CMakeFiles\mbedtls.dir\flags.make
lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_ciphersuites.c.obj: C:\Pico\pico-sdk\lib\mbedtls\library\ssl_ciphersuites.c
lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_ciphersuites.c.obj: lib\mbedtls\library\CMakeFiles\mbedtls.dir\compiler_depend.ts
	cd C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library
	$(CMAKE_COMMAND) -E cmake_cl_compile_depends --dep-file=CMakeFiles\mbedtls.dir\ssl_ciphersuites.c.obj.d --working-dir=C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library --filter-prefix="Note: including file: " -- C:\PROGRA~2\MICROS~2\2022\BUILDT~1\VC\Tools\MSVC\1442~1.344\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /showIncludes /FoCMakeFiles\mbedtls.dir\ssl_ciphersuites.c.obj /FdCMakeFiles\mbedtls.dir\mbedtls.pdb /FS -c C:\Pico\pico-sdk\lib\mbedtls\library\ssl_ciphersuites.c
<<
	cd C:\bno055\bbm\build\_deps\picotool-build

lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_ciphersuites.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/mbedtls.dir/ssl_ciphersuites.c.i"
	cd C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library
	C:\PROGRA~2\MICROS~2\2022\BUILDT~1\VC\Tools\MSVC\1442~1.344\bin\Hostx86\x86\cl.exe > CMakeFiles\mbedtls.dir\ssl_ciphersuites.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Pico\pico-sdk\lib\mbedtls\library\ssl_ciphersuites.c
<<
	cd C:\bno055\bbm\build\_deps\picotool-build

lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_ciphersuites.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/mbedtls.dir/ssl_ciphersuites.c.s"
	cd C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library
	C:\PROGRA~2\MICROS~2\2022\BUILDT~1\VC\Tools\MSVC\1442~1.344\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\mbedtls.dir\ssl_ciphersuites.c.s /c C:\Pico\pico-sdk\lib\mbedtls\library\ssl_ciphersuites.c
<<
	cd C:\bno055\bbm\build\_deps\picotool-build

lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_cli.c.obj: lib\mbedtls\library\CMakeFiles\mbedtls.dir\flags.make
lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_cli.c.obj: C:\Pico\pico-sdk\lib\mbedtls\library\ssl_cli.c
lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_cli.c.obj: lib\mbedtls\library\CMakeFiles\mbedtls.dir\compiler_depend.ts
	cd C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library
	$(CMAKE_COMMAND) -E cmake_cl_compile_depends --dep-file=CMakeFiles\mbedtls.dir\ssl_cli.c.obj.d --working-dir=C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library --filter-prefix="Note: including file: " -- C:\PROGRA~2\MICROS~2\2022\BUILDT~1\VC\Tools\MSVC\1442~1.344\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /showIncludes /FoCMakeFiles\mbedtls.dir\ssl_cli.c.obj /FdCMakeFiles\mbedtls.dir\mbedtls.pdb /FS -c C:\Pico\pico-sdk\lib\mbedtls\library\ssl_cli.c
<<
	cd C:\bno055\bbm\build\_deps\picotool-build

lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_cli.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/mbedtls.dir/ssl_cli.c.i"
	cd C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library
	C:\PROGRA~2\MICROS~2\2022\BUILDT~1\VC\Tools\MSVC\1442~1.344\bin\Hostx86\x86\cl.exe > CMakeFiles\mbedtls.dir\ssl_cli.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Pico\pico-sdk\lib\mbedtls\library\ssl_cli.c
<<
	cd C:\bno055\bbm\build\_deps\picotool-build

lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_cli.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/mbedtls.dir/ssl_cli.c.s"
	cd C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library
	C:\PROGRA~2\MICROS~2\2022\BUILDT~1\VC\Tools\MSVC\1442~1.344\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\mbedtls.dir\ssl_cli.c.s /c C:\Pico\pico-sdk\lib\mbedtls\library\ssl_cli.c
<<
	cd C:\bno055\bbm\build\_deps\picotool-build

lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_cookie.c.obj: lib\mbedtls\library\CMakeFiles\mbedtls.dir\flags.make
lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_cookie.c.obj: C:\Pico\pico-sdk\lib\mbedtls\library\ssl_cookie.c
lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_cookie.c.obj: lib\mbedtls\library\CMakeFiles\mbedtls.dir\compiler_depend.ts
	cd C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library
	$(CMAKE_COMMAND) -E cmake_cl_compile_depends --dep-file=CMakeFiles\mbedtls.dir\ssl_cookie.c.obj.d --working-dir=C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library --filter-prefix="Note: including file: " -- C:\PROGRA~2\MICROS~2\2022\BUILDT~1\VC\Tools\MSVC\1442~1.344\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /showIncludes /FoCMakeFiles\mbedtls.dir\ssl_cookie.c.obj /FdCMakeFiles\mbedtls.dir\mbedtls.pdb /FS -c C:\Pico\pico-sdk\lib\mbedtls\library\ssl_cookie.c
<<
	cd C:\bno055\bbm\build\_deps\picotool-build

lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_cookie.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/mbedtls.dir/ssl_cookie.c.i"
	cd C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library
	C:\PROGRA~2\MICROS~2\2022\BUILDT~1\VC\Tools\MSVC\1442~1.344\bin\Hostx86\x86\cl.exe > CMakeFiles\mbedtls.dir\ssl_cookie.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Pico\pico-sdk\lib\mbedtls\library\ssl_cookie.c
<<
	cd C:\bno055\bbm\build\_deps\picotool-build

lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_cookie.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/mbedtls.dir/ssl_cookie.c.s"
	cd C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library
	C:\PROGRA~2\MICROS~2\2022\BUILDT~1\VC\Tools\MSVC\1442~1.344\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\mbedtls.dir\ssl_cookie.c.s /c C:\Pico\pico-sdk\lib\mbedtls\library\ssl_cookie.c
<<
	cd C:\bno055\bbm\build\_deps\picotool-build

lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_msg.c.obj: lib\mbedtls\library\CMakeFiles\mbedtls.dir\flags.make
lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_msg.c.obj: C:\Pico\pico-sdk\lib\mbedtls\library\ssl_msg.c
lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_msg.c.obj: lib\mbedtls\library\CMakeFiles\mbedtls.dir\compiler_depend.ts
	cd C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library
	$(CMAKE_COMMAND) -E cmake_cl_compile_depends --dep-file=CMakeFiles\mbedtls.dir\ssl_msg.c.obj.d --working-dir=C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library --filter-prefix="Note: including file: " -- C:\PROGRA~2\MICROS~2\2022\BUILDT~1\VC\Tools\MSVC\1442~1.344\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /showIncludes /FoCMakeFiles\mbedtls.dir\ssl_msg.c.obj /FdCMakeFiles\mbedtls.dir\mbedtls.pdb /FS -c C:\Pico\pico-sdk\lib\mbedtls\library\ssl_msg.c
<<
	cd C:\bno055\bbm\build\_deps\picotool-build

lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_msg.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/mbedtls.dir/ssl_msg.c.i"
	cd C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library
	C:\PROGRA~2\MICROS~2\2022\BUILDT~1\VC\Tools\MSVC\1442~1.344\bin\Hostx86\x86\cl.exe > CMakeFiles\mbedtls.dir\ssl_msg.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Pico\pico-sdk\lib\mbedtls\library\ssl_msg.c
<<
	cd C:\bno055\bbm\build\_deps\picotool-build

lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_msg.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/mbedtls.dir/ssl_msg.c.s"
	cd C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library
	C:\PROGRA~2\MICROS~2\2022\BUILDT~1\VC\Tools\MSVC\1442~1.344\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\mbedtls.dir\ssl_msg.c.s /c C:\Pico\pico-sdk\lib\mbedtls\library\ssl_msg.c
<<
	cd C:\bno055\bbm\build\_deps\picotool-build

lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_srv.c.obj: lib\mbedtls\library\CMakeFiles\mbedtls.dir\flags.make
lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_srv.c.obj: C:\Pico\pico-sdk\lib\mbedtls\library\ssl_srv.c
lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_srv.c.obj: lib\mbedtls\library\CMakeFiles\mbedtls.dir\compiler_depend.ts
	cd C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library
	$(CMAKE_COMMAND) -E cmake_cl_compile_depends --dep-file=CMakeFiles\mbedtls.dir\ssl_srv.c.obj.d --working-dir=C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library --filter-prefix="Note: including file: " -- C:\PROGRA~2\MICROS~2\2022\BUILDT~1\VC\Tools\MSVC\1442~1.344\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /showIncludes /FoCMakeFiles\mbedtls.dir\ssl_srv.c.obj /FdCMakeFiles\mbedtls.dir\mbedtls.pdb /FS -c C:\Pico\pico-sdk\lib\mbedtls\library\ssl_srv.c
<<
	cd C:\bno055\bbm\build\_deps\picotool-build

lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_srv.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/mbedtls.dir/ssl_srv.c.i"
	cd C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library
	C:\PROGRA~2\MICROS~2\2022\BUILDT~1\VC\Tools\MSVC\1442~1.344\bin\Hostx86\x86\cl.exe > CMakeFiles\mbedtls.dir\ssl_srv.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Pico\pico-sdk\lib\mbedtls\library\ssl_srv.c
<<
	cd C:\bno055\bbm\build\_deps\picotool-build

lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_srv.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/mbedtls.dir/ssl_srv.c.s"
	cd C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library
	C:\PROGRA~2\MICROS~2\2022\BUILDT~1\VC\Tools\MSVC\1442~1.344\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\mbedtls.dir\ssl_srv.c.s /c C:\Pico\pico-sdk\lib\mbedtls\library\ssl_srv.c
<<
	cd C:\bno055\bbm\build\_deps\picotool-build

lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_ticket.c.obj: lib\mbedtls\library\CMakeFiles\mbedtls.dir\flags.make
lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_ticket.c.obj: C:\Pico\pico-sdk\lib\mbedtls\library\ssl_ticket.c
lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_ticket.c.obj: lib\mbedtls\library\CMakeFiles\mbedtls.dir\compiler_depend.ts
	cd C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library
	$(CMAKE_COMMAND) -E cmake_cl_compile_depends --dep-file=CMakeFiles\mbedtls.dir\ssl_ticket.c.obj.d --working-dir=C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library --filter-prefix="Note: including file: " -- C:\PROGRA~2\MICROS~2\2022\BUILDT~1\VC\Tools\MSVC\1442~1.344\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /showIncludes /FoCMakeFiles\mbedtls.dir\ssl_ticket.c.obj /FdCMakeFiles\mbedtls.dir\mbedtls.pdb /FS -c C:\Pico\pico-sdk\lib\mbedtls\library\ssl_ticket.c
<<
	cd C:\bno055\bbm\build\_deps\picotool-build

lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_ticket.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/mbedtls.dir/ssl_ticket.c.i"
	cd C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library
	C:\PROGRA~2\MICROS~2\2022\BUILDT~1\VC\Tools\MSVC\1442~1.344\bin\Hostx86\x86\cl.exe > CMakeFiles\mbedtls.dir\ssl_ticket.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Pico\pico-sdk\lib\mbedtls\library\ssl_ticket.c
<<
	cd C:\bno055\bbm\build\_deps\picotool-build

lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_ticket.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/mbedtls.dir/ssl_ticket.c.s"
	cd C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library
	C:\PROGRA~2\MICROS~2\2022\BUILDT~1\VC\Tools\MSVC\1442~1.344\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\mbedtls.dir\ssl_ticket.c.s /c C:\Pico\pico-sdk\lib\mbedtls\library\ssl_ticket.c
<<
	cd C:\bno055\bbm\build\_deps\picotool-build

lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_tls.c.obj: lib\mbedtls\library\CMakeFiles\mbedtls.dir\flags.make
lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_tls.c.obj: C:\Pico\pico-sdk\lib\mbedtls\library\ssl_tls.c
lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_tls.c.obj: lib\mbedtls\library\CMakeFiles\mbedtls.dir\compiler_depend.ts
	cd C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library
	$(CMAKE_COMMAND) -E cmake_cl_compile_depends --dep-file=CMakeFiles\mbedtls.dir\ssl_tls.c.obj.d --working-dir=C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library --filter-prefix="Note: including file: " -- C:\PROGRA~2\MICROS~2\2022\BUILDT~1\VC\Tools\MSVC\1442~1.344\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /showIncludes /FoCMakeFiles\mbedtls.dir\ssl_tls.c.obj /FdCMakeFiles\mbedtls.dir\mbedtls.pdb /FS -c C:\Pico\pico-sdk\lib\mbedtls\library\ssl_tls.c
<<
	cd C:\bno055\bbm\build\_deps\picotool-build

lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_tls.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/mbedtls.dir/ssl_tls.c.i"
	cd C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library
	C:\PROGRA~2\MICROS~2\2022\BUILDT~1\VC\Tools\MSVC\1442~1.344\bin\Hostx86\x86\cl.exe > CMakeFiles\mbedtls.dir\ssl_tls.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Pico\pico-sdk\lib\mbedtls\library\ssl_tls.c
<<
	cd C:\bno055\bbm\build\_deps\picotool-build

lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_tls.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/mbedtls.dir/ssl_tls.c.s"
	cd C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library
	C:\PROGRA~2\MICROS~2\2022\BUILDT~1\VC\Tools\MSVC\1442~1.344\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\mbedtls.dir\ssl_tls.c.s /c C:\Pico\pico-sdk\lib\mbedtls\library\ssl_tls.c
<<
	cd C:\bno055\bbm\build\_deps\picotool-build

lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_tls13_keys.c.obj: lib\mbedtls\library\CMakeFiles\mbedtls.dir\flags.make
lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_tls13_keys.c.obj: C:\Pico\pico-sdk\lib\mbedtls\library\ssl_tls13_keys.c
lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_tls13_keys.c.obj: lib\mbedtls\library\CMakeFiles\mbedtls.dir\compiler_depend.ts
	cd C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library
	$(CMAKE_COMMAND) -E cmake_cl_compile_depends --dep-file=CMakeFiles\mbedtls.dir\ssl_tls13_keys.c.obj.d --working-dir=C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library --filter-prefix="Note: including file: " -- C:\PROGRA~2\MICROS~2\2022\BUILDT~1\VC\Tools\MSVC\1442~1.344\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /showIncludes /FoCMakeFiles\mbedtls.dir\ssl_tls13_keys.c.obj /FdCMakeFiles\mbedtls.dir\mbedtls.pdb /FS -c C:\Pico\pico-sdk\lib\mbedtls\library\ssl_tls13_keys.c
<<
	cd C:\bno055\bbm\build\_deps\picotool-build

lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_tls13_keys.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/mbedtls.dir/ssl_tls13_keys.c.i"
	cd C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library
	C:\PROGRA~2\MICROS~2\2022\BUILDT~1\VC\Tools\MSVC\1442~1.344\bin\Hostx86\x86\cl.exe > CMakeFiles\mbedtls.dir\ssl_tls13_keys.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Pico\pico-sdk\lib\mbedtls\library\ssl_tls13_keys.c
<<
	cd C:\bno055\bbm\build\_deps\picotool-build

lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_tls13_keys.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/mbedtls.dir/ssl_tls13_keys.c.s"
	cd C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library
	C:\PROGRA~2\MICROS~2\2022\BUILDT~1\VC\Tools\MSVC\1442~1.344\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\mbedtls.dir\ssl_tls13_keys.c.s /c C:\Pico\pico-sdk\lib\mbedtls\library\ssl_tls13_keys.c
<<
	cd C:\bno055\bbm\build\_deps\picotool-build

# Object files for target mbedtls
mbedtls_OBJECTS = \
"CMakeFiles\mbedtls.dir\debug.c.obj" \
"CMakeFiles\mbedtls.dir\net_sockets.c.obj" \
"CMakeFiles\mbedtls.dir\ssl_cache.c.obj" \
"CMakeFiles\mbedtls.dir\ssl_ciphersuites.c.obj" \
"CMakeFiles\mbedtls.dir\ssl_cli.c.obj" \
"CMakeFiles\mbedtls.dir\ssl_cookie.c.obj" \
"CMakeFiles\mbedtls.dir\ssl_msg.c.obj" \
"CMakeFiles\mbedtls.dir\ssl_srv.c.obj" \
"CMakeFiles\mbedtls.dir\ssl_ticket.c.obj" \
"CMakeFiles\mbedtls.dir\ssl_tls.c.obj" \
"CMakeFiles\mbedtls.dir\ssl_tls13_keys.c.obj"

# External object files for target mbedtls
mbedtls_EXTERNAL_OBJECTS =

lib\mbedtls\library\mbedtls.lib: lib\mbedtls\library\CMakeFiles\mbedtls.dir\debug.c.obj
lib\mbedtls\library\mbedtls.lib: lib\mbedtls\library\CMakeFiles\mbedtls.dir\net_sockets.c.obj
lib\mbedtls\library\mbedtls.lib: lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_cache.c.obj
lib\mbedtls\library\mbedtls.lib: lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_ciphersuites.c.obj
lib\mbedtls\library\mbedtls.lib: lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_cli.c.obj
lib\mbedtls\library\mbedtls.lib: lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_cookie.c.obj
lib\mbedtls\library\mbedtls.lib: lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_msg.c.obj
lib\mbedtls\library\mbedtls.lib: lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_srv.c.obj
lib\mbedtls\library\mbedtls.lib: lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_ticket.c.obj
lib\mbedtls\library\mbedtls.lib: lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_tls.c.obj
lib\mbedtls\library\mbedtls.lib: lib\mbedtls\library\CMakeFiles\mbedtls.dir\ssl_tls13_keys.c.obj
lib\mbedtls\library\mbedtls.lib: lib\mbedtls\library\CMakeFiles\mbedtls.dir\build.make
lib\mbedtls\library\mbedtls.lib: lib\mbedtls\library\CMakeFiles\mbedtls.dir\objects1.rsp
	cd C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library
	$(CMAKE_COMMAND) -P CMakeFiles\mbedtls.dir\cmake_clean_target.cmake
	cd C:\bno055\bbm\build\_deps\picotool-build
	cd C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library
	C:\PROGRA~2\MICROS~2\2022\BUILDT~1\VC\Tools\MSVC\1442~1.344\bin\Hostx86\x86\lib.exe /nologo /machine:X86 /out:mbedtls.lib @CMakeFiles\mbedtls.dir\objects1.rsp
	cd C:\bno055\bbm\build\_deps\picotool-build

# Rule to build all files generated by this target.
lib\mbedtls\library\CMakeFiles\mbedtls.dir\build: lib\mbedtls\library\mbedtls.lib
.PHONY : lib\mbedtls\library\CMakeFiles\mbedtls.dir\build

lib\mbedtls\library\CMakeFiles\mbedtls.dir\clean:
	cd C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library
	$(CMAKE_COMMAND) -P CMakeFiles\mbedtls.dir\cmake_clean.cmake
	cd C:\bno055\bbm\build\_deps\picotool-build
.PHONY : lib\mbedtls\library\CMakeFiles\mbedtls.dir\clean

lib\mbedtls\library\CMakeFiles\mbedtls.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\bno055\bbm\build\_deps\picotool-src C:\Pico\pico-sdk\lib\mbedtls\library C:\bno055\bbm\build\_deps\picotool-build C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library C:\bno055\bbm\build\_deps\picotool-build\lib\mbedtls\library\CMakeFiles\mbedtls.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : lib\mbedtls\library\CMakeFiles\mbedtls.dir\depend
