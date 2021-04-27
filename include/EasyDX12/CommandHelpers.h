#pragma once
#pragma comment(lib,"d3d12.lib")
#include <d3d12.h>
#include <wrl/client.h>
namespace EasyDX12 {
	inline HRESULT __cdecl CreateDirectCommandQueue(_In_ ID3D12Device* device, _COM_Outptr_  ID3D12CommandQueue** ppCommandQueue) {
		if (!ppCommandQueue)
			return E_INVALIDARG;
		*ppCommandQueue = nullptr;
		if (!device)
			return E_INVALIDARG;
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> myQueue;
		D3D12_COMMAND_QUEUE_DESC queueDesc = {};
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		HRESULT hr = device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&myQueue));
		if (FAILED(hr))
			return hr;
		*ppCommandQueue = myQueue.Detach();
		return S_OK;
	}

	inline HRESULT __cdecl CreateCopyCommandQueue(_In_ ID3D12Device* device, _COM_Outptr_  ID3D12CommandQueue** ppCommandQueue) {
		if (!ppCommandQueue)
			return E_INVALIDARG;
		*ppCommandQueue = nullptr;
		if (!device)
			return E_INVALIDARG;
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> myQueue;
		D3D12_COMMAND_QUEUE_DESC queueDesc = {};
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_COPY;
		HRESULT hr = device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&myQueue));
		if (FAILED(hr))
			return hr;
		*ppCommandQueue = myQueue.Detach();
		return S_OK;
	}

	inline HRESULT __cdecl CreateComputeCommandQueue(_In_ ID3D12Device* device, _COM_Outptr_  ID3D12CommandQueue** ppCommandQueue) {
		if (!ppCommandQueue)
			return E_INVALIDARG;
		*ppCommandQueue = nullptr;
		if (!device)
			return E_INVALIDARG;
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> myQueue;
		D3D12_COMMAND_QUEUE_DESC queueDesc = {};
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_COMPUTE;
		HRESULT hr = device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&myQueue));
		if (FAILED(hr))
			return hr;
		*ppCommandQueue = myQueue.Detach();
		return S_OK;
	}
}
