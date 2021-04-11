#pragma once
#pragma comment(lib,"d3d12.lib")
#include <d3d12.h>
#include <wrl/client.h>
namespace EasyDX12 {
	class MultithreadedCommand{
	public:
		MultithreadedCommand(_In_ ID3D12Device* device) noexcept : mDevice(device) {}
		virtual ~MultithreadedCommand() {}
		MultithreadedCommand(MultithreadedCommand&&) noexcept = default;
		MultithreadedCommand& operator=(MultithreadedCommand&&) noexcept = default;
		MultithreadedCommand(const MultithreadedCommand&) = delete;
		MultithreadedCommand& operator=(const MultithreadedCommand&) = delete;
	private:
		Microsoft::WRL::ComPtr<ID3D12Device> mDevice;
	};
}