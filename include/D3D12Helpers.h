#pragma once
#pragma comment(lib,"d3d12.lib")
#include <d3d12.h>
namespace EasyDX12 {
	inline HRESULT __cdecl CreateDirectCommandQueue(_In_ ID3D12Device *device, _COM_Outptr_ ID3D12CommandQueue** ppCommandQueue) {
		D3D12_COMMAND_QUEUE_DESC queueDesc = {};
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		return device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(ppCommandQueue));
	}

	inline HRESULT __cdecl CreateCopyCommandQueue(_In_ ID3D12Device* device, _COM_Outptr_ ID3D12CommandQueue** ppCommandQueue) {
		D3D12_COMMAND_QUEUE_DESC queueDesc = {};
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_COPY;
		return device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(ppCommandQueue));
	}

	inline HRESULT __cdecl CreateComputeCommandQueue(_In_ ID3D12Device* device, _COM_Outptr_ ID3D12CommandQueue** ppCommandQueue) {
		D3D12_COMMAND_QUEUE_DESC queueDesc = {};
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_COMPUTE;
		return device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(ppCommandQueue));
	}
}