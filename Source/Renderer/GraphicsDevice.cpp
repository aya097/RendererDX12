#include "GraphicsDevice.h"

GraphicsDevice* g_GraphicsDevice;

GraphicsDevice::GraphicsDevice(HWND hwnd, int width, int height)
{
#ifdef DEBUG
	EnableDebugLayer();
#endif
	_hwnd = hwnd;
	_screenWidth = width;
	_screenHeight = height;

	CreateDevice();
	CreateFactory();
	CreateCommandObjects();
	CreateSwapChain();
	CreateFence();
}

void GraphicsDevice::BeginRender()
{
	auto bbIdx = _swapChain->GetCurrentBackBufferIndex();

	// set barrier
	SetBarrierTransition(_swapChainBuffers[bbIdx].Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);

	// set RenderTarget
	auto rtvHandle = _rtvHeap->GetCPUHandleAt(bbIdx);
	_commandList->OMSetRenderTargets(1, &rtvHandle, false, nullptr);

	// set viewport and scissorrect
	_commandList->RSSetViewports(1, GetViewport());
	_commandList->RSSetScissorRects(1, GetScissor());

	// clear RenderTarget
	_commandList->ClearRenderTargetView(rtvHandle, _backColor, 0, nullptr);
}

void GraphicsDevice::EndRender()
{
	auto bbIdx = _swapChain->GetCurrentBackBufferIndex();

	// set barrier
	SetBarrierTransition(_swapChainBuffers[bbIdx].Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);

	// execute CommandList
	_commandList->Close();
	ID3D12CommandList* commandLists[] = { _commandList.Get() };
	_commandQueue->ExecuteCommandLists(1, commandLists);

	WaitRenderer();

	// reset CommandAllocator and CommandList
	_commandAllocator->Reset();
	_commandList->Reset(_commandAllocator.Get(), nullptr);

	// flip
	_swapChain->Present(1, 0);
}


void GraphicsDevice::SetBackGroundColor(const std::array<float, 4>& color)
{
	std::copy(color.begin(), color.end(), _backColor);
}


void GraphicsDevice::CreateDevice()
{
	D3D_FEATURE_LEVEL levels[] =
	{
		D3D_FEATURE_LEVEL_12_2,
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
	};

	for (auto lv : levels)
	{
		auto result = D3D12CreateDevice(nullptr, lv, IID_PPV_ARGS(&_device));
		if (FAILED(result))
		{
			assert(false && ("CreateDevice is failed"));
		}
	}
}

void GraphicsDevice::CreateFactory()
{
	UINT flag = DXGI_CREATE_FACTORY_DEBUG;
	auto result = CreateDXGIFactory2(flag, IID_PPV_ARGS(&_dxgiFactory));

	if (FAILED(result))
	{
		assert(false && "CreateFactory is failed");
	}
}

void GraphicsDevice::CreateCommandObjects()
{
	auto result = _device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&_commandAllocator));

	if (FAILED(result))
	{
		assert(false && "CreateCommandAlocatpr is failed");
	}

	result = _device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, _commandAllocator.Get(), nullptr, IID_PPV_ARGS(&_commandList));

	if (FAILED(result))
	{
		assert(false && "CreateCommandList is failed");
	}

	D3D12_COMMAND_QUEUE_DESC commandQueueDesc = {};
	commandQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	commandQueueDesc.NodeMask = 0;
	commandQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	commandQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

	result = _device->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(&_commandQueue));

	if (FAILED(result))
	{
		assert(false && "CreateCommandQueue is failed");
	}
}

void GraphicsDevice::CreateSwapChain()
{
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
	swapChainDesc.Width = _screenWidth;
	swapChainDesc.Height = _screenHeight;
	swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapChainDesc.Stereo = false;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;
	swapChainDesc.BufferCount = 2;
	swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	auto result = _dxgiFactory->CreateSwapChainForHwnd(_commandQueue.Get(), _hwnd, &swapChainDesc, nullptr, nullptr, (IDXGISwapChain1**)_swapChain.GetAddressOf());
	
	if (FAILED(result))
	{
		assert(false && "CreateSwapChain is failed");
	}



	int heapNum = 2;
	_rtvHeap = std::make_unique<RTVHeap>(_device.Get(), heapNum);

	for (int index = 0; index < swapChainDesc.BufferCount; index++)
	{
		result = _swapChain->GetBuffer(index, IID_PPV_ARGS(&_swapChainBuffers[index]));
		if (FAILED(result))
		{
			assert(false && "Get SwapChainBuffer is failed");
		}
		_rtvHeap->RegistRTVHeap(_swapChainBuffers[index].Get(), index);
	}
}

void GraphicsDevice::CreateFence()
{
	auto result = _device->CreateFence(_fenceValue, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&_fence));

	if (FAILED(result))
	{
		assert(false && "Create Fence is failed");
	}
}

D3D12_VIEWPORT* GraphicsDevice::GetViewport()
{
	D3D12_VIEWPORT viewport = {};

	viewport.Width = _screenWidth;
	viewport.Height = _screenHeight;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MaxDepth = 1.0f;
	viewport.MinDepth = 0.0f;

	return &viewport;
}
D3D12_RECT* GraphicsDevice::GetScissor() 
{
	D3D12_RECT scissorrect = {};
	scissorrect.top = 0;
	scissorrect.left = 0;
	scissorrect.right = scissorrect.left + _screenWidth;
	scissorrect.bottom = scissorrect.top + _screenHeight;

	return &scissorrect;
}

void GraphicsDevice::SetBarrierTransition(ID3D12Resource* resource, D3D12_RESOURCE_STATES before, D3D12_RESOURCE_STATES after)
{
	D3D12_RESOURCE_BARRIER barrierDesc = {};
	barrierDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrierDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrierDesc.Transition.pResource = resource;
	barrierDesc.Transition.Subresource = 0;
	barrierDesc.Transition.StateBefore = before;
	barrierDesc.Transition.StateAfter = after;
	_commandList->ResourceBarrier(1, &barrierDesc);
}

void GraphicsDevice::WaitRenderer()
{
	_commandQueue->Signal(_fence.Get(), ++_fenceValue);
	if (_fence->GetCompletedValue() != _fenceValue)
	{
		auto event = CreateEvent(nullptr, false, false, nullptr);
		if (!event)
		{
			assert(0 && "Create Event is failed");
		}
		_fence->SetEventOnCompletion(_fenceValue, event);
		WaitForSingleObject(event, INFINITE);
		CloseHandle(event);
	}
}

void GraphicsDevice::EnableDebugLayer()
{
	ID3D12Debug* debugLayer = nullptr;
	D3D12GetDebugInterface(IID_PPV_ARGS(&debugLayer));
	debugLayer->EnableDebugLayer();
	debugLayer->Release();
}


