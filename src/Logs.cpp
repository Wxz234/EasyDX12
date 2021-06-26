#include "pch.h"

__declspec(dllexport) HRESULT D3D12Log(_In_ ID3D12Device* device,_In_ D3D12_MESSAGE_SEVERITY Severity,_In_ LPCSTR pDescription) {
	if (!device)
		return E_INVALIDARG;
	ID3D12InfoQueue* myInfo = nullptr;
	HRESULT hr = device->QueryInterface(IID_PPV_ARGS(&myInfo));
	if (FAILED(hr))
		return hr;
	hr = myInfo->AddApplicationMessage(Severity, pDescription);
	if (FAILED(hr))
		return hr;
	myInfo->Release();
	return S_OK;
}