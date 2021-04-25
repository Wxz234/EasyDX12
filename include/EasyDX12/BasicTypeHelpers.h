#pragma once
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#include <d3d12.h>
#include <dxgi1_6.h>
#include <string>
namespace EasyDX12 {
	inline HRESULT __cdecl CreateDirectCommandQueue(_In_ ID3D12Device* device, _COM_Outptr_ ID3D12CommandQueue** ppCommandQueue) {
		D3D12_COMMAND_QUEUE_DESC queueDesc = {};
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		return device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(ppCommandQueue));
	}

	inline HRESULT __cdecl CreateCopyCommandQueue(_In_ ID3D12Device* device, _COM_Outptr_ ID3D12CommandQueue** ppCommandQueue) {
		D3D12_COMMAND_QUEUE_DESC queueDesc = {};
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_COPY;
		return device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(ppCommandQueue));
	}

	inline HRESULT __cdecl CreateComputeCommandQueue(_In_ ID3D12Device* device, _COM_Outptr_ ID3D12CommandQueue** ppCommandQueue) {
		D3D12_COMMAND_QUEUE_DESC queueDesc = {};
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_COMPUTE;
		return device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(ppCommandQueue));
	}
	inline HRESULT __cdecl CreateFactory(_COM_Outptr_ IDXGIFactory** ppFactory) {
		return CreateDXGIFactory2(0, IID_PPV_ARGS(ppFactory));
	}
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

	inline std::wstring __cdecl GetAdapterName(_In_ IDXGIAdapter *adapter) {
		if (adapter) {
			DXGI_ADAPTER_DESC desc;
			adapter->GetDesc(&desc);
			return std::wstring(desc.Description);
		}
		return L"";
	}
}
