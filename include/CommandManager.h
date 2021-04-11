#pragma once
#pragma comment(lib,"d3d12.lib")
#include <d3d12.h>
namespace EasyDX12 {
	class CommandQueueManager {
	public:
		CommandQueueManager() noexcept {}
		~CommandQueueManager() {}
		CommandQueueManager(CommandQueueManager&&) noexcept = default;
		CommandQueueManager& operator=(CommandQueueManager&&) noexcept = default;
		CommandQueueManager(const CommandQueueManager&) = delete;
		CommandQueueManager& operator=(const CommandQueueManager&) = delete;
	private:

	};
}
