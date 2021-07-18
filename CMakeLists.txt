cmake_minimum_required (VERSION 3.16)
project ("EasyDX12")
IF (WIN32)
	set(CMAKE_SYSTEM_NAME Windows)
	set(CMAKE_SYSTEM_VERSION 10.0.19041.0)

	FILE(GLOB_RECURSE Headers "include/*.h")
	add_subdirectory ("src")
ELSE()
	MESSAGE("Not supported!")
ENDIF()


