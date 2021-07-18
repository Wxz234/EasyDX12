#pragma once
#ifndef _EASYDX12_H_
#define _EASYDX12_H_
#include <d3d12.h>
#include <dxgi.h>
#include <sal.h>

//HRESULT EnableDebugLayer();
//HRESULT CreateDefaultDevice(REFIID riid, _COM_Outptr_ void** ppDevice);
//HRESULT CreateDefaultFence(_In_ ID3D12Device* device, UINT64 InitialValue, REFIID riid, _COM_Outptr_ void** ppFence);
//HRESULT CreateDefaultFactory(REFIID riid, _COM_Outptr_ void** ppFactory);
//HRESULT GetDefaultAdapter(_In_ IDXGIFactory* factory, REFIID riid, _COM_Outptr_ void** ppvAdapter);
//HRESULT GetMinimumPowerAdapter(_In_ IDXGIFactory* factory, REFIID riid, _COM_Outptr_ void** ppvAdapter);
//HRESULT GetHighPerformanceAdapter(_In_ IDXGIFactory* factory, REFIID riid, _COM_Outptr_ void** ppvAdapter);

HRESULT GetWarpAdapter(_In_ IDXGIFactory* factory, _COM_Outptr_ IDXGIAdapter** ppvAdapter);
bool IsNVIDIAAdapter(_In_ IDXGIAdapter* adapter);
bool IsAMDAdapter(_In_ IDXGIAdapter* adapter);
bool IsIntelAdapter(_In_ IDXGIAdapter* adapter);
bool IsWarpAdapter(_In_ IDXGIAdapter* adapter);
//HRESULT CreateRTVDescriptorHeap(_In_ ID3D12Device* device, UINT NumDescriptors, REFIID riid, _COM_Outptr_  void** ppvHeap);
//HRESULT CreateCBVDescriptorHeap(_In_ ID3D12Device* device, UINT NumDescriptors, REFIID riid, _COM_Outptr_  void** ppvHeap);
//HRESULT CreateSRVDescriptorHeap(_In_ ID3D12Device* device, UINT NumDescriptors, REFIID riid, _COM_Outptr_  void** ppvHeap);
//HRESULT CreateUAVDescriptorHeap(_In_ ID3D12Device* device, UINT NumDescriptors, REFIID riid, _COM_Outptr_  void** ppvHeap);
//HRESULT CreateDSVDescriptorHeap(_In_ ID3D12Device* device, UINT NumDescriptors, REFIID riid, _COM_Outptr_  void** ppvHeap);
//HRESULT CreateSamplerDescriptorHeap(_In_ ID3D12Device* device, UINT NumDescriptors, REFIID riid, _COM_Outptr_  void** ppvHeap);
//bool IsDirectXRaytracingSupported(_In_ ID3D12Device* device);
//bool IsMeshShaderSupported(_In_ ID3D12Device* device);
//bool IsVariableRateShadingSupported(_In_ ID3D12Device* device);
//bool IsShaderModelSupported(_In_ ID3D12Device* device, D3D_SHADER_MODEL shader_model);
//HRESULT D3D12Log(_In_ ID3D12Device* device, _In_ D3D12_MESSAGE_SEVERITY Severity, _In_ LPCSTR pDescription);
//HRESULT CreateUploadHeapBufferResource(_In_ ID3D12Device* device, _In_reads_bytes_(count) const void* data, UINT64 count, _COM_Outptr_ ID3D12Resource** ppvResource)

HRESULT CreateDefaultDirectCommandQueue(_In_ ID3D12Device* device, _COM_Outptr_ ID3D12CommandQueue** ppCommandQueue);
HRESULT CreateDefaultCopyCommandQueue(_In_ ID3D12Device* device, _COM_Outptr_ ID3D12CommandQueue** ppCommandQueue);
HRESULT CreateDefaultComputeCommandQueue(_In_ ID3D12Device* device, _COM_Outptr_ ID3D12CommandQueue** ppCommandQueue);
HRESULT CreateDefaultDirectCommandAllocator(_In_ ID3D12Device* device, _COM_Outptr_ ID3D12CommandAllocator** ppCommandAllocator);
HRESULT CreateDefaultCopyCommandAllocator(_In_ ID3D12Device* device, _COM_Outptr_ ID3D12CommandAllocator** ppCommandAllocator);
HRESULT CreateDefaultComputeCommandAllocator(_In_ ID3D12Device* device, _COM_Outptr_ ID3D12CommandAllocator** ppCommandAllocator);
HRESULT FlushCommandQueue(_In_ ID3D12CommandQueue* queue, _In_ ID3D12Fence* fence, UINT64 value);
HRESULT FlushCommandQueue(_In_ ID3D12CommandQueue* queue);
#endif 
