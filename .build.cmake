# Compilers
set(CMAKE_x86_64_C_COMPILER   "/usr/bin/i686-linux-gnu-gcc")
set(CMAKE_x86_64_CXX_COMPILER "/usr/bin/i686-linux-gnu-g++")

set(CMAKE_x64_C_COMPILER   "gcc")
set(CMAKE_x64_CXX_COMPILER "g++")

# Build info
set(TARGET_ARCH "x64")

if(${TARGET_ARCH} STREQUAL "x86_64")
    set(CMAKE_C_COMPILER   ${CMAKE_x86_64_C_COMPILER})
    set(CMAKE_CXX_COMPILER ${CMAKE_x86_64_CXX_COMPILER})
elseif(${TARGET_ARCH} STREQUAL "x64")
    set(CMAKE_C_COMPILER   ${CMAKE_x64_C_COMPILER})
    set(CMAKE_CXX_COMPILER ${CMAKE_x64_CXX_COMPILER})
else()
    message(FATAL_ERROR "ERROR: Unsupported target architecture!")
endif()