# .txt
# Z CMake Configuration
# by Kyle Furey

# Initialize CMake with vcpkg (if Windows)
# set(CMAKE_TOOLCHAIN_FILE "$ENV{USERPROFILE}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
cmake_minimum_required(VERSION 3.16)
project(ZRuntimeLib C)

# Set C compiler version
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/lib)

# Build Z Runtime Library
add_library(ZRuntimeLib SHARED
        ${CMAKE_SOURCE_DIR}/include/ZLang.h
        ${CMAKE_SOURCE_DIR}/include/External.h
        ${CMAKE_SOURCE_DIR}/include/Export.h
        ${CMAKE_SOURCE_DIR}/include/Types.h
        ${CMAKE_SOURCE_DIR}/include/Error.h
        ${CMAKE_SOURCE_DIR}/include/Execute.h
        ${CMAKE_SOURCE_DIR}/include/Program.h
        ${CMAKE_SOURCE_DIR}/include/Coroutine.h
        ${CMAKE_SOURCE_DIR}/include/FileStream.h
        ${CMAKE_SOURCE_DIR}/include/Stack.h
        ${CMAKE_SOURCE_DIR}/include/Opcode.h
        ${CMAKE_SOURCE_DIR}/include/FFI.h
        ${CMAKE_SOURCE_DIR}/src/Execute.c
        ${CMAKE_SOURCE_DIR}/src/Program.c
        ${CMAKE_SOURCE_DIR}/src/Coroutine.c
        ${CMAKE_SOURCE_DIR}/src/FileStream.c
        ${CMAKE_SOURCE_DIR}/src/Stack.c
        ${CMAKE_SOURCE_DIR}/src/Opcode.c
        ${CMAKE_SOURCE_DIR}/src/FFI.c
)

# Rename the Z Runtime Library
set_target_properties(ZRuntimeLib PROPERTIES OUTPUT_NAME "ZLang")

# Set include directory and build macro
target_include_directories(ZRuntimeLib PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_compile_definitions(ZRuntimeLib PUBLIC
        $<$<CONFIG:Debug>:_DEBUG>
)
target_compile_definitions(ZRuntimeLib PRIVATE
        ZLANG_EXPORTS
)

# Find external libraries
find_package(PkgConfig REQUIRED)                # Linux
pkg_check_modules(LIBFFI REQUIRED libffi)       # Linux

# Include external libraries
target_include_directories(ZRuntimeLib PUBLIC
        ${LIBFFI_INCLUDE_DIRS}
)

# Link external libraries to Z Runtime Library
target_link_libraries(ZRuntimeLib PUBLIC
        #libffi::libffi         # Windows
        ${LIBFFI_LIBRARIES}     # Linux
)

# Build Z Runtime Executable
add_executable(ZRuntimeExe
        ${CMAKE_SOURCE_DIR}/include/ZLang.h
        ${CMAKE_SOURCE_DIR}/include/External.h
        ${CMAKE_SOURCE_DIR}/include/Export.h
        ${CMAKE_SOURCE_DIR}/include/Types.h
        ${CMAKE_SOURCE_DIR}/include/Error.h
        ${CMAKE_SOURCE_DIR}/include/Execute.h
        ${CMAKE_SOURCE_DIR}/include/Program.h
        ${CMAKE_SOURCE_DIR}/include/Coroutine.h
        ${CMAKE_SOURCE_DIR}/include/FileStream.h
        ${CMAKE_SOURCE_DIR}/include/Stack.h
        ${CMAKE_SOURCE_DIR}/include/Opcode.h
        ${CMAKE_SOURCE_DIR}/include/FFI.h
        ${CMAKE_SOURCE_DIR}/src/Execute.c
        ${CMAKE_SOURCE_DIR}/src/Program.c
        ${CMAKE_SOURCE_DIR}/src/Coroutine.c
        ${CMAKE_SOURCE_DIR}/src/FileStream.c
        ${CMAKE_SOURCE_DIR}/src/Stack.c
        ${CMAKE_SOURCE_DIR}/src/Opcode.c
        ${CMAKE_SOURCE_DIR}/src/FFI.c
        ${CMAKE_SOURCE_DIR}/main.c
)

# Set include directory and build macro
target_include_directories(ZRuntimeExe PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_compile_definitions(ZRuntimeExe PRIVATE
        $<$<CONFIG:Debug>:_DEBUG>
)

# Rename the Z Runtime Executable
set_target_properties(ZRuntimeExe PROPERTIES OUTPUT_NAME "Z")

# Include external libraries
target_include_directories(ZRuntimeExe PRIVATE
        ${LIBFFI_INCLUDE_DIRS}
)

# Link external libraries to Z Runtime Executable
target_link_libraries(ZRuntimeExe PRIVATE
        #libffi::libffi         # Windows
        ${LIBFFI_LIBRARIES}     # Linux
)
