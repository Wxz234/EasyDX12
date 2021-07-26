#include "pch.h"

__declspec(dllexport) bool IsDirectXRaytracingSupported(ID3D12Device* device) {
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

__declspec(dllexport) bool IsMeshShaderSupported(ID3D12Device* device) {
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

__declspec(dllexport) bool IsVariableRateShadingSupported(ID3D12Device* device) {
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

__declspec(dllexport) bool IsShaderModelSupported(ID3D12Device* device, D3D_SHADER_MODEL shader_model) {
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