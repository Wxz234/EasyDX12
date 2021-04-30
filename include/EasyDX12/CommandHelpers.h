#pragma once
#pragma comment(lib,"d3d12.lib")
#include <d3d12.h>
#include <wrl/client.h>
namespace EasyDX12 {
	inline HRESULT __cdecl CreateCommandQueue(_In_ ID3D12Device* device, _In_ D3D12_COMMAND_LIST_TYPE type,_COM_Outptr_  ID3D12CommandQueue** ppCommandQueue) {
		if (!ppCommandQueue)
			return E_INVALIDARG;
		*ppCommandQueue = nullptr;
		if (!device)
			return E_INVALIDARG;
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> myQueue;
		D3D12_COMMAND_QUEUE_DESC queueDesc = {};
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDesc.Type = type;
		HRESULT hr = device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&myQueue));
		if (FAILED(hr))
			return hr;
		*ppCommandQueue = myQueue.Detach();
		return S_OK;
	}

	inline HRESULT __cdecl CreateDirectCommandQueue(_In_ ID3D12Device* device, _COM_Outptr_  ID3D12CommandQueue** ppCommandQueue) {
		return CreateCommandQueue(device, D3D12_COMMAND_LIST_TYPE_DIRECT, ppCommandQueue);
	}

	inline HRESULT __cdecl CreateCopyCommandQueue(_In_ ID3D12Device* device, _COM_Outptr_  ID3D12CommandQueue** ppCommandQueue) {
		return CreateCommandQueue(device, D3D12_COMMAND_LIST_TYPE_COPY, ppCommandQueue);
	}

	inline HRESULT __cdecl CreateComputeCommandQueue(_In_ ID3D12Device* device, _COM_Outptr_ ID3D12CommandQueue** ppCommandQueue) {
		return CreateCommandQueue(device, D3D12_COMMAND_LIST_TYPE_COMPUTE, ppCommandQueue);
	}

	inline HRESULT __cdecl CreateCommandAllocator(_In_ ID3D12Device* device, _In_ D3D12_COMMAND_LIST_TYPE type,_COM_Outptr_ ID3D12CommandAllocator** ppCommandAllocator) {
		if (!ppCommandAllocator)
			return E_INVALIDARG;
		*ppCommandAllocator = nullptr;
		if (!device)
			return E_INVALIDARG;
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> myAlloc;
		HRESULT hr = device->CreateCommandAllocator(type, IID_PPV_ARGS(&myAlloc));
		if (FAILED(hr))
			return hr;
		*ppCommandAllocator = myAlloc.Detach();
		return S_OK;
	}

	inline HRESULT __cdecl CreateDirectCommandAllocator(_In_ ID3D12Device* device, _COM_Outptr_ ID3D12CommandAllocator** ppCommandAllocator){
		return CreateCommandAllocator(device, D3D12_COMMAND_LIST_TYPE_DIRECT, ppCommandAllocator);
	}

	inline HRESULT __cdecl CreateCopyCommandAllocator(_In_ ID3D12Device* device, _COM_Outptr_ ID3D12CommandAllocator** ppCommandAllocator) {
		return CreateCommandAllocator(device, D3D12_COMMAND_LIST_TYPE_COPY, ppCommandAllocator);
	}

	inline HRESULT __cdecl CreateComputeCommandAllocator(_In_ ID3D12Device* device, _COM_Outptr_ ID3D12CommandAllocator** ppCommandAllocator) {
		return CreateCommandAllocator(device, D3D12_COMMAND_LIST_TYPE_COMPUTE, ppCommandAllocator);
	}

	class CommandQueue {
	public:
		CommandQueue(_In_ ID3D12Device* device,_In_ D3D12_COMMAND_LIST_TYPE type) noexcept {
			CreateCommandQueue(device, type, &m_Queue);
		}
		~CommandQueue() {}

		CommandQueue(CommandQueue&&) noexcept = default;
		CommandQueue& operator=(CommandQueue&&) noexcept = default;

		CommandQueue(const CommandQueue&) = delete;
		CommandQueue& operator=(const CommandQueue&) = delete;
	private:
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_Queue;
	};
}
