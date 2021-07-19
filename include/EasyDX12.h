#pragma once
#ifndef _EASYDX12_H_
#define _EASYDX12_H_
#include <d3d12.h>
#include <dxgi.h>
#include <d3d12sdklayers.h>
#include <sal.h>

HRESULT GetDefaultAdapter(_In_ IDXGIFactory* factory, _COM_Outptr_ IDXGIAdapter** ppvAdapter);
HRESULT GetMinimumPowerAdapter(_In_ IDXGIFactory* factory, _COM_Outptr_ IDXGIAdapter** ppvAdapter);
HRESULT GetHighPerformanceAdapter(_In_ IDXGIFactory* factory, _COM_Outptr_ IDXGIAdapter** ppvAdapter);
HRESULT GetWarpAdapter(_In_ IDXGIFactory* factory, _COM_Outptr_ IDXGIAdapter** ppvAdapter);
bool IsNVIDIAAdapter(_In_ IDXGIAdapter* adapter);
bool IsAMDAdapter(_In_ IDXGIAdapter* adapter);
bool IsIntelAdapter(_In_ IDXGIAdapter* adapter);
bool IsWarpAdapter(_In_ IDXGIAdapter* adapter);
HRESULT CreateRTVDescriptorHeap(_In_ ID3D12Device* device, _In_ UINT NumDescriptors, _COM_Outptr_  ID3D12Heap** ppvHeap);
HRESULT CreateCBVDescriptorHeap(_In_ ID3D12Device* device, _In_ UINT NumDescriptors, _COM_Outptr_  ID3D12Heap** ppvHeap);
HRESULT CreateSRVDescriptorHeap(_In_ ID3D12Device* device, _In_ UINT NumDescriptors, _COM_Outptr_  ID3D12Heap** ppvHeap);
HRESULT CreateUAVDescriptorHeap(_In_ ID3D12Device* device, _In_ UINT NumDescriptors, _COM_Outptr_  ID3D12Heap** ppvHeap);
HRESULT CreateDSVDescriptorHeap(_In_ ID3D12Device* device, _In_ UINT NumDescriptors, _COM_Outptr_  ID3D12Heap** ppvHeap);
HRESULT CreateSamplerDescriptorHeap(_In_ ID3D12Device* device, _In_ UINT NumDescriptors, _COM_Outptr_  ID3D12Heap** ppvHeap);
bool IsDirectXRaytracingSupported(_In_ ID3D12Device* device);
bool IsMeshShaderSupported(_In_ ID3D12Device* device);
bool IsVariableRateShadingSupported(_In_ ID3D12Device* device);
bool IsShaderModelSupported(_In_ ID3D12Device* device, _In_ D3D_SHADER_MODEL shader_model);
HRESULT D3D12Log(_In_ ID3D12Device* device, _In_ D3D12_MESSAGE_SEVERITY Severity, _In_ LPCSTR pDescription);
HRESULT CreateUploadHeapBufferResource(_In_ ID3D12Device* device, _In_reads_bytes_(count) const void* data, _In_ UINT64 count, _COM_Outptr_ ID3D12Resource** ppvResource);
HRESULT CreateDefaultHeapBufferResource(_In_ ID3D12Device* device, _In_reads_bytes_(count) const void* data, _In_ UINT64 count, _COM_Outptr_ ID3D12Resource** ppvResource);
HRESULT CreateDefaultDirectCommandQueue(_In_ ID3D12Device* device, _COM_Outptr_ ID3D12CommandQueue** ppCommandQueue);
HRESULT CreateDefaultCopyCommandQueue(_In_ ID3D12Device* device, _COM_Outptr_ ID3D12CommandQueue** ppCommandQueue);
HRESULT CreateDefaultComputeCommandQueue(_In_ ID3D12Device* device, _COM_Outptr_ ID3D12CommandQueue** ppCommandQueue);
HRESULT CreateDefaultDirectCommandAllocator(_In_ ID3D12Device* device, _COM_Outptr_ ID3D12CommandAllocator** ppCommandAllocator);
HRESULT CreateDefaultCopyCommandAllocator(_In_ ID3D12Device* device, _COM_Outptr_ ID3D12CommandAllocator** ppCommandAllocator);
HRESULT CreateDefaultComputeCommandAllocator(_In_ ID3D12Device* device, _COM_Outptr_ ID3D12CommandAllocator** ppCommandAllocator);
HRESULT FlushCommandQueue(_In_ ID3D12CommandQueue* queue, _In_ ID3D12Fence* fence, _In_ UINT64 value);
HRESULT FlushCommandQueue(_In_ ID3D12CommandQueue* queue);
#endif 
