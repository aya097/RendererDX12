#pragma once
#include "../Renderer//GraphicsDevice.h"

// ŽOŠpƒ|ƒŠƒSƒ“
class Mesh
{
public:
	Mesh(const std::vector<XMFLOAT3>& vertices);

private:
	ComPtr<ID3D12Resource> _vertexBuffer = nullptr;
};