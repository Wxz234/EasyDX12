#pragma once
#pragma comment(lib,"dxgi.lib")
#include <dxgi1_6.h>
#include <wrl/client.h>
#include <string>
namespace EasyDX12 {
	inline HRESULT __cdecl GetWarpAdapter(_In_ IDXGIFactory* factory, _COM_Outptr_ IDXGIAdapter** ppvAdapter) {
		if (!ppvAdapter)
			return E_INVALIDARG;
		*ppvAdapter = nullptr;
		if (!factory)
			return E_INVALIDARG;

		Microsoft::WRL::ComPtr<IDXGIFactory> myfactory(factory);
		Microsoft::WRL::ComPtr<IDXGIFactory4> myfactory4;
		HRESULT hr = myfactory.As(&myfactory4);
		if (FAILED(hr))
			return hr;
		Microsoft::WRL::ComPtr<IDXGIAdapter> myadapter;
		hr = myfactory4->EnumWarpAdapter(IID_PPV_ARGS(&myadapter));
		if (FAILED(hr))
			return hr;
		*ppvAdapter = myadapter.Detach();
		return S_OK;
	}

	inline HRESULT __cdecl GetDefaultAdapter(_In_ IDXGIFactory* factory, _COM_Outptr_ IDXGIAdapter** ppvAdapter) {
		if (!ppvAdapter)
			return E_INVALIDARG;
		*ppvAdapter = nullptr;
		if (!factory)
			return E_INVALIDARG;
		Microsoft::WRL::ComPtr<IDXGIAdapter> myadapter;
		HRESULT hr = factory->EnumAdapters(0, &myadapter);
		if (FAILED(hr))
			return hr;
		*ppvAdapter = myadapter.Detach();
		return S_OK;
	}

	inline HRESULT __cdecl GetHighPerformanceAdapter(_In_ IDXGIFactory* factory, _COM_Outptr_ IDXGIAdapter** ppvAdapter) {
		if (!ppvAdapter)
			return E_INVALIDARG;
		*ppvAdapter = nullptr;
		if (!factory)
			return E_INVALIDARG;

		Microsoft::WRL::ComPtr<IDXGIFactory> myfactory(factory);
		Microsoft::WRL::ComPtr<IDXGIFactory6> myfactory6;
		HRESULT hr = myfactory.As(&myfactory6);
		if (FAILED(hr))
			return hr;
		Microsoft::WRL::ComPtr<IDXGIAdapter> myadapter;
		hr = myfactory6->EnumAdapterByGpuPreference(0, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&myadapter));
		if (FAILED(hr))
			return hr;
		*ppvAdapter = myadapter.Detach();
		return S_OK;
	}
	inline HRESULT __cdecl GetMinimumPowerAdapter(_In_ IDXGIFactory* factory, _COM_Outptr_ IDXGIAdapter** ppvAdapter) {
		if (!ppvAdapter)
			return E_INVALIDARG;
		*ppvAdapter = nullptr;
		if (!factory)
			return E_INVALIDARG;

		Microsoft::WRL::ComPtr<IDXGIFactory> myfactory(factory);
		Microsoft::WRL::ComPtr<IDXGIFactory6> myfactory6;
		HRESULT hr = myfactory.As(&myfactory6);
		if (FAILED(hr))
			return hr;
		Microsoft::WRL::ComPtr<IDXGIAdapter> myadapter;
		hr = myfactory6->EnumAdapterByGpuPreference(0, DXGI_GPU_PREFERENCE_MINIMUM_POWER, IID_PPV_ARGS(&myadapter));
		if (FAILED(hr))
			return hr;
		*ppvAdapter = myadapter.Detach();
		return S_OK;
	}

	inline std::wstring __cdecl GetAdapterName(_In_ IDXGIAdapter* adapter) {
		if (!adapter)
			return L"";
		DXGI_ADAPTER_DESC desc;
		HRESULT hr = adapter->GetDesc(&desc);
		if (FAILED(hr))
			return L"";
		return std::wstring(desc.Description);
	}

	inline bool __cdecl IsNVIDIAAdapter(_In_ IDXGIAdapter* adapter) {
		if (!adapter)
			return false;
		DXGI_ADAPTER_DESC desc;
		HRESULT hr = adapter->GetDesc(&desc);
		if (FAILED(hr))
			return false;
		if (desc.VendorId == 0x10DE) {
			return true;
		}
		return false;
	}

	inline bool __cdecl IsAMDAdapter(_In_ IDXGIAdapter* adapter) {
		if (!adapter)
			return false;
		DXGI_ADAPTER_DESC desc;
		HRESULT hr = adapter->GetDesc(&desc);
		if (FAILED(hr))
			return false;
		if (desc.VendorId == 0x1002) {
			return true;
		}
		return false;
	}

	inline bool __cdecl IsIntelAdapter(_In_ IDXGIAdapter* adapter) {
		if (!adapter)
			return false;
		DXGI_ADAPTER_DESC desc;
		HRESULT hr = adapter->GetDesc(&desc);
		if (FAILED(hr))
			return false;
		if (desc.VendorId == 0x8086) {
			return true;
		}
		return false;
	}

	inline bool __cdecl IsWarpAdapter(_In_ IDXGIAdapter* adapter) {
		if (!adapter)
			return false;
		DXGI_ADAPTER_DESC desc;
		HRESULT hr = adapter->GetDesc(&desc);
		if (FAILED(hr))
			return false;
		if (desc.VendorId == 0x1414) {
			return true;
		}
		return false;
	}

}
