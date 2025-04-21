#include "Mesh.h"

Mesh::Mesh(const std::vector<XMFLOAT3>& vertices)
{
	// ヒーププロパティ設定
	D3D12_HEAP_PROPERTIES heapProp = {};
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;	// CPUからアクセス（マップ）できる
	heapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;	// ページング設定、考えなくてよい
	heapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;	// メモリプール設定、考えなくてよい

	// リソース設定
	D3D12_RESOURCE_DESC resourceDesc = {};
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;	// バッファとして利用
	resourceDesc.Alignment = 0;
	resourceDesc.Width = sizeof(XMFLOAT3) * vertices.size();	// widthで全頂点を利用
	resourceDesc.Height = 1;									// Textureであればwidth x height
	resourceDesc.DepthOrArraySize = 1;	// アンチエイリアスは行わない
	resourceDesc.MipLevels = 1;
	resourceDesc.Format = DXGI_FORMAT_UNKNOWN;	// 画像がないのでUNKNOW
	resourceDesc.SampleDesc.Count = 1;
	resourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;	
	resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// 頂点バッファ生成
	auto result = g_GraphicsDevice->GetDevice()->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&resourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&_vertexBuffer));

	if (FAILED(result))
	{
		assert(false && "Create vertex buffer is failed");
	}




}