#pragma once
#include "../Renderer//GraphicsDevice.h"

// 三角ポリゴン
class Mesh
{
public:
	Mesh(const std::vector<XMFLOAT3>& vertices, const std::vector<uint16_t>& indices);
	D3D12_VERTEX_BUFFER_VIEW GetVertexBufferView() { return _vertexBufferView; }
	D3D12_INDEX_BUFFER_VIEW GetIndexBufferView() { return _indexBufferView; }
private:
	ComPtr<ID3D12Resource> _vertexBuffer = nullptr;	// 頂点のデータ
	D3D12_VERTEX_BUFFER_VIEW _vertexBufferView;	// 頂点のビュー
	ComPtr<ID3D12Resource> _indexBuffer = nullptr;	// インデックスのデータ
	D3D12_INDEX_BUFFER_VIEW _indexBufferView;	// インデックスのビュー

};