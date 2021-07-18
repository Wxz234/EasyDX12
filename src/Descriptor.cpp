#include "pch.h"

HRESULT createDescriptorHeaps(
	ID3D12Device* device,
	UINT NumDescriptors,
	D3D12_DESCRIPTOR_HEAP_TYPE type,
	_COM_Outptr_  ID3D12Heap** ppvHeap) {
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
	return device->CreateDescriptorHeap(&HeapDesc, IID_PPV_ARGS(ppvHeap));
}

__declspec(dllexport) HRESULT CreateRTVDescriptorHeap(ID3D12Device* device, UINT NumDescriptors, ID3D12Heap** ppvHeap) {
	return createDescriptorHeaps(device, NumDescriptors, D3D12_DESCRIPTOR_HEAP_TYPE_RTV, ppvHeap);
}

__declspec(dllexport) HRESULT CreateCBVDescriptorHeap(ID3D12Device* device, UINT NumDescriptors, ID3D12Heap** ppvHeap) {
	return createDescriptorHeaps(device, NumDescriptors, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,  ppvHeap);
}

__declspec(dllexport) HRESULT CreateSRVDescriptorHeap(ID3D12Device* device, UINT NumDescriptors, ID3D12Heap** ppvHeap) {
	return createDescriptorHeaps(device, NumDescriptors, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,  ppvHeap);
}

__declspec(dllexport) HRESULT CreateUAVDescriptorHeap(ID3D12Device* device, UINT NumDescriptors, ID3D12Heap** ppvHeap) {
	return createDescriptorHeaps(device, NumDescriptors, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, ppvHeap);
}

__declspec(dllexport) HRESULT CreateDSVDescriptorHeap(ID3D12Device* device, UINT NumDescriptors, ID3D12Heap** ppvHeap) {
	return createDescriptorHeaps(device, NumDescriptors, D3D12_DESCRIPTOR_HEAP_TYPE_DSV, ppvHeap);
}

__declspec(dllexport) HRESULT CreateSamplerDescriptorHeap(ID3D12Device* device, UINT NumDescriptors, ID3D12Heap** ppvHeap) {
	return createDescriptorHeaps(device, NumDescriptors, D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER,  ppvHeap);
}
