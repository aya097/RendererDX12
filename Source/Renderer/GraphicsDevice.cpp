#include "GraphicsDevice.h"

GraphicsDevice* g_GraphicsDevice;

GraphicsDevice::GraphicsDevice(HWND hwnd, int width, int height)
{
#ifdef DEBUG
	EnableDebugLayer();
#endif // DEBUG

	CreateDevice();
	CreateFactory();
	CreateCommandObjects();
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

void GraphicsDevice::EnableDebugLayer()
{
	ID3D12Debug* debugLayer = nullptr;
	D3D12GetDebugInterface(IID_PPV_ARGS(&debugLayer));
	debugLayer->EnableDebugLayer();
	debugLayer->Release();
}


