#include "pch.h"

HRESULT getAdapter(IDXGIFactory* factory, DXGI_GPU_PREFERENCE preference, IDXGIAdapter** ppvAdapter) {
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
	return myfactory6->EnumAdapterByGpuPreference(0, preference, IID_PPV_ARGS(ppvAdapter));
}

bool is_adapter(IDXGIAdapter* adapter, UINT vendorId) {
	if (!adapter)
		return false;
	DXGI_ADAPTER_DESC desc;
	HRESULT hr = adapter->GetDesc(&desc);
	if (FAILED(hr) || (desc.VendorId != vendorId))
		return false;
	return true;
}

__declspec(dllexport) HRESULT GetWarpAdapter(IDXGIFactory* factory, IDXGIAdapter** ppvAdapter) {
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
	return myfactory4->EnumWarpAdapter(IID_PPV_ARGS(ppvAdapter));
}
//__declspec(dllexport) HRESULT GetWarpAdapter(_In_ IDXGIFactory* factory, REFIID riid, _COM_Outptr_ void** ppvAdapter){
//	if (!ppvAdapter)
//		return E_INVALIDARG;
//	*ppvAdapter = nullptr;
//	if (!factory)
//		return E_INVALIDARG;
//	Microsoft::WRL::ComPtr<IDXGIFactory> myfactory(factory);
//	Microsoft::WRL::ComPtr<IDXGIFactory4> myfactory4;
//	HRESULT hr = myfactory.As(&myfactory4);
//	if (FAILED(hr))
//		return hr;
//	return myfactory4->EnumWarpAdapter(riid, ppvAdapter);
//}
//
//__declspec(dllexport) HRESULT  GetDefaultAdapter(_In_ IDXGIFactory* factory, REFIID riid, _COM_Outptr_ void** ppvAdapter) {
//	return getAdapter(factory, DXGI_GPU_PREFERENCE_UNSPECIFIED, riid, ppvAdapter);
//}
//
//__declspec(dllexport) HRESULT GetMinimumPowerAdapter(_In_ IDXGIFactory* factory, REFIID riid, _COM_Outptr_ void** ppvAdapter) {
//	return getAdapter(factory, DXGI_GPU_PREFERENCE_MINIMUM_POWER, riid, ppvAdapter);
//}
//
//__declspec(dllexport) HRESULT GetHighPerformanceAdapter(_In_ IDXGIFactory* factory, REFIID riid, _COM_Outptr_ void** ppvAdapter) {
//	return getAdapter(factory, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, riid, ppvAdapter);
//}
//
__declspec(dllexport) bool IsNVIDIAAdapter(IDXGIAdapter* adapter) {
	return is_adapter(adapter, 0x10DE);
}

__declspec(dllexport) bool IsAMDAdapter(IDXGIAdapter* adapter) {
	return is_adapter(adapter, 0x1002);
}

__declspec(dllexport) bool IsIntelAdapter(IDXGIAdapter* adapter) {
	return is_adapter(adapter, 0x8086);
}

__declspec(dllexport) bool IsWarpAdapter(IDXGIAdapter* adapter) {
	return is_adapter(adapter, 0x1414);
}
