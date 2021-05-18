#pragma once
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl/client.h>
#include <cstring>
#include <limits>
#include <memory>

namespace EasyDX12 {
	namespace __internal {
		inline HRESULT __cdecl getAdapter(_In_ IDXGIFactory* factory, DXGI_GPU_PREFERENCE preference, REFIID riid, _COM_Outptr_ void** ppvAdapter) {
			if (!ppvAdapter)
				return E_INVALIDARG;
			*ppvAdapter = nullptr;
			if (!factory)
				return E_INVALIDARG;
			Microsoft::WRL::ComPtr<IDXGIFactory> myfactory(factory);
			Microsoft::WRL::ComPtr<IDXGIFactory6> myfactory6;
			HRESULT hr = myfactory.As(&myfactory6);
			if (FAILED(hr))
				return hr;
			return myfactory6->EnumAdapterByGpuPreference(0, preference, riid, ppvAdapter);
		}

		inline bool __cdecl is_adapter(_In_ IDXGIAdapter* adapter, UINT vendorId) {
			if (!adapter)
				return false;
			DXGI_ADAPTER_DESC desc;
			HRESULT hr = adapter->GetDesc(&desc);
			if (FAILED(hr) || (desc.VendorId != vendorId))
				return false;
			return true;
		}

		inline HRESULT __cdecl createCommandQueue(_In_ ID3D12Device* device, D3D12_COMMAND_LIST_TYPE type, REFIID riid, _COM_Outptr_ void** ppCommandQueue) {
			if (!ppCommandQueue)
				return E_INVALIDARG;
			*ppCommandQueue = nullptr;
			if (!device)
				return E_INVALIDARG;
			D3D12_COMMAND_QUEUE_DESC queueDesc = {};
			queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
			queueDesc.Type = type;
			return device->CreateCommandQueue(&queueDesc, riid, ppCommandQueue);
		}

		inline HRESULT __cdecl createCommandAllocator(_In_ ID3D12Device* device, D3D12_COMMAND_LIST_TYPE type, REFIID riid, _COM_Outptr_ void** ppCommandAllocator) {
			if (!ppCommandAllocator)
				return E_INVALIDARG;
			*ppCommandAllocator = nullptr;
			if (!device)
				return E_INVALIDARG;
			return device->CreateCommandAllocator(type, riid, ppCommandAllocator);
		}

		inline void* memcpy_u64(void* _Dst, void const* _Src, UINT64 _Size) {
			if (_Size <= std::numeric_limits<std::size_t>::max()) {
				return std::memcpy(_Dst, _Src, static_cast<std::size_t>(_Size));
			}
			const char* csrc = (const char*)_Src;
			char* cdest = (char*)_Dst;
			for (UINT64 i = 0; i < _Size; ++i)
				cdest[i] = csrc[i];
			return _Dst;
		}

		struct handle_closer { 
			void operator()(HANDLE h) noexcept { 
				if (h && h != INVALID_HANDLE_VALUE) {
					CloseHandle(h);
				} 
			} 
		};
		using ScopedHandle = std::unique_ptr<void, handle_closer>;
		inline HANDLE safe_handle(HANDLE h) noexcept { return (h == INVALID_HANDLE_VALUE) ? nullptr : h; }
	}

	inline HRESULT __cdecl GetWarpAdapter(_In_ IDXGIFactory* factory, REFIID riid, _COM_Outptr_ void** ppvAdapter) {
		if (!ppvAdapter)
			return E_INVALIDARG;
		*ppvAdapter = nullptr;
		if (!factory)
			return E_INVALIDARG;
		Microsoft::WRL::ComPtr<IDXGIFactory> myfactory(factory);
		Microsoft::WRL::ComPtr<IDXGIFactory4> myfactory4;
		HRESULT hr = myfactory.As(&myfactory4);
		if (FAILED(hr))
			return hr;
		return myfactory4->EnumWarpAdapter(riid, ppvAdapter);
	}

	inline HRESULT __cdecl GetDefaultAdapter(_In_ IDXGIFactory* factory, REFIID riid, _COM_Outptr_ void** ppvAdapter) {
		return __internal::getAdapter(factory, DXGI_GPU_PREFERENCE_UNSPECIFIED, riid, ppvAdapter);
	}

	inline HRESULT __cdecl GetMinimumPowerAdapter(_In_ IDXGIFactory* factory, REFIID riid, _COM_Outptr_ void** ppvAdapter) {
		return __internal::getAdapter(factory, DXGI_GPU_PREFERENCE_MINIMUM_POWER, riid, ppvAdapter);
	}

	inline HRESULT __cdecl GetHighPerformanceAdapter(_In_ IDXGIFactory* factory, REFIID riid, _COM_Outptr_ void** ppvAdapter) {
		return __internal::getAdapter(factory, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, riid, ppvAdapter);
	}

