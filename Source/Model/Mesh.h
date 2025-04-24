#pragma once
#include "../Renderer//GraphicsDevice.h"

// 三角ポリゴン
class Mesh
{
public:
	Mesh(const std::vector<XMFLOAT3>& vertices);
	D3D12_VERTEX_BUFFER_VIEW GetVertexBufferView() { return _vertexBufferView; }
private:
	ComPtr<ID3D12Resource> _vertexBuffer = nullptr;	// 頂点のデータ
	D3D12_VERTEX_BUFFER_VIEW _vertexBufferView;	// 頂点のビュー
};