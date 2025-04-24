#pragma once
#include "Heap/RTVHeap.h"

class GraphicsDevice
{
public:
	GraphicsDevice(HWND hwnd, int width, int height);
	void BeginRender();
	void EndRender();
	void SetBackGroundColor(const std::array<float, 4> &color);
	ID3D12Device9* GetDevice() const { return _device.Get(); }
	ID3D12GraphicsCommandList7* GetCommandList() const { return _commandList.Get(); }

private:
	void CreateDevice();
	void CreateFactory();
	void CreateCommandObjects();
	void CreateSwapChain();
	void CreateFence();
	D3D12_VIEWPORT* GetViewport();
	D3D12_RECT* GetScissor();
	void SetBarrierTransition(ID3D12Resource* resource, D3D12_RESOURCE_STATES before, D3D12_RESOURCE_STATES after);
	void WaitRenderer();
	void EnableDebugLayer();

	HWND _hwnd;
	int _screenWidth = 0;
	int _screenHeight = 0;
	float _backColor[4] = { 1.0f,1.0f,1.0f,1.0f };


	ComPtr<ID3D12Device9> _device = nullptr;
	ComPtr<IDXGIFactory7> _dxgiFactory = nullptr;

	ComPtr<ID3D12CommandAllocator> _commandAllocator = nullptr;
	ComPtr<ID3D12GraphicsCommandList7> _commandList = nullptr;
	ComPtr<ID3D12CommandQueue> _commandQueue = nullptr;

	ComPtr<IDXGISwapChain4> _swapChain = nullptr;
	std::array<ComPtr<ID3D12Resource>, 2> _swapChainBuffers;
	std::unique_ptr<RTVHeap> _rtvHeap = nullptr;

	ComPtr<ID3D12Fence> _fence = nullptr;
	UINT64 _fenceValue = 0;
};

extern GraphicsDevice* g_GraphicsDevice;
