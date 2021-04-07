#pragma once
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#include <d3d12.h>
#include <dxgi1_6.h>
#include <thread>
namespace EasyDX12 {
	class MultithreadingCommandLists {
	public:
		MultithreadingCommandLists(_In_ ID3D12CommandQueue* queue) {}
		virtual ~MultithreadingCommandLists() {}

		MultithreadingCommandLists(MultithreadingCommandLists&&) noexcept = default;
		MultithreadingCommandLists& operator=(MultithreadingCommandLists&&) noexcept = default;

		MultithreadingCommandLists(const MultithreadingCommandLists&) = delete;
		MultithreadingCommandLists& operator=(const MultithreadingCommandLists&) = delete;
	private:
	};
}