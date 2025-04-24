#pragma once

#include <Windows.h>
#include <assert.h>
#include <iostream>
#include <string>
#include <memory>
#include <array>
#include <vector>
#include <wrl.h>
#include <map>
#include <unordered_map>


using Microsoft::WRL::ComPtr;


// DirectX12
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

#include <d3d12.h>
#include <dxgi1_6.h>
#include <DirectXMath.h>
using namespace DirectX;

// DX12ShaderCompile
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")


