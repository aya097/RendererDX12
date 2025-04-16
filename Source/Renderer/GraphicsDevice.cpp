#include "GraphicsDevice.h"

GraphicsDevice* g_GraphicsDevice;

GraphicsDevice::GraphicsDevice(HWND hwnd, int width, int height)
{
	CreateDevice;
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