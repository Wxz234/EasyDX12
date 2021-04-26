#pragma once
#pragma comment(lib,"dxgi.lib")
#include <dxgi1_6.h>
#include <string>
namespace EasyDX12 {
	inline HRESULT __cdecl GetWarpAdapter(_In_ IDXGIFactory* factory, _COM_Outptr_ IDXGIAdapter** ppvAdapter) {
		IDXGIFactory4* factory4;
		factory->QueryInterface(&factory4);
		auto HR = factory4->EnumWarpAdapter(IID_PPV_ARGS(ppvAdapter));
		factory4->Release();
		return HR;
	}
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

	inline std::wstring __cdecl GetAdapterName(_In_ IDXGIAdapter* adapter) {
		if (adapter) {
			DXGI_ADAPTER_DESC desc;
			adapter->GetDesc(&desc);
			return std::wstring(desc.Description);
		}
		return L"";
	}

	inline bool __cdecl IsNVIDIAAdapter(_In_ IDXGIAdapter* adapter) {
		DXGI_ADAPTER_DESC desc;
		adapter->GetDesc(&desc);
		if (desc.VendorId == 0x10DE) {
			return true;
		}
		return false;
	}

	inline bool __cdecl IsAMDAdapter(_In_ IDXGIAdapter* adapter) {
		DXGI_ADAPTER_DESC desc;
		adapter->GetDesc(&desc);
		if (desc.VendorId == 0x1002) {
			return true;
		}
		return false;
	}

	inline bool __cdecl IsIntelAdapter(_In_ IDXGIAdapter* adapter) {
		DXGI_ADAPTER_DESC desc;
		adapter->GetDesc(&desc);
		if (desc.VendorId == 0x8086) {
			return true;
		}
		return false;
	}

}