	inline bool __cdecl IsNVIDIAAdapter(_In_ IDXGIAdapter* adapter) {
		return __internal::is_adapter(adapter, 0x10DE);
	}

	inline bool __cdecl IsAMDAdapter(_In_ IDXGIAdapter* adapter) {
		return __internal::is_adapter(adapter, 0x1002);
	}

	inline bool __cdecl IsIntelAdapter(_In_ IDXGIAdapter* adapter) {
		return __internal::is_adapter(adapter, 0x8086);
	}

	inline bool __cdecl IsWarpAdapter(_In_ IDXGIAdapter* adapter) {
		return __internal::is_adapter(adapter, 0x1414);
	}

	inline HRESULT __cdecl CreateDirectCommandQueue(_In_ ID3D12Device* device, REFIID riid, _COM_Outptr_ void** ppCommandQueue) {
		return __internal::createCommandQueue(device, D3D12_COMMAND_LIST_TYPE_DIRECT, riid, ppCommandQueue);
	}

	inline HRESULT __cdecl CreateCopyCommandQueue(_In_ ID3D12Device* device, REFIID riid, _COM_Outptr_ void** ppCommandQueue) {
		return __internal::createCommandQueue(device, D3D12_COMMAND_LIST_TYPE_COPY, riid, ppCommandQueue);
	}

	inline HRESULT __cdecl CreateComputeCommandQueue(_In_ ID3D12Device* device, REFIID riid, _COM_Outptr_ void** ppCommandQueue) {
		return __internal::createCommandQueue(device, D3D12_COMMAND_LIST_TYPE_COMPUTE, riid, ppCommandQueue);
	}

	inline HRESULT __cdecl CreateDirectCommandAllocator(_In_ ID3D12Device* device, REFIID riid, _COM_Outptr_ void** ppCommandAllocator) {
		return __internal::createCommandAllocator(device, D3D12_COMMAND_LIST_TYPE_DIRECT, riid, ppCommandAllocator);
	}

	inline HRESULT __cdecl CreateCopyCommandAllocator(_In_ ID3D12Device* device, REFIID riid, _COM_Outptr_ void** ppCommandAllocator) {
		return __internal::createCommandAllocator(device, D3D12_COMMAND_LIST_TYPE_COPY, riid, ppCommandAllocator);
	}

	inline HRESULT __cdecl CreateComputeCommandAllocator(_In_ ID3D12Device* device, REFIID riid, _COM_Outptr_ void** ppCommandAllocator) {
		return __internal::createCommandAllocator(device, D3D12_COMMAND_LIST_TYPE_COMPUTE, riid, ppCommandAllocator);
	}

