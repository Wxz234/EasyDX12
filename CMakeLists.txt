cmake_minimum_required (VERSION 3.16)
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_VERSION 10.0.19041.0)
set(CMAKE_CXX_STANDARD 17) 
project ("EasyDX12")
FILE(GLOB_RECURSE Headers "include/*.h")
add_subdirectory("src")



