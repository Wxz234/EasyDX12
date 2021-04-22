#pragma once
namespace EasyDX12 {
	class FXAA {
	public:
		FXAA() {}
		~FXAA() {}
		FXAA(FXAA&&) noexcept = default;
		FXAA& operator=(FXAA&&) noexcept = default;
		FXAA(const FXAA&) = delete;
		FXAA& operator=(const FXAA&) = delete;
	private:
	};

}