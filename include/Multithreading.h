#pragma once
#pragma comment(lib,"d3d12.lib")
#include <d3d12.h>
#include <wrl/client.h>
namespace EasyDX12 {
	class MultithreadingCommand{
	public:
		MultithreadingCommand(_In_ ID3D12Device* device) noexcept : mDevice(device) {}
		virtual ~MultithreadingCommand() {}
		MultithreadingCommand(MultithreadingCommand&&) noexcept = default;
		MultithreadingCommand& operator=(MultithreadingCommand&&) noexcept = default;
		MultithreadingCommand(const MultithreadingCommand&) = delete;
		MultithreadingCommand& operator=(const MultithreadingCommand&) = delete;
	private:
		Microsoft::WRL::ComPtr<ID3D12Device> mDevice;
	};
}