#include "pch.h"
#include <Windows.h>


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

__declspec(dllexport) HRESULT CreateDefalutHeapBufferResource(ID3D12Device* device, const void* data, UINT64 count, ID3D12Resource** ppvResource) {

}


