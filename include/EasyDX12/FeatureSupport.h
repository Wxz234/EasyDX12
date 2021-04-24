#pragma once
#pragma comment(lib,"d3d12.lib")
#include <d3d12.h>
namespace EasyDX12 {
	inline bool __cdecl IsDirectXRaytracingSupported(_In_ ID3D12Device* device) {
		D3D12_FEATURE_DATA_D3D12_OPTIONS5 featureSupportData = {};
		if (SUCCEEDED(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS5, &featureSupportData, sizeof(featureSupportData)))
			&& featureSupportData.RaytracingTier != D3D12_RAYTRACING_TIER_NOT_SUPPORTED) {
			return true;
		}
		return false;
	}

	inline bool __cdecl IsMeshShaderSupported(_In_ ID3D12Device* device) {
		D3D12_FEATURE_DATA_D3D12_OPTIONS7 featureSupportData = {};
		if (SUCCEEDED(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS7, &featureSupportData, sizeof(featureSupportData)))
			&& featureSupportData.MeshShaderTier != D3D12_MESH_SHADER_TIER_NOT_SUPPORTED) {
			return true;
		}
		return false;
	}

	inline bool __cdecl IsShaderModel6Supported(_In_ ID3D12Device* device) {
		D3D12_FEATURE_DATA_SHADER_MODEL shaderModel = { D3D_SHADER_MODEL_6_0 };
		if (FAILED(device->CheckFeatureSupport(D3D12_FEATURE_SHADER_MODEL, &shaderModel, sizeof(shaderModel)))
			|| (shaderModel.HighestShaderModel < D3D_SHADER_MODEL_6_0))
		{
			return false;
		}
		return true;
	}

	inline bool __cdecl IsVariableRateShadingSupported(_In_ ID3D12Device* device) {
		D3D12_FEATURE_DATA_D3D12_OPTIONS6 featureSupportData = {};
		if (SUCCEEDED(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS6, &featureSupportData, sizeof(featureSupportData)))
			&& featureSupportData.VariableShadingRateTier != D3D12_VARIABLE_SHADING_RATE_TIER_NOT_SUPPORTED) {
			return true;
		}
		return false;
	}
}
