#include "pch.h"

__declspec(dllexport) HRESULT CreateDefaultDevice(REFIID riid, _COM_Outptr_ void** ppDevice) {
	return D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, riid, ppDevice);
}

__declspec(dllexport) HRESULT CreateDefaultFence(
	_In_ ID3D12Device* device,
	UINT64 InitialValue,
	REFIID riid,
	_COM_Outptr_ void** ppFence) {
	if (!device)
		return E_INVALIDARG;
	return device->CreateFence(InitialValue, D3D12_FENCE_FLAG_NONE, riid, ppFence);
}

__declspec(dllexport) HRESULT CreateDefaultFactory(REFIID riid, _COM_Outptr_ void** ppFactory) {
	return CreateDXGIFactory2(0, riid, ppFactory);
}

__declspec(dllexport) HRESULT EnableDebugLayer() {
	Microsoft::WRL::ComPtr<ID3D12Debug> debugController;
	HRESULT hr = D3D12GetDebugInterface(IID_PPV_ARGS(&debugController));
	if (FAILED(hr)) {
		return hr;
	}
	debugController->EnableDebugLayer();
	return S_OK;
}
namespace _internal {
	HRESULT createDescriptorHeaps(
		_In_ ID3D12Device* device,
		UINT NumDescriptors,
		D3D12_DESCRIPTOR_HEAP_TYPE type,
		REFIID riid,
		_COM_Outptr_  void** ppvHeap) {
		if (!ppvHeap)
			return E_INVALIDARG;
		*ppvHeap = nullptr;
		if (!device)
			return E_INVALIDARG;
		D3D12_DESCRIPTOR_HEAP_DESC HeapDesc = {};
		HeapDesc.NumDescriptors = NumDescriptors;
		HeapDesc.Type = type;
		HeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		HeapDesc.NodeMask = 0;
		return device->CreateDescriptorHeap(&HeapDesc, riid, ppvHeap);
	}

	HRESULT createCommandQueue(_In_ ID3D12Device* device, D3D12_COMMAND_LIST_TYPE type, REFIID riid, _COM_Outptr_ void** ppCommandQueue) {
		if (!ppCommandQueue)
			return E_INVALIDARG;
		*ppCommandQueue = nullptr;
		if (!device)
			return E_INVALIDARG;
		D3D12_COMMAND_QUEUE_DESC queueDesc = {};
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDesc.Type = type;
		return device->CreateCommandQueue(&queueDesc, riid, ppCommandQueue);
	}
	HRESULT createCommandAllocator(_In_ ID3D12Device* device, D3D12_COMMAND_LIST_TYPE type, REFIID riid, _COM_Outptr_ void** ppCommandAllocator) {
		if (!ppCommandAllocator)
			return E_INVALIDARG;
		*ppCommandAllocator = nullptr;
		if (!device)
			return E_INVALIDARG;
		return device->CreateCommandAllocator(type, riid, ppCommandAllocator);
	}
}

__declspec(dllexport) HRESULT CreateRTVDescriptorHeap(_In_ ID3D12Device* device, UINT NumDescriptors, REFIID riid, _COM_Outptr_  void** ppvHeap) {
	return _internal::createDescriptorHeaps(device, NumDescriptors, D3D12_DESCRIPTOR_HEAP_TYPE_RTV, riid, ppvHeap);
}

__declspec(dllexport) HRESULT CreateCBVDescriptorHeap(_In_ ID3D12Device* device, UINT NumDescriptors, REFIID riid, _COM_Outptr_  void** ppvHeap) {
	return _internal::createDescriptorHeaps(device, NumDescriptors, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, riid, ppvHeap);
}

__declspec(dllexport) HRESULT CreateSRVDescriptorHeap(_In_ ID3D12Device* device, UINT NumDescriptors, REFIID riid, _COM_Outptr_  void** ppvHeap) {
	return _internal::createDescriptorHeaps(device, NumDescriptors, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, riid, ppvHeap);
}

__declspec(dllexport) HRESULT CreateUAVDescriptorHeap(_In_ ID3D12Device* device, UINT NumDescriptors, REFIID riid, _COM_Outptr_  void** ppvHeap) {
	return _internal::createDescriptorHeaps(device, NumDescriptors, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, riid, ppvHeap);
}

__declspec(dllexport) HRESULT CreateDSVDescriptorHeap(_In_ ID3D12Device* device, UINT NumDescriptors, REFIID riid, _COM_Outptr_  void** ppvHeap) {
	return _internal::createDescriptorHeaps(device, NumDescriptors, D3D12_DESCRIPTOR_HEAP_TYPE_DSV, riid, ppvHeap);
}

__declspec(dllexport) HRESULT CreateSamplerDescriptorHeap(_In_ ID3D12Device* device, UINT NumDescriptors, REFIID riid, _COM_Outptr_  void** ppvHeap) {
	return _internal::createDescriptorHeaps(device, NumDescriptors, D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER, riid, ppvHeap);
}


__declspec(dllexport) HRESULT CreateDefaultDirectCommandQueue(_In_ ID3D12Device* device, REFIID riid, _COM_Outptr_ void** ppCommandQueue) {
	return _internal::createCommandQueue(device, D3D12_COMMAND_LIST_TYPE_DIRECT, riid, ppCommandQueue);
}

