#include "pch.h"
#include <wrl/wrappers/corewrappers.h>
#include <Windows.h>


namespace ___internal_ {
	HRESULT ___createCommandQueue(ID3D12Device* device, D3D12_COMMAND_LIST_TYPE type, ID3D12CommandQueue** ppCommandQueue) {
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

	HRESULT ___FlushCommandQueue(ID3D12CommandQueue* queue, ID3D12Fence* fence, UINT64 value) {
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

	HRESULT __FlushCommandQueue(ID3D12CommandQueue* queue) {
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
		return ___FlushCommandQueue(queue, myFence.Get(), 1);
	}
}

__declspec(dllexport) HRESULT CreateUploadHeapBufferResource(ID3D12Device* device, const void* data, UINT64 count, ID3D12Resource** ppvResource) {
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

__declspec(dllexport) HRESULT CreateDefaultHeapBufferResource(
	ID3D12Device* device,
	ID3D12CommandList* cmdList,
	const void* data,
	UINT64 count,
	ID3D12Resource** ppvResource)
{
	if (!ppvResource)
		return E_INVALIDARG;
	*ppvResource = nullptr;
	if (!device || !cmdList || !data || !count)
		return E_INVALIDARG;
	Microsoft::WRL::ComPtr<ID3D12Resource> defaultBuffer;

	HRESULT hr = device->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(count),
		D3D12_RESOURCE_STATE_COMMON,
		nullptr,
		IID_PPV_ARGS(&defaultBuffer));
	if (FAILED(hr))
		return hr;
	
	Microsoft::WRL::ComPtr<ID3D12Resource> uploadBuffer;
	hr = CreateUploadHeapBufferResource(device, data, count, &uploadBuffer);
	if (FAILED(hr))
		return hr;

	D3D12_SUBRESOURCE_DATA subResourceData = {};
	subResourceData.pData = data;
	subResourceData.RowPitch = count;
	subResourceData.SlicePitch = subResourceData.RowPitch;

	Microsoft::WRL::ComPtr<ID3D12CommandList> _list(cmdList);
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> my_list;
	hr = _list.As(&my_list);
	if (FAILED(hr))
		return hr;

	my_list->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(defaultBuffer.Get(),
		D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_DEST));
	UpdateSubresources<1>(my_list.Get(), defaultBuffer.Get(), uploadBuffer.Get(), 0, 0, 1, &subResourceData);
	my_list->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(defaultBuffer.Get(),
		D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_COMMON));

	//sync
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> my_queue;
	hr = ___internal_::___createCommandQueue(device, D3D12_COMMAND_LIST_TYPE_COPY, &my_queue);
	if (FAILED(hr))
		return hr;

	hr = ___internal_::__FlushCommandQueue(my_queue.Get());
	if (FAILED(hr))
		return hr;

	*ppvResource = defaultBuffer.Detach();
	return S_OK;
}