	inline bool __cdecl IsDirectXRaytracingSupported(_In_ ID3D12Device* device) {
		if (!device) {
			return false;
		}
		D3D12_FEATURE_DATA_D3D12_OPTIONS5 featureSupportData = {};
		if (SUCCEEDED(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS5, &featureSupportData, sizeof(featureSupportData)))
			&& featureSupportData.RaytracingTier != D3D12_RAYTRACING_TIER_NOT_SUPPORTED) {
			return true;
		}
		return false;
	}

	inline bool __cdecl IsMeshShaderSupported(_In_ ID3D12Device* device) {
		if (!device) {
			return false;
		}
		D3D12_FEATURE_DATA_D3D12_OPTIONS7 featureSupportData = {};
		if (SUCCEEDED(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS7, &featureSupportData, sizeof(featureSupportData)))
			&& featureSupportData.MeshShaderTier != D3D12_MESH_SHADER_TIER_NOT_SUPPORTED) {
			return true;
		}
		return false;
	}

	inline bool __cdecl IsVariableRateShadingSupported(_In_ ID3D12Device* device) {
		if (!device) {
			return false;
		}
		D3D12_FEATURE_DATA_D3D12_OPTIONS6 featureSupportData = {};
		if (SUCCEEDED(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS6, &featureSupportData, sizeof(featureSupportData)))
			&& featureSupportData.VariableShadingRateTier != D3D12_VARIABLE_SHADING_RATE_TIER_NOT_SUPPORTED) {
			return true;
		}
		return false;
	}

	inline bool __cdecl IsShaderModelSupported(_In_ ID3D12Device* device, D3D_SHADER_MODEL shader_model) {
		if (!device) {
			return false;
		}
		D3D12_FEATURE_DATA_SHADER_MODEL shaderModel = { shader_model };
		if (FAILED(device->CheckFeatureSupport(D3D12_FEATURE_SHADER_MODEL, &shaderModel, sizeof(shaderModel)))
			|| (shaderModel.HighestShaderModel < shader_model)) {
			return false;
		}
		return true;
	}

	inline HRESULT __cdecl FlushCommandQueue(_In_ ID3D12CommandQueue* queue) {
		if (!queue)
			return E_INVALIDARG;
		Microsoft::WRL::ComPtr<ID3D12Device> myDevice;
		HRESULT hr = queue->GetDevice(IID_PPV_ARGS(&myDevice));
		if (FAILED(hr))
			return hr;
		Microsoft::WRL::ComPtr<ID3D12Fence> myFence;
		hr = myDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&myFence));
		if (FAILED(hr))
			return hr;
		hr = queue->Signal(myFence.Get(), 1);
		if (FAILED(hr))
			return hr;
		if (myFence->GetCompletedValue() != 1) {
			__internal::ScopedHandle m_fenceEvent(__internal::safe_handle(CreateEvent(nullptr, FALSE, FALSE, nullptr)));
			if (m_fenceEvent.get() == nullptr) {
				return HRESULT_FROM_WIN32(GetLastError());
			}
			hr = myFence->SetEventOnCompletion(1, m_fenceEvent.get());
			if (FAILED(hr)) {
				return hr;
			}
			if (WaitForSingleObject(m_fenceEvent.get(), INFINITE) == WAIT_FAILED) {
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}
		return S_OK;
	}

	inline HRESULT __cdecl CreateConstantBuffer(
		_In_ ID3D12Device* device,
		_In_reads_bytes_(count) const void* data,
		UINT64 count,
		_COM_Outptr_ ID3D12Resource** ppvResource) {
		if (!ppvResource)
			return E_INVALIDARG;
		*ppvResource = nullptr;
		if (!device || !data || (count == 0))
			return E_INVALIDARG;

		Microsoft::WRL::ComPtr<ID3D12CommandQueue> myQueue;
		HRESULT hr = CreateCopyCommandQueue(device, IID_PPV_ARGS(&myQueue));
		if (FAILED(hr))
			return hr;
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> myAllocator;
		hr = CreateCopyCommandAllocator(device, IID_PPV_ARGS(&myAllocator));
		if (FAILED(hr))
			return hr;
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> myList;
		hr = device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_COPY, myAllocator.Get(), nullptr, IID_PPV_ARGS(&myList));
		if (FAILED(hr))
			return hr;
		Microsoft::WRL::ComPtr<ID3D12Resource> defaultBuffer;
		D3D12_HEAP_PROPERTIES prop = {};
		prop.Type = D3D12_HEAP_TYPE_DEFAULT;
		prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
		prop.CreationNodeMask = 1;
		prop.VisibleNodeMask = 1;
		D3D12_RESOURCE_DESC desc = {};
		desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		desc.Alignment = 0;
		desc.Width = count;
		desc.Height = 1;
		desc.DepthOrArraySize = 1;
		desc.MipLevels = 1;
		desc.Format = DXGI_FORMAT_UNKNOWN;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
		desc.Flags = D3D12_RESOURCE_FLAG_NONE;
		hr = device->CreateCommittedResource(
			&prop,
			D3D12_HEAP_FLAG_NONE,
			&desc,
			D3D12_RESOURCE_STATE_COMMON,
			nullptr,
			IID_PPV_ARGS(&defaultBuffer));
		if (FAILED(hr))
			return hr;
		Microsoft::WRL::ComPtr<ID3D12Resource> uploadBuffer;
		prop.Type = D3D12_HEAP_TYPE_UPLOAD;
		hr = device->CreateCommittedResource(
			&prop,
			D3D12_HEAP_FLAG_NONE,
			&desc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&uploadBuffer));
		if (FAILED(hr))
			return hr;
		UINT8* pVertexDataBegin;
		hr = uploadBuffer->Map(0, nullptr, reinterpret_cast<void**>(&pVertexDataBegin));
		if (FAILED(hr))
			return hr;
		__internal::memcpy_u64(pVertexDataBegin, data, count);
		uploadBuffer->Unmap(0, nullptr);

		D3D12_RESOURCE_BARRIER barrier = {};
		barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrier.Transition.pResource = defaultBuffer.Get();
		barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COMMON;
		barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_COPY_DEST;
		barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
		myList->ResourceBarrier(1, &barrier);
		myList->CopyBufferRegion(defaultBuffer.Get(), 0, uploadBuffer.Get(), 0, count);
		barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
		barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_COMMON;
		myList->ResourceBarrier(1, &barrier);
		hr = myList->Close();
		if (FAILED(hr))
			return hr;
		ID3D12CommandList* ppCommandLists[] = { myList.Get() };
		myQueue->ExecuteCommandLists(1, ppCommandLists);
		hr = FlushCommandQueue(myQueue.Get());
		if (FAILED(hr))
			return hr;
		*ppvResource = defaultBuffer.Detach();
		return S_OK;
	}
}
