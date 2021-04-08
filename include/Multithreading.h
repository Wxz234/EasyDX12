#pragma once
#pragma comment(lib,"d3d12.lib")
#include <d3d12.h>
#include <wrl/client.h>
namespace EasyDX12 {
	class MultithreadingCommandLists {
	public:
		MultithreadingCommandLists(_In_ ID3D12Device* device) noexcept : mDevice(device) {}
		virtual ~MultithreadingCommandLists() {}

		MultithreadingCommandLists(MultithreadingCommandLists&&) noexcept = default;
		MultithreadingCommandLists& operator=(MultithreadingCommandLists&&) noexcept = default;

		MultithreadingCommandLists(const MultithreadingCommandLists&) = delete;
		MultithreadingCommandLists& operator=(const MultithreadingCommandLists&) = delete;

		void Execute(_In_ ID3D12CommandQueue *queue) {}
	private:
		Microsoft::WRL::ComPtr<ID3D12Device> mDevice;
	};
}