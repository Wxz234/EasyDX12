#include "pch.h"

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

//__declspec(dllexport) HRESULT CreateDefaultHeapBufferResource(
//	ID3D12Device* device,
//	const void* data,
//	UINT64 count,
//	ID3D12Resource** ppvResource)
//{
//	if (!ppvResource)
//		return E_INVALIDARG;
//	*ppvResource = nullptr;
//	if (!device || !data || !count)
//		return E_INVALIDARG;
//	Microsoft::WRL::ComPtr<ID3D12Resource> defaultBuffer;
//
//	HRESULT hr = device->CreateCommittedResource(
//		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
//		D3D12_HEAP_FLAG_NONE,
//		&CD3DX12_RESOURCE_DESC::Buffer(count),
//		D3D12_RESOURCE_STATE_COMMON,
//		nullptr,
//		IID_PPV_ARGS(&defaultBuffer));
//	if (FAILED(hr))
//		return hr;
//	//
//	Microsoft::WRL::ComPtr<ID3D12Resource> uploadBuffer;
//	hr = CreateUploadHeapBufferResource(device, data, count, &uploadBuffer);
//	if (FAILED(hr))
//		return hr;
//
//	D3D12_SUBRESOURCE_DATA subResourceData = {};
//	subResourceData.pData = data;
//	subResourceData.RowPitch = count;
//	subResourceData.SlicePitch = subResourceData.RowPitch;
//
//	{
//		auto& my_mutex = __internal_::get_mutex();
//		const std::lock_guard<std::mutex> lock(my_mutex);
//		__internal_::_reset();
//		auto& my_list = __internal_::get_list();
//		my_list->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(defaultBuffer.Get(), D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_DEST));
//		UpdateSubresources<1>(my_list.Get(), defaultBuffer.Get(), uploadBuffer.Get(), 0, 0, 1, &subResourceData);
//		my_list->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(defaultBuffer.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_COMMON));
//		hr = my_list->Close();
//		if (FAILED(hr)) {
//			return hr;
//		}
//		auto& my_queue = __internal_::get_queue();
//		ID3D12CommandList* ppCommandLists[] = { my_list.Get() };
//		my_queue->ExecuteCommandLists(1, ppCommandLists);
//		hr = __internal_::__flushCommandQueue(my_queue.Get());
//		if (FAILED(hr)) {
//			return hr;
//		}
//	}
//	*ppvResource = defaultBuffer.Detach();
//	return S_OK;
//}



