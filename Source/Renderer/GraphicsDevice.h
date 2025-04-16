#pragma once

class GraphicsDevice
{
public:
	GraphicsDevice(HWND hwnd, int width, int height);

private:
	void CreateDevice();
	void CreateFactory();
	void CreateCommandObjects();
	//void CreateSwapChain(HWND hwnd, int width, int height);
	//void CreateFence();
	//void SetBarrierTransition();
	//void WaitRenderer();
	void EnableDebugLayer();

	ComPtr<ID3D12Device9> _device = nullptr;
	ComPtr<IDXGIFactory7> _dxgiFactory = nullptr;

	ComPtr<ID3D12CommandAllocator> _commandAllocator = nullptr;
	ComPtr<ID3D12GraphicsCommandList7> _commandList = nullptr;
	ComPtr<ID3D12CommandQueue> _commandQueue = nullptr;
};

extern GraphicsDevice* g_GraphicsDevice;
