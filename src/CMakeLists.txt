add_library(EasyDX12 SHARED Command.cpp Adapter.cpp Feature.cpp Log.cpp Resource.cpp Descriptor.cpp Global.cpp)
target_precompile_headers(EasyDX12 PRIVATE pch.h)
target_link_libraries(EasyDX12 PRIVATE dxgi d3d12)