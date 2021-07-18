cmake_minimum_required (VERSION 3.16)
project ("EasyDX12")
set(CMAKE_SYSTEM_NAME Windows)
message(${CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION})
set(CMAKE_SYSTEM_VERSION 10.0.19041.0)

set(CMAKE_CXX_STANDARD 17) 
FILE(GLOB_RECURSE Headers "include/*.h")
add_subdirectory("src")



