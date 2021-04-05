#pragma once
#pragma comment(lib,"d3d12.lib")
#include <d3d12.h>
namespace EasyDX12 {
	inline HRESULT __cdecl CreateDefaultGraphicsCommandQueue(_In_ ID3D12Device *device, _COM_Outptr_ ID3D12CommandQueue** ppCommandQueue) {
		D3D12_COMMAND_QUEUE_DESC queueDesc = {};
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		return device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(ppCommandQueue));
	}
}