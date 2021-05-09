#pragma once
#pragma comment(lib,"d3d12.lib")
#include <d3d12.h>
#include <wrl/client.h>
#include <cstring>
#include "CommandHelpers.h"
namespace EasyDX12 {
	inline HRESULT __cdecl CreateConstantBuffer(
		_In_ ID3D12Device* device,
		_In_reads_(count) const void* data, 
		UINT64 count, 
		_COM_Outptr_ ID3D12Resource** ppvResource) 
	{
		if (!ppvResource)
			return E_INVALIDARG;
		*ppvResource = nullptr;
		if (!device || !data ||(count == 0))
			return E_INVALIDARG;
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> myQueue;
		HRESULT hr = CreateCopyCommandQueue(device, &myQueue);
		if (FAILED(hr))
			return hr;
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> myAllocator;
		hr = CreateCopyCommandAllocator(device, &myAllocator);
		if (FAILED(hr))
			return hr;
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> myList;
		hr = device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_COPY, myAllocator.Get(), nullptr, IID_PPV_ARGS(&myList));
		if (FAILED(hr))
			return hr;
		Microsoft::WRL::ComPtr<ID3D12Resource> defaultBuffer;
		D3D12_HEAP_PROPERTIES prop = {};
		prop.Type = D3D12_HEAP_TYPE_DEFAULT;
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
		hr = device->CreateCommittedResource(
			&prop,
			D3D12_HEAP_FLAG_NONE,
			&desc,
			D3D12_RESOURCE_STATE_COMMON,
			nullptr,
			IID_PPV_ARGS(&defaultBuffer));
		if (FAILED(hr))
			return hr;
		Microsoft::WRL::ComPtr<ID3D12Resource> uploadBuffer;
		prop.Type = D3D12_HEAP_TYPE_UPLOAD;
		hr = device->CreateCommittedResource(
			&prop,
			D3D12_HEAP_FLAG_NONE,
			&desc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&uploadBuffer));
		if (FAILED(hr))
			return hr;

		UINT8* pVertexDataBegin;
		D3D12_RANGE readRange = {};
		readRange.Begin = 0;
		readRange.End = 0;
		hr = uploadBuffer->Map(0, &readRange, reinterpret_cast<void**>(&pVertexDataBegin));
		if (FAILED(hr))
			return hr;
		memcpy(pVertexDataBegin, data, count);
		uploadBuffer->Unmap(0, nullptr);

		D3D12_RESOURCE_BARRIER barrier = {};
		barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrier.Transition.pResource = defaultBuffer.Get();
		barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COMMON;
		barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_COPY_DEST;
		barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
		myList->ResourceBarrier(1, &barrier);
		myList->CopyBufferRegion(defaultBuffer.Get(), 0, uploadBuffer.Get(), 0, count);
		barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
		barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_COMMON;
		myList->ResourceBarrier(1, &barrier);
		hr = myList->Close();
		if (FAILED(hr))
			return hr;

		ID3D12CommandList* ppCommandLists[] = { myList.Get() };
		myQueue->ExecuteCommandLists(1, ppCommandLists);
		hr = FlushCommandQueue(myQueue.Get());
		if (FAILED(hr))
			return hr;
		*ppvResource = defaultBuffer.Detach();
		return S_OK;
	}
}
