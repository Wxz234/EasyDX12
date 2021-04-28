#pragma once
#pragma comment(lib,"d3d12.lib")
#include <d3d12.h>
namespace EasyDX12 {
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

	inline bool __cdecl IsShaderModelSupported(_In_ ID3D12Device* device,_In_ D3D_SHADER_MODEL shader_model) {
		if (!device) {
			return false;
		}
		D3D12_FEATURE_DATA_SHADER_MODEL shaderModel = { shader_model };
		if (FAILED(device->CheckFeatureSupport(D3D12_FEATURE_SHADER_MODEL, &shaderModel, sizeof(shaderModel)))
			|| (shaderModel.HighestShaderModel < shader_model)){
			return false;
		}
		return true;
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

	//从UE4抄的。创建factory5成功就支持HDR，我也不太理解
	inline bool __cdecl IsHDRSupported() {
		Microsoft::WRL::ComPtr<IDXGIFactory5> myFactory;
		HRESULT hr = CreateDXGIFactory2(0, IID_PPV_ARGS(&myFactory));
		if (SUCCEEDED(hr) && myFactory.Get()) {
			return true;
		}
		return false;
	}
}
