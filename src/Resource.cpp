#include "pch.h"
#include <wrl/wrappers/corewrappers.h>
#include <Windows.h>
#include <mutex>
#include <vector>

namespace __internal_ {

	std::mutex& get_mutex() {
		static std::mutex __my_mutex;
		return __my_mutex;
	}


	Microsoft::WRL::ComPtr<ID3D12Device> createDevice() {
		Microsoft::WRL::ComPtr<ID3D12Device> mydevice;
		D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&mydevice));
		return mydevice;
	}
	Microsoft::WRL::ComPtr<ID3D12Device>& get_device() {
		static Microsoft::WRL::ComPtr<ID3D12Device> deivce = createDevice();
		return deivce;
	}

	Microsoft::WRL::ComPtr<ID3D12CommandQueue> createQueue() {
		D3D12_COMMAND_QUEUE_DESC queueDesc = {};
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_COPY;
		auto& device = get_device();
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> myqueue;
		device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&myqueue));
		return myqueue;
	}

	Microsoft::WRL::ComPtr<ID3D12CommandQueue>& get_queue() {
		static Microsoft::WRL::ComPtr<ID3D12CommandQueue> queue = createQueue();
		return queue;
	}

	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> createAlloc() {
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> myalloc;
		auto& device = get_device();
		device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_COPY, IID_PPV_ARGS(&myalloc));
		return myalloc;
	}

	Microsoft::WRL::ComPtr<ID3D12CommandAllocator>& get_alloc() {
		static Microsoft::WRL::ComPtr<ID3D12CommandAllocator> alloc = createAlloc();
		return alloc;
	}

	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> createList() {
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> mylist;
		auto& device = get_device();
		auto& alloc = get_alloc();
		device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_COPY, alloc.Get(), nullptr, IID_PPV_ARGS(&mylist));
		mylist->Close();
		return mylist;
	}

	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>& get_list() {
		static Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> list = createList();
		return list;
	}


	HRESULT _flushCommandQueue(ID3D12CommandQueue* queue, ID3D12Fence* fence, UINT64 value) {
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

	HRESULT __flushCommandQueue(ID3D12CommandQueue* queue) {
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
		return _flushCommandQueue(queue, myFence.Get(), 1);
	}

	void _reset() {
		auto& alloc = get_alloc();
		auto& list = get_list();
		alloc->Reset();
		list->Reset(alloc.Get(), nullptr);
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
	const void* data,
	UINT64 count,
	ID3D12Resource** ppvResource)
{
	if (!ppvResource)
		return E_INVALIDARG;
	*ppvResource = nullptr;
	if (!device || !data || !count)
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
	//
	Microsoft::WRL::ComPtr<ID3D12Resource> uploadBuffer;
	hr = CreateUploadHeapBufferResource(device, data, count, &uploadBuffer);
	if (FAILED(hr))
		return hr;

	D3D12_SUBRESOURCE_DATA subResourceData = {};
	subResourceData.pData = data;
	subResourceData.RowPitch = count;
	subResourceData.SlicePitch = subResourceData.RowPitch;

	{
		const std::lock_guard<std::mutex> lock(__internal_::get_mutex());
		__internal_::_reset();
		auto& my_list = __internal_::get_list();
		my_list->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(defaultBuffer.Get(), D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_DEST));
		UpdateSubresources<1>(my_list.Get(), defaultBuffer.Get(), uploadBuffer.Get(), 0, 0, 1, &subResourceData);
		my_list->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(defaultBuffer.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_COMMON));
		hr = my_list->Close();
		if (FAILED(hr)) {
			return hr;
		}
		auto& my_queue = __internal_::get_queue();
		ID3D12CommandList* ppCommandLists[] = { my_list.Get() };
		my_queue->ExecuteCommandLists(1, ppCommandLists);
		hr = __internal_::__flushCommandQueue(my_queue.Get());
		if (FAILED(hr)) {
			return hr;
		}
	}
	*ppvResource = defaultBuffer.Detach();
	return S_OK;
}