__declspec(dllexport) HRESULT CreateDefaultCopyCommandQueue(_In_ ID3D12Device* device, REFIID riid, _COM_Outptr_ void** ppCommandQueue) {
	return _internal::createCommandQueue(device, D3D12_COMMAND_LIST_TYPE_COPY, riid, ppCommandQueue);
}

__declspec(dllexport) HRESULT CreateDefaultComputeCommandQueue(_In_ ID3D12Device* device, REFIID riid, _COM_Outptr_ void** ppCommandQueue) {
	return _internal::createCommandQueue(device, D3D12_COMMAND_LIST_TYPE_COMPUTE, riid, ppCommandQueue);
}

__declspec(dllexport) HRESULT CreateDefaultDirectCommandAllocator(_In_ ID3D12Device* device, REFIID riid, _COM_Outptr_ void** ppCommandAllocator) {
	return _internal::createCommandAllocator(device, D3D12_COMMAND_LIST_TYPE_DIRECT, riid, ppCommandAllocator);
}

__declspec(dllexport) HRESULT CreateDefaultCopyCommandAllocator(_In_ ID3D12Device* device, REFIID riid, _COM_Outptr_ void** ppCommandAllocator) {
	return _internal::createCommandAllocator(device, D3D12_COMMAND_LIST_TYPE_COPY, riid, ppCommandAllocator);
}

__declspec(dllexport) HRESULT CreateDefaultComputeCommandAllocator(_In_ ID3D12Device* device, REFIID riid, _COM_Outptr_ void** ppCommandAllocator) {
	return _internal::createCommandAllocator(device, D3D12_COMMAND_LIST_TYPE_COMPUTE, riid, ppCommandAllocator);
}


// __declspec(dllexport) HRESULT CreateRenderTargetView(_In_ ID3D12Device* device, _In_ ID3D12Resource* resource, REFIID riid, _COM_Outptr_ void** ppvHeap) {
// 	if (!ppvHeap) {
// 		return E_INVALIDARG;
// 	}
// 	*ppvHeap = nullptr;
// 	if (!device || !resource)
// 		return E_INVALIDARG;
// 	if (riid != IID_ID3D12DescriptorHeap) {
// 		return E_NOINTERFACE;
// 	}
// 	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> myHeap;
// 	HRESULT hr = CreateRTVDescriptorHeap(device, 1, IID_PPV_ARGS(&myHeap));
// 	if (FAILED(hr))
// 		return hr;
// 	device->CreateRenderTargetView(resource, nullptr, myHeap->GetCPUDescriptorHandleForHeapStart());
// 	*ppvHeap = myHeap.Detach();
// 	return S_OK;
// }

__declspec(dllexport) HRESULT FlushCommandQueue(_In_ ID3D12CommandQueue* queue, _In_ ID3D12Fence* fence, UINT64 value) {
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
	if (WaitForSingleObject(m_fenceEvent.Get(), INFINITE) == WAIT_FAILED) {
		return HRESULT_FROM_WIN32(GetLastError());
	}
	return S_OK;
}

__declspec(dllexport) HRESULT FlushCommandQueue(_In_ ID3D12CommandQueue* queue) {
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

__declspec(dllexport) HRESULT CreateUploadHeapBufferResource(_In_ ID3D12Device* device, _In_reads_bytes_(count) const void* data, UINT64 count, _COM_Outptr_ ID3D12Resource** ppvResource) {
	if (!ppvResource)
		return E_INVALIDARG;
	*ppvResource = nullptr;
	if (!device || !data || !count)
		return E_INVALIDARG;
	D3D12_HEAP_PROPERTIES prop = {};
	prop.Type = D3D12_HEAP_TYPE_UPLOAD;
	prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	prop.CreationNodeMask = 1;
	prop.VisibleNodeMask = 1;
	D3D12_RESOURCE_DESC desc = {};
	desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	desc.Alignment = 0;
	desc.Width = count;
	desc.Height = 1;
	desc.DepthOrArraySize = 1;
	desc.MipLevels = 1;
	desc.Format = DXGI_FORMAT_UNKNOWN;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	desc.Flags = D3D12_RESOURCE_FLAG_NONE;
	Microsoft::WRL::ComPtr<ID3D12Resource> uploadBuffer;
	HRESULT hr = device->CreateCommittedResource(
		&prop,
		D3D12_HEAP_FLAG_ALLOW_ALL_BUFFERS_AND_TEXTURES,
		&desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&uploadBuffer));
	if (FAILED(hr))
		return hr;
	UINT8* pVertexDataBegin;
	hr = uploadBuffer->Map(0, nullptr, reinterpret_cast<void**>(&pVertexDataBegin));
	if (FAILED(hr))
		return hr;
	const UINT8* myData = reinterpret_cast<const UINT8*>(data);
	for (UINT64 i = 0; i < count; ++i) {
		pVertexDataBegin[i] = myData[i];
	}
	uploadBuffer->Unmap(0, nullptr);
	*ppvResource = uploadBuffer.Detach();
	return S_OK;
}

