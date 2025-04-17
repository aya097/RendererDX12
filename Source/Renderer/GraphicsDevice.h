#pragma once
#include "Heap/RTVHeap.h"

class GraphicsDevice
{
public:
	GraphicsDevice(HWND hwnd, int width, int height);

private:
	void CreateDevice();
	void CreateFactory();
	void CreateCommandObjects();
	void CreateSwapChain();
	//void CreateFence();
	//void SetBarrierTransition();
	//void WaitRenderer();
	void EnableDebugLayer();

	HWND _hwnd;
	int _screenWidth = 0;
	int _screenHeight = 0;


	ComPtr<ID3D12Device9> _device = nullptr;
	ComPtr<IDXGIFactory7> _dxgiFactory = nullptr;

	ComPtr<ID3D12CommandAllocator> _commandAllocator = nullptr;
	ComPtr<ID3D12GraphicsCommandList7> _commandList = nullptr;
	ComPtr<ID3D12CommandQueue> _commandQueue = nullptr;

	ComPtr<IDXGISwapChain4> _swapChain = nullptr;
	std::array<ComPtr<ID3D12Resource>, 2> _swapChainBuffers;
	std::unique_ptr<RTVHeap> _rtvHeap = nullptr;
};

extern GraphicsDevice* g_GraphicsDevice;
