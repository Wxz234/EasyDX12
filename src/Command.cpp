#include "pch.h"

Microsoft::WRL::ComPtr<ID3D12CommandQueue> my_queue;


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

__declspec(dllexport) HRESULT CreateDefaultDirectCommandQueue(ID3D12Device* device, ID3D12CommandQueue** ppCommandQueue) {
	return createCommandQueue(device, D3D12_COMMAND_LIST_TYPE_DIRECT, ppCommandQueue);
}

__declspec(dllexport) HRESULT CreateDefaultCopyCommandQueue(ID3D12Device* device, ID3D12CommandQueue** ppCommandQueue) {
	return createCommandQueue(device, D3D12_COMMAND_LIST_TYPE_COPY, ppCommandQueue);
}

__declspec(dllexport) HRESULT CreateDefaultComputeCommandQueue(ID3D12Device* device, ID3D12CommandQueue** ppCommandQueue) {
	return createCommandQueue(device, D3D12_COMMAND_LIST_TYPE_COMPUTE, ppCommandQueue);
}


