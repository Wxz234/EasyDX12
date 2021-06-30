cmake_minimum_required (VERSION 3.16)
add_library(EasyDX12 SHARED EasyDX12.cpp Adapter.cpp DXObject.cpp Feature.cpp Logs.cpp)
target_precompile_headers(EasyDX12 PRIVATE pch.h)
target_link_libraries(EasyDX12 PRIVATE dxgi d3d12)
