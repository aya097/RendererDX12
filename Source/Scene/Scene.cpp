#include "Scene.h"

Scene* g_Scene;

void Scene::Init()
{
	// メッシュの頂点
	std::vector<XMFLOAT3> vertices =
	{
		{-0.4f, -0.7f, 0.0f},
		{-0.4f, 0.7f, 0.0f},
		{0.4f, -0.7f, 0.0f},
		{0.4f, 0.7f, 0.0f},
	};
	// インデックス
	std::vector<uint16_t> indices = {
		0,1,2,
		2,1,3
	};

	// メッシュの追加
	_meshes.push_back(std::make_shared<Mesh>(vertices, indices));
	
	// ルートシグネチャ作成
	_rootSignature = std::make_shared<RootSignature>();
	
	// シェーダー作成
	std::shared_ptr<ShaderData> shaderData = std::make_shared<ShaderData>();
	shaderData->SetShader(L"BasicVertexShader.hlsl", ShaderType::VS);
	shaderData->SetShader(L"BasicPixelShader.hlsl", ShaderType::PS);
	
	// パイプラインステート作成
	_pipelineState = std::make_shared<PipelineState>(_rootSignature,shaderData);

}

void Scene::Update()
{

}

void Scene::Draw()
{
	// パイプラインステートセット
	g_GraphicsDevice->GetCommandList()->SetPipelineState(_pipelineState->GetPipelineState());

	// ルートシグネチャセット
	g_GraphicsDevice->GetCommandList()->SetGraphicsRootSignature(_rootSignature->GetRootSignature());

	// トポロジーセット
	g_GraphicsDevice->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// 頂点情報セット
	D3D12_VERTEX_BUFFER_VIEW vbView = _meshes[0]->GetVertexBufferView();
	g_GraphicsDevice->GetCommandList()->IASetVertexBuffers(0, 1, &vbView);
	g_GraphicsDevice->GetCommandList()->DrawInstanced(3, 1, 0, 0);
}