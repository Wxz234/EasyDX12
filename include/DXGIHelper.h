#pragma once
#pragma comment(lib,"dxgi.lib")
#include <dxgi1_6.h>

namespace EasyDX12 {
	inline HRESULT __cdecl GetDefaultAdapter(_In_ IDXGIFactory* factory, _COM_Outptr_ IDXGIAdapter** ppvAdapter) {
		return factory->EnumAdapters(0, ppvAdapter);
	}
	inline HRESULT __cdecl GetHighPerformanceAdapter(_In_ IDXGIFactory* factory, _COM_Outptr_ IDXGIAdapter** ppvAdapter) {
		IDXGIFactory6* factory6;
		factory->QueryInterface(&factory6);
		auto HR = factory6->EnumAdapterByGpuPreference(0, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(ppvAdapter));
		factory6->Release();
		return HR;
	}
	inline HRESULT __cdecl GetMinimumPowerAdapter(_In_ IDXGIFactory* factory, _COM_Outptr_ IDXGIAdapter** ppvAdapter) {
		IDXGIFactory6* factory6;
		factory->QueryInterface(&factory6);
		auto HR = factory6->EnumAdapterByGpuPreference(0, DXGI_GPU_PREFERENCE_MINIMUM_POWER, IID_PPV_ARGS(ppvAdapter));
		factory6->Release();
		return HR;
	}
}