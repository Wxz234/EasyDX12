#pragma once
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl/client.h>
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
		if (FAILED(hr)) {
			return hr;
		}
		if (myFence->GetCompletedValue() != 1) {
			HANDLE m_fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
			if (m_fenceEvent == nullptr) {
				return HRESULT_FROM_WIN32(GetLastError());
			}
			hr = myFence->SetEventOnCompletion(1, m_fenceEvent);
			if (FAILED(hr)) {
				CloseHandle(m_fenceEvent);
				return hr;
			}
			WaitForSingleObject(m_fenceEvent, INFINITE);
			CloseHandle(m_fenceEvent);
		}
		return S_OK;
	}

}