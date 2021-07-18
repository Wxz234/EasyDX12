#include "pch.h"
#include <wrl/wrappers/corewrappers.h>
#include <Windows.h>

HRESULT createCommandQueue(ID3D12Device* device, D3D12_COMMAND_LIST_TYPE type, ID3D12CommandQueue** ppCommandQueue) {
	if (!ppCommandQueue)
		return E_INVALIDARG;
	*ppCommandQueue = nullptr;
	if (!device)
		return E_INVALIDARG;
	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	queueDesc.Type = type;
	return device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(ppCommandQueue));
}

HRESULT createCommandAllocator(ID3D12Device* device, D3D12_COMMAND_LIST_TYPE type, ID3D12CommandAllocator** ppCommandAllocator) {
	if (!ppCommandAllocator)
		return E_INVALIDARG;
	*ppCommandAllocator = nullptr;
	if (!device)
		return E_INVALIDARG;
	return device->CreateCommandAllocator(type, IID_PPV_ARGS(ppCommandAllocator));
}

__declspec(dllexport) HRESULT CreateDefaultDirectCommandQueue(ID3D12Device* device, ID3D12CommandQueue** ppCommandQueue) {
	return createCommandQueue(device, D3D12_COMMAND_LIST_TYPE_DIRECT, ppCommandQueue);
}

__declspec(dllexport) HRESULT CreateDefaultCopyCommandQueue(ID3D12Device* device, ID3D12CommandQueue** ppCommandQueue) {
	return createCommandQueue(device, D3D12_COMMAND_LIST_TYPE_COPY, ppCommandQueue);
}

__declspec(dllexport) HRESULT CreateDefaultComputeCommandQueue(ID3D12Device* device, ID3D12CommandQueue** ppCommandQueue) {
	return createCommandQueue(device, D3D12_COMMAND_LIST_TYPE_COMPUTE, ppCommandQueue);
}

__declspec(dllexport) HRESULT CreateDefaultDirectCommandAllocator(ID3D12Device* device, ID3D12CommandAllocator** ppCommandAllocator) {
	return createCommandAllocator(device, D3D12_COMMAND_LIST_TYPE_DIRECT, ppCommandAllocator);
}
__declspec(dllexport) HRESULT CreateDefaultCopyCommandAllocator(ID3D12Device* device, ID3D12CommandAllocator** ppCommandAllocator) {
	return createCommandAllocator(device, D3D12_COMMAND_LIST_TYPE_COPY, ppCommandAllocator);
}
__declspec(dllexport) HRESULT CreateDefaultComputeCommandAllocator(ID3D12Device* device, ID3D12CommandAllocator** ppCommandAllocator) {
	return createCommandAllocator(device, D3D12_COMMAND_LIST_TYPE_COMPUTE, ppCommandAllocator);
}

__declspec(dllexport) HRESULT FlushCommandQueue(ID3D12CommandQueue* queue, ID3D12Fence* fence, UINT64 value) {
	if (!queue || !fence)
		return E_INVALIDARG;
	HRESULT hr = queue->Signal(fence, value);
	if (FAILED(hr))
		return hr;
	Microsoft::WRL::Wrappers::Event m_fenceEvent;
	m_fenceEvent.Attach(CreateEvent(nullptr, FALSE, FALSE, nullptr));
	hr = fence->SetEventOnCompletion(value, m_fenceEvent.Get());
	if (FAILED(hr))
		return hr;
	WaitForSingleObject(m_fenceEvent.Get(), INFINITE);
	return S_OK;
}

__declspec(dllexport) HRESULT FlushCommandQueue(ID3D12CommandQueue* queue) {
	if (!queue)
		return E_INVALIDARG;
	Microsoft::WRL::ComPtr<ID3D12Device> myDevice;
	HRESULT hr = queue->GetDevice(IID_PPV_ARGS(&myDevice));
	if (FAILED(hr))
		return hr;
	Microsoft::WRL::ComPtr<ID3D12Fence> myFence;
	hr = myDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&myFence));
	if (FAILED(hr))
		return hr;
	return FlushCommandQueue(queue, myFence.Get(), 1);
}


